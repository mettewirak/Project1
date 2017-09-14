#include <iostream>
#include <math.h>
#include <fstream>
#include <time.h>
#include <string>
//using namespace std;
std::ofstream ofile;

double u(double x){
    return 1-(1-exp(-10))*x-exp(-10*x);
}



double f_analytic(double x){
    return 100*exp(-10*x);
}

double relative_error(int n, double* v_vector, double* err){

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

int general(int n)
{
    clock_t t1,t2;


double h= 1.0/(n);
double* v_vector = new double [n];
double* a_vector =new double [n];
double* b_vector =new double [n+1];
double* c_vector =new double [n+1];
double* tilde_vector=new double[n];
double* x_vector =new double[n];
double* u_vector =new double[n];

//start koefisienter
    t1=clock();
double a=-1.0;
double b=2.0;
double c=-1.0;
double power=pow(h,2);
    
for(int i=0; i<=n; i++){
    *(a_vector + i)=a;
    *(b_vector + i)=b;
    *(c_vector + i)=c;
    *(x_vector+i)=h*i;
    *(tilde_vector + i)=f_analytic(x_vector[i])*power;
    *(u_vector+i)=u(x_vector[i]);
}
    t1=clock();
//forward substetution
for(int i=1;i<(n);i+=1 ){
    *(b_vector+i+1)=*(b_vector+i+1)-*(c_vector+i)*(*(a_vector+i)/(*(b_vector+i)));
    *(tilde_vector +i)=*(tilde_vector+i)-*(tilde_vector+i-1)*(*(a_vector+i)/(*(b_vector+i)));
    *(a_vector+i)=0;

}

//Finner verdien til v_n


*(v_vector +n-1)=*(tilde_vector +n-1)/(*(b_vector +n-1));



//backward substitution

for(int k=n-2;k>=0;k-=1){

    *(v_vector +k)=(*(tilde_vector +k)-*(c_vector +k +1)*(*(v_vector +k+1)))/(*(b_vector +k));

}

//finne error
double* error_vector = new double [n];

for(int i=0; i<=n; i+=1){
    *(error_vector +i)=log(fabs(*(v_vector + i)-*(u_vector +i))/(*(u_vector +i)));
}
double max_err = relative_error(n, v_vector, error_vector);

using namespace std;
cout<<"max_err,g= "<<max_err<<endl;
t2=clock();

std::string filename ="resultat" + std::to_string(n) + ".txt";

ofile.open(filename);
//ofile.open("g_100.txt");



for(int i=0; i<=n; i+=1){

    //cout<<i<< " error= "<< error_vector[i]<<" v= "<<v_vector[i]<<" u= "<< u_vector[i]<< <<endl;
    ofile << x_vector[i]<< " error= "<< error_vector[i]<<" v= "<<v_vector[i]<<" u= "<< u_vector[i]<< std::endl;
}

ofile.close();


float diff = (float)t2 - (float)t1;
using namespace std;
cout <<"general algorithm="<< diff/CLOCKS_PER_SEC << endl;
return 0;


}

int special(int n)
{
clock_t t1,t2;



double h= 1.0/(n);
double power=pow(h,2);


double* v_vector = new double [n];
double* b_vector =new double [n+1];
double* tilde_vector=new double[n];
double* x_vector =new double[n];
double* u_vector =new double[n];

//start koefisienter


t1=clock();
double b=2.0;
*(b_vector)=b;
*(tilde_vector + 0)=f_analytic(0);
*(x_vector+0)=0;
    



for(int i=1; i<=n; i++){
    *(x_vector+i)=h*i;
    *(b_vector+i) = double(i+1)/double(i);
    *(tilde_vector +i)=f_analytic(x_vector[i])*power;
    *(u_vector+i)=u(x_vector[i]);
}

// Forward substitution

for (int i = 1; i < n; ++i)
{
   *(tilde_vector +i)=*(tilde_vector+i)+*(tilde_vector+i-1)/(*(b_vector+i));
}

//Finner verdien til v_n
*(v_vector +n-1)=*(tilde_vector +n-1)/(*(b_vector +n-1));


//backward substetution
for(int k=n-2;k>=0;k-=1){

    *(v_vector +k)=(*(tilde_vector +k)+(*(v_vector +k+1)))/(*(b_vector +k));


}


//finne error
double* error_vector = new double [n];



for(int i=0; i<=n; i+=1){
    *(error_vector +i)=log(fabs(*(v_vector + i)-*(u_vector +i))/(*(u_vector +i)));
}
double max_err = relative_error(n, v_vector, error_vector);
using namespace std;
cout<<"max_err,s= "<<max_err<< endl;


t2=clock();

float diff = (float)t2 - (float)t1;
using namespace std;
cout <<"special algorithm="<< diff/CLOCKS_PER_SEC << endl;


std::string filename ="resultat" + std::to_string(n) + ".txt";

ofile.open(filename);

for(int i=0; i<=n; i+=1){
    //cout<<i<< " error= "<< error_vector[i]<<" v= "<<v_vector[i]<<" u= "<< u_vector[i]<< <<endl;
    ofile << x_vector[i]<< " error= "<< error_vector[i]<<" v= "<<v_vector[i]<<" u= "<< u_vector[i]<< std::endl;
}

ofile.close();
return 0;


}


int main(){

	cout << "test" << endl;

 int n = pow(10,3);
 special(n);
 general(n);

}
