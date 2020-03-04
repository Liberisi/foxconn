#ifndef CONFIG_SAVE_H
#define CONFIG_SAVE_H

#include <QDialog>

namespace Ui {
class Configsave;
}

class SaveConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveConfigDialog(QWidget *parent = 0);
    ~SaveConfigDialog();

private:
    Ui::Configsave *ui;
};

#endif // CONFIG_SAVE_H
