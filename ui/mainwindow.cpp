#include "mainwindow.h"

Ui::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    widget = new QWidget();
    widget->setWindowTitle("Post Delivery Logistics");
    widget->setFixedSize(800,512);
    showLoginScreen();
}

void Ui::MainWindow::showLoginScreen() {
    if (widget != nullptr) {
        delete widget;
        widget = nullptr;
    }
    widget = new QWidget();

    LoginScreen *loginScreen = new LoginScreen(widget);
    connect(loginScreen, SIGNAL(checkCredentialsSignal(QString, QString)), this, SLOT(checkCredentials(QString, QString)));

    this->setCentralWidget(widget);
}

void Ui::MainWindow::showStartScreen(bool adminRights) {
    if (widget != nullptr) {
        delete widget;
        widget = nullptr;
    }
    widget = new QWidget();

    if (adminRights){
        AdminScreen *adminScreen = new AdminScreen(widget);
        connect(adminScreen, SIGNAL(logout()), this, SLOT(showLoginScreen()));
    }
    else {
        UserScreen *userScreen = new UserScreen(widget);
        connect(userScreen, SIGNAL(logout()), this, SLOT(showLoginScreen()));
    }

    this->setCentralWidget(widget);
}

void Ui::MainWindow::checkCredentials(const QString &login, const QString &pass)
{
    Credentials credentials(login, pass);
    switch (credentials.checkCredentials()) {
    case 0: {
        showStartScreen(false);
        break;
    }
    case 1: {
        showStartScreen(true);
        break;
    }
    case -1: {
        break;
    }
    }
}

Ui::MainWindow::~MainWindow()
{
    delete widget;
}
