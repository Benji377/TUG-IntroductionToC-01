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
/// @param argc not used
/// @param argv not used
///
/// @return always zero
//
int main(int argc, char* argv[]) {
    int juiceType, liters, canisterSize, quantity;
    double juiceCosts, canisterCosts, totalCosts;
    int confirmation;

    // Welcome message
    printf("Welcome to the juice filling machine calculator!\n");
    // A loop that goes trough each instructions at least once, as long as the user doesn't stop it.
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

            if (juiceType != 1 && juiceType != 2)
            {
                printf("Invalid input! Please choose a valid juice.\n");
            }
        }
        while (juiceType != 1 && juiceType != 2);

        // User input: Liters
        do
        {
            printf("\nHow many litres do you want to fill? (1 to 1000)\n > ");
            if (scanf("%d", &liters) != 1)
            {
                printf("Invalid input! Please choose a valid amount.\n");
                // Clear input buffer
                while (getchar() != '\n');
                continue;
            }

            if (liters < 1 || liters > 1000)
            {
                printf("Invalid input! Please choose a valid amount.\n");
            }
        }
        while (liters < 1 || liters > 1000);

        // User input: Canister Size
        do
        {
            if (juiceType == 1)
            { // Orange juice
                printf("\nWhich size of canister would you like to use for your orange juice?\n");
                printf("- 5 litres\n- 10 litres\n- 20 litres\n > ");
            }
            else
            { // Apple juice
                printf("\nWhich size of canister would you like to use for your apple juice?\n");
                printf("- 5 litres\n- 15 litres\n- 25 litres\n > ");
            }

            if (scanf("%d", &canisterSize) != 1)
            {
                printf("Invalid input! Please choose a valid canister size.\n");
                // Clear input buffer
                while (getchar() != '\n');
                continue;
            }
            // Depending on the juice type, only certain canister types are allowed
            if ((juiceType == 1 && (canisterSize != 5 && canisterSize != 10 && canisterSize != 20)) ||
                (juiceType == 2 && (canisterSize != 5 && canisterSize != 15 && canisterSize != 25)))
            {
                printf("Invalid input! Please choose a valid canister size.\n");
            }
        }
        while ((juiceType == 1 && (canisterSize != 5 && canisterSize != 10 && canisterSize != 20)) ||
                 (juiceType == 2 && (canisterSize != 5 && canisterSize != 15 && canisterSize != 25)));

        // Calculate canister quantity and left-over litres
        quantity = liters / canisterSize;
        int leftoverLiters = liters % canisterSize;
        liters -= leftoverLiters;

        // Calculate juice costs
        juiceCosts = calculateJuiceCosts(liters, juiceType);

        // Calculate canister costs
        canisterCosts = calculateCanisterCosts(quantity, canisterSize);

        // Calculate total costs
        totalCosts = juiceCosts + canisterCosts + 5.00; // Flat rate for using the machine

        // Display results
        printf("\nIt is possible to fill %d canisters with the size of %d litres.\n", quantity, canisterSize);
        printf("This results in %d left-over litres.\n", leftoverLiters);

        printf("\nThe filling costs are:\n");
        printf("----------------------------------------------\n");
        printf("- %d litres of %s juice: %.2f €\n", liters, (juiceType == 1) ? "orange" : "apple", juiceCosts);
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

        printf("\nThe canisters will be filled as soon as we receive your payment.\n");
        printf("Thank you for using the juice filling machine calculator!\n");

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
    double juiceCostPerLiter;

    if (juiceType == 1)
    { // Orange juice
        juiceCostPerLiter = 0.20;
    }
    else
    { // Apple juice
        juiceCostPerLiter = 0.15;
    }

    return liters * juiceCostPerLiter;
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
    double canisterCostPerLiter;

    switch (canisterSize)
    {
        case 5:
            canisterCostPerLiter = 0.10;
            break;
        case 10:
            canisterCostPerLiter = 0.15;
            break;
        case 15:
        case 20:
            canisterCostPerLiter = 0.20;
            break;
        case 25:
            canisterCostPerLiter = 0.25;
            break;
        default:
            return -1; // Invalid canister size
    }

    return quantity * canisterCostPerLiter;
}