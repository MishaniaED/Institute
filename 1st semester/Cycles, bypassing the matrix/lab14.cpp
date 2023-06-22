#include<stdio.h>
int main()
{
	int N,i,j,k;
	printf("Vvedite razmer matrizi N=");
	while(scanf("%d", &N)==1)
	{
	int a[N][N];
	printf("Vvedite matrizy:\n");
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			scanf("%d", &a[i][j]);
		}
	}
	printf("Isxodnie dannie\n", a[i][j]);
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}	
	printf("Rezultat:\n");
	N--;
	while(N!=0)
	{
		k=N;
		while((N!=0)&&(a[i][N]!=0))
		{
			printf("%d ", a[i][N]);
			a[i][N]=0;
			N--;
		}
		if(a[i][N]==0)
		N++;
		while((i!=k)&&(a[i][N]!=0))
		{
			printf("%d ", a[i][N]);
			a[i][N]=0;
			i++;
		}
		if(a[i][N]==0)
		i--;
		while((N!=k)&&(a[i][N]!=0))
		{
			printf("%d ", a[i][N]);
			a[i][N]=0;
			N++;
		}
		if(a[i][N]==0)
		N--;
		while((i!=0)&&(a[i][N]!=0))
		{
			printf("%d ", a[i][N]);
			a[i][N]=0;
			i--;
		}
		if(a[i][N]==0)
		i++;
		N=k;
		N--;
	}
	printf("Vvedite razmer matrizi N=");
	}
}
