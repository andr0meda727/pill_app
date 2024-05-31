#include "pill_app.h"
#include "PillBox.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QPushButton>
#include <QDebug>
#include <QVBoxLayout>

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

    pills_layout = new QVBoxLayout();
    ui.list_of_pills_display->setLayout(pills_layout);

    taken_pills_layout = new QVBoxLayout();
    ui.taken_pills_display->setLayout(taken_pills_layout);

    load_state();

    // Load pills from file
    if (!pillBox.read_from_file("pills.txt")) {
        QMessageBox::warning(this, "Error", "Could not load pills from file");
    }


    user_date_changed();
}

pill_app::~pill_app()
{
    save_state();
}

void pill_app::add_pill_button_clicked()
{
    AddPillDialog dialog(this);
    dialog.exec();
    user_date_changed();  // refresh
}

void pill_app::user_date_changed()
{
    QDate date = ui.date_edit->date();

    // clearing previous buttons
    QLayoutItem* item;
    while ((item = pills_layout->takeAt(0)) != nullptr) {
        delete item->widget(); 
        delete item; 
    }

    while ((item = taken_pills_layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }


    QList<Pill> pills = pillBox.get_list_of_pills(date);
    QList<Pill> taken_pills = taken_pills_map.value(date);

    // Add buttons for pills that are not taken
    foreach(const Pill & pill, pills) {
        if (!taken_pills.contains(pill)) {
            QPushButton* pill_button = new QPushButton(QString("Pill: %1, Quantity: %2, Dose: %3")
                .arg(pill.get_name())
                .arg(pill.get_quantity())
                .arg(pill.get_dose()));

            pill_button->setProperty("start_date", pill.get_start_date());
            pill_button->setProperty("end_date", pill.get_end_date());
            pill_button->setProperty("name", pill.get_name());
            pill_button->setProperty("quantity", pill.get_quantity());
            pill_button->setProperty("dose", pill.get_dose());

            connect(pill_button, &QPushButton::clicked, this, &pill_app::pill_button_clicked);
            pills_layout->addWidget(pill_button);
        }
    }

    // Add buttons for taken pills
    foreach(const Pill & pill, taken_pills) {
        QPushButton* taken_pill_button = new QPushButton(QString("Taken Pill: %1, Dose: %3")
            .arg(pill.get_name())
            .arg(pill.get_quantity())
            .arg(pill.get_dose()));

        taken_pills_layout->addWidget(taken_pill_button);
    }

    ui.list_of_pills_display->adjustSize();
    ui.taken_pills_display->adjustSize();
}


void pill_app::pill_button_clicked()
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

    // Create the pill object
    Pill pill(start_date, end_date, name, quantity, dose);

    QDate date = ui.date_edit->date();

    int new_quantity = quantity - 1;
    if (new_quantity > 0) {
        Pill updated_pill(start_date, end_date, name, new_quantity, dose);
        pillBox.update_pill(pill, updated_pill);
        pillBox.save_to_file("pills.txt");
    }

    else {
        pillBox.remove_pill(pill);
        pillBox.save_to_file("pills.txt");
    }

    // Add to taken pills list for the current date
    taken_pills_map[date].append(pill);

    // Remove the button from the layout and delete it
    pills_layout->removeWidget(button);
    delete button;

    user_date_changed();
}

void pill_app::remove_pill_button_clicked()
{}


void pill_app::remaining_quantity_button_clicked()
{}


void pill_app::save_state()
{
    // save current state of taken pills
    QFile file("taken_pills.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (auto it = taken_pills_map.begin(); it != taken_pills_map.end(); ++it) {
            QDate date = it.key();
            foreach(const Pill & pill, it.value()) {
                out << date.toString("yyyy-MM-dd") << ","
                    << pill.get_start_date().toString("yyyy-MM-dd") << ","
                    << pill.get_end_date().toString("yyyy-MM-dd") << ","
                    << pill.get_name() << ","
                    << pill.get_quantity() << ","
                    << pill.get_dose() << "\n";
            }
        }
        file.close();
    }
}


void pill_app::load_state()
{
    // Load taken pills from file
    QFile file("taken_pills.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList pill_data = line.split(',');

            if (pill_data.size() == 6) {
                QDate date = QDate::fromString(pill_data[0].trimmed(), "yyyy-MM-dd");
                QDate start_date = QDate::fromString(pill_data[1].trimmed(), "yyyy-MM-dd");
                QDate end_date = QDate::fromString(pill_data[2].trimmed(), "yyyy-MM-dd");
                QString name = pill_data[3].trimmed();
                int quantity = pill_data[4].trimmed().toInt();
                double dose = pill_data[5].trimmed().toDouble();

                if (start_date.isValid() && end_date.isValid() && date.isValid()) {
                    Pill pill(start_date, end_date, name, quantity, dose);
                    taken_pills_map[date].append(pill);
                }
            }
        }
        file.close();
    }
}