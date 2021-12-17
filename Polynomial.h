#include <iostream>
#include <string>
#include <cmath>


class Polynomial
{
private:
    const short _degree;
    double *coefficients;
    double _x;
public:
    Polynomial(int n);
    Polynomial(const Polynomial& p);
    ~Polynomial();

    void scanPolynomial(const std::string &polynomial);
    double& operator() (int n);
    double coeff(int n) const;

    short degree() const { return _degree; };
    double P_x(double x);

    double find_root(const Polynomial p, int accuracy);
};

Polynomial::Polynomial(int degree) : _degree(degree) {
    coefficients = new double[_degree+1];
}

Polynomial::~Polynomial() {
    delete[] coefficients;
}

void Polynomial::scanPolynomial(const std::string &polynomial) {

}

double& Polynomial::operator() (int n) {
    static double dummy = 0.0;
    return (n >= 0 && n <= _degree)
        ? coefficients[n]
        : dummy;
}

double Polynomial::coeff(int n) const {
    static double dummy = 0.0;
    return (n >= 0 && n <= _degree)
        ? coefficients[n]
        : dummy;
}

double Polynomial::P_x(double x) {
    _x = x;
    double _P_x = 0.0;

    for (int i = 0; i <= _degree; i++)
        _P_x += coefficients[i]*pow(_x, i);

    return _P_x;
}

std::ostream& operator << (std::ostream& os, const Polynomial &p) {
    for (int n = p.degree(); n > 1; n--)
        os << p.coeff(n)<<"x^"<<n << " + ";
    os << p.coeff(1)<<"x"; 
    os << " + " << p.coeff(0);       
    os << std::endl;

    return os;
}

// double Polynomial::find_root(Polynomial P, int accuracy) {

// }

int max(int a, int b) {
    return  a > b ? a : b;
}

Polynomial operator + (const Polynomial &p, const Polynomial &q) {
    int degree = max(p.degree(), q.degree());
    Polynomial polynomial(degree);

    for (int n = degree; n >= 0; n++)
        polynomial(n) = p.coeff(n) + q.coeff(n);

    return polynomial;
}

Polynomial operator - (const Polynomial &p, const Polynomial &q) {
    int degree = max(p.degree(), q.degree());
    Polynomial polynomial(degree);

    for (int n = degree; n >= 0; n++)
        polynomial(n) = p.coeff(n) - q.coeff(n);

    return polynomial;
}

Polynomial operator * (const Polynomial &p, const Polynomial &q) {
    int degree = p.degree() + q.degree();
    Polynomial polynomial(degree);

    int n = max(p.degree(), q.degree());
    for (int k = 0; k <= 2*n; k++) {
        double diagonal_sum_k = 0;
        if (k <= n)
            for (int i = 0, j = k; i <= k && j >= 0; i++, j--)
                diagonal_sum_k += p.coeff(i)*q.coeff(j);
        else
            for (int i = n, j = k-n; i >= k-n && j <= n; i--, j++)
                diagonal_sum_k += p.coeff(i)*q.coeff(j);
        
        polynomial(k) = diagonal_sum_k;
    }

    return polynomial;
}

Polynomial operator * (double k, const Polynomial &p) {
    Polynomial polynomial(p.degree());

    for (int n = p.degree(); n >= 0; n++)
        polynomial(n) = k * p.coeff(n); 

    return polynomial;
}


bool operator == (const Polynomial &p, const Polynomial &q) {
    int degree = max(p.degree(), q.degree());

    for (int n = degree; n >= 0; n++)
        if (p.coeff(n) != q.coeff(n)) return false;

    return true;
}

// bool operator == (const Polynomial &p, const std::string& polynomial) {

// }

bool operator != (const Polynomial &p, const Polynomial &q) {
    return !(p == q);
}

Polynomial Derivative(const Polynomial &p) {
    Polynomial polynomial(p.degree()-1);

    for (int n = p.degree(); n >= 1; n--)
        polynomial(n-1) = n*p.coeff(n);

    return polynomial;
}

Polynomial Antiderivative(const Polynomial &p) {
    Polynomial polynomial(p.degree()+1);

    for (int n = p.degree(); n >= 0; n--)
        polynomial(n+1) = p.coeff(n)/(n+1);

    return polynomial;
}

double Integral(const Polynomial &p, int a, int b) {
    Polynomial polynomial = Antiderivative(p);

    return polynomial.P_x(b) - polynomial.P_x(a);
}