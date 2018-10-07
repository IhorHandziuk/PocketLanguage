#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cmath>

using namespace std;

class Expression {
public:
    explicit Expression(string);

    int get_result();

private:
    int priority(char a);

    string reversePolishNotation(string expression);

    int calculate(string postfixNotation);

    string RPN;
    int result;
};