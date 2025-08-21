#pragma once
#include <string>
#include "player_data.h"
#include "grade_three_level.h"

class IPlayerFactory
{
public:
	virtual PlayerData* createPlayer(const std::string& name) = 0;
};

class PlayerGradeThreeLevelFactory : public IPlayerFactory
{
public:
	static PlayerGradeThreeLevelFactory& getInstance() {
		static PlayerGradeThreeLevelFactory instance;
		return instance;
	}

	PlayerData* createPlayer(const std::string& name) override {
		return new PlayerData(name, new GradeThreeLevel());
	}

private:
	PlayerGradeThreeLevelFactory() {}
};

