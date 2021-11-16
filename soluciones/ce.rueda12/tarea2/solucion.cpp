// cofactores 

#include<bits/stdc++.h>
using namespace std;
#define N 3
 

void hallarCofactor(int A[N][N], int temp[N][N], int p, int q, int n)
{
    int i = 0, j = 0;
 

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];
 
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 

int determinante(int A[N][N], int n)
{
    int D = 0; 
 
    if (n == 1)
        return A[0][0];
 
    int temp[N][N]; 
 
    int sign = 1;  
 
    for (int f = 0; f < n; f++)
    {
        
        hallarCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinante(temp, n - 1);
        sign = -sign;
    }
 
    return D;
}

void adjunta(int A[N][N],int adj[N][N])
{
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }

    int sign = 1, temp[N][N];
 
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            hallarCofactor(A, temp, i, j, N);
            sign = ((i+j)%2==0)? 1: -1;
            adj[j][i] = (sign)*(determinante(temp, N-1));
        }
    }
}
 
bool inversa(int A[N][N], float inversa[N][N])
{
    int det = determinante(A, N);
    if (det == 0)
    {
        cout << "no se puede encontrar la matriz inversa";
        return false;
    }
 
    int adj[N][N];
    adjunta(A, adj);
 
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            inversa[i][j] = adj[i][j]/float(det);
 
    return true;
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
 
    int adj[N][N];  
 
    float inv[N][N]; 
 
    cout << "La matriz  :\n";
    display(A);
 
 
    cout << "\nLa matriz inversa :\n";
    if (inversa(A, inv))
        display(inv);
 
    return 0;
}
