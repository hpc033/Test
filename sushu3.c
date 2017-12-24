#include<stdio.h>
#include <time.h>
#include<omp.h>
int isprime(int k)
{
int i;
for(i=2;i*i<=k;i++)
{
if(k%i==0)
return 0;
}
return 1;
}
int main()
{
clock_t t1,t2;
FILE *fp = fopen("out-omp.txt", "w");
long i, n=100000, sum=0;
//scanf("%ld", &n);
t1 = clock();
#pragma omp parallel for private(i) reduction(+:sum) num_threads(8)
for(i=2;i<=n;i++)
{
if(isprime(i))
{
sum+=i;
fprintf(fp,"%ld\n",i);
}
}
t2 = clock();
fclose(fp);
printf("%ld\n", sum);
printf("thread 8 : t=%f\n",(double)(t2-t1)/CLOCKS_PER_SEC);
return 0;
}
