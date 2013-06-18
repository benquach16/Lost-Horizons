// IniFile
// Based on ini_file by Henrik Rydgard
#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
	// Function Cross-Compatibility
#define strcasecmp _stricmp
#endif

std::string StringFromBool(bool value)
{
	return value ? "True" : "False";
}

std::string StringFromInt(int value)
{
	std::stringstream convert;
	convert << value;
	return convert.str();
}

std::string StringFromDouble(double value)
{
	std::string temp = StringFromInt(static_cast<int>(value)) + '.';
	value -= static_cast<int>(value);
	while (value / 1 != static_cast<int>(value)) {
		value *= 10;
	}
	return temp + StringFromInt(static_cast<int>(value));
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

static bool ParseLine(const std::string& line, std::string* keyOut, std::string* valueOut, std::string* commentOut)
{
	int FirstEquals = (int)line.find("=", 0);
	int FirstCommentChar = -1;

	// Comments
	if (FirstCommentChar < 0)
		FirstCommentChar = (int)line.find("#", FirstEquals > 0 ? FirstEquals : 0);
	if (FirstCommentChar < 0 && line[0] == ';')
		FirstCommentChar = 0;

	// Allow preservation of spacing before comment
	if (FirstCommentChar > 0)
	{
		while (line[FirstCommentChar - 1] == ' ' || line[FirstCommentChar - 1] == 9) // 9 == tab
		{
			FirstCommentChar--;
		}
	}

	if ((FirstEquals >= 0) && ((FirstCommentChar < 0) || (FirstEquals < FirstCommentChar)))
	{
		// Yes, a valid key/value line!
		*keyOut = StripSpaces(line.substr(0, FirstEquals));
		if (commentOut) *commentOut = FirstCommentChar > 0 ? line.substr(FirstCommentChar) : std::string("");
		if (valueOut) *valueOut = StripQuotes(StripSpaces(line.substr(FirstEquals + 1, FirstCommentChar - FirstEquals - 1)));
		return true;
	}
	return false;
}

bool validNumber(const std::string &str)
{
	if (str.find_first_of('.') != str.find_last_of('.') || str.find_last_of('-') > 0 || str.find_last_of('+') > 0)
		return false;
	if (str[0] != '.' && str[0] != '-' && str[0] != '+' && !(str[0] > '0' && str[0] < '9'))
		return false;
	for (unsigned i = 1; i < str.size(); ++i) {
		if (str[i] != '.' && !(str[i] > '0' && str[i] < '9'))
			return false;
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

bool TryParse(const std::string &str, int *const output)
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
	if (validNumber(str) && str.find('.') == -1 && str.find('-') == -1) {
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

// Supports bool, unsigned, int, double, and string
class IniFile
{
public:
	class Section
	{
		friend class IniFile;

	public:
		Section() {}
		Section(const std::string& name) : name_(name) {}

		std::string* GetLine(const char* key, std::string* valueOut, std::string* commentOut)
		{
			for (std::vector<std::string>::iterator iter = lines.begin(); iter != lines.end(); ++iter)
			{
				std::string& line = *iter;
				std::string lineKey;
				ParseLine(line, &lineKey, valueOut, commentOut);
				if (!strcasecmp(lineKey.c_str(), key))
					return &line;
			}
			return 0;
		}
		void Set(const char* key, const char* newValue)
		{
			std::string value, commented;
			std::string* line = GetLine(key, &value, &commented);
			if (line)
			{
				// Change the value - keep the key and comment
				*line = StripSpaces(key) + " = " + newValue + commented;
			}
			else
			{
				// The key did not already exist in this section - let's add it.
				lines.push_back(std::string(key) + " = " + newValue);
			}
		}

		void Set(const std::string &key, const std::string &value) {
			Set(key.c_str(), value.c_str());
		}
		bool Get(const char* key, std::string* value, const char* defaultValue)
		{
			std::string* line = GetLine(key, value, 0);
			if (!line)
			{
				if (defaultValue)
				{
					*value = defaultValue;
				}
				return false;
			}
			return true;
		}

		void Set(const char* key, double newValue) {
			Set(key, StringFromDouble(newValue).c_str());
		}
		bool Get(const char* key, double* value, double defaultValue = false)
		{
			std::string temp;
			bool retval = Get(key, &temp, 0);
			if (retval && TryParse(temp.c_str(), value))
				return true;
			*value = defaultValue;
			return false;
		}

		void Set(const char* key, int newValue) {
			Set(key, StringFromInt(newValue).c_str());
		}
		bool Get(const char* key, int* value, int defaultValue = 0)
		{
			std::string temp;
			bool retval = Get(key, &temp, 0);
			if (retval && TryParse(temp.c_str(), value))
				return true;
			*value = defaultValue;
			return false;
		}

		void Set(const char* key, unsigned newValue) {
			Set(key, StringFromInt(newValue).c_str());
		}
		bool Get(const char* key, unsigned* value, unsigned defaultValue = 0)
		{
			std::string temp;
			bool retval = Get(key, &temp, 0);
			if (retval && TryParse(temp.c_str(), value))
				return true;
			*value = defaultValue;
			return false;
		}

		void Set(const char* key, bool newValue) {
			Set(key, StringFromBool(newValue).c_str());
		}
		bool Get(const char* key, bool* value, bool defaultValue = false)
		{
			std::string temp;
			bool retval = Get(key, &temp, 0);
			if (retval && TryParse(temp.c_str(), value))
				return true;
			*value = defaultValue;
			return false;
		}

		const std::string &name() const {
			return name_;
		}

	protected:
		std::vector<std::string> lines;
		std::string name_;
		std::string comment;
	};

	// ini file load functions
	bool Load(std::istream &in) {
		// Maximum number of letters in a line
		static const int MAX_BYTES = 1024*32;

		while (!in.eof())
		{
			char templine[MAX_BYTES];
			in.getline(templine, MAX_BYTES);
			std::string line = templine;

			// Remove UTF-8 byte order marks.
			if (line.substr(0, 3) == "\xEF\xBB\xBF")
				line = line.substr(3);
		 
			// Check for CRLF eol and convert it to LF
			if (!line.empty() && line.at(line.size()-1) == '\r')
			{
				line.erase(line.size()-1);
			}

			if (in.eof()) break;

			if (line.size() > 0)
			{
				if (line[0] == '[')
				{
					size_t endpos = line.find("]");

					if (endpos != std::string::npos)
					{
						// New section!
						std::string sub = line.substr(1, endpos - 1);
						sections.push_back(Section(sub));

						if (endpos + 1 < line.size())
						{
							sections[sections.size() - 1].comment = line.substr(endpos + 1);
						}
					}
				}
				else
				{
					if (sections.size() > 0)
						sections[sections.size() - 1].lines.push_back(line);
				}
			}
		}

		return true;
	}
	bool Load(const char* filename)
	{
		sections.clear();
		sections.push_back(Section(""));
		// first section consists of the comments before the first real section

		// Open file
		std::ifstream in;
		in.open(filename, std::ios::in);

		if (in.fail()) return false;

		bool success = Load(in);
		in.close();
		return success;
	}
	bool Load(const std::string &filename) { return Load(filename.c_str()); }

	// ini file save functions
	bool Save(const char* filename)
	{
		std::ofstream out;
		out.open(filename, std::ios::out);

		if (out.fail())
		{
			return false;
		}

		// UTF-8 byte order mark. To make sure notepad doesn't go nuts.
		out << "\xEF\xBB\xBF";

		// Currently testing if dolphin community can handle the requirements of C++11 compilation
		// If you get a compiler error on this line, your compiler is probably old.
		// Update to g++ 4.4 or a recent version of clang (XCode 4.2 on OS X).
		// If you don't want to update, complain in a google code issue, the dolphin forums or #dolphin-emu.
		for (std::vector<Section>::iterator iter = sections.begin(); iter != sections.end(); ++iter)
		{
			const Section& section = *iter;

			if (section.name() != "")
			{
				out << "[" << section.name() << "]" << section.comment << std::endl;
			}

			for (std::vector<std::string>::const_iterator liter = section.lines.begin(); liter != section.lines.end(); ++liter)
			{
				std::string s = *liter;
				out << s << std::endl;
			}
		}

		out.close();
		return true;
	}
	bool Save(const std::string &filename) { return Save(filename.c_str()); }

	Section* GetOrCreateSection(const char* sectionName)
	{
		Section* section = GetSection(sectionName);
		if (!section)
		{
			sections.push_back(Section(sectionName));
			section = &sections[sections.size() - 1];
		}
		return section;
	}

private:
	std::vector<Section> sections;

	const Section* GetSection(const char* sectionName) const
	{
		for (std::vector<Section>::const_iterator iter = sections.begin(); iter != sections.end(); ++iter)
			if (!strcasecmp(iter->name().c_str(), sectionName))
				return (&(*iter));
		return 0;
	}
	Section* GetSection(const char* sectionName)
	{
		for (std::vector<Section>::iterator iter = sections.begin(); iter != sections.end(); ++iter)
			if (!strcasecmp(iter->name().c_str(), sectionName))
				return (&(*iter));
		return 0;
	}
};
