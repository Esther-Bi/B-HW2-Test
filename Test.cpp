#include "doctest.h"
#include "Notebook.hpp"
using namespace ariel;

#include <string>
#include <algorithm>
using namespace std;

TEST_CASE("Good input") {
	ariel::Notebook notebook;
	for (int i=0 ; i<20 ; i++){
		for (int j=0 ; j<50 ; j++){
			for (int k=0 ; k<50 ; k+=10){
				CHECK_NOTHROW(notebook.write(i, j, k, ariel::Direction::Horizontal, "abcdefghij"));
				CHECK_NOTHROW(notebook.read(i, j, k, ariel::Direction::Horizontal, 10));
				CHECK_NOTHROW(notebook.erase(i, j, k, ariel::Direction::Horizontal, 10));
			}
		}
	}
}

TEST_CASE("Negative input") {
	ariel::Notebook notebook;
	for (int i=-20 ; i<0 ; i++){
		for (int j=-20 ; j<10 ; j++){
			for (int k=-50 ; k<3 ; k+=10){
				for (int m=-5 ; m<0 ; m++){
					CHECK_THROWS(notebook.write(i, j, k, ariel::Direction::Horizontal, "abcdefghij"));
					CHECK_THROWS(notebook.read(i, j, k, ariel::Direction::Vertical, m));
					CHECK_THROWS(notebook.erase(i, j, k, ariel::Direction::Horizontal, m));
				}
			}
		}
	}
}

TEST_CASE("Write to not enough space") {
	ariel::Notebook notebook;
	CHECK_THROWS(notebook.write(0, 1, 95, ariel::Direction::Horizontal, "1234567"));
	CHECK_THROWS(notebook.write(0, 3, 99, ariel::Direction::Horizontal, "abc"));
}

TEST_CASE("Delete from not enough space") {
	ariel::Notebook notebook;
	CHECK_THROWS(notebook.erase(0, 1, 95, ariel::Direction::Horizontal, 7));
	CHECK_THROWS(notebook.erase(0, 3, 99, ariel::Direction::Horizontal, 3));
}

TEST_CASE("Write to already written place") {
	ariel::Notebook notebook;
	CHECK_NOTHROW(notebook.write(0, 0, 4, ariel::Direction::Horizontal, "456789"));
	CHECK_THROWS(notebook.write(0, 0, 7, ariel::Direction::Vertical, "abc"));
	CHECK_NOTHROW(notebook.write(1, 1, 5, ariel::Direction::Vertical, "12345"));
	CHECK_THROWS(notebook.write(1, 3, 4, ariel::Direction::Horizontal, "abc"));
	CHECK_NOTHROW(notebook.write(2, 0, 7, ariel::Direction::Vertical, "0123456789"));
	CHECK_THROWS(notebook.write(2, 3, 4, ariel::Direction::Horizontal, "45678"));
}

TEST_CASE("Delete from already deleted place") {
	ariel::Notebook notebook;
	CHECK_NOTHROW(notebook.erase(0, 0, 4, ariel::Direction::Horizontal, 6));
	CHECK_THROWS(notebook.erase(0, 0, 7, ariel::Direction::Vertical, 3));
	CHECK_NOTHROW(notebook.erase(1, 1, 5, ariel::Direction::Vertical, 5));
	CHECK_THROWS(notebook.erase(1, 3, 4, ariel::Direction::Horizontal, 3));
	CHECK_NOTHROW(notebook.erase(2, 0, 7, ariel::Direction::Vertical, 10));
	CHECK_THROWS(notebook.erase(2, 3, 4, ariel::Direction::Horizontal, 5));
}


TEST_CASE("Write to unreachable space") {
	ariel::Notebook notebook;
	CHECK_THROWS(notebook.write(0, 1, 101, ariel::Direction::Vertical, "1234567"));
	CHECK_THROWS(notebook.write(0, 3, 200, ariel::Direction::Vertical, "abc"));
	CHECK_THROWS(notebook.write(0, 1, 304, ariel::Direction::Horizontal, "1234567"));
	CHECK_THROWS(notebook.write(0, 3, 500, ariel::Direction::Horizontal, "abc"));
}

TEST_CASE("Delete from unreachable space") {
	ariel::Notebook notebook;
	CHECK_THROWS(notebook.erase(0, 1, 101, ariel::Direction::Vertical, 15));
	CHECK_THROWS(notebook.erase(0, 3, 200, ariel::Direction::Vertical, 1));
	CHECK_THROWS(notebook.erase(0, 1, 304, ariel::Direction::Horizontal, 4));
	CHECK_THROWS(notebook.erase(0, 3, 500, ariel::Direction::Horizontal, 8));
}

TEST_CASE("Undefined chars in string input") {
	string word;
	ariel::Notebook notebook;
	for (int i=0 ; i<32 ; i++){
		word = i;
		CHECK_THROWS(notebook.write(0, 1, 3, ariel::Direction::Vertical, word));
	}
	word = 95;
	CHECK_THROWS(notebook.write(0, 3, 7, ariel::Direction::Vertical, word));
	for (int i=126 ; i<200 ; i++){
		word = i;
		CHECK_THROWS(notebook.write(0, 1, 3, ariel::Direction::Vertical, word));
	}
}

TEST_CASE("Write more than 100 chars horizontally") {
	string word;
	for (int i=0 ; i<101 ; i++){
		word = word + "a";
	}
	ariel::Notebook notebook;
	CHECK_THROWS(notebook.write(0, 1, 0, ariel::Direction::Horizontal, word));
}

TEST_CASE("Delete more than 100 chars horizontally") {
	ariel::Notebook notebook;
	CHECK_THROWS(notebook.erase(0, 1, 101, ariel::Direction::Horizontal, 101));
}