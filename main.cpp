#include <QtGui/QApplication>
#include "mainwindow.h"
#include "iostream"
#include "dnasearch.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName("DNA Primer Search");
    QCoreApplication::setApplicationVersion("v0.2");
    QCoreApplication::setOrganizationDomain("http://code.google.com");
    QCoreApplication::setOrganizationName("zEr0sUm");

    MainWindow w;
    w.show();

    return a.exec();
}
