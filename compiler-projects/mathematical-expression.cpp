//
//  main.cpp
//  compiler-projects
//
//  Created by Amirkian Kiani on 2/24/24.
//

#include <iostream>
#include <stack>
#include <sstream>

using namespace std;

// Function to check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to perform a binary operation
int applyOperator(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            return 0; // Invalid operator
    }
}

// Function to evaluate the expression with parentheses
int evaluateExpression(const string& expression) {
    stack<int> values;
    stack<char> operators;

    stringstream ss(expression);
    char token;

    while (ss >> token) {
        if (isdigit(token)) {
            // If the token is a digit, convert it to int and push to values stack
            ss.putback(token);
            int value;
            ss >> value;
            values.push(value);
        } else if (token == '(') {
            // If the token is an opening parenthesis, push to operators stack
            operators.push(token);
        } else if (token == ')') {
            // If the token is a closing parenthesis, evaluate until matching opening parenthesis
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top();
                operators.pop();

                int b = values.top();
                values.pop();
                int a = values.top();
                values.pop();

                values.push(applyOperator(a, b, op));
            }

            // Pop the matching opening parenthesis
            operators.pop();
        } else if (isOperator(token)) {
            // If the token is an operator, evaluate higher precedence operators before pushing
            while (!operators.empty() && isOperator(operators.top())) {
                char op = operators.top();
                operators.pop();

                int b = values.top();
                values.pop();
                int a = values.top();
                values.pop();

                values.push(applyOperator(a, b, op));
            }

            // Push the current operator to the stack
            operators.push(token);
        }
    }

    // Final evaluation of remaining operators
    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();

        int b = values.top();
        values.pop();
        int a = values.top();
        values.pop();

        values.push(applyOperator(a, b, op));
    }

    // The final result is at the top of the values stack
    return values.top();
}

int main() {
    cout << "Enter an expression with parentheses: ";
    string expression;
    getline(cin, expression);

    int result = evaluateExpression(expression);
    cout << "Result: " << result << endl;

    return 0;
}
