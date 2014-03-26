// IniFile
// A class for parsing ini files
#pragma once

#include <vector>

static bool ParseLine(const std::string& line, std::string* keyOut, std::string* valueOut, std::string* commentOut);

// Supports bool, unsigned, int, double, and string
class IniFile
{
public:
	class Section
	{
		friend class IniFile;

	public:
		Section();
		Section(const std::string& name);

		std::string* GetLine(const char* key, std::string* valueOut, std::string* commentOut);
		void Set(const char* key, const char* newValue);
		void Set(const std::string &key, const std::string &newValue);
		bool Get(const char* key, std::string* value, const char* defaultValue);

		void Set(const char* key, double newValue);
		void Set(const char* key, signed newValue);
		void Set(const char* key, unsigned newValue);
		void Set(const char* key, bool newValue);
		bool Get(const char* key, double* value, double defaultValue = false);
		bool Get(const char* key, signed* value, signed defaultValue = 0);
		bool Get(const char* key, unsigned* value, unsigned defaultValue = 0);
		bool Get(const char* key, bool* value, bool defaultValue = false);

		const std::string &name() const;

	protected:
		std::vector<std::string> lines;
		std::string name_;
		std::string comment;
	};

	// ini file load functions
	bool Load(std::istream &in);
	bool Load(const char* filename);
	bool Load(const std::string &filename);

	// ini file save functions
	bool Save(const char* filename);
	bool Save(const std::string &filename);

	Section* GetOrCreateSection(const char* sectionName);

private:
	std::vector<Section> sections;

	const Section* GetSection(const char* sectionName) const;
	Section* GetSection(const char* sectionName);
};
