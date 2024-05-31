#pragma once
#include "Pill.h"
#include <QList>

class PillBox
{
public:
    void filling_pills(const Pill& pill);
    bool read_from_file(const QString& filePath);
    QList<Pill> get_list_of_pills(const QDate& date) const;

private:
    QList<Pill> pills;
};


