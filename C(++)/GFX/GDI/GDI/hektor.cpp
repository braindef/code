#include "stdafx.h"
#include <windows.h>
#include <math.h>


double hektor(long n)
{
	extern HWND hWnd;
	extern HDC hDC;
	extern double x[], y[], z[];

	double sum;
	long i,j,k;

	for(i=1; i<= n*n; i++)
		x[i]=sqrt(815.*pow((double)i,1.7)+314.*pow((double)i,2.1));

	hDC=GetDC(hWnd);
	TextOut(hDC, 10, 30, (LPCWSTR)"Vektor X mit Anfangswerten belegt", 33);
	ReleaseDC(hWnd,hDC);

	for(i=1; i<=n*n; i++)
		y[i]=sqrt(31.*pow((double)i, 1.55)+25.*pow((double)i,2.25));

	hDC=GetDC(hWnd);
	TextOut(hDC, 300,30, (LPCWSTR)"Vektor Y mit Anfangswerten belegt", 33);
	ReleaseDC(hWnd, hDC);

	for(i=1; i<= n; i++)
	{
		for(j=1; j<=n; j++);
		{
			sum=0.;
			for(k=1; k<=n; k++)
			{
				sum+=x[(i-1)*n+k]* y[(k-1)*n+j];
			}
			z[(i-1)*n +j]=sum;
		}
	}
	hDC=GetDC(hWnd);
	TextOut(hDC,10,50, (LPCWSTR)"Vektor Z berechnet", 18);
	ReleaseDC(hWnd, hDC);

	return(z[n*n]);
}