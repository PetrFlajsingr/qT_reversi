/**
 * @file reversigui.cpp
 * @author Petr Flajsingr(xflajs00), Dominik Dvorak(xdvora1t)
 * @date 2 May 2016
 * @brief Soubor obsahujici definice funkci pro tridu reversiui
 **/

#include "reversigui.h"
#include "ui_reversigui.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include "aiplayer.h"
#include "gameinfo.h"
#include "savefiles.h"

/**
 * @brief konstruktor tridy
 */
reversigui::reversigui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::reversigui)
{
    ui->setupUi(this);
    ui->helpMessage->hide();
    ui->backToMenuButton->hide();
    ui->onePlayerButton->hide();
    ui->twoPlayersButton->hide();
    ui->diffChooseLabel->hide();
    ui->easyAiButton->hide();
    ui->hardAiButton->hide();
    ui->boardsizeLabel->hide();
    ui->x6SizeButton->hide();
    ui->x8SizeButton->hide();
    ui->x10SizeButton->hide();
    ui->x12SizeButton->hide();
    ui->undoButton->hide();
    ui->redoButton->hide();
    ui->turnLabel->hide();
    blacktile.load(":/images/blacktile.png");
    whitetile.load(":/images/whitetile.png");
    highlightedbackg.load(":/images/highlightedbackg.png");
    backg.load(":/images/backg.png");
    ui->quitGameButton->hide();
}
/**
 * @brief destruktor tridy
 */
reversigui::~reversigui()
{
    delete ui;
}

/**
 * @brief pri kliknuti na napovedu
 *
 * Nastavuje viditelnost dalsich objektu
 */
void reversigui::on_helpButton_clicked()
{
    ui->helpMessage->setVisible(true);
    ui->helpButton->hide();
    ui->exitButton->hide();
    ui->newGameButton->hide();
    ui->loadGameButton->hide();
    ui->backToMenuButton->setVisible(true);
    ui->gameNameLabel->hide();
}

/**
 * @brief pri kliknuti na zpet
 *
 * Nastavuje viditelnost dalsich objektu
 */
void reversigui::on_backToMenuButton_clicked()
{
    ui->helpMessage->hide();
    ui->helpButton->setVisible(true);
    ui->exitButton->setVisible(true);
    ui->newGameButton->setVisible(true);
    ui->loadGameButton->setVisible(true);
    ui->backToMenuButton->hide();
    ui->gameNameLabel->setVisible(true);
    ui->onePlayerButton->hide();
    ui->twoPlayersButton->hide();
    ui->diffChooseLabel->hide();
    ui->easyAiButton->hide();
    ui->hardAiButton->hide();
    ui->boardsizeLabel->hide();
    ui->x6SizeButton->hide();
    ui->x8SizeButton->hide();
    ui->x10SizeButton->hide();
    ui->x12SizeButton->hide();
}

/**
 * @brief pri kliknuti na Nova hra
 *
 * Nastavuje viditelnost dalsich objektu a prepinac newOrSaved
 */
void reversigui::on_newGameButton_clicked()
{
    ui->helpButton->hide();
    ui->exitButton->hide();
    ui->newGameButton->hide();
    ui->loadGameButton->hide();
    ui->backToMenuButton->setVisible(true);
    ui->onePlayerButton->setVisible(true);
    ui->twoPlayersButton->setVisible(true);
    newOrSaved = false;
}

/**
 * @brief pri kliknuti na Nacist hru
 *
 * Nastavuje viditelnost dalsich objektu, vyuziva QFileDialog pro vyber souboru
 * Pripravuje prepinac newOrSaved
 */
void reversigui::on_loadGameButton_clicked()
{
    ui->helpButton->hide();
    ui->exitButton->hide();
    ui->newGameButton->hide();
    ui->loadGameButton->hide();
    ui->backToMenuButton->setVisible(true);
    ui->gameNameLabel->hide();
    QString temp = QFileDialog::getOpenFileName(this, tr("Open savefile"), "./saves", tr("save.*") );
    fileName = temp.toUtf8().constData();
    if(fileName.length() > 4){
        newOrSaved = true;
        ui->backToMenuButton->hide();
        playGame();
    }else{
        ui->loadGameButton->setVisible(true);
        ui->helpButton->setVisible(true);
        ui->exitButton->setVisible(true);
        ui->newGameButton->setVisible(true);
        ui->loadGameButton->setVisible(true);
        ui->backToMenuButton->setVisible(true);
        ui->gameNameLabel->setVisible(true);
        ui->backToMenuButton->hide();
    }
}

