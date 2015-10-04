#include <cmath>
#include <ctime>
#include <iostream>
#include <limits>
#include "ttmath/ttmath.h"
#define PI 3.141592653589793238462643383279502884

using namespace std;

typedef ttmath::Big<TTMATH_BITS(64), TTMATH_BITS(1024)> MyBig;

double ccoef(int n,int d) {
    double r = 1;
    for (int i = 2*n+1; i <= 2*(n+d)+1; i++) {
        r *= PI/i;
    }
    return r;
}

int main()
{
    MyBig pi = 0.;
    pi.SetPi();
    MyBig b = 1.;
    int n = 100; int mm = 10;
    double* Sn = (double*)malloc(sizeof(double)*(n+1));
    double* Sn2 = (double*)malloc(sizeof(double)*(n+1));
    Sn[0] = 0;
    Sn[1] = b.ToDouble();
    Sn2[0] = 0;
    Sn2[1] = 1;
    for (int i = 2; i <= n; i+=2) {
            MyBig t = (i+1)*i;
            b = MyBig(1) - t/(pi*pi)*b;
            Sn[i] = 0;
            Sn[i+1] = b.ToDouble();

            Sn2[i] = 0;
            int xy = -1; 
            double rr = 0;
            for (int d = 1; d <= mm; d++) {
                rr += xy*ccoef(i/2+1,d);
                xy *= -1;
            }
            Sn2[i+1] = -rr;
    }

    for (int i = 1; i <= n; i += 2) {
        cout << "i = " << i << ", S(i) = " << Sn[i] << ", S.(i) = " << Sn2[i] << endl;
    }

    return 0;
}
