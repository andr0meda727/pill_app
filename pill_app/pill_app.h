#pragma once

#include <QMainWindow>
#include "PillBox.h"
#include "ui_pill_app.h"
#include "AddPillDialog.h"
#include <QPushButton>
#include <QMap>
#include <QVBoxLayout>
#include <QDate>

class pill_app : public QMainWindow
{
    Q_OBJECT

public:
    pill_app(QWidget* parent = nullptr);
    ~pill_app();

private slots:
    void add_pill_button_clicked();
    void remove_pill_button_clicked();
    void show_remaining_pills();
    void user_date_changed();
    void pill_button_clicked();
    void taken_pill_button_clicked();

private:
    Ui::pill_appClass ui;
    PillBox pillBox;
    QVBoxLayout* pills_layout; 
    QVBoxLayout* taken_pills_layout;
    QMap<QDate, QList<Pill>> taken_pills_map;

    void save_state();
    void load_state();
};