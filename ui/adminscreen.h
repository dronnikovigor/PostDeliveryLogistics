#ifndef ADMINSCREEN_H
#define ADMINSCREEN_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>
#include <QLineEdit>

#include "ui/graph/graphwidget.h"

namespace Ui {

class AdminScreen : public QObject
{
    Q_OBJECT
public:
    AdminScreen(QWidget *widget);

private:
    GraphWidget *graphWidget;
    QWidget *edgeWidget;

    QString fromCity;
    QString toCity;
    QString vertex;
    QString newCity;


private slots:
    void addNewCity();
    void addNewEdge();
    void deleteEdge();
    void deleteVertex();

    void addVertexToGraph();
    void addEdgesToGraph();
    void delEdgeFromGraph();
    void delVertexFromGraph();

    void handleFromSelectChanged(QListWidgetItem *item);
    void handleToSelectChanged(QListWidgetItem *item);
    void handleVertexSelectChanged(QListWidgetItem *item);
    void handleNewCityChanged(const QString &item);

signals:
    void logout();
};

}



#endif // ADMINSCREEN_H
