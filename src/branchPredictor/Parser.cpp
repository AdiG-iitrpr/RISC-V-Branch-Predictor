#include "Parser.h"

std::vector<Instruction> Parser::parse(const std::string& input) {

	std::vector<Instruction> instructions;
	std::string currentToken;
	std::vector<std::string> tokens;

	for (std::size_t i = 0; i < input.length(); ++i) {
		char c = input[i];

		if (isWhitespace(c) || isDelimiter(c)) {

			if (!currentToken.empty()) {
				if (currentToken.length() >= 2 and currentToken.substr(0, 2) == "0x")
					tokens.push_back(currentToken);
				currentToken.clear();
			}

		} else if (isComment(c)) {
			while (i < input.length() && c != '\n' && c != '\r') {
				c = input[++i];
			}
		} else {
			currentToken += c;
		}

	}


	if (!currentToken.empty()) {
		if (currentToken.length() >= 2 and currentToken.substr(0, 2) == "0x")
			tokens.push_back(currentToken);
		currentToken.clear();
	}

	for (std::size_t i = 0; i < tokens.size(); i += 2)
		instructions.emplace_back(Instruction(tokens[i], tokens[i + 1]));


	return instructions;
}

bool Parser::isWhitespace(char c) {
	return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == ':';
}

bool Parser::isDelimiter(char c) {
	return c == ',' || c == '(' || c == ')';
}

bool Parser::isComment(char c) {
	return c == '#';
}