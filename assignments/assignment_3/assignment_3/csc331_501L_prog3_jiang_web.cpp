/******************************************************
Xin Yu (Jason) Jiang
CSC331 | Section: 501L
Program Assignment 3: Stack Implementation
Due Date: Oct 31st, 2025 at 11:59PM

Program Name: csc331_501L_prog3_jiang_web.cpp

MODIFICATION FOR WEB: Added evaluateExpression() function
at the bottom to expose functionality to JavaScript.
All original logic remains unchanged.
******************************************************/

#include <iostream>
#include <string>
#include <cmath>
#include <cstddef>

#include "stack331_f25.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#endif

using namespace std;

// Function to check if a character is an operator
bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^');
}

// Function to check if a character is a digit
bool isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

// Function to check if a number is an integer (no fractional part)
bool isInteger(double num)
{
    return (num == std::floor(num));
}

// Function to perform the operation
double performOperation(double operand1, double operand2, char op, bool &error, std::string &errorMsg)
{
    error = false;

    switch (op)
    {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        if (operand2 == 0)
        {
            error = true;
            errorMsg = "error: division by zero";
            return 0;
        }
        return operand1 / operand2;
    case '%':
        if (!isInteger(operand1) || !isInteger(operand2))
        {
            error = true;
            errorMsg = "error: non-integer operand for %";
            return 0;
        }
        if (operand2 == 0)
        {
            error = true;
            errorMsg = "error: division by zero";
            return 0;
        }
        return (int)operand1 % (int)operand2;
    case '^':
        return std::pow(operand1, operand2);
    default:
        return 0;
    }
}

// Function to evaluate postfix expression
void evaluatePostfix(std::string expression)
{
    stack331_f25 myStack;
    bool error = false;
    std::string errorMsg = "";

    for (int i = 0; i < expression.length(); i++)
    {
        char c = expression[i];

        if (isDigit(c))
        {
            myStack.push(c - '0');
        }
        else if (isOperator(c))
        {
            if (myStack.empty())
            {
                error = true;
                errorMsg = "error: invalid expression";
                break;
            }
            double operand2 = myStack.top();
            myStack.pop();

            if (myStack.empty())
            {
                error = true;
                errorMsg = "error: invalid expression";
                break;
            }
            double operand1 = myStack.top();
            myStack.pop();

            double result = performOperation(operand1, operand2, c, error, errorMsg);

            if (error)
            {
                break;
            }

            myStack.push(result);
        }
    }

    if (error)
    {
        std::cout << errorMsg << std::endl;
    }
    else if (myStack.empty())
    {
        std::cout << "error: invalid expression" << std::endl;
    }
    else
    {
        double finalResult = myStack.top();

        if (isInteger(finalResult))
        {
            std::cout << (int)finalResult << std::endl;
        }
        else
        {
            std::cout << finalResult << std::endl;
        }
    }
}

// ORIGINAL MAIN - only compiled for terminal use (not web)
#ifndef __EMSCRIPTEN__
int main()
{
    std::string expression;

    while (true)
    {
        std::cout << "Please enter an expression in post-fix notation: ";

        if (!std::getline(std::cin, expression))
        {
            break;
        }

        if (expression.empty())
        {
            continue;
        }

        if (expression == "end-of-file" || expression == "end of file")
        {
            break;
        }

        evaluatePostfix(expression);
    }

    return 0;
}
#endif

#ifdef __EMSCRIPTEN__
// WEB-ONLY: Function exposed to JavaScript (does not affect terminal version)
std::string evaluateExpression(std::string expression)
{
    if (expression.empty())
    {
        return "error: empty expression";
    }

    stack331_f25 myStack;
    bool error = false;
    std::string errorMsg = "";

    for (int i = 0; i < expression.length(); i++)
    {
        char c = expression[i];

        if (isDigit(c))
        {
            myStack.push(c - '0');
        }
        else if (isOperator(c))
        {
            if (myStack.empty())
            {
                return "error: invalid expression";
            }
            double operand2 = myStack.top();
            myStack.pop();

            if (myStack.empty())
            {
                return "error: invalid expression";
            }
            double operand1 = myStack.top();
            myStack.pop();

            double result = performOperation(operand1, operand2, c, error, errorMsg);

            if (error)
            {
                return errorMsg;
            }

            myStack.push(result);
        }
    }

    if (myStack.empty())
    {
        return "error: invalid expression";
    }
    else
    {
        double finalResult = myStack.top();

        if (isInteger(finalResult))
        {
            return std::to_string((int)finalResult);
        }
        else
        {
            return std::to_string(finalResult);
        }
    }
}

// Bind the function to JavaScript
EMSCRIPTEN_BINDINGS(postfix_module)
{
    emscripten::function("evaluateExpression", &evaluateExpression);
}
#endif