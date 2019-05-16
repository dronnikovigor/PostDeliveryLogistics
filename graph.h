#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <QString>

namespace GraphContainer
{

template <class T>
class Graph
{
public :
    Graph();
    Graph(const std::vector<std::pair<T, T> > &vertices);
    ~Graph(){}
    void insert_vertex(T key);
    void remove_vertex(T key);
    void insert_vertex_pair(T key1, T key2);
    void remove_vertex_pair(T key1, T key2);
    std::list<T> search_dist(T key1, T key2);
    void print_graph();
    void clear();

    class Vertex;
    static int vertCount;

    struct Edge
    {
        Edge(Vertex *edge) :
            m_Edge(edge)
        {}
        Vertex *m_Edge;

        const Vertex &key() const {return *m_Edge;}

        bool operator< (const Edge &other) const {
            return key() < other.key();
        }

        bool operator== (const Edge &other) const {
            return key() == other.key();
        }
    };

    class Vertex
    {
    public:
        Vertex(T key) :
            m_Key(key)
        { setNumber(++vertCount); }
        void connect_edge(Vertex *adjacent);
        void disconnect_edge(Graph<T>::Vertex *adjacent);
        const T key() const {return m_Key;}
        int getNumber() {return number;}
        void setNumber(int n) {number = n;}
        const std::list<Edge> &edges() const {return m_Edges;}
        bool operator< (const Vertex &other) const {
            return key() < other.key();
        }

        bool operator== (const Vertex &other) const {
            return key() == other.key();
        }

    private:
        std::list<Edge> m_Edges;
        T m_Key;
        int number;
        bool contains_edge_to_vertex(const T key);
    };

private:
    using vertices_type = std::list<Vertex>;

public:
    using iterator = typename vertices_type::iterator;
    using const_iterator = typename vertices_type::const_iterator;
    iterator begin() { return m_Vertices.begin(); }
    iterator end() { return m_Vertices.end(); }
    const_iterator begin() const { return m_Vertices.begin(); }
    const_iterator end() const { return m_Vertices.end(); }
    const_iterator cbegin() const { return m_Vertices.cbegin(); }
    const_iterator cend() const { return m_Vertices.cend(); }

private:
    vertices_type m_Vertices;
    Vertex *contains_vertex(const T key);
    bool contains_vertex_in_list(std::list<T> list, const T key);
    T getVertexKey(int position)
    {
        typename std::list<Vertex>::iterator find_it = m_Vertices.begin();
        for(; find_it != m_Vertices.end(); ++find_it) {
            if (find_it->getNumber() == position) {
                return find_it->key();
            }
        }
        return NULL;
    }
    std::list<T> vertices;
};
}

template <class T>
int GraphContainer::Graph<T>::vertCount = -1;

template <class T>
GraphContainer::Graph<T>::Graph()
{
}

template <class T>
GraphContainer::Graph<T>::Graph(const std::vector<std::pair<T, T> > &vertices_relation)
{
    typename std::vector<std::pair<T, T> >::const_iterator insert_it = vertices_relation.begin();
    for(; insert_it != vertices_relation.end(); ++insert_it) {
        insert_vertex_pair(insert_it->first, insert_it->second);
    }
}

/*!
 * Takes in a value of type T as a key and
 * inserts it into graph data structure if
 * key not already present
 */
template <typename T>
void GraphContainer::Graph<T>::insert_vertex(T key)
{
    /*!
   * Check if vertex already in graph
   */
    Graph<T>::Vertex *insert = contains_vertex(key);
    /*!
   * If not in graph then insert it and get a pointer to it
   * to pass into edge. See () for information on how
   * to build graph
   */
    if (insert == NULL) {
        m_Vertices.push_back(Vertex(key));
        insert = contains_vertex(key);
    }
    /*!
   * At this point we should have a Vertex in graph
   * if not throw an error.
   */
    if (insert == NULL) {
        throw std::runtime_error("Unknown");
    }
}

/*!
 * Takes in a value of type T as a key and
 * inserts it into graph data structure if
 * key not already present
 */
