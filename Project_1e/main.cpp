#include <iostream>
#include <math.h>
#include <fstream>

#include <armadillo>
#include <time.h>


using namespace std;
using namespace arma ;

double u(double x){
    return 1-(1-exp(-10))*x-exp(-10*x);
}
double relative_error(int n, double* err){

    double max_err;
    for(int i=1; i<n; i++){

        if(i==1){
            max_err = *(err + i);
        }
        else if(*(err + i)>max_err){
            max_err = *(err + i);
        }
    }
    return max_err;
}

double f_analytic(double x){
    return 100*exp(-10*x);
}

int with_solver(int n){

    mat A(n,n,fill::zeros);

    vec tilde_vector(n);

    //start koefisienter

    double a=-1.0;
    double b=2.0;
    double c=-1.0;

    for(int i=0; i<n-2; i++){
    A(i,i+1)=c;
    A(i,i)=b;
    A(i+1,i)=a;
    }

    A(n-2,n-2)=b;
    A(n-2,n-1)=c;
    A(n-1,n-2)=a;
    A(n-1,n-1)=b;

    double* x_vector =new double[n];
    double* error_vector =new double[n];
    double h= 1.0/(n);
    for(int i=0;i<n;i++){
            *(x_vector+i)=h*i;
            tilde_vector(i)=f_analytic(x_vector[i])*pow(h,2);

    }

    clock_t t1,t2;
    t1=clock();


    vec v;
    v=solve(A,tilde_vector);




    for(int i=0; i<=n; i+=1){
        *(error_vector +i)=log(fabs(v[i]-u(x_vector[i])/u(x_vector[i])));
    }
    double max_err = relative_error(n, error_vector);
    t2=clock();
    float diff = (float)t2 - (float)t1;
    using namespace std;
    cout <<"tid uten LU= "<< diff/CLOCKS_PER_SEC << endl;
    using namespace std;
    cout<<"max_err,g= "<<max_err<<endl;

    return 0;

}
int LU(int n){

    mat A(n,n,fill::zeros);

    vec tilde_vector(n);

    //start koefisienter

    double a=-1.0;
    double b=2.0;
    double c=-1.0;

    for(int i=0; i<n-2; i++){
    A(i,i+1)=c;
    A(i,i)=b;
    A(i+1,i)=a;
    }

    A(n-2,n-2)=b;
    A(n-2,n-1)=c;
    A(n-1,n-2)=a;
    A(n-1,n-1)=b;

    double* x_vector =new double[n];
    double* error_vector =new double[n];
    double h= 1.0/(n);
    for(int i=0;i<n;i++){
            *(x_vector+i)=h*i;
            tilde_vector(i)=f_analytic(x_vector[i])*pow(h,2);

    }

    clock_t t1,t2;


    mat L, U;
    t1=clock();
    lu(L,U, A);

    vec z;
    vec y;

    z=solve(L,tilde_vector);
    y=solve(U,z);


    for(int i=0; i<=n; i+=1){
        *(error_vector +i)=log(fabs(y[i]-u(x_vector[i])/u(x_vector[i])));
    }
    double max_err = relative_error(n, error_vector);
    t2 = clock();
    float diff = (float)t2 - (float)t1;


    cout <<"tid med LU= "<< diff/CLOCKS_PER_SEC << endl;
    using namespace std;
    cout<<"max_err,g= "<<max_err<<endl;
    return 0;

}

int main()
{
    int n=1000;
    LU(n);
    with_solver(n);


return 0;


}

