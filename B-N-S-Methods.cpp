#include <iostream>
#include <cmath>
#include <bitset>
#include <iomanip>
using namespace std;

// BISECTIONAL METHOD
float Bisection(float (*f)(float), float a, float b, int maxIter, float eps) {
    float fa = f(a);
    float fb = f(b);

    if (fa * fb >= 0) {
        cout << "Inadequate values for a and b." << endl;
        return -1.0;
    }

    float error = b - a;
    float c = 0.0;
    float fc = 0.0;

    for (int it = 1; it <= maxIter; ++it) {
        error /= 2;
        c = a + error;
        fc = f(c);

        if (abs(error) < eps || fc == 0) {
            cout << "BISECTIONAL METHOD: Algorithm has converged after " << it << " iterations!" << endl;
            return c;
        }

        if (fa * fc < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
    }

    cout << "Max iterations reached without convergence..." << endl;
    return c;
}

// NEWTON'S METHOD
float Newton(float (*f)(float), float (*derF)(float), float x, int maxIter, float eps, float delta) {
    float fx = f(x);

    for (int it = 1; it <= maxIter; it++) {
        float fd = derF(x);

        if (abs(fd) < delta) {
            cout << "Small slope!" << endl;
            return x;
        }

        float d = fx / fd;
        x -= d;
        fx = f(x);

        if (abs(d) < eps) {
            cout << "NEWTON'S METHOD: Algorithm has converged after " << it << " iterations!" << endl;
            return x;
        }
    }

    cout << "Max iterations reached without convergence..." << endl;
    return x;
}

// SECANT METHOD
float Secant(float (*f)(float), float a, float b, int maxIter, float eps) {
    float fa = f(a);
    float fb = f(b);

    if (std::abs(fa) > std::abs(fb)) {
        std::swap(a, b);
        std::swap(fa, fb);
    }

    for (int it = 1; it <= maxIter; ++it) {
        if (std::abs(fa) > std::abs(fb)) {
            std::swap(a, b);
            std::swap(fa, fb);
        }

        float d = (b - a) / (fb - fa);
        b = a;
        fb = fa;
        d = d * fa;

        if (std::abs(d) < eps) {
            std::cout << "SECANT METHOD: Algorithm has converged after " << it << " iterations!\n";
            return a;
        }

        a = a - d;
        fa = f(a);
    }

    std::cout << "Maximum number of iterations reached!\n";
    return a;
}

// Define the function f(x) = x^3 - x - 1 // f(x) = 3x^3 + 5x^2 - 7
float f(float x) {
    //return 3 * pow(x, 3) + 5 * pow(x, 2) - 0 * pow(x, 1) - 7;
    //return pow(x, 3) + 3*x - 1;
    return pow(x, 3) + 2 * pow(x, 2) + 10 * pow(x, 1) - 20;
}

// Differentiated Function.
float derF(float x) {
    //return 2*x;
    return 2 * pow(x, 2) + 4 * pow(x, 1) + 10;
}
/*
//HYBRID
float Hybrid(float (*f)(float), float a, float b, int maxIter, float eps) {
    float fa = f(a);
    float fb = f(b);

    if (fa * fb >= 0) {
        cout << "Inadequate values for a and b." << endl;
        return -1.0;
    }

    float error = b - a;
    float c, fc;

    for (int it = 1; it <= maxIter; it++) {
        error = error / 2;
        c = a + error;
        fc = f(c);

        if (fabs(error) < eps || fc == 0) {
            cout << "Algorithm has converged after " << it << " iterations!" << endl;
            return c;
        }

        if (fa * fc < 0) {
            b = c;
            fb = fc;
        }
        else {
            a = c;
            fa = fc;
        }
        
        // After 5 iterations, switch to Newton's Method
        if (it == 5) {
            cout << "Switching to Newton's Method..." << endl;
            return Newton(f, derF, c, maxIter - 5, eps, eps);
        }
    }

    cout << "Max iterations reached without convergence..." << endl;
    return c;
}
*/

float Hybrid(float (*f)(float), float (*derF)(float), float a, float b, int maxIter, float eps, float delta) {
    double x = Bisection(f, a, b, 3, eps);
    x = Newton(f, derF, x, maxIter - 3, eps, delta);
    return x;
}

int main() {
    float a = 1.0;
    float b = 2.0;
    int maxIter = 10000;                               // maximum number of iterations
    float eps = 1e-6;                                  // tolerance for convergence
    float delta = 1e-6;                                // tolerance for small slope
    
    float root_by_bisection = Bisection(f, a, b, maxIter, eps);
    float root_by_newton = Newton(f, derF, b, maxIter, eps, delta);
    float root_by_secant = Secant(f, a, b, maxIter, eps);
    cout << "Root found at x (By Bisectiona Method.) = " << setprecision(32) << root_by_bisection << endl;
    cout << "Root found at x (By Newton's Method.) = " << setprecision(32) << root_by_newton << endl;
    cout << "Root found at x (By Secant's Method.) = " << setprecision(32) << root_by_newton << endl;
    
   float root_by_hybrid= Hybrid(f, derF, a, b, maxIter, eps, delta);
   cout << "Root found at x (By Hybrid Method.) = " << setprecision(32) << root_by_hybrid << endl;
    return 0;
}