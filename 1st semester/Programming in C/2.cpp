#include<stdio.h>
#define abs(a) (((a)>=0)?(a):(-a))
int mod(int a,int b)
{
	if(a>=0)
	return a%b;
	else return b-((-a)%b);
}
#define sign(a) (((a)>0)?(1):((a<0)?(-1):(0)))
#define min(a,b) (((a)<=(b))?(a):(b))
#define max(a,b) (((a)>=(b))?(a):(b))
int main() {
   int i0=20,j0=0,l0=11,k,i1=0,j1=0,l1=0,max1,max2,max3,min1,min2,min3,sign1;
	for(k=0;k<50;k++)
	{
		max1=max(j0,l0);
		max2=max(i0,j0);
		max3=max(i0,l0);
		min1=min(i0,l0);
		min2=min(j0,l0);
		min3=min(i0,j0);
		sign1=sign(i0-j0+l0-k);
		i1=mod(((i0-k)*max1+(i0-k)*min1+(l0-k)*max2),(23));
		j1=-mod(((i0-k)*min2+(i0-k)*max3+(l0-k)*min3),(27));
		l1=abs(i0+j0-l0-k)*sign1;
		if((i1>=-10)&&(i1<=0)&&((j1>=i1+10)&&(j1<=-i1+10)))
			break;
		i0=i1;
		j0=j1;
		l0=l1;
	}
	if(k==50)
	{
	printf("Tochka ne popala v treygolnik\n");
	printf("i=%d\n", i1);
	printf("j=%d\n", j1);
	printf("l=%d\n", l1);
	printf("k=%d\n", k);
	}
	else
	{
		printf("Tochka popala v treygolnik\n");
	    printf("i=%d\n", i1);
	    printf("j=%d\n", j1);
 	    printf("l=%d\n", l1);
	    printf("k=%d\n", k);
	}
	
}
