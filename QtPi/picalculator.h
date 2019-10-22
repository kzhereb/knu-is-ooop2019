#ifndef PICALCULATOR_H
#define PICALCULATOR_H


class PiCalculator
{
public:
    PiCalculator();
    virtual ~PiCalculator();
    virtual double calculate(int steps) const =0;
};


class AtanCalculator: public PiCalculator {
public:
    double calculate(int steps) const override;
};

class IntegrateCalculator: public PiCalculator {
public:
    double calculate(int steps) const override;
};

class MonteCarloCalculator: public PiCalculator {
public:
    double calculate(int steps) const override;
};

class TwoAtanCalculator: public PiCalculator {
private:
    int a1,b1,c1, a2,b2,c2;
    double atan(double x, int steps) const;
public:
    TwoAtanCalculator(int a1,int b1,int c1, int a2,int b2,int c2);
    double calculate(int steps) const override;
};
#endif // PICALCULATOR_H
