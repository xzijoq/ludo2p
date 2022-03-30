#include "visualtest.h"

#include "global.h"
#include "helper.h"
#include "square.h"


void PieceDeStringTest()
{
    Piece p1;
    p1.mPiece = 0;

    p1.mPiece=SetBits( p1.mPiece, 0b1101110110110, 0, 13 );
    p1.setEce( 47 );
    p1.setSq( 123 );
    p1.setEntrySq( 10 );
    p1.setSwitchSq( 111 );
    print( okStyle, "\n{}\n", p1.DebugString() );
    std::cout.flush();
}

void SquareDeStringTest()
{
    Square s1;
    print( okStyle, " {}\n", s1.DebugString() );
    for ( auto i = 0; i < (int)Global::MAX_PLAYERS; i++ )
    {
        for ( auto j = 0; j < (int)Global::MAX_PAWNS; j++ )
        {
            s1.putEce( Global::GetEce( (u64)i, (u64)j ) );
            print( okStyle, " {}\n", s1.DebugString() );
        }
    }
}
