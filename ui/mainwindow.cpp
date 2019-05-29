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
    widget = Manip::Manipulator::getInstance().buildWidget(widget);
    connect(Manip::Manipulator::getInstance().showScreen(widget), SIGNAL(checkCredentialsSignal(QString, QString)), this, SLOT(showStartScreen(QString, QString)));
    this->setCentralWidget(widget);
}

void Ui::MainWindow::showStartScreen(const QString &login, const QString &pass) {
    Credentials credentials(login, pass);
    qint8 grants = credentials.checkCredentials();
    if (grants == -1){
        return;
    }
    widget = Manip::Manipulator::getInstance().buildWidget(widget);
    Ui::Screen *screen = Manip::Manipulator::getInstance().showScreen(grants, widget);
    connect(screen, SIGNAL(logout()), this, SLOT(showLoginScreen()));
    this->setCentralWidget(widget);
}

Ui::MainWindow::~MainWindow()
{
    delete widget;
}
