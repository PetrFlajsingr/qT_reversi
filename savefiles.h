/**
 * @file savefiles.h
 * @author Petr Flajsingr(xflajs00), Dominik Dvorak(xdvora1t)
 * @date 2 May 2016
 * @brief Hlavickovy soubor savefiles.cpp
 **/

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


void getListOfSaveFiles();
int getNumberOfNextSave();
std::string newSaveFile(int);
std::string makeSaveString(int);
