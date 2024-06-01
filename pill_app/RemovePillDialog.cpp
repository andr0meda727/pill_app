#include "RemovePillDialog.h"
#include <QMessageBox>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include "Pill.h"
#include "PillBox.h"


RemovePillDialog::RemovePillDialog(PillBox& pillBox,QWidget* parent)
    : QDialog(parent), pillBox(pillBox)

{
    setWindowTitle("Remove Pills");
    remove_pills_layout = new QVBoxLayout(this);
    load_pills_to_remove();
    setLayout(remove_pills_layout);

   
}

void RemovePillDialog::load_pills_to_remove() {
    // Clear the layout
    QLayoutItem* item;
    while ((item = remove_pills_layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Get all pills from the PillBox
    QList<Pill> all_pills = pillBox.get_all_pills();

  
    // Add pills to the layout
    foreach(const Pill & pill, all_pills) {
        QPushButton* pill_button = new QPushButton(QString("Pill: %1, Quantity: %2, Dose: %3, Start : %4, End : %5")
            .arg(pill.get_name())
            .arg(pill.get_quantity())
            .arg(pill.get_dose())
            .arg(pill.get_start_date().toString("yyyy-MM-dd"))
            .arg(pill.get_end_date().toString("yyyy-MM-dd")));

        pill_button->setProperty("start_date", pill.get_start_date());
        pill_button->setProperty("end_date", pill.get_end_date());
        pill_button->setProperty("name", pill.get_name());
        pill_button->setProperty("quantity", pill.get_quantity());
        pill_button->setProperty("dose", pill.get_dose());

        connect(pill_button, &QPushButton::clicked, this, &RemovePillDialog::removePill);
        remove_pills_layout->addWidget(pill_button);

    }

};


void RemovePillDialog::removePill()
{
    // Get the button that was clicked
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    // Get pill information from button properties
    QDate start_date = button->property("start_date").toDate();
    QDate end_date = button->property("end_date").toDate();
    QString name = button->property("name").toString();
    int quantity = button->property("quantity").toInt();
    double dose = button->property("dose").toDouble();
    Pill pill(start_date, end_date, name, quantity, dose);

   //remove_pills_layout
    pillBox.remove_pill(pill);
    pillBox.save_to_file("pills.txt");
    remove_pills_layout->removeWidget(button);
    button->deleteLater();
}
