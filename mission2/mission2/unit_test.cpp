#include "gmock/gmock.h"

#include <string>

#include "attendance.h"
#include "player_data.h"
#include "baseball_team.h"

#include <iostream>
#include <fstream>

using namespace std;

class AttendanceTestFixture : public ::testing::Test {
public:
	BaseballTeam team;
	PlayerData* player;
	PlayerData* player2;

	void registerAttendanceDataTenTimes(PlayerData* player, Weekday weekday) {
		for (int i = 0; i < 10; ++i) {
			player->registerAttendanceData(weekday);
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

protected:
	void SetUp() override {}
	void TearDown() override {}
};

TEST_F(AttendanceTestFixture, NonPlayer) {

	EXPECT_EQ(0, team.getPlayerCount());
}

TEST_F(AttendanceTestFixture, CreatePlayer) {

	player = team.getPlayer("Umar");

	EXPECT_EQ(1, team.getPlayerCount());
}

TEST_F(AttendanceTestFixture, CreatePlayerDuplication) {

	player = team.getPlayer("Umar");
	player2 = team.getPlayer("Umar");

	EXPECT_EQ(1, team.getPlayerCount());
}

TEST_F(AttendanceTestFixture, CreatePlayerOther) {

	player = team.getPlayer("Umar");
	player2 = team.getPlayer("Daisy");

	EXPECT_EQ(2, team.getPlayerCount());
}

TEST_F(AttendanceTestFixture, AttendanceWeekday) {

	player = team.getPlayer("Umar");

	player->registerAttendanceData(MONDAY);

	EXPECT_EQ(1, player->getPoint());
	EXPECT_EQ(0, player->getCountTraining());
	EXPECT_EQ(0, player->getCountWeekendAttendance());
}

TEST_F(AttendanceTestFixture, AttendanceWednesday) {

	player = team.getPlayer("Umar");

	player->registerAttendanceData(WEDNESDAY);

	EXPECT_EQ(3, player->getPoint());
	EXPECT_EQ(1, player->getCountTraining());
	EXPECT_EQ(0, player->getCountWeekendAttendance());
}

TEST_F(AttendanceTestFixture, AttendanceWeekend) {

	player = team.getPlayer("Umar");

	player->registerAttendanceData(SATURDAY);

	EXPECT_EQ(2, player->getPoint());
	EXPECT_EQ(0, player->getCountTraining());
	EXPECT_EQ(1, player->getCountWeekendAttendance());
}

TEST_F(AttendanceTestFixture, CheckBonusPointTraining) {

	player = team.getPlayer("Umar");

	registerAttendanceDataTenTimes(player, WEDNESDAY);
	player->checkBonusPoint();

	EXPECT_EQ(40, player->getPoint());
	EXPECT_EQ(10, player->getCountTraining());
	EXPECT_EQ(0, player->getCountWeekendAttendance());
}

TEST_F(AttendanceTestFixture, CheckBonusPointWeekend) {

	player = team.getPlayer("Umar");

	registerAttendanceDataTenTimes(player, SATURDAY);
	player->checkBonusPoint();

	EXPECT_EQ(30, player->getPoint());
	EXPECT_EQ(0, player->getCountTraining());
	EXPECT_EQ(10, player->getCountWeekendAttendance());
}

TEST_F(AttendanceTestFixture, CheckGradeGold) {

	player = team.getPlayer("Umar");

	registerAttendanceDataTenTimes(player, WEDNESDAY);
	registerAttendanceDataTenTimes(player, MONDAY);
	player->checkBonusPoint();

	EXPECT_EQ(50, player->getPoint());
	EXPECT_EQ(10, player->getCountTraining());
	EXPECT_EQ(0, player->getCountWeekendAttendance());
	EXPECT_EQ("GOLD", player->getGradeString());
}

TEST_F(AttendanceTestFixture, CheckGradeSilver) {

	player = team.getPlayer("Umar");

	registerAttendanceDataTenTimes(player, SATURDAY);
	player->checkBonusPoint();

	EXPECT_EQ(30, player->getPoint());
	EXPECT_EQ(0, player->getCountTraining());
	EXPECT_EQ(10, player->getCountWeekendAttendance());
	EXPECT_EQ("SILVER", player->getGradeString());
}

TEST_F(AttendanceTestFixture, CheckGradeNormal) {

	player = team.getPlayer("Umar");

	registerAttendanceDataTenTimes(player, MONDAY);
	player->checkBonusPoint();

	EXPECT_EQ(10, player->getPoint());
	EXPECT_EQ(0, player->getCountTraining());
	EXPECT_EQ(0, player->getCountWeekendAttendance());
	EXPECT_EQ("NORMAL", player->getGradeString());
}

TEST_F(AttendanceTestFixture, CheckCandidateForEliminationTrue) {

	player = team.getPlayer("Umar");

	registerAttendanceDataTenTimes(player, MONDAY);
	player->checkBonusPoint();

	EXPECT_EQ(10, player->getPoint());
	EXPECT_EQ(0, player->getCountTraining());
	EXPECT_EQ(0, player->getCountWeekendAttendance());
	EXPECT_EQ(true, player->isCandidateForElimination());
}

TEST_F(AttendanceTestFixture, CheckCandidateForEliminationFalse) {

	player = team.getPlayer("Umar");

	registerAttendanceDataTenTimes(player, SATURDAY);
	player->checkBonusPoint();

	EXPECT_EQ(30, player->getPoint());
	EXPECT_EQ(0, player->getCountTraining());
	EXPECT_EQ(10, player->getCountWeekendAttendance());
	EXPECT_EQ(false, player->isCandidateForElimination());
}

TEST_F(AttendanceTestFixture, PrintPlayerData) {

	player = team.getPlayer("Umar");

	registerAttendanceDataTenTimes(player, SATURDAY);
	player->checkBonusPoint();

	EXPECT_EQ(30, player->getPoint());
	EXPECT_EQ(0, player->getCountTraining());
	EXPECT_EQ(10, player->getCountWeekendAttendance());
	EXPECT_EQ("NAME : Umar, POINT : 30, GRADE : SILVER\n", player->getPlayerResult());
}

TEST_F(AttendanceTestFixture, TestFromFile) {

	ifstream fin{ "attendance_weekday_500.txt" }; //500개 데이터 입력
	for (int inputNum = 0; inputNum < MAX_INPUT_NUM; inputNum++) {
		string name;
		string weekday;
		fin >> name >> weekday;

		player = team.getPlayer(name);
		player->registerAttendanceData(changeWeekdayStringToEnum(weekday));
	}

	team.checkBonusPointForAllPlayers();
	team.printPlayers();
	team.printCandidateForElimination();
}



