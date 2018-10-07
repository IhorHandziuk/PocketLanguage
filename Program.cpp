#include <cstring>
#include "Program.h"

string Program::exchange_variables(string expr) {
    //if there are variables in expr
    //then exchange them by their values
    for (int i = 0; i < expr.size(); i++) {
        if ((expr[i] >= 'a' && expr[i] <= 'z') ||
            (expr[i] >= 'A' && expr[i] <= 'Z')) {
            char var = expr[i];
            expr.erase(i, 1);
            expr.insert(i, to_string(variables[var]));
        }
    }
    return expr;
}

void Program::parse() {
    //the order in this array is significant
    string relSigns[] = {">=", "<=", "!=", "<", ">", "="};
    char *currLine = new char[256];
    char *pos;
    while (source.getline(currLine, 256)) {
        if (pos = strstr(currLine, "#")) {
            string label;
            for (int i = 0; currLine[i] != '#'; i++)
                label += currLine[i];
            labels[stoi(label)] = source.tellg();
        }
        if (pos = strstr(currLine, "if")) {
            char *relBeg = strstr(currLine, "(") + 1;
            char *relEnd = strstr(currLine, ")");
            //if (char* relation_pos = strstr(currLine, "<=")) {
            //	string leftExpr = exchange_variables(string(relBeg, relation_pos));
            //	string rightExpr = exchange_variables(string(relation_pos + 2, relEnd));
            //	int left = Expression(leftExpr).get_result();
            //	int right = Expression(rightExpr).get_result();
            //	if (left > right) continue;
            //}
            if (char *relation_pos = strstr(currLine, "=")) {
                string leftExpr = exchange_variables(string(relBeg, relation_pos));
                string rightExpr = exchange_variables(string(relation_pos + 1, relEnd));
                int left = Expression(leftExpr).get_result();
                int right = Expression(rightExpr).get_result();
                if (left != right) continue;
            }
        }
        if (pos = strstr(currLine, ":=")) {
            char varName;
            for (int i = 0; currLine[i] != ':'; i++) {
                if (!isspace(currLine[i])) {
                    varName = currLine[i];
                    break;
                }
            }
            string onlyConstants = exchange_variables(string(pos + 2));
            Expression exp(onlyConstants);
            variables[varName] = exp.get_result();
        }
        if (pos = strstr(currLine, "go")) {
            string desireLebel = string(pos + 2);
            source.seekg(labels[stoi(desireLebel)]);
        }
        if (pos = strstr(currLine, "get")) {
            variables[*(pos + 4)] = cin.get();
        }
        if (strstr(currLine, "finish")) {
            exit(0);
        }
        if (pos = strstr(currLine, "println")) {
            printMsg(pos + 8);
            cout << std::endl;
        } else if (pos = strstr(currLine, "print")) {
            printMsg(pos + 6);
        }
    }
    delete currLine;
}

void Program::printMsg(char *pos) {
    char *strLiteral = pos;
    if (*strLiteral == '$') {
        strLiteral++;
        while (*strLiteral != ')') {
            cout << *strLiteral;
            strLiteral++;
        }
    } else if (variables.count(*strLiteral))
        cout << variables[*strLiteral];
}
