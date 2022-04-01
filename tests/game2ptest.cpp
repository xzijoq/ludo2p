#include <gtest/gtest.h>
#include <stdarg.h>

#include "Game.h"
#include "game2p.h"
#include "global.h"
#include "helper.h"

using fmt::print;
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
/*
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
    MoveRaw( p00, 3, pece, sq );
    MoveRaw( p03, 4, pece, sq );
    MoveRaw( p10, 5, pece, sq );
    MoveRaw( p13, 6, pece, sq );
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

    //$MOVE TO sameplayer SQUARE----START-----------------
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
    //$MOVE TO sampleplayer SQUARE----END-----------------

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
    MoveRaw( p00, 3, pece, sq );
    MoveRaw( p03, 4, pece, sq );
    MoveRaw( p10, 5, pece, sq );
    MoveRaw( p13, 6, pece, sq );

    //% move em to 10 wthich is a safe square
    GameMove( p00, 7, pece, sq, gs );
    GameMove( p03, 6, pece, sq, gs );
    GameMove( p10, 5, pece, sq, gs );
    GameMove( p13, 4, pece, sq, gs );

    ASSERT_TRUE( p00.getSq() == 10 );
    ASSERT_TRUE( p03.getSq() == 10 );
    ASSERT_TRUE( p10.getSq() == 10 );
    ASSERT_TRUE( p13.getSq() == 10 );

    ASSERT_TRUE( sq[10].hasEce( p00.getEce() ) );
    ASSERT_TRUE( sq[10].hasEce( p03.getEce() ) );
    ASSERT_TRUE( sq[10].hasEce( p10.getEce() ) );
    ASSERT_TRUE( sq[10].hasEce( p13.getEce() ) );
    //$NO CAPTURE ON SAFE SQUARE----END---

    //$NO CAPTURE ON SAME TEAM----START---

    MoveRaw( p00, 3, pece, sq );
    MoveRaw( p03, 4, pece, sq );
    MoveRaw( p10, 5, pece, sq );
    MoveRaw( p13, 6, pece, sq );

    p00.setTeam( 0 );
    p03.setTeam( 0 );
    p10.setTeam( 0 );
    p13.setTeam( 0 );
    //% move  em all to sq 7
    GameMove( p00, 4, pece, sq, gs );
    GameMove( p03, 3, pece, sq, gs );
    GameMove( p10, 2, pece, sq, gs );
    GameMove( p13, 1, pece, sq, gs );

    ASSERT_TRUE( p00.getSq() == 7 );
    ASSERT_TRUE( p03.getSq() == 7 );
    ASSERT_TRUE( p10.getSq() == 7 );
    ASSERT_TRUE( p13.getSq() == 7 );
    ASSERT_TRUE( sq[7].hasEce( p00.getEce() ) );
    ASSERT_TRUE( sq[7].hasEce( p03.getEce() ) );
    ASSERT_TRUE( sq[7].hasEce( p10.getEce() ) );
    ASSERT_TRUE( sq[7].hasEce( p13.getEce() ) );

    //$NO CAPTURE ON SAME TEAM----END---

    //$NO CAPTURE ON Different TEAM but same player----START---

    MoveRaw( p00, 3, pece, sq );
    MoveRaw( p03, 4, pece, sq );
    MoveRaw( p10, 5, pece, sq );
    MoveRaw( p13, 6, pece, sq );

    p00.setTeam( 1 );
    p03.setTeam( 2 );
    p10.setTeam( 3 );
    p13.setTeam( 4 );
    //% move  em all to sq 7
    GameMove( p00, 1, pece, sq, gs );
    GameMove( p03, 0, pece, sq, gs );
    GameMove( p10, 1, pece, sq, gs );
    GameMove( p13, 0, pece, sq, gs );

    ASSERT_TRUE( p00.getSq() == 4 );
    ASSERT_TRUE( p03.getSq() == 4 );
    ASSERT_TRUE( p10.getSq() == 6 );
    ASSERT_TRUE( p13.getSq() == 6 );
    ASSERT_TRUE( sq[4].hasEce( p00.getEce() ) );
    ASSERT_TRUE( sq[4].hasEce( p03.getEce() ) );
    ASSERT_TRUE( sq[6].hasEce( p10.getEce() ) );
    ASSERT_TRUE( sq[6].hasEce( p13.getEce() ) );

    //$NO CAPTURE ON Different TEAM but same player--------END---

    //*reset
    p00.setTeam( 0 );
    p03.setTeam( 0 );
    p10.setTeam( 1 );
    p13.setTeam( 1 );

    //$Inner Square Switch-FromSwitchSq-----START----------

    MoveRaw( p00, p00.getEntrySq(), pece, sq );
    MoveRaw( p03, p03.getEntrySq(), pece, sq );
    MoveRaw( p10, p10.getEntrySq(), pece, sq );
    MoveRaw( p13, p13.getEntrySq(), pece, sq );

    //% Send em to 2 before entry sq onto switch sq
    GameMove( p00, 12, pece, sq, gs );
    GameMove( p03, 12, pece, sq, gs );
    GameMove( p10, 12, pece, sq, gs );
    GameMove( p13, 12, pece, sq, gs );

    GameMove( p00, 12, pece, sq, gs );
    GameMove( p03, 12, pece, sq, gs );
    GameMove( p10, 12, pece, sq, gs );
    GameMove( p13, 12, pece, sq, gs );

    //%Move in
    GameMove( p00, 2, pece, sq, gs );
    GameMove( p03, 2, pece, sq, gs );
    GameMove( p10, 2, pece, sq, gs );
    GameMove( p13, 2, pece, sq, gs );

    ASSERT_TRUE( p00.getSq() == 27 );
    ASSERT_TRUE( p03.getSq() == 27 );
    ASSERT_TRUE( p10.getSq() == 27 );
    ASSERT_TRUE( p13.getSq() == 27 );
    ASSERT_TRUE( sq[27].hasEce( p00.getEce() ) );
    ASSERT_TRUE( sq[27].hasEce( p03.getEce() ) );
    ASSERT_TRUE( sq[27].hasEce( p10.getEce() ) );
    ASSERT_TRUE( sq[27].hasEce( p13.getEce() ) );

    //$Inner Square Switch--FromSwitchSq----END----------------

    //$Inner Square Switch-FromEarlySq-----START----------

    MoveRaw( p00, p00.getEntrySq(), pece, sq );
    MoveRaw( p03, p03.getEntrySq(), pece, sq );
    MoveRaw( p10, p10.getEntrySq(), pece, sq );
    MoveRaw( p13, p13.getEntrySq(), pece, sq );

    //% Send em to 2 before entry sq onto switch sq

    GameMove( p00, 12, pece, sq, gs );
    GameMove( p03, 12, pece, sq, gs );
    GameMove( p10, 12, pece, sq, gs );
    GameMove( p13, 12, pece, sq, gs );

    GameMove( p00, 10, pece, sq, gs );
    GameMove( p03, 10, pece, sq, gs );
    GameMove( p10, 10, pece, sq, gs );
    GameMove( p13, 10, pece, sq, gs );

    //%Move in
    GameMove( p00, 3, pece, sq, gs );
    GameMove( p03, 3, pece, sq, gs );
    GameMove( p10, 3, pece, sq, gs );
    GameMove( p13, 3, pece, sq, gs );

    ASSERT_TRUE( p00.getSq() == 26 );
    ASSERT_TRUE( p03.getSq() == 26 );
    ASSERT_TRUE( p10.getSq() == 26 );
    ASSERT_TRUE( p13.getSq() == 26 );
    ASSERT_TRUE( sq[26].hasEce( p00.getEce() ) );
    ASSERT_TRUE( sq[26].hasEce( p03.getEce() ) );
    ASSERT_TRUE( sq[26].hasEce( p10.getEce() ) );
    ASSERT_TRUE( sq[26].hasEce( p13.getEce() ) );
    //*reset
    MoveRaw( p00, p00.getEntrySq(), pece, sq );
    MoveRaw( p03, p03.getEntrySq(), pece, sq );
    MoveRaw( p10, p10.getEntrySq(), pece, sq );
    MoveRaw( p13, p13.getEntrySq(), pece, sq );

    //$Inner Square Switch-FromEarlySq-----END----------

    //$Player 0 single move in
    MoveRaw( p00, 24, pece, sq );
    ASSERT_TRUE( p00.getSq() == 24 );
    ASSERT_TRUE( sq[24].hasEce( p00.getEce() ) );

    GameMove( p00, 1, pece, sq, gs );
    ASSERT_FALSE( p00.getSq() == 24 );
    ASSERT_FALSE( sq[24].hasEce( p00.getEce() ) );
    ASSERT_TRUE( p00.getSq() == 25 );
    ASSERT_TRUE( sq[25].hasEce( p00.getEce() ) );

    GameMove( p00, 1, pece, sq, gs );
    ASSERT_FALSE( p00.getSq() == 25 );
    ASSERT_FALSE( sq[25].hasEce( p00.getEce() ) );
    ASSERT_TRUE( p00.getSq() == 0 );
    ASSERT_TRUE( sq[0].hasEce( p00.getEce() ) );

    GameMove( p00, 1, pece, sq, gs );

    ASSERT_FALSE( p00.getSq() == 0 );
    ASSERT_FALSE( sq[25].hasEce( p00.getEce() ) );
    ASSERT_TRUE( p00.getSq() == 26 );
    ASSERT_TRUE( sq[26].hasEce( p00.getEce() ) );
    //$Player 0 single move in

    //$Player 0 single move in
    MoveRaw( p13, 11, pece, sq );
    ASSERT_TRUE( p13.getSq() == 11 );
    ASSERT_TRUE( sq[11].hasEce( p13.getEce() ) );

    GameMove( p13, 1, pece, sq, gs );
    ASSERT_FALSE( p13.getSq() == 11 );
    ASSERT_FALSE( sq[11].hasEce( p13.getEce() ) );
    ASSERT_TRUE( p13.getSq() == 12 );
    ASSERT_TRUE( sq[12].hasEce( p13.getEce() ) );

    GameMove( p13, 1, pece, sq, gs );
    ASSERT_FALSE( p13.getSq() == 12 );
    ASSERT_FALSE( sq[12].hasEce( p13.getEce() ) );
    ASSERT_TRUE( p13.getSq() == 13 );
    ASSERT_TRUE( sq[13].hasEce( p13.getEce() ) );

    GameMove( p13, 1, pece, sq, gs );
    ASSERT_FALSE( p13.getSq() == 13 );
    ASSERT_FALSE( sq[13].hasEce( p13.getEce() ) );
    ASSERT_TRUE( p13.getSq() == 26 );
    ASSERT_TRUE( sq[26].hasEce( p13.getEce() ) );
    //$Player 0 single move in

    // print( "\np00: {}", p00.DebugString() );
    // print( "\np03: {}", p03.DebugString() );
    // print( "\np10: {}", p10.DebugString() );
    // print( "\np13: {}", p13.DebugString() );
}
*/
//$ THE MOST IMPORTANT TEST OF PROJECT END

