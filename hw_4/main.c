
#include <stdio.h>

long long int binom_coef(long long int n, long long int k)
{
	return k == 1 ?  n : n * binom_coef(n-1, k-1) / k;
}


int main(int argc, char **argv)
{
	int n, k;
	printf("Enter n k: ");
	scanf("%d %d", &n, &k);
	printf("%lld", binom_coef(n, k));
	return 0;
}

