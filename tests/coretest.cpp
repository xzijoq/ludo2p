#include <gtest/gtest.h>
#include <math.h>

#include <cstdint>
#include <limits>

#include "core.h"
#include "global.h"
#include "helper.h"
#include "piece.h"
#include "square.h"
using std::cout;
using std::endl;
TEST( GlobalTest, GlobalConstraints )
{
    ASSERT_LE( CURRENT_PLAYERS * CURRENT_PAWNS, MAX_PIECE_COUNT );
}

TEST( Core, bits )
{
    // DisplayBits(num);
    //$SetBit
    u64 num = 0;
    SetBit( num, 31 );
    ASSERT_EQ( num, 2147483648 );
    num = 0;
    SetBit( num, 32 );
    ASSERT_EQ( num, 4294967296 );

    //$UnSetBit
    num = UINT64_MAX;
    UnSetBit( num, 63 );
    ASSERT_EQ( num, 9223372036854775807 );
    num = 0b11;
    UnSetBit( num, 1 );
    ASSERT_EQ( num, 1 );

    //$GetBit
    num = 0b100011;
    ASSERT_EQ( GetBit( num, 0 ), 1 );
    ASSERT_EQ( GetBit( num, 2 ), 0 );
    num = UINT64_MAX;
    ASSERT_EQ( GetBit( num, 63 ), 1 );
    num = UINT64_MAX / 2;
    ASSERT_EQ( GetBit( num, 63 ), 0 );

    //$SetBits
    num       = 0;
    int count = 5;
    u64 bits  = 0b11111;
    int posi  = 28;
    SetBits( num, bits, posi , count);
    ASSERT_EQ( num, 8321499136 );

    //$GetBits
    num = 0b110011;
    ASSERT_EQ( GetBits( num, 0, 3 ), 0b011 );
    SetBits( num, 0b11001, 28, 5 );
    ASSERT_EQ( GetBits( num, 28, 5 ), 0b11001 );
    num = 6710886451;
    ASSERT_EQ( GetBits( num, 0, 3 ), 0b011 );
    ASSERT_EQ( GetBits( num, 28, 5 ), 0b11001 );

    //    DisplayBits( num );
}

int main( int argc, char* argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
