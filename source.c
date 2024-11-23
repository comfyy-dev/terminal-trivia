#include <stdio.h>
#include "trivia.h"
#include "question.h"


Node *phead = NULL;
QNode *qhead = NULL;
int total_players = 0;
int total_questions = 0;
int total_rounds = 0;
int current_round = 1;

int main(int argc, char *argv[]) {
    if (argc != 2) { // Expect exactly one argument (the file name)
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char *questions_file = argv[1]; // File name passed as argument
    srand(time(NULL));

    /*                             Start up Sequence                         */
    #ifdef RELEASE
        clear_terminal();
    #endif
    intro(&total_players, &total_rounds, &phead);
    create_questions_list(questions_file, &qhead, &total_questions);
    #ifdef DEBUG
        printf(BOLD BLUE"total_players = %d\n", total_players);
        printf(BOLD BLUE"total_questions = %d\n", total_questions+1);
        printf(BOLD BLUE"total_rounds = %d\n", total_rounds);
        printf(BOLD BLUE"current_round = %d\n", current_round);
    #endif
    wait_for_admin();

    /*                              Trivia Loop                               */
    while ((qhead && total_questions > 0) && (current_round <= total_rounds)) {
        clear_terminal();

        if (current_round % 5 == 0) {
            special_round(&phead);
        }

        if (current_round == total_rounds) {
            printf(NORMAL "FINAL QUESTION\n\n");
        }
        #ifdef DEBUG
            printf(BOLD BLUE"total_questions = %d\n", total_questions+1);
            printf(BOLD BLUE"total_rounds = %d\n", total_rounds);
            printf(BOLD BLUE"current_round = %d\n", current_round);
        #endif

        QNode *current_question = get_question(&qhead, total_questions, &current_round);
        if (current_question == NULL) {
            break;
        }
        Node *current_player = phead;
        #ifdef RELEASE
            clock_timer();
        #endif
        while (current_player != NULL) {
            get_hidden_input(current_player);
            current_player = current_player->next;
        }
        wait_for_admin();
        clear_terminal();
        reveal_answer(current_question, &phead);
        give_points(&phead);
        clear_terminal();
        if (current_round != total_rounds) {
            scoreboard(&phead);
        }
        remove_question(&qhead, &current_question, &total_questions);
        wait_for_admin();
        current_round++;
    }
    clear_terminal();
    printf(NORMAL"\t\t\t\t    GAME OVER\n\n\n\n\n");
    scoreboard(&phead);
    play_sound(0);
    printf("\n\nHope you guys enjoyed this :)\n\n\n");
    free_lists(&qhead, &phead);
    return EXIT_SUCCESS;
}

        