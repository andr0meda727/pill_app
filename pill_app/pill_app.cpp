#include "pill_app.h"
#include "Pill.h"
#include <qmessagebox.h>
#include <QFile>


pill_app::pill_app(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.date_edit->setCalendarPopup(true);
    ui.date_edit->setDate(QDate::currentDate());
    connect(ui.add_pill_push_button, &QPushButton::clicked, this, &pill_app::add_pill_button_clicked);
    connect(ui.remove_pill_push_button, &QPushButton::clicked, this, &pill_app::remove_pill_button_clicked);
    connect(ui.remaining_quantity_push_button, &QPushButton::clicked, this, &pill_app::remaining_quantity_button_clicked);
    connect(ui.date_edit, &QDateEdit::userDateChanged, this, &pill_app::user_date_changed);
}


pill_app::~pill_app()
{}
QList<Pill> get_list_of_pills(QString received_date) {
   
    /*
    format of data stored in pills_list
    yyyy-MM-dd number_of_pills pill_name quantity dose
    for example
    2024-05-31 1 ala 1 12
    2024-06-01 3 ala 1 12 ma 2 22 kota 3 33
    
    
    */   
    QList<Pill> pills_list;
    QFile file("pills_list.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file for reading:" << file.errorString();
        return pills_list;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(' ');

        // Check if the date matches
        if (parts[0] == received_date) {
            int index = 2;
            while (index < parts.size()) {
                Pill pill(parts[index], parts[index + 1].toInt(), parts[index + 2].toInt());
                pills_list.append(pill);
                index += 3;
            }
            break;
        }
    }
    file.close();
    return pills_list;
}
void pill_app::user_date_changed() {
    QDate date = ui.date_edit->date();
    QString to_return = "List for " + date.toString("yyyy-MM-dd"); //string which will be displayed in the list_of_pills_display after changing date in dateEdit
    to_return += "\n";
    QList<Pill> pills = get_list_of_pills(date.toString("yyyy-MM-dd"));
    foreach(const Pill & pill, pills) {
        to_return += QString("Pill Name: %1, Quantity: %2, Dose: %3\n")
            .arg(pill.get_name())
            .arg(pill.get_quantity())
            .arg(pill.get_dose());
    }
    ui.list_of_pills_display->setText(to_return);
}

void pill_app::add_pill_button_clicked()
{
    AddPillDialog dialog(this);
    dialog.exec();
}


void pill_app::remove_pill_button_clicked()
{

}


void pill_app::remaining_quantity_button_clicked()
{

}