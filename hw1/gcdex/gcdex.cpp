#include <iostream>
#include "gcdex.h"

using namespace std;

int main()
{
    int a, b, x, y;
    cin >> a >> b;
    int GCD = gcdex(a, b, x, y);
    cout << a << '*' << x << " + " << b << '*' << y << " = " << GCD << endl;
    if(invert(a, b, x))
        cout << x << endl;
    else
        cout << "false" << endl;
    return 0;
}

