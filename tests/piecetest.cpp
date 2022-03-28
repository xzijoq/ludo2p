#include <gtest/gtest.h>
#include <piece.h>

#include <cstdint>

#include "core.h"
#include "global.h"
#include "helper.h"
using std::cout;
using std::endl;



//$check line 109-110

TEST( PieceTest, SetGetEce )
{
    //*circularly depends on correctness of set ece
    cout << endl;
    //$getEce()
    Piece ece;
    u64   num = 0;
    ece.setEce( num );
    ASSERT_EQ( ece.getEce(), 0 );

    // SetBits(num, 10, 0b1111111111, 0);
    num = Global::GetEce( CURRENT_PLAYERS - 1, CURRENT_AWNS - 1 );
    ece.setEce( num );
    ASSERT_EQ( ece.getEce(), num );
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
    ece.setEce( 0 );
    ASSERT_EQ( ece.getPlr(), 0 );
    ASSERT_EQ( ece.getAwn(), 0 );

    ece.setEce( CURRENT_AWNS * CURRENT_PLAYERS - 1 );

    ASSERT_EQ( ece.getPlr(), CURRENT_PLAYERS - 1 );
    ASSERT_EQ( ece.getAwn(), CURRENT_AWNS - 1 );
}


TEST( PieceTest, setEce1 )
{
    Piece ece;

    ece.setEce( 0, 0 );
    ASSERT_EQ( ece.getEce(), 0 );

    ece.mPiece = 0;
    u64 num    = Global::GetEce( CURRENT_PLAYERS - 1, CURRENT_AWNS - 1 );
    ece.setEce( CURRENT_PLAYERS - 1, CURRENT_AWNS - 1 );
    ASSERT_EQ( ece.getEce(), num );
}

TEST( PieceTest, SetGetSqareT )
{
    Piece ece;
    u64   num = CURRENT_SQUARES-1;
    ece.setSq( num );
    ASSERT_EQ( ece.getSq(), num );
}

TEST( PieceTest, SetGetEntrySqareT )
{
    Piece ece;
    u64   num = CURRENT_SQUARES-1;
    ece.setEntrySq( num );
    ASSERT_EQ( ece.getEntrySq(), num );
}
TEST( PieceTest, SetGetSwitchSqareT )
{
    Piece ece;
    u64   num = CURRENT_SQUARES-1;
    ece.setSwitchSq( num );
    ASSERT_EQ( ece.getSwitchSq(), num );
}

TEST( PieceTest, SetGetFlagsT )
{
    Piece ece;
    ASSERT_FALSE( ece.getFlag( b_PieceFlags::b_ece_won ) );
    ece.setFlag( b_PieceFlags::b_ece_won, true );
    ASSERT_TRUE( ece.getFlag( b_PieceFlags::b_ece_won ) );
    ece.setFlag( b_PieceFlags::b_ece_won, false );
    ASSERT_FALSE( ece.getFlag( b_PieceFlags::b_ece_won ) );

    ASSERT_FALSE( ece.getFlag( b_PieceFlags::b_ece_valid ) );
    ece.setFlag( b_PieceFlags::b_ece_valid, true );
    ASSERT_TRUE( ece.getFlag( b_PieceFlags::b_ece_valid ) );
    ece.setFlag( b_PieceFlags::b_ece_valid, false );
    ASSERT_FALSE( ece.getFlag( b_PieceFlags::b_ece_valid ) );
}
