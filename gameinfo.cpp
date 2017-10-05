/**
 * @file gameinfo.cpp
 * @author Petr Flajsingr(xflajs00), Dominik Dvorak(xdvora1t)
 * @date 2 May 2016
 * @brief Soubor obsahujici definice funkci pro tridu gameInfo
 **/
#include "gameinfo.h"

/**
 * @brief Konstruktor tridy
 *
 * nastavuje hodnoty informaci podle parametru a uklada pocatecni hodnoty hry
 * @param size velikost herniho pole
 * @param player pocet hracu
 * @param file soubor pro ulozeni hry
 **/
gameInfo::gameInfo(int size, bool player, std::string file){
    //alokace pole pro herni plochu
    boardSize = size;
    board = new int*[boardSize];
    weightMap = new int*[boardSize];
    moveMap = new bool*[boardSize];
    for(int i = 0; i < boardSize; ++i){
        board[i] = new int[boardSize];
        memset(board[i], 0, sizeof(int) * boardSize);
        weightMap[i] = new int[boardSize];
        moveMap[i] = new bool[boardSize];
    }
    setWMap();
    //nastaveni pocatecniho stavu plochy
    int mid = boardSize / 2 - 1;
    board[mid][mid] = 1;
    board[mid + 1][mid + 1] = 1;
    board[mid + 1][mid] = 2;
    board[mid][mid + 1] = 2;
    //nastaveni pocatecnich hodnot
    players = player;
    moveCount = 0;
    checkScore();
    fileName = file;
    //otevreni souboru pro ulozeni hry
    saveFile.open(file, std::fstream::out);
    //ulozeni hlavicky
    saveHeader();
    saveMap();
}

/**
 * @brief Konstruktor tridy
 *
 * nastavuje objekt ze zadaneho savefile
 * @param file soubor pro nacteni a ulozeni hry
 **/
gameInfo::gameInfo(std::string file){
    fileName = file;
    saveFile.open(file, std::fstream::in);
    char check[100];
    memset(check, 0, sizeof(check));

    saveFile.read(check, 10);

    memset(check, 0, sizeof(check));
    saveFile.read(check, 2);
    boardSize = std::atoi(check);

    memset(check, 0, sizeof(check));
    saveFile.read(check, 6);

    memset(check, 0, sizeof(check));
    saveFile.read(check, 1);
    players = std::stoi(check, NULL, 10);

    board = new int*[boardSize];
    weightMap = new int*[boardSize];
    moveMap = new bool*[boardSize];
    for(int i = 0; i < boardSize; ++i){
        board[i] = new int[boardSize];
        weightMap[i] = new int[boardSize];
        moveMap[i] = new bool[boardSize];
    }
    moveCount = -1;
    while(loadMap(true) != false);
    setWMap();
    saveFile.close();
    checkScore();
    saveFile.open(file, std::fstream::app|std::fstream::out);
}

/**
 * @brief Destruktor tridy
 *
 * Dealokuje vsechnu vyuzitou pamet
 **/
gameInfo::~gameInfo(){
    for(int i = 0; i < boardSize; ++i){
        delete[] board[i];
        delete[] moveMap[i];
        delete[] weightMap[i];
    }
    delete[] board;
    delete[] moveMap;
    delete[] weightMap;
    saveFile.close();
}

/**
 * @brief Nastaveni barvy kamene
 * @param color barva kamene
 * @param x x souradnice
 * @param y y souradnice
 **/
void gameInfo::setStone(bool color, int x, int y){
    board[x][y] = color + 1;
}

/**
 * @brief Kontrola okolnich kamenu pro zmenu podle pravidel hry
 * @param color barva na kterou se meni kameny
 * @param x x souradnice
 * @param y y souradnice
 * @param mode typ kontroly, true - pri pridani kamene, false - vyhledavani pro mapu moznych tahu
 **/
