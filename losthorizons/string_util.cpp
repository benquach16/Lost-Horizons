// String Utility
// Has some functions you can use when dealing with strings

#include "stdafx.h"
#include "string_util.h"
#include <sstream>

#ifdef _WIN32
	// Function Cross-Compatibility
#define strcasecmp _stricmp
#endif

std::string StringFrom(double value)
{
	std::stringstream convert;
	convert << value;
	return convert.str();
}

std::string StringFrom(signed value)
{
	std::stringstream convert;
	convert << value;
	return convert.str();
}

std::string StringFrom(unsigned value)
{
	std::stringstream convert;
	convert << value;
	return convert.str();
}

std::string StringFrom(bool value)
{
	return value ? "True" : "False";
}

std::string StripSpaces(const std::string &str)
{
	const size_t s = str.find_first_not_of(" \t\r\n");

	if (str.npos != s)
		return str.substr(s, str.find_last_not_of(" \t\r\n") - s + 1);
	else
		return "";
}

std::string StripQuotes(const std::string& s)
{
	if (s.size() && '\"' == s[0] && '\"' == *s.rbegin())
		return s.substr(1, s.size() - 2);
	else
		return s;
}

bool validNumber(const std::string &str)
{
	if (str[0] != '.' && str[0] != '-' && str[0] != '+' && !(str[0] >= '0' && str[0] <= '9'))
		return false;
	bool decimal(false);
	for (unsigned i = 1; i < str.size(); ++i) {
		if (str[i] != '.' && !(str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '+')
			return false;
		if (str[i] == '.') {
			if (decimal)
				return false;
			else
				decimal = true;
		}
	}
	return true;
}

template <typename T>
void convert(const std::string &str, T *const output)
{
	std::stringstream convert;
	convert << str;
	convert >> *output;
}

bool TryParse(const std::string &str, double *const output)
{
	if (validNumber(str)) {
		convert(str, output);
		return true;
	} else {
		return false;
	}
}

bool TryParse(const std::string &str, signed *const output)
{
	if (validNumber(str) && str.find('.') == -1) {
		convert(str, output);
		return true;
	} else {
		return false;
	}
}

bool TryParse(const std::string &str, unsigned *const output)
{
	if (validNumber(str) && str.find(".-") == -1) {
		convert(str, output);
		return true;
	} else {
		return false;
	}
}

bool TryParse(const std::string &str, bool *const output)
{
	if ("1" == str || !strcasecmp("true", str.c_str()))
		*output = true;
	else if ("0" == str || !strcasecmp("false", str.c_str()))
		*output = false;
	else
		return false;

	return true;
}
