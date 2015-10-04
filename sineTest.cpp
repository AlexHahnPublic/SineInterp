#include "sineTest.h"
// Add your header file here
#include "LeastSquareSine.h"

#include <cmath>
#include <ctime>
#include <iostream>
#include <limits>

using namespace std;

void EvaluateYourSine(SinePrototype *yoursine, const char *name);
#define NTIME 10000
#define NERR 1000000
// tunable parameters
static double randarr[NTIME];

int main()
{
    clock_t st, ed;

    // generate an array of random numbers to test the time
    for(int i=0; i<NTIME; i++) {
        randarr[i] = rand()*2.*M_PI/RAND_MAX;
    }

    // Instantiate machineSine, linearSine
    // Add your sine class and call EvaluateYourSine with your class instance.
    SinePrototype machineSine;
    LinearSine linear(17);
    
    EvaluateYourSine(&machineSine, "our machine sine");
    EvaluateYourSine(&linear, "least squares sine (using legendre polynomials)");
    //cout << linear.sine(0.7) << ", " << machineSine.sine(0.7) << linear.sine(0.7) - machineSine.sine(0.7) << "\n";

    //for (int i = 1; i < 45; i++) {
    //    cout << "Iteration " << (2*i-1) << endl;
    //    LinearSine l(2*i-1);
    //    EvaluateYourSine(&l, "least squares sine (using legendre polynomials)");
    //    cout << l.sine(0.7) << ", " << machineSine.sine(0.7) << l.sine(0.7) - machineSine.sine(0.7) << "\n";
    //}
}

void EvaluateYourSine(SinePrototype *yoursine, const char *name) {
    clock_t st, ed;
    double tmp;

    st = clock();
    for(int i=0; i<NTIME; i++) {
    // We add up the results to keep the optimizing compiler from removing the line
        tmp += yoursine->sine(randarr[i]);
    }
    ed = clock();
    cout << "Time for " << name << ":" << endl;
    cout << (double(ed)-double(st))/CLOCKS_PER_SEC << "s per " << NTIME << " repetitions" << endl;

    // Evaluate errors
    double errorMax = 0.;
    double avg = 0.;
    double avg2 = 0.;
    int ii = 0;
    double err;
    for(double t=0.; t<2.*M_PI; t += 2.*M_PI/NERR) {
       ii++;
       err = abs(yoursine->sine(t) - sin(t));
       if (errorMax <= err) errorMax = err; 
       avg = (avg*(ii-1)+err)/ii;
       avg2 = (avg2*(ii-1)+err*err)/ii;
    }

    // print error
    cout << "Maximum Error   = " << errorMax << endl;
    cout << "Average Error   = " << avg << endl;
    cout << "Standard Deviat = " << sqrt(avg2 - avg*avg) << endl << endl;
}