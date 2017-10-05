/**
 * @file clifunctions.h
 * @author Petr Flajsingr(xflajs00), Dominik Dvorak(xdvora1t)
 * @date 2 May 2016
 * @brief Hlavickovy soubor clifunctions.cpp
 **/

#pragma once
 
#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include "gameinfo.h"
#include "aiplayer.h"
#include "savefiles.h"

///Enum pro vypis zprav
namespace Messages{
	enum messagesEnum{
		WELC_NEW_SAVED = 0,
		BOARD_SIZE,
		BAD_CHOICE,
		FILE_CHOICE,
		FILE_NOEXIST,
		GAME_MODE,
		LIST_OF_SAVED_GAMES,
		NO_SAVED_GAMES,
		BAD_CHOICE_SAVED,
		MAKE_MOVE,
		UNDEFINED_MOVE,
		HELP,
		BAD_MOVE,
		AI_ALG_CHOOSE,
		NO_MORE_MOVES_AI,
		NO_MORE_MOVES_PLAYER,
		CONTINUE,
		NO_MORE_MOVES,
		GAME_OVER
	};
}

/**
 * @brief Namespace s vyctem pro operace
 **/
namespace Operations{
	enum operationsEnum{
		OK_MOVE = 0,
		UNDO,
		REDO,
		HELP,
		AFTER_UNDO,
		MOVE,
		EXIT
	};
}

/**
 * @brief Namespace s vyctem pro zpravy
 **/
namespace Mode{
	enum modeEnum{
		AI = 0,
		PLAYER
	};
}

/**
 * @brief Namespace s vyctem pro koncove stavy hry
 **/
namespace Gameover{
	enum gameOverEnum{
		NO_MORE_MOVES = 0,
		FULL_BOARD,
		ONE_ZERO,
		DRAW
	};
}

//Deklarace funkci
int clearScreen(void);
void coutMessage(int);
void badChoice(Messages::messagesEnum, Messages::messagesEnum);
int newOrSavedGame(void);
int newGame(void);
int chooseBoardSize(void);
int chooseAIAlg(void);
int chooseGameMode(void);
int noSavedGames(void);
int makeChoice(int);
void colorItAndPrint(int type);
void printBoard(gameInfo&);
void showMoves(gameInfo&, int);
void printScoreEtc(gameInfo&);
int trasferAlhabet(char);
int getMove(gameInfo&, int &, int &, int, bool, bool, int, aiPlayer&, bool);
int letsPlayTheGame(int, int, std::string);
int letsPlayTheGame(std::string);
int gameMovesLogic(gameInfo &, int, int, aiPlayer&);
int playerVsPlayer(gameInfo&, int);
int playerVsComputer(gameInfo&, int, int);
int gameOver(gameInfo&, int);