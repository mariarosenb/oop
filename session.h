
#pragma once
#include "player.h"
#include "hero.h"
#include "teamPart.h"
#include <fstream>
#include <iostream>
#include<ctime>
#include<vector>
#include <stdio.h>
#include <windows.h>

using namespace std;

template <typename T>

void randVector(vector<T>& vec) {
	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < vec.size(); i++) {
		swap(vec[i], vec[rand() % vec.size()]);
	}
}
class gameSession {

	vector <TeamPart> Lobby;
	vector <TeamPart> TeamRed;
	vector <TeamPart> TeamBlue;
	vector <Hero> initHeroes;
	vector <TeamPart> TeamSave;

	time_t StartTime = 0;

	int winner = 999;
	void GameSet() {
		int hpBlue = 0, hpRed = 0, damageBlue = 0, damageRed = 0;
		for (size_t i = 0; i < TeamBlue.size(); i++) {
			hpBlue += TeamBlue[i].hero.getHP();
			damageBlue += TeamBlue[i].hero.getDamage();
		}
		for (size_t i = 0; i < TeamRed.size(); i++) {
			hpRed += TeamRed[i].hero.getHP();
			damageRed += TeamRed[i].hero.getDamage();
		}

		if (hpBlue - damageRed > hpRed - damageBlue) {
			winner = 1;
		}
		else if (hpBlue - damageRed == hpRed - damageBlue) {
			winner = 0;
		}
		else {
			winner = 2;
		}
	}

	void changeRank(vector<Player>& players) {

		for (size_t i = 0; i < TeamBlue.size(); i++) {

			int idBlue = TeamBlue[i].player.getID();
			int idRed = TeamRed[i].player.getID();

			for (size_t j = 0; j < players.size(); j++)
			{
				switch (winner) {
				case 1:
					if (players[j].getID() == idBlue) players[j].addRank();
					if (players[j].getID() == idRed) players[j].subRank();
					break;
				case 2:
					if (players[j].getID() == idRed) players[j].addRank();
					if (players[j].getID() == idBlue) players[j].subRank();
					break;
				}
			}
		}
	}
	void winnerAnnouncement() {
		if (winner > 0) {
			cout << arr[winner] << "Won this game " << endl;
		}
		else {
			cout << arr[winner] << endl;
		}
	}
	bool checkTeams() {
		int mmrRed = 0, mmrBlue = 0;
		for (size_t i = 0; i < TeamRed.size(); i++) {
			mmrRed += TeamRed[i].player.getRank();
			mmrBlue += TeamBlue[i].player.getRank();
		}
		if (fabs(mmrBlue - mmrRed) >= 100)	return false;
		return true;
	}
	void addTeamPart() {
		for (size_t i = 0; i < Lobby.size(); i++) {
			if (i < 5) {
				TeamBlue.push_back(Lobby[i]);
			}
			else {
				TeamRed.push_back(Lobby[i]);
			}
		}
	}
	bool checkPlayers() {
		int maxBlue = 0, maxRed = 0, minBlue = 999999999, minRed = 999999999;

		for (size_t i = 0; i < TeamBlue.size(); i++)
		{
			if (TeamBlue[i].player.getRank() > maxBlue) maxBlue = TeamBlue[i].player.getRank();
			if (TeamBlue[i].player.getRank() < minBlue) minBlue = TeamBlue[i].player.getRank();

			if (TeamRed[i].player.getRank() > maxRed) maxRed = TeamRed[i].player.getRank();
			if (TeamRed[i].player.getRank() < minRed) minRed = TeamRed[i].player.getRank();
		}

		if (maxBlue - minBlue >= 200 || maxRed - minRed >= 200) return false;

		return true;
	}
	

public:
	string arr[3] = { "Tie", "Blue", "Red" };
	
	  gameSession(vector <Player> & players, vector <Hero> & heroes) {
	
		for (size_t i = 0; i < heroes.size(); i++) {
			initHeroes.push_back(heroes[i]);
		}

		randVector(players);
		randVector(initHeroes);

		for (size_t i = 0; i < 10; i++) {
			if (initHeroes.size() < 10) {
				if (i < 5) {
					TeamPart tp = TeamPart(players[i], initHeroes[i]);
					Lobby.push_back(tp);
				}
				else {
					TeamPart tp = TeamPart(players[i], initHeroes[i - 5]);
					Lobby.push_back(tp);
				}
			}
			else {
				TeamPart tp = TeamPart(players[i], initHeroes[i]);
				Lobby.push_back(tp);
			}
		}

		addTeamPart();
		
		for (int i = 0; (!checkTeams() || !checkPlayers()) && i < 10000; i++)
		{
			randVector(Lobby);
			TeamBlue.clear();
			TeamRed.clear();
			addTeamPart();
		}
		Sleep(1000);
	}

