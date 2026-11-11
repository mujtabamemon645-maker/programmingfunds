
#include <stdio.h>

#define MAX 100

// Function to input readings
void inputReadings(float temp[][MAX],
                   int sensors, int hours)
{
    int i, j;

    for (i = 0; i < sensors; i++)
    {
        printf("\nSensor %d:\n", i);

        for (j = 0; j < hours; j++)
        {
            printf("Enter temperature for hour %d: ", j);
            scanf("%f", &temp[i][j]);
        }
    }
}

// Function to analyze a sensor
float analyzeSensor(float readings[], int hours)
{
    int i;
    float sum = 0;
    float highest = readings[0];
    float lowest = readings[0];

    int critical = 0;
    int warning = 0;

    int currentStreak = 0;
    int longestStreak = 0;

    for (i = 0; i < hours; i++)
    {
        sum += readings[i];

        if (readings[i] > highest)
            highest = readings[i];

        if (readings[i] < lowest)
            lowest = readings[i];

        if (readings[i] >= 40)
        {
            critical++;
        }

        if (readings[i] >= 35 &&
            readings[i] <= 39)
        {
            warning++;
        }

        if (readings[i] >= 35)
        {
            currentStreak++;

            if (currentStreak > longestStreak)
            {
                longestStreak = currentStreak;
            }
        }
        else
        {
            currentStreak = 0;
        }
    }

    printf("Total temperature: %.2f\n", sum);
    printf("Average temperature: %.2f\n",
           sum / hours);

    printf("Highest temperature: %.2f\n", highest);
    printf("Lowest temperature: %.2f\n", lowest);

    printf("Critical readings: %d\n", critical);
    printf("Warning readings: %d\n", warning);

    printf("Longest streak: %d hours\n",
           longestStreak);

    return sum / hours;
}

// Function to find sensor with highest average
int highestAverageSensor(float temp[][MAX],
                         int sensors, int hours)
{
    int i, j;
    int highestSensor = 0;

    float sum;
    float highestAverage = 0;
    float average;

    for (i = 0; i < sensors; i++)
    {
        sum = 0;

        for (j = 0; j < hours; j++)
        {
            sum += temp[i][j];
        }

        average = sum / hours;

        if (i == 0 || average > highestAverage)
        {
            highestAverage = average;
            highestSensor = i;
        }
    }

    return highestSensor;
}

int main()
{
    float temp[MAX][MAX];
    float average;

    int sensors, hours;
    int i;
    int highestSensor;

    printf("Enter number of sensors: ");
    scanf("%d", &sensors);

    printf("Enter number of hourly readings: ");
    scanf("%d", &hours);

    if (sensors <= 0 || sensors > MAX ||
        hours <= 0 || hours > MAX)
    {
        printf("Invalid input.\n");
        return 0;
    }

    inputReadings(temp, sensors, hours);

    // Individual sensor reports
    for (i = 0; i < sensors; i++)
    {
        printf("\n===== Sensor %d Report =====\n", i);

        average = analyzeSensor(temp[i], hours);
    }

    // Highest average sensor
    highestSensor = highestAverageSensor(
                        temp, sensors, hours);

    printf("\nSensor with highest average: %d\n",
           highestSensor);

    average = 0;

    for (i = 0; i < hours; i++)
    {
        average += temp[highestSensor][i];
    }

    average = average / hours;

    printf("Highest average temperature: %.2f\n",
           average);

    return 0;
}
