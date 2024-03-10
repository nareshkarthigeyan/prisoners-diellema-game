#include "cs50.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_ROUNDS 100
#define BOTS_NUM 8
int MAX_PLAYERS = 2;

typedef struct
{
    bool attack[MAX_ROUNDS];
    int score;
    string name;
} player;

string bots[BOTS_NUM] = {"tit4tat", "random", "tit4twotat", "grudge", "revenger", "clutch", "killer", "aggressor"};

// Bot algorithms:
void tit4tat(int pos, bool player[], bool bot[]);
void random(int pos, bool player[], bool bot[], int *player_score, int *bot_score);
void tit4twotat(int pos, bool player[], bool bot[]);
void grudge(int pos, bool player[], bool bot[]);
void revenger(int pos, bool player[], bool bot[], int *player_score, int *bot_score);
void clutch(int pos, bool player[], int *player_score, int *bot_score);
void killer(int pos, bool bot[]);
void aggressor(int pos, bool bot[], int *player_score, int *bot_score);

// Game:
void play(int i, player players, player bot, int *player_score, int *bot_score);

// Main:
int main(void)
{
    player players[MAX_PLAYERS];
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        players[i].score = 0;
        for (int j = 0; j < MAX_ROUNDS; j++)
        {
            players[i].attack[j] = false;
        }
    }
    bool BOTvBOT = false;
    int choose_gm_mode;
    do
    {
        choose_gm_mode = get_int("\n\nChoose Game Mode:\n1) Player vs Bot\n2) Bot vs Bot\n\nChoose: ");
        if (choose_gm_mode == 2)
        {
            BOTvBOT = true;
        }
    }
    while (choose_gm_mode > 2 || choose_gm_mode <= 0);



    if (BOTvBOT == false)
    {
        players[0].name = get_string("Enter Player 1 Name: ");
        for(int i = 0; i < strlen(players[0].name); i++)
        {
            players[0].name[i] = toupper(players[0].name[i]);
        }


        int botnum;
        do
        {
            for(int i = 0; i < BOTS_NUM; i++)
            {
                printf("%i) %s\n", i + 1, bots[i]);
            }
            botnum = get_int("\n\nChoose Bot: ");
            printf("\n");
        }
        while (botnum > BOTS_NUM || botnum < 1);
        players[1].name = bots[botnum - 1];

        for (int i = 0; i < MAX_ROUNDS; i++)
        {
            printf("Round %d:\n", i + 1);
            string res = get_string("Attack or Co-operare? A/C: ");
            char response = toupper(res[0]);

            if (response == 'A')
            {
                players[0].attack[i] = true;
            }

            switch (botnum)
            {
                case 1:
                    tit4tat(i, players[0].attack, players[1].attack);
                    break;

                case 2:
                    random(i, players[0].attack, players[1].attack, &players[0].score, &players[1].score);
                    break;

                case 3:
                    tit4twotat(i, players[0].attack, players[1].attack);
                    break;

                case 4:
                    grudge(i, players[0].attack, players[1].attack);
                    break;

                case 5:
                    revenger(i, players[0].attack, players[1].attack, &players[0].score, &players[1].score);
                    break;

                case 6:
                    clutch(i, players[1].attack, &players[1].score, &players[0].score);
                    break;

                case 7:
                    killer(i, players[1].attack);
                    break;

                case 8:
                    aggressor(i, players[1].attack, &players[1].score, &players[0].score);
                    break;
            }
            play(i, players[0], players[1], &players[0].score, &players[1].score);
        }
    }
    else if (BOTvBOT == true)
    {
        //TODO
        int botnum1, botnum2;
        do
        {
            for(int i = 0; i < BOTS_NUM; i++)
            {
                printf("%i) %s\n", i + 1, bots[i]);
            }
            botnum1 = get_int("\n\nChoose Bot: ");
            printf("\n");
        }
        while (botnum1 > BOTS_NUM || botnum1 < 1);

        players[0].name = bots[botnum1 - 1];

        do
        {
            for(int i = 0; i < BOTS_NUM; i++)
            {
                printf("%i) %s\n", i + 1, bots[i]);
            }
            botnum2 = get_int("\n\nChoose Bot: ");
            printf("\n");
        }
        while (botnum2 > BOTS_NUM || botnum2 < 1);

        players[1].name = bots[botnum2 - 1];

        for (int i = 0; i < MAX_ROUNDS; i++)
        {
            printf("Round %i:\n", i + 1);
           //lol
            switch (botnum1)
            {
                case 1:
                    tit4tat(i, players[1].attack, players[0].attack);
                    break;

                case 2:
                    random(i, players[1].attack, players[0].attack, &players[1].score, &players[0].score);
                    break;

                case 3:
                    tit4twotat(i, players[1].attack, players[0].attack);
                    break;

                case 4:
                    grudge(i, players[1].attack, players[0].attack);
                    break;

                case 5:
                    revenger(i, players[1].attack, players[0].attack, &players[1].score, &players[0].score);
                    break;

                case 6:
                    clutch(i, players[0].attack, &players[0].score, &players[1].score);
                    break;

                case 7:
                    killer(i, players[0].attack);
                    break;

                case 8:
                    aggressor(i, players[0].attack, &players[0].score, &players[1].score);
                    break;
            }
             switch (botnum2)
            {
                case 1:
                    tit4tat(i, players[0].attack, players[1].attack);
                    break;

                case 2:
                    random(i, players[0].attack, players[1].attack, &players[0].score, &players[1].score);
                    break;

                case 3:
                    tit4twotat(i, players[0].attack, players[1].attack);
                    break;

                case 4:
                    grudge(i, players[0].attack, players[1].attack);
                    break;

                case 5:
                    revenger(i, players[0].attack, players[1].attack, &players[0].score, &players[1].score);
                    break;

                case 6:
                    clutch(i, players[1].attack, &players[1].score, &players[0].score);
                    break;

                case 7:
                    killer(i, players[1].attack);
                    break;

                case 8:
                    aggressor(i, players[1].attack, &players[1].score, &players[0].score);
                    break;
            }

            play(i, players[0], players[1], &players[0].score, &players[1].score);
        }

    }

    printf("\nGAME OVER\n");
    if (players[0].score > players[1].score)
    {
        printf("%s Wins!!!\n", players[0].name);
    }
    else if (players[1].score > players[0].score)
    {
        printf("%s Wins!!!\n", players[1].name);
    }
    else
    {
        printf("Game Tied.\n");
    }
}

