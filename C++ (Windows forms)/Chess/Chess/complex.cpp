using namespace std;
#include "complex.h"

complex::complex() {
    real = 0;
    image = 0;
}
 
complex::complex(double r) {
    real = r;
    image = 0;
}

complex::complex(double r, double im) {
    real = r;
    image = im;
}

complex complex::operator*(const complex& other) {
    return complex(real * other.real - image * other.image,
        real * other.image + image * other.real);
}

complex complex::operator*(const double& other) {
    return complex(real * other, image * other);
}

complex complex::operator+(const complex& other) {
    return complex(real + other.real, image + other.image);
}

complex complex::operator-(const complex& other) {
    return complex(real - other.real, image - other.image);
}

complex complex::operator/ (const complex& other) {
    if ((complex)other != 0) {
        double div = (other.real * other.real) + (other.image * other.image);
        complex tmp;
        tmp.real = (real * other.real) + (image * other.image);
        tmp.real /= div;
        tmp.image = (image * other.real) - (real * other.image);
        tmp.image /= div;
        return tmp;
    }
    throw std::invalid_argument("divide by zero");
}

complex complex::operator~() {
    return complex(real, -image);
}

complex complex::operator-() {
    return complex(-real, -image);
}

bool complex::operator== (const complex& other) {
    return (real == other.real && image == other.image);
}

bool complex::operator== (const complex& other) const {
    return (real == other.real && image == other.image);
}

bool complex::operator!= (const complex& other) {
    return (real != other.real || image != other.image);
}

complex& complex::operator=(const complex& other) {
    if (this != &other) {
        real = other.real;
        image = other.image;
    }
    return *this;
}

ostream& operator<< (ostream& out, const complex& x) {
    double im = x.image;
    double r = x.real;
    //if (abs(im) < 1e-8) im = 0;
    //if (abs(r) < 1e-8) r = 0;
    if (im == 0) {
        return (out << r);
    }
    if (r == 0) {
        if (im == 1) return (out << "i");
        if (im == -1) return (out << "-i");
        return (out << im << "i");
    }
    if (im == 1) return (out << r << "+" << "i");
    if (im == -1) return (out << r << "-" << "i");
    if (im > 0) return (out << r << "+" << im << "i");

    return (out << r << "-" << -im << "i");
}

istream& operator>> (istream& in, complex& x) {
    string temp;
    int p1 = 0, p2 = 0;

    in >> temp;
    for (int i = 0; i < temp.size(); ++i) {
        if (temp[i] == 'i') {
            p1 = i;
        }
        else if (temp[i] == '+' || temp[i] == '-') {
            p2 = i;
        }
    }
    if (temp[p1] != 'i') {
        x.image = 0;
        x.real = stod(temp);
    }
    else if (p2 == 0) {
        x.real = 0;
        string t = temp.substr(0, temp.size() - 1);
        if (t.empty() || (t.size() == 1 && t[0] == '+')) t = "1";
        else if (t.size() == 1 && t[0] == '-') t = "-1";
        x.image= stod(t);
    }
    else {
        string real, image;
        if (p1 < p2) {
            real = temp.substr(p2);
            image = temp.substr(0, p1);
            if (image.empty() || (image.size() == 1 && image[0] == '+')) image = "1";
            else if (image.size() == 1 && image[0] == '-') image = "-1";
        }
        else {
            real = temp.substr(0, p2);
            image = temp.substr(p2);
            image = image.substr(0, image.size() - 1);
            if (image.empty() || (image.size() == 1 && image[0] == '+')) image = "1";
            else if (image.size() == 1 && image[0] == '-') image = "-1";
        }

        x.real = stod(real);
        x.image = stod(image);
    }
    return in;
}