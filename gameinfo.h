/**
 * @file gameinfo.h
 * @author Petr Flajsingr(xflajs00), Dominik Dvorak(xdvora1t)
 * @date 2 May 2016
 * @brief Soubor obsahujici tridu pro ukladani informaci o hre
 **/
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdio>
 
/**
 * @brief Trida pro ukladani informaci o hre a praci s nimi
 *
 * trida gameInfo obsahuje informace o hernim poli, poctu hracu, jejich skore a 
 * dale i funkce pro praci s temito informacemi
 **/
class gameInfo{

public:
	/// enum pro jednotlive mapy hry
	enum maps{
		M_BOARD = 0, /**< Zakladni plocha hry */
		M_WEIGHT, /**< Mapa jednotlivych vah poli */
		M_MOVES /**< Mapa moznych pohybu */
	};
	//konstruktory
	gameInfo(int size, bool player, std::string file);
	gameInfo(std::string file);
	//destruktor
	~gameInfo();
	//verejne funkce
	int makeMove(bool color, int x, int y);
	int getScore(bool player);
	int getRound();
	int getStone(int x, int y, maps map);
	bool loadNthMap(int n);
	void deleteHistory(int n);
	bool checkMoves(bool color); 
	int getBoardSize();
	bool getMode();
	void checkScore();
private:
	int boardSize; /**< velikost herni plochy*/
	int** board; /**< pole pro herni plochu a jeji stav
						0 znaci policko bez "kamenu"
						1 znaci policko s bilym "kamenem"
						2 znaci policko s cernym "kamenem"*/
	int** weightMap; /**< mapa znacici vahy jednotlivych pozic 
						0 - nejnizsi vaha, 3 - nejvyssi vaha*/
	bool** moveMap; /**< mapa moznych tahu, true - mozny tah, false - nemozny tah*/
	bool players; /**< false - 1 hrac, true - 2 hraci */
	int scorePlayer1; /**< pocet bodu prvniho hrace */
	int scorePlayer2; /**< pocet bodu druheho hrace */
	int moveCount; /**< pocet tahu od zacatku hry, sudy - 1. hrac je na tahu, lichy - 2. hrac je na tahu */
	std::fstream saveFile; /**< Stream pro praci se souborem pro ulozeni hry */
	std::string fileName; /**<< Cesta/nazev k savefile */
	//privatni funkce
	void changeRange(bool color, int x1, int x2, int y1, int y2);
	void setWMap();
	void set4(char val, int i, int j);
	void setStone(bool color, int x, int y);
	bool checkBoard(bool color, int x, int y, bool mode);
	void saveHeader();
	void saveMap();
	bool loadMap(bool mode);
};