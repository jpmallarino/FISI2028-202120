// Gauss
#include<iostream>
#include<iomanip>
#include<math.h>
#include<stdlib.h>
#include<bits/stdc++.h>
#define N 3

using namespace std;


float A[N][N], x[N], ratio;
		 int i,j,k,n;
 
int aumentada(int A[N][N], int n, int i, int j)	
	{
	
		 for(i=1;i<=n;i++)
		 {
			  for(j=1;j<=n;j++)
			  {
				   if(i==j)
				   {
				    	A[i][j+n] = 1;
				   }
				   else
				   {
				    	A[i][j+n] = 0;
				   }
			  }
		 }
	}
		 
void eliminacionGauss(int A[N][N], int i, int j, int n, int k) 
     {
	     for(i=1;i<=n;i++)
		 {
			  if(A[i][i] == 0.0)
			  {
				   cout<<"Error!";
				   exit(0);
			  }
			  for(j=1;j<=n;j++)
			  {
				   if(i!=j)
				   {
					    ratio = A[j][i]/A[i][i];
					    for(k=1;k<=2*n;k++)
					    {
					     	A[j][k] = A[j][k] - ratio*A[i][k];
					    }
				   }
			  }
		 }
     }
int Diagonal(int A[N][N] , int n )
{
	 for(i=1;i<=n;i++)
		 {
			  for(j=n+1;j<=2*n;j++)
			  {
			   	A[i][j] = A[i][j]/A[i][i];
			  }
		 }
}

bool inversa(int A[N][N], float inv[N][N])
	{
		  
		 for(i=1;i<=n;i++)
		 {
			  for(j=n+1;j<=2*n;j++)
			  {
			   	cout<< A[i][j]<<"\t";
			  }
			  cout<< endl;
		 }
	}

template<class T>
void display(T A[N][N])
{
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
}
int main()
{
    int A[N][N] = { {2,-2,2},
                    {2,1,0},
                    {3,-2,2}
    };
 
 
    float inv[N][N];
 
    cout << "La matriz  :\n";
    display(A);
 
 
    cout << "\nLa matriz inversa :\n";
     display(inv);
 
    return 0;
	
}
