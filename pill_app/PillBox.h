#pragma once

#include "Pill.h"
#include <QDate>
#include <QString>
#include <QList>

class PillBox
{
public:
    void filling_pills(const Pill& pill);
    bool read_from_file(const QString& file_path);
    QList<Pill> get_list_of_pills(const QDate& date) const;
    QList<Pill> get_all_pills() const;
    void remove_pill(const Pill& pill);
    void update_pill(const Pill& old_pill, const Pill& new_pill);
    bool save_to_file(const QString& filePath) const;
    void clear_box();


private:
    QList<Pill> pills;
    QString file_path;
};


