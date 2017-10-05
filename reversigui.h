/**
 * @file reversigui.h
 * @author Petr Flajsingr(xflajs00), Dominik Dvorak(xdvora1t)
 * @date 2 May 2016
 * @brief Header obsahujici tridu reversigui. Tato trida obstarava vse ohledne grafickeho rozhrani pro hru
 **/

#ifndef REVERSIGUI_H
#define REVERSIGUI_H

#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>
#include <QPixmap>
#include <QSignalMapper>
#include "gameinfo.h"
#include "aiplayer.h"

namespace Ui {
class reversigui;
}
///Trida pro graficke rozhrani
class reversigui : public QMainWindow
{
    Q_OBJECT

public:
    explicit reversigui(QWidget *parent = 0);
    ~reversigui();

private slots:
    void on_helpButton_clicked();

    void on_backToMenuButton_clicked();

    void on_newGameButton_clicked();

    void on_loadGameButton_clicked();

    void on_onePlayerButton_clicked();

    void on_twoPlayersButton_clicked();

    void on_easyAiButton_clicked();

    void on_hardAiButton_clicked();

    void on_x6SizeButton_clicked();

    void on_x8SizeButton_clicked();

    void on_x10SizeButton_clicked();

    void on_x12SizeButton_clicked();

    void changeIcon();

    void on_undoButton_clicked();

    void on_redoButton_clicked();

private:
    Ui::reversigui *ui; /**< hlavni cast GUI */

    bool players; /**< pocet hracu */
    int boardSize; /**< velikost herni plochy */
    std::string fileName; /**< Nazev souboru pro ukladani dat */
    int aiType; /**< typ protihrace */
    gameInfo* info; /**< hlavni trida hry */
    aiPlayer *ai; /**< hlavni trida AI */
    bool newOrSaved; /**< nova nebo nactena hra */
    bool undoDelete; /**< prepinac pro pouzivani undo */
    int topMove; /**< celkovy pocet tahu ve hre */

    QList<QPushButton*> playField; /**< herni plocha realizovana pomoci QPushButton */
    QPixmap blacktile; /**< pixmap pro cerne kameny */
    QPixmap whitetile; /**< pixmap pro bile kameny */
    QPixmap backg; /**< pixmap pro pozadi */
    QPixmap highlightedbackg; /**< pixmap pro zvyraznene pozadi */
    void allocateLabels();
    void playGame();
    void printBoard();

};

#endif // REVERSIGUI_H
