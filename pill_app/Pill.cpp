#include "Pill.h"
#include <QFile>
#include <QTextStream>

Pill::Pill(const QString& name, int quantity, double dose)
    : name(name), quantity(quantity), dose(dose) {}

bool Pill::writeToFile(const QString& filePath) const 
{
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) 
    {
        return false;
    }

    QTextStream out(&file);
    out << "Pill: " << name << ", Quantity: " << quantity << ", Dose: " << dose << " mg\n";
    file.close();
    return true;
}

