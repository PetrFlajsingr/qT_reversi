/**
 * @file aiplayer.h
 * @author Petr Flajsingr(xflajs00), Dominik Dvorak(xdvora1t)
 * @date 2 May 2016
 * @brief Soubor obsahujici tridu pro ovladani ai hrace
 **/

#pragma once
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "gameinfo.h"

class aiPlayer{
public:
    aiPlayer(bool type);
	bool aiMove(int &x, int &y, gameInfo &info); /**< TODO funkce pro polozeni kamene, vraci false pri nemoznost hrat */
private:
	int mode; /**< Typ algoritmu pro hru, false - random, true - vyber podle vah pozic */
	void weightMove(int &x, int &y, gameInfo &info);
	void bestMove(int &x, int &y, gameInfo &info);
	int stonesChanged(int x, int y, gameInfo &info);
};
