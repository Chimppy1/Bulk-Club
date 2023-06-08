#include "loginwindow.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    LoginWindow ourLogin;

    ourLogin.show();

    return a.exec();
}
