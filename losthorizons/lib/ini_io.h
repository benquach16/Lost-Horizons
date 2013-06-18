// IniFile
// Based on ini_file by Henrik Rydgard
#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#ifdef _WIN32
	// Function Cross-Compatibility
#define strcasecmp _stricmp
#endif

std::string StringFromInt(int value)
{
	std::stringstream format;
	format << value;
	return format.str();
}
std::string StringFromInt(unsigned value) { return StringFromInt(static_cast<int>(value)); }

std::string StringFromDouble(double value)
{
	std::string temp = StringFromInt(static_cast<int>(value)) + '.';
	value -= static_cast<int>(value);
	while (value / 1 != static_cast<int>(value)) {
		value *= 10;
	}
	return temp + StringFromInt(static_cast<int>(value));
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
		FirstCommentChar =
			(int)line.find("#", FirstEquals > 0 ? FirstEquals : 0);
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

bool numbersOnly(const std::string &str)
{
	for (unsigned i = 0; i < str.size(); ++i) {

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

// Support bool, unsigned, int, double, char, and string
class IniFile
{
public:
	class Section
	{
		friend class IniFile;

	public:
		Section() {}
		Section(const std::string& name) : name_(name) {}

		bool Exists(const char *key) const;
		bool Delete(const char *key);

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
		// stuff

		bool operator < (const Section& other) const {
			return name_ < other.name_;
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

	bool Exists(const char* sectionName, const char* key) const;
	// stuff

	void SetLines(const char* sectionName, const std::vector<std::string> &lines);
	bool GetLines(const char* sectionName, std::vector<std::string>& lines, const bool remove_comments = true) const;

	bool DeleteKey(const char* sectionName, const char* key)
	{
		Section* section = GetSection(sectionName);
		if (!section)
			return false;
		std::string* line = section->GetLine(key, 0, 0);
		for (std::vector<std::string>::iterator liter = section->lines.begin(); liter != section->lines.end(); ++liter)
		{
			if (line == &(*liter))
			{
				section->lines.erase(liter);
				return true;
			}
		}
		return false; //shouldn't happen
	}
	bool DeleteSection(const char* sectionName)
	{
		Section* s = GetSection(sectionName);
		if (!s)
			return false;
		for (std::vector<Section>::iterator iter = sections.begin(); iter != sections.end(); ++iter)
		{
			if (&(*iter) == s)
			{
				sections.erase(iter);
				return true;
			}
		}
		return false;
	}

	void SortSections();
	const std::vector<Section> &Sections() { return sections; }

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
	std::string* GetLine(const char* section, const char* key);
	void CreateSection(const char* section);
};
