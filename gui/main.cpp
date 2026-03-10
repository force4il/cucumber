#include <QApplication>
#include "loginwindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow w;    

    w.show();

    return a.exec();
}
