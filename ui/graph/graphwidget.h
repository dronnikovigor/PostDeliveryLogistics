#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QMap>
#include <QMessageBox>

#include "graph.h"
#include "serialize.h"

using GraphContainer::Graph;
using Serializer::Serialize;

class Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    void addNewVertex(const QString &newVertex);
    void addNewEdge(QString from, QString to);
    void deleteVertex(QString vertex);
    void deleteEdge(QString from, QString to);
    void itemMoved();
    void drawGraph();
    std::list<int> getVertices();

public slots:
    void exportToFile();
    void importFromFile();
    void importFromFileAndDraw();

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

    Serialize<int> serializer;
};

#endif