	gameSession() {
		initHeroes.clear();
		TeamRed.clear();
		TeamBlue.clear();
		Lobby.clear();
	}

	void showTeamRed() {
		cout << endl
			<< "                  Team Red" << endl << endl
			<< "================================================" << endl << endl;
		for (size_t i = 0; i < TeamRed.size(); i++)
		{
			
			cout << "Name: " << TeamRed[i].player.getName()
				<< "\tID: " << TeamRed[i].player.getID()
				<< "\tRank: " << TeamRed[i].player.getRank()
				<< endl;
			
			cout << "Name: " << TeamRed[i].hero.getName()
				<< "\tHP: " << TeamRed[i].hero.getHP()
				<< "\tDamage: " << TeamRed[i].hero.getDamage()
				<< "\tSpeed: " << TeamRed[i].hero.getSpeed()
				<< endl
				<< (i == TeamRed.size() - 1 ? "" : "------------------------------------------------")
				<< endl;
		}
		cout << "================================================" << endl << endl;
	}

	void showTeamBlue() {
		cout << endl
			<< "                  Team Blue" << endl << endl
			<< "================================================" << endl << endl;
		for (size_t i = 0; i < TeamBlue.size(); i++)
		{
			cout << "Name: " << TeamBlue[i].player.getName()
				<< "\tID: " << TeamBlue[i].player.getID()
				<< "\tRank: " << TeamBlue[i].player.getRank()
				<< endl;
			
			cout << "Name: " << TeamBlue[i].hero.getName()
				<< "\tHP: " << TeamBlue[i].hero.getHP()
				<< "\tDamage: " << TeamBlue[i].hero.getDamage()
				<< "\tSpeed: " << TeamBlue[i].hero.getSpeed()
				<< endl
				<< (i == TeamBlue.size() - 1 ? "" : "------------------------------------------------")
				<< endl;
		}
		cout << "================================================" << endl << endl;
	}

	void gameStart(vector<Player>& players) {
		StartTime = time(0);
		getWinner();
		winnerAnnouncement();
		changeRank(players);
	}

	time_t getTime() {
		return StartTime;
	}

	void showTime() {
		tm* ltm = localtime(&StartTime);
		cout << "Date: " << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << "\t"
			<< "Time: " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl;
	}

	int getWinner() {
		return winner;
	}

	void saveLog() {
		ofstream fout;
		fout.open("log.txt", ofstream::app);

		fout << endl << endl << "New Game" << endl << endl;

		tm* ltm = localtime(&StartTime);
		fout << "Date: " << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << "\t"
			<< "Time: " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl;

		int winner = getWinner();
		fout << arr[winner] << " won" << endl;

		fout << endl
			<< "                  Team Red" << endl << endl
			<< "================================================" << endl << endl;
		for (size_t i = 0; i < TeamRed.size(); i++)
		{
			fout << "Name: " << TeamRed[i].player.getName()
				<< "\tID: " << TeamRed[i].player.getID()
				<< "\tRank: " << TeamRed[i].player.getRank()
				<< endl;
			
			fout << "Name: " << TeamRed[i].hero.getName()
				<< "\tHP: " << TeamRed[i].hero.getHP()
				<< "\tDamage: " << TeamRed[i].hero.getDamage()
				<< "\tSpeed: " << TeamRed[i].hero.getSpeed()
				<< endl
				<< (i == TeamRed.size() - 1 ? "" : "------------------------------------------------")
				<< endl;
		}
		fout << "================================================" << endl << endl;

		
		fout << endl
			<< "                  Team Blue" << endl << endl
			<< "================================================" << endl << endl;
		for (size_t i = 0; i < TeamBlue.size(); i++)
		{
			fout << "Name: " << TeamBlue[i].player.getName()
				<< "\tID: " << TeamBlue[i].player.getID()
				<< "\tRank: " << TeamBlue[i].player.getRank()
				<< endl;
		
			fout << "Name: " << TeamBlue[i].hero.getName()
				<< "\tHP: " << TeamBlue[i].hero.getHP()
				<< "\tDamage: " << TeamBlue[i].hero.getDamage()
				<< "\tSpeed: " << TeamBlue[i].hero.getSpeed()
				<< endl
				<< (i == TeamBlue.size() - 1 ? "" : "------------------------------------------------")
				<< endl;
		}
		fout << "================================================" << endl << endl;

		fout.close();
	}
};