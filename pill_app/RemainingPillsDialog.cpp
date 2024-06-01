#include "RemainingPillsDialog.h"
#include "PillBox.h"
#include <algorithm>

RemainingPillsDialog::RemainingPillsDialog(PillBox& pillBox, QWidget* parent)
    : QDialog(parent), pillBox(pillBox)
{
    setWindowTitle("Remaining Pills");

    remaining_pills_layout = new QVBoxLayout(this);
    load_remaining_pills();

    setLayout(remaining_pills_layout);
}

void RemainingPillsDialog::load_remaining_pills()
{
    // Clear the layout
    QLayoutItem* item;
    while ((item = remaining_pills_layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Get all pills from the PillBox
    QList<Pill> all_pills = pillBox.get_all_pills();

    // Sort pills by quantity from lowest to highest
    std::sort(all_pills.begin(), all_pills.end(), [](const Pill& a, const Pill& b) {
        return a.get_quantity() < b.get_quantity();
        });

    // Add pills to the layout
    foreach(const Pill & pill, all_pills) {
        QLabel* pillLabel = new QLabel(QString("Pill: %1, Quantity: %2, Dose: %3")
            .arg(pill.get_name())
            .arg(pill.get_quantity())
            .arg(pill.get_dose()));
        remaining_pills_layout->addWidget(pillLabel);
    }
}
