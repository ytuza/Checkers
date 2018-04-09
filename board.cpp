#include "board.h"
#include "checkersbox.h"
#include "game.h"

extern Game *game;
Board::Board()
{
    setUpBlack();
    setUpWhite();
}
void Board::drawBoxes(int x,int y)
{
    int SHIFT = 100;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            CheckersBox *box = new CheckersBox();
            game->collection[i][j] = box;
            box->rowLoc = i;
            box->colLoc = j;
            box->setPos(x+SHIFT*j,y+SHIFT*i);
            if((i+j)%2==0)
                box->setOriginalColor(Qt::lightGray);
            else
                box->setOriginalColor(Qt::darkGray);
            game->addToScene(box);



        }
    }

}



void Board::addChessPiece() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {

            CheckersBox *box =game->collection[i][j];
            if(((i == 0 || i == 2) && (j % 2 != 0)) || (i==1 && j % 2 == 0)) {
                static int k;
                box->placePiece(black[k]);
                game->alivePiece.append(black[k]);
                game->addToScene(black[k++]);
            }
            if(((i == 7 || i == 5) && (j % 2 == 0)) || (i==6 && j % 2 != 0)) {
                static int h;
                box->placePiece(white[h]);
                game->alivePiece.append(white[h]);
                game->addToScene(white[h++]);
            }

        }
    }
}

void Board::setUpWhite()
{
   Piece *piece;
    for(int i = 0; i < 12; i++) {
        piece = new Piece("WHITE");
        white.append(piece);
    }

}

void Board::setUpBlack()
{
    Piece *piece;
    for(int i = 0; i < 12; i++) {
        piece = new Piece("BLACK");
        black.append(piece);
    }
}


void Board::reset() {
    //int k = 0; int h = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {

            CheckersBox *box =game->collection[i][j];
            box->setHasCheckersPiece(false);
            box->setCheckersPieceColor("NONE");
            box->currentPiece = NULL;

            if(((i == 0 || i == 2) && (j % 2 != 0)) || (i==1 && j % 2 == 0)) {
                static int k;
                box->placePiece(black[k]);
                black[k]->setIsPlaced(true);
                black[k]->firstMove = true;
                game->alivePiece.append(black[k++]);
            }
            if(((i == 7 || i == 5) && (j % 2 == 0)) || (i==6 && j % 2 != 0)) {
                static int h;
                box->placePiece(white[h]);
                white[h]->setIsPlaced(true);
                white[h]->firstMove = true;
                game->alivePiece.append(white[h++]);
            }


        }
    }
}
