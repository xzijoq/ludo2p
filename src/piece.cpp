//$ INLINE THEM REMOVE ERROR CHECKING EVENTUALLY
//$ Move Em To Header so they can be inlined
//$ Or make an honest macro out of em
#include "piece.h"

#include <array>
#include <cstdio>

#include "core.h"
#include "global.h"
#include "helper.h"

#ifdef NDEBUG
    #undef NDEBUG
#endif
#include <cassert>

static constexpr u64 ece_sz = ceillog2( MAX_PIECE_COUNT );
using fmt::format;
using fmt::print;

//$ elementes in this enum must have correct size in SzOf
//$ in correct order
enum struct b_PieceLayout : u64
{
    b_ece,
    b_current_sq,
    b_entry_sq,
    b_switch_sq,
    zly_size

};

using enum b_PieceLayout;
using enum b_PieceFlags;

static constexpr std::array<u64, (u64)zly_size> b_SzOf  // %order matters
    {
        //% MUST MATCH b_PieceLayout Enum ABOVE
        ece_sz,  //*   b_ece,
        SQ_SZb,  //*   b_current_sq,
        SQ_SZb,  //*   b_entry_sq,
        SQ_SZb   //*   b_switch_sq,
    };

void Piece::InitPiece( u64 ece, u64 sq, u64 entry_sq, u64 switch_sq )
{
    setEce( ece );
    setSq( sq );
    setEntrySq( entry_sq );
    setSwitchSq( switch_sq );
}

static consteval u64 b_frm( const b_PieceLayout inx )
{
    u64 result = 0;
    for ( auto i = 0; i < (u64)inx; i++ ) { result += b_SzOf[(u64)i]; }
    return result;
}

void Piece::testing()
{
    print( okStyle, "\nwaa:{}\n", b_frm( (b_PieceLayout)( b_SzOf.size() ) ) );
}

void Piece::setEce( u64 plr, u64 awn )
{
    u64 tece = Global::GetEce( plr, awn );
    setEce( tece );
}
void Piece::setEce( u64 ece )
{
    check_f( ece < CURRENT_PLAYERS * CURRENT_AWNS );
    SetBits( mPiece, ece, b_frm( b_ece ), b_SzOf[(u64)b_ece] );
    // SetBits( mEce, ece, ece_frm, ece_sz );
}

u64 Piece::getEce() const
{
    u64 res = GetBits( mPiece, b_frm( b_ece ), b_SzOf[(u64)b_ece] );
    // GetBits( mEce, ece_frm, ece_sz );
    check_f( res >= 0 && res <= CURRENT_PLAYERS * CURRENT_AWNS );
    return res;
}

void Piece::setSq( u64 sq )
{
    check_f( sq < CURRENT_SQUARES );
    SetBits( mPiece, sq, b_frm( b_current_sq ), b_SzOf[(u64)b_current_sq] );
}

u64 Piece::getSq() const
{
    auto result =
        GetBits( mPiece, b_frm( b_current_sq ), b_SzOf[(u64)b_current_sq] );
    check_f( result < CURRENT_SQUARES );
    return result;
}

void Piece::setEntrySq( u64 sq )
{
    check_f( sq < CURRENT_SQUARES );
    SetBits( mPiece, sq, b_frm( b_entry_sq ), b_SzOf[(u64)b_entry_sq] );
}

u64 Piece::getEntrySq() const
{
    auto result =
        GetBits( mPiece, b_frm( b_entry_sq ), b_SzOf[(u64)b_entry_sq] );
    check_f( result < CURRENT_SQUARES );
    return result;
}

void Piece::setSwitchSq( u64 sq )
{
    check_f( sq < CURRENT_SQUARES );
    SetBits( mPiece, sq, b_frm( b_switch_sq ), b_SzOf[(u64)b_switch_sq] );
}

