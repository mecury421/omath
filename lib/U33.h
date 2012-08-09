//------------------------------------------------------------------------------
//
// Name:    U33.h
// Author:  Ed FitzGerald
//
//------------------------------------------------------------------------------

#ifndef U33_H
#define U33_H

#include <iosfwd>

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

#endif // U33_H
