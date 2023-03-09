#include <iostream>
#include <cmath>
#include <bitset>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// BISECTIONAL METHOD
pair<float, int> Bisection(float (*f)(float), float a, float b, int maxIter, float eps)
{
    float fa = f(a);
    float fb = f(b);

    if (fa * fb >= 0)
    {
        cout << "Inadequate values for a and b." << endl;
        return make_pair(-1.0, -1);
    }

    float error = b - a;
    float c = 0.0;
    float fc = 0.0;

    for (int it = 1; it <= maxIter; ++it)
    {
        error /= 2;
        c = a + error;
        fc = f(c);

        if (abs(error) < eps || fc == 0)
        {
            return make_pair(c, it);
        }

        if (fa * fc < 0)
        {
            b = c;
            fb = fc;
        }
        else
        {
            a = c;
            fa = fc;
        }
    }
    return make_pair(c, -1);;
}

// NEWTON'S METHOD
pair<float, int> Newton(float (*f)(float), float (*derF)(float), float x, int maxIter, float eps, float delta)
{
    float fx = f(x);

    for (int it = 1; it <= maxIter; it++)
    {
        float fd = derF(x);

        if (abs(fd) < delta)
        {
            cout << "Small slope!" << endl;
            return make_pair(x, -1);
        }

        float d = fx / fd;
        x -= d;
        fx = f(x);

        if (abs(d) < eps)
        {
            return make_pair(x, it);
        }
    }
    return make_pair(x, -1);
}

// SECANT METHOD
pair<float, int> Secant(float (*f)(float), float a, float b, int maxIter, float eps)
{
    float fa = f(a);
    float fb = f(b);

    if (abs(fa) > abs(fb))
    {
        swap(a, b);
        swap(fa, fb);
    }

    for (int it = 1; it <= maxIter; ++it)
    {
        if (abs(fa) > abs(fb))
        {
            swap(a, b);
            swap(fa, fb);
        }

        float d = (b - a) / (fb - fa);
        b = a;
        fb = fa;
        d = d * fa;

        if (abs(d) < eps)
        {
            return make_pair(a, it);
        }
        a = a - d;
        fa = f(a);
    }
    cout << "Maximum number of iterations reached!\n";
    return make_pair(a, -1);
}

pair<float, int> Hybrid(float (*f)(float), float (*derF)(float), float a, float b, int maxIter, float eps, float delta)
{
    pair<float, int> x = Bisection(f, a, b, 3, eps);
    x = Newton(f, derF, x.first, maxIter - 3, eps, delta);
    return x;
}

// Define the function f(x) = x^3 - x - 1 // f(x) = 3x^3 + 5x^2 - 7
float f(float x)
{
    ifstream inputFile("fun1.pol");
    int n;
    float result;
    vector<float> a(4);
    if (inputFile.is_open())
    {
        string line;
        getline(inputFile, line);

        // Read the first integer
        stringstream(line) >> n;
        for (int i = 0; i < 4; i++)
        {
            inputFile >> a[i];
        }
    }
    else
    {
        cerr << "Unable to open input file" << std::endl;
    }
    return (a[0] * pow(x, 3) + a[1] * pow(x, 2) + a[2] * pow(x, 1) + a[3]);
}

// Differentiated Function.
float derF(float x)
{
    // return 9 * pow(x, 2) + 10 * pow(x, 1);
    return 2 * pow(x, 2) + 4 * pow(x, 1) + 10;
}

int main()
{
    float a = 2.0;
    float b = 1.0;
    int maxIter = 10000;            // maximum number of iterations
    float eps = 1e-6;               // tolerance for convergence
    float delta = 1e-6;             // tolerance for small slope
    pair<float, int> root_by_bisection = Bisection(f, a, b, maxIter, eps);
    pair<float, int> root_by_newton = Newton(f, derF, b, maxIter, eps, delta);
    pair<float, int> root_by_secant = Secant(f, a, b, maxIter, eps);
    pair<float, int> root_by_hybrid = Hybrid(f, derF, a, b, maxIter, eps, delta);
    cout << "Solutions are being saved in \"solution.sol\" file!!"  << endl;
    ofstream outputFile;
    outputFile.open("solution.sol");
    outputFile << "Method\t\tRoot\t\t\t\t\t\tIterations\t\tOutcome" << endl;
    outputFile << "Bisection\t" << setw(30) << left << setprecision(32) << root_by_bisection.first << setw(9) << root_by_bisection.second << "\t\tSuccess!" << endl;
    outputFile << "Newton's \t" << setw(30) << left << setprecision(32) << root_by_newton.first << setw(9) << root_by_newton.second << "\t\tSuccess!" << endl;
    outputFile << "Secant   \t" << setw(30) << left << setprecision(32) << root_by_secant.first << setw(9) << root_by_secant.second << "\t\tSuccess!" << endl;
    outputFile << "Hybrid   \t" << setw(30) << left << setprecision(32) << root_by_hybrid.first << setw(9) << root_by_hybrid.second << "\t\tSuccess!" << endl;
    outputFile.close();
    return 0;
}