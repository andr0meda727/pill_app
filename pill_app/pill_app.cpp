#include "pill_app.h"
#include <qmessagebox.h>

pill_app::pill_app(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.add_pill_push_button, &QPushButton::clicked, this, &pill_app::add_pill_button_clicked);
    connect(ui.remove_pill_push_button, &QPushButton::clicked, this, &pill_app::remove_pill_button_clicked);
    connect(ui.calendar_push_button, &QPushButton::clicked, this, &pill_app::calendar_button_clicked);
    connect(ui.remaining_quantity_push_button, &QPushButton::clicked, this, &pill_app::remaining_quantity_button_clicked);
}


pill_app::~pill_app()
{}


void pill_app::add_pill_button_clicked()
{
    AddPillDialog dialog(this);
    dialog.exec();
}


void pill_app::remove_pill_button_clicked()
{

}


void pill_app::calendar_button_clicked()
{

}


void pill_app::remaining_quantity_button_clicked()
{

}