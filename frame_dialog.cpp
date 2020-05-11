#include "frame_dialog.h"
#include "ui_frame_dialog.h"
#include <halconcpp/HalconCpp.h>
#include <QFileDialog>
#include <QString>
#include <QTextCodec>
#include "baojitai.h"
#include "halcon_tools.h"
#include "product.h"

using namespace HalconCpp;

Frame_Dialog::Frame_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Frame_Dialog)
{
    ui->setupUi(this);
    ui->image_window->set_halcon_widget_delegate(this);

    Baojitai* baojitai = Baojitai::instance();
    int x = baojitai->frame_param_.x();
    int y = baojitai->frame_param_.y();
    int w = baojitai->frame_param_.w();
    int h = baojitai->frame_param_.h();
    int mw = baojitai->frame_param_.magic_w();
    int mh = baojitai->frame_param_.magic_h();

    int lx = baojitai->frame_param_.lx();
    int ly = baojitai->frame_param_.ly();
    int lw = baojitai->frame_param_.lw();
    int lh = baojitai->frame_param_.lh();
    int side_hand_magic_w = baojitai->frame_param_.side_hand_magic_w();

    int rx = baojitai->frame_param_.rx();
    int ry = baojitai->frame_param_.ry();
    int rw = baojitai->frame_param_.rw();
    int rh = baojitai->frame_param_.rh();
    int side_hand_magic_h = baojitai->frame_param_.side_hand_magic_h();

    ui->spinBox_x->setValue(x);
    ui->spinBox_y->setValue(y);
    ui->spinBox_w->setValue(w);
    ui->spinBox_h->setValue(h);
    ui->spinBox_disk_magic_width->setValue(mw);
    ui->spinBox_disk_magic_height->setValue(mh);
    ui->spinBox_lx->setValue(lx);
    ui->spinBox_ly->setValue(ly);
    ui->spinBox_lw->setValue(lw);
    ui->spinBox_lh->setValue(lh);
    ui->spinBox_side_hand_magic_x->setValue(side_hand_magic_w);
    ui->spinBox_rx->setValue(rx);
    ui->spinBox_ry->setValue(ry);
    ui->spinBox_rw->setValue(rw);
    ui->spinBox_rh->setValue(rh);
    ui->spinBox_side_hand_magic_y->setValue(side_hand_magic_h);
    detect_finish_ = false;
    disk_ok_ = false;
    found_left_ = false;
    found_right_ = false;

    Product* product = Baojitai::instance()->current_product();
    if (product)
    {
        Product::VisionParam param = product->vision_param();
        ui->spinBox_frame_exposure_time->setValue(param.frame_exposure_time);
        //待保存至每个产品

    }
    connect(Baojitai::instance(), SIGNAL(signal_camera_buffer_updated(Camera*)), this, SLOT(on_camera_buffer_changed(Camera*)), Qt::QueuedConnection);
}

Frame_Dialog::~Frame_Dialog()
{
    delete ui;
}

