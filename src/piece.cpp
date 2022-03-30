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

//$ is safe,

//$ elementes in this enum must have correct size in SzOf
//$ in correct order

constexpr std::array<u64, (u64)b_PieceLayout::zly_size>
    b_SzOf_PieLay  // %order matters
    {
        //% MUST MATCH b_PieceLayout Enum ABOVE
        Global::ECE_SZb,  //*   b_ece,
        Global::SQ_SZb,   //*   b_current_sq,
        Global::SQ_SZb,   //*   b_entry_sq,
        Global::SQ_SZb    //*   b_switch_sq,
    };

void Piece::InitPiece( u64 ece, u64 sq, u64 entry_sq, u64 switch_sq )
{
    setEce( ece );
    setSq( sq );
    setEntrySq( entry_sq );
    setSwitchSq( switch_sq );
}

consteval u64 b_frm( const b_PieceLayout inx )
{
    u64 result = 0;
    for ( u64 i = 0; i < (u64)inx; i++ ) { result += b_SzOf_PieLay[(u64)i]; }
    return result;
}
constexpr u64 b_frm_nc( const b_PieceLayout inx )
{
    u64 result = 0;
    for ( u64 i = 0; i < (u64)inx; i++ ) { result += b_SzOf_PieLay[(u64)i]; }
    return result;
}



void Piece::setEce( u64 plr, u64 awn )
{
    check_fp( Global::GetEce( plr, awn ) < Global::MAX_PIECE_COUNT, "" );
    setEce( Global::GetEce( plr, awn ) );
}


void Piece::setAny(b_PieceLayout what, u64 value){
        mPiece=SetBits( mPiece, value, b_frm_nc( what ),
             b_SzOf_PieLay[(u64)what] );
}

void Piece::setEce( u64 ece )
{
    mPiece=SetBits( mPiece, ece, b_frm( b_PieceLayout::b_ece ),
             b_SzOf_PieLay[(u64)b_PieceLayout::b_ece] );
    // SetBits( mEce, ece, ece_frm, ece_sz );
}

u64 Piece::getEce() const
{
    return GetBits( mPiece, b_frm( b_PieceLayout::b_ece ),
                    b_SzOf_PieLay[(u64)b_PieceLayout::b_ece] );
}

void Piece::setSq( u64 sq )
{
    mPiece=SetBits( mPiece, sq, b_frm( b_PieceLayout::b_current_sq ),
             b_SzOf_PieLay[(u64)b_PieceLayout::b_current_sq] );
}

u64 Piece::getSq() const
{
    return GetBits( mPiece, b_frm( b_PieceLayout::b_current_sq ),
                    b_SzOf_PieLay[(u64)b_PieceLayout::b_current_sq] );
}

void Piece::setEntrySq( u64 sq )
{
    mPiece=SetBits( mPiece, sq, b_frm( b_PieceLayout::b_entry_sq ),
             b_SzOf_PieLay[(u64)b_PieceLayout::b_entry_sq] );
}

u64 Piece::getEntrySq() const
{
    return GetBits( mPiece, b_frm( b_PieceLayout::b_entry_sq ),
                    b_SzOf_PieLay[(u64)b_PieceLayout::b_entry_sq] );
}

void Piece::setSwitchSq( u64 sq )
{
    mPiece=SetBits( mPiece, sq, b_frm( b_PieceLayout::b_switch_sq ),
             b_SzOf_PieLay[(u64)b_PieceLayout::b_switch_sq] );
}

u64 Piece::getSwitchSq() const
{
    return GetBits( mPiece, b_frm( b_PieceLayout::b_switch_sq ),
                    b_SzOf_PieLay[(u64)b_PieceLayout::b_switch_sq] );
}

u64 Piece::getPlr()
{
    //! potential bug fraction to u64
    u64 result = getEce() / Global::MAX_PAWNS;
    

    return result;
}

u64 Piece::getAwn() { return getEce() % Global::MAX_PAWNS; }

void Piece::setFlag( b_PieceFlags flg, bool what )
{
    check_f( ( 63 - (u64)flg ) > b_frm( b_PieceLayout::zly_size ) );
    ( what ) ? mPiece=SetBit( mPiece, 63 - (u64)flg )
             : mPiece=UnSetBit( mPiece, 63 - (u64)flg );
}

u64 Piece::getFlag( b_PieceFlags flg )
{
    return GetBit( mPiece, 63 - (u64)flg );
}

using namespace Global;

using fmt::format;
using fmt::print;

using enum b_PieceFlags;
using enum b_PieceLayout;
//&Debug ahead

void Piece::CheckPiece( u64 crntSq, u64 crntPlr, u64 crntAwn )
{  //@In complete
    u64 result = crntSq;
    result=crntPlr;
    result=crntAwn;
    result ++;
    check_fp(  Global::GetEce( getPlr(), getAwn() ) < MAX_PIECE_COUNT ,
      format( "Ece:{}  MAX_PIECE:{}", Global::GetEce( getPlr(), getAwn() ), MAX_PIECE_COUNT ) );
    
    check_fp(
        getEce() < crntPlr * crntAwn,
        format( "Ece:{} != cP: {} * cA: {}", getEce(), crntPlr, crntAwn ) );

    check_fp( getSq() < crntSq, format( "Sq: {} crntSq:{}", getSq(), crntSq ) );

    check_fp( getEntrySq() < crntSq,
              format( "EntrySq: {} crntSq:{}", getEntrySq(), crntSq ) );

    check_fp( getSwitchSq() < crntSq,
              format( "EntrySq: {} crntSq:{}", getSwitchSq(), crntSq ) );

    check_fp( getPlr() < crntPlr,
              format( "getPlr: {} crntPlr:{}", getPlr(), crntPlr ) );

    check_fp( getAwn() < crntAwn,
              format( "getAwn: {} crntAwn:{}", getAwn(), crntAwn ) );

    check_fp( ( 63 - (u64)z_PieceFlagsSize ) > (u64)b_frm_copy( zly_size ),
              format( "TringSet: {} LayoutSz:{}", 63 - (u64)z_PieceFlagsSize,
                      (u64)b_frm_copy( zly_size ) ) );
}
void Piece::CheckPiece( GameState gs )
{  //@In complete
    u64 crntSq  = gs.getSqCnt();
    u64 crntPlr = gs.getCrntPlrCnt();
    u64 crntAwn = gs.getCrntAwnCnt();
    CheckPiece( crntSq, crntPlr, crntAwn );
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

        if ( b_frm_nc( b_current_sq ) == i )
        {
            res += fmt::format( fwStyle, " ece({}):", getEce() );
        }
        else if ( b_frm_nc( b_entry_sq ) == i )
        {
            res += fmt::format( orStyle, " Sqare({}):", getSq() );
        }
        else if ( b_frm_nc( b_switch_sq ) == i )
        {
            res += fmt::format( fwStyle, " entry_sq({}):", getEntrySq() );
        }
        else if ( b_frm_nc( zly_size ) == i )
        {
            res += fmt::format( fwStyle, " switch_sq({}):", getSwitchSq() );
        }
    }

    return res;
}
//% PieceNum  | Square  | Entry Sq | Switch Sq |
//% 0-5(6:64) | 6-12(7) | 13-19(7) | 20-26(7)  |
//@ Valid | Won |
//@  64   | 63  |
