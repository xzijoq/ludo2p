#pragma once
#include <global.h>

#include <string>
using namespace Global;

enum struct b_PieceFlags : u64
{
    b_ece_valid,
    b_ece_won,
    b_ece_start,
    b_ece_safe,
    z_PieceFlagsSize
};

class Piece
{
   public:
    u64        mPiece = 0;


    void setEce( u64 ece );
    void setEce( u64 plr, u64 pwn );
    u64  getEce() const;

    void setSq( u64 sq );
    u64  getSq() const;

    void setEntrySq( u64 sq );
    u64  getEntrySq() const;
 

    void setSwitchSq( u64 sq );
    u64  getSwitchSq() const;

    u64 getPlr();
    u64 getAwn();

    void setFlag( b_PieceFlags flg, bool what );
    u64  getFlag( b_PieceFlags flg );

    void InitPiece(u64 ece,u64 sq,u64 entry_sq,u64 switch_sq);

    void        testing();
    void        CheckPiece();
    std::string DebugString() const;
};

//$ is safe,