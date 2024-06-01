#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QDateEdit>
#include "PillBox.h"


class RemovePillDialog : public QDialog
{
    Q_OBJECT

public:
    RemovePillDialog(PillBox& pillBox, QWidget* parent = nullptr);

private slots:
    void removePill();
    void load_pills_to_remove();


private:
    QVBoxLayout* remove_pills_layout;

    PillBox& pillBox;
   
};