
#include <stdio.h>

// Function to calculate sum of proper divisors
int sumDivisors(int num)
{
    int i;
    int sum = 0;

    for (i = 1; i <= num / 2; i++)
    {
        if (num % i == 0)
        {
            sum += i;
        }
    }

    return sum;
}

int main()
{
    int n;
    int i, j;
    int sum1, sum2;
    int pairs = 0;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("\nAmicable Pairs:\n");

    for (i = 1; i <= n; i++)
    {
        sum1 = sumDivisors(i);

        j = sum1;

        // Both numbers must be different
        if (j > i && j <= n)
        {
            sum2 = sumDivisors(j);

            if (sum2 == i)
            {
                printf("(%d, %d)\n", i, j);
                pairs++;
            }
        }
    }

    if (pairs == 0)
    {
        printf("No amicable pairs found.\n");
    }

    printf("Total pairs found: %d\n", pairs);

    return 0;
}
