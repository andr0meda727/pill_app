#include <QString>

class Pill 
{
public:
    Pill(const QString& name, int quantity, double dose);

    bool writeToFile(const QString& filePath) const;
    QString get_name() const { return name; }
    int get_quantity() const { return quantity; }
    int get_dose() const { return dose; }
private:
    QString name;
    int quantity;
    double dose;
};
