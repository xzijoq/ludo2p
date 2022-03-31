

#pragma once
#include <array>
#include <string>

#include "core.h"
#include "gamestate.h"
#include "global.h"
#include "helper.h"
#include "u64def.h"

enum struct b_Piece : u64
{
    b_pece,
    b_current_sq,
    b_entry_sq,
    b_switch_sq,
    b_team,
    zb_piece_size

};

enum struct b_PieceFlags : u64
{
    b_ece_valid,
    b_ece_won,
    b_ece_start,
    b_ece_safe,
    zb_piece_flags_size
};

class Piece
{
   public:
    u64 mPiece = 0;

    void setAny( b_Piece what, u64 value );

    void setEce( u64 ece );
    void setEce( u64 plr, u64 pwn );
    u64  getEce() const;

    void setSq( u64 sq );
    u64  getSq() const;

    void setEntrySq( u64 sq );
    u64  getEntrySq() const;

    void setSwitchSq( u64 sq );
    u64  getSwitchSq() const;

    void setTeam( u64 team );
    u64  getTeam() const;

    u64 getPlr();
    u64 getAwn();

    void setFlag( b_PieceFlags flg, bool what );
    u64  getFlag( b_PieceFlags flg );

    void InitPiece( u64 ece, u64 sq, u64 entry_sq, u64 switch_sq ,u64 team);

    void                 testing();
    void                 CheckPiece( u64 crntSq, u64 crntPlr, u64 crntAwn );
    void                 CheckPiece( GameState gs );
    std::string          DebugString() const;
    inline consteval u64 setEntrySq1( u64 sq );
};
