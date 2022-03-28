#pragma once


#include "global.h"
#include "helper.h"
using namespace Global;

//$ To do make them defines or somethig 
//$ remove error checking to allow true inlining

//void SetBit( u64& num, u64 bit );
//void UnSetBit( u64& num, u64 bit );
//u64 GetBit(u64 num, u64 bit);
//
//void SetBits( u64& num, u64 bits, u64 posi, u64 count );
//u64 GetBits( u64 num, u64 posi, u64 count );

//$ if bits in '<<' opertor are not u64 anything aboove 31 will be set to 1

inline constexpr void SetBit( u64& num, u64 bit )
{
    assert( ( bit >= 0 && bit < 64 ) );
    num |= (u64)1 << bit;
}
inline constexpr void UnSetBit( u64& num, u64 bit )
{
    assert( ( bit >= 0 && bit < 64 ) );
    //%set it to 1 then negate it = ~(SetBit)
    num &= ~( (u64)1 << bit );
}
inline constexpr u64 GetBit( u64 num, u64 bit )
{  //$may not be trivial to inline
    assert( ( bit >= 0 && bit < 64 ) );
    return ( ( num >> bit ) & (u64)1 );
}

inline constexpr void SetBits( u64& num, u64 bits, u64 posi, u64 count )
{
    //%pow(2,n) is ( (u64)1 << count )

    assert( count > 0 && count < 64 && posi >= 0 && posi < 64 );
    assert( posi + count <= 64 );
    assert( bits <= ( ( (u64)1 << count ) - 1 ) );
    // assert( bits <= ( (u64)pow( 2, count ) - 1 ) );

    // num &= ~( ( (u64)pow( 2, count ) - 1 ) << posi );
    //%clear those bits to zero and set new
    num &= ~( ( ( (u64)1 << count ) - 1 ) << posi );
    num |= (u64)bits << posi;
}

inline constexpr u64 GetBits( u64 num, u64 posi, u64 count )
{
    assert( count > 0 && count < 64 && posi >= 0 && posi < 64 );
    assert( posi + count <= 64 );
    //% shift and clear else the rest bits, will go 1 all ovver 32
    //return ( num >> (u64)posi ) & ( (u64)pow( 2, count ) - 1 );
    return ( num >> (u64)posi ) & ( ((u64)1 << count) - 1 );
}
