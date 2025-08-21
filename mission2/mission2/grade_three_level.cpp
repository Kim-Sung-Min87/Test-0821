#include "grade_three_level.h"

using std::string;

string gradeString[3] = { "NORMAL", "GOLD", "SILVER" };

string GradeThreeLevel::getGradeString(int point)
{
	return gradeString[getGrade(point)];
}

bool GradeThreeLevel::isCandidateForElimination(int point)
{
	if (point < SILVER_POINT) return true;

	return false;
}

int GradeThreeLevel::getGrade(int point)
{
	if (point >= GOLD_POINT) return GOLD_GRADE;
	else if (point >= SILVER_POINT) return SILVER_GRADE;
	else return NORMAL_GRADE;
}
