#include "graphics_move.h"

#include <global.h>

#include <array>

#include "core.h"
#include "helper.h"

using namespace Global;
using enum b_GMoveFlags;
enum struct b_GMoveDataLayout : u64
{
    b_ece,
    b_frm_sq,
    b_to_sq,
    b_roll,
    zly_size

};
using enum b_GMoveDataLayout;
static constexpr std::array<u64, (u64)zly_size> b_SzOf  // %order matters
    {
        //% MUST MATCH b_GmoveDATALayout Enum ABOVE
        ECE_SZb,
        SQ_SZb,
        SQ_SZb,
        ROLL_SZb,
    };

static consteval u64 b_frm( const b_GMoveDataLayout inx )
{
    u64 result = 0;
    for ( auto i = 0; i < (u64)inx; i++ ) { result += b_SzOf[(u64)i]; }
    return result;
}



//* --------------------------- fFUNCTIONS START-----------------
void GraphicsMove::setMEce( u64 ece )
{

    mGMoveData=SetBits( mGMoveData, ece, b_frm( b_ece ), b_SzOf[(u64)b_ece] );
    // SetBits( mEce, ece, ece_frm, ece_sz );
}

u64 GraphicsMove::getMEce() const
{
    u64 res = GetBits( mGMoveData, b_frm( b_ece ), b_SzOf[(u64)b_ece] );
    // GetBits( mEce, ece_frm, ece_sz );

    return res;
}

void GraphicsMove::setFrom( u64 ece )
{

    mGMoveData=SetBits( mGMoveData, ece, b_frm( b_frm_sq), b_SzOf[(u64)b_frm_sq] );
    // SetBits( mEce, ece, ece_frm, ece_sz );
}

u64 GraphicsMove::getFrom() const
{
    u64 res = GetBits( mGMoveData, b_frm( b_frm_sq ), b_SzOf[(u64)b_frm_sq] );
    // GetBits( mEce, ece_frm, ece_sz );

    return res;
}

void GraphicsMove::setTo( u64 ece )
{

    mGMoveData=SetBits( mGMoveData, ece, b_frm( b_to_sq), b_SzOf[(u64)b_to_sq] );
    // SetBits( mEce, ece, ece_frm, ece_sz );
}

u64 GraphicsMove::getTo() const
{
    u64 res = GetBits( mGMoveData, b_frm( b_to_sq ), b_SzOf[(u64)b_to_sq] );
    // GetBits( mEce, ece_frm, ece_sz );

    return res;
}

void GraphicsMove::setRoll( u64 ece )
{

    mGMoveData=SetBits( mGMoveData, ece, b_frm( b_roll), b_SzOf[(u64)b_roll] );
    // SetBits( mEce, ece, ece_frm, ece_sz );
}

u64 GraphicsMove::getRoll() const
{
    u64 res = GetBits( mGMoveData, b_frm( b_roll), b_SzOf[(u64)b_roll] );
    // GetBits( mEce, ece_frm, ece_sz );

    return res;
}



