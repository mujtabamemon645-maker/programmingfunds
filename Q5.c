
#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 5
#define MAX_BORROWED 3

// Display menu
void displayMenu()
{
    printf("\n===== Library Menu =====\n");
    printf("1. Register Member\n");
    printf("2. Display Books\n");
    printf("3. Borrow Book\n");
    printf("4. Return Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter choice: ");
}

// Register member
void registerMember(char name[],
                    int *studentID,
                    int *memberType)
{
    printf("Enter member name: ");
    scanf(" %49[^\n]", name);

    printf("Enter student ID: ");
    scanf("%d", studentID);

    do
    {
        printf("Membership Type (1 Student, 2 Faculty): ");
        scanf("%d", memberType);

        if (*memberType != 1 && *memberType != 2)
        {
            printf("Invalid membership type.\n");
        }

    } while (*memberType != 1 && *memberType != 2);

    printf("Member registered successfully.\n");
}

// Display books
void displayBooks(int bookIDs[],
                  char bookTitles[][50],
                  int availableCopies[],
                  int totalBooks)
{
    int i;

    printf("\nID\tTitle\t\tAvailable Copies\n");

    for (i = 0; i < totalBooks; i++)
    {
        printf("%d\t%-20s\t%d\n",
               bookIDs[i],
               bookTitles[i],
               availableCopies[i]);
    }
}

// Borrow book
void borrowBook(int bookIDs[],
                char bookTitles[][50],
                int availableCopies[],
                int totalBooks,
                int borrowedBookIDs[],
                int *borrowedCount,
                int memberType)
{
    int bookID;
    int days;
    int i;
    int found = 0;

    if (*borrowedCount >= MAX_BORROWED)
    {
        printf("Maximum borrowing limit reached.\n");
        return;
    }

    printf("Enter book ID: ");
    scanf("%d", &bookID);

    printf("Enter intended borrowing days: ");
    scanf("%d", &days);

    if (days <= 0)
    {
        printf("Days must be positive.\n");
        return;
    }

    for (i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == bookID)
        {
            found = 1;

            if (availableCopies[i] <= 0)
            {
                printf("Book is unavailable.\n");
                return;
            }

            // Check permitted borrowing period
            if ((memberType == 1 && days > 14) ||
                (memberType == 2 && days > 30))
            {
                printf("Warning: Requested days exceed "
                       "the permitted period.\n");
            }

            borrowedBookIDs[*borrowedCount] = bookID;

            (*borrowedCount)++;

            availableCopies[i]--;

            printf("Book borrowed successfully: %s\n",
                   bookTitles[i]);

            return;
        }
    }

    if (!found)
    {
        printf("Invalid book ID.\n");
    }
}

