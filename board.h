#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QGraphicsRectItem>
#include "piece.h"
class Board
{
public:
    Board();

    //drawing public function
    void drawBoxes(int x, int y);

    void setUpWhite();
    void setUpBlack();



    void addChessPiece();
    void reset();
private:
    QList <Piece *> white;
    QList <Piece *> black;



};

#endif // CHESSBOARD_H
