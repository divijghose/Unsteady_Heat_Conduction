#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

int main()
{
    float alpha;
    int n;
    float dx ;
    float dt1 = 5.0;
    float tau1;

    ifstream infile;
    infile.open("input.txt"); //read values of no. of division and thermal diffusivity from file input.txt
    infile >> n;
    infile >> alpha;
    dx = 1.0/n; // step size for discretization
    tau1 = alpha*dt1/(pow(dx,2.0));

/* Temperature profiles from t = 0 to t = 100s are stored in 3D matrix T, in steps of 5s.
   The temperature profiles at t=5,20 & 50s are extracted from T into T5,T20 and T50 respectively
   Thereafter, the temperature profile at 7200s is directly calculated and stored in T7200, with time step of 5s */
    float T[n+1][n+1][21] = {0};
    float T5[n+1][n+1] = {0};
    float T20[n+1][n+1] = {0};
    float T50[n+1][n+1] = {0};
    float T1[n+1][n+1] = {0};
    float T7200[n+1][n+1] = {0};
    for(int i = 0; i<n+1; i++){ //initial condition
        for(int j = 0; j<n+1; j++){
            if((pow(((dx*i)-0.5),2.0) + pow(((dx*j)-0.5),2.0))<0.2){
                T[i][j][0] = 40.0;
            }else{
            T[i][j][0] = 20.0;}
        }
    }

    for(int t = 1; t<21; t++){
        for(int i= 0; i<n+1; i++){
            for(int j=0;j<n+1;j++){
                if(i==0 || i==n || j==0 || j==n){
                    T[i][j][t] = 20.0; // boundaries
                }else{
                T[i][j][t] = (tau1*(T[i+1][j][t-1]+T[i-1][j][t-1]+T[i][j+1][t-1]+T[i][-1][t-1]))+((1.0-(4.0*tau1))* T[i][j][t-1]); // interior
                }
            }
        }
    }
 //storing temperature profiles at t=5,20,50s
  for (int i = 0; i<n+1; i++){
    for(int j = 0; j<n+1; j++){
        T5[i][j] = T[i][j][1];
        T20[i][j] = T[i][j][4];
        T50[i][j] = T[i][j][10];
    }
  }
for(int i = 0; i<n+1;i++){
    for(int j = 0; j<n+1;j++){
        T1[i][j] = T[i][j][20]; //storing temperature profile for t=100s to begin calculation for t=7200s
    }
}
//calculating temperature profile at t=7220s, starting from t=100s with time step of 5s
for(int t = 1; t<1421; t++){
        for(int i= 0; i<n+1; i++){
            for(int j=0;j<n+1;j++){
                if(i==0 || i==n || j==0 || j==n){
                    T7200[i][j] = 20.0;
                }else{
                T7200[i][j] = (tau1*(T1[i+1][j]+T1[i-1][j]+T1[i][j+1]+T1[i][j-1]))+((1.0-(4.0*tau1))* T1[i][j]);
                }
            }
        }
        for(int i = 0;i<n+1;i++){
            for(int j = 0;j<n+1;j++){
                T1[i][j] = T7200[i][j];
            }
        }
    }
//writing the temperature profile in output files to be visualized in python
ofstream outfile;
outfile.open("T5.dat");
for(int i = 0; i<n+1;i++){
    for(int j=0;j<n+1;j++){
        outfile << T5[i][j] << endl;
    }
}
outfile.close();

outfile.open("T20.dat");
for(int i = 0; i<n+1;i++){
    for(int j=0;j<n+1;j++){
        outfile << T20[i][j] << endl;
    }
}
outfile.close();
outfile.open("T50.dat");
for(int i = 0; i<n+1;i++){
    for(int j=0;j<n+1;j++){
        outfile << T50[i][j] << endl;
    }
}
outfile.close();

outfile.open("T7200.dat");
for(int i = 0; i<n+1;i++){
    for(int j=0;j<n+1;j++){
        outfile << T7200[i][j] << endl;
    }
}
outfile.close();

    return 0;
}