bool gameInfo::checkBoard(bool color, int x, int y, bool mode){
    if(!mode && board[x][y] != 0){
        return false;
    }
    //kontrola dolu od kamene
    for(int i = x + 1; i < boardSize; ++i){
        if(getStone(i, y, M_BOARD) != 0){
            if(getStone(i, y, M_BOARD) == color + 1){
                if(mode){
                    changeRange(color, x, i, y, y);
                }else{
                    if(i - x > 1)
                        return true;
                }
                break;
            }
        }else{
            break;
        }
    }
    //kontrola vpravo od kamene
    for(int i = y + 1; i < boardSize; ++i){
        if(getStone(x, i, M_BOARD) != 0){
            if(getStone(x, i, M_BOARD) == color + 1){
                if(mode){
                    changeRange(color, x, x, y, i);
                }else{
                    if(i - y > 1)
                        return true;
                }
                break;
            }
        }else{
            break;
        }
    }
    //kontrola nahoru od kamene
    for(int i = x - 1; i >= 0; --i){
        if(getStone(i, y, M_BOARD) != 0){
            if(getStone(i, y, M_BOARD) == color + 1){
                if(mode){
                    changeRange(color, i, x, y, y);
                }else{
                    if(x - i > 1)
                        return true;
                }
                break;
            }
        }else{
            break;
        }
    }
    //kontrola vlevo od kamene
    for(int i = y - 1; i >= 0; --i){
        if(getStone(x, i, M_BOARD) != 0){
            if(getStone(x, i, M_BOARD) == color + 1){
                if(mode){
                    changeRange(color, x, x, i, y);
                }else{
                    if(y - i > 1)
                        return true;
                }
                break;
            }
        }else{
            break;
        }
    }
    //vpravo dolu
    for(int i = x + 1, j = y + 1; i < boardSize && j < boardSize; ++i, ++j){
        if(getStone(i, j, M_BOARD) != 0){
            if(getStone(i, j, M_BOARD) == color + 1){
                if(mode){
                    changeRange(color, x, i, y, j);
                }else{
                    if(i - x > 1 && j - y > 1){
                        return true;
                    }
                }
                break;
            }
        }else{
            break;
        }
    }
    //vpravo nahoru
    for(int i = x - 1, j = y + 1; i >= 0 && j < boardSize; --i, ++j){
        if(getStone(i, j, M_BOARD) != 0){
            if(getStone(i, j, M_BOARD) == color + 1){
                if(mode){
                    changeRange(color, x, i, y, j);
                }else{
                    if(x - i > 1 || y - j > 1)
                        return true;
                }
                break;
            }
        }else{
            break;
        }
    }
    //vlevo dolu
    for(int i = x + 1, j = y - 1; i < boardSize && j >= 0; ++i, --j){
        if(getStone(i, j, M_BOARD) != 0){
            if(getStone(i, j, M_BOARD) == color + 1){
                if(mode){
                    changeRange(color, x, i, y, j);
                }else{
                    if(x - i > 1 || y - j > 1)
                        return true;
                }
                break;
            }
        }else{
            break;
        }
    }
    //vlevo nahoru
    for(int i = x - 1, j = y - 1; i >= 0 && j >= 0; --i, --j){
        if(getStone(i, j, M_BOARD) != 0){
            if(getStone(i, j, M_BOARD) == color + 1){
                if(mode){
                    changeRange(color, x, i, y, j);
                }else{
                    if(x - i > 1 || y - j > 1)
                        return true;
                }
                break;
            }
        }else{
            break;
        }
    }
    return false;
}

/**
 * @brief Zjisteni barvy kamene na dane souradnici
 * @param x x souradnice
 * @param y y souradnice
 * @param map typ mapy, false - herni plocha, true - mozne tahy
 * @return barva kamene
 **/
int gameInfo::getStone(int x, int y, maps map){
    if(map == M_BOARD){
        return board[x][y];
    }else if(map == M_WEIGHT){
        return weightMap[x][y];
    }else if(map == M_MOVES){
        return moveMap[x][y];
    }
    return 0;
}

/**
 * Zmena barvy kamenu v rozsahu
 * @param color barva kamenu
 * @param x1 pocatecni x souradnice
 * @param x2 konecna x souradnice
 * @param y1 pocatecni y souradnice
 * @param y2 konecna y souradnice
 **/