void Frame_Dialog::on_paint(HalconWidget *, HWindow &halcon_window)
{
    if (!halcon_window.IsHandleValid())
        return;

    if (!halcon_image_.IsInitialized())
        return;

    halcon_window.SetPart(0, 0, (Hlong)halcon_image_.Height(), (Hlong)halcon_image_.Width());
    halcon_window.DispImage(halcon_image_);

    int x = ui->spinBox_x->text().toInt();
    int y = ui->spinBox_y->text().toInt();
    int w = ui->spinBox_w->text().toInt();
    int h = ui->spinBox_h->text().toInt();

    if (!detect_finish_)
    {
        halcontools::draw_rect(halcon_window, x + w * 0.5, y + h * 0.5, 0, w * 0.5, h * 0.5, halcontools::kHalconColorGreen, 1, false);
    }
    else
    {
        if (disk_ok_)
            halcontools::draw_rect(halcon_window, x + w * 0.5, y + h * 0.5, 0, w * 0.5, h * 0.5, halcontools::kHalconColorGreen, 1, false);
        else
            halcontools::draw_rect(halcon_window, x + w * 0.5, y + h * 0.5, 0, w * 0.5, h * 0.5, halcontools::kHalconColorRed, 1, false);

	}

    int lx = ui->spinBox_lx->text().toInt();
    int ly = ui->spinBox_ly->text().toInt();
    int lw = ui->spinBox_lw->text().toInt();
    int lh = ui->spinBox_lh->text().toInt();
    if (detect_finish_ && found_left_)
    {
        halcontools::draw_rect(halcon_window, lx, ly, 0, lw, lh, halcontools::kHalconColorRed, 1, false);
        halcontools::draw_region(halcon_window, left_white_area_, halcontools::kHalconColorRed, 1, true);
    }
    else
    {
        halcontools::draw_rect(halcon_window, lx, ly, 0, lw, lh, halcontools::kHalconColorGreen, 1, false);
    }

    int rx = ui->spinBox_rx->text().toInt();
    int ry = ui->spinBox_ry->text().toInt();
    int rw = ui->spinBox_rw->text().toInt();
    int rh = ui->spinBox_rh->text().toInt();
    if (detect_finish_ && found_right_)
    {
        halcontools::draw_rect(halcon_window, rx, ry, 0, rw, rh, halcontools::kHalconColorRed, 1, false);
        halcontools::draw_region(halcon_window, right_white_area_, halcontools::kHalconColorRed, 1, true);
    }
    else
    {
       halcontools::draw_rect(halcon_window, rx, ry, 0, rw, rh, halcontools::kHalconColorGreen, 1, false);
    }
}

void Frame_Dialog::on_toolButton_select_image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("open image file"), "./", tr("Image files(*.jpg *.png *.bmp *.tif);;All files (*.*)"));
     if (!filename.isNull())
    {
        QTextCodec *code = QTextCodec::codecForName("gb18030");//处理中文字符
        halcon_image_.ReadImage(code->fromUnicode(filename).data());
        detect_finish_ = false;
        ui->image_window->update();
    }
}

void Frame_Dialog::on_pushButton_clicked()
{
    if (!halcon_image_.IsInitialized())
        return;

    QString filename = QFileDialog::getSaveFileName(this,
           tr("Save Image"),
           "",
           tr("*.bmp;;")); //选择路径
    if(filename.isEmpty())
    {
        return;
    }
    else
    {
        halcontools::write_image(halcon_image_, filename.toStdString());
    }
}

void Frame_Dialog::on_camera_buffer_changed(Camera* camera)
{
    if (camera == Baojitai::instance()->camera_check_frame())
    {
        const unsigned char* image_buffer = NULL;
        int width, height;
        Baojitai::instance()->camera_check_frame_buffer(&image_buffer, &width, &height);
        if (image_buffer)
        {
            HImage img("byte", width, height, (void*)image_buffer);
            halcon_image_ = img.CopyImage();
            ui->image_window->update();
        }
    }
}

void Frame_Dialog::on_toolButton_capture_clicked()
{
    Camera* camera = Baojitai::instance()->camera_check_frame();
    if (camera && camera->is_open() && !camera->is_grabbing())
        camera->trigger();
}

void Frame_Dialog::on_spinBox_x_valueChanged(int arg1)
{
    detect_finish_ = false;
    ui->image_window->update();
}

void Frame_Dialog::on_spinBox_y_valueChanged(int arg1)
{
    detect_finish_ = false;
    ui->image_window->update();
}

void Frame_Dialog::on_spinBox_w_valueChanged(int arg1)
{
        detect_finish_ = false;
    ui->image_window->update();
}

void Frame_Dialog::on_spinBox_h_valueChanged(int arg1)
{
        detect_finish_ = false;
    ui->image_window->update();
}

void Frame_Dialog::on_spinBox_h2_valueChanged(int arg1)
{
        detect_finish_ = false;
    ui->image_window->update();
}

