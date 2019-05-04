#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    widget = new QWidget();
    QGridLayout *gridLayout = new QGridLayout();
    QVBoxLayout *vertLayout = new QVBoxLayout();
    QPushButton *loginBtn = new QPushButton("Sign In");
    QPushButton *helpBtn = new QPushButton("Help");
    loginBtn->setFixedHeight(45);
    helpBtn->setFixedHeight(45);
    QFont font = loginBtn->font();
    font.setPointSize(15);
    loginBtn->setFont(font);
    helpBtn->setFont(font);

    QImage *logoImg = new QImage(":/images/delivery-512.png");
    QLabel *imgDisplayLabel = new QLabel("");
    imgDisplayLabel->setPixmap(QPixmap::fromImage(*logoImg));
    imgDisplayLabel->adjustSize();

    vertLayout->addWidget(loginBtn);
    vertLayout->addWidget(helpBtn);
    gridLayout->addLayout(vertLayout, 0, 0, 0, 1);
    gridLayout->addWidget(imgDisplayLabel, 0, 1, 1, 1);

    widget->setLayout(gridLayout);
    widget->setWindowTitle("Post Delivery Logistics");
    widget->setFixedSize(800,512);
    this->setCentralWidget(widget);
}

MainWindow::~MainWindow()
{

}
