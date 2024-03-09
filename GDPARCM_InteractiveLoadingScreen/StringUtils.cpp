#include "StringUtils.h"

std::vector<std::string> StringUtils::split(const std::string& s, char delimiter)
{
	// Splits string according to delimiter and returns string

	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while(std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}

	return tokens;
}
