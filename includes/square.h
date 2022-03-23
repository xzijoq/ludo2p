#pragma once
#include "piece.h"

class Square
{
   public:
    bool hasPlayer(int plr);
    bool hasPiece(Piece ece);
    void hasPlAwn(int plr, int awn);

    void insertPiece(Piece ece);
    

    void CheckSquare();
    std::string DebugString() const;
};