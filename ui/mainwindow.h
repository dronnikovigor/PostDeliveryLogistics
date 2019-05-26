#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui/loginscreen.h"
#include "ui/adminscreen.h"
#include "ui/userscreen.h"
#include "ui/helpwindow.h"
#include "credentials.h"
#include "ui/manipulator.h"

namespace Ui {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showStartScreen(const QString &login, const QString &pass);
    void showLoginScreen();

private:
    QWidget *widget;
    Manip::Manipulator *manipulator;
};

}

#endif // MAINWINDOW_H
