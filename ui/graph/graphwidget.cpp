#include "graphwidget.h"

#include <QtGui>

#include <math.h>
#include "edge.h"
#include "node.h"

GraphWidgetUi::GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -310, 400, 510);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    //scale(qreal(0.8), qreal(0.8));
    adjustSize();
    setMinimumSize(400, 400);

    importFromFile();
    drawGraph();
}

void GraphWidgetUi::GraphWidget::addNewVertex(const QString &newVertex)
{
    graph.insert_vertex(newVertex.toStdString());
    serializer.exportToJson(graph);
    drawGraph();
}

void GraphWidgetUi::GraphWidget::addNewEdge(const QString &from, const QString &to)
{
    graph.insert_vertex_pair(from.toStdString(), to.toStdString());
    serializer.exportToJson(graph);
    drawGraph();
}

void GraphWidgetUi::GraphWidget::deleteEdge(const QString &from, const QString &to)
{
    graph.remove_vertex_pair(from.toStdString(), to.toStdString());
    serializer.exportToJson(graph);
    drawGraph();
}

void GraphWidgetUi::GraphWidget::deleteVertex(const QString &vertex)
{
    graph.remove_vertex(vertex.toStdString());
    serializer.exportToJson(graph);
    drawGraph();
}

std::list<std::string> GraphWidgetUi::GraphWidget::getVertices()
{
    return serializer.getVertices();
}

void GraphWidgetUi::GraphWidget::drawGraph()
{
    scene()->clear();

    typename std::list<Graph<std::string>::Vertex>::iterator add_nodes_it = graph.begin();
    for(; add_nodes_it != graph.end(); ++add_nodes_it) {
        Node *node = new Node(this, QString::fromStdString(add_nodes_it->key()));
        vertices.insert(add_nodes_it->key(), node);
        scene()->addItem(node);
    }

    typename std::list<Graph<std::string>::Vertex>::iterator add_edges_it = graph.begin();
    for(; add_edges_it != graph.end(); ++add_edges_it) {
        Node *nodeFrom = vertices.value(add_edges_it->key());
        typename std::list<Graph<std::string>::Edge>::const_iterator edge_it = add_edges_it->edges().begin();
        for(; edge_it != add_edges_it->edges().end(); ++edge_it) {
            Node *nodeTo = vertices.value(edge_it->m_Edge->key());
            scene()->addItem(new Edge(nodeFrom, nodeTo));
        }
    }

    for(QMap<Graph<std::string>::Vertex, Node*>::iterator pos_it=vertices.begin(); pos_it!=vertices.end(); ++pos_it)
    {
        pos_it.value()->setPos(rand()%50, rand()%50);
    }
}

void GraphWidgetUi::GraphWidget::exportToFile()
{
    serializer.exportToJson(graph);
    QMessageBox::information(this, "Done!", "Export done.", QMessageBox::Ok, 0);
}

void GraphWidgetUi::GraphWidget::importFromFile()
{
    serializer.importFromJson();
    graph.clear();
    std::list<std::string> vertices = serializer.getVertices();
    std::vector<std::pair<std::string, std::string>> edges = serializer.getEdges();
    for (std::string it: vertices) {
        graph.insert_vertex(it);
    }
    for (std::pair<std::string, std::string> it: edges) {
        graph.insert_vertex_pair(it.first, it.second);
    }
}

void GraphWidgetUi::GraphWidget::importFromFileAndDraw()
{
    importFromFile();
    drawGraph();
}

void GraphWidgetUi::GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}

void GraphWidgetUi::GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        //centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        //centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        //centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        //centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        scaleView(qreal(1.2));
        break;
    case Qt::Key_Minus:
        scaleView(1 / qreal(1.2));
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        foreach (QGraphicsItem *item, scene()->items()) {
            if (qgraphicsitem_cast<Node *>(item))
                item->setPos(-150 + qrand() % 300, -150 + qrand() % 300);
        }
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidgetUi::GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<Node *> nodes;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    foreach (Node *node, nodes)
        node->calculateForces();

    bool itemsMoved = false;
    foreach (Node *node, nodes) {
        if (node->advance())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}

void GraphWidgetUi::GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}

void GraphWidgetUi::GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    QRectF sceneRect = this->sceneRect();
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);
}

void GraphWidgetUi::GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