u64 Piece::getSwitchSq() const
{
    auto result =
        GetBits( mPiece, b_frm( b_switch_sq ), b_SzOf[(u64)b_switch_sq] );
    check_f( result < CURRENT_SQUARES );
    return result;
}

u64 Piece::getPlr()
{
    u64 result = getEce() / CURRENT_AWNS;
    check_f( result < CURRENT_PLAYERS );
    return result;
}

u64 Piece::getAwn()
{
    u64 result = getEce() % CURRENT_AWNS;
    check_f( result < CURRENT_AWNS );
    return result;
}

void Piece::setFlag( b_PieceFlags flg, bool what )
{
    check_f( ( 63 - (u64)flg ) > b_frm( zly_size ) );
    ( what ) ? SetBit( mPiece, 63 - (u64)flg )
             : UnSetBit( mPiece, 63 - (u64)flg );
}

u64 Piece::getFlag( b_PieceFlags flg )
{
    //(maybe should return bool)
    check_f( ( 63 - (u64)flg ) > b_frm( zly_size ) );
    return GetBit( mPiece, 63 - (u64)flg );
}

//&Debug ahead
u64 b_frm_copy( const b_PieceLayout inx )
{
    u64 result = 0;
    for ( auto i = 0; i < (int)inx; i++ ) { result += b_SzOf[(u64)i]; }
    return result;
}
void Piece::CheckPiece()
{  //@In complete
    u64 result = 0;
    result     = Global::GetEce( getPlr(), getAwn() );
    check_f( result < MAX_PIECE_COUNT );

    result = getEce();
    check_f( result < MAX_PIECE_COUNT );

    result = getSq();
    check_f( result < CURRENT_SQUARES );

    result = getEntrySq();
    check_f( result < CURRENT_SQUARES );

    result = getSwitchSq();
    check_f( result < CURRENT_SQUARES );

    result = getPlr();
    check_f( result < CURRENT_PLAYERS );

    result = getAwn();
    check_f( result < CURRENT_AWNS );

    check_f( ( 63 - (u64)z_PieceFlagsSize ) > (u64)b_frm_copy( zly_size ) );
}

std::string Piece::DebugString() const
{
    // DisplayBits(mEce);
    string res  = "";
    u64    cece = mPiece;
    u64    i    = 0;
    for ( auto k = 63; k >= 0; k-- )
    {
        i = (u64)k;
        if ( ( cece & (u64)1 << i ) ) { res += format( grStyle, "1" ); }
        else { res += format( grStyle, "0" ); }

        if ( b_frm_copy( b_current_sq ) == i )
        {
            res += fmt::format( fwStyle, " ece({}):", getEce() );
        }
        else if ( b_frm_copy( b_entry_sq ) == i )
        {
            res += fmt::format( fwStyle, " Sqare({}):", getSq() );
        }
        else if ( b_frm_copy( b_switch_sq ) == i )
        {
            res += fmt::format( fwStyle, " entry_sq({}):", getEntrySq() );
        }
        else if ( b_frm_copy( zly_size ) == i )
        {
            res += fmt::format( fwStyle, " switch_sq({}):", getSwitchSq() );
        }
    }
    // res += "\n";
    //
    // res += format( okStyle, "|| getSsq: " );
    // res += format( yeStyle, "{}={:b} ", getSwitchSq(), getSwitchSq() );
    //
    // res += format( okStyle, "|| getEsq: " );
    // res += format( yeStyle, "{}={:b} ", getEntrySq(), getEntrySq() );
    //
    // res += format( okStyle, "|| getSqr: " );
    // res += format( yeStyle, "{}={:b} ", getSq(), getSq() );
    //
    // res += format( okStyle, "getEce: " );
    // res += format( yeStyle, "{}={:b} ", getEce(), getEce() );
    return res;
}
//% PieceNum  | Square  | Entry Sq | Switch Sq |
//% 0-5(6:64) | 6-12(7) | 13-19(7) | 20-26(7)  |
//@ Valid | Won |
//@  64   | 63  |
