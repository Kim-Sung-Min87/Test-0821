#include "player_data.h"

void PlayerData::registerAttendanceData(const Weekday& weekday) {

	increaseAttendancePoint();
	checkTraining(weekday);
	checkWeekendAttendance(weekday);
}

void PlayerData::checkBonusPoint()
{
	if (_countTraining >= BONUS_TRAINING_COUNT) {
		_point += BONUS_POINT;
	}

	if (_countWeekendAttendance >= BONUS_WEEKEND_COUNT) {
		_point += BONUS_POINT;
	}
}

bool PlayerData::isCandidateForElimination() {
	return _grade->isCandidateForElimination(_point) && _countTraining == 0 && _countWeekendAttendance == 0;
}

void PlayerData::increaseAttendancePoint()
{
	++_point;
}

void PlayerData::checkTraining(const Weekday& weekday)
{
	if (weekday != WEDNESDAY) return;

	_point += 2;
	++_countTraining;
}

void PlayerData::checkWeekendAttendance(const Weekday& weekday)
{
	if (isWeekend(weekday) == false) return;

	++_point;
	++_countWeekendAttendance;
}

bool PlayerData::isWeekend(const Weekday& weekday)
{
	return weekday == SATURDAY || weekday == SUNDAY;
}
