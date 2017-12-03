#include<stdio.h>
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
    FILE *fp = fopen("out.txt", "w");
    long i, n=1000000, sum=0;
    //scanf("%ld", &n);
    for(i=2;i<=n;i++)
    {
	if(isprime(i))
        {
	    sum+=i;
            fprintf(fp,"%ld\n",i);     
	}
    }
    fclose(fp);
    printf("%ld", sum);
    return 0;
}
