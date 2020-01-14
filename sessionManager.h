
#pragma once
#include <vector>
#include <iostream>
#include "session.h"

class SessionManager
{
	vector <gameSession> sessions;
	time_t time = 0;

public:
	SessionManager() {}

	void listOfSessions() {
		for (size_t i = 0; i < sessions.size(); i++) {
			cout << i + 1 << ". ";
			sessions[i].showTime();
			int winner = sessions[i].getWinner();
			cout << sessions[i].arr[winner] << "Won " << endl;
		}
	}

	void performGameSession(vector <Player> & players, vector <Hero> & heroes, int num) {
		for (int i = 0; i < num; i++) {
			gameSession Session(players, heroes);
			Session.gameStart(players);
			Session.saveLog();
			Session.showTime();
			Session.showTeamBlue();
			Session.showTeamRed();
			sessions.push_back(session);
		}
	}
};