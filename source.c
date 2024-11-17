#include <stdio.h>
#include "trivia.h"
#include "question.h"


Node *phead = NULL;
QNode *qhead = NULL;
int total_players = 0;
int total_questions = 0;

int main(int argc, char *argv[]) {
    if (argc != 2) { // Expect exactly one argument (the file name)
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char *questions_file = argv[1]; // File name passed as argument


    /*                             Start up Sequence                         */

    //clear_terminal();
    intro(&total_players, &phead);
    create_questions_list(questions_file, &qhead, &total_questions);

    /*                              Trivia Loop                               */
    while (qhead && total_questions > 0) {
        // if player powerup >  0 ask to use
        QNode *current_question = get_question(&qhead, total_questions);
        printf(BOLD RED"Question %d: %s\n", current_question->question.qid, current_question->question.question);
        Node *current_player = phead;
        clock_timer();
        while (current_player != NULL) {
            get_hidden_input(current_player);
            current_player = current_player->next;
        }

        
        printf(BOLD RED"Press Enter to continue...\n");
        while (getchar() != '\n' && getchar() != EOF);
        
        
        // Reveal Answer
        // Reveal players Answers
        // LOSERS DRINK DELAY
        // Enter players who were correct
        /* Give powerups 
                - Truth - Ask a personal question they must answer
                - Double drink - double someones mistake
                - More the merrier - make someone who guessed right drink
                - Clip it! - Make someone record a sound for the discord
                - 
                
                  */
        // Give points
        
    
    #ifdef DEBUG
        if (current_question) {
            printf( BOLD BLUE"\nQID: " BOLD GREEN"%d\n" 
                    BOLD BLUE"Question: " BOLD GREEN"%s\n" 
                    BOLD BLUE"Answer: " BOLD GREEN"%s\n" 
                    BOLD BLUE"Powerup: " BOLD GREEN"%d\n\n",
                    current_question->question.qid, current_question->question.question,
                    current_question->question.answer, current_question->question.powerup);
        } else {
            printf(BOLD BLUE"Failed to retrieve question.\n"NORMAL);
        }
        #endif
        remove_question(&qhead, &current_question, &total_questions);
        // if final question -> double drink
    }
    printf("\n\nHope you guys enjoyed this :)\n\n\n");
    return EXIT_SUCCESS;
}

