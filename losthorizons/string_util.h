// String Utility
// Has some functions you can use when dealing with strings
#pragma once

#include <string>

std::string StringFrom(double value);
std::string StringFrom(signed value);
std::string StringFrom(unsigned value);
std::string StringFrom(bool value);

std::string StripSpaces(const std::string &str);
std::string StripQuotes(const std::string& s);

bool validNumber(const std::string &str);

template <typename T>
void convert(const std::string &str, T *const output);

bool TryParse(const std::string &str, double *const output);
bool TryParse(const std::string &str, float *const output);
bool TryParse(const std::string &str, signed *const output);
bool TryParse(const std::string &str, unsigned *const output);
bool TryParse(const std::string &str, bool *const output);
