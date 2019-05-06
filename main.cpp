#include "ui/mainwindow.h"
#include <QApplication>

using Ui::MainWindow;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