/**
 * @brief pri kliknuti na Jeden hrac
 *
 * Nastavuje viditelnost dalsich objektu a prepinac players
 */
void reversigui::on_onePlayerButton_clicked()
{
    ui->gameNameLabel->hide();
    ui->diffChooseLabel->setVisible(true);
    ui->twoPlayersButton->hide();
    ui->onePlayerButton->hide();
    ui->easyAiButton->setVisible(true);
    ui->hardAiButton->setVisible(true);
    players = false;
}

/**
 * @brief pri kliknuti na Dva hraci
 *
 * Nastavuje viditelnost dalsich objektu a prepinac players
 */
void reversigui::on_twoPlayersButton_clicked()
{
    ui->gameNameLabel->hide();
    ui->twoPlayersButton->hide();
    ui->onePlayerButton->hide();
    players = true;
    ui->boardsizeLabel->setVisible(true);
    ui->x6SizeButton->setVisible(true);
    ui->x8SizeButton->setVisible(true);
    ui->x10SizeButton->setVisible(true);
    ui->x12SizeButton->setVisible(true);
}

/**
 * @brief pri kliknuti na Lehke
 *
 * Nastavuje viditelnost dalsich objektu a prepinac typu AI
 */
void reversigui::on_easyAiButton_clicked()
{
    ui->diffChooseLabel->hide();
    ui->easyAiButton->hide();
    ui->hardAiButton->hide();
    ui->boardsizeLabel->setVisible(true);
    aiType = 0;
    ui->x6SizeButton->setVisible(true);
    ui->x8SizeButton->setVisible(true);
    ui->x10SizeButton->setVisible(true);
    ui->x12SizeButton->setVisible(true);
}

/**
 * @brief pri kliknuti na Tezke
 *
 * Nastavuje viditelnost dalsich objektu a prepinac typu AI
 */
void reversigui::on_hardAiButton_clicked()
{
    ui->diffChooseLabel->hide();
    ui->easyAiButton->hide();
    ui->hardAiButton->hide();
    ui->boardsizeLabel->setVisible(true);
    aiType = 1;
    ui->x6SizeButton->setVisible(true);
    ui->x8SizeButton->setVisible(true);
    ui->x10SizeButton->setVisible(true);
    ui->x12SizeButton->setVisible(true);
}

/**
 * @brief pri kliknuti na 6x6
 *
 * Nastavuje viditelnost dalsich objektu a velikost herni plochy. Zapina samotnou hru
 */
void reversigui::on_x6SizeButton_clicked()
{
    ui->diffChooseLabel->hide();
    ui->easyAiButton->hide();
    ui->hardAiButton->hide();
    ui->boardsizeLabel->hide();
    ui->x6SizeButton->hide();
    ui->x8SizeButton->hide();
    ui->x10SizeButton->hide();
    ui->x12SizeButton->hide();
    ui->backToMenuButton->hide();
    boardSize = 6;
    playGame();
}

/**
 * @brief pri kliknuti na 8x8
 *
 * Nastavuje viditelnost dalsich objektu a velikost herni plochy. Zapina samotnou hru
 */
void reversigui::on_x8SizeButton_clicked()
{
    ui->diffChooseLabel->hide();
    ui->easyAiButton->hide();
    ui->hardAiButton->hide();
    ui->boardsizeLabel->hide();
    ui->x6SizeButton->hide();
    ui->x8SizeButton->hide();
    ui->x10SizeButton->hide();
    ui->x12SizeButton->hide();
    ui->backToMenuButton->hide();
    boardSize = 8;
    playGame();
}

/**
 * @brief pri kliknuti na 10x10
 *
 * Nastavuje viditelnost dalsich objektu a velikost herni plochy. Zapina samotnou hru
 */
void reversigui::on_x10SizeButton_clicked()
{
    ui->diffChooseLabel->hide();
    ui->easyAiButton->hide();
    ui->hardAiButton->hide();
    ui->boardsizeLabel->hide();
    ui->x6SizeButton->hide();
    ui->x8SizeButton->hide();
    ui->x10SizeButton->hide();
    ui->x12SizeButton->hide();
    boardSize = 10;
    ui->backToMenuButton->hide();
    playGame();
}

/**
 * @brief pri kliknuti na 12x12
 *
 * Nastavuje viditelnost dalsich objektu a velikost herni plochy. Zapina samotnou hru
 */
