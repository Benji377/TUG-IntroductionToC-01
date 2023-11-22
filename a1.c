//---------------------------------------------------------------------------------------------------------------------
// a1.c
//
// This program implements a calculator for a juice filling machine.
// Farmers produce different amounts of various juices, which can be filled into canisters.
// Depending on the user's input, the calculator determines the price for the filling.
//
// Group: Not yet assigned
//
// Author: 12320035
//---------------------------------------------------------------------------------------------------------------------
//

// Include library to work with Input and output (standardIO)
#include <stdio.h>

#define WELCOME_MESSAGE "Welcome to the juice filling machine calculator!\n"
#define GOODBYE_MESSAGE "\nThe canisters will be filled as soon as we receive your payment.\nThank you for using the juice filling machine calculator!\n"

#define MINI_CANISTER 5
#define SMALL_CANISTER 10
#define MEDIUM_CANISTER 15
#define BIG_CANISTER 20
#define MEGA_CANISTER 25

const int ORANGE_JUICE = 1;
const double ORANGE_JUICE_COST_PER_LITER = 0.20;
const int APPLE_JUICE = 2;
const double APPLE_JUICE_COST_PER_LITER = 0.15;

const double FLAT_RATE = 5.00;
const int MAX_LITERS = 1000;
const int MIN_LITERS = 1;

const double MINI_CANISTER_COST = 0.10;
const double SMALL_CANISTER_COST = 0.15;
const double MEDIUM_CANISTER_COST = 0.20;
const double BIG_CANISTER_COST = 0.20;
const double MEGA_CANISTER_COST = 0.25;

// Forward declarations
double calculateJuiceCosts(int liters, int juiceType);
double calculateCanisterCosts(int quantity, int canisterSize);