TEST( Game2pTest, InitGame )
{
    Game2p gme;
    gme.InitGame();

    ASSERT_TRUE( gme.Ece[MaxPlayers2p * MAX_PAWNS - 1].getSq() ==
                 HomeSquare2p );
    ASSERT_TRUE( gme.Ece[0].getSq() == HomeSquare2p );
}

TEST( Game2pTest, MoveRaw )
{
    Game2p gme;
    gme.InitGame();
    ASSERT_TRUE( gme.Ece[0].getSq() == HomeSquare2p );
    ASSERT_TRUE( gme.Ece[MaxPlayers2p * MAX_PAWNS - 1].getSq() ==
                 HomeSquare2p );

    ASSERT_TRUE( gme.Sq[HomeSquare2p].hasEce( gme.Ece[0].getEce() ) );
    ASSERT_TRUE( gme.Sq[HomeSquare2p].hasEce(
        gme.Ece[MaxPlayers2p * MAX_PAWNS - 1].getEce() ) );

    ASSERT_FALSE( gme.Sq[EntrySq2p[0]].hasEce( gme.Ece[0].getEce() ) );
    ASSERT_FALSE( gme.Sq[WinSquare2p].hasEce(
        gme.Ece[MaxPlayers2p * MAX_PAWNS - 1].getEce() ) );

    //**MOVE
    MoveRaw( gme.Ece[0], gme.Ece[0].getEntrySq(), gme.Ece, gme.Sq );
    MoveRaw( gme.Ece[MaxPlayers2p * MAX_PAWNS - 1], gme.mGState.getWinSq(),
             gme.Ece, gme.Sq );
    //**END

    ASSERT_TRUE( gme.Ece[0].getSq() == EntrySq2p[0] );
    ASSERT_TRUE( gme.Ece[MaxPlayers2p * MAX_PAWNS - 1].getSq() == WinSquare2p );

    ASSERT_TRUE( gme.Sq[EntrySq2p[0]].hasEce( gme.Ece[0].getEce() ) );
    ASSERT_TRUE( gme.Sq[WinSquare2p].hasEce(
        gme.Ece[MaxPlayers2p * MAX_PAWNS - 1].getEce() ) );

    ASSERT_FALSE( gme.Sq[HomeSquare2p].hasEce( gme.Ece[0].getEce() ) );
    ASSERT_FALSE( gme.Sq[HomeSquare2p].hasEce(
        gme.Ece[MaxPlayers2p * MAX_PAWNS - 1].getEce() ) );
}
