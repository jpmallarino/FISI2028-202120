// Muy loco lo que hiciste! Era todo mucho mas facil si hubieras usado Eigen...

//Tarea 2 Metodos Computacionales Samuel David Cañas 201922001
//Esta parte del codigo es la responsable de invertir la matriz por gauss jordan 

#include<stdio.h>
#include<stdlib.h>
// #include<conio.h>
void imprimem(float [10][10]); //imprime una matriz de forma ordenada
void capturam(float [10][10],int,int); //captura una matriz n*m
void mid(float x[10][10]); //encuentra la matriz identidad de n*n
void igualam(float [10][10],float [10][10]); //iguala una matriz a otra, con el fin de no perder datos
void sumar(float [10][10],float [10][10], float,float,int,int); //determina si debe sumar o restar un renglón en la matriz inv
void cambiar(float [10][10],float[10][10],int,int); //cambia 2 renglones de una matriz entre si
void dirc(float [10][10],int,float);  //divide un renglon de una matriz entre una constante
void impriproc(void);  //imprime el estatus de la matriz aumentada
float minv(void); //determina la inversa, es donde esta el error...
//funciona así, primero verifica que el valor del primer pivote no sea 0, de ser así lo cambia por otro
//después convierte el primer pivote en 1, después suma o resta a los renglones de abajo,
//cambia de pivote y repite los pasos, sumando o restando ahora en los renglones de arriba o abajo

int n,m,o,p,opcion;
float a[10][10],b[10][10],c[10][10],d[10][10];
 
main()
{
	float z;
	// system("cls");
	printf("\nDa el tamaño de la matriz:>");
	scanf("%d",&n);
	m=n;
	// system("cls");
	z=minv();
	getch();
	return(0);
}
 
void capturam( float x[10][10],int y,int z)
{
	int i,j;
	for(i=0;i<y;i++)
	{
		for(j=0;j<z;j++)
		{
			printf("\nDa el elemento %d,%d:>",i+1,j+1);
			scanf("%f",&x[i][j]);
		}
	}
	system("cls");
}
 
void imprimem(float x[10][10])
{
	int i,j;
 
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			printf("\t%.2f",x[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}
 
void mid(float x[10][10])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			x[i][j]=0;
			if(i==j)
			{
				x[i][j]=1;
			}
		}
	}
}
 
void igualam(float mo[10][10],float ms[10][10])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			ms[i][j]=mo[i][j];
		}
	}
}
 
void sumar(float ma[10][10],float mc[10][10], float via,float vic,int fa,int fc)
{
	int j;
	float q;
	q=via*vic;
	for(j=0;j<m;j++)
	{
		if(q>0)
		{
			ma[fa][j]=ma[fa][j]-(via*mc[fc][j]);
			b[fa][j]=b[fa][j]-(via*d[fc][j]);
		}
		else
		{
			ma[fa][j]=ma[fa][j]+(via*mc[fc][j]);
			b[fa][j]=b[fa][j]+(via*d[fc][j]);
		}
	}
}
 
void cambiar(float mo[10][10],float ms[10][10],int fo,int fs)
{
	int j;
	for(j=0;j<m;j++)
	{
		ms[fs][j]=mo[fo][j];
		ms[fo][j]=mo[fs][j];
	}
	igualam(ms,mo);
}
 
void dirc(float x[10][10],int i,float k)
{
	int j;
	for(j=0;j<m;j++)
	{
		x[i][j]=(x[i][j])/k;
	}
}
 
void impriproc(void)
{
	int i,j,k;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			printf("\t%.2f",a[i][j]);
		}
		for(k=0;k<m;k++)
		{
			printf("\t%.2f",b[i][k]);
		}
		printf("\n");
	}
	printf("\n\n");
}
 
float minv(void)
{
	int i,j,k,l,q,r;
	float x=0;
	capturam(a,n,m);
	mid(b);
	igualam(a,c);
	igualam(b,d);
	impriproc();
	for(j=0;j<n;j++)
	{
		if(a[j][j]==0)
		{
			for(i=j;i<n;i++)
			{
				if(a[j][j]==0)     //cambia el renglon por uno diferente de 0
				{
					cambiar(a,c,j,i);
					cambiar(b,d,j,i);
				}
			}
			if(a[j][j]==0)
			{
				printf("\n\t La matriz inversa no existe");
				getch();
				return(x);
			}
		}
		else
		{
			if(a[j][j]!=1)     //convierte el pivote en 1
			{
				dirc(b,j,a[j][j]);
				dirc(a,j,a[j][j]);
				igualam(a,c);
				igualam(b,d);
			}
			i=0;
			while(i!=n)
			{
				if(i==j)
				{
				}
				else
				{
					sumar(a,c,a[i][j],c[j][j],i,j);     //suma o resta al renglon
					igualam(a,c);
					igualam(b,d);
					impriproc();
				}
				i++;
			}
 
		}
	}
	printf("\n\t La matriz inversa es: \n");
	impriproc();
	imprimem(b);
	return(x);
}