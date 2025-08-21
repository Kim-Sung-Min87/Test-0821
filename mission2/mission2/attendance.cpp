#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "attendance.h"

using namespace std;

struct AttendanceData {
	string name;
	Weekday weekday;
};

map<string, int> registerBackNumber;
int uniqueBackNumber = 0;

int points[MAX_PLAYERS];
int grade[MAX_PLAYERS];
string names[MAX_PLAYERS];

int countTraining[MAX_PLAYERS];
int countWeekendAttendance[MAX_PLAYERS];

string gradeString[3] = { "NORMAL", "GOLD", "SILVER" };

void readAttendanceDataFromFileAndRegisterAttendanceData();
Weekday changeWeekdayStringToEnum(const string& weekday);
void registerAttendanceData(const AttendanceData& inputData);
int getPlayerBackNumber(const string& name);
void increaseAttendancePoint(int playerBackNumber);
void checkTraining(int playerBackNumber, const AttendanceData& inputData);
void checkWeekendAttendance(int playerBackNumber, const AttendanceData& inputData);
bool isWeekend(const AttendanceData& inputData);
void checkBonusPoint();
void checkGrade();
void printPlayerAttendanceResult();
void printCandidateForElimination();
bool isCandidateForElimination(int playerBackNumber);


void logic() {

	readAttendanceDataFromFileAndRegisterAttendanceData();

	checkBonusPoint();
	checkGrade();

	printPlayerAttendanceResult();
	printCandidateForElimination();
}

void readAttendanceDataFromFileAndRegisterAttendanceData()
{
	ifstream fin{ "attendance_weekday_500.txt" }; //500개 데이터 입력
	for (int inputNum = 0; inputNum < MAX_INPUT_NUM; inputNum++) {
		AttendanceData inputData;
		string weekday;
		fin >> inputData.name >> weekday;

		inputData.weekday = changeWeekdayStringToEnum(weekday);
		registerAttendanceData(inputData);
	}
}

Weekday changeWeekdayStringToEnum(const string& weekday)
{
	if (weekday == "monday") return MONDAY;
	else if (weekday == "tuesday") return TUESDAY;
	else if (weekday == "wednesday") return WEDNESDAY;
	else if (weekday == "thursday") return THURSDAY;
	else if (weekday == "friday") return FRIDAY;
	else if (weekday == "saturday") return SATURDAY;
	else if (weekday == "sunday") return SUNDAY;
}

void registerAttendanceData(const AttendanceData& inputData) {

	int playerBackNumber = getPlayerBackNumber(inputData.name);

	increaseAttendancePoint(playerBackNumber);

	checkTraining(playerBackNumber, inputData);
	checkWeekendAttendance(playerBackNumber, inputData);
}

int getPlayerBackNumber(const string& name)
{
	if (registerBackNumber.count(name) == 0) {
		registerBackNumber.insert({ name, ++uniqueBackNumber });

		names[uniqueBackNumber] = name;
	}
	return registerBackNumber[name];
}

void increaseAttendancePoint(int playerBackNumber)
{
	++points[playerBackNumber];
}

void checkTraining(int playerBackNumber, const AttendanceData& inputData)
{
	if (inputData.weekday != WEDNESDAY) return;

	points[playerBackNumber] += 2;
	++countTraining[playerBackNumber];
}

void checkWeekendAttendance(int playerBackNumber, const AttendanceData& inputData)
{
	if (isWeekend(inputData) == false) return;

	++points[playerBackNumber];
	++countWeekendAttendance[playerBackNumber];
}

bool isWeekend(const AttendanceData& inputData)
{
	return inputData.weekday == SATURDAY || inputData.weekday == SUNDAY;
}

void checkBonusPoint()
{
	for (int playerBackNumber = 1; playerBackNumber <= uniqueBackNumber; playerBackNumber++) {
		if (countTraining[playerBackNumber] >= BONUS_TRAINING_COUNT) {
			points[playerBackNumber] += BONUS_POINT;
		}

		if (countWeekendAttendance[playerBackNumber] >= BONUS_WEEKEND_COUNT) {
			points[playerBackNumber] += BONUS_POINT;
		}
	}
}

void checkGrade()
{
	for (int playerBackNumber = 1; playerBackNumber <= uniqueBackNumber; playerBackNumber++) {

		if (points[playerBackNumber] >= GOLD_POINT) {
			grade[playerBackNumber] = GOLD_GRADE;
		}
		else if (points[playerBackNumber] >= SILVER_POINT) {
			grade[playerBackNumber] = SILVER_GRADE;
		}
		else {
			grade[playerBackNumber] = NORMAL_GRADE;
		}
	}
}

void printPlayerAttendanceResult()
{
	for (int playerBackNumber = 1; playerBackNumber <= uniqueBackNumber; playerBackNumber++) {

		cout << "NAME : " << names[playerBackNumber] << ", ";
		cout << "POINT : " << points[playerBackNumber] << ", ";
		cout << "GRADE : " << gradeString[grade[playerBackNumber]] << "\n";
	}
}

void printCandidateForElimination()
{
	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int playerBackNumber = 1; playerBackNumber <= uniqueBackNumber; playerBackNumber++) {

		if (isCandidateForElimination(playerBackNumber)) {
			std::cout << names[playerBackNumber] << "\n";
		}
	}
}

bool isCandidateForElimination(int playerBackNumber)
{
	return grade[playerBackNumber] != GOLD_GRADE && grade[playerBackNumber] != SILVER_GRADE && countTraining[playerBackNumber] == 0 && countWeekendAttendance[playerBackNumber] == 0;
}

