//------------------------------------------------------------------------------
//
// Filename: U33.cpp
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

//------------------------------------------------------------------------------
// System Includes
//------------------------------------------------------------------------------
#include <iostream>
#include <iomanip>

//------------------------------------------------------------------------------
// Library Includes
//------------------------------------------------------------------------------
#include "U33.h"

//------------------------------------------------------------------------------
// Namespaces
//------------------------------------------------------------------------------
using namespace std;

/// @name Constants
/// @{
static const unsigned int   MASK_OVERFLOW   (0x80000000);
static const unsigned int   MASK_32BIT      (0xffffffff);
static const unsigned int   MASK_17BIT      (0x1ffff);
static const unsigned int   MASK_16BIT      (0xffff);
static const unsigned int   MASK_1BIT       (0x1);
static const unsigned int   BIT17           (0x10000);
static const unsigned int   ONE             (1);
static const unsigned int   ZERO            (0);
static const int            MINUS_ONE       (-1);
static const U33            MAX33           (ONE,MASK_32BIT);
static const U33            ONE33           (ZERO,ONE);
/// @}

//------------------------------------------------------------------------------
//
U33::U33(unsigned int lsb32)
//
/// @brief Default Constructor
//------------------------------------------------------------------------------
    : mMsb17((lsb32 >> 16) & MASK_16BIT)
    , mLsb16(lsb32 & MASK_16BIT)
{
}

//------------------------------------------------------------------------------
//
U33::U33(unsigned int msb, unsigned int lsb32)
//
/// @brief Default Constructor
//------------------------------------------------------------------------------
    : mMsb17(((msb & MASK_1BIT) << 16) | ((lsb32 >> 16) & MASK_16BIT))
    , mLsb16(lsb32 & MASK_16BIT)
{
}

//------------------------------------------------------------------------------
//
U33::U33(const U33& ref)
//
/// @brief Copy Constructor
//------------------------------------------------------------------------------
    : mMsb17(ref.mMsb17)
    , mLsb16(ref.mLsb16)
{
}

//------------------------------------------------------------------------------
//
U33::~U33()
//
/// @brief Destructor
//------------------------------------------------------------------------------
{
}

//------------------------------------------------------------------------------
//
U33 U33::operator+(unsigned int val) const
//
/// @brief Addition Operator
//------------------------------------------------------------------------------
{
    const U33 convertedVal(ZERO, val);
    return (*this + convertedVal);
}

//------------------------------------------------------------------------------
//
U33 U33::operator+(int val) const
//
/// @brief Addition Operator
//------------------------------------------------------------------------------
{
    if (val < 0)
    {
        const U33 modVal(ONE, static_cast<unsigned int>(val * MINUS_ONE));
        return (*this - modVal);
    }
    else
    {
        const U33 convertedVal(ONE, static_cast<unsigned int>(val));
        return (*this + convertedVal);
    }
}

//------------------------------------------------------------------------------
//
U33 U33::operator-(unsigned int val) const
//
/// @brief Subtraction Operator
//------------------------------------------------------------------------------
{
    U33 convertedVal(ONE, val);
    return (*this - convertedVal);
}

//------------------------------------------------------------------------------
//
U33 U33::operator-(int val) const
//
/// @brief Subtraction Operator
//------------------------------------------------------------------------------
{
    if (val < 0)
    {
        const U33 modVal(ONE, static_cast<unsigned int>(val * MINUS_ONE));
        return (*this + modVal);
    }
    else
    {
        const U33 convertedVal(ONE, static_cast<unsigned int>(val));
        return (*this - convertedVal);
    }
}

//------------------------------------------------------------------------------
//
U33 U33::operator+(const U33& ref) const
//
/// @brief Addition Operator
//------------------------------------------------------------------------------
{
    // create copy
    U33 newValue(*this);

    newValue.mLsb16 += ref.mLsb16;
    newValue.mMsb17 += (ref.mMsb17 + ((newValue.mLsb16 & (~MASK_16BIT)) >> 16));
    newValue.mMsb17 &= MASK_17BIT;

    // return new value
    return newValue;
}

//------------------------------------------------------------------------------
//
U33 U33::operator-(const U33& ref) const
//
/// @brief Subtraction Operator
//------------------------------------------------------------------------------
{
    U33 newValue(*this);

    // check for the simple case
    if (newValue >= ref)
    {
        // simple deduction
        newValue.mMsb17 -= ref.mMsb17;
        newValue.mLsb16 -= ref.mLsb16;

        // check overflow
        if (newValue.mLsb16 & MASK_OVERFLOW)
        {
            newValue.mMsb17 -= 1;
            newValue.mLsb16 &= MASK_16BIT;
        }
    }
    else
    {
        // complex deduction
        newValue = (MAX33 - ref) + (*this + ONE33);
    }

    return newValue;
}

