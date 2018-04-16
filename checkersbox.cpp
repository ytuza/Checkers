#include "checkersbox.h"
#include "game.h"
#include <QDebug>


extern Game *game;

CheckersBox::CheckersBox(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    //making the Square CHess Box
    setRect(0,0,100,100);
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    setHasCheckersPiece(false);
    setCheckersPieceColor("NONE");
    currentPiece = NULL;
}


void CheckersBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
      //  qDebug() << getChessPieceColor();
        //Deselecting counter part of CheckersPiece
        if(currentPiece == game->pieceToMove && currentPiece){

            currentPiece->mousePressEvent(event);
            return;
        }

        //if selected
        if(game->pieceToMove){
            //if same team
            if(this->getCheckersPieceColor() == game->pieceToMove->getSide())
                return;
            //removing the eaten piece
            QList <CheckersBox *> movLoc = game->pieceToMove->moveLocation();
            //TO make sure the selected box is in move zone
            int check = 0;
            for(size_t i = 0, n = movLoc.size(); i < n;i++) {
                if(movLoc[i] == this) {
                    check++;

                }
            }
            // if not prsent return
            if(check == 0)
                return;
            //change the color back to normal
             game->pieceToMove->decolor();
             //make the first move false applicable for pawn only
             game->pieceToMove->firstMove = false;
             //this is to eat or consume the enemy present inn the movable region

             int row = (game->pieceToMove)->getCurrentBox()->rowLoc;
             int col = (game->pieceToMove)->getCurrentBox()->colLoc;

            if((row+(this->rowLoc)) % 2 == 0 && (col+(this->colLoc)) % 2 == 0){
                int trow = (row+(this->rowLoc))/2;
                int tcol = (col+(this->colLoc))/2;
                game->collection[trow][tcol]->currentPiece->setIsPlaced(false);
                game->collection[trow][tcol]->currentPiece->setCurrentBox(NULL);
                game->placeInDeadPlace(game->collection[trow][tcol]->currentPiece);

                game->collection[trow][tcol]->currentPiece=NULL;
                game->collection[trow][tcol]->setHasCheckersPiece(false);

            }
            //changing the new stat and resetting the previous left region
            game->pieceToMove->getCurrentBox()->setHasCheckersPiece(false);
            game->pieceToMove->getCurrentBox()->currentPiece = NULL;
            game->pieceToMove->getCurrentBox()->resetOriginalColor();
            placePiece(game->pieceToMove);

            game->pieceToMove = NULL;
            //changing turn
            game->changeTurn();
            checkForCheck();
        }
        //Selecting couterpart of the chessPiece
        else if(this->getHasCheckersPiece())
        {
            this->currentPiece->mousePressEvent(event);
        }

        //qDebug("paltas");
}



void CheckersBox::setColor(QColor color)
{
    brush.setColor(color);
    setBrush(color);
}

void CheckersBox::placePiece(Piece *piece)
{

    piece->setPos(x()+50- piece->pixmap().width()/2  ,y()+50-piece->pixmap().width()/2);
    piece->setCurrentBox(this);
    setHasCheckersPiece(true,piece);
    currentPiece = piece;


}

void CheckersBox::resetOriginalColor()
{
    setColor(originalColor);
}



void CheckersBox::setOriginalColor(QColor value)
{
    originalColor = value;
    setColor(originalColor);
}

bool CheckersBox::getHasCheckersPiece()
{
    return hasChessPiece;
}

void CheckersBox::setHasCheckersPiece(bool value, Piece *piece)
{
    hasChessPiece = value;
    if(value)
        setCheckersPieceColor(piece->getSide());
    else
        setCheckersPieceColor("NONE");
}

void CheckersBox::checkForCheck()
{
    int c = 0;
    QList <Piece *> pList = game->alivePiece;
    game->check->setVisible(false);
    for(size_t i = 0,n=pList.size(); i < n; i++ )
    pList[i]->getCurrentBox()->resetOriginalColor();

}


QString CheckersBox::getCheckersPieceColor()
{
    return chessPieceColor;
}

void CheckersBox::setCheckersPieceColor(QString value)
{
    chessPieceColor = value;
}
