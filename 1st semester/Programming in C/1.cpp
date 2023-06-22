#include<stdio.h>
#include<math.h>
#define sign(a) 
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
int main() {
   int i0=20, j0=0, l0=1, k=0;
	int i1,j1,l1;
	for(k=0;k<50;k++)
	{
		i1=((i0-k)*max(j0,l0)+(i0-k)*min(i0,l0)+(l0-k)*max(i0,j0))%23;
		j1=-((i0-k)*min(j0,l0)+(i0-k)*max(i0,l0)+(l0-k)*min(i0,j0))%27;
		l1=abs(i0+j0-l0-k)*sign(i0-j0+l0-k);
		if((i1>=-10)&&(i1<=0)&&((j1>=i1)&&(j1<=-i1)))
		{
			break;
		}
		i0=i1;
		j0=j1;
		l0=l1;
	}
	if(k==50)
	{
	printf("Промах\n");
	printf("%d %d %d %d", &i1,&j1,&l1,&k);
	}
	else printf("Попадание\n");
	printf("%d %d %d %d", &i1,&j1,&l1,&k);
}