void tit4tat(int pos, bool player[], bool bot[])
{
    srand(time(0));
    int random_number = rand() % 100;
    if (pos - 1 >= 0)
    {
        if ((player[pos - 1] == true) || (pos == MAX_ROUNDS - 1) || (random_number < 11))
        {
            bot[pos] = true;
        }
    }
}

void random(int pos, bool player[], bool bot[], int *player_score, int *bot_score)
{
    static bool seeded = false;
    if (!seeded)
    {
        srand(time(NULL));
        seeded = true;
    }
    srand(time(NULL) + *player_score + *bot_score + pos);
    if (pos == MAX_ROUNDS - 1)
    {
        bot[pos] = true;
    }
    else
    {
        bot[pos] = (rand() % 2) ? true : false;
    }
}

void tit4twotat(int pos, bool player[], bool bot[])
{
    srand(time(0));
    int random_number = rand() % 100;
    if (pos - 1 >= 0)
    {
        if ((player[pos - 1] == true && player[pos - 2] == true) || pos == MAX_ROUNDS - 1 || random_number < 20)
        {
            bot[pos] = true;
        }
    }
}

void grudge(int pos, bool player[], bool bot[])
{
    static bool isKilled = false;
    if (pos - 1 >= 0)
    {
        if (player[pos - 1] == true)
        {
            isKilled = true;
        }

        if (isKilled == true)
        {
            bot[pos] = true;
        }
    }
}

void revenger(int pos, bool player[], bool bot[], int *player_score, int *bot_score)
{
    if (pos - 5 >= 0)
    {
        if (player[pos - 1] == true || player[pos - 2] == true || player[pos - 3] == true || player[pos - 4] == true)
        {
            bot[pos] = true;
        }

        if(*bot_score - *player_score > 20)
        {
            bot[pos] = false;
        }
    }
}

void clutch(int pos, bool player[], int *player_score, int *bot_score)
{
    int botscore = *bot_score;
    int playerscore = *player_score;

    int behindBy = botscore - playerscore;

        int remrounds = MAX_ROUNDS - (pos + 1);
        bool lasthalf = (MAX_ROUNDS / 2 <= pos) ? true : false;

    if(pos == (MAX_ROUNDS - 1) / 4)
    {
        if(behindBy == 0)
        {
            player[pos] = true;
        }
    }
    if (behindBy > 3)
    {

        float botptrate = botscore / (pos + 1);
        float playerptrate = playerscore / (pos + 1);
        float risk_factor = (float)behindBy / (float)remrounds;

        if (risk_factor > 0.2)
        {
            player[pos] = true;
        }
        else if (risk_factor > 0.5 && remrounds < (MAX_ROUNDS / 4))
        {
            player[pos] = (rand() % 2 == 0);
        }
    }
    else if(remrounds <= MAX_ROUNDS / 6)
    {
        player[pos] = true;
    }
}

void killer(int pos, bool bot[])
{
    bot[pos] = true;
}

void aggressor(int pos, bool bot[], int *player_score, int *bot_score)
{

    int botscore = *bot_score;
    int playerscore = *player_score;
    int behindBy = botscore - playerscore; 

    srand(time(NULL) + pos - behindBy);

    if(pos < MAX_ROUNDS / 5 && (rand() % 100 > 80) || MAX_ROUNDS - 1 == pos)
    {
        bot[pos] = true;
    }
    else if (behindBy >= 7)
    {
        bot[pos] = true;
    }
    else if(rand() % 2 == 0)
    {
        bot[pos] = true;
    }
}

void play(int i, player players, player bot, int *players_score, int *bot_score)
{
    if (players.attack[i] == 1 && bot.attack[i] == 1)
    {
        (*players_score)++;
        (*bot_score)++;
        printf("Both Players attacked. +1 Point for both players\n");
    }
    else if (players.attack[i] == 1 && bot.attack[i] == 0)
    {
        (*players_score) += 5;
        printf("%s attacked and %s co-operated. +5 points for %s.\n", players.name,
               bot.name, players.name);
    }
    else if (players.attack[i] == 0 && bot.attack[i] == 1)
    {
        (*bot_score) += 5;
        printf("%s attacked and %s co-operated. +5 points for %s.\n", bot.name,
               players.name, bot.name);
    }
    else if (players.attack[i] == 0 && bot.attack[i] == 0)
    {
        (*players_score) += 3;
        (*bot_score) += 3;
        printf("Both Players Co-operated. +3 Points for both players\n");
    }
    printf("%s score: %d\n%s Score: %d\n", players.name, *players_score, bot.name,
               *bot_score);
}
