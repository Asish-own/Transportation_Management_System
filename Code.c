#include <stdio.h>
#include <string.h>

#define MAX_BUSES 10
#define MAX_ROUTE_LEN 50

int bus_numbers[MAX_BUSES];
char routes[MAX_BUSES][MAX_ROUTE_LEN];
float total_distances[MAX_BUSES]; // Array to store total distance for each bus
int num_buses = 0;

void clear_input_buffer() {
    while (getchar() != '\n'); // Clear the buffer
}

void add_bus() {
    if (num_buses < MAX_BUSES) {
        int bus_number;
        printf("Enter bus number: ");
        if (scanf("%d", &bus_number) != 1) {
            printf("Invalid input. Please enter a valid bus number.\n");
            clear_input_buffer();
            return;
        }

        // Check for duplicate bus number
        for (int i = 0; i < num_buses; i++) {
            if (bus_numbers[i] == bus_number) {
                printf("Bus number already exists. Try again.\n");
                return;
            }
        }

        bus_numbers[num_buses] = bus_number;

        printf("Enter route: ");
        clear_input_buffer();
        fgets(routes[num_buses], MAX_ROUTE_LEN, stdin);
        routes[num_buses][strcspn(routes[num_buses], "\n")] = 0; // Remove newline

        printf("Enter total distance (in km): ");
        if (scanf("%f", &total_distances[num_buses]) != 1) {
            printf("Invalid input. Please enter a valid distance.\n");
            clear_input_buffer();
            return;
        }

        num_buses++;
        printf("Bus added successfully!\n");
    } else {
        printf("Maximum number of buses reached.\n");
    }
}

void delete_bus() {
    int bus_number;
    printf("Enter bus number to delete: ");
    if (scanf("%d", &bus_number) != 1) {
        printf("Invalid input. Please enter a valid bus number.\n");
        clear_input_buffer();
        return;
    }

    for (int i = 0; i < num_buses; i++) {
        if (bus_numbers[i] == bus_number) {
            for (int j = i; j < num_buses - 1; j++) {
                bus_numbers[j] = bus_numbers[j + 1];
                strcpy(routes[j], routes[j + 1]);
                total_distances[j] = total_distances[j + 1];
            }
            num_buses--;
            printf("Bus deleted successfully!\n");
            return;
        }
    }
    printf("Bus number not found.\n");
}

void edit_bus() {
    int bus_number;
    printf("Enter bus number to edit: ");
    if (scanf("%d", &bus_number) != 1) {
        printf("Invalid input. Please enter a valid bus number.\n");
        clear_input_buffer();
        return;
    }

    for (int i = 0; i < num_buses; i++) {
        if (bus_numbers[i] == bus_number) {
            printf("Editing Bus %d\n", bus_number);

            printf("Enter new route: ");
            clear_input_buffer();
            fgets(routes[i], MAX_ROUTE_LEN, stdin);
            routes[i][strcspn(routes[i], "\n")] = 0; // Remove newline

            printf("Enter new total distance (in km): ");
            if (scanf("%f", &total_distances[i]) != 1) {
                printf("Invalid input. Please enter a valid distance.\n");
                clear_input_buffer();
                return;
            }

            printf("Bus details updated successfully!\n");
            return;
        }
    }
    printf("Bus number not found.\n");
}

void search_by_number() {
    int bus_number;
    printf("Enter bus number to search: ");
    if (scanf("%d", &bus_number) != 1) {
        printf("Invalid input. Please enter a valid bus number.\n");
        clear_input_buffer();
        return;
    }

    for (int i = 0; i < num_buses; i++) {
        if (bus_numbers[i] == bus_number) {
            printf("Bus Number: %d\nRoute: %s\nTotal Distance: %.2f km\n", bus_numbers[i], routes[i], total_distances[i]);
            return;
        }
    }
    printf("Bus number not found.\n");
}

void search_by_stoppage() {
    char stoppage[MAX_ROUTE_LEN];
    printf("Enter stoppage to search: ");
    clear_input_buffer();
    fgets(stoppage, MAX_ROUTE_LEN, stdin);
    stoppage[strcspn(stoppage, "\n")] = 0; // Remove newline

    int found = 0;
    for (int i = 0; i < num_buses; i++) {
        if (strstr(routes[i], stoppage) != NULL) {
            printf("Bus Number: %d\nRoute: %s\nTotal Distance: %.2f km\n", bus_numbers[i], routes[i], total_distances[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No buses found for the given stoppage.\n");
    }
}

void admin() {
    while (1) {
        int choice;
        printf("\n--- Admin Panel ---\n");
        printf("1. Add Bus to Schedule\n");
        printf("2. Delete Bus from Schedule\n");
        printf("3. Edit Bus in Schedule\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1: add_bus(); break;
            case 2: delete_bus(); break;
            case 3: edit_bus(); break;
            case 4: return;
            default: printf("Invalid choice. Try again.\n");
        }
    }
}

void users() {
    while (1) {
        int choice;
        printf("\n--- User Panel ---\n");
        printf("1. Search Bus by Number\n");
        printf("2. Search Buses by Stoppage\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1: search_by_number(); break;
            case 2: search_by_stoppage(); break;
            case 3: return;
            default: printf("Invalid choice. Try again.\n");
        }
    }
}

int main() {
    while (1) {
        int choice;
        printf("\n--- Transportation Management System ---\n");
        printf("1. Admin\n");
        printf("2. Users\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1: admin(); break;
            case 2: users(); break;
            case 3: printf("Exiting the system. Goodbye!\n"); return 0;
            default: printf("Invalid choice. Try again.\n");
        }
    }
}
