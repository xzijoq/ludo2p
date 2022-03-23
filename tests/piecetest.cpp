#include <gtest/gtest.h>
#include <piece.h>

#include <cstdint>

#include "core.h"
#include "helper.h"
using std::cout;
using std::endl;
TEST( Piece, pt ) {}
static int cpl = CURRENT_PLAYERS;
static int caw = CURRENT_PAWNS;

//$check line 109-110

TEST( PieceTest, getEceStatic )
{
    CURRENT_PLAYERS = 5;
    CURRENT_PAWNS   = 7;
    ASSERT_EQ( Piece::getEce( 4, 2 ), 30 );

    Piece ece;
    ece.mEce = Piece::getEce( 3, 2 );
    ASSERT_EQ( ece.getPlr(), 3 );
    ASSERT_EQ( ece.getAwn(), 2 );

    CURRENT_PLAYERS = caw;
    CURRENT_PAWNS   = cpl;
}
TEST( PieceTest, getEce )
{
    cout << endl;
    //$getEce()
    Piece ece;

    CURRENT_PLAYERS = INT_MAX / 2 - 1;
    CURRENT_PAWNS   = INT_MAX / 2;
    u64 num         = 0;
    // SetBits(num, 10, 0b1111111111, 0);
    num      = 1023;
    ece.mEce = num;
    ASSERT_EQ( ece.getEce(), 63 );
    CURRENT_PLAYERS = caw;
    CURRENT_PAWNS   = cpl;
}
TEST( PieceTest, getPlr0Awn )
{
    Piece ece;
    // for ( auto i = 0; i < CURRENT_PAWNS * CURRENT_PLAYERS; i++ )
    //{
    //     ece.mEce = i;
    //     cout << "Pl: " << ece.getPlr() << "Aw: " << ece.getAwn() << endl;
    // }
    //@ -1 as it starts form 0,0
    ece.mEce = CURRENT_PAWNS * CURRENT_PLAYERS - 1;

    ASSERT_EQ( ece.getPlr(), CURRENT_PLAYERS - 1 );
    ASSERT_EQ( ece.getAwn(), CURRENT_PAWNS - 1 );
    ece.mEce = 0;
    ASSERT_EQ( ece.getPlr(), 0 );
    ASSERT_EQ( ece.getAwn(), 0 );
}

TEST( PieceTest, setEceT )
{
    //$ASSUMES THAT ece_sz>=6 that is
    //$atleast 6bits are used to store ece
    CURRENT_PLAYERS = 20;
    CURRENT_PAWNS   = 40;
    Piece ece;

    u64 dummy = 0b101010;
    ece.setEce( dummy );
    ASSERT_EQ( ece.mEce, 42 );

    dummy    = 0b111111;
    ece.mEce = 0;
    ece.setEce( dummy );
    ASSERT_EQ( ece.mEce, 63 );

    // cout<<ece.mEce;
    // DisplayBits(ece.mEce);
    CURRENT_PLAYERS = caw;
    CURRENT_PAWNS   = cpl;
}

TEST( PieceTest, setEce1T )
{
    CURRENT_PLAYERS = 6;
    CURRENT_PAWNS   = 8;
    Piece ece;
 
    ece.setEce( 0, 0 );
    ASSERT_EQ( ece.mEce, 0 );


    ece.setEce( 2, 3 );
    ASSERT_EQ( ece.mEce, 19 );


    ece.mEce = 0;
    ece.setEce( 4, 0);
    ASSERT_EQ( ece.mEce, Piece::getEce( 4, 0 ) );

    ASSERT_EQ( ece.mEce, 32 );

    ece.mEce = 0;
    ece.setEce( 5, 7 );
    //$ Did i just call a static function via a member
    ASSERT_EQ( ece.mEce, ece.getEce( 5, 7 ) );
    ASSERT_EQ( ece.mEce, ece.getEce() );
    ASSERT_EQ( ece.mEce, 47 );
    // cout<<endl<<ece.getPlr();

    // cout<<ece.mEce;
    // DisplayBits(ece.mEce);
    CURRENT_PLAYERS = caw;
    CURRENT_PAWNS   = cpl;
}
