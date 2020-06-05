#include "location_config.h"
#include "ui_location_config.h"
#include <ssvision/ssvision>
#include "baojitai.h"
#include <QFileDialog>
#include <QString>
#include <QTextCodec>
#include <QMessageBox>
#include "halcon_tools.h"
#include "main_window.h"

LocationConfigDialog::LocationConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Imageparameter)
{
    ui->setupUi(this);
    ui->image_widget->set_halcon_widget_delegate(this);
	found_ = false;

    setFixedSize(this->width(), this->height());

    setMouseTracking(true);

    ui->image_widget->setMouseTracking(true);


    Product* product = Baojitai::instance()->current_product();
    if (product)
    {
        Product::VisionParam param = product->vision_param();
        ui->lineEdit_drop_z->setText(to_string(param.delta_z_put).c_str());
        ui->lineEdit_grap_z->setText(to_string(param.delta_z).c_str());
        ui->lineEdit_l1->setText(to_string(param.l1).c_str());
        ui->lineEdit_l2->setText(to_string(param.l2).c_str());
        ui->lineEdit_size_var->setText(to_string(param.xl1).c_str());
		ui->spinBox_x_offset->setValue(param.x_offset);
		ui->spinBox_y_offset->setValue(param.y_offset);
		ui->spinBox_z_offset->setValue(param.z_offset);
        ui->spinBox_location_exposure_time->setValue(param.location_exposure_time);
        ui->spinBox_black_region_threshold->setValue(param.black_region_threshold);
        //待保存至每个产品

    }

      Baojitai* baojitai = Baojitai::instance();
//    ui->spinBox_x_offset->setValue(baojitai->robotic_x_offset());
//    ui->spinBox_y_offset->setValue(baojitai->robotic_y_offset());
//    ui->spinBox_z_offset->setValue(baojitai->robotic_rz_offset());


    connect(Baojitai::instance(), SIGNAL(signal_camera_buffer_updated(Camera*)), this, SLOT(on_camera_buffer_changed(Camera*)), Qt::QueuedConnection);
    connect(Baojitai::instance(), SIGNAL(signal_robotic_command(RoboticTCPServer*,QString)), this, SLOT(on_robotic_command(RoboticTCPServer*,QString)));

}

LocationConfigDialog::~LocationConfigDialog()
{
    delete ui;
}

void LocationConfigDialog::closeEvent(QCloseEvent *event)
{
    Camera* camera = Baojitai::instance()->camera_location();
    if (camera && camera->is_open())
    {
        camera->stop();
        camera->close();
        event->accept();
    }
}

void LocationConfigDialog::on_paint2(HalconWidget *, HWindow &halcon_window)
{
    if (!halcon_window.IsHandleValid())
        return;

    if (!halcon_image_.IsInitialized())
        return;

    halcon_window.SetPart(0, 0, (Hlong)halcon_image_.Height(), (Hlong)halcon_image_.Width());
    halcon_window.DispImage(halcon_image_);

    int x = ui->spinBox_x->text().toInt();
    int y = ui->spinBox_y->text().toInt();
    int phi = ui->doubleSpinBox_phi->text().toInt();
    int w = ui->spinBox_width->text().toInt();
    int h = ui->spinBox_height->text().toInt();

    halcontools::draw_rect(halcon_window, x + w * 0.5, y + h * 0.5, 0, w * 0.5, h * 0.5, halcontools::kHalconColorGreen, 1, false);

}

