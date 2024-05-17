#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRAINS 5
#define MAX_TICKETS 100

typedef struct {
    char name[50];
    int age;
    char gender;
    int train_num;
    int num_of_tickets;
} PassengerDetails;

typedef struct {
    int train_num;
    char train_name[50];
    char destinations[50];
    float fare;
    char departure_time[10];
} TrainDetails;

TrainDetails trains[MAX_TRAINS] = {
    {101, "Express A", "Dhaka to Jamalpur", 1000.0, "9:00 AM"},
    {102, "Express B", "Dhaka to Chittagong", 1500.0, "12:00 PM"},
    {103, "Express C", "Jamalpur to Mymensingh", 800.0, "8:00 AM"},
    {104, "Express D", "Jamalpur to Cox's Bazar", 1200.0, "11:00 AM"},
    {105, "Express E", "Rajshahi to Rangpur", 900.0, "7:00 AM"}
};

PassengerDetails tickets[MAX_TICKETS];
int ticket_count = 0;

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pressAnyKey(void) {
    printf("\nPress any key to continue...");
    getchar();
}

void specificTrain(int train_num) {
    for (int i = 0; i < MAX_TRAINS; i++) {
        if (trains[i].train_num == train_num) {
            printf("Train:\t\t\t%s\n", trains[i].train_name);
            printf("Destinations:\t\t%s\n", trains[i].destinations);
            printf("Departure Time:\t\t%s\n", trains[i].departure_time);
            break;
        }
    }
}

void printTicket(PassengerDetails passenger, float charges) {
    system("cls");
    printf("-------------------\n");
    printf("\tTICKET\n");
    printf("-------------------\n\n");
    printf("Name:\t\t\t%s\n", passenger.name);
    printf("Age:\t\t\t%d\n", passenger.age);
    printf("Gender:\t\t\t%c\n", passenger.gender);
    printf("Number Of Tickets:\t%d\n", passenger.num_of_tickets);
    printf("Train Number:\t\t%d\n", passenger.train_num);
    specificTrain(passenger.train_num);
    printf("Charges:\t\t%.2f\n", charges);
}

float charge(int train_num, int num_of_tickets) {
    for (int i = 0; i < MAX_TRAINS; i++) {
        if (trains[i].train_num == train_num) {
            return trains[i].fare * num_of_tickets;
        }
    }
    return 0.0;
}

void viewDetails(void) {
    system("cls");
    printf("\n===============================================\n");
    printf("      AVAILABLE TRAINS FOR RESERVATION\n");
    printf("===============================================\n");
    printf("TRAIN No\tTrain Name\t\tDestinations\t\t\tFare\t\t\tDeparture Time\n");
    for (int i = 0; i < MAX_TRAINS; i++) {
        printf("%d\t\t%s\t\t%s\t\tBDT %.2f\t\t%s\n",
               trains[i].train_num, trains[i].train_name, trains[i].destinations,
               trains[i].fare, trains[i].departure_time);
    }
    printf("===============================================\n");
}

void reservation(void) {
    if (ticket_count >= MAX_TICKETS) {
        printf("\nAll tickets are booked!\n");
        pressAnyKey();
        return;
    }
    PassengerDetails passdetails;
    char confirm;

    system("cls");
    printf("\nEnter Your Name: ");
    fgets(passdetails.name, sizeof(passdetails.name), stdin);
    strtok(passdetails.name, "\n");
    printf("Enter Your Age: ");
    scanf("%d", &passdetails.age);
    printf("Enter Your Gender (M/F): ");
    scanf(" %c", &passdetails.gender);
    printf("Enter Number of Tickets: ");
    scanf("%d", &passdetails.num_of_tickets);
    clearInputBuffer();

    viewDetails();
    printf("\nEnter train number: ");
    scanf("%d", &passdetails.train_num);

    if (passdetails.train_num >= 101 && passdetails.train_num <= 105) {
        float charges = charge(passdetails.train_num, passdetails.num_of_tickets);
        printTicket(passdetails, charges);

        printf("\n\nConfirm Ticket (y/n): ");
        scanf(" %c", &confirm);

        if (confirm == 'y') {
            tickets[ticket_count++] = passdetails;
            printf("\nReservation successful!\n");
        } else {
            printf("\nReservation not done!\n");
        }
    } else {
        printf("\nInvalid train number!\n");
    }
    pressAnyKey();
}

void cancelReservation(void) {
    if (ticket_count == 0) {
        printf("\nNo tickets found!\n");
        return;
    }
    char name[50];
    printf("\nEnter Passenger Name to cancel: ");
    fgets(name, sizeof(name), stdin);
    strtok(name, "\n");

    int ticketFound = 0;
    for (int i = 0; i < ticket_count; i++) {
        if (strcmp(tickets[i].name, name) == 0) {
            for (int j = i; j < ticket_count - 1; j++) {
                tickets[j] = tickets[j + 1];
            }
            ticket_count--;
            printf("\nTicket cancelled successfully!\n");
            ticketFound = 1;
            break;
        }
    }

    if (!ticketFound) {
        printf("\nTicket not found for the given passenger name.\n");
    }
}

void generateReport(void) {
    system("cls");
    printf("\n===============================================\n");
    printf("           RAILWAY RESERVATION REPORT\n");
    printf("===============================================\n");
    for (int i = 0; i < ticket_count; i++) {
        printf("Passenger Name:\t%s\n", tickets[i].name);
        printf("Age:\t\t%d\n", tickets[i].age);
        printf("Gender:\t\t%c\n", tickets[i].gender);
        printf("Train Number:\t%d\n", tickets[i].train_num);
        printf("Number Of Tickets:\t%d\n", tickets[i].num_of_tickets);
        specificTrain(tickets[i].train_num);
        printf("-----------------------------------------------\n");
    }
    if (ticket_count == 0) {
        printf("No reservations found.\n");
    }
}

int main() {
    int menu_choice;
    while (1) {
        system("cls"); // For Windows
        printf("\t\t|           RAILWAY TICKET RESERVATION SYSTEM          |\n");
        printf("\t\t|                            By Tahira_Afia            |\n");
        printf("\t\t|                            Bangladesh Railway        |\n");
        printf("\t\t------------------------------------------------------\n");
        printf("\t\t1. Book Ticket\n");
        printf("\t\t2. View Available Trains\n");
        printf("\t\t3. Cancel Ticket\n");
        printf("\t\t4. Generate Report\n");
        printf("\t\t5. Exit\n");
        printf("\t\t------------------------------------------------------\n");
        printf("\t\tEnter your choice: ");
        scanf("%d", &menu_choice);
        clearInputBuffer();

        switch (menu_choice) {
            case 1:
                reservation();
                break;
            case 2:
                viewDetails();
                pressAnyKey();
                break;
            case 3:
                cancelReservation();
                pressAnyKey();
                break;
            case 4:
                generateReport();
                pressAnyKey();
                break;
            case 5:
                exit(0);
            default:
                printf("\nInvalid choice! Please enter a valid option.\n");
                pressAnyKey();
        }
    }
    return 0;
}
