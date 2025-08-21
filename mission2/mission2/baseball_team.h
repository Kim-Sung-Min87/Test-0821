#pragma once
#include <vector>
#include <map>
#include <string>

#include "player_data.h"

class BaseballTeam
{
public:
	PlayerData* getPlayer(const std::string& name);

	void printPlayers();
	void printCandidateForElimination();

	void checkBonusPointForAllPlayers();

	int getPlayerCount() { return _players.size(); }

private:
	std::map<std::string, PlayerData*> _registerPlayers;
	std::vector<PlayerData*> _players;
};

