#include "AddPillDialog.h"
#include <QMessageBox>

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

    QPushButton* add_button = new QPushButton("Add Pill", this);
    connect(add_button, &QPushButton::clicked, this, &AddPillDialog::addPill);

    layout->addWidget(name_label);
    layout->addWidget(pill_name_edit);
    layout->addWidget(quantity_label);
    layout->addWidget(pill_quantity_spin);
    layout->addWidget(dose_label);
    layout->addWidget(pill_dose_edit);
    layout->addWidget(add_button);

    setLayout(layout);
    setWindowTitle("Add Pill");
}

void AddPillDialog::addPill()
{
    QString pill_name = pill_name_edit->text();
    int quantity = pill_quantity_spin->value();
    QString dose = pill_dose_edit->text();

    // Perform the logic to add the pill details
    // For now, just show a message box with the entered details
    QMessageBox msgBox;
    msgBox.setText("Pill: " + pill_name + "\nQuantity: " + QString::number(quantity) + "\nDose: " + dose + " mg");
    msgBox.setWindowTitle("Pill added");
    msgBox.exec();

    accept(); // Close the dialog
}
