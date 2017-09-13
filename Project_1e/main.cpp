#include <iostream>
#include <math.h>
#include <fstream>
#include <ctime>
#include <armadillo>


//using namespace std;
using namespace arma ;

double u(double x){
    return 1-(1-exp(-10))*x-exp(-10*x);
}


double f_analytic(double x){
    return 100*exp(-10*x);
}
void printarray (double arg[], int length) {
  for (int n=0; n<length; ++n)
    cout << arg[n] << ' ';
  cout << '\n';
}


int main()
{

int n = 5;
mat A(n,n,fill::zeros);

vec tilde_vector=randu<vec>(5);

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
double h= 1.0/(n+1);
for(int i=0;i<n;i++){
        *(x_vector+i)=h*i;
        tilde_vector[i]=f_analytic(x_vector[i])*pow(h,2);

}

vec v;
v=solve(A,tilde_vector);

A.print();
tilde_vector.print();
cout<<"v"<<endl;
v.print();


mat L, U, P;
lu(L,U,P, A);
cout<<"L"<<endl;
L.print();
cout<<"U"<<endl;
U.print();
//A.print();


using namespace std;
cout<<"Clock ticks: "<<clock()<<" Seconds: "<<clock()/CLOCKS_PER_SEC;



return 0;


}

