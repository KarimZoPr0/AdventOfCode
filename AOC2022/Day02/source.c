#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    DRAW = 3,
    LOST = 0,
    WIN = 6
} RoundState;

typedef enum
{
    ROCK = 1,
    PAPER = 2,
    SCISSORS = 3
} Move;

typedef struct
{
    Move move;
} Player;

Move getMove(char moveType);
RoundState getRoundState(Player player1, Player player2);
RoundState getDecodedState(Player *player1, Player *player2);
void matchRoundState(Player *player1,Player *player2, RoundState matchState);

int main()
{
    Player player1, player2;
    FILE *fp =  fopen("input.txt", "r");

    if (!fp)
    {
        printf("Cannot open file \n");
        exit(EXIT_FAILURE);
    }

    char line[20], moveType1, moveType2;
    unsigned int totalScore1 = 0, totalScore2 = 0;
    RoundState roundState;

    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%c %c", &moveType1, &moveType2);

        player1.move = getMove(moveType2);
        player2.move = getMove(moveType1);

        roundState = getRoundState(player1, player2);
        totalScore1 += (player1.move + roundState);

        roundState = getDecodedState(&player1,&player2);
        totalScore2 += (player1.move + roundState);
    }

    printf("Total Score for part 1: %d\nTotal Score for Part 2: %d", totalScore1, totalScore2);
    fclose(fp);
    return 0;
}


Move getMove(char moveType)
{
    switch (moveType) {
        case 'A':
        case 'X':
            return ROCK;
        case 'B':
        case 'Y':
            return PAPER;
        case 'C':
        case 'Z':
            return SCISSORS;
        default:
            printf("Error: invalid move");
            exit(EXIT_FAILURE);
    }
}

RoundState getRoundState(Player player1, Player player2)
{
    if (player1.move == player2.move) { return DRAW; }
    else if (player1.move == ROCK && player2.move == SCISSORS) { return WIN; }
    else if (player1.move == PAPER && player2.move == ROCK)  { return WIN; }
    else if (player1.move == SCISSORS && player2.move == PAPER) { return WIN; }
    return LOST;
}

RoundState getDecodedState(Player *player1, Player *player2)
{
    if(player1->move == PAPER)
    {
        player1->move = player2->move;
        return DRAW;
    }
    else if (player1->move == SCISSORS)
    {
        matchRoundState(player1, player2, WIN);
        return WIN;
    }

    else if(player1->move == ROCK)
    {
        matchRoundState(player1, player2, LOST);
        return LOST;
    }
}

void matchRoundState(Player *player1,Player *player2, RoundState matchState)
{
    for(player1->move = ROCK; player1->move < SCISSORS; player1->move++)
    {
        if(getRoundState(*player1,*player2) == matchState) break;
    }
}