void gameInfo::changeRange(bool color, int x1, int x2, int y1, int y2){
    if(y1 == y2){
        for(int i = x1 + 1; i < x2; ++i){
            setStone(color, i, y1);
        }
    }else if(x1 == x2){
        for(int i = y1 + 1; i < y2; ++i){
            setStone(color, x1, i);
        }
    }else if(x1 < x2 && y1 < y2){
        for(int i = x1 + 1, j = y1 + 1; i < x2 && j < y2; ++i, ++j){
            setStone(color, i, j);
        }
    }else if(x1 > x2 && y1 < y2){
        for(int i = x1 - 1, j = y1 + 1; i >= 0 && j < y2; --i, ++j){
            setStone(color, i, j);
        }
    }else if(x1 < x2 && y1 > y2){
        for(int i = x1 + 1, j = y1 - 1; i < x2 && j >= 0; ++i, --j){
            setStone(color, i, j);
        }
    }else if(x1 > x2 && y1 > y2){
        for(int i = x1 - 1, j = y1 - 1; i > x2 && j > y2; --i, --j){
            //std::cout << i << j <<std::endl;
            setStone(color, i, j);
        }
    }
}

/**
 * @brief Nastaveni mapy vah
 *
 * nastavi mapu vah podle hodnot jednotlivych bodu v rozmezi 0 - 3
 * kde 0 je nejhorsi ohodnoceni a 3 nejlepsi
 **/
void gameInfo::setWMap(){
    for(int i = 0; i < boardSize / 2; ++i){
        for(int j = 0; j < boardSize / 2; ++j){
            //std::cout << i << " " << j << std::endl;
            if(i == 0){
                if(j == 0 || j == 2){
                    set4(3, i, j);
                }else if(j == 1){
                    set4(2, i, j);
                }else{
                    set4(1, i, j);
                }
            }else if(i == 1){
                if(j == 0){
                    set4(1, i, j);
                }else if(j == 1){
                    set4(0, i, j);
                }else{
                    set4(2, i, j);
                }
            }else if(i == 2){
                if(j != 1){
                    set4(3, i, j);
                }else{
                    set4(2, i, j);
                }
            }else{
                if(j == 0 || j == 1){
                    set4(2, i, j);
                }else{
                    set4(3, i, j);
                }
            }
        }
    }
}

/**
 * @brief Nastaveni ctyr bodu pole na danou hodnotu
 * @param val Nastavovana hodnota
 * @param i x souradnice
 * @param j y souradnice
 **/
void gameInfo::set4(char val, int i, int j){
    weightMap[i][j] = weightMap[i][boardSize - j - 1] = weightMap[boardSize - i - 1][j] = weightMap[boardSize - i - 1][boardSize - j - 1] = val;
}

/**
 * @brief Ulozeni moznych pohybu do moveMap
 *
 * Vola funkci checkBoard pro vsechny pozice herniho pole a uklada navratovou hodnotu
 * true reprezentuje mozny pohyb, false nemozny
 * @param color barva kontrolovanych kamenu
 **/
bool gameInfo::checkMoves(bool color){
    bool ret = false;
    for(int i = 0; i < boardSize; ++i){
        for(int j = 0; j < boardSize; ++j){
            moveMap[i][j] = checkBoard(color, i, j, 0);
            if(moveMap[i][j]){
                ret = true;
            }
        }
    }
    return ret;
}

/**
 * @brief Tah hrace
 *
 * Prida informace o tahu do poli hry, provadi kontrolu platnosti tahu
 * @param color Barva pokladaneho kamene
 * @param x Souradnice x
 * @param y Souradnice y
 * @retval -1 Nemoznost pohybu
 * @retval 0 Nepovoleny pohyb
 * @retval 1 Krok proveden
 **/
int gameInfo::makeMove(bool color, int x, int y){
    if(!checkMoves(color)){
        moveCount++;
        return -1;
    }
    if(moveMap[x][y] == 1){
        setStone(color, x, y);
        checkBoard(color, x, y, 1);
        checkScore();
        saveMap();
        moveCount++;
        return 1;
    }else{
        return 0;
    }
}

/**
 * @brief Kontrola skore
 *
 * Funkce slouzici pro kontrolu skore jednotlivych hracu
 * prochazi herni plochu a pocita jejich kameny
 **/
void gameInfo::checkScore(){
    int counter1 = 0, counter2 = 0;
    for(int i = 0; i < boardSize; ++i){
        for(int j = 0; j < boardSize; ++j){
            if(board[i][j] == 1){
                counter1++;
            }else if(board[i][j] == 2){
                counter2++;
            }
        }
    }
    scorePlayer1 = counter1;
    scorePlayer2 = counter2;
}

/**
 * @brief Funkce pro ziskani bodu hrace
 *
 * @param player hrac, jehoz body chceme ziskat
 * @return pocet bodu hrace
 **/
