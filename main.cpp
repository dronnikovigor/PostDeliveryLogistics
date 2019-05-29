#include "ui/mainwindow.h"
#include <QApplication>

#include "graph.h"
#include "serialize.h"

using Ui::MainWindow;
using GraphContainer::Graph;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


