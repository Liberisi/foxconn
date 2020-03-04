#ifndef HALCONWIDGET_H
#define HALCONWIDGET_H

#include <QWidget>
#include <halconcpp/HalconCpp.h>
#include <QPoint>

using namespace HalconCpp;

class HalconWidget;
class HalconWidgetDelegate
{
public:
    virtual void on_paint(HalconWidget* halcon_widget, HWindow& halcon_widow) = NULL;
};

class HalconWidget : public QWidget
{
    Q_OBJECT

public:
    static void parent_widget_position_to_image_row_col(const QWidget* parent, const QPoint& pos, const QWidget* widget, int image_width, int image_height, int* row, int* col, bool* is_child);

public:
    explicit HalconWidget(QWidget *parent = 0);
    virtual ~HalconWidget();

    void set_halcon_widget_delegate(HalconWidgetDelegate* delegate);


    virtual void resizeEvent(QResizeEvent *event);
    virtual void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    HalconCpp::HWindow halcon_window_;
    HalconWidgetDelegate* halcon_widget_delegate_;
};

#endif // HALCONWIDGET_H
