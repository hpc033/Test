#include <stdio.h>
#include <math.h>
int main(void)
{
	double a,b,c,x1,x2,d;
	scanf("%lf%lf%lf",&a,&b,&c);
	d = b * b - 4 * a * c;
	if(d > 0)
	{
		x1 = (-1 * b + sqrt(d)) / (2 * a);
		x2 = (-1 * b - sqrt(d)) / (2 * a);
		printf("x1 = %g,x2 = %g\n",x1,x2);
	} 
	else if(d = 0)
	{
		x1 = x2 = (-1 * b) / (2 * a);
		printf("x1 = %g,x2 = %g\n",x1,x2);
	}
	else
	{
		printf("方程没有实根\n");
	}
	
	return 0;
}
