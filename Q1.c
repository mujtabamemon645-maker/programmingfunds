
#include <stdio.h>

int main()
{
    int seats[50][50];
    int rows, cols;
    int i, j, k;
    int total = 0;
    int available;
    int count;
    int start;
    int middle;
    int allocated = 0;
    int allocatedRow = -1;
    int allocatedSeat = -1;
    int distance, r;

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter seats per row: ");
    scanf("%d", &cols);

    if (rows <= 0 || rows > 50 ||
        cols <= 0 || cols > 50)
    {
        printf("Invalid seating dimensions.\n");
        return 0;
    }

    // Input seating plan
    for (i = 0; i < rows; i++)
    {
        printf("Enter seats for row %d:\n", i);

        for (j = 0; j < cols; j++)
        {
            scanf("%d", &seats[i][j]);
        }
    }

    // Display seating arrangement
    printf("\nSeating Arrangement:\n");

    for (i = 0; i < rows; i++)
    {
        printf("Row %d: ", i);

        for (j = 0; j < cols; j++)
        {
            if (seats[i][j] == 0)
                printf("_ ");
            else
                printf("X ");
        }

        printf("\n");
    }

    // Available seats in each row
    printf("\nSeat Availability Report:\n");

    for (i = 0; i < rows; i++)
    {
        available = 0;

        for (j = 0; j < cols; j++)
        {
            if (seats[i][j] == 0)
            {
                available++;
            }
        }

        printf("Row %d: %d available seats\n",
               i, available);

        total += available;
    }

    printf("Total available seats: %d\n", total);

    // Input group size
    printf("\nEnter number of customers: ");
    scanf("%d", &k);

    if (k <= 0 || k > cols)
    {
        printf("Invalid group size.\n");
        return 0;
    }

    middle = rows / 2;

    // Search middle row first
    for (distance = 0; distance < rows; distance++)
    {
        // Smaller row number first when equally distant
        for (r = middle - distance;
             r <= middle + distance;
             r++)
        {
            if (r < 0 || r >= rows)
                continue;

            if (distance > 0 &&
                r != middle - distance &&
                r != middle + distance)
                continue;

            count = 0;

            for (j = 0; j < cols; j++)
            {
                if (seats[r][j] == 0)
                {
                    count++;
                }
                else
                {
                    count = 0;
                }

                if (count == k)
                {
                    start = j - k + 1;

                    allocatedRow = r;
                    allocatedSeat = start;
                    allocated = 1;

                    break;
                }
            }

            if (allocated)
                break;
        }

        if (allocated)
            break;
    }

    // Confirm booking
    if (allocated)
    {
        printf("\nBooking Successful!\n");
        printf("Allocated row: %d\n", allocatedRow);

        printf("Allocated seats: ");

        for (j = allocatedSeat;
             j < allocatedSeat + k;
             j++)
        {
            seats[allocatedRow][j] = 1;
            printf("%d ", j);
        }

        printf("\nUpdated Seating Arrangement:\n");

        for (i = 0; i < rows; i++)
        {
            printf("Row %d: ", i);

            for (j = 0; j < cols; j++)
            {
                if (seats[i][j] == 0)
                    printf("_ ");
                else
                    printf("X ");
            }

            printf("\n");
        }

        total -= k;

        printf("Remaining available seats: %d\n",
               total);
    }
    else
    {
        printf("No consecutive seats available.\n");
    }

    return 0;
}
