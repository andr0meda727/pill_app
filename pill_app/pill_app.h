#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_pill_app.h"

class pill_app : public QMainWindow
{
    Q_OBJECT

public:
    pill_app(QWidget *parent = nullptr);
    ~pill_app();

private:
    Ui::pill_appClass ui;
};
