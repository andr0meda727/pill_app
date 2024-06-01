#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QDateEdit>

class AddPillDialog : public QDialog
{
    Q_OBJECT

public:
    AddPillDialog(QWidget* parent = nullptr);

private slots:
    void addPill();

private:
    QLineEdit* pill_name_edit;
    QSpinBox* pill_quantity_spin;
    QLineEdit* pill_dose_edit;
    QDateEdit* pill_start_date_edit;
    QDateEdit* pill_end_date_edit;
};