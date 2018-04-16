#include "piece.h"
#include "game.h"
#include <QDebug>
//#include "king.h"

extern Game *game;
Piece::Piece(QString team, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    side = team;
    isPlaced = true;
    firstMove = true;
    setImage();
}

CheckersBox *Piece::getCurrentBox()
{
    return currentBox;
}


void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Deselect
    if(this == game->pieceToMove){
        game->pieceToMove->getCurrentBox()->resetOriginalColor();
        game->pieceToMove->decolor();
        game->pieceToMove = NULL;
       return;
    }
    //if it is already consumed or not the respective color's turn
    if((!getIsPlaced() )|| ( (game->getTurn() != this->getSide())&& (!game->pieceToMove)) )
        return;
    //selecting
    if(!game->pieceToMove){

        game->pieceToMove = this;
        game->pieceToMove->getCurrentBox()->setColor(Qt::red);
        game->pieceToMove->moves();
    }
    //Consuming counterPart of the CHeckersBox
    else if(this->getSide() != game->pieceToMove->getSide()){
        this->getCurrentBox()->mousePressEvent(event);
    }


}

void Piece::setCurrentBox(CheckersBox *box)
{

    currentBox = box;
}


QString Piece::getSide()
{
    return side;
}

void Piece::setSide( QString value)
{
    side = value;
}

bool Piece::getIsPlaced()
{
    return isPlaced;
}

void Piece::setIsPlaced(bool value)
{
    isPlaced = value;

}
QList<CheckersBox *> Piece::moveLocation()
{
    return location;
}
void Piece::decolor()
{
    for(size_t i = 0, n = location.size(); i < n;i++) {
         location[i]->resetOriginalColor();
    }
}

void Piece::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/images/white.png"));
    else
        setPixmap(QPixmap(":/images/black.png"));
}

void Piece::moves()
{
    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();


    if(side == "WHITE"){

        if(col > 1 && row > 1 && game->collection[row-1][col-1]->getCheckersPieceColor() == "BLACK" && (!game->collection[row-2][col-2]->getHasCheckersPiece())) {
            location.append(game->collection[row-2][col-2]);
            boxSetting(location.last());
        }
        if(col < 6 && row > 1 && game->collection[row-1][col+1]->getCheckersPieceColor() == "BLACK" && (!game->collection[row-2][col+2]->getHasCheckersPiece())) {
            location.append(game->collection[row-2][col+2]);
            boxSetting(location.last());
        }
        if(col > 0 && row > 0 && (!game->collection[row-1][col-1]->getHasCheckersPiece())) {
            location.append(game->collection[row-1][col-1]);
            boxSetting(location.last());
        }
        if(col < 7 && row > 0 && (!game->collection[row-1][col+1]->getHasCheckersPiece())) {
            location.append(game->collection[row-1][col+1]);
            boxSetting(location.last());
        }



    }else{
      //For downward right

        if(col > 1 && row < 6 && game->collection[row+1][col-1]->getCheckersPieceColor() == "WHITE" && (!game->collection[row+2][col-2]->getHasCheckersPiece())) {
            location.append(game->collection[row+2][col-2]);
            boxSetting(location.last());
        }
        if(col < 6 && row < 6 && game->collection[row+1][col+1]->getCheckersPieceColor() == "WHITE" && (!game->collection[row+2][col+2]->getHasCheckersPiece())) {
            location.append(game->collection[row+2][col+2]);
            boxSetting(location.last());
        }
        if(col > 0 && row < 7 && (!game->collection[row+1][col-1]->getHasCheckersPiece())) {
            location.append(game->collection[row+1][col-1]);
            boxSetting(location.last());
        }
        if(col < 7 && row < 7 && (!game->collection[row+1][col+1]->getHasCheckersPiece())) {
            location.append(game->collection[row+1][col+1]);
            boxSetting(location.last());
        }
     }

}



bool Piece::boxSetting(CheckersBox *box)
{
    if(box->getHasCheckersPiece()) {
            box->setColor(Qt::red);
        return true;
    }
    else
        location.last()->setColor(Qt::darkRed);
    return false;
}

