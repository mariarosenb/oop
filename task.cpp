
#include "string.h"
#include "playerManager.h"
#include "heroManager.h"
#include "session.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int main() {
	playerManager pm;
	heroManager hm;
	session sm;


	pm.generatePlayers(20);
	hm.createHeroes(10);

	pm.listOfPlayers();

	sm.performGameSession(pm.players, hm.heroes, 10);
	sm.listOfSessions();

	pm.listOfPlayers();

	system("pause");
	return 0;
}