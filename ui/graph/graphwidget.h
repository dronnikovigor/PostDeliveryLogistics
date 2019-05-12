#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QMap>
#include <QMessageBox>

#include "graph.h"
#include "serialize.h"

using GraphContainer::Graph;
using Serializer::Serialize;

namespace GraphWidgetUi {
class Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    void addNewVertex(const QString &newVertex);
    void addNewEdge(const QString &from, const QString &to);
    void deleteVertex(const QString &vertex);
    void deleteEdge(const QString &from, const QString &to);
    void itemMoved();
    void drawGraph();

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
    QMap<Graph<std::string>::Vertex, Node*> vertices;
    Graph<std::string> graph;
};
}

#endif
