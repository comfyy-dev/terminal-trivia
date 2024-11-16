#ifndef QUESTION_H
#define QUESTION_H

#include "trivia.h"

typedef struct {
    char question[100];
    char answer[30];
    int qid;
    int powerup;
} Question;

typedef struct {
    Question question;
    struct QNode *next;
} QNode;

void create_questions_list(const char *filename, QNode **qhead, int *total_questions);
void add_question(QNode **head, const char *question_text, const char *answer_text, int qid);
QNode *get_question(QNode **head, int total_questions);
void remove_question(QNode **head, QNode **current, int *total_questions);
void free_list(QNode *head);

#endif