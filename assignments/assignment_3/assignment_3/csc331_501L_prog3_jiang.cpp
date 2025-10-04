/******************************************************
Xin Yu (Jason) Jiang
CSC331 | Section: 501L
Program Assignment 3: Stack Implementation
Due Date: Oct 31st, 2025 at 11:59PM

Program Name: csc331_501L_prog3_jiang.cpp

Program Purpose:
This program implements an interactive stack-based postfix expression evaluator in C++.
It allows users to input arithmetic expressions either manually or through a text file using command-line redirection.
Each expression is processed using a stack to compute its result, with support for basic arithmetic operations (+, -, *, /, %, ^).
The program displays the result or appropriate error messages
(e.g., division by zero or invalid modulus with non-integers) directly to the console, continuing until an end-of-file signal is received.
******************************************************/

#include <iostream>
#include <string>
#include <cmath>

/*
The header file stack331_f25.h uses cout and NULL
but doesn't include the necessary headers. Since I cannot modify the header file per assignment rules, I will include the required cstddef header here:
*/
#include <cstddef> // provides the definition for NULL

/* Note: header file already implements a linked list-based stack, not an array or vector-based one.
Additionally, no changes can be made to the header file!
*/
#include "stack331_f25.h"

using namespace std;

// Function to check if a character is an operator
bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^');
}

// Function to check if a character is a digit
bool isDigit(char c)
{
    return (c >= '0' && c <= '9'); // 0-9 inclusive
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

    // Process each character in the expression
    for (int i = 0; i < expression.length(); i++)
    {
        char c = expression[i];

        // If the character is a digit, push it onto the stack
        if (isDigit(c))
        {
            myStack.push(c - '0'); // Convert char to int
        }
        // If the character is an operator
        else if (isOperator(c))
        {
            // Pop two operands from stack
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

            // Perform the operation
            double result = performOperation(operand1, operand2, c, error, errorMsg);

            if (error)
            {
                break;
            }

            // Push the result back onto the stack
            myStack.push(result);
        }
    }

    // Display result or error
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

        // Check if result is an integer to display appropriately
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

int main()
{
    std::string expression;

    // Main loop - continue until EOF
    while (true)
    {
        std::cout << "Please enter an expression in post-fix notation: ";

        // Read the expression
        if (!std::getline(std::cin, expression))
        {
            // EOF detected
            break;
        }

        // Skip empty lines
        if (expression.empty())
        {
            continue;
        }

        // Check if user typed "end-of-file" or "end of file"
        if (expression == "end-of-file" || expression == "end of file")
        {
            break;
        }

        // Evaluate the postfix expression
        evaluatePostfix(expression);
    }

    return 0;
}