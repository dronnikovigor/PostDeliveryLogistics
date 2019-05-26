#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QFile>
#include <QDebug>

#include "singleton.h"
#include "graph.h"
#include "exceptions.h"

using GraphContainer::Graph;

namespace Serializer
{

template <class T>
class Serialize:public Singleton<Serialize<T>>
{
public:
    void exportToJson(GraphContainer::Graph<T> graph);
    void importFromJson();
    std::vector<std::pair<T, T>> getEdges();
    std::list<T> getVertices();

private:
    friend class Singleton<Serialize<T>>;
    Serialize();
    std::vector<std::pair<T, T>> edges;
    std::list<T> vertices;
};
}

template <class T>
Serializer::Serialize<T>::Serialize()
{
    importFromJson();
}

template <class T>
void Serializer::Serialize<T>::exportToJson(GraphContainer::Graph<T> graph)
{

    edges.clear();
    vertices.clear();
    typename std::list<typename Graph<T>::Vertex>::iterator graph_it = graph.begin();
    for(; graph_it != graph.end(); ++graph_it) {
        vertices.push_back(graph_it->key());
        typename std::list<typename Graph<T>::Edge>::const_iterator edge_it = graph_it->edges().begin();
        for(; edge_it != graph_it->edges().end(); ++edge_it) {
            edges.push_back(std::make_pair(graph_it->key(), edge_it->m_Edge->key()));
        }
    }

    QJsonObject jobject;
    QJsonArray jEdges;
    QJsonArray jVertices;

    for (T it: vertices) {
        QJsonObject obj;
        obj["vertex"] = QString::fromStdString(it); //not template thing! temporary solution
        jVertices.push_back(obj);
    }

    for (std::pair<T, T> it: edges) {
        QJsonObject obj;
        obj["from"] = QString::fromStdString(it.first); //not template thing! temporary solution
        obj["to"] = QString::fromStdString(it.second); //not template thing! temporary solution
        jEdges.push_back(obj);
    }

    jobject["Vertices"] = jVertices;
    jobject["Edges"] = jEdges;

    QJsonDocument json_doc(jobject);
    QString json_string = json_doc.toJson();
    QString path = "json.json";
    QFile save_file(path);
    if (save_file.exists())
        save_file.remove();
    if (!save_file.open(QIODevice::WriteOnly)) {
        throw FileException(path.toStdString());
    }
    save_file.write(json_string.toLocal8Bit());
    save_file.close();
}

template <class T>
void Serializer::Serialize<T>::importFromJson()
{
    QString path = "json.json";
    QString json;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
       throw FileException(path.toStdString());
    }
    json = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jEdges = jsonObject["Edges"].toArray();
    QJsonArray jVertices = jsonObject["Vertices"].toArray();

    edges.clear();
    vertices.clear();

    QString propertyVertex;
    foreach (const QJsonValue &value, jVertices) {
        QJsonObject obj = value.toObject();
        propertyVertex = obj["vertex"].toString();
        vertices.push_back(propertyVertex.toStdString());
    }

    QString propertyFrom;
    QString propertyTo;
    foreach (const QJsonValue &value, jEdges) {
        QJsonObject obj = value.toObject();
        propertyFrom = obj["from"].toString();
        propertyTo = obj["to"].toString();
        edges.push_back(std::make_pair(propertyFrom.toStdString(), propertyTo.toStdString()));
    }
}

template <class T>
std::vector<std::pair<T, T>> Serializer::Serialize<T>::getEdges()
{
    return edges;
}

template <class T>
std::list<T> Serializer::Serialize<T>::getVertices()
{
    return vertices;
}

#endif // SERIALIZE_H
