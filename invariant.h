#ifndef INVARIANT_H
#define INVARIANT_H

#include <list>
#include <allocator.h>

template<class T>

class Invariant
{
public:
    Invariant();
    ~Invariant(){}

    static bool checkLoop(int from, int to) {
        return (from == to) ? false : true;
    }

    static bool checkEdgeDist(T graph, int to) {
        for(auto iter = graph.begin();iter!=graph.end(); ++iter)
        {
            if(iter->getNumber() == to){
                return true;
            }
        }
        return false;
    }
};

#endif // INVARIANT_H
