//------------------------------------------------------------------------------
//
// Filename: U33.h
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

#ifndef OMATH_U33_H
#define OMATH_U33_H

//------------------------------------------------------------------------------
// System Includes
//------------------------------------------------------------------------------
#include <iosfwd>

//------------------------------------------------------------------------------
// Library Includes
//------------------------------------------------------------------------------
// none

//------------------------------------------------------------------------------
//
class U33
//
/// @name 33 Bit Unsigned Integer
//------------------------------------------------------------------------------
{
public:

    /// @name Construction / Destruction
    /// @{
    explicit U33(unsigned int lsb32);
    U33(unsigned int msb=0, unsigned int lsb32=0);
    U33(const U33& ref);
    ~U33();
    /// @}

    /// @name Addition / Subtraction Methods
    /// @{
    U33 operator+(unsigned int val) const;
    U33 operator-(unsigned int val) const;
    U33 operator+(int val) const;
    U33 operator-(int val) const;
    U33 operator+(const U33& ref) const;
    U33 operator-(const U33& ref) const;
    /// @}

    /// @name Assignment Operator
    /// @{
    const U33& operator=(const U33& ref);
    /// @}

    /// @name Addition / Subtraction Changer Methods
    /// @{
    const U33& operator+=(const U33& ref);
    const U33& operator-=(const U33& ref);
    /// @}

    /// @name Equality / Inequality Methods
    /// @{
    bool operator==(const U33& ref) const;
    bool operator!=(const U33& ref) const;
    bool operator< (const U33& ref) const;
    bool operator<=(const U33& ref) const;
    bool operator> (const U33& ref) const;
    bool operator>=(const U33& ref) const;
    /// @}

    /// @name Getters
    /// @{
    void getRaw(unsigned int& msb17, unsigned int& lsb16) const;
    bool getMsb() const;
    bool getLsb() const;
    unsigned int getMsb32() const;
    unsigned int getLsb32() const;
    /// @}

    /// @name Stream Operator
    /// @{
    friend std::ostream& operator<<(std::ostream& stream, const U33& value);
    /// @}

private:

    /// @name Variables
    /// @{
    unsigned int mMsb17;    ///< The 17 most significant bits
    unsigned int mLsb16;    ///< The 16 least significant bits
    /// @}
};

#endif // OMATH_U33_H
