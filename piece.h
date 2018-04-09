#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QGraphicsPixmapItem>
#include "checkersbox.h"
#include <QGraphicsSceneMouseEvent>

class CheckersBox;
class Piece:public QGraphicsPixmapItem
{
public:
    Piece(QString team = "",QGraphicsItem *parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setCurrentBox(CheckersBox *box);

    CheckersBox *getCurrentBox() ;

    QString getSide() ;
    void setSide( QString value);
    virtual void setImage() = 0;

    bool getIsPlaced() ;
    void setIsPlaced(bool value);

    QList <CheckersBox *> moveLocation();
    virtual void moves() = 0;
    void decolor();

    bool firstMove;

    //bool boxSetting(ChessBox *box);
protected:
    CheckersBox *currentBox;
    QString side;
    bool isPlaced;
    QList <CheckersBox *> location;

};
#endif // PIECE_H
