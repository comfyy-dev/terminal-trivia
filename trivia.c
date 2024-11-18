#include <stdio.h>
#include <time.h>
#include "trivia.h"
#include "question.h"

char * colours [] = { CS_O, CS_B, CS_G, CS_Y, CS_M, 
                      CYAN, WHITE, BLACK ON_WHITE, BLACK ON_GREEN, BLACK ON_RED,
                      BLACK ON_YELLOW, BLACK ON_BLUE, BLACK ON_MAGENTA, BLACK ON_CYAN, WHITE ON_GREEN,
                      WHITE ON_CYAN, WHITE ON_BLUE, WHITE ON_RED, WHITE ON_YELLOW, WHITE BCS_O
                    };

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
        printf(NORMAL"\nEnter new player's name:"GREEN BOLD" ");
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
                printf(NORMAL"\nName cannot be empty. Please try again.\n");
            }
        } else {
            fprintf(stderr, NORMAL"\nError reading input. Please try again.\n");
        }
    }
   
    // Initialize player fields
    new_node->player.score = 0;
    new_node->player.powerup = 0; 
    new_node->player.colour = colours[*joined_players];
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

    printf(NORMAL "\nWelcome %s%s" NORMAL ". Go choose your beverage.\n",
       new_node->player.colour, new_node->player.name);
    for (int i = 0;i < 4; i++) {
        printf(NORMAL".");
        fflush(stdout);
        sleep_seconds(0.25);
    }
    (*joined_players)++;

    #ifdef DEBUG
        printf(BOLD BLUE"\nPlayer Score: %d\n", new_node->player.score);
        printf(BOLD BLUE"\nPlayer Powerup: %d\n", new_node->player.powerup);
        printf(BOLD BLUE"\nPlayer Answer: %s\n", new_node->player.answer);
        printf(BOLD BLUE"\nPlayer Id: %d\n", new_node->player.id);
    #endif
    return new_node; // Return the newly created node
}

void intro(int *total_players, Node **head) {


    printf(NORMAL"Parsing Universe's Knowledge"NORMAL"\n");
    printf(NORMAL"|");
    for (int i = 0; i < 27; i++) {
        printf(NORMAL"-");
        fflush(stdout);
        sleep_seconds(0.25);
    }
    printf(NORMAL"|\n\n");

    while (1) {
        printf(NORMAL"How many individuals do you want to inebriate?"" "GREEN BOLD);
        
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
                printf(NORMAL"Invalid input. Please enter a positive integer (1-20).\n");
            }
        } else {
            printf(NORMAL"Error reading input. Please try again.\n");
        }
    }
    int joined_players = 0;
    while (joined_players != *total_players) {
        if (create_player(head, &joined_players) == NULL) {
            fprintf(stderr, "Failed to create the first player.\n");
            exit(EXIT_FAILURE);
        }
        if (joined_players != *total_players) {
            printf(NORMAL"\nOk. Next?\n\n");
        }
    }
    printf(NORMAL"\nLet us begin\n\n");
}


void clock_timer() {
    for (int i = 5; i >= 0; i--) {
        if (i <= 10) {
            printf(NORMAL"\rCountdown: " NORMAL ON_WHITE"%d" NORMAL  
                   " seconds remaining...   ", i); // Overwrite the same line
            printf("\a");
        } else {
            printf(NORMAL"\rCountdown: %d  seconds remaining...   ", i); // Overwrite the same line
        }
        fflush(stdout);
        sleep_seconds(1.0);
    }
    system("aplay ./times_up.wav > /dev/null 2>&1");
    printf(NORMAL"\n\rTimes Up                              \n\n");
}

void wait_for_admin() {
    printf(NORMAL"\nPress Enter to continue...\n");
    while (getchar() != '\n' && getchar() != EOF);
}

