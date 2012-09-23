//------------------------------------------------------------------------------
//
// Filename: profile.cpp
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
#include <sstream>
#include "U33.h"

using namespace std;

static const U33 A(0,1);
static const U33 B(1,0xffffffff);

void loop(U33& value)
{
    value = A - B;
}

int main(int argc, char** argv)
{
    if (argc == 2)
    {
        unsigned int count(0);

        istringstream iss(argv[1]);
        iss >> count;

        cout << "Count: " << count << endl;

        U33 val;

        for (unsigned int i=0; i<count; ++i)
            loop(val);
    }
    else
    {
        return 1;
    }

    return 0;
}
