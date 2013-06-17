// IniFile
// Based on ini_file by Henrik Rydgard
#pragma once

#include <string>
#include <sstream>

std::string StringFromInt(int value)
{
	std::stringstream format;
	format << value;
	return format.str();
}

std::string StringFromBool(bool value)
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

class IniFile
{




};
