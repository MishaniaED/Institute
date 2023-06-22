#include<stdio.h>
int main()
{
	int N,i,j,k,M,b;
	printf("Vvedite razmer matrizi N=");
	while(scanf("%d", &N)==1)
	{
		if(N<9)
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
	b=0;
	int m[N*N];
	printf("Isxodnie dannie\n");
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			m[b]=a[i][j];
			b++;
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
	printf("Vvedite razmer sdviga M=");
	scanf("%d", &M);
	while(M!=0)
	{
		k=m[N*N-1];
		for(i=(N*N)-1;i>0;i--)
		{
			m[i]=m[i-1];
		}
		m[0]=k;
		M--;
	}
	b=0;
	printf("Rezultat:\n");
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			a[i][j]=m[b];
			b++;
			printf("%d ", a[i][j]);
		}
		printf("\n");	
	}
	}
	else printf("N ne dolgno bit >8\n");
	printf("Vvedite razmer matrizi N=");
		}
	
}
