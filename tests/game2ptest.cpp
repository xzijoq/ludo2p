#include <gtest/gtest.h>
#include <stdarg.h>

#include "Game.h"
#include "game2p.h"
#include "global.h"
#include "helper.h"

// template<u64 sq,Piece ... pc>
void checkSqHas( Square sq[], u64 squ, bool has, int count, ... )
{
    va_list args;
    va_start( args, count );
    for ( int i = 0; i < count; ++i )
    {
        Piece p;
        p.mPiece = 0;
        p.mPiece = va_arg( args, u64 );
        if ( has ) { ASSERT_TRUE( sq[squ].hasEce( p.getEce() ) ); }
        else { ASSERT_FALSE( sq[squ].hasEce( p.getEce() ) ); }
    }
    va_end( args );
}
void checkPiceIsOn( u64 sq, int count, ... )
{
    va_list args;
    va_start( args, count );
    for ( int i = 0; i < count; ++i )
    {
        Piece p;
        p.mPiece = 0;
        p.mPiece = va_arg( args, u64 );
        ASSERT_TRUE( p.getSq() == sq );
    }
    va_end( args );
}
//$ THE MOST IMPORTANT TEST OF PROJECT
TEST( Game2pTest, GameMove2p )
{
    Game2p gme;
    gme.InitGame();
    auto& pece = gme.Ece;
    auto& sq   = gme.Sq;
    auto& gs   = gme.mGState;

    auto& p00 = gme.Ece[GetEce( 0, 0 )];
    auto& p03 = gme.Ece[GetEce( 0, 3 )];
    auto& p10 = gme.Ece[GetEce( 1, 0 )];
    auto& p13 = gme.Ece[GetEce( 1, 3 )];

    //$MOVE TO ENTRY SQUARE----START-------------------
    //% All pieces are in HomeSquare and they know it
    checkSqHas( sq, gs.getHomeSq(), true, 4, p00, p03, p10, p13 );
    checkPiceIsOn( gs.getHomeSq(), 4, p00, p03, p10, p13 );
    ASSERT_FALSE( sq[p00.getEntrySq()].hasEce( p00.getEce() ) );
    ASSERT_FALSE( sq[p03.getEntrySq()].hasEce( p03.getEce() ) );
    ASSERT_FALSE( sq[p10.getEntrySq()].hasEce( p10.getEce() ) );
    ASSERT_FALSE( sq[p13.getEntrySq()].hasEce( p13.getEce() ) );

    //^Moves Start
    GameMove( p00, 6, pece, sq, gs );
    GameMove( p03, 6, pece, sq, gs );
    GameMove( p10, 6, pece, sq, gs );
    GameMove( p13, 6, pece, sq, gs );
    //^Moves End

    //% ALl Pieces Are at Their EntrySquare
    checkSqHas( sq, gs.getHomeSq(), 4, false, p00, p03, p10, p13 );
    ASSERT_TRUE( sq[p00.getEntrySq()].hasEce( p00.getEce() ) );
    ASSERT_TRUE( sq[p03.getEntrySq()].hasEce( p03.getEce() ) );
    ASSERT_TRUE( sq[p10.getEntrySq()].hasEce( p10.getEce() ) );
    ASSERT_TRUE( sq[p13.getEntrySq()].hasEce( p13.getEce() ) );
    ////%and they know it
    ASSERT_TRUE( p00.getSq() == p00.getEntrySq() );
    ASSERT_TRUE( p03.getSq() == p03.getEntrySq() );
    ASSERT_TRUE( p10.getSq() == p10.getEntrySq() );
    ASSERT_TRUE( p13.getSq() == p13.getEntrySq() );

    //$MOVE TO ENTRY SQUARE----END-----------------

    //$RAW MOVE TO 2,3,4,5----START----------------
    //^*RawMove em to 3,4,5,6
    MoveRaw( p00, 3,pece, sq );
    MoveRaw( p03, 4,pece, sq );
    MoveRaw( p10, 5,pece, sq );
    MoveRaw( p13, 6,pece, sq );
    //*RawMove ENd

    //%check sq
    ASSERT_FALSE( sq[p00.getEntrySq()].hasEce( p00.getEce() ) );
    ASSERT_FALSE( sq[p03.getEntrySq()].hasEce( p03.getEce() ) );
    ASSERT_FALSE( sq[p10.getEntrySq()].hasEce( p10.getEce() ) );
    ASSERT_FALSE( sq[p13.getEntrySq()].hasEce( p13.getEce() ) );

    ASSERT_TRUE( sq[3].hasEce( p00.getEce() ) );
    ASSERT_TRUE( sq[4].hasEce( p03.getEce() ) );
    ASSERT_TRUE( sq[5].hasEce( p10.getEce() ) );
    ASSERT_TRUE( sq[6].hasEce( p13.getEce() ) );
    //%and they know it
    ASSERT_TRUE( p00.getSq() == 3 );
    ASSERT_TRUE( p03.getSq() == 4 );
    ASSERT_TRUE( p10.getSq() == 5 );
    ASSERT_TRUE( p13.getSq() == 6 );
    //$RAW MOVE TO 2,3,4,5----END----------------

    //$MOVE TO TEAM SQUARE----START-----------------
    GameMove( p00, 1, pece, sq, gs );
    GameMove( p03, 0, pece, sq, gs );
    GameMove( p10, 1, pece, sq, gs );
    GameMove( p13, 0, pece, sq, gs );
    //%check sq
    ASSERT_FALSE( sq[3].hasEce( p00.getEce() ) );
    ASSERT_FALSE( sq[5].hasEce( p10.getEce() ) );

    ASSERT_TRUE( sq[4].hasEce( p00.getEce() ) );
    ASSERT_TRUE( sq[4].hasEce( p03.getEce() ) );
    ASSERT_TRUE( sq[6].hasEce( p10.getEce() ) );
    ASSERT_TRUE( sq[6].hasEce( p13.getEce() ) );
    //%and they know it
    ASSERT_TRUE( p00.getSq() == 4 );
    ASSERT_TRUE( p03.getSq() == 4 );
    ASSERT_TRUE( p10.getSq() == 6 );
    ASSERT_TRUE( p13.getSq() == 6 );
    //$MOVE TO TEAM SQUARE----END-----------------

    //$MULTI CAPTURE p1 by p0
    GameMove( p00, 2, pece, sq, gs );

    ASSERT_FALSE( sq[4].hasEce( p00.getEce() ) );
    // ASSERT_FALSE( sq[4].hasEce( p03.getEce() ) );
    ASSERT_TRUE( sq[6].hasEce( p00.getEce() ) );
    ASSERT_TRUE( sq[4].hasEce( p03.getEce() ) );
    ASSERT_TRUE( p00.getSq() == 6 );
    ASSERT_TRUE( p03.getSq() == 4 );

    ASSERT_FALSE( sq[6].hasEce( p10.getEce() ) );
    ASSERT_FALSE( sq[6].hasEce( p13.getEce() ) );
    ASSERT_TRUE( sq[gs.getHomeSq()].hasEce( p10.getEce() ) );
    ASSERT_TRUE( sq[gs.getHomeSq()].hasEce( p13.getEce() ) );
    ASSERT_TRUE( p10.getSq() == gs.getHomeSq() );
    ASSERT_TRUE( p13.getSq() == gs.getHomeSq() );
    //$MULTI CAPTURE p1 by p0---END-----

    
    //$NO CAPTURE ON SAFE SQUARE----START---
    //$NO CAPTURE ON SAFE SQUARE----END---



}

