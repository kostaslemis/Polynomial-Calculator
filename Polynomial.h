#include <iostream>
#include <string>
#include <cmath>


class Polynomial
{
private:
    const short _degree;
    double *coefficients;
    double _x;
    double _P_x;
public:
    Polynomial(int n);
    ~Polynomial();

    void scanPolynomial();
    short degree() const { return _degree; };

    double& operator() (int n);

    void set_x(int x);
    double P_x() { return _P_x; };

    double find_root(Polynomial, int);
};

Polynomial::Polynomial(int degree) : _degree(degree) {
    coefficients = new double[_degree+1];
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
    return (n >= 0 && n <= _degree)
        ? coefficients[n]
        : dummy;
}

void Polynomial::set_x(int x) {
    _x = x;
    _P_x = 0.0;

    for (int i = 0; i <= _degree; i++)
        _P_x += coefficients[i]*pow(_x, i);
}

std::ostream& operator << (std::ostream& os, Polynomial &p) {
    for (int n = p.degree(); n > 1; n--)
        os << p(n)<<"x^"<<n << " + ";
    os << p(1)<<"x" << " + "; 
    os << " + " << p(0);       
    os << std::endl;

    return os;
}

// double Polynomial::find_root(Polynomial P, int accuracy) {

// }

int max(int a, int b) {
    return a ? a > b : b;
}

Polynomial operator + (Polynomial &p, Polynomial &q) {
    int degree = max(p.degree(), q.degree());
    Polynomial polynomial(degree);

    for (int n = degree; n >= 0; n++)
        polynomial(n) = p(n) + q(n);

    return polynomial;
}

Polynomial operator - (Polynomial &p, Polynomial &q) {
    int degree = max(p.degree(), q.degree());
    Polynomial polynomial(degree);

    for (int n = degree; n >= 0; n++)
        polynomial(n) = p(n) - q(n);

    return polynomial;
}

Polynomial operator * (Polynomial &p, Polynomial &q) {
    int degree = p.degree() + q.degree();
    Polynomial polynomial(degree);

    int n = max(p.degree(), q.degree());
    for (int k = 0; k <= 2*n; k++) {
        double diagonal_sum_k = 0;
        if (k <= n)
            for (int i = 0, j = k; i <= k && j >= 0; i++, j--)
                diagonal_sum_k += p(i)*q(j);
        else
            for (int i = n, j = k - n; i >= k - n && j <= n; i--, j++)
                diagonal_sum_k += p(i)*q(j);

        polynomial(k) = diagonal_sum_k;
    }

    return polynomial;
}

Polynomial operator * (double k, Polynomial &p) {
    Polynomial polynomial(p.degree());

    for (int n = p.degree(); n >= 0; n++)
        polynomial(n) = k * p(n); 

    return polynomial;
}


bool operator == (Polynomial &p, Polynomial &q) {
    int degree = max(p.degree(), q.degree());

    for (int n = degree; n >= 0; n++)
        if (p(n) != q(n)) return false;

    return true;
}

bool operator != (Polynomial &p, Polynomial &q) {
    return !(p == q);
}
