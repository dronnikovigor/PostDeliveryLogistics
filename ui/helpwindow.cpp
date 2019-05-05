#include "helpwindow.h"

HelpWindow::HelpWindow(QWidget *parent) : QMainWindow(parent)
{    
    QWidget *widget = new QWidget();
    QLabel *text = new QLabel("help here");
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(text);
    widget->setLayout(layout);
    widget->setFixedSize(400,300);
    this->setCentralWidget(widget);
}

HelpWindow::~HelpWindow()
{
    delete widget;
}
