#pragma once
#include <iostream>
#include <string>

using namespace std;
class Exception {
public:
   Exception() {printError();}
   Exception(const string& msg) : msg_(msg) {printError();}
  ~Exception( ) {}
   string getMessage( ) const {return(msg_);}
   void printError() {
       cout << getMessage( ) << endl;
   }
private:
   string msg_;
};


class FileException: public Exception {
private:
   string file_name;
public:
    FileException(string file_name): Exception("File is opened:" + file_name) {}
};


class SimularVertexException: public Exception {
private:
   string vertex;
public:
    SimularVertexException(string vertex): Exception("Simular Vertices:" + vertex) {}
};

class VertexNotFoundException: public Exception {
private:
   int vertex_number;
public:
    VertexNotFoundException(int vertex_number): Exception("Vertex is not found:" + to_string(vertex_number)) {}
};