template <typename T>
void GraphContainer::Graph<T>::insert_vertex_pair(T key1, T key2)
{
    /*!
   * Check if vertices are simular
   */
    if (key1 == key2) {
        //throw std::runtime_error("Simular Vertices!");
        return;
    }
    /*!
   * Check if vertices already in graph
   */
    Graph<T>::Vertex *insert1 = contains_vertex(key1);
    Graph<T>::Vertex *insert2 = contains_vertex(key2);
    /*!
   * If not in graph then insert it and get a pointer to it
   * to pass into edge. See () for information on how
   * to build graph
   */
    if (insert1 == NULL) {
        m_Vertices.push_back(Vertex(key1));
        insert1 = contains_vertex(key1);
    }
    if (insert2 == NULL) {
        m_Vertices.push_back(Vertex(key2));
        insert2 = contains_vertex(key2);
    }

#ifndef NDEBUG
    assert(insert1 != NULL && "Failed to insert first vertex");
    assert(insert2 != NULL && "Failed to insert second vertex");
#endif
    /*!
   * At this point we should have a Vertex to insert an edge on
   * if not throw an error.
   */
    if (insert1 != NULL && insert2 != NULL) {
        insert1->connect_edge(insert2);

#ifndef NDEBUG
        std::cout <<"Inserting pair: " <<  insert1->key() << " -- > " << insert2->key() <<
                    std::endl;
#endif
        //insert2->connect_edge(insert1);
    } else {
        throw std::runtime_error("Unknown");
    }
}

/*!
 * Takes in a value of type T as a key and
 * removes it from graph data structure if
 * key present
 */
template <typename T>
void GraphContainer::Graph<T>::remove_vertex(T key)
{
    /*!
   * Check if vertex exist in graph
   */
    Graph<T>::Vertex *vertex = contains_vertex(key);

#ifndef NDEBUG
    assert(vertex != NULL && "Failed to find vertex");
#endif

    /*!
   * At this point we should have a Vertex to remove
   * if not throw an error.
   */
    if (vertex != NULL) {
        /*!
         * Removing edges from vertex
         */
        typename std::list<Edge>::const_iterator edge_it = vertex->edges().begin();
        for(; edge_it != vertex->edges().end(); ++edge_it) {
            remove_vertex_pair(vertex->key(), edge_it->m_Edge->key());
        }
        /*!
         * Removing edges to vertex
         */
        typename std::list<Vertex>::iterator vert_it = m_Vertices.begin();
        for(; vert_it != m_Vertices.end(); ++vert_it) {
            typename std::list<Edge>::const_iterator edge_it = vert_it->edges().begin();
            for(; edge_it != vert_it->edges().end(); ++edge_it) {
                if (edge_it->m_Edge->key() == vertex->key()) {
                    remove_vertex_pair(vert_it->key(), vertex->key());
                }
            }
        }
        /*!
         * Removing vertex
         */
        m_Vertices.remove(vertex->key());
    } else {
        throw std::runtime_error("Unknown");
    }
}

/*!
 * Takes in a value of type T as a key and
 * removes it from graph data structure if
 * key present
 */
template <typename T>
void GraphContainer::Graph<T>::remove_vertex_pair(T key1, T key2)
{
    /*!
   * Check if vertices are simular
   */
    if (key1 == key2) {
        //throw std::runtime_error("Simular Vertices!");
        return;
    }
    /*!
   * Check if vertices already in graph
   */
    Graph<T>::Vertex *vertex1 = contains_vertex(key1);
    Graph<T>::Vertex *vertex2 = contains_vertex(key2);

#ifndef NDEBUG
    assert(vertex1 != NULL && "Failed to find pair (first vertex not exists)");
    assert(vertex2 != NULL && "Failed to find pair (second vertex not exists)");
#endif

    /*!
   * At this point we should have a Vertex to insert an edge on
   * if not throw an error.
   */
    if (vertex1 != NULL && vertex2 != NULL) {
        vertex1->disconnect_edge(vertex2);
        //insert2->disconnect_edge(insert1);
    } else {
        throw std::runtime_error("Unknown");
    }
}

/*!
 * Search the std::list of vertices for key
 * if present return the Vertex to indicate
 * already in graph else return NULL to indicate
 * new node
 */
template <typename T>
typename GraphContainer::Graph<T>::Vertex *GraphContainer::Graph<T>::contains_vertex(T key)
{
    typename std::list<Vertex >::iterator find_it = m_Vertices.begin();
    for(; find_it != m_Vertices.end(); ++find_it) {
        if (find_it->key() == key) {
            return &(*find_it);
        }
    }
    return NULL;
}

