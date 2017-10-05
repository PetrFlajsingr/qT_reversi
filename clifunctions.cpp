/**
 * @file clifunctions.cpp
 * @author Petr Flajsingr(xflajs00), Dominik Dvorak(xdvora1t)
 * @date 2 May 2016
 * @brief Modul funkci pro reversecli.cpp
 **/

#include "clifunctions.h"

/**
 * @brief Const. char** s reakcemi pri hre
 **/
const char *messages[] =
{
	"Vitejte ve hre Reversi!\n\n"
	"Chcete hrat novou hru nebo pokracovat v ulozene?\n\n"
	"Zadejte cislo a potvrdte stisknutim klavesy ENTER.\n\n"
	"1 pro novou hru\n"
	"2 pro ulozenou hru\n"
	"0 pro ukonceni\n",
	//-----------------------------------------------------------------
	"Zadejte velikost hraciho pole a potvrdte stisknutim klavesy ENTER.\n\n"
	"1 pro pole 6x6\n"
	"2 pro pole 8x8\n"
	"3 pro pole 10x10\n"
	"4 pro pole 12x12\n"
	"0 pro ukonceni\n",
	//-----------------------------------------------------------------
	"Nedefinovana volba, zkuste to znovu :))\n",
	//-----------------------------------------------------------------
	"Zadejte nazev souboru s ulozenou hrou a stisknete ENTER.\n\n"
	"Pro ukonceni zadejte 0.\n",
	//-----------------------------------------------------------------
	"Zadany soubor neexistuje, zkuste to znovu :))\n",
	//-----------------------------------------------------------------
	"Zadejte mod hry a potvrdte stisknutim klavesy ENTER.\n\n"
	"1 hrac vs PC\n"
	"2 hrac vs hrac\n"
	"0 pro ukonceni\n",
	//-----------------------------------------------------------------
	"Zadejte cislo ulozene hry a potvrdte stisknutim klavesy ENTER.\n\n"
	"Vypis ulozenych her:\n",
	//-----------------------------------------------------------------
	":(( nejsou ulozeny zadne predchozi hry.\n\n"
	"Zadejte cislo a potvrdte klavesou ENTER.\n\n"
	"1 pro novou hru\n"
	"0 pro ukonceni\n",
	//-----------------------------------------------------------------
	"Zvolena hra neni mezi ulozenymi.\n"
	"Zkuste to znovu nebo zadejte 0 pro ukonceni.\n",
	//-----------------------------------------------------------------
	"Zadejte tah nebo nekterou z operaci: ",
	//-----------------------------------------------------------------
	"Tah mimo pole nebo znak nedefinovany pro tah.\n\n"
	"Zkuste to znovu.\n\n",
	//-----------------------------------------------------------------
	"\nZadani tahu: radek (pismeno) a sloupec (cislo), napr. 4f\n"
	"UNDO - o tah zpet\n"
	"REDO - o tah dopredu\n"
	"EXIT - ukonceni hry, hra bude ulozena\n"
	"MOVE - ukazka moznych tahu\n"
	"HELP - vypsani aktualni obrazovky\n\n",
	//-----------------------------------------------------------------
	"Chybny tah :(( Zkuste to znovu.\n\n",
	//-----------------------------------------------------------------
	"Vyberte herni algoritmus.\n\n"
	"1 pro algoritmus nejlepsi pozice.\n"
	"2 pro algoritmus pozice + pocet kamenu\n"
	"0 pro ukonceni\n",
	//-----------------------------------------------------------------
	"Neni mozny dalsi tah, pokracujte klavesou ENTER pro tah pocitace.\n\n",
	//-----------------------------------------------------------------
	"Neni mozny dalsi tah, tahne protihrac.\n\n",
	//-----------------------------------------------------------------
	"Pokračujte stisknutim klavesy ENTER.\n",
	//-----------------------------------------------------------------
	"Neexistuji zadne dalsi tahy, konec hry.\n",
	//-----------------------------------------------------------------
	"Konec hry.\n"
};

