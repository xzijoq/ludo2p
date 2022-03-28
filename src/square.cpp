#include "square.h"

#include <array>

#include "core.h"
#include "global.h"
#include "helper.h"
using fmt::format;
// 48
static constexpr u64 allece_sz = MAX_PIECE_COUNT;

// basically a bit mask for each ece
enum struct b_SquareLayout : u64
{
    b_allece,
    zly_size

};

using enum b_SquareLayout;
using enum b_SquareFlags;

static constexpr std::array<u64, (u64)zly_size> b_SzOf  // %order matters
    {
        //% MUST MATCH b_SquareLayout Enum ABOVE
        allece_sz,  //*   b_allece,

    };

//@ may wanna test this too
[[maybe_unused]] static consteval u64 b_frm( const b_SquareLayout inx )
{
    u64 result = 0;
    for ( auto i = 0; i < (u64)inx; i++ ) { result += b_SzOf[(u64)i]; }
    return result;
}

void Square::putEce( u64 ece )
{
    check_f( ece < MAX_PIECE_COUNT );
    SetBit( mSquare, ece );
}
void Square::popEce( u64 ece )
{
    check_f( ece < MAX_PIECE_COUNT );
    UnSetBit( mSquare, ece );
}
u64 Square::hasEce( u64 ece ) { return GetBit( mSquare, ece ); }
u64 Square::hasPlr( u64 plr ) const
{
    check_f( plr < CURRENT_PLAYERS );
    return GetBits( mSquare, plr * CURRENT_AWNS, CURRENT_AWNS );
}

void Square::setFlag( b_SquareFlags flg, bool what )
{
    check_f( ( 63 - (u64)flg ) > b_frm( zly_size ) );
    ( what ) ? SetBit( mSquare, 63 - (u64)flg )
             : UnSetBit( mSquare, 63 - (u64)flg );
}

u64 Square::getFlag( b_SquareFlags flg ) const
{
    check_f( ( 63 - (u64)flg ) > b_frm( zly_size ) );
    return GetBit( mSquare, 63 - (u64)flg );
}

//&Debug stuff ahead
void Square::CheckSquare() {}

std::string Square::DebugString() const
{
    std::string res = "";
    u64         dsq = mSquare;
    u64         i   = 0;
    int         pl  = (int)CURRENT_PLAYERS - 1;
    for ( auto k = 63; k >= 0; k-- )
    {
        i = (u64)k;
        if ( ( dsq & (u64)1 << i ) ) { res += format( grStyle, "1" ); }
        else { res += format( grStyle, "0" ); }

        if ( i == MAX_PIECE_COUNT ) { res += " Pieces:("; }
        if ( i % CURRENT_AWNS == 0 && i <= CURRENT_PLAYERS * CURRENT_AWNS &&
             i > 0 )
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