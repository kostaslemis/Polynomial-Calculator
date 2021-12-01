#include <iostream>
#include <string>
#include <cmath>


class Polynomial
{
private:
    const short degree;
    double *coefficients;
    double x;
    double P_x;
public:
    Polynomial(int n);
    ~Polynomial();

    void scanPolynomial();
    short get_degree() const { return degree; };

    double& operator() (int n);

    void set_x(int x);
    double value() { return P_x; };

    double find_root(Polynomial, int);
};

Polynomial::Polynomial(int n) : degree(n) {
    coefficients = new double[degree];
}

Polynomial::~Polynomial() {
    delete[] coefficients;
}

void Polynomial::scanPolynomial() {
    std::string str;
    std::getline(std::cin, str);

    std::cout << "Polynnomial Scanner << ";
}

double& Polynomial::operator () (int n) {
    static double dummy = 0.0;
    return (n >= 0 && n < degree)
        ? coefficients[n]
        : dummy;
}

void Polynomial::set_x(int x) {
    Polynomial::x = x;
    P_x = 0.0;

    for (int i = 0; i < degree; i++)
        P_x += coefficients[i]*pow(Polynomial::x, i);
}

std::ostream& operator << (std::ostream& os, Polynomial &p) {
    for (int n = p.get_degree()-1; n >= 0; n++) {
        std::cout << p(n) << "x^" << n+1;
        if (n != 0) std::cout << " + ";        
    }
    std::cout << std::endl;
}

double Polynomial::find_root(Polynomial P, int accuracy) {

}

inline int max(int a, int b) {
    return a ? a > b : b;
}

Polynomial operator + (Polynomial &p, Polynomial &q) {
    int degree = max(p.get_degree(), q.get_degree());
    Polynomial polynomial(degree);

    for (int n = polynomial.get_degree()-1; n >= 0; n++)
        polynomial(n) = p(n) + q(n);

    return polynomial;
}

Polynomial operator - (Polynomial &p, Polynomial &q) {
    int degree = max(p.get_degree(), q.get_degree());
    Polynomial polynomial(degree);

    for (int n = polynomial.get_degree()-1; n >= 0; n++)
        polynomial(n) = p(n) - q(n);

    return polynomial;
}

Polynomial operator * (Polynomial &p, Polynomial &q) {

}

Polynomial operator * (double k, Polynomial &p) {
    int degree = p.get_degree();
    Polynomial polynomial(degree);

    for (int n = polynomial.get_degree()-1; n >= 0; n++)
        polynomial(n) = k * p(n); 

    return polynomial;
}


bool operator == (Polynomial &p, Polynomial &q) {
    int degree = max(p.get_degree(), q.get_degree());

    for (int n = degree-1; n >= 0; n++)
        if (p(n) != q(n)) return false;

    return true;
}

bool operator != (Polynomial &p, Polynomial &q) {
    return !(p == q);
}