/**
 * @brief Vymazani obrazovky
 **/
int clearScreen(void){
    #ifdef __MINGW32__
       	return(system("cls"));
    #else
      	return(system("clear"));
    #endif
}

/**
 * @brief Vypis zpravy na obrazovku
 * @param type typ zprávy
 **/
void coutMessage(int type){
	std::cout << messages[type];
}

/**
 * @brief Vypis na obrazovku pri spatnem vyberu
 * @param firstMessage Prvni chybova zprava
 * @param secondMesage Druha chybova zprava
 **/
void badChoice(Messages::messagesEnum firstMessage, Messages::messagesEnum secondMesage){
	clearScreen();
	coutMessage(firstMessage);
	coutMessage(secondMesage);
}

/**
 * @brief Vyber mezi novou nebo ulozenou hrou
 **/
int newOrSavedGame(void){
	int newOrSaved;
	coutMessage(Messages::WELC_NEW_SAVED);
	while(1){
		std::cin >> newOrSaved;
		if(!std::cin){
			std::cin.clear();
			std::cin.ignore();
		}else if(newOrSaved == 0){
			clearScreen();
			return newOrSaved;
		}else if(newOrSaved == 1){
			clearScreen();
			return newOrSaved;
		}else if(newOrSaved == 2){
			clearScreen();
			return newOrSaved;
		}
		badChoice(Messages::WELC_NEW_SAVED, Messages::BAD_CHOICE);
	}
}

/**
 * @brief Zvolena nova hra
 **/
int newGame(void){
	int getSize;
	int getMode;
	int numberOfSaveFile;
	std::string saveFile;
	if(!(getSize = chooseBoardSize())){
		return 0;
	}
	getMode = chooseGameMode();
	if(getMode == -1){
		return 0;
	}
	numberOfSaveFile = getNumberOfNextSave();
	saveFile = newSaveFile(numberOfSaveFile);
	return(letsPlayTheGame(getSize, getMode, saveFile));
}

/**
 * @brief Volba velikosti hraci desky
 **/
int chooseBoardSize(void){
	int getSize;
	coutMessage(Messages::BOARD_SIZE);
	while(1){
		std::cin >> getSize;
		if(!std::cin){
			std::cin.clear();
			std::cin.ignore();
		}else if(getSize == 0){
			clearScreen();
			return 0;
		}else if(getSize == 1){
			clearScreen();
			return 6;	
		}else if(getSize == 2){
			clearScreen();
			return 8;
		}else if(getSize == 3){
			clearScreen();
			return 10;
		}else if(getSize == 4){
			clearScreen();
			return 12;
		}
		badChoice(Messages::BOARD_SIZE, Messages::BAD_CHOICE);
	}
}

/**
 * @brief Volba AI algoritmu
 **/
int chooseAIAlg(void){
	int getAI;
	coutMessage(Messages::AI_ALG_CHOOSE);
	while(1){
		std::cin >> getAI;
		if(!std::cin){
			std::cin.clear();
			std::cin.ignore();
		}else if(getAI == 0){
			clearScreen();
			return getAI;
		}else if(getAI == 1){
			clearScreen();
			return getAI;
		}else if(getAI == 2){
			clearScreen();
			return getAI;
		}	
		badChoice(Messages::AI_ALG_CHOOSE, Messages::BAD_CHOICE);
	}
}


/**
 * @brief Vyber herniho modu
 **/
int chooseGameMode(void){
	int getMode;
	coutMessage(Messages::GAME_MODE);
	while(1){
		std::cin >> getMode;
		if(!std::cin){
			std::cin.clear();
			std::cin.ignore();
		}else if(getMode == 0){
			clearScreen();
			return -1;
		}else if(getMode == 1){
			clearScreen();
			return 0;
		}else if(getMode == 2){
			clearScreen();
			return 1;
		}
		badChoice(Messages::GAME_MODE, Messages::BAD_CHOICE);
	}
}

/**
 * @brief Zadna ulozena hra
 **/