/*!
 * Take the oposing Vertex from input and insert it
 * into adjacent list, you can have multiple edges
 * between vertices
 */
template <class T>
void GraphContainer::Graph<T>::Vertex::connect_edge(Graph<T>::Vertex *adjacent)
{
    if (adjacent == NULL)
        return;

    if (!contains_edge_to_vertex(adjacent->key())) {
        Graph<T>::Edge e(adjacent);
        m_Edges.push_back(e);
    }
}

/*!
 * Take the oposing Vertex from input and remove it
 * from adjacent list
 */
template <class T>
void GraphContainer::Graph<T>::Vertex::disconnect_edge(Graph<T>::Vertex *adjacent)
{
    if (adjacent == NULL)
        return;

    if (contains_edge_to_vertex(adjacent->key())) {
        Graph<T>::Edge e(adjacent);
        m_Edges.remove(e);
    }
}

/*!
 * Private member function that check if there is already
 * an edge between the two vertices
 */
template <class T>
bool GraphContainer::Graph<T>::Vertex::contains_edge_to_vertex(const T key)
{
    typename std::list<Edge>::iterator find_it = m_Edges.begin();
    for(; find_it != edges().end(); ++find_it) {
        if (find_it->m_Edge->key() == key) {
            return true;
        }
    }
    return false;
}

template <typename T>
void GraphContainer::Graph<T>::print_graph()
{
    std::cout << "Graph: " << std::endl;
    typename std::list<Vertex>::iterator print_it = m_Vertices.begin();
    for(; print_it != m_Vertices.end(); ++print_it) {
        std::cout << print_it->key();
        typename std::list<Edge>::const_iterator edge_it = print_it->edges().begin();
        for(; edge_it != print_it->edges().end(); ++edge_it) {
            std::cout << "-->" << edge_it->m_Edge->key();
        }
        std::cout << std::endl;
    }
}

template <typename T>
void GraphContainer::Graph<T>::clear()
{
    m_Vertices.clear();
}

template <typename T>
typename std::list<T> GraphContainer::Graph<T>::search_dist(T key1, T key2)
{
    Graph<T>::Vertex *from = contains_vertex(key1);
    Graph<T>::Vertex *to = contains_vertex(key2);
    vertices.clear();
    int N = m_Vertices.size();

    std::vector < std::vector <int> > b(N, std::vector <int> (N) );
    std::vector < std::vector <int> > c(N, std::vector <int> (N) );

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++) {b[i][j]=999999;b[i][i]=999999;c[i][j]=-1;}
    typename std::list<Vertex>::iterator print_it = m_Vertices.begin();
    for(; print_it != m_Vertices.end(); ++print_it) {
        typename std::list<Edge>::const_iterator edge_it = print_it->edges().begin();
        for(; edge_it != print_it->edges().end(); ++edge_it) {
            b[print_it->getNumber()][edge_it->m_Edge->getNumber()] = 1;
        }

    }
    for(int k=0;k<N;k++)
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++){
                int a=b[i][k]+b[k][j];
                if(b[i][j]>a)
                {
                    c[i][j]=k;
                    b[i][j]=a;
                }
            }
    int i=from->getNumber(),j=to->getNumber();
    while(c[i][j]!=-1){
        vertices.push_front(getVertexKey(c[i][j]));
        j=c[i][j];
    }
    i=from->getNumber(),j=to->getNumber();
    while(c[i][j]!=-1){
        if( !contains_vertex_in_list(vertices, getVertexKey(c[i][j]))){
            vertices.push_back(getVertexKey(c[i][j]));
        }
        i=c[i][j];
    }
    vertices.push_front(getVertexKey(from->getNumber()));
    vertices.push_back(getVertexKey(to->getNumber()));
    return vertices;
}

template <typename T>
bool GraphContainer::Graph<T>::contains_vertex_in_list(std::list<T> list, T key)
{
    typename std::list<std::string>::iterator find_it = list.begin();
    for(; find_it != list.end(); ++find_it) {
        if (find_it->data() == key) {
            return true;
        }
    }
    return false;
}

#endif // GRAPH_H
