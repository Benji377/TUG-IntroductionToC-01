#include <stdio.h>

// Function to calculate juice costs
double calculateJuiceCosts(int liters, int juiceType) {
    double juiceCostPerLiter;

    if (juiceType == 1) { // Orange juice
        juiceCostPerLiter = 0.20;
    } else { // Apple juice
        juiceCostPerLiter = 0.15;
    }

    return liters * juiceCostPerLiter;
}

// Function to calculate canister costs
double calculateCanisterCosts(int quantity, int canisterSize) {
    double canisterCostPerLiter;

    switch (canisterSize) {
        case 5:
            canisterCostPerLiter = 0.10;
            break;
        case 10:
        case 20:
            canisterCostPerLiter = 0.15;
            break;
        case 15:
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

int main() {
    int juiceType, liters, canisterSize, quantity;
    double juiceCosts, canisterCosts, totalCosts;

    // Welcome message
    printf("Welcome to the juice filling machine calculator!\n\n");

    // User input: Juice Type
    do {
        printf("Which juice do you want to fill?\n1. Orange juice\n2. Apple juice\n > ");
        if (scanf("%d", &juiceType) != 1) {
            printf("Invalid input! Please choose a valid juice.\n\n");
            // Clear input buffer
            while (getchar() != '\n');
            continue;
        }

        if (juiceType != 1 && juiceType != 2) {
            printf("Invalid input! Please choose a valid juice.\n\n");
        }
    } while (juiceType != 1 && juiceType != 2);

    // User input: Liters
    do {
        printf("\nHow many litres do you want to fill? (1 to 1000)\n > ");
        if (scanf("%d", &liters) != 1) {
            printf("Invalid input! Please choose a valid amount.\n\n");
            // Clear input buffer
            while (getchar() != '\n');
            continue;
        }

        if (liters < 1 || liters > 1000) {
            printf("Invalid input! Please choose a valid amount.\n\n");
        }
    } while (liters < 1 || liters > 1000);

    // User input: Canister Size
    do {
        if (juiceType == 1) { // Orange juice
            printf("\nWhich size of canister would you like to use for your orange juice?\n");
            printf("- 5 litres\n- 10 litres\n- 20 litres\n > ");
        } else { // Apple juice
            printf("\nWhich size of canister would you like to use for your apple juice?\n");
            printf("- 5 litres\n- 15 litres\n- 25 litres\n > ");
        }

        if (scanf("%d", &canisterSize) != 1) {
            printf("Invalid input! Please choose a valid canister size.\n\n");
            // Clear input buffer
            while (getchar() != '\n');
            continue;
        }

        if ((juiceType == 1 && (canisterSize != 5 && canisterSize != 10 && canisterSize != 20)) ||
            (juiceType == 2 && (canisterSize != 5 && canisterSize != 15 && canisterSize != 25))) {
            printf("Invalid input! Please choose a valid canister size.\n\n");
        }
    } while ((juiceType == 1 && (canisterSize != 5 && canisterSize != 10 && canisterSize != 20)) ||
             (juiceType == 2 && (canisterSize != 5 && canisterSize != 15 && canisterSize != 25)));

    // Calculate canister quantity and left-over litres
    quantity = liters / canisterSize;
    int leftoverLiters = liters % canisterSize;

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
    int confirmation;
    do {
        printf("Are you sure you want to fill the canisters?\n1. Yes\n2. No\n > ");
        if (scanf("%d", &confirmation) != 1) {
            printf("Invalid input! Please choose a valid option.\n\n");
            // Clear input buffer
            while (getchar() != '\n');
            continue;
        }

        if (confirmation != 1 && confirmation != 2) {
            printf("Invalid input! Please choose a valid option.\n\n");
        }
    } while (confirmation != 1 && confirmation != 2);

    if (confirmation == 1) {
        printf("\nThe canisters will be filled as soon as we receive your payment.\n");
        printf("Thank you for using the juice filling machine calculator!\n");
    } else {
        // Restart from the juice type input
        main();
    }

    return 0;
}
