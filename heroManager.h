
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "hero.h"

using namespace std;

class heroManager
{
public:
	vector<Hero> heroes;

	void createHeroes(int n) {
		vector<string> names = {
			"Atsushi", "Daiki", "Hotaru", "Yuki", "Kosuke", "Tomo", "Ryota", "Haru", "Yamato", "Yuta", "Kai"
		};
		srand((unsigned)time(NULL));
		for (int i = 0; i < n; i++) {
			int idx = rand() % names.size();
			int hp = rand() % 100 + 1;
			int damage = rand() % 10 + 1;
			int speed = rand() % 2 + 1;
			Hero hero = Hero(names[idx], hp, damage, speed);
			heroes.push_back(hero);
		}
	}

	void listOfHeroes() {
		
		for (size_t i = 0; i < heroes.size(); i++) {
			cout << "Name: " << heroes[i].getName()
				<< "\tHP: " << heroes[i].getHP()
				<< "\tDamage: " << heroes[i].getDamage()
				<< "\tSpeed: " << heroes[i].getSpeed()
				<< endl;
		}
	}

	int addHero(string name, int hp, int damage, int speed) {
		for (size_t i = 0; i < heroes.size(); i++) {
			if (heroes[i].getName() == name) {
				cout << "This name is already exist " << endl;
				return 0;
			}
		}
		Hero hero = Hero(name, hp, damage, speed);
		heroes.push_back(hero);
	}

	Hero getHeroByName(string name) {
		for (size_t i = 0; i < heroes.size(); i++) {
			if (heroes[i].getName() == name) {
				return heroes[i];
			}
		}
	}

	void removePlayer(string name) {
		for (size_t i = 0; i < heroes.size(); i++) {
			if (heroes[i].getName() == name) heroes.erase(heroes.begin() + i);
			break;
		}
	}
};
