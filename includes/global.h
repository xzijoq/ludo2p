
#pragma once
//$short is-- player:plr || pawn:awn || piece:ece --for better readability
#include <sys/types.h>

#include <cstdint>

#ifdef NDEBUG
    #undef NDEBUG
#endif
#include <cassert>

using u64 = std::uint_fast64_t;

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
inline constexpr u64 GetWinSquare(u64 otrSqCnt,u64 inrSqCnt){
    return otrSqCnt+inrSqCnt;
}
inline constexpr u64 GetHomeSquare(u64 otrSqCnt,u64 inrSqCnt){
    return GetWinSquare(otrSqCnt, inrSqCnt)+1;
}
inline constexpr u64 GetSquareCount(u64 otrSqCnt,u64 inrSqCnt){
    return GetHomeSquare(otrSqCnt, inrSqCnt)+1;
}

inline constexpr u64 MAX_SQUARES = 128;
inline constexpr u64 SQ_SZb      = Global::ceillog2( MAX_SQUARES );

inline constexpr u64 MAX_PIECE_COUNT = 48;
inline constexpr u64 MAX_PLAYERS     = 8;
inline constexpr u64 MAX_PAWNS       = 24;

inline constexpr u64 OUTER_RING = 28;

//*for teting and debugging only these will not be used by relevent game files
extern u64 CURRENT_PLAYERS;
extern u64 CURRENT_AWNS;
extern u64 CURRENT_SQUARES;
//*for teting only these will not be used by relevent game files

//$ storage size in bits

inline u64 GetEce( u64 pl, u64 awn )
{
    assert( pl < CURRENT_PLAYERS && awn < CURRENT_AWNS );
    u64 result = CURRENT_AWNS * pl + awn;

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