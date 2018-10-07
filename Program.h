#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unordered_map>
#include "arithmetics/Expression.h"
using namespace std;

class Program
{
public:
	Program(string fileName) : source(fileName){}
	unsigned int abs(int x) { if (x > 0) return x; else return -x; };
	void parse();
	string exchange_variables(string);
private:
	ifstream source;
	unordered_map <char, int> variables;
	unordered_map <int, streampos> labels;
	bool exit_success;

	void printMsg(char *pos);
};