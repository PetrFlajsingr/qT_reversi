/**
 * @file main.cpp
 * @author Petr Flajsingr(xflajs00), Dominik Dvorak(xdvora1t)
 * @date 2 May 2016
 * @brief Hlavni cast programu
 **/
#include "reversigui.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    reversigui w;
    w.show();

    return a.exec();
}
