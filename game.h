#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <board.h>
#include "piece.h"
class Game:public QGraphicsView
{
    Q_OBJECT
public:
    //Constructors
    Game(QWidget *parent = 0);

    //public Methods

    void drawDeadHolder(int x, int y, QColor color);

    void displayDeadWhite();
    void displayDeadBlack();

    void drawCheckersBoard();

    void placeInDeadPlace(Piece *piece);

    //Scene Related
    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);

    //getters/setters
    Piece *pieceToMove;

    QString getTurn() ;
    void setTurn( QString value);
    void changeTurn();



    CheckersBox *collection[8][8];

    QGraphicsTextItem *check;
    QList <Piece *> alivePiece;

    void displayMainMenu();
    void gameOver();
    void removeAll();
public slots:
    void start();
private:
    QGraphicsScene *gameScene;
    QList <Piece *> whiteDead;
    QList <Piece *> blackDead;
    QGraphicsRectItem * deadHolder;
    QString turn;
    Board *checkers;
    QList <QGraphicsItem *> listG;
    QGraphicsTextItem * turnDisplay;


};

enum class Player {
  player0 = 0,
  player1 = 1,
  nothing = 2
};

#endif // GAME_H
