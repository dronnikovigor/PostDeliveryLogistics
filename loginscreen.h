#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>

class LoginScreen: public QObject
{
    Q_OBJECT
public:
    LoginScreen(QWidget *widget);

private slots:
    void checkCredentials();

signals:
    void checkCredentialsSignal(QString, QString);

private:
    QTextEdit *loginEdit;
    QTextEdit *passEdit;
};

#endif // LOGINSCREEN_H