void LocationConfigDialog::on_paint(HalconWidget *, HWindow &halcon_window)
{
    if (!halcon_window.IsHandleValid())
        return;
    if (halcon_image_.IsInitialized())
    {
        halcon_window.SetPart(0, 0, (Hlong)halcon_image_.Height(), (Hlong)halcon_image_.Width());
        halcon_window.DispImage(halcon_image_);
        halcon_window.SetLineWidth(10);
        halcon_window.SetRgb(128, 128, 128);
        halcon_window.DispCross(
                    halcon_image_.Height() * 0.5,
                    halcon_image_.Width() * 0.5,
                    halcon_image_.Height() * 0.9,
                    0
                    );
    }
	if (found_)
	{
        halcontools::draw_rect(halcon_window, x_, y_, phi_, l1_, l2_, halcontools::kHalconColorRed, 1, false);
        float x1 = x_ + l1_ * cos(phi_);
        float y1 = y_ - l1_ * sin(phi_);
        float x2 = x_ - l1_ * cos(phi_);
        float y2 = y_ + l1_ * sin(phi_);
        halcontools::draw_line(halcon_window, x1, y1, x2, y2, halcontools::kHalconColorBlue);
        float pi_2 = 3.14159f * 0.5;
        float x3 = x_ + l2_ * cos(pi_2 + phi_);
        float y3 = y_ - l2_ * sin(pi_2 + phi_);
        float x4 = x_ - l2_ * cos(pi_2 + phi_);
        float y4 = y_ + l2_ * sin(pi_2 + phi_);
        halcontools::draw_line(halcon_window, x3, y3, x4, y4, halcontools::kHalconColorBlue);

        HHomMat2D mat = Baojitai::instance()->image_to_robotic_matrix();
        halcontools::transform_point(mat, x3, y3, x3, y3);
        halcontools::transform_point(mat, x4, y4, x4, y4);
        float dx = x1 - x2;
        float dy = y1 - y2;
        float width_mm = sqrt(dx * dx + dy * dy);
        dx = x3 - x4;
        dy = y3 - y4;
        float height_mm = sqrt(dx * dx + dy * dy);
    }
}

void LocationConfigDialog::on_toolButton_choose_image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("open image file"), "./", tr("Image files(*.jpg *.png *.bmp *.tif);;All files (*.*)"));
     if (!filename.isNull())
    {
        QTextCodec *code = QTextCodec::codecForName("gb18030");//处理中文字符
        halcon_image_.ReadImage(code->fromUnicode(filename).data());
        support_location_ = true;
		found_ = false;
        ui->image_widget->update();
    }
}

void LocationConfigDialog::on_toolButton_extract_clicked()
{
	char file_name[128];
	memset(file_name, 0, 128);
	sprintf(file_name, "location.log");
	std::ofstream out_log(file_name);
	if (!halcon_image_.IsInitialized())
		return;
	out_log << "this" << endl;
//    for (int row = 152; row < 500; row++)
//    {
//        for (int col = 765; col < 1662; ++col)
//        {
//            //unsigned char* byte = img_data + row * width + col;
//            //*byte = 255;
//            halcon_image_.SetGrayval(row, col, 255);
//        }
//    }

//    for (int row = 1354; row < 1652; row++)
//    {
//        for (int col = 569; col < 1357; col++)
//        {
//            //unsigned char* byte = img_data + row * width + col;
//            //*byte = 255;
//            halcon_image_.SetGrayval(row, col, 255);
//        }
//    }

    int black_threshold = ui->spinBox_black_region_threshold->text().toInt();

	int width = halcon_image_.Width();
	int height = halcon_image_.Height();

    halcontools::extract_rect(halcon_image_, &x_, &y_, &phi_, &l1_, &l2_, &found_, black_threshold);
   
    out_log << "start" << endl;
    
    out_log << "koko" << endl;
//    if (found_ && (l1_ * 2 < width *0.2 || l1_ * 2 > width*0.9 || l2_ * 2 < height * 0.2 || l2_ * 2 > height * 0.9 ))
//    {
//        found_ = false;
//    }

	if (found_)
    {
        //halcontools::draw_rect(halcon_window, x_, y_, phi_, l1_, l2_, halcontools::kHalconColorRed, 1, false);
        float x1 = x_ + l1_ * cos(phi_);
        float y1 = y_ - l1_ * sin(phi_);
        float x2 = x_ - l1_ * cos(phi_);
        float y2 = y_ + l1_ * sin(phi_);
        //halcontools::draw_line(halcon_window, x1, y1, x2, y2, halcontools::kHalconColorBlue);
        float pi_2 = 3.14159f * 0.5;
        float x3 = x_ + l2_ * cos(pi_2 + phi_);
        float y3 = y_ - l2_ * sin(pi_2 + phi_);
        float x4 = x_ - l2_ * cos(pi_2 + phi_);
        float y4 = y_ + l2_ * sin(pi_2 + phi_);
        //halcontools::draw_line(halcon_window, x3, y3, x4, y4, halcontools::kHalconColorBlue);
        out_log << "114" << endl;
        HHomMat2D mat = Baojitai::instance()->image_to_robotic_matrix();
        halcontools::transform_point(mat, x1, y1, x1, y1);
        halcontools::transform_point(mat, x2, y2, x2, y2);
        halcontools::transform_point(mat, x3, y3, x3, y3);
        halcontools::transform_point(mat, x4, y4, x4, y4);
        float dx = x1 - x2;
        float dy = y1 - y2;
        float width_mm = sqrt(dx * dx + dy * dy);
        dx = x3 - x4;
        dy = y3 - y4;
        float height_mm = sqrt(dx * dx + dy * dy);
        out_log << "514" << endl;
        QString size_str;
        size_str.sprintf("[%0.2f, %0.2f]", width_mm, height_mm);
        ui->label_size->setText(size_str);
        ui->image_widget->update();
        ui->lineEdit_l1->setText(QString::number((int)width_mm));
        ui->lineEdit_l2->setText(QString::number((int)height_mm));
    }
}

