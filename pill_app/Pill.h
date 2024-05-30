#include <QString>

class Pill 
{
public:
    Pill(const QString& name, int quantity, double dose);

    bool writeToFile(const QString& filePath) const;

private:
    QString name;
    int quantity;
    double dose;
};
