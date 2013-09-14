#ifndef _OFFICER_H_
#define _OFFICER_H_

#include <string>

enum E_OFFICER_TYPES
{
	E_OFFICER_HELMSMAN,
	E_OFFICER_FIRECONTROL,
	E_OFFICER_ENGINEERING,
	E_OFFICER_NAVIGATION,
};

//the player is allowed to hire officers, with each officer having different roles
class Officer
{
public:
	Officer(const std::wstring &officerName, const E_OFFICER_TYPES officerType);
	~Officer();

protected:
	std::wstring officerName;
	unsigned currentExperience;
	unsigned experienceToLevel;
	E_OFFICER_TYPES officerType;
};

#endif
