#include "ui/mainwindow.h"
#include <QApplication>

#include "graph.h"

using Ui::MainWindow;
using GraphContainer::Graph;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    //Graph example usage
    /*std::vector<std::pair<int, int> > graph_vect;
    for (int i = 0; i < 100; i++) {
        graph_vect.push_back(std::make_pair(rand()%20, rand()%20));
    }
    Graph<int> test_graph(graph_vect);

    test_graph.insert_vertex_pair(1,200);
    test_graph.print_graph();


    std::cout << "External iterator example: " << std::endl;
    typename std::list<Graph<int>::Vertex>::iterator print_it = test_graph.begin();
    for(; print_it != test_graph.end(); ++print_it) {
        std::cout << print_it->key();
        typename std::list<Graph<int>::Edge>::const_iterator edge_it = print_it->edges().begin();
        for(; edge_it != print_it->edges().end(); ++edge_it) {
            std::cout << "-->" << edge_it->m_Edge->key();
        }
        std::cout << std::endl;
    }
    */
    //

    return a.exec();
}


