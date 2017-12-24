#include <stdio.h>
#include <time.h>
#include <omp.h>
int main()
{
clock_t t1,t2;
t1 = clock();
int i, n;
float a[10000], b[10000], result;
n = 10000;
result = 0.0;
for (i = 0; i < n; i++)
{
a[i] = i * 1.0;
b[i] = i * 2.0;
}
#pragma omp parallel for private(i) reduction(+:result)
for (i = 0; i < n; i++)
{
result = result + (a[i] * b[i]);
}
t2 = clock();
printf("t=%f\n",(double)(t2-t1)/CLOCKS_PER_SEC);
printf("a*b= %12.6lf\n", result);
return 0;
}
