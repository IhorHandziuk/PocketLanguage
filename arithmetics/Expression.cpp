#include "Expression.h"

Expression::Expression(string exp) {
    RPN = reversePolishNotation(exp);
    result = calculate(RPN);
}

int Expression::get_result() {
    return result;
}

int Expression::priority(char a) {
    if ((a == '+') || (a == '-')) return 1;
    if ((a == '*') || (a == '/')) return 2;
    if (a == '^') return 3;
    if (a == '#') return 4;
    else return 0;
}

string Expression::reversePolishNotation(string expression) {
    string outputLine;
    stack<char> postNotationStack;
    if (expression[0] == '-') expression[0] = '#';
    if (expression[0] == '+') expression = expression.substr(1, expression.length() - 1);
    for (unsigned int curr_char = 0; curr_char < expression.length(); curr_char++) {
        if (expression[curr_char] >= '0' && expression[curr_char] <= '9') {
            outputLine += expression[curr_char];
        }
        if (expression[curr_char] == '(') {
            if (expression[curr_char + 1] == '-') expression[curr_char + 1] = '#';
            if (expression[curr_char + 1] == '+')
                expression = expression.substr(0, curr_char) +
                             expression.substr(curr_char + 2, expression.length() - 1);
            postNotationStack.push(expression[curr_char]);
        }
        if (expression[curr_char] == ')') {
            while (!postNotationStack.empty() && postNotationStack.top() != '(') {
                outputLine += postNotationStack.top();
                postNotationStack.pop();
            }
            postNotationStack.pop(); //delete left bracket
        }
        if (expression[curr_char] == '+' || expression[curr_char] == '-' ||
            expression[curr_char] == '/' || expression[curr_char] == '*' ||
            expression[curr_char] == '^' || expression[curr_char] == '#') {
            outputLine += " ";
            while (priority(expression[curr_char]) <=
                   ((!postNotationStack.empty()) ? priority(postNotationStack.top()) : 0)) {
                outputLine += postNotationStack.top();
                postNotationStack.pop();
            }
            postNotationStack.push(expression[curr_char]);
        }
        if (curr_char == expression.length() - 1) {
            while (!postNotationStack.empty()) {
                outputLine += postNotationStack.top();
                postNotationStack.pop();
            }
        }
    }
    return outputLine;
}

int Expression::calculate(string postfixNotation) {
    stack<int> calculateStack;
    string digits;
    int tempOperandLeft, tempOperandRight, result = 0;
    for (int curr_char = 0; curr_char < postfixNotation.length(); curr_char++) {
        if (postfixNotation[curr_char] >= '0' && postfixNotation[curr_char] <= '9') {
            while (postfixNotation[curr_char] >= '0' && postfixNotation[curr_char] <= '9') {
                digits += postfixNotation[curr_char];
                curr_char++;
            }
            calculateStack.push(stoi(digits));
            digits = "";
        }
        if (postfixNotation[curr_char] == '#') {
            result = 0 - calculateStack.top();
            calculateStack.pop();
            calculateStack.push(result);
        }
        if (postfixNotation[curr_char] == '+' || postfixNotation[curr_char] == '-' ||
            postfixNotation[curr_char] == '/' || postfixNotation[curr_char] == '*' ||
            postfixNotation[curr_char] == '^') {
            tempOperandRight = calculateStack.top();
            calculateStack.pop();
            tempOperandLeft = calculateStack.top();
            calculateStack.pop();

            switch (postfixNotation[curr_char]) {
                case '-': {
                    result = tempOperandLeft - tempOperandRight;
                    break;
                }
                case '+': {
                    result = tempOperandLeft + tempOperandRight;
                    break;
                }
                case '*': {
                    result = tempOperandLeft * tempOperandRight;
                    break;
                }
                case '/': {
                    result = tempOperandLeft / tempOperandRight;
                    break;
                }
                case '^': {
                    result = static_cast<int>(pow(tempOperandLeft, tempOperandRight));
                    break;
                }
                default:break;
            }
            calculateStack.push(result);
        }
    }
    return calculateStack.top();
}



