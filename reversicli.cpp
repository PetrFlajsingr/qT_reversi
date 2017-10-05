/**
 * @file reversicli.cpp
 * @author Petr Flajsingr(xflajs00), Dominik Dvorak(xdvora1t)
 * @date 2 May 2016
 * @brief Soubor obsahujici definice funkci pro tridu gameInfo
**/
#include "reversicli.h"

/**
 * @brief Main funkce pro CLI Reversi
 **/
int main(void){
	clearScreen();
	int newOrSaved;
	int countOfSavedGames;
	int savedGameChoiced;
	std::string saveFile;

	newOrSaved = newOrSavedGame();
	if(newOrSaved == 0){
			return 0;
	}else if(newOrSaved == 1){
		if(!newGame()){
			return 0;
		}
	}else if(newOrSaved == 2){
		getListOfSaveFiles();
		countOfSavedGames = getNumberOfNextSave();
		if(!countOfSavedGames){
			if(!noSavedGames()){
				return 0;
			}else{
				if(!newGame()){
					return 0;
				}
			}
		}else{
			savedGameChoiced = makeChoice(countOfSavedGames);
			saveFile = makeSaveString(savedGameChoiced);
			return(letsPlayTheGame(saveFile));
		}
	}else{
		return 0;
	}
}