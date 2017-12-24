#include "mpi.h"
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define N 100000 
// 判断是否为素数
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
	{	//最后一个线程对均分的结果进行收尾工作
		if (coreid == last_id)
		{
			Num = is_prime((coreid-1)*ave,coreid*ave+residue);
			//将最后一位线程处理的结果发送给0号线程进行汇总处理
			MPI_Send(&Num, 1, MPI_INT, 0, 99 , MPI_COMM_WORLD);
		}
		//其它线程处理均分的工作
		else
		{
			Num = is_prime((coreid-1)*ave, coreid*ave);
			//其它线程处理的结果一样发送给0号线程汇总
			MPI_Send(&Num, 1, MPI_INT, 0, 99, MPI_COMM_WORLD);
	
		}
		
	}
		//0号线程接受其它线程所发送的结果	
	else
	
	{
		int id_sum;
		int Total_prime_num = 0;
		//开始接受其它结构
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
