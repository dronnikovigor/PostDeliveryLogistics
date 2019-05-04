#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>

class HelpWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit HelpWindow(QWidget *parent = nullptr);
    ~HelpWindow();

signals:

public slots:

private:
     QWidget *widget;
};

#endif // HELPWINDOW_H