//------------------------------------------------------------------------------
//
const U33& U33::operator=(const U33& ref)
//
/// @brief Assignment Operator
//------------------------------------------------------------------------------
{
    // assign over the variables
    mMsb17 = ref.mMsb17;
    mLsb16 = ref.mLsb16;

    return *this;
}

//------------------------------------------------------------------------------
//
const U33& U33::operator+=(const U33& ref)
//
/// @brief Addition Equals Operator
//------------------------------------------------------------------------------
{
    // calculate the new value
    const U33 newValue = *this + ref;

    // assign the new value
    *this = newValue;

    // return a reference to ourself
    return *this;
}

//------------------------------------------------------------------------------
//
const U33& U33::operator-=(const U33& ref)
//
/// @brief Subtraction Equals Operator
//------------------------------------------------------------------------------
{
    // calculate the new value
    const U33 newValue = *this - ref;

    // assign the new value
    *this = newValue;

    // return a reference to ourself
    return *this;
}

//------------------------------------------------------------------------------
//
bool U33::operator==(const U33& ref) const
//
/// @brief Equality Operator
//------------------------------------------------------------------------------
{
    if ( (ref.mMsb17 == mMsb17) &&
         (ref.mLsb16 == mLsb16) )
    {
        return true;
    }

    return false;
}

//------------------------------------------------------------------------------
//
bool U33::operator!=(const U33& ref) const
//
/// @brief Inequality Operator
//------------------------------------------------------------------------------
{
    return ( !
             (*this == ref)
           );
}

//------------------------------------------------------------------------------
//
bool U33::operator<(const U33& ref) const
//
/// @brief Less Than Operator
//------------------------------------------------------------------------------
{
    return (
             (mMsb17 < ref.mMsb17)
             ||
             (
               (mMsb17 == ref.mMsb17)
               &&
               (mLsb16  < ref.mLsb16)
             )
           );
}

//------------------------------------------------------------------------------
//
bool U33::operator<=(const U33& ref) const
//
/// @brief Less Than Equals Operator
//------------------------------------------------------------------------------
{
    return (
             (*this < ref)
             ||
             (*this == ref)
           );
}

//------------------------------------------------------------------------------
//
bool U33::operator>(const U33& ref) const
//
/// @brief More Than Operator
//------------------------------------------------------------------------------
{
    return ( !
             (*this <= ref)
           );
}

//------------------------------------------------------------------------------
//
bool U33::operator>=(const U33& ref) const
//
/// @brief More Than Equals Operator
//------------------------------------------------------------------------------
{
    return (
             (*this > ref)
             ||
             (*this == ref)
           );
}

//------------------------------------------------------------------------------
//
void U33::getRaw(unsigned int& msb17, unsigned int& lsb16) const
//
/// @brief Raw Access Getter
//------------------------------------------------------------------------------
{
    // return the raw values
    msb17 = mMsb17;
    lsb16 = mLsb16;
}

//------------------------------------------------------------------------------
//
bool U33::getMsb() const
//
/// @brief MSB Getter
/// @return The MSB of the 33 bit value
//------------------------------------------------------------------------------
{
    return ((mMsb17 & BIT17) ? true : false);
}

//------------------------------------------------------------------------------
//
bool U33::getLsb() const
//
/// @brief LSB Getter
/// @return The LSB of the 33 bit value
//------------------------------------------------------------------------------
{
    return ((mLsb16 & ONE) ? true : false);
}

//------------------------------------------------------------------------------
//
unsigned int U33::getMsb32() const
//
/// @brief 32bit MSB Getter
/// @return The 32 MSB of the 33 bit value
//------------------------------------------------------------------------------
{
    unsigned int msb32(0);

    msb32 |= (((mMsb17 >> 1) & MASK_16BIT) << 16);
    msb32 |= (mLsb16 & MASK_16BIT);

    return msb32;
}

//------------------------------------------------------------------------------
//
unsigned int U33::getLsb32() const
//
/// @brief 32bit LSB Getter
/// @return The 32 LSB of the 33 bit value
//------------------------------------------------------------------------------
{
    unsigned int lsb32(0);

    lsb32 |= (mMsb17 & MASK_16BIT) << 16;
    lsb32 |= (mLsb16 & MASK_16BIT) <<  0;

    return lsb32;
}

//------------------------------------------------------------------------------
//
std::ostream& operator<<(std::ostream& stream, const U33& value)
//
/// @brief Stream Output Operator
/// @return A Reference to the modified stream
//------------------------------------------------------------------------------
{
    // convert to 1 : 32 form
    const unsigned int msb   = (value.mMsb17 & BIT17) ? ONE : ZERO;
    const unsigned int lsb32 = (
                                 ((value.mMsb17 & MASK_16BIT) << 16)
                                 |
                                 (value.mLsb16 & MASK_16BIT)
                               );

    // generate the stream notation (hex)
    stream << "0x" << msb << setw(8) << setfill('0') << hex << lsb32 << dec;

    return stream;
}
