#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

class QGraphicsSceneMouseEvent;

namespace GraphWidgetUi {

class Edge;
class GraphWidget;

class Node : public QGraphicsItem
{
public:
    Node(GraphWidget *graphWidget, const QString &name);

    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    void calculateForces();
    bool advance();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    GraphWidget *graph;
    QString name;
    QList<Edge *> edgeList;
    QPointF newPos;
};
}



#endif
