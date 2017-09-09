#include "stdafx.h"
#include "test_bitset.h"
#include <bitset>


test_bitset::test_bitset()
{
    std::bitset<64> bit64(false);
    assert(bit64.to_ullong() == 0);
    assert(!bit64[0]);
    bit64.set(0, true);
    assert(bit64[0]);
    bit64.set(0, false);
    assert(!bit64[0]);
    bit64.flip(0);
    assert(bit64[0]);
    assert(bit64.to_ullong() == 0X0000000000000001);

    assert(!bit64[63]);
    bit64.set(63, true);
    assert(bit64[63]);
    bit64.set(63, false);
    assert(!bit64[63]);
    bit64.flip(63);
    assert(bit64[63]);
    assert(bit64.to_ullong() == 0X8000000000000001);

    bit64 = 0;
    assert(!bit64[0]);
    assert(!bit64[63]);

    bit64 = 0X8000000000000001;
    assert(bit64[0]);
    assert(!bit64[1]);
    assert(!bit64[62]);
    assert(bit64[63]);
}


test_bitset::~test_bitset()
{
}
