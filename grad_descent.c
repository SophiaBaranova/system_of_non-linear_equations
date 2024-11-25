#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#define N 3 //number of variables

void F(double *f, double *x); //vector of functions
void W(double w[][N], double *x); //Jacobian matrix
double M(double *f, double w[][N], double *wtf, double *x); //stepsize
void GRAD(double *grad, double *x); //gradient of function U

int main()
{
    double x0[N], x1[N], f[N], w[N][N], wtf[N], grad[N];
    double m, e = 1, delta;
    int i, j, e_out, numb_steps = 0;
    printf("system of nonlinear equations\n");
    printf("x^2+2y-3z=0.9\n2x-y^2+z=1.7\n2+3y-z^2=4.51\n");
    //enter initial approximation of variables
    printf("enter initial values x, y, z (using space) -> ");
    for (i = 0; i < N; i++)
    {
        scanf("%lf", &x0[i]);
    }
    //enter desired accuracy
    do
    {
        printf("enter desired accuracy - number of digits after the decimal point -> ");
        scanf("%d", &e_out);
    } while (e_out <= 0);
    //calculate accuracy
    for (i = 0; i < e_out; i++)
    {
        e /= 10;
    }
    //perform GD algorithm to achieve a given accuracy
    do
    {
        //calculate vector of functions for x k-th
        F(f, x0);
        //calculate Jacobian matrix for x k-th
        W(w, x0);
        //calculate product of transpose of Jacobian matrix and vector of functions for x k-th
        for (i = 0; i < N; i++)
        {
            wtf[i] = 0;
            for (j = 0; j < N; j++)
            {
                wtf[i] += w[j][i] * f[j];
            }
        }
        //calculate stepsize
        m = M(f, w, wtf, x0);
        //calculate x (k+1)-th
        for (i = 0; i < N; i++)
        {
            x1[i] = x0[i] - m * wtf[i];
        }
        //calculate gradient of function U for x (k+1)-th
        GRAD(grad, x1);
        delta = grad[0];
        //calculate error - m-norm of gradient
        for (i = 1; i < N; i++)
        {
            if (delta < fabs(grad[i]))
            {
                delta = fabs(grad[i]);
            }
        }
        for (i = 0; i < N; i++)
        {
            x0[i] = x1[i];
        }
        numb_steps++;
    } while (delta > e);
    //print results
    printf("x = %.*lf, y = %.*lf, z = %.*lf\nnumber of steps: %d\ncalculation error: %lg\n", e_out, x1[0], e_out, x1[1], e_out, x1[2], numb_steps, delta);
    return 0;
}

void F(double *f, double *x)
{
    f[0] = pow(x[0], 2) + 2 * x[1] - 3 * x[2] - 0.9;
    f[1] = 2 * x[0] - pow(x[1], 2) + x[2] - 1.7;
    f[2] = 2 * x[0] + 3 * x[1] - pow(x[2], 2) - 4.51;
    return;
}

void W(double w[][N], double *x)
{
    w[0][0] = 2 * x[0];
    w[0][1] = 2;
    w[0][2] = -3;
    w[1][0] = 2;
    w[1][1] = -2 * x[1];
    w[1][2] = 1;
    w[2][0] = 2;
    w[2][1] = 3;
    w[2][2] = -2 * x[2];
    return;
}

double M(double *f, double w[][N], double *wtf, double *x)
{
    double m;
    double numer = 0, denom = 0, *wwtf = NULL;
    int i, j;
    wwtf = (double*)malloc(N * sizeof(double));
    if (!wwtf)
    {
        exit(1);
    }
    //calculate product of Jacobian matrix, transpose of Jacobian matrix and vector of functions
    for (i = 0; i < N; i++)
    {
        wwtf[i] = 0;
        for (j = 0; j < N; j++)
        {
            wwtf[i] += w[i][j] * wtf[j];
        }
    }
    //calculate numerator and denominator for stepsize formula
    for (i = 0; i < N; i++)
    {
        numer += f[i] * wwtf[i];
        denom += pow(wwtf[i], 2);
    }
    //if division by 0
    if (!denom)
    {
        exit(2);
    }
    m = numer / denom;
    free(wwtf);
    return m;
}

void GRAD(double *grad, double *x)
{
    grad[0] = 16 * x[0] + 12 * x[1] + 4 * x[2] - 4 * pow(x[1], 2) - 4 * pow(x[2], 2) + 4 * x[0] * (2 * x[1] - 3 * x[2] + pow(x[0], 2) - 0.9) - 24.84;
    grad[1] = 12 * x[0] + 26 * x[1] - 12 * x[2] + 4 * pow(x[0], 2) - 6 * pow(x[2], 2) - 4 * x[1] * (2 * x[0] + x[2] - pow(x[1], 2) - 1.7) - 30.66;
    grad[2] = 4 * x[0] - 12 * x[1] + 20 * x[2] - 6 * pow(x[0], 2) - 2 * pow(x[1], 2) - 4 * x[2] * (2 * x[0] + 3 * x[1] - pow(x[2], 2) - 4.51) + 2.;
    return;
}
