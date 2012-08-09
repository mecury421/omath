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
