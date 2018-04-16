#ifndef CHECKERSBOX_H
#define CHECKERSBOX_H

#include <QGraphicsRectItem>
#include <QBrush>
#include "piece.h"
#include <QGraphicsSceneMouseEvent>

class Piece;
class CheckersBox:public QGraphicsRectItem
{
public:
    CheckersBox(QGraphicsItem *parent=0);

    //public member function

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setColor(QColor color);
    void placePiece(Piece *piece);


    bool getHasCheckersPiece();
    void setHasCheckersPiece(bool value,Piece *piece = 0);

    void checkForCheck();

    void setOriginalColor(QColor value);
    void resetOriginalColor();

    QString getCheckersPieceColor() ;
    void setCheckersPieceColor(QString value);

    int rowLoc;
    int colLoc;

    Piece * currentPiece;

private:
    QBrush brush;
    QColor originalColor;
    bool hasChessPiece;
    QString chessPieceColor;


};


#endif // CHECKERSBOX_H
