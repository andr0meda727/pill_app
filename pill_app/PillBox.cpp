#include "PillBox.h"
#include "Pill.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDate>

void PillBox::filling_pills(const Pill& pill)
{
    pills.append(pill);
}

bool PillBox::read_from_file(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList pillData = line.split(',');

        if (pillData.size() == 5)
        {
            QDate start_date = QDate::fromString(pillData[0].trimmed(), "yyyy-MM-dd");
            QDate end_date = QDate::fromString(pillData[1].trimmed(), "yyyy-MM-dd");
            QString name = pillData[2].trimmed();
            int quantity = pillData[3].trimmed().toInt();
            double dose = pillData[4].trimmed().toDouble();

            if (start_date.isValid() && end_date.isValid()) {
                Pill pill(start_date, end_date, name, quantity, dose);
                filling_pills(pill);
            }
        }
    }

    file.close();
    return true;
}


QList<Pill> PillBox::get_list_of_pills(const QDate& date) const
{    
    QList<Pill> pills_list;
    foreach(const Pill & pill, pills) {
        if (date >= pill.get_start_date() && date <= pill.get_end_date()) {
            pills_list.append(pill);
        }
    }
    return pills_list;
}

void PillBox::clear_box() {

    foreach(const Pill & pill, pills) {
        pills.removeOne(pill);
    }

};

void PillBox::update_pill(const Pill& old_pill, const Pill& new_pill)
{
    int index = pills.indexOf(old_pill);
    if (index != -1) {
        pills[index] = new_pill;
    }
}


void PillBox::remove_pill(const Pill& pill)
{
    pills.removeOne(pill);
}


bool PillBox::save_to_file(const QString& filePath) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    foreach(const Pill & pill, pills) {
        out << pill.get_start_date().toString("yyyy-MM-dd") << ","
            << pill.get_end_date().toString("yyyy-MM-dd") << ","
            << pill.get_name() << ","
            << pill.get_quantity() << ","
            << pill.get_dose() << "\n";
    }

    file.close();
    return true;
}