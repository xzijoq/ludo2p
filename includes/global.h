#pragma once
//$short is-- player:plr || pawn:awn || piece:ece --for better readability
#include <sys/types.h>
#include <cstdint>
#include "u64def.h"

#ifdef NDEBUG
    #undef NDEBUG
#endif
#include <cassert>
namespace Global
{
inline consteval u64 ceillog2( u64 num )
{
    for ( u64 i = 0; i < 63; i++ )
    {
        if ( num <= ( (u64)1 << i ) ) { return i; }
    }
    return 0;
}


inline constexpr u64 MAX_SQUARES = 128;
inline constexpr u64 SQ_SZb      = Global::ceillog2( MAX_SQUARES );

inline constexpr u64 MAX_PIECE_COUNT = 48;
inline constexpr u64 ECE_SZb = ceillog2( MAX_PIECE_COUNT );

inline constexpr u64 MAX_ROLL = 48;
inline constexpr u64 ROLL_SZb = ceillog2( MAX_ROLL);

inline constexpr u64 MAX_PLAYERS     = 8;
inline constexpr u64 MAX_PAWNS       = 6;

inline constexpr u64 MAX_TEAMS =8;
inline constexpr u64  TEAM_SZb=Global::ceillog2( MAX_TEAMS);



//$ storage size in bits

inline u64 GetEce( u64 pl, u64 awn )
{
    assert( pl < MAX_PLAYERS && awn < MAX_PAWNS);
    u64 result = MAX_PAWNS * pl + awn;

    assert( result < MAX_PIECE_COUNT );
    return result;
}

}  // namespace Global

// inline consteval u64  GetEce( u64 pl, u64 awn )
//{
//     assert( pl < CURRENT_PLAYERS && awn < CURRENT_PAWNS );
//     u64 result = CURRENT_PAWNS * pl + awn;
//
//     assert( result < MAX_PIECE_COUNT );
//     return result;
// }