int noSavedGames(void){
	int getChoice;
	clearScreen();
	coutMessage(Messages::NO_SAVED_GAMES);
	while(1){
		std::cin >> getChoice;
		if(!std::cin){
			std::cin.clear();
			std::cin.ignore();
		}else if(getChoice == 0){
			clearScreen();
			return getChoice;
		}else if(getChoice == 1){
			clearScreen();
			return getChoice;
		}
		badChoice(Messages::NO_SAVED_GAMES, Messages::BAD_CHOICE);
	}
}

/**
 * @brief Vyber ulozene hry
 * @param makeChoice cislo ulozene hry
 **/
int makeChoice(int makeChoice){
	int choiceSavedGame;
	bool badSaved = false;
	while(1){
		std::cin >> choiceSavedGame;
		if(!std::cin){
			std::cin.clear();
			std::cin.ignore();
		}else if(((choiceSavedGame < 1) || (choiceSavedGame > makeChoice)) && choiceSavedGame != 0){
			badSaved = 1;
			clearScreen();
			coutMessage(Messages::BAD_CHOICE_SAVED);
			getListOfSaveFiles();
		}else if(badSaved && choiceSavedGame == 0){
			clearScreen();
			return 0;
		}else{
			return choiceSavedGame;
		}
	}
}

/**
 * @brief Tiskne barevne pole na zaklade druhu kamene
 * @param type druh pole na tisk
 **/
void colorItAndPrint(int type){
	if(type == 0){
		std::cout << "\u25A1 ";
	}
	else if(type == 1){
		std::cout << "\033[30;49m\u2B22 \x1b[0m";
	}
	else if(type == 2){
		std::cout << "\033[37;49m\u2B22 \x1b[0m";
	}
	else if(type == 3){
		std::cout << "\033[32;49m\u2611 \x1b[0m";
	}
}

/**
 * @brief Parsuje hraci desku a posila do colorItAndPrint na vytisknuti
 * @param game reference na tridu gameInfo
 * @param boardSize velikost vykreslovane desky
 **/
