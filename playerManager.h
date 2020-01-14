
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "player.h"

using namespace std;

class playerManager
{
public:
	vector<Player> players;

	void generatePlayers(int n) {
		vector<string> names = {
			"Atsushi", "Daiki", "Hotaru", "Yuki", "Kosuke", "Tomo", "Ryota", "Haru", "Yamato", "Yuta", "Kai"
		};
		srand((unsigned)time(NULL));
		for (int i = 0; i < n; i++) {
			int idx = rand() % names.size();
			Player player = Player(names[idx], 1000, i + 1);
			players.push_back(player);
		}
	}

	void sortPlayersById() {
		for (size_t i = 0; i < players.size() - 1; i++)
		{
			for (size_t j = 0; j < players.size() - i - 1; j++)
			{
				if (players[j].getID() > players[j + 1].getID()) swap(players[j], players[j + 1]);
			}
		}
	}

	void listOfPlayers() {
		sortPlayersById();
		cout << "==================================" << endl << endl;
		for (size_t i = 0; i < players.size(); i++) {
			cout << "Name: " << players[i].getName()
				<< "\tID: " << players[i].getID()
				<< "\tRank: " << players[i].getRank()
				<< endl << endl
				<< "=================================="
				<< endl << endl;
		}
	}

	Player getPlayerByName(string name) {
		for (size_t i = 0; i < players.size(); i++) {
			if (players[i].getName() == name) {
				return players[i];
			}
		}
	}

	Player getPlayerById(int id) {
		for (size_t i = 0; i < players.size(); i++) {
			if (players[i].getID() == id) {
				return players[i];
			}
		}
	}

	void removePlayer(int id) {
		for (size_t i = 0; i < players.size(); i++) {
			if (players[i].getID() == id) players.erase(players.begin() + i);
			break;
		}
	}

	void addPlayer(string name) {
		int id = players[players.size() - 1].getID() + 1;
		Player player = Player(name, 1000, id);
		players.push_back(player);
	}
};
