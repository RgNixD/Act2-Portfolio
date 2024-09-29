#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SEATS 50
#define MAX_FOODS 4

struct seat {
int seat_number;
int not_available;
int available;
char name[20];
int num_food_items;
char food_items[10][20];
};

struct seat seats[NUM_SEATS];

struct food
{
    char name[50];
    int price;
    int quantity;
};


void init_seats()
{
    int i;
    for (i = 0; i < NUM_SEATS; i++)
        {
            seats[i].seat_number = i + 1;
            seats[i].available = 1;
            strcpy(seats[i].name, "");
            seats[i].num_food_items = 0;
        }
}

void reserve_seat()
{
    char name[20];
    int seat_number;
    printf("\n\t------------------------------------------------------------------------\n");
    printf("\n\tEnter your name: ");
    scanf("%s", name);

    printf("\n\tEnter seat number to reserve: ");
    scanf("%d", &seat_number);

    if (seat_number < 1 || seat_number > NUM_SEATS)
        {
            printf("\n\t\tInvalid seat number.\n");
        }
    else if (!seats[seat_number - 1].available)
        {
            printf("\n\t\tSeat is not available.\n");
        }
    else
        {
            seats[seat_number - 1].available = 0;
            strcpy(seats[seat_number - 1].name, name);
            printf("\n\t\t\t\t[Seat reserved.]\n");
            printf("\n\t------------------------------------------------------------------------\n");

            FILE *file;
            file = fopen("reservation.txt", "a");
            if (file == NULL)
                {
                    printf("\n\tError opening file!\n");
                    return;
                }

            fprintf(file, "\n\t------------------------------------------------------------------------\n\t\t\t\t\tSEAT RESERVATION\n\t------------------------------------------------------------------------\n\n\tName: %s \t\t\t\tSeat Number: %d\n\t------------------------------------------------------------------------\n\n", name, seat_number);

            fclose(file);
        }
}

void cancel_reservation()
{
    int seat_num, i;

    printf("\n\t------------------------------------------------------------------------\n");
    printf("\n\t\t\tEnter seat number to cancel reservation: ");
    scanf("%d", &seat_num);

    for (i = 0; i < NUM_SEATS; i++)
    {
        if (seats[i].seat_number == seat_num)
        {
            if (seats[i].available)
            {
                printf("\n\t\tSeat is already available\n");
                return;
            }
            else
            {
                seats[i].available = 1;
                printf("\n\t\t\tReservation canceled for seat %d\n", seat_num);
                printf("\n\t------------------------------------------------------------------------\n");
                return;
            }
        }
    }
    printf("\n\t\t[Invalid seat number]\n");
}

void view_seats()
{
    int i;
    for (i = 0; i < NUM_SEATS; i++)
    {
        printf("\n\t------------------------------------------------------------------------\n");
        if (!seats[i].available)
        {
            printf("Seat %d: This seat is booked to %s\n", seats[i].seat_number, seats[i].name);

        }
        else
        {
            printf("Seat %d: Available\n", seats[i].seat_number);
        }
    }
}

void buy_food()
{
    FILE *fp;
    struct food foods[MAX_FOODS] =
    {
        {"Popcorn", 50, 0},
        {"1 Bottle of Water", 20, 0},
        {"Hotdog", 35, 0},
        {"Nachos", 30, 0}
    };
        printf("\n\t------------------------------------------------------------------------\n");
        printf("\n\t\t\t\tENJOY EATING FOODIE!\n");
        printf("\tMENU: \n");
    for(int i = 0; i < MAX_FOODS; i++)
        {
            printf("\n\t%d. %s - Php %d\n", i+1, foods[i].name, foods[i].price);
        }

    int choice, quantity;
        printf("\n\t------------------------------------------------------------------------\n");
        printf("\n\tEnter number of your food choice: ");
        scanf("%d", &choice);
        printf("\n\tEnter quantity: ");
        scanf("%d", &quantity);

        foods[choice-1].quantity += quantity;

        fp = fopen("sales.txt", "a");

        fprintf(fp, "\n\t------------------------------------------------------------------------\n\tItem\t\t\t\t\tPrice\t\tQuantity\n\t------------------------------------------------------------------------\n\n\t%s\t\t\t\t\t%d\t\t%d\n\t------------------------------------------------------------------------\n\n", foods[choice-1].name, foods[choice-1].price, quantity);

        fclose(fp);

        printf("\n\tFood purchased successfully! Total cost: Php %d\n", foods[choice-1].price * quantity);

         time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\n\t\t\tOrder placed at %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("\n\t\t\t[Thank you for shopping with us!]\n");
    printf("\n\t------------------------------------------------------------------------\n");
}

int main()
{
    int choice;
    init_seats();

    while (1)
    {
            printf("\n\t------------------------------------------------------------------------\n");
            printf("\n\t\t\t\tWELCOME TO CINEBITE!\n\n\t------------------------------------------------------------------------\n");
            printf("\nGood day! Here's a menu of what you would like to do.\n");
            printf("\n[1]. Reserve a seat\n[2]. Cancel a reservation\n[3]. View all seats\n[4]. Order food\n[5]. Exit\n");
            printf("\nEnter your choice: ");
            scanf("%d", &choice);

    switch (choice)
        {
            case 1: reserve_seat(); break;
            case 2: cancel_reservation(); break;
            case 3: view_seats(); break;
            case 4: buy_food(); break;
            case 5: exit(0); break;
            default:
            printf("\n\t\t\t\t[Invalid choice.]\n");
            break;
        }
    }
}
