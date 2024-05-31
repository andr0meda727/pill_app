#include "AddPillDialog.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "Pill.h"

AddPillDialog::AddPillDialog(QWidget* parent)
    : QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* name_label = new QLabel("Pill name:", this);
    pill_name_edit = new QLineEdit(this);

    QLabel* quantity_label = new QLabel("Quantity:", this);
    pill_quantity_spin = new QSpinBox(this);
    pill_quantity_spin->setMinimum(1);

    QLabel* dose_label = new QLabel("Dose (mg):", this);
    pill_dose_edit = new QLineEdit(this);

    QLabel* start_date_label = new QLabel("Start date:", this);
    pill_start_date_edit = new QDateEdit(this);
    pill_start_date_edit->setDisplayFormat("dd MMM yyyy");
    pill_start_date_edit->setDate(QDate::currentDate());
    pill_start_date_edit->setCalendarPopup(true);

    QLabel* end_date_label = new QLabel("End date:", this);
    pill_end_date_edit = new QDateEdit(this);
    pill_end_date_edit->setDisplayFormat("dd MMM yyyy");
    pill_end_date_edit->setDate(QDate::currentDate());
    pill_end_date_edit->setCalendarPopup(true);

    QPushButton* add_button = new QPushButton("Add Pill", this);
    connect(add_button, &QPushButton::clicked, this, &AddPillDialog::addPill);

    layout->addWidget(name_label);
    layout->addWidget(pill_name_edit);
    layout->addWidget(quantity_label);
    layout->addWidget(pill_quantity_spin);
    layout->addWidget(dose_label);
    layout->addWidget(pill_dose_edit);
    layout->addWidget(start_date_label);
    layout->addWidget(pill_start_date_edit);
    layout->addWidget(end_date_label);
    layout->addWidget(pill_end_date_edit);
    layout->addWidget(add_button);

    setLayout(layout);
    setWindowTitle("Add Pill");
}

void AddPillDialog::addPill()
{
    QString pill_name = pill_name_edit->text();
    int quantity = pill_quantity_spin->value();
    QString dose = pill_dose_edit->text();
    QDate start_date = pill_start_date_edit->date();
    QDate end_date = pill_end_date_edit->date();

    bool dose_is_valid;
    double dose_value = dose.toDouble(&dose_is_valid);

    if (pill_name.isEmpty() || dose.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Enter necessary data");
        return;
    }

    if (!dose_is_valid || dose_value <= 0)
    {
        QMessageBox::warning(this, "Input Error", "Enter a valid dose");
        return;
    }

    if (pill_name.length() > 100)
    {
        QMessageBox::warning(this, "Input Error", "Pill name should not exceed 100 characters.");
        return;
    }

    if (start_date > end_date)
    {
        QMessageBox::warning(this, "Input Error", "Start date must be before end date.");
        return;
    }

    Pill pill(start_date, end_date, pill_name, quantity, dose_value);
    if (!pill.writeToFile("pills.txt"))
    {
        QMessageBox::critical(this, "Error", "Could not open file for writing.");
        return;
    }

    QMessageBox msgBox;
    msgBox.setText("Pill: " + pill_name + "\nQuantity: " + QString::number(quantity) + "\nDose: " + dose + " mg\nStart Date: " + start_date.toString("dd MMM yyyy") + "\nEnd Date: " + end_date.toString("dd MMM yyyy"));
    msgBox.setWindowTitle("Pill added");
    msgBox.exec();

    accept(); // Close the dialog
}
