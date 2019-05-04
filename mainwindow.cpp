#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    widget = new QWidget();
    helpWindow = new HelpWindow();
    showStartScreen();
}

void MainWindow::showStartScreen() {
    if (widget != nullptr) {
        delete widget;
        widget = nullptr;
    }
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

    connect(loginBtn, SIGNAL(clicked()), this, SLOT(showLoginScreen()));
    connect(helpBtn, SIGNAL(clicked()), helpWindow, SLOT(show()));

    widget->setLayout(gridLayout);
    widget->setWindowTitle("Post Delivery Logistics");
    widget->setFixedSize(800,512);
    this->setCentralWidget(widget);
}

void MainWindow::showLoginScreen() {
    if (widget != nullptr) {
        delete widget;
        widget = nullptr;
    }
    widget = new QWidget();
    QLabel *text = new QLabel("You need to log in!");
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(text);
    widget->setLayout(layout);
    this->setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete widget;
    delete helpWindow;
}
