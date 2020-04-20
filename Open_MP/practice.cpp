#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

int f(int m, int n)
{
    int x = m + n;
    return (((x - 2) * (x - 1) / 2) + m);
}

void invert(int y, int& m, int& n)
{
    int x = 8; // what should this assignment to x really be?
    m = y - ((x-1)*(x-2)/2);
    n = x - m;
}

int main(int argc, char* argv[])
{
    //int y = (argc > 1) ? atoi(argv[1]) : global_y;
    int y = 23;
    int m = 0;
    int n = 0;
    invert(y, m, n);
    // check answer
    cout << "m = " << m << ", n = " << n << ", y = " << y << endl;

    if (y == f(m, n)) {
        cout << "m = " << m << ", n = " << n << endl;
    }
    return 0;
}
