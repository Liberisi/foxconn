#include "position_calibrate.h"
#include "ui_position_calibrate.h"
#include <QFileDialog>
#include <QTextCodec>
#include <QMessageBox>
#include <QMouseEvent>
#include <iostream>

#include "halcon_tools.h"
#include "baojitai.h"

PositionCalibrate::PositionCalibrate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PositionCalibrate)
{
    calibrate_finish_ = false;
    editing_ = false;
    ui->setupUi(this);\

    setFixedSize(this->width(), this->height());

	setMouseTracking(true);
    ui->mid_str->setMouseTracking(true);
	ui->image_window->setMouseTracking(true);

    QStandardItem *header_0 = new QStandardItem;
    header_0->setData("x", 0);
    QStandardItem *header_1 = new QStandardItem;
    header_1->setData("y", 0);
    item_model_markers_.setHorizontalHeaderItem(0, header_0);
    item_model_markers_.setHorizontalHeaderItem(1, header_1);
    ui->tableView->setModel(&item_model_markers_);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    item_model_editable_markers_.setHorizontalHeaderItem(0, header_0);
    item_model_editable_markers_.setHorizontalHeaderItem(1, header_1);
    ui->tableView_2->setModel(&item_model_editable_markers_);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->image_window->set_halcon_widget_delegate(this);

    connect(ui->tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(on_tableview_selection_changed(QItemSelection,QItemSelection)));
    connect(ui->tableView_2->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(on_tableview_selection_changed(QItemSelection,QItemSelection)));

    connect(Baojitai::instance(), SIGNAL(signal_camera_buffer_updated(Camera*)), this, SLOT(on_camera_buffer_changed(Camera*)), Qt::QueuedConnection);
    connect(Baojitai::instance(), SIGNAL(signal_robotic_command(RoboticTCPServer*,QString)), this, SLOT(on_robotic_command(RoboticTCPServer*,QString)));
}

PositionCalibrate::~PositionCalibrate()
{
    delete ui;
}

void PositionCalibrate::on_robotic_command(RoboticTCPServer* robotic_tcp_server, QString command)
{
    if (command.toStdString().compare("t") != 0 && command.toStdString().compare("T") != 0)
        return;

     QModelIndexList list = ui->tableView->selectionModel()->selectedIndexes();
     if (list.length() == 0)
         return;

     QModelIndex index = list[0];
     int row = index.row();
     if (row >= ellipses_.size())
         return;
     Ellipse ellipse = ellipses_[row];
     HalconCpp::HHomMat2D mat = Baojitai::instance()->image_to_robotic_matrix();
     float x, y;
     halcontools::transform_point(mat, ellipse.x, ellipse.y, x, y);
     Product* product = Baojitai::instance()->current_product();
     Product::VisionParam param;
     if (product)
     {
         param.delta_z = product->vision_param().delta_z;
         param.delta_z_put = product->vision_param().delta_z_put;
     }

     float test_rotation[7] = {0,
                               -10 * 3.14 / 180,
                               10 * 3.14 / 180,
                               -20 * 3.14 / 180,
                               20 * 3.14 / 180,
                               -30 * 3.14 / 180,
                               30 * 3.14 / 180};
     static int test_rotation_index = 0;
     Baojitai::instance()->send_product_information_to_robotic(x, y, param.delta_z, test_rotation[test_rotation_index++], param.delta_z_put);
     if (test_rotation_index == sizeof(test_rotation) / sizeof(test_rotation[0]))
     {
         test_rotation_index = 0;
     }
}

void PositionCalibrate::on_paint(HalconWidget *, HWindow &halcon_window)
{
    if (!halcon_window.IsHandleValid())
        return;
    if (!halcon_image_.IsInitialized())
        return;

    halcon_window.SetPart(0, 0, (Hlong)halcon_image_.Height() - 1, (Hlong)halcon_image_.Width() - 1);
    halcon_window.DispImage(halcon_image_);

    if (editing_)
    {
		const char* cross_color = halcontools::kHalconColorBlue;
		const char* circle_color = halcontools::kHalconColorBlue;
		if (mark_moving_)
		{
			cross_color = halcontools::kHalconColorGreen;
			circle_color = cross_color;
		}
		else if (mark_scaling_)
		{
			circle_color = halcontools::kHalconColorGreen;
		}
		else if (mark_can_moving_)
		{
			cross_color = halcontools::kHalconColorGreen;
		}
		else if (mark_can_scaling_)
		{
			circle_color = halcontools::kHalconColorGreen;
		}

        //halcontools::draw_cross(halcon_window, mark_x_, mark_y_, mark_cross_r_, cross_color, 0);
        halcontools::draw_circle(halcon_window, mark_x_, mark_y_, mark_r_, circle_color, 1, false);
    }

	foreach(Ellipse ellipse, ellipses_)
	{
        halcontools::draw_circle(halcon_window, ellipse.x, ellipse.y, ellipse.r1, halcontools::kHalconColorRed, 1, false);
	}

    foreach(QModelIndex index, ui->tableView->selectionModel()->selectedIndexes()) {
        int idx = index.row();
        Ellipse ellipse = ellipses_[idx];
        halcontools::draw_cross(halcon_window, ellipse.x, ellipse.y, mark_cross_r_, halcontools::kHalconColorGreen, 45, 2);
    }
}