void Frame_Dialog::on_spinBox_threshold_area_valueChanged(int arg1)
{
        detect_finish_ = false;
    ui->image_window->update();
}

void Frame_Dialog::on_spinBox_w2_valueChanged(int arg1)
{
    detect_finish_ = false;
    ui->image_window->update();
}

void Frame_Dialog::on_pushButton_save_config_clicked()
{
    int x = ui->spinBox_x->text().toInt();
    int y = ui->spinBox_y->text().toInt();
    int w = ui->spinBox_w->text().toInt();
    int h = ui->spinBox_h->text().toInt();
    int mw = ui->spinBox_disk_magic_width->text().toInt();
    int mh = ui->spinBox_disk_magic_height->text().toInt();
    int lx = ui->spinBox_lx->text().toInt();
    int ly = ui->spinBox_ly->text().toInt();
    int lw = ui->spinBox_lw->text().toInt();
    int lh = ui->spinBox_lh->text().toInt();
    int side_hand_magic_w = ui->spinBox_side_hand_magic_x->text().toInt();
    int rx = ui->spinBox_rx->text().toInt();
    int ry = ui->spinBox_ry->text().toInt();
    int rw = ui->spinBox_rw->text().toInt();
    int rh = ui->spinBox_rh->text().toInt();
    int side_hand_magic_h = ui->spinBox_side_hand_magic_y->text().toInt();
    int frame_exposure_time = ui->spinBox_frame_exposure_time->text().toInt();

	Product* current_product = Baojitai::instance()->current_product();
    Product::VisionParam param = current_product->vision_param();
    param.frame_exposure_time = frame_exposure_time;
    current_product->set_vision_param(param);
    current_product->save_config(ProductManager::instance()->product_config_path(current_product->name()));

    Baojitai* baojitai = Baojitai::instance();
    baojitai->frame_param_.set_x(x);
    baojitai->frame_param_.set_y(y);
    baojitai->frame_param_.set_w(w);
    baojitai->frame_param_.set_h(h);
    baojitai->frame_param_.set_magic_w(mw);
    baojitai->frame_param_.set_magic_h(mh);
    baojitai->frame_param_.set_lx(lx);
    baojitai->frame_param_.set_ly(ly);
    baojitai->frame_param_.set_lw(lw);
    baojitai->frame_param_.set_lh(lh);
    baojitai->frame_param_.set_side_hand_magic_w(side_hand_magic_w);
    baojitai->frame_param_.set_rx(rx);
    baojitai->frame_param_.set_ry(ry);
    baojitai->frame_param_.set_rw(rw);
    baojitai->frame_param_.set_rh(rh);
    baojitai->frame_param_.set_side_hand_magic_h(side_hand_magic_h);
    baojitai->save_frame_param();
}

