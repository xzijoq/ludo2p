#include "game2p.h"

#include <gtest/gtest.h>
#include <math.h>

#include <cstdint>
#include <limits>

#include "core.h"
#include "global.h"
#include "Game.h"

TEST( Game2pTest, InitGame )
{
    Game2p gme;
    gme.InitGame();
    gme.Ece[gme.EceSz - 1];

    ASSERT_TRUE( gme.Ece[gme.EceSz - 1].getSq() == HomeSquare2p );
    ASSERT_TRUE( gme.Ece[0].getSq() == HomeSquare2p );
}

TEST( Game2pTest, Move )
{
    Game2p gme;
    gme.InitGame();
    ASSERT_TRUE( gme.Ece[0].getSq() == HomeSquare2p );
    ASSERT_TRUE( gme.Ece[gme.EceSz - 1].getSq() == HomeSquare2p );

    ASSERT_TRUE( gme.Sq[HomeSquare2p].hasEce( gme.Ece[0].getEce() ) );
    ASSERT_TRUE(gme.Sq[HomeSquare2p].hasEce(gme.Ece[gme.EceSz - 1].getEce()));

    ASSERT_FALSE( gme.Sq[EntrySq2p[0]].hasEce( gme.Ece[0].getEce() ) );
    ASSERT_FALSE(gme.Sq[WinSquare2p].hasEce(gme.Ece[gme.EceSz - 1].getEce()));

    //**MOVE
    MoveRaw(gme.Ece[0], gme.Ece[0].getEntrySq(),gme.Sq);
    MoveRaw(gme.Ece[gme.EceSz - 1], gme.mGState.getWinSq(),gme.Sq);
    //**END

    ASSERT_TRUE( gme.Ece[0].getSq() == EntrySq2p[0] );
    ASSERT_TRUE( gme.Ece[gme.EceSz - 1].getSq() == WinSquare2p );

    ASSERT_TRUE( gme.Sq[EntrySq2p[0]].hasEce( gme.Ece[0].getEce() ) );
    ASSERT_TRUE(gme.Sq[WinSquare2p].hasEce(gme.Ece[gme.EceSz - 1].getEce()));

    ASSERT_FALSE( gme.Sq[HomeSquare2p].hasEce( gme.Ece[0].getEce() ) );
    ASSERT_FALSE(gme.Sq[HomeSquare2p].hasEce(gme.Ece[gme.EceSz - 1].getEce()));


}