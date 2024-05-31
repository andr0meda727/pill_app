#include "pill_app.h"
#include "PillBox.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>

pill_app::pill_app(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.date_edit->setCalendarPopup(true);
    ui.date_edit->setDate(QDate::currentDate());

    connect(ui.add_pill_push_button, &QPushButton::clicked, this, &pill_app::add_pill_button_clicked);
    connect(ui.remove_pill_push_button, &QPushButton::clicked, this, &pill_app::remove_pill_button_clicked);
    connect(ui.remaining_quantity_push_button, &QPushButton::clicked, this, &pill_app::remaining_quantity_button_clicked);
    connect(ui.date_edit, &QDateEdit::userDateChanged, this, &pill_app::user_date_changed);

    // Load pills from file
    if (!pillBox.read_from_file("pills.txt")) {
        QMessageBox::warning(this, "Error", "Could not load pills from file");
    }

    // Update the display initially
    user_date_changed();
}

pill_app::~pill_app()
{}

void pill_app::add_pill_button_clicked()
{
    AddPillDialog dialog(this);
    dialog.exec();
    user_date_changed();  // Refresh the display after adding a new pill
}

void pill_app::user_date_changed()
{
    QDate date = ui.date_edit->date();
    QString to_return = "List for " + date.toString("yyyy-MM-dd") + "\n";

    QList<Pill> pills = pillBox.get_list_of_pills(date);
    foreach(const Pill & pill, pills) {
        to_return += QString("Pill Name: %1, Quantity: %2, Dose: %3\n")
            .arg(pill.get_name())
            .arg(pill.get_quantity())
            .arg(pill.get_dose());
    }

    ui.list_of_pills_display->setText(to_return);
}


void pill_app::remove_pill_button_clicked()
{

}


void pill_app::remaining_quantity_button_clicked()
{

}