
#include <stdio.h>

// Function to get valid festival days
int getValidDays()
{
    int days;

    do
    {
        printf("Enter number of festival days (1-7): ");
        scanf("%d", &days);

        if (days < 1 || days > 7)
        {
            printf("Invalid days. Try again.\n");
        }

    } while (days < 1 || days > 7);

    return days;
}

// Function to calculate daily sales
float calculateDailySales(int dayNumber)
{
    int orders;
    int i;

    float amount;
    float total = 0;
    float highest = 0;

    printf("\nDay %d - Number of orders: ",
           dayNumber);

    scanf("%d", &orders);

    while (orders < 1)
    {
        printf("Orders must be at least 1: ");
        scanf("%d", &orders);
    }

    for (i = 1; i <= orders; i++)
    {
        do
        {
            printf("Enter amount for order %d: ", i);
            scanf("%f", &amount);

            if (amount <= 0)
            {
                printf("Amount must be greater than zero.\n");
            }

        } while (amount <= 0);

        total += amount;

        if (i == 1 || amount > highest)
        {
            highest = amount;
        }
    }

    printf("Total sales: Rs. %.2f\n", total);

    printf("Average order amount: Rs. %.2f\n",
           total / orders);

    printf("Highest order amount: Rs. %.2f\n",
           highest);

    return total;
}

// Function to find highest sales day
int findHighestSalesDay(float dailySales[],
                       int numberOfDays)
{
    int i;
    int highestDay = 1;

    for (i = 1; i < numberOfDays; i++)
    {
        if (dailySales[i] > dailySales[highestDay - 1])
        {
            highestDay = i + 1;
        }
    }

    return highestDay;
}

// Function to display bar chart
void displayBarChart(float dailySales[],
                     int numberOfDays)
{
    int i, j;

    printf("\nDaily Sales Bar Chart:\n");

    for (i = 0; i < numberOfDays; i++)
    {
        printf("Day %d: ", i + 1);

        for (j = 0; j < dailySales[i] / 100; j++)
        {
            printf("*");
        }

        printf("\n");
    }
}

int main()
{
    float dailySales[7];
    float totalSales = 0;

    int days;
    int i;
    int highestDay;

    days = getValidDays();

    for (i = 0; i < days; i++)
    {
        dailySales[i] = calculateDailySales(i + 1);

        totalSales += dailySales[i];
    }

    highestDay = findHighestSalesDay(
                     dailySales, days);

    printf("\n===== Festival Summary =====\n");

    printf("Total festival sales: Rs. %.2f\n",
           totalSales);

    printf("Highest sales day: Day %d\n",
           highestDay);

    displayBarChart(dailySales, days);

    return 0;
}
