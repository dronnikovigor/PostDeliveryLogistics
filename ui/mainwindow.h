#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui/loginscreen.h"
#include "ui/adminscreen.h"
#include "ui/userscreen.h"
#include "ui/helpwindow.h"
#include "credentials.h"

namespace Ui {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showStartScreen(bool adminRights);
    void showLoginScreen();

    void checkCredentials(const QString &login, const QString &pass);

private:
    QWidget *widget;
};

}

#endif // MAINWINDOW_H
