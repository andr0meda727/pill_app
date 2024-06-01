#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include "PillBox.h"

class RemainingPillsDialog : public QDialog
{
    Q_OBJECT

public:
    RemainingPillsDialog(PillBox& pillBox, QWidget* parent = nullptr);

private:
    void load_remaining_pills();

    QVBoxLayout* remaining_pills_layout;
    PillBox& pillBox;
};