//$ THE MOST IMPORTANT TEST OF PROJECT END

TEST( Game2pTest, InitGame )
{
    Game2p gme;
    gme.InitGame();

    ASSERT_TRUE( gme.Ece[MaxPlayers2p*MAX_PAWNS- 1].getSq() == HomeSquare2p );
    ASSERT_TRUE( gme.Ece[0].getSq() == HomeSquare2p );
}

TEST( Game2pTest, MoveRaw )
{
    Game2p gme;
    gme.InitGame();
    ASSERT_TRUE( gme.Ece[0].getSq() == HomeSquare2p );
    ASSERT_TRUE( gme.Ece[MaxPlayers2p*MAX_PAWNS- 1].getSq() == HomeSquare2p );

    ASSERT_TRUE( gme.Sq[HomeSquare2p].hasEce( gme.Ece[0].getEce() ) );
    ASSERT_TRUE(
        gme.Sq[HomeSquare2p].hasEce( gme.Ece[MaxPlayers2p*MAX_PAWNS - 1].getEce() ) );

    ASSERT_FALSE( gme.Sq[EntrySq2p[0]].hasEce( gme.Ece[0].getEce() ) );
    ASSERT_FALSE(
        gme.Sq[WinSquare2p].hasEce( gme.Ece[MaxPlayers2p*MAX_PAWNS - 1].getEce() ) );

    //**MOVE
    MoveRaw( gme.Ece[0], gme.Ece[0].getEntrySq(),gme.Ece, gme.Sq );
    MoveRaw( gme.Ece[MaxPlayers2p*MAX_PAWNS - 1], gme.mGState.getWinSq(),gme.Ece, gme.Sq );
    //**END

    ASSERT_TRUE( gme.Ece[0].getSq() == EntrySq2p[0] );
    ASSERT_TRUE( gme.Ece[MaxPlayers2p*MAX_PAWNS - 1].getSq() == WinSquare2p );

    ASSERT_TRUE( gme.Sq[EntrySq2p[0]].hasEce( gme.Ece[0].getEce() ) );
    ASSERT_TRUE(
        gme.Sq[WinSquare2p].hasEce( gme.Ece[MaxPlayers2p*MAX_PAWNS - 1].getEce() ) );

    ASSERT_FALSE( gme.Sq[HomeSquare2p].hasEce( gme.Ece[0].getEce() ) );
    ASSERT_FALSE(
        gme.Sq[HomeSquare2p].hasEce( gme.Ece[MaxPlayers2p*MAX_PAWNS - 1].getEce() ) );
}