void reversigui::on_x12SizeButton_clicked()
{
    ui->diffChooseLabel->hide();
    ui->easyAiButton->hide();
    ui->hardAiButton->hide();
    ui->boardsizeLabel->hide();
    ui->x6SizeButton->hide();
    ui->x8SizeButton->hide();
    ui->x10SizeButton->hide();
    ui->x12SizeButton->hide();
    boardSize = 12;
    ui->backToMenuButton->hide();
    playGame();
}

/**
 * @brief Alokace potrebne pameti
 *
 * Alokuje playField pro herni plochu. Propojuje signaly z herni plochy do handleru "changeIcon".
 * Nastavuje labely a tlacitka na potrebne hodnoty.
 */
void reversigui::allocateLabels(){
    int x = 0, y = 0;
    QString labelText1;
    QString labelText2;

    for(int i = 0; i < info->getBoardSize() * info->getBoardSize(); ++i){
        playField << new QPushButton(this);
        playField.at(i)->setGeometry(QRect(x * 50 + 50, y * 50 + 50, 50, 50));
        playField.at(i)->setIcon(backg);
        playField.at(i)->setIconSize(QSize(50, 55));
        playField.at(i)->setFlat(true);
        playField.at(i)->show();
        connect(playField.at(i), SIGNAL(clicked()), this, SLOT(changeIcon()));
        x++;
        if((i + 1) % info->getBoardSize() == 0 && i){
            x = 0;
            labelText1.append("<p style=\"line-height:88%\">"+ QString::number(y + 1) + "</p>");
            labelText2.append(('A' + y));
            labelText2.append("  ");
            y++;
        }
    }
    ui->numLocLabel->setText(labelText1);
    ui->alphaLocLabel->setText(labelText2);
    ui->scoreLabel->setGeometry(QRect(info->getBoardSize() * 50 + 50, 50, 150, 400));
    ui->scoreLabel->setText("Skore:\nPrvni hrac\n" + QString::number(info->getScore(0)) + "\nDruhy hrac\n" + QString::number(info->getScore(1)));
    info->checkMoves(info->getRound() % 2);
    ui->undoButton->setGeometry(QRect(info->getBoardSize() * 50 + 200, 150, 80, 80));
    ui->redoButton->setGeometry(QRect(info->getBoardSize() * 50 + 200, 250, 80, 80));
    ui->undoButton->setVisible(true);
    ui->redoButton->setVisible(true);
    ui->turnLabel->setGeometry(QRect(50, info->getBoardSize() *50 + 50, 300, 50));
    ui->turnLabel->setText("Na tahu je cerny");
    ui->quitGameButton->setGeometry(QRect(info->getBoardSize() * 50 + 200, info->getBoardSize() *50 + 50, 150, 50));
    ui->quitGameButton->setVisible(true);
    ui->turnLabel->setVisible(true);
}

/**
 * @brief Zapnuti hry
 *
 * Pripravuje objekt gameInfo a aiPlayer. Vola alokace a tisk herni plochy
 */
void reversigui::playGame(){
    if(!newOrSaved){
        fileName = newSaveFile(getNumberOfNextSave());
        info = new gameInfo(boardSize, players, fileName);
        if(!info->getMode())
            ai = new aiPlayer(aiType);
        allocateLabels();
        printBoard();
    }else{
        info = new gameInfo(fileName);
        if(!info->getMode())
            ai = new aiPlayer(1);
        allocateLabels();
        printBoard();
    }
}

/**
 * @brief Tisk herni plochy
 *
 * Prochazi informace o hre pomoci gameinfo->getStone() a meni podle nich herni plochu
 */
void reversigui::printBoard(){;
    int temp = 0;
    for(int i = 0; i < info->getBoardSize(); ++i){
        for(int j = 0; j < info->getBoardSize(); ++j){
            if((temp = info->getStone(i, j, gameInfo::M_BOARD)) == 1){
                playField.at(i * info->getBoardSize() + j)->setIcon(blacktile);
            }else if(temp == 2){
                playField.at(i * info->getBoardSize() + j)->setIcon(whitetile);
            }else{
                if(info->getStone(i, j, gameInfo::M_MOVES) == 0)
                    playField.at(i * info->getBoardSize() + j)->setIcon(backg);
                else
                    playField.at(i * info->getBoardSize() + j)->setIcon(highlightedbackg);
            }
        }
    }
}

/**
 * @brief Handler kliknuti do herni plochy
 *
 * Zpracovava vyber pozice pro dalsi tah hry. Provadi kontrolu platnosti tahu.
 * Vypisuje skore.
 */
