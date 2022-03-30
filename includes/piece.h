

#pragma once
#include <array>
#include <string>

#include "core.h"
#include "gamestate.h"
#include "global.h"
#include "helper.h"
#include "u64def.h"


enum struct b_PieceLayout : u64
{
    b_ece,
    b_current_sq,
    b_entry_sq,
    b_switch_sq,
    zly_size

};

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
    u64 mPiece = 0;

    void setAny(b_PieceLayout what, u64 value);

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

    void InitPiece( u64 ece, u64 sq, u64 entry_sq, u64 switch_sq );


    void        testing();
    void        CheckPiece( u64 crntSq, u64 crntPlr, u64 crntAwn );
    void        CheckPiece( GameState gs );
    std::string DebugString() const;
    inline consteval u64 setEntrySq1( u64 sq );
};

enum struct b_PieceLayout1 : u64
{
    b_ece,
    b_current_sq,
    b_entry_sq,
    b_switch_sq,
    zly_size

};

constexpr std::array<u64, (u64)b_PieceLayout1::zly_size>
    b_SzOf_PieLay1  // %order matters
    {
        //% MUST MATCH b_PieceLayout Enum ABOVE
        Global::ECE_SZb,  //*   b_ece,
        Global::SQ_SZb,   //*   b_current_sq,
        Global::SQ_SZb,   //*   b_entry_sq,
        Global::SQ_SZb    //*   b_switch_sq,
    };

static consteval u64 b_frm1( const b_PieceLayout1 inx )
{
    u64 result = 0;
    for ( auto i = 0; i < (u64)inx; i++ ) { result += b_SzOf_PieLay1[(u64)i]; }
    return result;
}

inline consteval u64 Piece::setEntrySq1( u64 sq )
{
    return SetBits( mPiece, sq, b_frm1( b_PieceLayout1::b_entry_sq ),
             b_SzOf_PieLay1[(u64)b_PieceLayout1::b_entry_sq] );
}
inline consteval u64 setEntrySq2( u64 mPiece,u64 sq )
{
    return SetBits( mPiece, sq, b_frm1( b_PieceLayout1::b_entry_sq ),
             b_SzOf_PieLay1[(u64)b_PieceLayout1::b_entry_sq] );
}
