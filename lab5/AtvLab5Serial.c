#include <stdio.h>
#include <math.h>
double f(double x)
{
    return exp(x);
}

int main(void)
{
    double a, b, approx, h, x_i;
    int n;

    a =15;
    b =20;
    n = 5;
    h = (b - a) / n;
    approx = (f(a) + f(b)) / 2.0;
    for(int i = 1; i <= n - 1; i++)
        {
            x_i = a + i*h;
            approx += f(x_i);
        }
    approx += h*approx;
    printf("Approx: %lf.\n", approx);

    return 0;
}
