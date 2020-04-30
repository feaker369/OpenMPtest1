#include<stdio.h>
#include<stdlib.h>
#include <omp.h>
#include<string.h>
#include<time.h>


int main(int argc,char* argv[]){
	int m,n,i,j,thread_count;
	thread_count=strtol(argv[1],NULL,10);	
	int **A,*x,*y,*y1;                   //�������A������x,���г������ɵĽ��y�����г������ɵĽ��y1
	printf("����������������");
	scanf("%d",&m);
	printf("����������������");
	scanf("%d",&n);
	//Ϊ����A��̬����ռ�
	A = (int **)malloc(m * sizeof(int *));
	for(i=0;i<m;i++)
	{
		A[i]=(int *)malloc(n * sizeof(int));
	}

	x = (int *)malloc(n * sizeof(int));   //Ϊ����x��̬����ռ�
	y = (int *)malloc(m * sizeof(int));   //Ϊ����y��̬����ռ�
	y1 = (int *)malloc(m * sizeof(int));  //Ϊ����y1��̬����ռ�
	srand(time(NULL));                    //����ʱ������
	//�����������A[m,n]
	for (i = 0; i < m; i++)   
	{
		for (j=0; j < n; j++)
			A[i][j] = rand()%10000+1;     //�����Χ�޶�Ϊ1-10000
	}
	//�����������x[n]
	for (j=0; j < n; j++)
		x[j] = rand()%10000+1;              //�����Χ�޶�Ϊ1-10000

	//����A[m][n]*x[n]���д��м���
	double start1=omp_get_wtime();
	printf("���Ϊ\n");
	for(i=0;i<m;i++)
	{
		y[i]=0.0;
		for(j=0;j<n;j++)
		{
			y[i]+=A[i][j]*x[j];
		}
	}
	double end1=omp_get_wtime();

	//����A[m][n]*x[n]���в��м���
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
	printf("����%d�У�%d�о�����Ծ���%d���������������贮��ʱ��Ϊ%f,���貢��ʱ��Ϊ%f\n",m,n,m,(end1-start1),(end2-start2));
	printf("���ٱ�Ϊ%f������Ч��Ϊ%f",((end1-start1)/(end2-start2)),((end1-start1)/((end2-start2)*thread_count)));
}

