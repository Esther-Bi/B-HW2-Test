#include <iostream>
#include <string>
#include "Direction.hpp"
#include "Notebook.hpp"
using namespace std;

namespace ariel
{
    const int y = 8;
    Notebook::Notebook(){
        width = y;
        str = "this";
    }
    Notebook::Notebook(ariel::Notebook const &other){
        width = other.width;
        str = other.str;
    }

    void Notebook::write(int page, int row, int column, ariel::Direction dir, std::string const & str){
        int x = y;
    }
    string Notebook::read(int page, int row, int column, ariel::Direction dir, int length){
        return "answer";
    }
    void Notebook::erase(int page, int row, int column, ariel::Direction dir, int length){
        int x=y;
    }
    string Notebook::show(int page){
        return "answer";
    }
}