void get_hidden_input(Node *current) {
    if (current == NULL) {
        fprintf(stderr, "Error: Player is null.\n");
        return;
    }

    struct termios oldt, newt;
    char buffer[50]; // Fixed size for input
    size_t size = sizeof(buffer);
    size_t i = 0;
    char ch;

    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable echo
    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    printf(NORMAL"What is %s%s's"NORMAL" answer: ", current->player.colour, current->player.name);
    fflush(stdout);

    // Read characters one by one
    while (i < size - 1 && read(STDIN_FILENO, &ch, 1) == 1 && ch != '\n') {
        if (ch == 127) { // Handle backspace
            if (i > 0) {
                i--;
                printf("\b \b"); // Remove last asterisk
                fflush(stdout);
            }
        } else {
            buffer[i++] = ch;
        }
    }
    buffer[i] = '\0'; // Null-terminate the string

    printf("\n");

    // Store input in player's answer
    strncpy(current->player.answer, buffer, sizeof(current->player.answer) - 1);
    current->player.answer[sizeof(current->player.answer) - 1] = '\0';

    #ifdef DEBUG
        printf(BOLD BLUE"\nPlayer Score: %d" NORMAL, current->player.score);
        printf(BOLD BLUE"\nPlayer Powerup: %d" NORMAL, current->player.powerup);
        printf(BOLD BLUE"\nPlayer Answer: %s" NORMAL, current->player.answer);
        printf(BOLD BLUE"\nPlayer Id: %d\n" NORMAL, current->player.id );
    #endif

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void give_points(Node **head) {
    if (head == NULL || *head == NULL) {
        fprintf(stderr, "Error: Player list is empty or head is null.\n");
        return;
    }
    Node *current = *head;
    char response[10];
    printf(NORMAL "Who was correct?\n");
    while (current != NULL) {
        printf("\r%s%s?" NORMAL"\t (y/n):", current->player.colour, current->player.name);
        fflush(stdout);

        // Scan for 'y' or 'n'
        if (fgets(response, sizeof(response), stdin) != NULL) {
            // Remove trailing newline
            response[strcspn(response, "\n")] = '\0';

            // Check response and assign points
            if (strcmp(response, "y") == 0 || strcmp(response, "Y") == 0) {
                current->player.score += 100; // Award 100 points
                printf(INVERT"%s gained 100 points!\n" NORMAL, current->player.name);
            } else if (strcmp(response, "n") == 0 || strcmp(response, "N") == 0) {
                printf("%s received no points.\n" NORMAL, current->player.name);
            } else {
                printf(NORMAL "Invalid input. Please enter 'y' or 'n'.\n" NORMAL);
                continue; // Repeat for the same player
            }
        }

        current = current->next; // Move to the next player

    }
}

void scoreboard(Node **head) {
    if (head == NULL || *head == NULL) {
        fprintf(stderr, "Error: Player list is empty or head is null.\n");
        return;
    }

    // Count players
    Node *current_player = *head;
    int player_count = 0;
    while (current_player != NULL) {
        player_count++;
        current_player = current_player->next;
    }

    // Allocate array for sorting
    Node **players = malloc(player_count * sizeof(Node *));
    if (players == NULL) {
        perror("Failed to allocate memory for scoreboard");
        return;
    }

    // Populate array
    current_player = *head;
    for (int i = 0; i < player_count; i++) {
        players[i] = current_player;
        current_player = current_player->next;
    }

    // Sort players by score (descending order)
    for (int i = 0; i < player_count - 1; i++) {
        for (int j = i + 1; j < player_count; j++) {
            if (players[i]->player.score < players[j]->player.score) {
                Node *temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    // Print the scoreboard
    printf(NORMAL "\n\t\t\t\tCURRENT STANDINGS\n");
    printf(NORMAL "=================================================================================\n");
    printf(NORMAL "| %-20s | %-10s | %-20s |\n" NOTHING, "PLAYER NAME", "SCORE", "STATUS");
    printf(NORMAL "=================================================================================\n");

    // Highlight ties and top players
    int top_score = players[0]->player.score;
    for (int i = 0; i < player_count; i++) {
        int is_tied = (i > 0 && players[i]->player.score == players[i - 1]->player.score);

        if (players[i]->player.score == top_score) {
            // Highlight the top player(s)
            printf(BOLD GREEN "| %-20s | %-10d | %-20s |\n" NOTHING, 
                   players[i]->player.name, 
                   players[i]->player.score, 
                   is_tied ? "TIED FOR TOP" : "LEADER");
        } else if (is_tied) {
            // Highlight tied players
            printf(BOLD BLUE "| %-20s | %-10d | %-20s |\n" NOTHING, 
                   players[i]->player.name, 
                   players[i]->player.score, 
                   "TIED");
        } else {
            // Regular players
            printf("| %-20s | %-10d | %-20s |\n", 
                   players[i]->player.name, 
                   players[i]->player.score, 
                   "-");
        }
    }

    printf(NORMAL "=================================================================================\n");

    // Free allocated memory
    free(players);
}