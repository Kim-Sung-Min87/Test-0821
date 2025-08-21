#pragma once
#include <string>

#include "attendance.h"
#include "grade_interface.h"

class GradeThreeLevel : public IGradeInterface
{
public:
	std::string getGradeString(int point) override;
	bool isCandidateForElimination(int point) override;

private:
	int getGrade(int point);
};

