#include "halcon_widget.h"
#include <QResizeEvent>
#include <QPaintEvent>

void HalconWidget::parent_widget_position_to_image_row_col(const QWidget* parent, const QPoint& pos, const QWidget* widget, int image_width, int image_height, int* row, int* col, bool* is_child)
{
    if (!parent || !widget)
        return;

    int widget_x = pos.x();
    int widget_y = pos.y();
    if (is_child)
        *is_child = true;

    if (widget == parent)
    {
        if (is_child)
            *is_child = false;
    }
    else
    {
        QWidget* p_widget = widget->parentWidget();
        while (p_widget && p_widget != parent)
        {
            QPoint offset = p_widget->pos();
            widget_y += offset.y();
            widget_x += offset.x();
            p_widget = p_widget->parentWidget();
        }
        if (!p_widget && is_child)
        {
            is_child = false;
        }
    }
    int widget_width = widget->size().width();
    int widget_height = widget->size().height();
    if (col && widget_width != 0)
        *col = image_width * (1.0 * widget_x) / widget_width;
    if (row && widget_height != 0)
        *row = image_height * (1.0 * widget_y) / widget_height;
}

HalconWidget::HalconWidget(QWidget *parent) : QWidget(parent)
{
    halcon_widget_delegate_ = NULL;
}

HalconWidget::~HalconWidget()
{
    if (halcon_window_.IsHandleValid())
        halcon_window_.CloseWindow();
}

void HalconWidget::set_halcon_widget_delegate(HalconWidgetDelegate* delegate)
{
    halcon_widget_delegate_ = delegate;
}

void HalconWidget::resizeEvent(QResizeEvent *event)
{
    if (halcon_window_.IsHandleValid())
        halcon_window_.CloseWindow();
    if (!halcon_window_.IsHandleValid())
    {
        int width = event->size().width();
        int height = event->size().height();
		if (width > 0 && height > 0)
            halcon_window_.OpenWindow(0, 0, width, height, (long)this->winId(), "", "");
    }
}

void HalconWidget::paintEvent(QPaintEvent *)
{
    if (halcon_widget_delegate_)
        halcon_widget_delegate_->on_paint(this, halcon_window_);
}
