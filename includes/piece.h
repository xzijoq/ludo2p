#pragma once
#include <global.h>

#include <string>
struct op
{
    int from;
    int size;
};

//% PieceNum  | Square  | Entry Sq | Switch Sq |
//% 0-5(6:64) | 6-12(7) | 13-19(7) | 20-26(7)  |
//@ Valid | Won |
//@  64   | 63  |
class Piece
{
   public:
    u64         mEce=0;
    static u64 getEce(u64 ply, u64 awn);



    void        setEce( u64 );
    void        setEce( u64,u64 );
    //void setSq();


    u64         getPlr();
    u64         getAwn();
    u64         getEce();

    void        CheckPiece();
    std::string DebugString() const;
};

//$ is safe,