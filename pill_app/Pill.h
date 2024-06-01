#pragma once

#include <QString>
#include <QDate>


class Pill
{
public:
    Pill(const QDate& start_date, const QDate& end_date, const QString& name, int quantity, double dose);

    bool write_to_file(const QString& filePath) const;
    QString get_name() const { return name; }
    int get_quantity() const { return quantity; }
    double get_dose() const { return dose; }
    QDate get_start_date() const { return start_date; }
    QDate get_end_date() const { return end_date; }
    void increment_quantity(int received) { quantity+=received;};

    bool operator==(const Pill& other) const {
        return start_date == other.start_date && end_date == other.end_date &&
            name == other.name && quantity == other.quantity && dose == other.dose;
    }

private:
    QString name;
    int quantity;
    double dose;
    QDate start_date;
    QDate end_date;
};