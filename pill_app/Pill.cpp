#include "Pill.h"
#include <QFile>
#include <QTextStream>

Pill::Pill(const QDate& start_date, const QDate& end_date, const QString& name, int quantity, double dose)
    : start_date(start_date), end_date(end_date), name(name), quantity(quantity), dose(dose) {}

bool Pill::write_to_file(const QString& filePath) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        return false;
    }

    QTextStream out(&file);
    out << start_date.toString("yyyy-MM-dd") << "," << end_date.toString("yyyy-MM-dd") << "," << name << "," << quantity << "," << dose << "\n";
    file.close();
    return true;
}