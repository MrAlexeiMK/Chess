#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <string>

class complex {
    public:
        double real, image;

        complex();
        complex(double r);
        complex(double r, double im);

        complex operator+(const complex& other);
        complex operator-(const complex& other);
        complex operator*(const complex& other);
        complex operator*(const double& other);
        complex operator/(const complex& other);
        complex& operator=(const complex& other);
        bool operator== (const complex& other);
        bool operator== (const complex& other) const;
        bool operator!= (const complex& other);
        complex operator~();
        complex operator-();

        friend std::ostream& operator<< (std::ostream& out, const complex& x);
        friend std::istream& operator>> (std::istream& out, complex& x);
};
#endif