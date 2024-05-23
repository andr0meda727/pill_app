#include "pill_app.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pill_app w;
    w.show();
    return a.exec();
}


//TODO
//zapisywanie do pliku aktualnie branych lekow na podstawie wczesniej dodanych
//zczytanie danych z pliku i pokazywanie na biezaco w kalendarzu dni w ktorych wzieto dane leki
//mozliwosc usuniecia danego leku
//quantity - pokazywanie aktualnego stanu dostepnosci, jak wprowadziles 30, a pozniej zaznaczyles ze wziales to bedzie 29 itp
