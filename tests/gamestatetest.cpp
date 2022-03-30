#include <gtest/gtest.h>

#include "global.h"
#include "gamestate.h"
#include "RegularMaps.h"
using namespace Global;
TEST( GameStateTest, SetGetCnt )
{
    GameState g1;
    for ( u64 i = 0; i < MAX_PLAYERS; i++ )
    {
        ASSERT_FALSE( g1.getPlrState( i ) );
        g1.setPlrState( i, true );
        ASSERT_TRUE( g1.getPlrState( i ) );
    }
    for ( u64 i = 0; i < MAX_PLAYERS; i++ )
    {
        ASSERT_TRUE( g1.getPlrState( i ) );
        g1.setPlrState( i, false );
        ASSERT_FALSE( g1.getPlrState( i ) );
    }

    u64 cnt = 0;
    g1.setMaxPlrCnt( cnt );
    ASSERT_EQ( g1.getMaxPlrCnt(), cnt );

    g1.setCrntPlrCnt( cnt );
    ASSERT_EQ( g1.getCrntPlrCnt(), cnt );

    g1.setCrntAwnCnt( cnt );
    ASSERT_EQ( g1.getCrntAwnCnt(), cnt );

    g1.setOtrSqCnt( cnt );
    ASSERT_EQ( g1.getOtrSqCnt(), cnt );

    g1.setInrSqCnt( cnt );
    ASSERT_EQ( g1.getInrSqCnt(), cnt );

    //^MAX
    cnt = MAX_PLAYERS;
    g1.setMaxPlrCnt( cnt );
    ASSERT_EQ( g1.getMaxPlrCnt(), cnt );

    g1.setCrntPlrCnt( cnt );
    ASSERT_EQ( g1.getCrntPlrCnt(), cnt );

    cnt = MAX_PAWNS;
    g1.setCrntAwnCnt( cnt );
    ASSERT_EQ( g1.getCrntAwnCnt(), cnt );

    u64 inrSqCnt = 5;
    int temp = (int)( GetSquareCount( MAX_SQUARES, inrSqCnt ) - MAX_SQUARES );
    ASSERT_LT( temp, MAX_SQUARES );
    u64 otrSqCnt = MAX_SQUARES - (u64)temp;

    g1.setOtrSqCnt( otrSqCnt );
    ASSERT_EQ( g1.getOtrSqCnt(), otrSqCnt );

    g1.setInrSqCnt( inrSqCnt );
    ASSERT_EQ( g1.getInrSqCnt(), inrSqCnt );
}
TEST( GameStateTest, InitGameState )
{
    GameState gs;
    u64       maxPlrCnt  = 0;
    u64       crntPlrCnt = 0;
    u64       crntAwnCnt = 0;
    u64       otrSqCnt   = 0;
    u64       inrSqCnt   = 0;
    gs.InitGameState( maxPlrCnt, crntPlrCnt, crntAwnCnt, otrSqCnt, inrSqCnt );
    ASSERT_EQ( maxPlrCnt, gs.getMaxPlrCnt() );
    ASSERT_EQ( crntPlrCnt, gs.getCrntPlrCnt() );
    ASSERT_EQ( crntAwnCnt, gs.getCrntAwnCnt() );
    ASSERT_EQ( otrSqCnt, gs.getOtrSqCnt() );
    ASSERT_EQ( inrSqCnt, gs.getInrSqCnt() );

    //^max
    maxPlrCnt  = MAX_PLAYERS;
    crntPlrCnt = MAX_PLAYERS;
    crntAwnCnt = MAX_PAWNS;
    inrSqCnt   = 5;
    int temp   = (int)( GetSquareCount( MAX_SQUARES, inrSqCnt ) - MAX_SQUARES );
    ASSERT_LT( temp, MAX_SQUARES );
    otrSqCnt = MAX_SQUARES - (u64)temp;

    gs.InitGameState( maxPlrCnt, crntPlrCnt, crntAwnCnt, otrSqCnt, inrSqCnt );
    // std::cout << gs.DebugString();
    ASSERT_EQ( maxPlrCnt, gs.getMaxPlrCnt() );
    ASSERT_EQ( crntPlrCnt, gs.getCrntPlrCnt() );
    ASSERT_EQ( crntAwnCnt, gs.getCrntAwnCnt() );
    ASSERT_EQ( otrSqCnt, gs.getOtrSqCnt() );
    ASSERT_EQ( inrSqCnt, gs.getInrSqCnt() );

    ASSERT_LE( gs.getWinSq(), MAX_SQUARES );
    ASSERT_LE( gs.getHomeSq(), MAX_SQUARES );
    ASSERT_LE( gs.getSqCnt(), MAX_SQUARES );
}