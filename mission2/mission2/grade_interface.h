#pragma once
#include <string>

class IGradeInterface
{
public:
	virtual std::string getGradeString(int point) = 0;
	virtual bool isCandidateForElimination(int point) = 0;
};
