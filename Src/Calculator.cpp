#include "Include\Calculator.h"

Calculator::Calculator()
	: infixExpression{}, postfixExpression{}, expressionStack{}, evaluationStack{} {}

bool Calculator::setExpression(std::string& userExpression) {
	std::string errorMessage{};

	infixExpression.clear();
	bool valid = validate(userExpression, errorMessage);

	if (!valid) {
		std::cout << errorMessage << std::endl << std::endl;
		
		return false;
	}

	convertInfixToPostfix();
	return true;
}

bool Calculator::validate(const std::string& expression, std::string& errorMessage) {
	// If the expression starts with a '+', '/', or '*', it is invalid and should return false. 
	// If the expression starts with a '-', '+', '/', '*', or decimal point, it is invalid and should return false. 
	if ((isOperator(expression[0]) && expression[0] != '-') || isOperator(expression[expression.length() - 1]) || expression[expression.length() - 1] == '.') {
		errorMessage = "Error: missing operand(s)";
		return false;
	}

	for (size_t i{ 0 }; i < expression.length(); i++) {
		// Checks that operators have operands on both sides, unless its a '-' because '-' can be for negation.
		if (i > 0 && isOperator(expression[i]) && expression[i] != '-' && isOperator(infixExpression.back())) {
			errorMessage = "Error: missing operand(s)";
			return false;
		}
		// Checks if a decimal point has numbers on both sides. Won't accept an operand like 7. , but will accept .7 and evaluates it to be 0.7.
		else if (i < (expression.length() - 1) && expression[i] == '.' && !std::isdigit(expression[i + 1])) {
			errorMessage = "Error: needs a number on both sides of the '.'";
			return false;
		}
		// Handles double negatives and evaluates them to be a '+'. (ex: 5--5 == 5+5)
		else if (i > 0 && (i < expression.length() - 1) && expression[i] == '-' && expression[i + 1] == '-') {
			if (infixExpression.back() == '+') {

			}
			else if (isOperator(infixExpression.back())){
				errorMessage = "Error: missing operand(s)";
				return false;
			}
			else {
				infixExpression += '+';
			}
			i++;
		}
		else if (expression[i] == ' ') {
			continue;
		}
		// Checks if parenthesis are properly balanced.
		else if (expression[i] == '(') {
			expressionStack.push(expression[i]);
		}
		else if (expression[i] == ')') {
			if (expressionStack.isEmpty()) {
				expressionStack.clear();
				errorMessage = "Error: missing '('";
				return false;
			}
			else {
				expressionStack.pop();
			}
		}
		else if (std::isdigit(expression[i]) || isOperator(expression[i]) || expression[i] == '.') {
			infixExpression += expression[i];
		}
		else {
			expressionStack.clear();
			errorMessage = "Error: invalid symbol(s)";
			return false;
		}
	}

	if (!expressionStack.isEmpty()) {
		expressionStack.clear();
		errorMessage = "Error: missing ')'";
		return false;
	}

	expressionStack.clear();
	return true;
}

void Calculator::convertInfixToPostfix() {
	postfixExpression.clear();
	postfixExpression += infixExpression[0];

	for (size_t i{ 1 }; i < infixExpression.size(); i++) {
		if ((infixExpression[i] == '-' && isOperator(infixExpression[i - 1])) || infixExpression[i] == '.' || std::isdigit(infixExpression[i])) {
			postfixExpression += infixExpression[i];
		}
		else if (infixExpression[i] == ')' && expressionStack.top() == '(') {
			expressionStack.pop();
		}
		else if (expressionStack.isEmpty() || (outStackPrecedence(infixExpression[i]) > inStackPrecedence(expressionStack.top()))) {
			expressionStack.push(infixExpression[i]);
			postfixExpression += ' ';
		}
		else {
			postfixExpression += ' ';
			postfixExpression += expressionStack.pop();
			i--;
		}
	}

	while (!expressionStack.isEmpty()) {
		postfixExpression += ' ';
		postfixExpression += expressionStack.pop();
	}

	expressionStack.clear();
}

double Calculator::evaluate() {
	// Extracts operands and operators and strings, then evaluates the postfix expression using a stack.
	std::istringstream iss{ postfixExpression };
	std::string s;
	double leftOperand{};
	double rightOperand{};
	double answer{};

	while (iss >> s) {
		if (!isOperator(s)) {
			evaluationStack.push(std::stod(s));
		}
		else {
			rightOperand = evaluationStack.pop();
			leftOperand = evaluationStack.pop();
			answer = solve(leftOperand, s[0], rightOperand);
			evaluationStack.push(answer);
		}
	}

	return evaluationStack.pop();
}

const std::string& Calculator::postfix() const {
	return postfixExpression;
}

bool Calculator::isOperator(char c) const {
	if (c == '^' || c == '*' || c == '/' || c == '+' || c == '-') {
		return true;
	}

	return false;
}

bool Calculator::isOperator(const std::string& s) const {
	if (s == "^" || s == "*" || s == "/" || s == "+" || s == "-") {
		return true;
	}

	return false;
}

size_t Calculator::inStackPrecedence(char c) const {
	if (c == '(') {
		return 0;
	}
	else if (c == '^') {
		return 5;
	}
	else if (c == '*' || c == '/') {
		return 4;
	}
	else if (c == '+' || c == '-') {
		return 2;
	}
	else {
		return 0;
	}
}

size_t Calculator::outStackPrecedence(char c) const {
	if (c == '(') {
		return 7;
	}
	else if (c == '^') {
		return 6;
	}
	else if (c == '*' || c == '/') {
		return 3;
	}
	else if (c == '+' || c == '-') {
		return 1;
	}
	else {
		return 0;
	}
}

double Calculator::solve(double x, char op, double y) const {
	if (op == '/' && y == 0) {
		throw std::runtime_error("Error: division by zero");
	}

	if (x == 0 || y == 0) {
		return 0;
	}

	if (op == '*') {
		return x * y;
	}
	else if (op == '/') {
		return x / y;
	}
	else if (op == '+') {
		return x + y;
	}
	else if (op == '-') {
		return x - y;
	}
	else if (op == '^') {
		return pow(x, y);
	}
	else {
		return 0.0;
	}
}