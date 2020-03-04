#pragma once

#include <QWidget>
#include "ui_ModifyUSER.h"
#include"UserIni.h"

class ModifyUSER : public QWidget
{
    Q_OBJECT

public:
    ModifyUSER(QWidget *parent = Q_NULLPTR);
    ~ModifyUSER();

private:
    Ui::ModifyUSER ui;
    UserIni userini;

private slots:
    void tol_exit_clicked();
    void Cancel();
    void Modify();
};
