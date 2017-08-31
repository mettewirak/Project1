#include <iostream>

using namespace std;

double u(double x){
    return 1-(1-exp(-10))x-exp(-10x);
}

double f_analytic(double x){
    return 100exp(-10x);
}

double f(double a,double b, double c,double v, double v_pluss, double a_minus, double h){

    return (a*v_minus+b*v+c*v_pluss)/h^2;

}

int main()
{
int n = 5;
double* v_vector = new double [n];
double* a_vector =new double [n];
double* b_vector =new double [n];
double* c_vector =new double [n];
double* tilde_vector=new double[n];



}

