#include<stdio.h>
#include <time.h>
#include<omp.h>

void smallwork()  
{  
    printf("smallwork ThreadID %d\n",omp_get_thread_num());  
}  
void bigwork()  
{  
    long long sum=0;  
    for(long i=1;i<=1000000000;i++)  
        sum+=i;  
    printf("bigwork ThreadID %d sum=%lld\n",omp_get_thread_num(),sum);  
}  

int main()
{
 
    clock_t t1,t2;  
    t1=clock();  
     #pragma omp parallel for num_threads(2)
    for(int i=1;i<=4;i++)  
    {  
        if(i<=2)          //线程1、2上做smallwork，3、4上做bigwork  
            smallwork();  
        else  
            bigwork();  
    }  
    t2=clock();  
     printf("first : t=%f\n",(double)(t2-t1)/CLOCKS_PER_SEC); 
      
    t1=clock();  
     #pragma omp parallel for num_threads(2)
    for(int i=1;i<=4;i++)  
    {  
        if(i%2)          //线程1、3上做smallwork，2、4上做bigwork  
            smallwork();  
        else  
            bigwork();  
    }  
    t2=clock();  
    printf("second : t=%f\n",(double)(t2-t1)/CLOCKS_PER_SEC);    
    return 0;  
}
