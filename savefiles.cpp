/**
 * @file savefiles.cpp
 * @author Petr Flajsingr(xflajs00), Dominik Dvorak(xdvora1t)
 * @date 2 May 2016
 * @brief Modul funkci ukladani savefiles
 **/

#include "savefiles.h"

 /**
 * @brief Vypis ulozenych her na obrazovku.
 **/
void getListOfSaveFiles(){
    std::string saveFile = "saves/save.";
    for(int i = 1; ; i++){
        saveFile += std::to_string(i);
        if (std::ifstream(saveFile)){
                std::cout << saveFile << std::endl;
        }else{
            return;
        }
        saveFile = "saves/save.";
    }
}

 /**
 * @brief Vraci nasledujici cislo savu.
 **/
int getNumberOfNextSave(){
    std::string saveFile = "saves/save.";
    for(int i = 1; ; i++){
        saveFile += std::to_string(i);
        if (!(std::ifstream(saveFile))){
            return(i);
        }
        saveFile = "saves/save.";
    }
}

/**
 * @brief Vytvoreni nove save file
 * @param numberOfSaveFile cislo nove ukladane hry
 **/
std::string newSaveFile(int numberOfSaveFile){
    std::string saveFile = "saves/save.";
    saveFile += std::to_string(numberOfSaveFile);
    std::ofstream outfile (saveFile);
    outfile.close();
    return(saveFile);
}

/**
 * @brief Vraci string pro zvoleny save number
 * @param savedGameChoiced cislo zvolene hry
 **/
std::string makeSaveString(int savedGameChoiced){
    return("saves/save." + std::to_string(savedGameChoiced));
}
