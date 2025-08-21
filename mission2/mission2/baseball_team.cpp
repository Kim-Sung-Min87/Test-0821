#include "baseball_team.h"
#include <iostream>
#include "player_data.h"

using std::string;
using std::cout;

PlayerData* BaseballTeam::getPlayer(const string& name)
{
	if (_registerPlayers.count(name) == 0) {

		PlayerData * newPlayer = new PlayerData(name);
		_registerPlayers.insert({ name, newPlayer });

		_players.push_back(newPlayer);
	}
    return _registerPlayers[name];
}

void BaseballTeam::printPlayers() {
	for (const auto& player : _players) {
		cout << player->getPlayerResult();
	}
}

void BaseballTeam::printCandidateForElimination() {

	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";

	for (const auto& player : _players) {
		if (player->isCandidateForElimination()) {
			std::cout << player->getName() << "\n";
		}
	}
}

void BaseballTeam::checkBonusPointForAllPlayers() {
	for (auto& player : _players) {
		player->checkBonusPoint();
	}
}
