#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "loginscreen.h"
#include "adminscreen.h"
#include "userscreen.h"
#include "helpwindow.h"
#include "credentials.h"

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

#endif // MAINWINDOW_H
