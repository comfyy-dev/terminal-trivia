#include <stdio.h>
#include "trivia.h"
#include "question.h"

// Free all nodes in the linked list
void free_list(QNode *head) {
    while (head) {
        QNode *temp = head;
        head = head->next;
        free(temp);
    }
}

void add_question(QNode **head, const char *question_text, const char *answer_text, int qid) {
    QNode *new_qnode = (QNode *)malloc(sizeof(QNode));
    if (new_qnode == NULL) {
        perror("Failed to allocate memory for new question");
        exit(EXIT_FAILURE);
    }

    // Populate the question fields
    strncpy(new_qnode->question.question, question_text, sizeof(new_qnode->question.question) - 1);
    new_qnode->question.question[sizeof(new_qnode->question.question) - 1] = '\0'; // Null-terminate
    strncpy(new_qnode->question.answer, answer_text, sizeof(new_qnode->question.answer) - 1);
    new_qnode->question.answer[sizeof(new_qnode->question.answer) - 1] = '\0'; // Null-terminate
    new_qnode->question.qid = qid;
    new_qnode->question.powerup = 0;

    // Attach the node to the end of the list
    new_qnode->next = NULL;
    if (*head == NULL) {
        *head = new_qnode; // First node
    } else {
        QNode *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_qnode;
    }
}

void create_questions_list(const char *filename, QNode **qhead, int *total_questions) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening questions file");
        exit(EXIT_FAILURE);
    }

    char line[150];
    while (fgets(line, sizeof(line), file) != NULL) { // Read a line from the file
        // Split the line into question and answer
        char *token = strtok(line, ",");
        if (token == NULL) {
            fprintf(stderr, "Invalid line format: missing question\n");
            continue;
        }

        char write_q[100];
        strncpy(write_q, token, sizeof(write_q) - 1);
        write_q[sizeof(write_q) - 1] = '\0'; // Ensure null termination

        token = strtok(NULL, ",");
        if (token == NULL) {
            fprintf(stderr, "Invalid line format: missing answer\n");
            continue;
        }

        char write_a[30];
        strncpy(write_a, token, sizeof(write_a) - 1);
        write_a[sizeof(write_a) - 1] = '\0'; // Ensure null termination

        // Remove the trailing newline from the answer
        size_t len = strlen(write_a);
        if (len > 0 && write_a[len - 1] == '\n') {
            write_a[len - 1] = '\0';
        }

        // Add the question to the linked list
        add_question(qhead, write_q, write_a, (*total_questions)++);
    }

    fclose(file);
}

QNode *get_question(QNode **head, int total_questions) {
    if (*head == NULL || total_questions <= 0) {
        fprintf(stderr, "[Get_Question] Error: No questions available or invalid total_questions.\n");
        return NULL;
    }
    srand(time(NULL));
    int random_index = rand() % total_questions;

    QNode *current = *head;
     for (int i = 0; i < random_index; i++) {
        current = current->next;
    }
    printf(NORMAL"Question %d: %s\n", current->question.qid, current->question.question);
    return current;
}

void remove_question(QNode **head, QNode **current, int *total_questions) {
    if (*current == NULL || *head == NULL || *total_questions <= 0) {
        fprintf(stderr, "[Remove_Question] Error: No questions available or invalid total_questions.\n");
        return;
    }
    QNode *to_remove = *current;
    // If the node to remove is the head node
    if (to_remove == *head) {
        *head = to_remove->next; // Update head to the next node
    } else {
        // Traverse the list to find the previous node
        QNode *join_node = *head;
        while (join_node->next != to_remove) {
            join_node = join_node->next;
        }
        join_node->next = to_remove->next; // Bypass the node to remove
    }

    free(to_remove); // Free the memory of the removed node
    (*total_questions)--; // Decrement the total questions
}

void reveal_answer(QNode *c_question, Node **head) {
    
        printf(NORMAL"You'd be surpised that the actual answer is: \n\n"BOLD GREEN"%s\n\n" , c_question->question.answer);
        printf(NORMAL"Lets see how you all did...\n");

        Node *current_player = *head;
        while (current_player != NULL) {
            printf(NORMAL"---------------------------------------------------------------------------------\n"NORMAL);
            printf("%s%s:\t\t"NOTHING BOLD GREEN"%s\n",current_player->player.colour, current_player->player.name, current_player->player.answer);
            current_player = current_player->next;
        }
        printf(NORMAL"---------------------------------------------------------------------------------\n"NORMAL);
        printf(NORMAL UNDERLINE "DRINK UP\n"NORMAL);
}