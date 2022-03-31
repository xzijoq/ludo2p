#include "graphics_move.h"

#include <global.h>

#include <array>

#include "core.h"
#include "helper.h"

using namespace Global;
using enum b_GMoveFlags;

using enum b_GMove;
constexpr std::array<u64, (u64)zb_gmv_size> b_GMvSz  // %order matters
    {
        //% MUST MATCH b_GmoveDATALayout Enum ABOVE
        ECE_SZb,
        SQ_SZb,
        SQ_SZb,
        ROLL_SZb,
    };

consteval u64 b_GmvFrm( const b_GMove inx )
{
    u64 result = 0;
    for ( auto i = 0; i < (u64)inx; i++ ) { result += b_GMvSz[(u64)i]; }
    return result;
}
consteval u64 b_GmvFrm_nc( const b_GMove inx )
{
    u64 result = 0;
    for ( auto i = 0; i < (u64)inx; i++ ) { result += b_GMvSz[(u64)i]; }
    return result;
}









//* --------------------------- fFUNCTIONS START-----------------
void GraphicsMove::setMEce( u64 ece )
{

    mGMove=SetBits( mGMove, ece, b_GmvFrm( b_mece ), b_GMvSz[(u64)b_mece] );

}

u64 GraphicsMove::getMEce() const
{
    return GetBits( mGMove, b_GmvFrm( b_mece ), b_GMvSz[(u64)b_mece] );


}

void GraphicsMove::setFrom( u64 ece )
{

    mGMove=SetBits( mGMove, ece, b_GmvFrm( b_frm_sq), b_GMvSz[(u64)b_frm_sq] );

}

u64 GraphicsMove::getFrom() const
{
    return  GetBits( mGMove, b_GmvFrm( b_frm_sq ), b_GMvSz[(u64)b_frm_sq] );
 

}

void GraphicsMove::setTo( u64 ece )
{

    mGMove=SetBits( mGMove, ece, b_GmvFrm( b_to_sq), b_GMvSz[(u64)b_to_sq] );
 
}

u64 GraphicsMove::getTo() const
{
    return GetBits( mGMove, b_GmvFrm( b_to_sq ), b_GMvSz[(u64)b_to_sq] );

}

void GraphicsMove::setRoll( u64 ece )
{

    mGMove=SetBits( mGMove, ece, b_GmvFrm( b_roll), b_GMvSz[(u64)b_roll] );

}

u64 GraphicsMove::getRoll() const
{
    return GetBits( mGMove, b_GmvFrm( b_roll), b_GMvSz[(u64)b_roll] );

}



