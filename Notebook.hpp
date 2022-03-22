#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "Direction.hpp"
using namespace std;

#ifndef MY_HEADER
#define MY_HEADER

namespace ariel{

    class Notebook{
        private:
            double width;
            string str;
        public:
            Notebook();
            Notebook(ariel::Notebook const & other);

            static void write(int page, int row, int column, Direction dir, std::string const & str);
            static string read(int page, int row, int column, Direction dir, int length);
            static void erase(int page, int row, int column, Direction dir, int length);
            static string show(int page);
    };

}

#endif