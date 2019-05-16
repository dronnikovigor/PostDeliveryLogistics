#ifndef USERSCREEN_H
#define USERSCREEN_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QStringList>
#include <QListWidgetItem>

#include "serialize.h"

using Serializer::Serialize;

namespace Ui {

class UserScreen : public QObject
{
    Q_OBJECT
public:
    UserScreen(QWidget *widget);

private slots:
    void handleFromSelectChanged(QListWidgetItem *item);
    void handleToSelectChanged(QListWidgetItem *item);
    void getDirections();

signals:
    void logout();

private:
    QListWidget *fromCityList;
    QListWidget *toCityList;
    QListWidget *resultList;
    QLineEdit *fromSelect;
    QLineEdit *toSelect;
    Graph<std::string> graph;
};

}

#endif // USERSCREEN_H
