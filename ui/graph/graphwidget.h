#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QMap>

#include "graph.h"

using GraphContainer::Graph;

class Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    void addNewEdge(QString from, QString to);
    void deleteEdge(QString from, QString to);
    void deleteVertex(QString vertex);
    void itemMoved();
    void drawGraph();

protected:
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    void wheelEvent(QWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

    void scaleView(qreal scaleFactor);

private:
    int timerId;
    QMap<Graph<int>::Vertex, Node*> vertices;
    Graph<int> graph;
};

#endif
