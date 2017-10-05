/**
 * @file aiplayer.cpp
 * @author Petr Flajsingr(xflajs00), Dominik Dvorak(xdvora1t)
 * @date 2 May 2016
 * @brief Soubor obsahujici definice funkci pro aiplayer.h
 **/
#include "aiplayer.h"

/**
 * @brief Konstruktor tridy
 *
 * nahodne vybira jaky algoritmus bude aplikovan
 **/
aiPlayer::aiPlayer(bool type){
    mode = type;
}

/**
 * @brief Volani algoritmu pro vyber pozice
 *
 * Funkce vola algoritmus za zaklade predem definovaneho prepinace
 * @param x x souradnice
 * @param y y souradnice
 * @param info Informace o hre
 * @retval false pri nemoznosti pohybu
 * @retval true pri moznosti pohybu
 **/
bool aiPlayer::aiMove(int &x, int &y, gameInfo &info){
    if(!info.checkMoves(1)){
        return false;
    }
    if(mode == 0){
        weightMove(x, y, info);
    }else if(mode == 1){
        bestMove(x, y, info);
    }
    return true;
}

/**
 * @brief Vyber pozice na zaklade hodnoty dane pozice
 *
 * @param x x souradnice
 * @param y y souradnice
 * @param info Informace o hre
 **/
void aiPlayer::weightMove(int &x, int &y, gameInfo &info){
    int tempx = 0;
    int tempy = 0;
    int w = -1;
    for(int i = 0; i < info.getBoardSize(); ++i){
        for(int j = 0; j < info.getBoardSize(); ++j){
            if(info.getStone(i, j, gameInfo::M_MOVES) == 1){
                if(info.getStone(i, j, gameInfo::M_WEIGHT) > w){
                    w = info.getStone(i, j, gameInfo::M_WEIGHT);
                    tempx = i;
                    tempy = j;
                }
            }
        }
    }
    x = tempx;
    y = tempy;
}

/**
 * @brief Vyber pozice na zaklade hodnoty pozice a zmenenych kamenu
 *
 * @param x x souradnice
 * @param y y souradnice
 * @param info Informace o hre
 **/
void aiPlayer::bestMove(int &x, int &y, gameInfo &info){
    int tempx = 0;
    int tempy = 0;
    double w = -1;
    double tempw;
    for(int i = 0; i < info.getBoardSize(); ++i){
        for(int j = 0; j < info.getBoardSize(); ++j){
            if(info.getStone(i, j, gameInfo::M_MOVES) == 1){
                if((tempw = info.getStone(i, j, gameInfo::M_WEIGHT) * stonesChanged(i, j, info) + 0.1) > w){
                    w = tempw;
                    tempx = i;
                    tempy = j;
                }
            }
        }
    }
    x = tempx;
    y = tempy;
}

/**
 * @brief Funkce pro vypocet zmenenych kamenu pro danou pozici
 *
 * @param x x souradnice
 * @param y y souradnice
 * @param info Informace o hre
 * @return Pocet potencialne zmenenych kamenu
 **/
int aiPlayer::stonesChanged(int x, int y, gameInfo &info){
    if(!mode && info.getStone(x, y, gameInfo::M_BOARD) != 0){
        return 0;
    }
    int count = 0;
    //kontrola dolu od kamene
    for(int i = x + 1; i < info.getBoardSize(); ++i){
        if(info.getStone(i, y, gameInfo::M_BOARD) != 0){
            if(info.getStone(i, y, gameInfo::M_BOARD) == 2){
                count += i - x - 1;
                break;
            }
        }else{
            break;
        }
    }
    //kontrola vpravo od kamene
    for(int i = y + 1; i < info.getBoardSize(); ++i){
        if(info.getStone(x, i, gameInfo::M_BOARD) != 0){
            if(info.getStone(x, i, gameInfo::M_BOARD) == 2){
                count += i - y - 1;
                break;
            }
        }else{
            break;
        }
    }
    //kontrola nahoru od kamene
    for(int i = x - 1; i >= 0; --i){
        if(info.getStone(i, y, gameInfo::M_BOARD) != 0){
            if(info.getStone(i, y, gameInfo::M_BOARD) == 2){
                count += x - i - 1;
                break;
            }
        }else{
            break;
        }
    }
    //kontrola vlevo od kamene
    for(int i = y - 1; i >= 0; --i){
        if(info.getStone(x, i, gameInfo::M_BOARD) != 0){
            if(info.getStone(x, i, gameInfo::M_BOARD) == 2){
                count += y - i - 1;
                break;
            }
        }else{
            break;
        }
    }
    //vpravo dolu
    for(int i = x + 1, j = y + 1; i < info.getBoardSize() && j < info.getBoardSize(); ++i, ++j){
        if(info.getStone(i, j, gameInfo::M_BOARD) != 0){
            if(info.getStone(i, j, gameInfo::M_BOARD) == 2){
                count += i - x - 1;
                break;
            }
        }else{
            break;
        }
    }
    //vpravo nahoru
    for(int i = x - 1, j = y + 1; i >= 0 && j < info.getBoardSize(); --i, ++j){
        if(info.getStone(i, j, gameInfo::M_BOARD) != 0){
            if(info.getStone(i, j, gameInfo::M_BOARD) == 2){
                count += x - i - 1;
                break;
            }
        }else{
            break;
        }
    }
    //vlevo dolu
    for(int i = x + 1, j = y - 1; i < info.getBoardSize() && j >= 0; ++i, --j){
        if(info.getStone(i, j, gameInfo::M_BOARD) != 0){
            if(info.getStone(i, j, gameInfo::M_BOARD) == 2){
                count += i - x - 1;
                break;
            }
        }else{
            break;
        }
    }
    //vlevo nahoru
    for(int i = x - 1, j = y - 1; i >= 0 && j >= 0; --i, --j){
        if(info.getStone(i, j, gameInfo::M_BOARD) != 0){
            if(info.getStone(i, j, gameInfo::M_BOARD) == 2){
                count += x - i - 1;
                break;
            }
        }else{
            break;
        }
    }
    return count;
}
