#include "picalculator.h"

PiCalculator::PiCalculator()
{

}

PiCalculator::~PiCalculator()
{

}
//
double AtanCalculator::calculate(int steps)
{
    double sum = 0.0;
    double sign = 1.0;
    for (int i=0;i<steps;i++) {
        sum += sign/(2*i+1);
        sign = -sign;
    }
    return 4*sum;
}
