#include <stdio.h>
#include "trivia.h"
#include "question.h"

Node *phead = NULL;
QNode *qhead = NULL;
int total_players = 0;
int total_questions = 0;

int main(int argc, char *argv[]) {

    /*                              Start up Sequence                         */
    //clear_terminal();
    
    if (argc != 2) { // Expect exactly one argument (the file name)
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char *questions_file = argv[1]; // File name passed as argument

    intro(&total_players, phead);
    create_questions_list(questions_file, &qhead, &total_questions);

    /*                              Trivia Loop                               */
    while (qhead && total_questions > 0) {
        // if player powerup >  0 ask to use
        QNode *current = get_question(&qhead, total_questions);
        //timer countdown
        //ask for player answers
        //delay
        // Reveal Answer
        // Reveal players Answers
        // LOSERS DRINK DELAY
        // Enter players who were correct
        // Give powerups
        // Give points
        
    
    #ifdef DEBUG
        if (current) {
            printf( BOLD BLUE"\nQID: " BOLD GREEN"%d\n" 
                    BOLD BLUE"Question: " BOLD GREEN"%s\n" 
                    BOLD BLUE"Answer: " BOLD GREEN"%s\n" 
                    BOLD BLUE"Powerup: " BOLD GREEN"%d\n",
                    current->question.qid, current->question.question,
                    current->question.answer, current->question.powerup);
        } else {
            printf(BOLD BLUE"Failed to retrieve question.\n"NORMAL);
        }
        #endif
        remove_question(&qhead, &current, &total_questions);
        // if final question -> double drink
    }
    printf("\n\nHope you guys enjoyed this :)\n\n\n");
    return EXIT_SUCCESS;
}

