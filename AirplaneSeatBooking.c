#include <stdio.h>
#include <ctype.h>

// Define the number of rows and columns for the airplane seats
#define ROWS 5
#define COLS 4

// Define a struct to represent the status of a seat ('X' for occupied, letters from 'A' to 'D' for available)
struct SeatStatus {
    char status;
};

// Define a struct to represent the small airplane with a 2D array of SeatStatus to store seat statuses
struct SmallAirplane {
    struct SeatStatus seats[ROWS][COLS];
};

// Function to assign initial seat statuses to the airplane
void AssigningElements(struct SmallAirplane *airplane) {
    for (int i = 0; i < ROWS * COLS; i++)
        airplane->seats[0][i].status = 'A' + i % COLS;
}

// Function to print the airplane seat pattern with seat numbers and statuses
void PrintingAirplaneSeats(struct SmallAirplane *airplane) {
    printf("\nSeat Pattern:\n\n");

    for (int i = 0; i < ROWS; i++) {
        printf("%d\t", i + 1);
        for (int j = 0; j < COLS; j++)
            printf("%c\t", (*(*(airplane->seats + i) + j)).status);

        printf("\n");
    }
}

// Function to display available seats and their corresponding row numbers and letters
void displayAvailableSeats(struct SmallAirplane *airplane) {
    int i, j, availableSeats = 0;
    
    printf("Available Seats:\n");
    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            if (airplane->seats[i][j].status != 'X') {
                printf("%d%c | ", i + 1, airplane->seats[i][j].status);
                availableSeats++;
            }

    printf("\n\n");
    printf("Number of available seats: %d\n", availableSeats);
}

// Function to ask the user to enter a seat number and letter, check seat availability, and assign the seat if available
void GetSeatNumber(struct SmallAirplane *airplane, int *assignedSeats) {
    int seatNumber, row, column;
    char seatLetter;

    do {
        printf("Enter seat number (1-5): ");
        while (scanf("%d", &seatNumber) != 1 || seatNumber <= 0 || seatNumber > ROWS) {
            printf("Invalid input. Please enter a valid seat number (1-5):\n\tRESPONSE: ");
            while (getchar() != '\n');
        }

        printf("Enter seat letter (A-D): ");
        while (scanf(" %c", &seatLetter) != 1 || !isalpha(seatLetter) || seatLetter < 'A' || seatLetter > 'D') {
            printf("Invalid input. Please enter a valid capital column letter (A-D):\n\tRESPONSE: ");
            while (getchar() != '\n');
        }         

        row = seatNumber - 1;
        column = seatLetter - 'A';   

        if (airplane->seats[row][column].status == 'X')
            printf("Sorry, the seat is already occupied. Please choose another seat.\n");

    } while (airplane->seats[row][column].status == 'X');

    airplane->seats[row][column].status = 'X';
    printf("\n%d%c | Seat assigned successfully!\n", seatNumber, seatLetter);

    (*assignedSeats)++;
}

// Main function
int main() {
    struct SmallAirplane airplane;

    int totalSeats = ROWS * COLS;
    int assignedSeats = 0;
    int numSeatsToTake;

    // Assign initial seat statuses to the airplane
    AssigningElements(&airplane);

    // Display welcome messages and initial airplane seat pattern
    printf("Experience the joy in every journey with Laurenz Airlines. BOOK NOW.\n");
    printf("Welcome to the Seat Assignment System!\n");
    PrintingAirplaneSeats(&airplane);
    displayAvailableSeats(&airplane);
    
    // Loop to ask the user how many seats they want to take and assign seats accordingly
    while (assignedSeats != totalSeats) {
        printf("How many seats would you like to take?\n\tRESPONSE: ");
        while (scanf("%d", &numSeatsToTake) != 1 || numSeatsToTake <= 0 || numSeatsToTake > totalSeats) {
            printf("Invalid input. Please enter a positive number within the available seat range:\n\tRESPONSE: ");
            while (getchar() != '\n');
        }

        // Loop to assign each seat requested by the user
        while (numSeatsToTake--) {
            GetSeatNumber(&airplane, &assignedSeats);
            PrintingAirplaneSeats(&airplane);
            displayAvailableSeats(&airplane);
        }

        // Update the total available seats count after assigning seats
        totalSeats -= assignedSeats;
    }

    printf("Congratulations! Your ticket has been confirmed.\nPlease print your boarding pass and proceed to the departure gate. Thank you!");
}
