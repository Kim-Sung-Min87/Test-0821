#pragma once

#include "attendance.h"
#include <string>
#include "grade_three_level.h"
#include <iostream>

class IGradeInterface;

class PlayerData
{
public:
	PlayerData(const std::string& name)
		: _name(name), _point(0), _grade(new GradeThreeLevel()), _countTraining(0), _countWeekendAttendance(0) {}
	
	void registerAttendanceData(const Weekday& weekday);
	void checkBonusPoint();
	bool isCandidateForElimination();
	std::string getPlayerResult() {
		return "NAME : " + _name + ", "
			+ "POINT : " + std::to_string(_point) + ", "
			+ "GRADE : " + getGradeString() + "\n";
	}

	std::string getName() { return _name; }
	int getPoint() { return _point; }
	std::string getGradeString() { return _grade->getGradeString(_point); }
	int getCountTraining() { return _countTraining; }
	int getCountWeekendAttendance() { return _countWeekendAttendance; }

private:
	void increaseAttendancePoint();
	void checkTraining(const Weekday& weekday);
	void checkWeekendAttendance(const Weekday& weekday);
	bool isWeekend(const Weekday& weekday);


	std::string _name;

	int _point;
	IGradeInterface * _grade;

	int _countTraining;
	int _countWeekendAttendance;
};