void Frame_Dialog::on_pushButton_detect_clicked()
{
    if (!halcon_image_.IsInitialized())
        return;

    disk_ok_ = false;
    found_left_ = false;
    found_right_ = false;

    int x = ui->spinBox_x->text().toInt();
    int y = ui->spinBox_y->text().toInt();
    int w = ui->spinBox_w->text().toInt();
    int h = ui->spinBox_h->text().toInt();
    int mw = ui->spinBox_disk_magic_width->text().toInt();
    int mh = ui->spinBox_disk_magic_height->text().toInt();

    cv::HOGDescriptor hog;
    hog.load(Baojitai::instance()->frame_hog_file_path());
    cv::Mat image = halcontools::HImageToIplImage(halcon_image_);
    halcontools::detect_frame_disk(image, hog, x, y, w, h, mw, mh, disk_ok_);

    int lx = ui->spinBox_lx->text().toInt();
    int ly = ui->spinBox_ly->text().toInt();
    int lw = ui->spinBox_lw->text().toInt();
    int lh = ui->spinBox_lh->text().toInt();
    int rx = ui->spinBox_rx->text().toInt();
    int ry = ui->spinBox_ry->text().toInt();
    int rw = ui->spinBox_rw->text().toInt();
    int rh = ui->spinBox_rh->text().toInt();
    int side_hand_magic_w = ui->spinBox_side_hand_magic_x->text().toInt();
    int side_hand_magic_h = ui->spinBox_side_hand_magic_y->text().toInt();
    cv::HOGDescriptor hog_side_hand;
    hog_side_hand.load(Baojitai::instance()->frame_side_hand_hog_file_path());

    int left_rect_x = lx - lw;
    int left_rect_y = ly - lh;
    int left_rect_w = lw * 2;
    int left_rect_h = lh * 2;
    halcontools::detect_frame_side_hand(image, hog_side_hand, left_rect_x, left_rect_y, left_rect_w, left_rect_h,
                                        side_hand_magic_w, side_hand_magic_h, found_left_);


    int right_rect_x = rx - rw;
    int right_rect_y = ry - rh;
    int right_rect_w = rw * 2;
    int right_rect_h = rh * 2;
    halcontools::detect_frame_side_hand(image, hog_side_hand, right_rect_x, right_rect_y, right_rect_w, right_rect_h,
                                        side_hand_magic_w, side_hand_magic_h, found_right_);

    if (disk_ok_ && !found_left_ && !found_right_)
    {
        ui->label_result->setText("OK");
    }
    else
    {
        ui->label_result->setText("NG");
    }

    detect_finish_ = true;
    ui->image_window->update();
}

void Frame_Dialog::on_spinBox_lx_valueChanged(int arg1)
{
    detect_finish_ = false;
    ui->image_window->update();
}

void Frame_Dialog::on_spinBox_ly_valueChanged(int arg1)
{
    detect_finish_ = false;
    ui->image_window->update();
}

void Frame_Dialog::on_spinBox_lw_valueChanged(int arg1)
{
    detect_finish_ = false;
    ui->image_window->update();
}

void Frame_Dialog::on_spinBox_lh_valueChanged(int arg1)
{
    detect_finish_ = false;
    ui->image_window->update();
}

void Frame_Dialog::on_spinBox_rx_valueChanged(const QString &arg1)
{
    detect_finish_ = false;
    ui->image_window->update();
}

void Frame_Dialog::on_spinBox_ry_valueChanged(int arg1)
{
    detect_finish_ = false;
    ui->image_window->update();
}

void Frame_Dialog::on_spinBox_rw_valueChanged(int arg1)
{
    detect_finish_ = false;
    ui->image_window->update();
}

void Frame_Dialog::on_spinBox_rh_valueChanged(int arg1)
{
    detect_finish_ = false;
    ui->image_window->update();
}

void Frame_Dialog::on_pushButton_2_clicked()
{
    if (detect_finish_ && halcon_image_.IsInitialized())
    {
        QString filename = QFileDialog::getSaveFileName(this,
               tr("Save Image"),
               "",
               tr("*.jpg;;")); //选择路径
        if(!filename.isEmpty())
        {
            int x = ui->spinBox_x->text().toInt();
            int y = ui->spinBox_y->text().toInt();
            int w = ui->spinBox_w->text().toInt();
            int h = ui->spinBox_h->text().toInt();


            int lx = ui->spinBox_lx->text().toInt();
            int ly = ui->spinBox_ly->text().toInt();
            int lw = ui->spinBox_lw->text().toInt();
            int lh = ui->spinBox_lh->text().toInt();
            int rx = ui->spinBox_rx->text().toInt();
            int ry = ui->spinBox_ry->text().toInt();
            int rw = ui->spinBox_rw->text().toInt();
            int rh = ui->spinBox_rh->text().toInt();

            cv::Mat image = halcontools::HImageToIplImage(halcon_image_);
            halcontools::write_frame_image_ng(image, disk_ok_, x, y, w, h,
                                              found_left_, lx, ly, lw, lh,
                                              found_right_, rx, ry, rw, rh, filename.toStdString());
        }
    }
}
