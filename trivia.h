#ifndef TRIVIA_H
#define TRIVIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

#define BLACK   "\033[30m"       // foreground colours
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

#define ON_BLACK   "\033[40m"    // background colours 
#define ON_RED     "\033[41m"
#define ON_GREEN   "\033[42m"
#define ON_YELLOW  "\033[43m"
#define ON_BLUE    "\033[44m"
#define ON_MAGENTA "\033[45m"
#define ON_CYAN    "\033[46m"
#define ON_WHITE   "\033[47m"

#define CS_O       "\033[38;2;230;129;43m"
#define CS_B       "\033[38;2;137;206;245m"
#define CS_G       "\033[38;2;0;159;129m"
#define CS_Y       "\033[38;2;241;228;66m"
#define CS_M       "\033[38;2;190;45;151m"

#define BCS_O      "\033[30m\033[48;2;230;129;43m"
#define BCS_B      "\033[30m\033[48;2;137;206;245m"
#define BCS_G      "\033[30m\033[48;2;0;159;129m"
#define BCS_Y      "\033[30m\033[48;2;241;228;66m"
#define BCS_M      "\033[30m\033[48;2;190;45;151m"

#define NORMAL	   "\033[0m"     // not bold/underline/flashing/... 
#define BOLD	   "\033[1m"
#define DIM 	   "\033[2m"
#define ITALIC     "\033[3m"
#define UNDERLINE  "\033[4m"
#define BLINK      "\033[5m"
#define INVERT	   "\033[7m"

#define STRIKE     "\033[9m"

typedef struct {
    char name[21];
    int id;
    int score;
    int answer;
    int powerup;
    char *colour;
} Player;

typedef struct {
    Player player;
    struct Node *next;
} Node;

void intro(int * total_players, Node **head);
void clear_terminal();
Node *create_player(Node **head, int *joined_players);


#endif