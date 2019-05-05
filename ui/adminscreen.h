#ifndef ADMINSCREEN_H
#define ADMINSCREEN_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>

class AdminScreen : public QObject
{
    Q_OBJECT
public:
    AdminScreen(QWidget *widget);

signals:
    void logout();
};

#endif // ADMINSCREEN_H
