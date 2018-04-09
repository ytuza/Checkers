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
    //Consuming counterPart of the CHessBox
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
    //For upper Left

     for(int i = row-1,j = col-1; i >= 0 && j >=0; i--,j--) {
       if(game->collection[i][j]->getCheckersPieceColor() == team ) {
           break;

       }
       else
       {
           location.append(game->collection[i][j]);
           if(boxSetting(location.last()) ){
               break;
           }
       }
    }

     //For upper right

      for(int i = row-1,j = col+1; i >= 0 && j <= 7; i--,j++) {
        if(game->collection[i][j]->getCheckersPieceColor() == team ) {
            break;

        }
        else
        {
            location.append(game->collection[i][j]);
            if(boxSetting(location.last())){
                break;
            }
        }
     }

      //For downward right

       for(int i = row+1,j = col+1; i <= 7 && j <= 7; i++,j++) {
         if(game->collection[i][j]->getCheckersPieceColor() == team ) {
             break;

         }
         else
         {
             location.append(game->collection[i][j]);
             if(boxSetting(location.last())){
                 break;
             }
         }
      }

       //For downward left

        for(int i = row+1,j = col-1; i <= 7 && j >= 0; i++,j--) {
          if(game->collection[i][j]->getCheckersPieceColor() == team ) {
              break;

          }
          else
          {
              location.append(game->collection[i][j]);
              if(boxSetting(location.last())){
                  break;
              }

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

