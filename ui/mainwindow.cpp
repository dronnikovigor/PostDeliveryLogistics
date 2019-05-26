#include "mainwindow.h"

Ui::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    manipulator= new Manip::Manipulator();
    widget = new QWidget();
    widget->setWindowTitle("Post Delivery Logistics");
    widget->setFixedSize(800,512);
    showLoginScreen();
}

void Ui::MainWindow::showLoginScreen() {
    widget = manipulator->buildWidget(widget);
    connect(manipulator->showScreen(widget), SIGNAL(checkCredentialsSignal(QString, QString)), this, SLOT(showStartScreen(QString, QString)));
    this->setCentralWidget(widget);
}

void Ui::MainWindow::showStartScreen(const QString &login, const QString &pass) {
    Credentials credentials(login, pass);
    if (credentials.checkCredentials()==-1){
        return;
    }
    widget = manipulator->buildWidget(widget);
    Ui::Screen *screen = manipulator->showScreen(credentials.checkCredentials(), widget);
    connect(screen, SIGNAL(logout()), this, SLOT(showLoginScreen()));
    this->setCentralWidget(widget);
}

Ui::MainWindow::~MainWindow()
{
    delete widget;
}
