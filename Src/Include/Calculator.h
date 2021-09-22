#pragma once
#include <iostream>
#include <string>
#include <math.h>
//#include <ctype.h>
#include <sstream>
#include "Include\Stack.h"

class Calculator {
public:
	Calculator();
	bool setExpression(std::string& userExpression);
	double evaluate();
	const std::string& postfix() const;

protected:
	std::string infixExpression, postfixExpression;
	Stack<char> expressionStack;
	Stack<double> evaluationStack;

protected:
	bool validate(const std::string& expression, std::string& errorMessage);
	void convertInfixToPostfix();
	bool isOperator(char c) const;
	bool isOperator(const std::string& s) const;
	size_t outStackPrecedence(char c) const;
	size_t inStackPrecedence(char c) const;
	double solve(double x, char op, double y) const;
};