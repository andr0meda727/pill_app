#pragma once

#include <QString>
#include <QDate>


class Pill
{
public:
    Pill(const QDate& start_date, const QDate& end_date, const QString& name, int quantity, double dose);

    bool writeToFile(const QString& filePath) const;
    QString get_name() const { return name; }
    int get_quantity() const { return quantity; }
    double get_dose() const { return dose; }
    QDate get_start_date() const { return start_date; }
    QDate get_end_date() const { return end_date; }

private:
    QString name;
    int quantity;
    double dose;
    QDate start_date;
    QDate end_date;
};