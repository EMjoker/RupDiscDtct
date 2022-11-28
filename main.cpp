#include "rupdiscdtct.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RupDiscDtct w;
    w.show();
    return a.exec();
}
