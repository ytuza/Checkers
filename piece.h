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
    void setImage();

    bool getIsPlaced() ;
    void setIsPlaced(bool value);

    QList <CheckersBox *> moveLocation();
    void moves();
    void decolor();


    bool firstMove;
    bool isPlaced;
    bool boxSetting(CheckersBox *box);
protected:
    CheckersBox *currentBox;
    QString side;

    QList <CheckersBox *> location;

};
#endif // PIECE_H
