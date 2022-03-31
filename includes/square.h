#pragma once
#include <array>
#include <string>

#include "core.h"
#include "global.h"
#include "helper.h"
#include "u64def.h"

enum struct b_Square : u64
{
    b_alleceSq,

    zb_sq_sz

};

enum struct b_SquareFlags : u64
{
    b_sq_valid,
    b_sq_safe,
    b_sq_empty,
    b_sq_start,
    b_sq_end,
    zSqFgSz
};
// 0-48 ece
class Square
{
   public:
    u64 mSquare = 0;

    void putEce( u64 ece );
    void popEce( u64 ece );

 

    u64 hasEce( u64 ece );
    u64 hasPlr( u64 plr ) const;

    void setFlag( b_SquareFlags flg, bool what );

    u64 getFlag( b_SquareFlags flg ) const;

    void        CheckSquare();
    std::string DebugString( u64 CrntPlr = Global::MAX_PLAYERS,
                             u64 CrntAwn = Global::MAX_PAWNS ) const;
};
// basically a bit mask for each ece
