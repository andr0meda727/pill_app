#include "pill_app.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pill_app w;
    w.show();
    return a.exec();
}