//------------------------------------------------------------------------------
///
/// The main program.
/// It starts by printing a welcome message, then it starts a loop where it asks for the input information. Since its a
/// do-while loop, it is executed at least once. After the first execution, we ask if the user wants to fill the canister.
/// In case he does, we stop the loop and greet him, else we start the loop again from the beginning.
/// Inside the loop, we ask the juice type, how many litres he wants to fill and which canister he wants to use.
/// Using this information, we then create a small infobox where we display the amount of litres we can fill in each
/// canister, how many canister we need and how much this would cost.
///
/// @return always zero
//
int main()
{
    int juiceType, liters, canisterSize, quantity;
    double juiceCosts, canisterCosts, totalCosts;
    int confirmation;

    // Welcome message
    printf(WELCOME_MESSAGE);
    // A loop that goes through each instruction at least once, as long as the user doesn't stop it.
    do
    {
        // User input: Juice Type. Ask until the inputted value is correct
        do
        {
            printf("\nWhich juice do you want to fill?\n1. Orange juice\n2. Apple juice\n > ");
            if (scanf("%d", &juiceType) != 1)
            {
                printf("Invalid input! Please choose a valid juice.\n");
                // Clear input buffer
                while (getchar() != '\n');
                continue;
            }

            if (juiceType != ORANGE_JUICE && juiceType != APPLE_JUICE)
            {
                printf("Invalid input! Please choose a valid juice.\n");
            }
        }
        while (juiceType != ORANGE_JUICE && juiceType != APPLE_JUICE);

        // User input: Liters
        do
        {
            printf("\nHow many litres do you want to fill? (%d to %d)\n > ", MIN_LITERS, MAX_LITERS);
            if (scanf("%d", &liters) != 1)
            {
                printf("Invalid input! Please choose a valid amount.\n");
                // Clear input buffer
                while (getchar() != '\n');
                continue;
            }

            if (liters < MIN_LITERS || liters > MAX_LITERS)
            {
                printf("Invalid input! Please choose a valid amount.\n");
            }
        }
        while (liters < MIN_LITERS || liters > MAX_LITERS);

        // User input: Canister Size
        do
        {
            if (juiceType == ORANGE_JUICE)
            {
                printf("\nWhich size of canister would you like to use for your orange juice?\n");
                printf("- %d litres\n- %d litres\n- %d litres\n > ", MINI_CANISTER, SMALL_CANISTER, BIG_CANISTER);
            }
            else
            {
                printf("\nWhich size of canister would you like to use for your apple juice?\n");
                printf("- %d litres\n- %d litres\n- %d litres\n > ", MINI_CANISTER, MEDIUM_CANISTER, MEGA_CANISTER);
            }

            if (scanf("%d", &canisterSize) != 1)
            {
                printf("Invalid input! Please choose a valid canister size.\n");
                // Clear input buffer
                while (getchar() != '\n');
                continue;
            }
            // Depending on the juice type, only certain canister types are allowed
            if ((juiceType == ORANGE_JUICE && (canisterSize != MINI_CANISTER && canisterSize != SMALL_CANISTER && canisterSize != BIG_CANISTER)) ||
                (juiceType == APPLE_JUICE && (canisterSize != MINI_CANISTER && canisterSize != MEDIUM_CANISTER && canisterSize != MEGA_CANISTER)))
            {
                printf("Invalid input! Please choose a valid canister size.\n");
            }
        }
        while ((juiceType == ORANGE_JUICE && (canisterSize != MINI_CANISTER && canisterSize != SMALL_CANISTER && canisterSize != BIG_CANISTER)) ||
                 (juiceType == APPLE_JUICE && (canisterSize != MINI_CANISTER && canisterSize != MEDIUM_CANISTER && canisterSize != MEGA_CANISTER)));

        // Calculate canister quantity and left-over litres
        quantity = liters / canisterSize;
        int leftoverLiters = liters % canisterSize;
        liters -= leftoverLiters;

        // Calculate juice costs
        juiceCosts = calculateJuiceCosts(liters, juiceType);

        // Calculate canister costs
        canisterCosts = calculateCanisterCosts(quantity, canisterSize);

        // Calculate total costs
        totalCosts = juiceCosts + canisterCosts + FLAT_RATE; // Flat rate for using the machine

        // Display results
        printf("\nIt is possible to fill %d canisters with the size of %d litres.\n", quantity, canisterSize);
        printf("This results in %d left-over litres.\n", leftoverLiters);

        printf("\nThe filling costs are:\n");
        printf("----------------------------------------------\n");
        printf("- %d litres of %s juice: %.2f €\n", liters, (juiceType == ORANGE_JUICE) ? "orange" : "apple", juiceCosts);
        printf("- %d canisters: %.2f €\n", quantity, canisterCosts);
        printf("- Flat rate for using the machine: 5.00 €\n");
        printf("----------------------------------------------\n");
        printf("This results in a total cost of %.2f €.\n\n", totalCosts);

        // User input: Confirmation
        do
        {
            printf("Are you sure you want to fill the canisters?\n1. Yes\n2. No\n > ");
            if (scanf("%d", &confirmation) != 1)
            {
                printf("Invalid input! Please choose a valid option.\n");
                // Clear input buffer
                while (getchar() != '\n');
                continue;
            }

            if (confirmation != 1 && confirmation != 2)
            {
                printf("Invalid input! Please choose a valid option.\n");
            }
        }
        while (confirmation != 1 && confirmation != 2);

    }
    while (confirmation != 1);

        printf(GOODBYE_MESSAGE);

    return 0;
}

//------------------------------------------------------------------------------
///
/// Calculates the cost of filling up a given amount of liters of a given type of juice
/// by multiplying a fixed cost, depending of the juice type, with the amount of liters
///
/// @param liters the amount of juice in liters
/// @param juiceType the type of the juice (1 = Orange, 2 = Apple)
///
/// @return the total cost of filling up that amount of liters
//
double calculateJuiceCosts(int liters, int juiceType)
{
    if (juiceType == ORANGE_JUICE)
    {
        return liters * ORANGE_JUICE_COST_PER_LITER;
    }
    else
    {
        return liters * APPLE_JUICE_COST_PER_LITER;
    }
}

//------------------------------------------------------------------------------
///
/// Calculates the total cost of the canister by multiplying the given quantity of canister with the
/// selected canister size.
///
/// @param quantity the amount of canisters
/// @param canisterSize what size of canister to use
///
/// @return the total cost of the canisters
//
double calculateCanisterCosts(int quantity, int canisterSize)
{

    switch (canisterSize)
    {
        case MINI_CANISTER:
            return quantity * MINI_CANISTER_COST;
        case SMALL_CANISTER:
            return quantity * SMALL_CANISTER_COST;
        case MEDIUM_CANISTER:
            return quantity * MEDIUM_CANISTER_COST;
        case BIG_CANISTER:
            return quantity * BIG_CANISTER_COST;
        case MEGA_CANISTER:
            return quantity * MEGA_CANISTER_COST;
        default:
            return -1; // Invalid canister size
    }
}
