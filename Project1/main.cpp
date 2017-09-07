#include <iostream>
#include <math.h>
#include <fstream>
#include <ctime>
//using namespace std;
std::ofstream ofile;

double u(double x){
    return 1-(1-exp(-10))*x-exp(-10*x);
}


double f_analytic(double x){
    return 100*exp(-10*x);
}


int general(int n)
{

double h= 1.0/(n+1);
double* v_vector = new double [n];
double* a_vector =new double [n];
double* b_vector =new double [n+1];
double* c_vector =new double [n+1];
double* tilde_vector=new double[n];
double* x_vector =new double[n];
double* u_vector =new double[n];

//start koefisienter

double a=-1.0;
double b=2.0;
double c=-1.0;

for(int i=0; i<=n; i++){
    *(a_vector + i)=a;
    *(b_vector + i)=b;
    *(c_vector + i)=c;
    *(x_vector+i)=h*i;
    *(tilde_vector + i)=f_analytic(x_vector[i]);

    *(u_vector+i)=u(x_vector[i]);
}

//forward substetution
for(int i=1;i<(n);i+=1 ){
    *(b_vector+i+1)=*(b_vector+i+1)-*(c_vector+i)*(*(a_vector+i)/(*(b_vector+i)));
    *(tilde_vector +i)=*(tilde_vector+i)-*(tilde_vector+i-1)*(*(a_vector+i)/(*(b_vector+i)));
    *(a_vector+i)=*(a_vector+i)-*(b_vector+i)*(*(a_vector+i)/(*(b_vector+i)));

}

//Finner verdien til v_n

*(v_vector +n)=*(tilde_vector +n)*pow(h,2)/(*(b_vector +n));


//backward substetution

for(int k=n-2;k>=0;k-=1){
    *(v_vector +k)=(*(tilde_vector +k)*pow(h,2)-*(c_vector +k +1)*(*(v_vector +k+1)))/(*(b_vector +k+1));

}

//finne error
double* error_vector = new double [n];

ofile.open("andre_tall_10_6.txt");



for(int i=0; i<=n; i+=1){
    *(error_vector +i)=log(fabs(*(v_vector + i)-*(u_vector +i))/(*(u_vector +i)));
    //cout<<i<< " error= "<< error_vector[i]<<" v= "<<v_vector[i]<<" u= "<< u_vector[i]<< <<endl;
    ofile << x_vector[i]<< " error= "<< error_vector[i]<<" v= "<<v_vector[i]<<" u= "<< u_vector[i]<< std::endl;
}

ofile.close();

using namespace std;
cout<<"general algorithm"<<endl;
cout<<"Clock ticks: "<<clock()<<" Seconds: "<<clock()/CLOCKS_PER_SEC<<endl;

return 0;


}

int special(int n)
{

double h= 1.0/(n+1);
double* v_vector = new double [n];
double* a_c_vector =new double [n];
double* b_vector =new double [n+1];
double* tilde_vector=new double[n];
double* x_vector =new double[n];
double* u_vector =new double[n];

//start koefisienter

double a_c=-1.0;
double b=2.0;


for(int i=0; i<=n; i++){
    *(a_c_vector + i)=a_c;
    *(b_vector + i)=b;
    *(x_vector+i)=h*i;
    *(tilde_vector + i)=f_analytic(x_vector[i]);

    *(u_vector+i)=u(x_vector[i]);
}

//forward substetution
for(int i=1;i<(n);i+=1 ){
    *(b_vector+i+1)=*(b_vector+i+1)-*(a_c_vector+i)*(*(a_c_vector+i)/(*(b_vector+i)));
    *(tilde_vector +i)=*(tilde_vector+i)-*(tilde_vector+i-1)*(*(a_c_vector+i)/(*(b_vector+i)));


}

//Finner verdien til v_n

*(v_vector +n)=*(tilde_vector +n)*pow(h,2)/(*(b_vector +n));


//backward substetution

for(int k=n-2;k>=0;k-=1){
    *(v_vector +k)=(*(tilde_vector +k)*pow(h,2)-*(a_c_vector +k +1)*(*(v_vector +k+1)))/(*(b_vector +k+1));

}

//finne error
double* error_vector = new double [n];

ofile.open("andre_tall_10_6.txt");



for(int i=0; i<=n; i+=1){
    *(error_vector +i)=log(fabs(*(v_vector + i)-*(u_vector +i))/(*(u_vector +i)));
    //cout<<i<< " error= "<< error_vector[i]<<" v= "<<v_vector[i]<<" u= "<< u_vector[i]<< <<endl;
    ofile << x_vector[i]<< " error= "<< error_vector[i]<<" v= "<<v_vector[i]<<" u= "<< u_vector[i]<< std::endl;
}

ofile.close();

using namespace std;
cout<<"special algorithm"<<endl;
cout<<"Clock ticks: "<<clock()<<" Seconds: "<<clock()/CLOCKS_PER_SEC<<endl;

return 0;


}


int main(){
 int n = pow(10,6);
 special(n);
 general(n);

}
