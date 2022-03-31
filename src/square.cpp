//$ has plr depends on knowledge of current awns
#include "square.h"

#include <array>

#include "core.h"
#include "global.h"
#include "helper.h"

using enum b_Square;

constexpr std::array<u64, (u64)b_Square::zb_sq_sz> b_SqSz  // %order matters
    {
        //% MUST MATCH b_SquareLayout Enum ABOVE
        Global::MAX_PIECE_COUNT,  //*   b_allece,


    };

//@ may wanna test this too
consteval u64 b_Sqfrm( const b_Square inx )
{
    u64 result = 0;
    for ( auto i = 0; i < (u64)inx; i++ ) { result += b_SqSz[(u64)i]; }
    return result;
}
constexpr u64 b_Sqfrm_nc( const b_Square inx )
{
    u64 result = 0;
    for ( u64 i = 0; i < (u64)inx; i++ ) { result += b_SqSz[(u64)i]; }
    return result;
}

void Square::putEce( u64 ece )
{
    check_f( ece < Global::MAX_PIECE_COUNT );
    mSquare = SetBit( mSquare, ece );
}
void Square::popEce( u64 ece )
{
    check_f( ece < Global::MAX_PIECE_COUNT );
    mSquare = UnSetBit( mSquare, ece );
}


u64 Square::hasEce( u64 ece ) { return GetBit( mSquare, ece ); }
u64 Square::hasPlr( u64 plr ) const
{
    return GetBits( mSquare, plr * Global::MAX_PAWNS, Global::MAX_PAWNS );
}

void Square::setFlag( b_SquareFlags flg, bool what )
{
    check_f( ( 63 - (u64)flg ) > b_Sqfrm( b_Square::zb_sq_sz ) );
    ( what ) ? mSquare = SetBit( mSquare, 63 - (u64)flg )
             : mSquare = UnSetBit( mSquare, 63 - (u64)flg );
}

u64 Square::getFlag( b_SquareFlags flg ) const
{
    check_f( ( 63 - (u64)flg ) > b_Sqfrm( b_Square::zb_sq_sz ) );
    return GetBit( mSquare, 63 - (u64)flg );
}

//&Debug stuff ahead
using fmt::format;
// 48
using namespace Global;

void Square::CheckSquare() {}

std::string Square::DebugString( u64 CrntPlr, u64 CrntAwn ) const
{
    std::string res = "";
    u64         dsq = mSquare;
    u64         i   = 0;
    int         pl  = (int)CrntPlr - 1;
    for ( auto k = 63; k >= 0; k-- )
    {
        i = (u64)k;
        if ( ( dsq & (u64)1 << i ) ) { res += format( grStyle, "1" ); }
        else { res += format( grStyle, "0" ); }


        if ( i == MAX_PIECE_COUNT ) { res += " Pieces:("; }
        if ( i % CrntAwn == 0 && i <= CrntPlr * CrntAwn && i > 0 )
        {
            res += format( fwStyle, " pl{}:", pl );
            pl--;
        };

        // std::cout<<i<<std::endl;
        // break;
    }
    res += " )";
    // res += format( fwStyle, "\nhasPlayer: " );
    // for ( auto k = (int)CURRENT_PLAYERS - 1; k >= 0; k-- )
    //{
    //     if ( hasPlr( (u64)k ) )
    //     {
    //         res += format( grStyle, " pl:{},{:b} ", k, hasPlr( (u64)k ) );
    //     }
    // }
    // res += "\n";

    return res;
}