void reversigui::changeIcon(){
    if(info->getMode()){
        if(info->getRound() % 2){
            ui->turnLabel->setText("Na tahu je cerny");
        }else{
            ui->turnLabel->setText("Na tahu je bily");
        }
    }
    QPushButton *temp = qobject_cast<QPushButton *>(sender());
    QMessageBox msg;
    bool skip = false;
    bool check = false;
    int temp2 = 0;
    int x = 0, y = 0;
    for(int i = 0; i < info->getBoardSize(); ++i){
        for(int j = 0; j < info->getBoardSize(); ++j){
            if(playField.at(i * info->getBoardSize() + j) == temp){
                x = i;
                y = j;
                break;
            }
        }
    }
    if((temp2 = info->makeMove(info->getRound() % 2, x, y)) == 0){
        msg.setText("Neplatný pohyb");
        msg.exec();
        skip=false;
        check = true;
    }else if(temp2 == -1){
        msg.setText("Nemožnost pohybu");
        msg.exec();
        skip = true;
    }
    if(temp2 != -1){
        if(undoDelete){
            info->deleteHistory(info->getRound() + 1);
            undoDelete = false;
        }
    }
    if((temp2 == -1 || temp2 == 1) && !check){
        if(!info->getMode()){
            ai->aiMove(x, y, *info);
            temp2 = info->makeMove(info->getRound() % 2, x, y);
        }
    }
    ui->scoreLabel->setText("Skore:\nPrvni hrac\n" + QString::number(info->getScore(0)) + "\nDruhy hrac\n" + QString::number(info->getScore(1)));
    if((info->getScore(0) == 0 || info->getScore(1) == 0) || (info->checkMoves(info->getRound() % 2) == false && temp2 == -1) || (info->getScore(0) + info->getScore(1) == info->getBoardSize() * info->getBoardSize()) || (skip && temp2 == -1) ){
        QString winmsg = ("Konec hry!\nVyhrává:\n");
        winmsg +=  (info->getScore(0) > info->getScore(1)) ? "hrac 1" : "hrac 2";
        msg.setText(winmsg);
        msg.exec();

        QApplication::quit();
    }
    printBoard();
}

/**
 * @brief pri kliknuti na undo
 *
 * Vraci se ve hre o krok zpet. Kontroluje moznost vyuzit undo a pripadne vypise chybovou hlasku.
 */
void reversigui::on_undoButton_clicked()
{
    if(!undoDelete){
        topMove = info->getRound();
    }
    undoDelete = true;
    QMessageBox msg;
    msg.setText("Nelze");
    if(info->getRound() == 0){
        msg.exec();
    }else{
        if(info->getMode()){
            if(!info->loadNthMap(info->getRound())){
                msg.setText("Nelze");
                msg.exec();
            }
            if(info->getRound() % 2){
                ui->turnLabel->setText("Na tahu je bily");
            }else{
                ui->turnLabel->setText("Na tahu je cerny");
            }
        }
        else{
            if(!info->loadNthMap(info->getRound() - 1)){
                msg.setText("Nelze");
                msg.exec();
            }
        }
        info->checkMoves(info->getRound() % 2);
        ui->scoreLabel->setText("Skore:\nPrvni hrac\n" + QString::number(info->getScore(0)) + "\nDruhy hrac\n" + QString::number(info->getScore(1)));
        printBoard();
    }
}

/**
 * @brief pri kliknuti na redo
 *
 * Vraci se ve hre o krok zpet. Kontroluje moznost vyuzit redo a pripadne vypise chybovou hlasku.
 */
void reversigui::on_redoButton_clicked()
{
    QMessageBox msg;
    msg.setText("Nelze");
    if(undoDelete && topMove > info->getRound()){
        if(info->getMode()){
            if(!info->loadNthMap(info->getRound() + 2)){
                msg.exec();
            }
            if(info->getRound() % 2){
                ui->turnLabel->setText("Na tahu je bily");
            }else{
                ui->turnLabel->setText("Na tahu je cerny");
            }
        }else{
            if(!info->loadNthMap(info->getRound() + 3)){
                msg.exec();
            }
        }
        info->checkMoves(info->getRound() % 2);
        printBoard();
        info->checkMoves(info->getRound() % 2);
        ui->scoreLabel->setText("Skore:\nPrvni hrac\n" + QString::number(info->getScore(0)) + "\nDruhy hrac\n" + QString::number(info->getScore(1)));
    }else{
        msg.exec();
    }
}
