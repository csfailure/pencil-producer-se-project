#include "mainwindow.h"
#include <QApplication>

using namespace std;

/**
 * @brief qMain main event loop for qt program
 * @param argc
 * @param argv
 * @return exit status
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet("background-image:url(:/light.jpg)");
    w.show();

    return a.exec();
}