void LocationConfigDialog::on_pushButton_save_image_clicked()
{
    if (!halcon_image_.IsInitialized())
    {
        //QMessageBox::warning(this, QStringLiteral("图片为空"), QStringLiteral("请先拍照或者选择图片"), QMessageBox::StandardButton::Ok);
        return;
    }

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

void LocationConfigDialog::on_robotic_command(RoboticTCPServer* robotic_tcp_server, QString command)
{
    if (command.toStdString().compare("t") != 0 &&
            command.toStdString().compare("T") != 0 &&
            command.toStdString().compare("s") != 0 &&
            command.toStdString().compare("S") != 0)
        return;

    Baojitai* baojitai = Baojitai::instance();
    Product* product = baojitai->current_product();
    if (found_ && product)
    {
        Product::VisionParam param = product->vision_param();
        float x = x_;
        float y = y_;
        halcontools::transform_point(baojitai->image_to_robotic_matrix(), x, y, x, y);
        float dz = param.delta_z;
        float r = phi_;
        float s = param.delta_z_put;
        baojitai->send_product_information_to_robotic(x, y, dz, r, s);
    }
}

void LocationConfigDialog::on_toolButton_save_product_param_clicked()
{
	char file_name[128];
	memset(file_name, 0, 128);
	sprintf(file_name, "location_param.log");
	std::ofstream out_log(file_name);
	out_log << "start" << endl;

    Product* current_product = Baojitai::instance()->current_product();
    if (!current_product)
    {
        QMessageBox::warning(this, QStringLiteral("未知产品型号"), QStringLiteral("请先创建选择产品"), QMessageBox::StandardButton::Ok);
        return;
    }

    int grab_z = ui->lineEdit_grap_z->text().toInt();
    int drop_z = ui->lineEdit_drop_z->text().toInt();

    ui->lineEdit_grap_z->setText(to_string(grab_z).c_str());
    ui->lineEdit_drop_z->setText(to_string(drop_z).c_str());

    if (grab_z < 5 || grab_z > 1000 || drop_z < 5 || drop_z > 1000)
    {
        QMessageBox::warning(this, QStringLiteral("Z Out of range"), QStringLiteral("5 ~ 400"), QMessageBox::StandardButton::Ok);
        return;
    }

    int l1 = ui->lineEdit_l1->text().toInt();
    int l2 = ui->lineEdit_l2->text().toInt();
    if (l1 < 100 || l1 > 800 || l2 < 100 || l2 > 800)
    {
        QMessageBox::warning(this, QStringLiteral("L Out of range"), QStringLiteral("100 ~ 800"), QMessageBox::StandardButton::Ok);
        return;
    }

    int size_var = ui->lineEdit_size_var->text().toInt();
    int x_offset = ui->spinBox_x_offset->text().toInt();
    int y_offset =ui->spinBox_y_offset->text().toInt();
    int z_offset =ui->spinBox_z_offset->text().toInt();
    int location_exposure_time =ui->spinBox_location_exposure_time->text().toInt();
    int black_region_threshold =ui->spinBox_black_region_threshold->text().toInt();

    Product::VisionParam param = current_product->vision_param();
    param.delta_z = grab_z;
    param.delta_z_put = drop_z;
    param.l1 = l1;
    param.l2 = l2;
    param.xl1 = size_var;
    param.x_offset = x_offset;
    param.y_offset = y_offset;
    param.location_exposure_time = location_exposure_time;
    param.z_offset = z_offset;
    param.black_region_threshold = black_region_threshold;
    current_product->set_vision_param(param);
    current_product->save_config(ProductManager::instance()->product_config_path(current_product->name()));

    QMessageBox::warning(this, QStringLiteral("Success"), QStringLiteral("Saved"), QMessageBox::StandardButton::Ok);
}

void LocationConfigDialog::on_toolButton_clicked()
{
    Camera* camera = Baojitai::instance()->camera_location();
    if (camera && !camera->is_open())
    {
        camera->open();
        if (camera && camera->is_open() && !camera->is_grabbing())
        {
          camera->trigger();
        }
    }
    if (camera && camera->is_open() && !camera->is_grabbing())
        camera->trigger();
}

void LocationConfigDialog::on_camera_buffer_changed(Camera* camera)
{
    if (camera == Baojitai::instance()->camera_location())
    {
        const unsigned char* image_buffer = NULL;
        int width, height;
        Baojitai::instance()->camera_location_buffer(&image_buffer, &width, &height);
        if (image_buffer)
        {
            HImage img("byte", width, height, (void*)image_buffer);
            halcon_image_ = img.CopyImage();
            ui->image_widget->update();
        }
    }
}

void LocationConfigDialog::on_pushButton_save_result_image_clicked()
{
    if (halcon_image_.IsInitialized())
    {
        QString filename = QFileDialog::getSaveFileName(this,
               tr("Save Image"),
               "",
               tr("*.jpg;;")); //选择路径
        if(!filename.isEmpty())
        {
            cv::Mat image = halcontools::HImageToIplImage(halcon_image_);
            halcontools::write_location_image_ng(image, found_, x_, y_, phi_, l1_, l2_, "unknown", filename.toStdString());
        }
    }
}

//void LocationConfigDialog::on_spinBox_x_offset_valueChanged(int arg1)
//{
//    Baojitai::instance()->set_robotic_x_offset(arg1);
//}

//void LocationConfigDialog::on_spinBox_y_offset_valueChanged(int arg1)
//{
//    Baojitai::instance()->set_robotic_y_offset(arg1);
//}

//void LocationConfigDialog::on_spinBox_z_offset_valueChanged(int arg1)
//{
//    Baojitai::instance()->set_robotic_rz_offset(arg1);
//}


//void LocationConfigDialog::on_toolButton_2_clicked()
//{
//    if (!halcon_image_.IsInitialized())
//    {
//      QMessageBox::information(this, QStringLiteral("未选择图片"), QStringLiteral("请先选择图片或拍照获取图片"), QMessageBox::StandardButton::Ok);
//      return;
//    }
//    editing_ = true;
//    mark_x_ = ((Hlong)halcon_image_.Width()) * 0.5;
//    mark_y_ = (Hlong)halcon_image_.Height() * 0.5;
//    mark_phi_ = 0;
//    mark_l1_ = 400;
//    mark_l2_ = 400;
//    mark_moving_ = false;
//    mark_scaling_ = false;
//    mark_can_moving_ = false;
//    mark_can_scaling_ = false;
//    ui->image_widget->update();
//}

//void LocationConfigDialog::on_paint(HalconWidget *, HWindow &halcon_window)
//{
//    if (!halcon_window.IsHandleValid())
//        return;
//    if (!halcon_image_.IsInitialized())
//        return;

//    halcon_window.SetPart(0, 0, (Hlong)halcon_image_.Height() - 1, (Hlong)halcon_image_.Width() - 1);
//    halcon_window.DispImage(halcon_image_);

//    if (editing_)
//    {
//		const char* cross_color = halcontools::kHalconColorBlue;
//		const char* circle_color = halcontools::kHalconColorBlue;
//		if (mark_moving_)
//		{
//			cross_color = halcontools::kHalconColorGreen;
//			circle_color = cross_color;
//		}
//		else if (mark_scaling_)
//		{
//			circle_color = halcontools::kHalconColorGreen;
//		}
//		else if (mark_can_moving_)
//		{
//			cross_color = halcontools::kHalconColorGreen;
//		}
//		else if (mark_can_scaling_)
//		{
//			circle_color = halcontools::kHalconColorGreen;
//		}

//        //halcontools::draw_cross(halcon_window, mark_x_, mark_y_, mark_cross_r_, cross_color, 0);
//        halcontools::draw_rect(halcon_window, mark_x_, mark_y_, mark_phi_, mark_l1_, mark_l2_, circle_color, 1, false);
//    }

//	foreach(Material material, Material_)
//	{
//        halcontools::draw_rect(halcon_window, material.x, material.y, material.phi, material.r1, material.r2, halcontools::kHalconColorRed, 1, false);
//	}

//    foreach(QModelIndex index, ui->tableView->selectionModel()->selectedIndexes()) {
//        int idx = index.row();
//        Ellipse ellipse = ellipses_[idx];
//        halcontools::draw_cross(halcon_window, ellipse.x, ellipse.y, mark_cross_r_, halcontools::kHalconColorGreen, 45, 2);
//    }
//}

//void LocationConfigDialog::mouseMoveEvent(QMouseEvent *event)
//{
//	if (!editing_)
//		return;

//    int widget_width = ui->image_widget->width();
//    int image_width = halcon_image_.Width();
//    int image_height = halcon_image_.Height();
//    int unit_length = 20.0 / widget_width * image_width;
//	mark_cross_r_ = unit_length;
//    int row, col;
//    HalconWidget::parent_widget_position_to_image_row_col(this, event->pos(), ui->image_widget, image_width, image_height, &row, &col, NULL);
//    int delta_x = col - mark_x_;
//    int delta_y = row - mark_y_;
//    int dist_2 = delta_x * delta_x + delta_y * delta_y;
//    if (dist_2 < unit_length * unit_length)
//    {
//        mark_can_moving_ = true;
//        mark_can_scaling_ = false;
//    }
//    else
//    {
//        int r_min = mark_r_ - unit_length;
//        int r_max = mark_r_ + unit_length;
//        if (r_min > 0 && r_max > 0)
//        {
//            int dist_min_2 = r_min * r_min;
//            int dist_max_2 = r_max * r_max;
//            if (dist_2 > dist_min_2 && dist_2 < dist_max_2)
//            {
//                mark_can_scaling_ = true;
//                mark_can_moving_ = false;
//            }
//			else
//			{
//				mark_can_moving_ = false;
//				mark_can_scaling_ = false;
//			}
//        }
//		else
//		{
//			mark_can_moving_ = false;
//			mark_can_scaling_ = false;
//		}
//    }

//	if (mark_moving_)
//	{
//        col = col < 0 ? 0 : col;
//        col = col > image_width ? image_width : col;
//        row = row < 0 ? 0 : row;
//        row = row > image_height ? image_height : row;
//		mark_x_ = col;
//		mark_y_ = row;
//	}
//	else if (mark_scaling_)
//	{
//		int mark_mouse_dist = sqrt(dist_2);
//		int delta_dist = 1.0 * (mark_mouse_dist - mark_mouse_dist_) * widget_width / image_width;
//		mark_r_ = mark_r_ + delta_dist;
//		if (mark_r_ < unit_length + 1)
//		{
//			mark_r_ = unit_length + 1;
//		}
//		else if (mark_r_ > image_width * 0.3)
//		{
//			mark_r_ = image_width * 0.3;
//		}
//		mark_mouse_dist_ = mark_mouse_dist;
//	}
//    ui->image_widget->update();
//}

//void LocationConfigDialog::mousePressEvent(QMouseEvent *event)
//{
//    static int n = 0;
//    if (event->button() == Qt::LeftButton)
//    {
//        QWidget *widget = childAt(event->pos());
//        if(widget == ui->image_widget && editing_)
//        {
//			if (mark_can_moving_)
//			{
//				mark_moving_ = true;
//			}
//			else if (mark_can_scaling_)
//			{
//				mark_scaling_ = true;
//				int image_width = halcon_image_.Width();
//				int image_height = halcon_image_.Height();
//				int row, col;
//				HalconWidget::parent_widget_position_to_image_row_col(this, event->pos(), ui->image_widget, image_width, image_height, &row, &col, NULL);
//				int dx = col - mark_x_;
//				int dy = row - mark_y_;
//				mark_mouse_dist_ = sqrt(dx * dx + dy * dy);
//			}
//        }
//    }
//    ui->image_widget->update();
//}

//void LocationConfigDialog::mouseReleaseEvent(QMouseEvent *event)
//{
//    if (event->button() == Qt::LeftButton)
//    {
//		mark_moving_ = false;
//		mark_scaling_ = false;
//	}
//    if (event->button() == Qt::RightButton)
//    {
//        if (editing_ && extract_current_marker())
//			editing_ = false;
//    }
//    if (!editing_ && ellipses_.size() > 0 && childAt(event->pos()) == ui->image_widget)
//    {
//        int image_width = halcon_image_.Width();
//        int image_height = halcon_image_.Height();
//        int row, col;
//        HalconWidget::parent_widget_position_to_image_row_col(this, event->pos(), ui->image_widget, image_width, image_height, &row, &col, NULL);
//        int ellipse_idx = -1;
//        for (int i = 0; i < ellipses_.size(); ++i)
//        {
//            Ellipse ellipse = ellipses_[i];
//            float dx = ellipse.x - col;
//            float dy = ellipse.y - row;
//            float dist = sqrt(dx*dx+dy*dy);
//            if (dist < (ellipse.r1 + ellipse.r2) * 0.5)
//            {
//                ellipse_idx = i;
//                break;
//            }
//        }
//        if (ellipse_idx != -1)
//        {
//            QModelIndex select_index = item_model_markers_.index(ellipse_idx, 0);
//            ui->tableView->selectionModel()->select(QItemSelection(select_index, select_index), QItemSelectionModel::Select | QItemSelectionModel::Rows);
//            ui->tableView_2->selectionModel()->select(QItemSelection(select_index, select_index), QItemSelectionModel::Select | QItemSelectionModel::Rows);
//        }
//    }
//    ui->image_window->update();
//}

void LocationConfigDialog::on_toolButton_2_clicked()
{

	ui->image_widget->update();
}

void LocationConfigDialog::on_spinBox_x_valueChanged(int arg1)
{
	support_location_ = true;
	ui->image_widget->update();
}

void LocationConfigDialog::on_spinBox_y_valueChanged(int arg1)
{
	support_location_ = true;
	ui->image_widget->update();
}

void LocationConfigDialog::on_spinBox_width_valueChanged(int arg1)
{
	support_location_ = true;
	ui->image_widget->update();
}

void LocationConfigDialog::on_spinBox_height_valueChanged(int arg1)
{
	support_location_ = true;
	ui->image_widget->update();
}

void LocationConfigDialog::on_doubleSpinBox_phi_valueChanged(double arg1)
{
	support_location_ = true;
	ui->image_widget->update();
}