void PositionCalibrate::mouseMoveEvent(QMouseEvent *event)
{
	if (!editing_)
		return;

    int widget_width = ui->image_window->width();
    int image_width = halcon_image_.Width();
    int image_height = halcon_image_.Height();
    int unit_length = 20.0 / widget_width * image_width;
	mark_cross_r_ = unit_length;
    int row, col;
    HalconWidget::parent_widget_position_to_image_row_col(this, event->pos(), ui->image_window, image_width, image_height, &row, &col, NULL);
    int delta_x = col - mark_x_;
    int delta_y = row - mark_y_;
    int dist_2 = delta_x * delta_x + delta_y * delta_y;
    if (dist_2 < unit_length * unit_length)
    {
        mark_can_moving_ = true;
        mark_can_scaling_ = false;
    }
    else
    {
        int r_min = mark_r_ - unit_length;
        int r_max = mark_r_ + unit_length;
        if (r_min > 0 && r_max > 0)
        {
            int dist_min_2 = r_min * r_min;
            int dist_max_2 = r_max * r_max;
            if (dist_2 > dist_min_2 && dist_2 < dist_max_2)
            {
                mark_can_scaling_ = true;
                mark_can_moving_ = false;
            }
			else
			{
				mark_can_moving_ = false;
				mark_can_scaling_ = false;
			}
        }
		else
		{
			mark_can_moving_ = false;
			mark_can_scaling_ = false;
		}
    }

	if (mark_moving_)
	{
        col = col < 0 ? 0 : col;
        col = col > image_width ? image_width : col;
        row = row < 0 ? 0 : row;
        row = row > image_height ? image_height : row;
		mark_x_ = col;
		mark_y_ = row;
	}
	else if (mark_scaling_)
	{
		int mark_mouse_dist = sqrt(dist_2);
		int delta_dist = 1.0 * (mark_mouse_dist - mark_mouse_dist_) * widget_width / image_width;
		mark_r_ = mark_r_ + delta_dist;
		if (mark_r_ < unit_length + 1)
		{
			mark_r_ = unit_length + 1;
		}
		else if (mark_r_ > image_width * 0.3)
		{
			mark_r_ = image_width * 0.3;
		}
		mark_mouse_dist_ = mark_mouse_dist;
	}
    ui->image_window->update();
}

void PositionCalibrate::mousePressEvent(QMouseEvent *event)
{
    static int n = 0;
    if (event->button() == Qt::LeftButton)
    {
        QWidget *widget = childAt(event->pos());
        if(widget == ui->image_window && editing_)
        {
			if (mark_can_moving_)
			{
				mark_moving_ = true;
			}
			else if (mark_can_scaling_)
			{
				mark_scaling_ = true;
				int image_width = halcon_image_.Width();
				int image_height = halcon_image_.Height();
				int row, col;
				HalconWidget::parent_widget_position_to_image_row_col(this, event->pos(), ui->image_window, image_width, image_height, &row, &col, NULL);
				int dx = col - mark_x_;
				int dy = row - mark_y_;
				mark_mouse_dist_ = sqrt(dx * dx + dy * dy);
			}
        }
    }
    ui->image_window->update();
}

void PositionCalibrate::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
		mark_moving_ = false;
		mark_scaling_ = false;
	}
    if (event->button() == Qt::RightButton)
    {
        if (editing_ && extract_current_marker())
			editing_ = false;
    }
    if (!editing_ && ellipses_.size() > 0 && childAt(event->pos()) == ui->image_window)
    {
        int image_width = halcon_image_.Width();
        int image_height = halcon_image_.Height();
        int row, col;
        HalconWidget::parent_widget_position_to_image_row_col(this, event->pos(), ui->image_window, image_width, image_height, &row, &col, NULL);
        int ellipse_idx = -1;
        for (int i = 0; i < ellipses_.size(); ++i)
        {
            Ellipse ellipse = ellipses_[i];
            float dx = ellipse.x - col;
            float dy = ellipse.y - row;
            float dist = sqrt(dx*dx+dy*dy);
            if (dist < (ellipse.r1 + ellipse.r2) * 0.5)
            {
                ellipse_idx = i;
                break;
            }
        }
        if (ellipse_idx != -1)
        {
            QModelIndex select_index = item_model_markers_.index(ellipse_idx, 0);
            ui->tableView->selectionModel()->select(QItemSelection(select_index, select_index), QItemSelectionModel::Select | QItemSelectionModel::Rows);
            ui->tableView_2->selectionModel()->select(QItemSelection(select_index, select_index), QItemSelectionModel::Select | QItemSelectionModel::Rows);
        }
    }
    ui->image_window->update();
}

