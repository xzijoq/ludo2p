//! this is very important or everythoing will be a waste
//! REad ahead
//$ To do make them defines or somethig
//$ remove error checking to allow true inlining
//$ they must be inlined
#include <core.h>
#include <fmt/format.h>
#include <helper.h>
#include <math.h>

#include <array>
#include <cstdint>

#ifdef NDEBUG
    #undef NDEBUG
#endif
#include <cassert>

//$ if bits in '<<' opertor are not u64 anything aboove 31 will be set to 1

void SetBit( u64& num, int bit )
{
    assert( ( bit >= 0 && bit < 64 ) );
    num |= (u64)1 << bit;
}
void UnSetBit( u64& num, int bit )
{
    assert( ( bit >= 0 && bit < 64 ) );
    //%set it to 1 then negate it = ~(SetBit)
    num &= ~( (u64)1 << bit );
}
u64 GetBit( u64 num, int bit )
{  //$may not be trivial to inline
    assert( ( bit >= 0 && bit < 64 ) );
    return ( ( num >> bit ) & (u64)1 );
}

void SetBits( u64& num, u64 bits, int posi, int count )
{
    //%pow(2,n) is optimised away, verified godbolt

    assert( count > 0 && count < 64 && posi >= 0 && posi < 64 );
    assert( posi + count <= 64 );
    assert( bits <= ( (u64)pow( 2, count ) - 1 ) );

    //%clear those bits to zero and set new
    num &= ~( ( (u64)pow( 2, count ) - 1 ) << posi );
    num |= (u64)bits << posi;
}

u64 GetBits( u64 num, int posi, int count )
{
    assert( count > 0 && count < 64 && posi >= 0 && posi < 64 );
    assert( posi + count <= 64 );
    //% shift and clear else the rest bits, will go 1 all ovver 32
    return ( num >> (u64)posi ) &  ( (u64)pow( 2, count ) - 1 );
}
