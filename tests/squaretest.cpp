#include <gtest/gtest.h>


#include "global.h"
#include "square.h"

using namespace Global;
// using std::cout;
// using std::endl;
u64 t_c_s = MAX_SQUARES;
TEST( SquareTest, Put0Has0Pop_Ece )
{
    srand( (unsigned int)time( 0 ) );
    Square s1;
    //* Min
    ASSERT_FALSE( s1.hasEce( 0 ) );
    s1.putEce( 0 );
    ASSERT_TRUE( s1.hasEce( 0 ) );
    s1.popEce( 0 );
    ASSERT_FALSE( s1.hasEce( 0 ) );

    //* Max
    ASSERT_FALSE( s1.hasEce( MAX_PIECE_COUNT - 1 ) );
    s1.putEce( MAX_PIECE_COUNT - 1 );
    ASSERT_TRUE( s1.hasEce( MAX_PIECE_COUNT - 1 ) );
    s1.popEce( MAX_PIECE_COUNT - 1 );
    ASSERT_FALSE( s1.hasEce( MAX_PIECE_COUNT - 1 ) );


    //for ( u64 i = 0; i < MAX_PIECE_COUNT; i++ )
    //{
    //    ran        = i;
    //    s1.mSquare = 0;
    //    ASSERT_FALSE( s1.hasEce( ran ) );
    //    s1.putEce( ran );
    //    ASSERT_TRUE( s1.hasEce( ran ) );
    //    s1.popEce( ran );
    //    ASSERT_FALSE( s1.hasEce( ran ) );
    //}
}

TEST( SquareTest, hasPlrT )
{
    //*min
    srand( (unsigned int)time( 0 ) );
    Square s1;
    ASSERT_FALSE( 0 );
    s1.putEce( Global::GetEce( 0, 0 ) );
    ASSERT_TRUE( s1.hasPlr( 0 ) );
    for ( u64 i = 1; i <  MAX_PLAYERS; i++ )
    {
        ASSERT_FALSE( s1.hasPlr( i ) );
    }

    //* max
    s1.mSquare = 0;
    u64 ece    = Global::GetEce(  MAX_PLAYERS - 1,  MAX_PAWNS - 1 );
    ASSERT_FALSE( s1.hasPlr(  MAX_PLAYERS - 1 ) );
    s1.putEce( ece );
    ASSERT_TRUE( s1.hasPlr(  MAX_PLAYERS - 1 ) );
    for ( u64 i = 0; i <  MAX_PLAYERS - 1; i++ )
    {
        ASSERT_FALSE( s1.hasPlr( i ) );
    }

 
}

TEST( SquareTest, SetGetFlags )
{
    Square sq;
    auto   flag = b_SquareFlags::b_sq_valid;
    ASSERT_FALSE( sq.getFlag( flag ) );
    sq.setFlag( flag, true );
    ASSERT_TRUE( sq.getFlag( flag ) );
    sq.setFlag( flag, false );
    ASSERT_FALSE( sq.getFlag( flag ) );

    flag = b_SquareFlags::b_sq_safe;
    ASSERT_FALSE( sq.getFlag( flag ) );
    sq.setFlag( flag, true );
    ASSERT_TRUE( sq.getFlag( flag ) );
    sq.setFlag( flag, false );
    ASSERT_FALSE( sq.getFlag( flag ) );
}
