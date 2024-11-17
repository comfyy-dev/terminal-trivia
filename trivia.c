#include <stdio.h>
#include <time.h>
#include "trivia.h"
#include "question.h"

void clear_terminal() {
    #ifdef _WIN32   // Windows
        system("cls"); 
    #else   // Linux/macOS
        if (system("clear") != 0) { // Check return value of system call
            perror("Failed to clear terminal");
        } 
    #endif
}

void sleep_seconds(double seconds) {
    struct timespec ts;
    ts.tv_sec = (time_t)seconds;                           // Whole seconds
    ts.tv_nsec = (seconds - ts.tv_sec) * 1e9;              // Fractional part converted to nanoseconds

    while (nanosleep(&ts, &ts) == -1 && errno == EINTR) {  // Retry if interrupted by a signal
        // Continue retrying with the remaining time
    }
}
    
Node *create_player(Node **head, int *joined_players) {
    // Allocate memory for a new node
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Failed to allocate memory for new node");
        return NULL;
    }

    // Retry mechanism for player name input
    while (1) {
        printf(BOLD RED"\nEnter new player's name:"GREEN BOLD" ");
        if (fgets(new_node->player.name, sizeof(new_node->player.name), stdin) != NULL) {
            size_t len = strlen(new_node->player.name);
            if (len > 0 && new_node->player.name[len - 1] == '\n') {
                new_node->player.name[len - 1] = '\0';
            } else {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF) {
                    // Discard extra characters
                }
            }
            if (strlen(new_node->player.name) > 0) {
                break; // Exit loop if valid input
            } else {
                printf(BOLD RED"\nName cannot be empty. Please try again.\n");
            }
        } else {
            fprintf(stderr, BOLD RED"\nError reading input. Please try again.\n");
        }
    }

    // Initialize player fields
    new_node->player.score = 0;
    new_node->player.powerup = 0;
    new_node->player.answer = 0;
    new_node->player.colour = NULL;
    new_node->next = NULL;
    new_node->player.id = *joined_players;

    // Attach node to the list
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next; // Traverse to the end of the list
        }
        current->next = new_node;
    }

    printf(BOLD RED"\nWelcome. Go choose your beverage.\n");
    for (int i = 0;i < 4; i++) {
        printf(BOLD RED".");
        fflush(stdout);
        sleep_seconds(0.25);
    }
    (*joined_players)++;

    #ifdef DEBUG
        printf(BOLD BLUE"\nPlayer Score: %d\n", new_node->player.score);
        printf(BOLD BLUE"\nPlayer Powerup: %d\n", new_node->player.powerup);
        printf(BOLD BLUE"\nPlayer Answer: %d\n", new_node->player.answer);
        printf(BOLD BLUE"\nPlayer Id: %d\n", new_node->player.id);
    #endif
    return new_node; // Return the newly created node
}

void intro(int *total_players, Node **head) {


    printf(BOLD RED"Parsing Universe's Knowledge"NORMAL"\n");
    printf(BOLD RED"|"NORMAL);
    for (int i = 0; i < 27; i++) {
        printf(BOLD RED"-"NORMAL);
        fflush(stdout);
        sleep_seconds(0.25);
    }
    printf(BOLD RED"|\n\n"NORMAL);

    while (1) {
        printf(BOLD RED"How many individuals do you want to inebriate?"" "GREEN BOLD);
        
        char input[10];
        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Check if input is a valid integer
            char *endptr;
            long num = strtol(input, &endptr, 10);


            // Validate input: must be a positive integer and within reasonable bounds
            if (endptr != input && *endptr == '\n' && num > 0 && num <= 20) {
                *total_players = (int)num; // Set the value to the provided pointer
                break;
            } else {
                printf(BOLD RED"Invalid input. Please enter a positive integer (1-20).\n");
            }
        } else {
            printf(BOLD RED"Error reading input. Please try again.\n");
        }
    }
    int joined_players = 0;
    while (joined_players != *total_players) {
        if (create_player(head, &joined_players) == NULL) {
            fprintf(stderr, "Failed to create the first player.\n");
            exit(EXIT_FAILURE);
        }
        if (joined_players != *total_players) {
            printf(BOLD RED"\nOk. Next?\n\n");
        }
    }
    printf(BOLD RED"\nLet us begin\n");
}


void clock_timer() {
    for (int i = 5; i >= 0; i--) {
        if (i <= 10) {
            printf(NORMAL BOLD RED"\rCountdown: " BOLD RED ON_WHITE"%d" NORMAL BOLD RED  
                   " seconds remaining...   ", i); // Overwrite the same line
            printf("\a");
        } else {
            printf(BOLD RED"\rCountdown: %d  seconds remaining...   ", i); // Overwrite the same line
        }
        fflush(stdout);
        sleep_seconds(1.0);
    }
    system("aplay ./times_up.wav > /dev/null 2>&1");
    printf("\rTimes Up                              \n");
}