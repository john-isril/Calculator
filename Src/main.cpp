#include <iostream>
#include <string>
#include "Include\Calculator.h"

int main() {
	Calculator calculator;
	std::string userExpression;
	double answer{};

	while (true) {
		std::cout << "Enter an expression: ";
		std::getline(std::cin, userExpression);

		bool expressionSet = calculator.setExpression(userExpression);

		if (expressionSet) {
			try {
				answer = calculator.evaluate();
			}
			catch (std::runtime_error& ex) {
				std::cout << ex.what() << std::endl << std::endl;
				continue;
			}
			std::cout << "Result: " << calculator.evaluate() << std::endl << std::endl;
		}
	}
}