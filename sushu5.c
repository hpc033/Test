#include "mpi.h"
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define N 100000 
// �ж��Ƿ�Ϊ����
int is_prime(int start, int finish)
{
	int pri_num =0;
	for(start; start < finish; start++)
	{
		int num = 0;
		
		for(int i=2; i<start; i++)
		{	if (start%i == 0)
			num ++;
		}
		
		if (num==0)
		pri_num++;

	}
	return pri_num;
}


int main(int argc, char *argv[])
{
	
	int coreid,pro_num,ave;
	int last_id,residue,Num;
	clock_t start, finish;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &coreid);
	MPI_Comm_size(MPI_COMM_WORLD, &pro_num);
	
	
	last_id = pro_num-1;
	residue = N%last_id+1;
	ave = N/last_id;
	start = clock();

	if (coreid !=0 )
	{	//���һ���̶߳Ծ��ֵĽ��������β����
		if (coreid == last_id)
		{
			Num = is_prime((coreid-1)*ave,coreid*ave+residue);
			//�����һλ�̴߳���Ľ�����͸�0���߳̽��л��ܴ���
			MPI_Send(&Num, 1, MPI_INT, 0, 99 , MPI_COMM_WORLD);
		}
		//�����̴߳�����ֵĹ���
		else
		{
			Num = is_prime((coreid-1)*ave, coreid*ave);
			//�����̴߳���Ľ��һ�����͸�0���̻߳���
			MPI_Send(&Num, 1, MPI_INT, 0, 99, MPI_COMM_WORLD);
	
		}
		
	}
		//0���߳̽��������߳������͵Ľ��	
	else
	
	{
		int id_sum;
		int Total_prime_num = 0;
		//��ʼ���������ṹ
		for(int core=1; core < pro_num; core++)
		{
			MPI_Recv(&id_sum, 10, MPI_INT, core, 99, MPI_COMM_WORLD, &status);
			Total_prime_num += id_sum;
		}
		
		printf("The prime number is: %d\n", Total_prime_num-2);
	}
	
	
	finish = clock();
	
	if (coreid == 0)
	{
		double time = (double)(finish - start)/CLOCKS_PER_SEC;
		
		printf("Time: %f s\n", time);		
	}

	MPI_Finalize();
	return 0;

}