int gameInfo::getScore(bool player){
    return player ? scorePlayer2 : scorePlayer1;
}

/**
 * @brief Ziskani cisla kola hry
 **/
int gameInfo::getRound(){
    return moveCount;
}

/**
 * @brief Ulozeni hlavicky saveFile
 *
 * Ukladane informace jsou velikost herni plochy a typ hry
 **/
void gameInfo::saveHeader(){
    std::string headerText = ("BOARDSIZE:");
    if(boardSize < 10)
        headerText += '0';
    headerText += std::to_string(boardSize) + " MODE:" + std::to_string(players);
    saveFile << headerText;
    saveFile.flush();
}

/**
 * @brief Ulozeni herni plochy
 **/
void gameInfo::saveMap(){
    saveFile << "\n\\\n";
    for(int i = 0; i < boardSize; ++i){
        for(int j = 0; j < boardSize; ++j){
            saveFile << board[i][j];
        }
    }
    saveFile.flush();
}

/**
 * @brief Nacteni mapy ze streamu
 *
 * Funkce nacte udaje mapy ze streamu a uklada je do aktualni mapy. Zaroven pocita ve kterem kroku se hra nachazi
 * @param mode prepinac pro pocitani kroku
 * @retval true vse ok
 * @retval false nenalezen dalsi zaznam
 **/
bool gameInfo::loadMap(bool mode){
    saveFile.ignore(1);
    char temp;
    saveFile.read(&temp, 1);
    if(temp == '\\'){
        if(mode)
            moveCount++;
    }else{
        return false;
    }
    saveFile.ignore(1);
    for(int i = 0; i < boardSize; ++i){
        for(int j = 0; j < boardSize; ++j){
            saveFile.read(&temp, 1);
            board[i][j] = temp - '0';
        }
    }
    return true;
}

/**
 * @brief Nacteni vyzadane mapy ze streamu
 *
 * Nacte n-tou mapu ze streamu za vyuziti funkce loadMap. Meni zapisovaci stream na cteci a po precteni dat zase zpet.
 * @param n Urceni kterou mapu nacist
 * @retval true vse ok
 * @retval false chybny pozadavek na nacteni
 **/
bool gameInfo::loadNthMap(int n){
    moveCount = n - 1;
    int counter = 0;
    if(n < 0){
        return false;
    }
    saveFile.close();
    saveFile.open(fileName, std::fstream::in);
    saveFile.ignore(17);
    while(counter <= n){
        /*if(!loadMap(0))
            break;*/
        loadMap(0);
        counter++;
    }
    saveFile.close();
    saveFile.open(fileName, std::fstream::out|std::fstream::app);
    checkScore();
    return true;
}

/**
 * @brief Smazani historie on urciteho kroku
 *
 * @param n krok, od ktereho se maze
 **/
void gameInfo::deleteHistory(int n){
    int counter = 0;
    char* buffer = new char[boardSize * boardSize];
    std::ofstream tempFile;
    saveFile.close();
    saveFile.open(fileName, std::fstream::in);
    tempFile.open(fileName + "~");
    //precteni hlavicky
    saveFile.read(buffer, 20);
    tempFile.write(buffer, 20);
    memset(buffer, 0, sizeof(char) * boardSize * boardSize);
    while(counter < n){
        saveFile.read(buffer, 2);
        if(strcmp(buffer, "\\\n") == 0){
            counter++;
        }else{
            break;
        }
        tempFile.write(buffer, 2);
        memset(buffer, 0, sizeof(char) * boardSize * boardSize);
        saveFile.read(buffer, boardSize * boardSize);
        tempFile.write(buffer, boardSize * boardSize);
        memset(buffer, 0, sizeof(char) * boardSize * boardSize);
        saveFile.ignore(1);
        if(counter != n)
            tempFile.write("\n", 1);
    }
    delete [] buffer;
    tempFile.close();
    saveFile.close();
    std::remove(fileName.c_str());
    std::rename((fileName + "~").c_str(), fileName.c_str());
    saveFile.open(fileName, std::fstream::app|std::fstream::out);
}

/**
 * @brief Predani velikosti herni plochy
 */
int gameInfo::getBoardSize(){
    return boardSize;
}

/**
 * @brief Predani poctu hracu
 */
bool gameInfo::getMode(){
    return players;
}
