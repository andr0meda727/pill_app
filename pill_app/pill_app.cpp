#include "pill_app.h"
#include "PillBox.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QPushButton>
#include <QDebug>
#include <QVBoxLayout>
#include "RemainingPillsDialog.h"
#include "RemovePillDialog.h"

pill_app::pill_app(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.date_edit->setCalendarPopup(true);
    ui.date_edit->setDate(QDate::currentDate());

    connect(ui.add_pill_push_button, &QPushButton::clicked, this, &pill_app::add_pill_button_clicked);
    connect(ui.remove_pill_push_button, &QPushButton::clicked, this, &pill_app::remove_pill_button_clicked);
    connect(ui.show_remaining_pills_push_button, &QPushButton::clicked, this, &pill_app::show_remaining_pills);
    connect(ui.date_edit, &QDateEdit::userDateChanged, this, &pill_app::user_date_changed);

    pills_layout = new QVBoxLayout();
    ui.list_of_pills_display->setLayout(pills_layout);

    taken_pills_layout = new QVBoxLayout();
    ui.taken_pills_display->setLayout(taken_pills_layout);

    load_state();
    QPixmap pixmap("mario.png");

    int width = 300;  // desired width
    int height = 400; // desired height
    QPixmap resizedPixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio);
    ui.label->setPixmap(resizedPixmap);
    ui.label->setFixedSize(resizedPixmap.size());

    QPixmap pixmap2("mario2.png");

    QPixmap resizedPixmap2 = pixmap2.scaled(width, height, Qt::KeepAspectRatio);
    ui.label_2->setPixmap(resizedPixmap2);
    ui.label_2->setFixedSize(resizedPixmap2.size());

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
    pillBox.clear_box();
    pillBox.read_from_file("pills.txt");
    QList<Pill> pills = pillBox.get_list_of_pills(date);

    QList<Pill> taken_pills = taken_pills_map.value(date);

    QString buttonStyleSheet = R"(
        QPushButton {
            appearance: none;
            background-color: #FAFBFC;
            border: 1px solid rgba(27, 31, 35, 0.15);
            border-radius: 6px;
            box-shadow: rgba(27, 31, 35, 0.04) 0 1px 0, rgba(255, 255, 255, 0.25) 0 1px 0 inset;
            box-sizing: border-box;
            color: #24292E;
            cursor: pointer;
            display: inline-block;
            font-family: -apple-system, system-ui, "Segoe UI", Helvetica, Arial, sans-serif, "Apple Color Emoji", "Segoe UI Emoji";
            font-size: 12px;
            font-weight: 500;
            line-height: 20px;
            list-style: none;
            padding: 6px 16px;
            position: relative;
            transition: background-color 0.2s cubic-bezier(0.3, 0, 0.5, 1);
            user-select: none;
        }
    )";

    // Add buttons for pills that are not taken
    foreach(const Pill & pill, pills) {
            QPushButton* pill_button = new QPushButton(QString("Pill: %1, Quantity: %2, Dose: %3")
                .arg(pill.get_name())
                .arg(pill.get_quantity())
                .arg(pill.get_dose()));

            pill_button->setProperty("start_date", pill.get_start_date());
            pill_button->setProperty("end_date", pill.get_end_date());
            pill_button->setProperty("name", pill.get_name());
            pill_button->setProperty("quantity", pill.get_quantity());
            pill_button->setProperty("dose", pill.get_dose());
            pill_button->setStyleSheet(buttonStyleSheet);

            connect(pill_button, &QPushButton::clicked, this, &pill_app::pill_button_clicked);
            pills_layout->addWidget(pill_button);
        
    }

    // Add buttons for taken pills
    foreach(const Pill & pill, taken_pills) {
        QPushButton* taken_pill_button = new QPushButton(QString("Taken Pill: %1, Quantity: %2, Dose: %3")
            .arg(pill.get_name())
            .arg(pill.get_quantity())
            .arg(pill.get_dose()));

        taken_pill_button->setProperty("start_date", pill.get_start_date());
        taken_pill_button->setProperty("end_date", pill.get_end_date());
        taken_pill_button->setProperty("name", pill.get_name());
        taken_pill_button->setProperty("quantity", pill.get_quantity());
        taken_pill_button->setProperty("dose", pill.get_dose());
        connect(taken_pill_button, &QPushButton::clicked, this, &pill_app::taken_pill_button_clicked);
        taken_pill_button->setStyleSheet(buttonStyleSheet);

        taken_pills_layout->addWidget(taken_pill_button);
    }

   /* ui.list_of_pills_display->adjustSize();
    ui.taken_pills_display->adjustSize();*/
}


void pill_app::taken_pill_button_clicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;


    // Get pill information from button properties
    QDate start_date = button->property("start_date").toDate();
    QDate end_date = button->property("end_date").toDate();
    QString name = button->property("name").toString();
    int quantity = button->property("quantity").toInt();
    double dose = button->property("dose").toDouble();


    Pill pill(start_date, end_date, name, 1, dose);
    QDate date = ui.date_edit->date();

    if (quantity == 1) {
    //remove from taken list
        taken_pills_map[date].removeOne(pill);
    }else{
    //decrement quantity
        for (Pill& pill : taken_pills_map[date]) {

            if (pill.get_name() == name) {
                pill.increment_quantity(-1);
                break;
            }

        }
    }
    if (!pill.write_to_file("pills.txt"))
    {
        QMessageBox::critical(this, "Error", "Could not open file for writing.");
        return;
    }
   
    user_date_changed();  // refresh

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
    // check if it exists already
    QDate date = ui.date_edit->date();
    bool wasInside = false;
    Pill pill(start_date, end_date, name, quantity, dose);
    for (Pill& pill : taken_pills_map[date]) {

        if (pill.get_name() == name) {
            wasInside = true;
            pill.increment_quantity(1);
            break;
        }
   
    }

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
    if (!wasInside) {
        pill = Pill(start_date, end_date, name, 1, dose);
        taken_pills_map[date].append(pill);
    }

    // Remove the button from the layout and delete it
    pills_layout->removeWidget(button);
    delete button;

    user_date_changed();
}

void pill_app::remove_pill_button_clicked()
{
    RemovePillDialog dialog(pillBox, this);
    dialog.exec();
    user_date_changed();  // refresh

}


void pill_app::show_remaining_pills()
{
    RemainingPillsDialog dialog(pillBox, this);
    dialog.exec();
}


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