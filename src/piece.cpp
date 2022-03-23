//$ INLINE THEM REMOVE ERROR CHECKING EVENTUALLY
//$ Move Em To Header so they can be inlined
//$ Or make an honest macro out of em
#include "piece.h"

#include <fmt/format.h>

#include "core.h"
#include "global.h"
#include "helper.h"

#ifdef NDEBUG
    #undef NDEBUG
#endif
#include <cassert>
//% PieceNum  | Square  | Entry Sq | Switch Sq |
//% 0-5(6:64) | 6-12(7) | 13-19(7) | 20-26(7)  |
//@ Valid | Won |
//@  64   | 63  |

static constexpr int ece_sz = 6;
//$storage bits
static constexpr int ece_frm = 0;
static constexpr int ece_to  = ece_frm + ece_sz;

static constexpr int sq_frm = ece_to;
static constexpr int sq_to  = sq_frm + SQ_SZb;

static constexpr int entry_sq_frm = sq_to;
static constexpr int entry_sq_to  = entry_sq_frm + SQ_SZb;

static constexpr int switch_sq_frm = entry_sq_to;
static constexpr int switch_sq_to  = switch_sq_frm + SQ_SZb;

u64 Piece::getEce( u64 pl, u64 awn )
{
    u64 result = CURRENT_PAWNS * pl + awn;
    assert( pl < CURRENT_PLAYERS && awn < CURRENT_PAWNS );

    assert( result < MAX_PIECE_COUNT );
    return result;
}
void Piece::setEce( u64 ece )
{
    assert( ece < CURRENT_PLAYERS * CURRENT_PAWNS );

    SetBits( mEce, ece, ece_frm, ece_sz );
}
void Piece::setEce( u64 plr, u64 awn )
{
    u64 tece = Piece::getEce( plr, awn );
    setEce( tece );
}


u64 Piece::getPlr()
{
    u64 result = getEce() / CURRENT_PAWNS;
    assert( result < CURRENT_PLAYERS );
    return result;
}

u64 Piece::getAwn()
{
    u64 result = getEce() % CURRENT_PAWNS;
    assert( result < CURRENT_PAWNS );
    return result;
}
u64 Piece::getEce()
{
    u64 res = GetBits( mEce, ece_frm, ece_sz );
    assert( res >= 0 && res <= CURRENT_PLAYERS * CURRENT_PAWNS );
    return res;
}

void Piece::CheckPiece()
{
    // assert( getPlr() >= 0 && getPlr() <= MAX_PLAYERS );
    // assert( getAwn() >= 0 && getAwn() <= MAX_PAWN );
    // assert( getEce() >= 0 && getAwn() <= MAX_PIECE_COUNT );
}