void printBoard(gameInfo& game, int boardSize){
	int stoneType;
	std::cout << "  ";
	for(int i = 0; i < boardSize; ++i){
		std::cout << " " << (char)(i + 97);
	}
	std::cout << std::endl;
	for(int i = 0; i < boardSize; i++){
		if(i < 9){
			std::cout << " ";
		}
		std::cout << i + 1 << " ";
		for(int j = 0; j < boardSize; j++){
			stoneType = game.getStone(i, j, game.M_BOARD);
			colorItAndPrint(stoneType);
		}
		std::cout<< i + 1 << std::endl;
	}
	std::cout << "  ";
	for(int i = 0; i < boardSize; ++i){
		std::cout << " " << (char)(i + 97);
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

/**
 * @brief Zobrazeni vsech moznych tahu zelenou barvou
 * @param game reference na tridu gameInfo
 * @param boardSize velikost vykreslovane desky
 **/
void showMoves(gameInfo& game, int boardSize){
	int stoneType;
	game.checkMoves(game.getRound() % 2);
	std::cout << "  ";
	for(int i = 0; i < boardSize; ++i){
		std::cout << " " << (char)(i + 97);
	}
	std::cout << std::endl;
	for(int i = 0; i < boardSize; i++){
		if(i < 9){
			std::cout << " ";
		}
		std::cout << i + 1 << " ";
		for(int j = 0; j < boardSize; j++){
			stoneType = game.getStone(i, j, game.M_BOARD);
			if(stoneType == 0){
				stoneType = game.getStone(i, j, game.M_MOVES);
				if(stoneType != 0){
					stoneType = 3;
				}
			}
			colorItAndPrint(stoneType);
		}
		std::cout<< i + 1 << std::endl;
	}
	std::cout << "  ";
	for(int i = 0; i < boardSize; ++i){
		std::cout << " " << (char)(i + 97);
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

/**
 * @brief Vypis
 * @param game reference na tridu gameInfo
 **/
void printScoreEtc(gameInfo& game){
	std::cout << "Score prvniho hrace \033[30;49m\u2B22 \x1b[0m: " << game.getScore(0) << "  ||  Score druheho hrace \033[37;49m\u2B22 \x1b[0m: " << game.getScore(1) << std::endl;
	std::string hrac;
	if((game.getRound() % 2 + 1) == 1){
		hrac = "prvni \033[30;49m\u2B22 \x1b[0m";
	}else{
		hrac = "druhy \033[37;49m\u2B22 \x1b[0m";
	}
	std::cout << "\nNa tahu je hrac " << hrac << std::endl << std:: endl;
}

/**
 * @brief Prevod pismena na int tak, aby se mohl parsovat
 * @param character pismeno k prevodu
 **/
int trasferAlhabet(char character){
	return(character - 97);
}

/**
 * @brief Parsovani prichozi operace od hrace
 * @param game reference na tridu gameInfo
 * @param rowMove reference na radek
 * @param columnMove reference na sloupec
 * @param boardSize velikost hraci desky
 * @param undo prepinac operace UNDO
 * @param badMove prepinac spatneho tahu
 * @param counter pocet tahu
 * @param ai reference na tridu aiPlayer
 * @param AIOrPlayer prepinac pro pl vs pl nebo pl vs AI
 **/
int getMove(gameInfo& game, int &rowMove, int &columnMove, int boardSize, bool undo, bool badMove, bool &noMoreMoves, int counter, aiPlayer& ai, bool AIOrPlayer){
	std::string move;
	int row = 0;
	bool help = false;
	while(1){
		if((counter % 2 == 0) || (AIOrPlayer == 1)){
			if(!help && !badMove && !noMoreMoves){
				coutMessage(Messages::MAKE_MOVE);
			}
			if(help){
				coutMessage(Messages::HELP);
				coutMessage(Messages::MAKE_MOVE);
				help = false;
			}
			if(badMove){
				clearScreen();
				printBoard(game, boardSize);
				printScoreEtc(game);
				coutMessage(Messages::BAD_MOVE);
				coutMessage(Messages::MAKE_MOVE);
			}
			std::cin >> move;
			if(!std::cin){
				std::cin.clear();
				std::cin.ignore();
			}else if(((move.length()) == 2) || ((move.length()) == 3)){
				std::string first;
				std::string second;
				if((move.length()) == 2){
					first = move.substr(0,1);
					second = move.substr(1,1);
				}else{
					first = move.substr(0,2);
					second = move.substr(2,1);
				}
				bool isNumber = (first.find_first_not_of("0123456789") == std::string::npos);
	    		if(isNumber){
	    			row = std::stoi(first, NULL, 0);
	    		}
				if(((row < 0) || (row > boardSize - 1)) && !isNumber){
					clearScreen();
					printBoard(game, boardSize);
					coutMessage(Messages::UNDEFINED_MOVE);
				}else{
					rowMove = row - 1;
				}
				int column = trasferAlhabet(second[0]);
				if((column < 0) || (column > boardSize - 1)){
					clearScreen();
					printBoard(game, boardSize);
					coutMessage(Messages::UNDEFINED_MOVE);
				}else{
					columnMove = column;
					if(isNumber){
						if(undo){
							return(Operations::AFTER_UNDO);
						}else{
							return(Operations::OK_MOVE);
						}
					}
				}
			}else if((move.length()) == 4){
				if(!(move.compare("UNDO")) || !(move.compare("undo"))){
					return(Operations::UNDO);
				}else if(!(move.compare("REDO")) || !(move.compare("redo"))){
					return(Operations::REDO);
				}else if(!(move.compare("HELP")) || !(move.compare("help"))){
					help = true;
				}else if(!(move.compare("MOVE")) || !(move.compare("move"))){
					getchar();
					clearScreen();
					showMoves(game, boardSize);
					printScoreEtc(game);
					coutMessage(Messages::CONTINUE);
					std::cin.get();
					clearScreen();
					return(Operations::MOVE);
				}else if(!(move.compare("EXIT")) || !(move.compare("exit"))){
					return(Operations::EXIT);
				}
			}
			clearScreen();
			printBoard(game, boardSize);
			printScoreEtc(game);
			if(!help){	
				coutMessage(Messages::UNDEFINED_MOVE);
			}			
		}else{
			if(noMoreMoves){
				clearScreen();
				printBoard(game, boardSize);
				printScoreEtc(game);
				coutMessage(Messages::NO_MORE_MOVES_AI);
				std::cin.get();
				clearScreen();
				if(ai.aiMove(rowMove, columnMove, game) == 0){
					return(-1);
				}else{
					return(Operations::OK_MOVE);
				}	
			}
			ai.aiMove(rowMove, columnMove, game);
			return(Operations::OK_MOVE);
		}
	}
}

/**
 * @brief Vytvoreni kostruktoru pro hru, overload na novou hru, dalsi krok podle modu
 * @param boardSize velikost vykreslovane desky
 * @param gameMode mod hry
 * @param saveFile soubor pro ukladani
 **/
int letsPlayTheGame(int boardSize, int gameMode, std::string saveFile){
	gameInfo game(boardSize, gameMode, saveFile);
	int AIAlg = 0;
	if(gameMode == 0){
		AIAlg = chooseAIAlg();
	}
	printBoard(game, boardSize);
	if(gameMode == 1){
		return(playerVsPlayer(game, boardSize));
	}else{
		return(playerVsComputer(game, boardSize, AIAlg));
	}
}

/**
 * @brief Vytvoreni kostruktoru pro hru, overload na ulozenou hru, dalsi krok podle modu
 * @param saveFile soubor pro ukladani
 **/
int letsPlayTheGame(std::string saveFile){
	gameInfo game(saveFile);
	int boardSize = game.getBoardSize();
	int gameMode = game.getMode();
	int AIAlg = 0;
	if(gameMode == 0){
		AIAlg = chooseAIAlg();
	}
	clearScreen();
	printBoard(game, boardSize);
	if(gameMode == 1){
		return(playerVsPlayer(game, boardSize));
	}else{
		return(playerVsComputer(game, boardSize, AIAlg));
	} 
}

/**
 * @brief Parsovani tahu herni logiky
 * @param AIOrPlayer prepinac pro pl vs pl nebo pl vs AI
 * @param aiPlayer reference na tridu
 **/
int gameMovesLogic(gameInfo &game, int boardSize, int AIOrPlayer, aiPlayer &ai){
	int counter = game.getRound();
	int temp;
	int rowMove;
	int columnMove;
	int undoCounter = 0;
	bool undo = false;
	bool possibleRedo = false;
	bool badMove = false;
	bool noSwitch = false;
	bool noMoreMoves = false;
	bool noUndoButNoBadMove = false;
	bool showPossibleMoves = false;
	game.checkScore();
	while(1){
		if((game.getScore(0) == (boardSize * boardSize)) || (game.getScore(1) == (boardSize * boardSize))){
			return(gameOver(game, Gameover::ONE_ZERO));
		}else if((game.getScore(0) == ((boardSize*boardSize)/2)) && (game.getScore(1) == ((boardSize*boardSize)/2))){
			return(gameOver(game, Gameover::DRAW));
		}else if((game.getScore(0) + game.getScore(1)) == boardSize * boardSize){
			return(gameOver(game, Gameover::FULL_BOARD));
		}else if((game.getScore(0) == 0) || (game.getScore(1) == 0)){
			return(gameOver(game, Gameover::ONE_ZERO));
		}

		printScoreEtc(game);
		switch(getMove(game,rowMove, columnMove, boardSize, undo, badMove, noMoreMoves, counter, ai, AIOrPlayer)){
			case Operations::OK_MOVE:{
				undo = false;
				break;
			}
			case Operations::UNDO:{
				if(counter != 0){
					if(AIOrPlayer == 1){
						game.loadNthMap(game.getRound());
						counter--;
					}else{
						game.loadNthMap(game.getRound() - 1);
						counter -= 2;
					}	
					undoCounter++;
					possibleRedo = true;
					undo = true;
					badMove = false;
				}else{
					noUndoButNoBadMove = true;
					noSwitch = true;
					badMove = false;
				}
				break;
			}
			case Operations::REDO:{
				if(undo && possibleRedo && (undoCounter != 0)){
					if(AIOrPlayer == 1){
						game.loadNthMap(game.getRound() + 2);
						counter++;
					}else{
						game.loadNthMap(game.getRound() + 3);
						counter+= 2;
					}
					undoCounter--;
				}else{
					noUndoButNoBadMove = true;
					possibleRedo = false;
					noSwitch = true;
					badMove = false;
				}
				break;
			}
			case Operations::AFTER_UNDO:{
				game.deleteHistory(game.getRound() + 1);
				undoCounter = 0;
				possibleRedo = false;
				undo = false;
				break;
			}
			case Operations::MOVE:{
				noUndoButNoBadMove = true;
				noSwitch = true;
				badMove = false;
				showPossibleMoves = true;
				break;
			}
			case Operations::EXIT:{
				return 0;
			}
			case -1:{
				return(gameOver(game, Gameover::NO_MORE_MOVES));
			}
		}

		badMove = false;
		clearScreen();
		if(!noSwitch){
			if(!undo){
				if(!noUndoButNoBadMove || !showPossibleMoves){
					if((temp = game.makeMove(game.getRound() % 2, rowMove, columnMove)) == 0){
						badMove = true;
					}else if (temp == -1){
						noMoreMoves = true;
						counter++;				
					}
				}
			}
		}
		if(!badMove){
				printBoard(game, boardSize);
			if(!noSwitch || !badMove){
				if(!undo){
					if(!noUndoButNoBadMove || !showPossibleMoves){
						counter++;
					}
				}
			}
		}
		noUndoButNoBadMove = false;
		showPossibleMoves = false;
		noSwitch = false;
	}
}

/**
 * @brief Spusteni hry, hrac vs hrac
 * @param game reference na tridu gameInfo
 * @param boardSize velikost hraci plochy
 **/
int playerVsPlayer(gameInfo& game, int boardSize){
	aiPlayer fakeAIReference(-1);
	gameMovesLogic(game, boardSize, Mode::PLAYER, fakeAIReference);
	return 0;
}

/**
 * @brief Spusteni hry, hrac vs PC
 * @param game reference na tridu gameInfo
 * @param boardSize velikost hraci plochy
 **/
int playerVsComputer(gameInfo& game, int boardSize, int AIAlg){
	aiPlayer ai(AIAlg);
	gameMovesLogic(game, boardSize, Mode::AI, ai);
	return 0;
}

/**
 * @brief Typ ukonceni hry
 * @param game reference na tridu gameInfo
 * @param type typ ukonceni
 **/
int gameOver(gameInfo& game, int type){
	switch(type){
		case Gameover::NO_MORE_MOVES:{
			coutMessage(Messages::NO_MORE_MOVES);
			if(game.getScore(0) > game.getScore(1)){
				std::cout << "Vitez: Hrac prvni.\n";
			}else{
				std::cout << "Vitez: Hrac druhy.\n";
			}
			break;
		}
		case Gameover::FULL_BOARD:{
			coutMessage(Messages::GAME_OVER);
			if(game.getScore(0) > game.getScore(1)){
				std::cout << "Vitez: Hrac prvni.\n";
			}else{
				std::cout << "Vitez: Hrac druhy.\n";
			}
			break;
		}
		case Gameover::ONE_ZERO:{
			coutMessage(Messages::GAME_OVER);
			if(game.getScore(0) > game.getScore(1)){
				std::cout << "Vitez: Hrac prvni.\n";
			}else{
				std::cout << "Vitez: Hrac druhy.\n";
			}
			break;
		}
		case Gameover::DRAW:{
			coutMessage(Messages::GAME_OVER);
			std::cout << "Remiza.\n";
			break;
		}
	}
	return 0;
}