void PositionCalibrate::on_toolButton_select_image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.bmp *.tif)"));
    if (filename.length() > 0)
    {
        QTextCodec *code = QTextCodec::codecForName("gb18030");
        halcon_image_.ReadImage(code->fromUnicode(filename).data());
        editing_ = false;
        ui->image_window->update();
    }
}

void PositionCalibrate::on_toolButton_add_mark_clicked()
{
    if (!halcon_image_.IsInitialized())
    {
        QMessageBox::information(this, QStringLiteral("未选择图片"), QStringLiteral("请先选择图片或拍照获取图片"), QMessageBox::StandardButton::Ok);
		return;
    }
    editing_ = true;
	mark_x_ = ((Hlong)halcon_image_.Width()) * 0.5;
	mark_y_ = (Hlong)halcon_image_.Height() * 0.5;
	mark_r_ = 100;
    mark_moving_ = false;
    mark_scaling_ = false;
    mark_can_moving_ = false;
    mark_can_scaling_ = false;
	ui->image_window->update();
}

void PositionCalibrate::on_tableview_selection_changed(QItemSelection selected, QItemSelection deselected)
{
    ui->tableView->selectionModel()->select(selected, QItemSelectionModel::Select | QItemSelectionModel::Rows);
    ui->tableView->selectionModel()->select(deselected, QItemSelectionModel::Deselect | QItemSelectionModel::Rows);
    ui->tableView_2->selectionModel()->select(selected, QItemSelectionModel::Select | QItemSelectionModel::Rows);
    ui->tableView_2->selectionModel()->select(deselected, QItemSelectionModel::Deselect | QItemSelectionModel::Rows);
    ui->image_window->update();
}

bool PositionCalibrate::extract_current_marker()
{
	float x, y, r1, r2, angle;
	bool found;
	halcontools::extract_ellipse(halcon_image_, mark_x_, mark_y_, mark_r_, &x, &y, &r1, &r2, &angle, &found);
	if (found)
	{
		Ellipse ellipse;
		ellipse.x = x;
		ellipse.y = y;
		ellipse.r1 = r1;
		ellipse.r2 = r2;
		ellipse.phi = angle;
		ellipses_.push_back(ellipse);

        QStandardItem* item1 = new QStandardItem;
         item1->setData(x, 0);
         QStandardItem* item2 = new QStandardItem;
         item2->setData(y, 0);
         QList<QStandardItem *> row;
         row.append(item1);
         row.append(item2);
        item_model_markers_.appendRow(row);

        QStandardItem* item3 = new QStandardItem;
         item3->setData(0.00, 0);
         QStandardItem* item4 = new QStandardItem;
         item4->setData(0.00, 0);
         QList<QStandardItem *> row2;
         row2.append(item3);
         row2.append(item4);
        item_model_editable_markers_.appendRow(row2);

        ui->tableView->clearSelection();
        ui->tableView_2->clearSelection();
        QModelIndex last_index = item_model_markers_.index(item_model_markers_.rowCount() - 1, 0);
        ui->tableView->selectionModel()->select(QItemSelection(last_index, last_index), QItemSelectionModel::Select | QItemSelectionModel::Rows);
        ui->tableView_2->selectionModel()->select(QItemSelection(last_index, last_index), QItemSelectionModel::Select | QItemSelectionModel::Rows);

		return true;
	}
	return false;
}

void PositionCalibrate::on_toolButton_remove_selected_rows_clicked()
{
    QList<int> removeRows;
    foreach(QModelIndex index, ui->tableView->selectionModel()->selectedIndexes()) {
        if(!removeRows.contains(index.row())) {
            removeRows.append(index.row());
        }
    }

    qSort(removeRows);
    int countRow = removeRows.count();
    for( int i = countRow; i > 0; i--)
    {
        item_model_markers_.removeRow( removeRows.at(i-1), QModelIndex());
        item_model_editable_markers_.removeRow( removeRows.at(i-1), QModelIndex());
        ellipses_.erase(ellipses_.begin() + removeRows.at(i-1));
    }
    ui->image_window->update();
}

void PositionCalibrate::on_toolButton_remove_all_rows_clicked()
{
    item_model_markers_.removeRows(0, item_model_markers_.rowCount());
    item_model_editable_markers_.removeRows(0, item_model_editable_markers_.rowCount());
    ellipses_.clear();
    ui->image_window->update();
}