// Return book
float returnBook(int bookIDs[],
                 int availableCopies[],
                 int totalBooks,
                 int borrowedBookIDs[],
                 int *borrowedCount,
                 int memberType,
                 float *totalFine)
{
    int bookID;
    int actualDays;
    int allowedDays;
    int fineRate;

    int i, j;
    int found = 0;

    float fine = 0;
    char code[20];

    printf("Enter book ID to return: ");
    scanf("%d", &bookID);

    printf("Enter actual days kept: ");
    scanf("%d", &actualDays);

    if (actualDays <= 0)
    {
        printf("Days must be positive.\n");
        return 0;
    }

    // Verify borrowed book
    for (i = 0; i < *borrowedCount; i++)
    {
        if (borrowedBookIDs[i] == bookID)
        {
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("You have not borrowed this book.\n");
        return 0;
    }

    // Find book in inventory
    for (j = 0; j < totalBooks; j++)
    {
        if (bookIDs[j] == bookID)
        {
            break;
        }
    }

    if (j == totalBooks)
    {
        printf("Book not found in inventory.\n");
        return 0;
    }

    // Calculate fine
    if (memberType == 1)
    {
        allowedDays = 14;
        fineRate = 20;
    }
    else
    {
        allowedDays = 30;
        fineRate = 10;
    }

    if (actualDays > allowedDays)
    {
        fine = (actualDays - allowedDays) * fineRate;
    }

    printf("Fine before waiver: Rs. %.2f\n", fine);

    // Membership code for waiver
    if (fine > 0)
    {
        printf("Enter membership code for 50%% waiver: ");
        scanf("%19s", code);

        if (strcmp(code, "LIB2026") == 0)
        {
            fine = fine * 0.5;

            printf("50%% waiver applied.\n");
        }
        else
        {
            printf("Invalid code. No waiver applied.\n");
        }
    }

    // Update available copies
    availableCopies[j]++;

    // Remove returned book from borrowing list
    for (i = 0; i < *borrowedCount - 1; i++)
    {
        if (borrowedBookIDs[i] == bookID)
        {
            int k;

            for (k = i; k < *borrowedCount - 1; k++)
            {
                borrowedBookIDs[k] =
                    borrowedBookIDs[k + 1];
            }

            break;
        }
    }

    (*borrowedCount)--;

    *totalFine += fine;

    printf("Book returned successfully.\n");
    printf("Fine payable: Rs. %.2f\n", fine);

    return fine;
}

// Display member record
void displayMemberRecord(char name[],
                         int studentID,
                         int memberType,
                         int borrowedBookIDs[],
                         int borrowedCount,
                         float totalFine,
                         float fineAfterWaiver)
{
    int i;

    printf("\n===== Member Record =====\n");

    printf("Name: %s\n", name);
    printf("Student ID: %d\n", studentID);

    if (memberType == 1)
        printf("Membership: Student\n");
    else
        printf("Membership: Faculty\n");

    printf("Currently Borrowed Books: ");

    if (borrowedCount == 0)
    {
        printf("None");
    }

    for (i = 0; i < borrowedCount; i++)
    {
        printf("%d ", borrowedBookIDs[i]);
    }

    printf("\n");

    printf("Total fine charged: Rs. %.2f\n",
           totalFine);

    printf("Final fine payable: Rs. %.2f\n",
           fineAfterWaiver);
}

int main()
{
    int bookIDs[MAX_BOOKS] =
    {
        101, 102, 103, 104, 105
    };

    char bookTitles[MAX_BOOKS][50] =
    {
        "C Programming",
        "Data Structures",
        "Algorithms",
        "Database Systems",
        "Computer Networks"
    };

    int availableCopies[MAX_BOOKS] =
    {
        5, 3, 4, 2, 3
    };

    int borrowedBookIDs[MAX_BORROWED];

    char name[50];

    int studentID = 0;
    int memberType = 0;
    int borrowedCount = 0;

    int choice;
    int registered = 0;

    float totalFine = 0;
    float fineAfterWaiver = 0;
    float currentFine;

    do
    {
        displayMenu();

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:

                registerMember(name,
                               &studentID,
                               &memberType);

                registered = 1;

                break;

            case 2:

                displayBooks(bookIDs,
                             bookTitles,
                             availableCopies,
                             MAX_BOOKS);

                break;

            case 3:

                if (registered)
                {
                    borrowBook(bookIDs,
                               bookTitles,
                               availableCopies,
                               MAX_BOOKS,
                               borrowedBookIDs,
                               &borrowedCount,
                               memberType);
                }
                else
                {
                    printf("Register first.\n");
                }

                break;

            case 4:

                if (registered)
                {
                    currentFine = returnBook(
                        bookIDs,
                        availableCopies,
                        MAX_BOOKS,
                        borrowedBookIDs,
                        &borrowedCount,
                        memberType,
                        &totalFine);

                    fineAfterWaiver += currentFine;
                }
                else
                {
                    printf("Register first.\n");
                }

                break;

            case 5:

                if (registered)
                {
                    displayMemberRecord(
                        name,
                        studentID,
                        memberType,
                        borrowedBookIDs,
                        borrowedCount,
                        totalFine,
                        fineAfterWaiver);
                }
                else
                {
                    printf("Register first.\n");
                }

                break;

            case 6:

                printf("Exiting Library System.\n");

                break;

            default:

                printf("Invalid choice.\n");
        }

    } while (choice != 6);

    return 0;
}
