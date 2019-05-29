#pragma once
#include <iostream>
#include <string>

class Exception {
public:
   Exception() {printError();}
   Exception(const std::string& msg) : msg_(msg) {printError();}
  ~Exception( ) {}
   std::string getMessage( ) const {return(msg_);}
   void printError() {
       std::cout << getMessage( ) << std::endl;
   }
private:
   std::string msg_;
};


class FileException: public Exception {
private:
   std::string file_name;
public:
    FileException(std::string file_name): Exception("File is opened:" + file_name) {}
};


class SimularVertexException: public Exception {
private:
   std::string vertex;
public:
    SimularVertexException(std::string vertex): Exception("Simular Vertices:" + vertex) {}
};

class VertexNotFoundException: public Exception {
private:
   int vertex_number;
public:
    VertexNotFoundException(int vertex_number): Exception("Vertex is not found:" + std::to_string(vertex_number)) {}
};
