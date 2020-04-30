#include<stdio.h>
#include<stdlib.h>
#include <omp.h>
#include<string.h>
#include<time.h>


int main(int argc,char* argv[]){
	int m,n,i,j,thread_count;
	thread_count=strtol(argv[1],NULL,10);	
	int **A,*x,*y,*y1;                   //代表矩阵A，向量x,串行程序生成的结果y，并行程序生成的结果y1
	printf("请输入矩阵的行数：");
	scanf("%d",&m);
	printf("请输入矩阵的列数：");
	scanf("%d",&n);
	//为矩阵A动态分配空间
	A = (int **)malloc(m * sizeof(int *));
	for(i=0;i<m;i++)
	{
		A[i]=(int *)malloc(n * sizeof(int));
	}

	x = (int *)malloc(n * sizeof(int));   //为向量x动态分配空间
	y = (int *)malloc(m * sizeof(int));   //为向量y动态分配空间
	y1 = (int *)malloc(m * sizeof(int));  //为向量y1动态分配空间
	srand(time(NULL));                    //分配时间种子
	//生成随机矩阵A[m,n]
	for (i = 0; i < m; i++)   
	{
		for (j=0; j < n; j++)
			A[i][j] = rand()%10000+1;     //随机范围限定为1-10000
	}
	//随机生成向量x[n]
	for (j=0; j < n; j++)
		x[j] = rand()%10000+1;              //随机范围限定为1-10000

	//矩阵A[m][n]*x[n]进行串行计算
	double start1=omp_get_wtime();
	printf("结果为\n");
	for(i=0;i<m;i++)
	{
		y[i]=0.0;
		for(j=0;j<n;j++)
		{
			y[i]+=A[i][j]*x[j];
		}
	}
	double end1=omp_get_wtime();

	//矩阵A[m][n]*x[n]进行并行计算
	double start2=omp_get_wtime();
#pragma omp parallel for num_threads(thread_count)\
	default(none) shared(A,x,y1,m,n) private(i,j)
	for(i = 0;i<m;i++)
	{
		y1[i]=0;
		for(j=0;j<n;j++)
			y1[i] += A[i][j]*x[j];
	}
	double end2=omp_get_wtime();
	printf("具有%d行，%d列矩阵乘以具有%d个变量的向量所需串行时间为%f,所需并行时间为%f\n",m,n,m,(end1-start1),(end2-start2));
	printf("加速比为%f，并行效率为%f",((end1-start1)/(end2-start2)),((end1-start1)/((end2-start2)*thread_count)));
}