void PositionCalibrate::on_toolButton_calibrate_clicked()
{
    int point_pair_count = item_model_editable_markers_.rowCount();
    int ellipse_count = ellipses_.size();
    if (ellipse_count != point_pair_count)
    {
        QMessageBox::warning(this, QStringLiteral("内部错误"), QStringLiteral("请重新打开标定对话框标定"), QMessageBox::StandardButton::Ok);
        return;
    }
    if (point_pair_count < 9)
    {
        QMessageBox::information(this, QStringLiteral("数据不足"), QStringLiteral("请至少输入9对坐标"), QMessageBox::StandardButton::Ok);
        return;
    }

    vector<float> x1, y1, x2, y2;
    for (int i = 0; i < point_pair_count; ++i)
    {
        Ellipse ellipse = ellipses_[i];
        x1.push_back(ellipse.x);
        y1.push_back(ellipse.y);
        x2.push_back(item_model_editable_markers_.data(item_model_editable_markers_.index(i, 0)).toFloat());
        y2.push_back(item_model_editable_markers_.data(item_model_editable_markers_.index(i, 1)).toFloat());
    }

    for (int i = 0; i < point_pair_count; ++i)
    {
        float px = x1[i];
        float py = y1[i];
        for (int j = 0; j < point_pair_count; ++j)
        {
            if (j == i)
                continue;
            float qx = x1[j];
            float qy = y1[j];
            if (abs(px-qx) < 1 && abs(py - qy) < 1)
            {
				char message[512];
                sprintf(message, "%d             %d", i+1, j+1);
                QMessageBox::information(this, QStringLiteral("像素坐标重合"), message, QMessageBox::StandardButton::Ok);
                return;
            }
        }
    }

    for (int i = 0; i < point_pair_count; ++i)
    {
        float px = x2[i];
        float py = y2[i];
        for (int j = 0; j < point_pair_count; ++j)
        {
            if (j == i)
                continue;
            float qx = x2[j];
            float qy = y2[j];
            if (abs(px-qx) < 1 && abs(py - qy) < 1)
            {
                char message[512];
                sprintf(message, "%d           %d", i+1, j+1);
                QMessageBox::information(this, QStringLiteral("机械手坐标重合"), message, QMessageBox::StandardButton::Ok);
                return;
            }
        }
    }

	HTuple px(x1.data(), point_pair_count);
	HTuple py(y1.data(), point_pair_count);
	HTuple qx(x2.data(), point_pair_count);
	HTuple qy(y2.data(), point_pair_count);
    try
    {
        hommat2d_.VectorToProjHomMat2d(px, py, qx, qy, "normalized_dlt", HTuple(), HTuple(), HTuple(), HTuple(), HTuple(), HTuple());
    }
    catch (exception &)
    {
        calibrate_finish_ = false;
        QMessageBox::warning(this, QStringLiteral("内部错误"), QStringLiteral("请重新打开标定对话框标定"), QMessageBox::StandardButton::Ok);
        return;
    }

	Baojitai::instance()->set_image_to_robotic_matrix(hommat2d_);

	//hommat2d_ = Baojitai::instance()->image_to_robotic_matrix();

    for (int i = 0; i < x1.size(); ++i)
    {
        HTuple x, y, w;
        ProjectiveTransPoint2d(hommat2d_, px[i], py[i], 1, &x, &y, &w);
        double xx = x;
        double yy = y;
        double ww = w;
        cout << x1[i] << " " << y1[i] << " -> " << (double) xx / ww << " " << (double) yy / ww << " " << endl;
    }
    QMessageBox::warning(this, QStringLiteral("标定成功"), QStringLiteral("标定成功"), QMessageBox::StandardButton::Ok);
    calibrate_finish_ = true;
}

void PositionCalibrate::on_toolButton_save_clicked()
{
    if (! calibrate_finish_)
    {
        QMessageBox::warning(this, QStringLiteral("calibrate not finish"), QStringLiteral("again"), QMessageBox::StandardButton::Ok);
        return;
    }
	Baojitai::instance()->set_image_to_robotic_matrix(hommat2d_);
}

void PositionCalibrate::on_toolButton_capture_clicked()
{
    Camera* camera = Baojitai::instance()->camera_location();
    if (camera && camera->is_open() && !camera->is_grabbing())
        camera->trigger();
}

void PositionCalibrate::on_camera_buffer_changed(Camera* camera)
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
            ui->image_window->update();
        }
    }
}

void PositionCalibrate::on_pushButton_save_image_clicked()
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

void PositionCalibrate::on_spinBox_x_offset_valueChanged(int arg1)
{
    Baojitai::instance()->set_robotic_x_offset(arg1);
}

void PositionCalibrate::on_spinBox_y_offset_valueChanged(int arg1)
{
    Baojitai::instance()->set_robotic_y_offset(arg1);
}
