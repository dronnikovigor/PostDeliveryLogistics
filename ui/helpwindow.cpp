#include "helpwindow.h"

Ui::HelpWindow::HelpWindow(QWidget *parent) : QMainWindow(parent)
{    
    QWidget *widget = new QWidget();
    QLabel *text = new QLabel("help here");
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(text);
    widget->setLayout(layout);
    widget->setFixedSize(400,300);
    this->setCentralWidget(widget);
}

Ui::HelpWindow::~HelpWindow()
{
    delete widget;
}
