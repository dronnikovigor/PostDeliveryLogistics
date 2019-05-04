#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPushButton"
#include "QGridLayout"
#include "QVBoxLayout"
#include "QLabel"

#include "helpwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showStartScreen();
    void showLoginScreen();

private:
    QWidget *widget;

    HelpWindow *helpWindow;
};

#endif // MAINWINDOW_H
