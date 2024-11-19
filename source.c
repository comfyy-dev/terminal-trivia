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
        // if player powerup >  0 ask to use
        clear_terminal();
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
        
        clock_timer();
        while (current_player != NULL) {
            get_hidden_input(current_player);
            current_player = current_player->next;
        }
        wait_for_admin();
        clear_terminal();
        reveal_answer(current_question, &phead);
        wait_for_admin();
        give_points(&phead);
        clear_terminal();
        scoreboard(&phead);
        /* Give powerups 
                - Truth - Ask a personal question they must answer
                - Double drink - double someones mistake
                - More the merrier - make someone who guessed right drink
                - Clip it! - Make someone record a sound for the discord
                - Simon Says - Maybe in a cs game or IRL
                - 
        */      

        remove_question(&qhead, &current_question, &total_questions);
        wait_for_admin();
        
        // if final question -> double drink
    }
    printf("\n\nHope you guys enjoyed this :)\n\n\n");
    free_lists(&qhead, &phead);
    return EXIT_SUCCESS;
}

