#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>
#include <list>
#include <iterator>
#include <assert.h>
#include <QDebug>

template<typename T>

class Iterator {
private:
    std::list<T> * pointer;
    T * current;
public:
    Iterator(std::list<T> * itm) : pointer(itm){
        current = itm->front();
    }

    bool operator!=(const Iterator<T> & iter) const;
    bool operator==(const Iterator<T> & iter) const;

    Iterator& operator++();
    Iterator& operator--();
    Iterator*  next();
    Iterator*  prev();
};

template<typename T>
bool Iterator<T>::operator==(const Iterator<T> & iter) const {
    return current == iter;
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator<T> & iter) const {
    return current != iter;
}

template<typename T>
Iterator<T>* Iterator<T>::next(){
    current = current+1;
    return this;
}

template<typename T>
Iterator<T>* Iterator<T>::prev(){
    current--;
    return this;
}

#endif // ITERATOR_H
