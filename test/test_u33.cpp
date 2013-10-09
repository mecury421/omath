//------------------------------------------------------------------------------
//
// Filename: test.cpp
// Author:   Ed FitzGerald
//
// Copyright (c) 2012 Ed FitzGerald
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//------------------------------------------------------------------------------

#include <iostream>
#include <stdexcept>
#include "U33.h"

typedef unsigned long long U64;

static const U64 MASK33(0x1ffffffff);
static const U64 MASK32(0x0ffffffff);
static const bool DumpAll(false);

using namespace std;

U33 convert(const U64& ref)
{
    U64 val(ref);

    // do 33bit mask
    val &= MASK33;

    const unsigned int msb   = (val & 0x100000000) ? 1 : 0;
    const unsigned int lsb32 = static_cast<unsigned int>(val & MASK32);

    return U33(msb,lsb32);
}

U64 convert(const U33& ref)
{
    unsigned int msb17(0);
    unsigned int lsb16(0);

    // get the raw values
    ref.getRaw(msb17,lsb16);

    U64 value(0);

    value |= (static_cast<U64>(lsb16 & 0xffff) <<  0);
    value |= (static_cast<U64>(msb17 & 0xffff) << 16);

    if (msb17 & 0x10000)
        value |= 0x100000000;

    return value;
}

void checkAddition(U64 a, U64 b)
{
    const U64 expectedValue = (a + b) & MASK33;

    // convert the 64bit numbers to 33 bits
    const U33 a33 = convert(a);
    const U33 b33 = convert(b);

    // do the addition
    const U33 result33 = a33 + b33;

    // convert the result
    const U64 result = convert(result33);

    // check the result
    const bool success = (result == expectedValue);

    // check for the lack of sweet success
    if (!success || DumpAll)
    {
        cout << "==============================================================" << endl;
        cout << "DUMP ADDITION" << endl;
        cout << "==============================================================" << endl;
        cout << "a              : 0x" << hex << a << endl;
        cout << "b              : 0x" << hex << b << endl;
        cout << "expectedValue  : 0x" << hex << expectedValue << endl;
        cout << "a33            : " << a33 << endl;
        cout << "b33            : " << b33 << endl;
        cout << "result33       : " << result33 << endl;
        cout << "result         : 0x" << hex << result << endl;
        cout << "success        : " << boolalpha << success << endl;
        cout << "==============================================================" << endl << endl;
    }

    if (!success)
    {
        throw std::logic_error("Test failure");
    }
}

void checkSubtraction(U64 a, U64 b)
{
    ///----------------------------------------------------------------
    U64 expectedValue = (a >= b) ? (a - b) : (((MASK33) - b) + a + 1);
    if (b)
    {
        if (a >= b)
        {
            expectedValue = a - b;
        }
        else
        {
            expectedValue = (MASK33 - (b - 1)) + a;
        }
    }
    else
    {
        expectedValue = a;
    }
    ///----------------------------------------------------------------

    // convert the 64bit numbers to 33 bits
    const U33 a33 = convert(a);
    const U33 b33 = convert(b);

    // do the addition
    const U33 result33 = a33 - b33;

    // convert the result
    const U64 result = convert(result33);

    // check the result
    const bool success = (result == expectedValue);

    // check for the lack of sweet success
    if (!success || DumpAll)
    {
        cout << "==============================================================" << endl;
        cout << "DUMP SUBTRACTION" << endl;
        cout << "==============================================================" << endl;
        cout << "a              : 0x" << hex << a << endl;
        cout << "b              : 0x" << hex << b << endl;
        cout << "expectedValue  : 0x" << hex << expectedValue << endl;
        cout << "a33            : " << a33 << endl;
        cout << "b33            : " << b33 << endl;
        cout << "result33       : " << result33 << endl;
        cout << "result         : 0x" << hex << result << endl;
        cout << "success        : " << boolalpha << success << endl;
        cout << "==============================================================" << endl << endl;
    }

    if (!success)
    {
        throw std::logic_error("Test failure");
    }
}

int main()
{
    checkAddition(0x1, 0x1);
    checkAddition(0x1ffffffff, 0x1);
    checkAddition(0x1, 0x1ffffffff);
    checkAddition(0x1ffffffff, 0x1ffffffff);
    checkAddition(0, 0);
    checkAddition(1234567, 1111111);

    checkSubtraction(0x1, 0x1);
    checkSubtraction(0x1ffffffff, 0x1);
    checkSubtraction(0x1, 0x1ffffffff);
    checkSubtraction(0x1ffffffff, 0x1ffffffff);
    checkSubtraction(0, 0);
    checkSubtraction(1234567, 1111111);

    cout << "Sweet success!" << endl;

    return 0;
}
