#include "cs50.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_ROUNDS 21
#define BOTS_NUM 10
int MAX_PLAYERS = 2;

typedef struct
{
    int wins;
    int losses;
    int ties;

} stat;

typedef struct
{
    bool attack[MAX_ROUNDS];
    int score;
    string name;
    stat stats;
} player;

typedef struct
{
    string name;
    string description;
    stat stats;
} bot;




bot bots[BOTS_NUM] = {
        {"tit4tat", "Prefers to mirror its opponent's moves, creating a delicate dance of strategy. Watch its moves closely for a clue on how to respond.", {0, 0, 0}},
        {"random", "Embraces randomness, making every move a surprise. Predicting this bot's next move is like trying to catch a breeze.", {0, 0, 0}},
        {"tit4twotat", "A variation of tit-for-tat, offering a glimpse of forgiveness. It might give you a second chance, but don't rely on it too much.", {0, 0, 0}},
        {"grudge", "Holds onto past betrayals, responding with caution. Be careful not to provoke its lingering distrust.", {0, 0, 0}},
        {"revenger", "Strikes back with force, seeking retribution for perceived wrongs. Push it too far, and it will come back at you with a vengeance.", {0, 0, 0}},
        {"clutch", "Thrives under pressure, revealing its true strength in critical moments. Be prepared for a surprising move when the game hangs in the balance.", {0, 0, 0}},
        {"killer", "A relentless hunter, aiming for swift victory with precision. Once it senses weakness, it won't hesitate to strike.", {0, 0, 0}},
        {"aggressor", "Assertive and dominating, pushing boundaries to control the game. It plays to win, no matter the cost.", {0, 0, 0}},
        {"vengence", "A deep-seated desire for retribution, fueling every calculated move. Beware the consequences of provoking this bot's wrath.", {0, 0, 0}},
        {"mysterybot", "One of the random bots from the above nine. Name will be covered for a very hardcore experience.", {0, 0, 0}}
    };

// Bot algorithms:
void tit4tat(int pos, bool player[], bool bot[]);
void random(int pos, bool player[], bool bot[], int *player_score, int *bot_score);
void tit4twotat(int pos, bool player[], bool bot[]);
void grudge(int pos, bool player[], bool bot[]);
void revenger(int pos, bool player[], bool bot[], int *player_score, int *bot_score);
void clutch(int pos, bool player[], int *player_score, int *bot_score);
void killer(int pos, bool bot[]);
void aggressor(int pos, bool bot[], int *player_score, int *bot_score);
void vengence(int pos, bool player[], bool bot[], int *player_score, int *bot_score);

// Game:
int displayBots(void);
void play(int i, player players, player bot, int *player_score, int *bot_score);
void rules(void);
void mainmenu(void)
{
     char *asciiart =
    "     ___      _                      _        ___  _     __                    \n"
    "    / _ \\____(_)__ ___  ___  ___ ___( )___   / _ \\(_)__ / /__ __ _  __ _  ___ _\n"
    "   / ___/ __/ (_-</ _ \\/ _ \\/ -_) __//(_-<  / // / / -_) / -_)  ' \\/  ' \\/ _ `/\n"
    "  /_/  /_/ /_/___/\\___/_//_/\\__/_/   /___/ /____/_/\\__/_/\\__/_/_/_/_/_/\\_,_/ \n"
    "                                                                               \n";
    printf("%s", asciiart);
    printf("Made by K.V.Naresh Karthigeyan\n");
    printf("source code: https://github.com/nareshkarthigeyan/prisoners-diellema-game\n\n");
    char userres = get_char("Click (P) to play game - or - (Q) to quit. Click (R) for rules: \n");
    if(toupper(userres) == 'Q')
    {
        exit(0);
    }
    else if (toupper(userres) == 'R')
    {
        rules();
    }
    else if(toupper(userres) != 'P')
    {
        exit(0);
    }

}

void rules()
{
    printf("\n\nWelcome to the Prisoner's Dilemma Game!\n");
    printf("In this game, you will play against 10 different bots, each with their own personality.\n");
    printf("The rules are simple:\n");
    printf("1. You and your opponent have two choices: 'co-op' or 'attack'.\n");
    printf("2. If both players 'co-op', you both get +3 points.\n");
    printf("3. If both players 'attack', you both get +1 point.\n");
    printf("4. If you 'attack' while your opponent 'co-ops', you get +5 points, and your opponent gets 0 points.\n");
    printf("5. The game will last for 21 rounds.\n");
    printf("6. After 21 rounds, the player with the most points wins!\n");
    printf("7. Get ready to make your moves and outwit the bots!\n");

    char userres = get_char("Click (Q) to quit to main menu: \n");
    if(toupper(userres) == 'Q')
    {
        mainmenu();
    }
}
// Main:
int main(void)
{
    quit:
    mainmenu();
    player players[MAX_PLAYERS];

    restart:
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
        players[0].name = get_string("Enter Player Name: ");
        for(int i = 0; i < strlen(players[0].name); i++)
        {
            players[0].name[i] = toupper(players[0].name[i]);
        }


        int botnum = displayBots();
        players[1].name = bots[botnum - 1].name;

        if(botnum == 10)
        {
            srand(time(NULL) + strlen(players[0].name));
            botnum = rand() % 9 + 1;
        }

        for (int i = 0; i < MAX_ROUNDS; i++)
        {
            printf("\nRound %d:\n", i + 1);
            string res = get_string("Attack or Co-operare? A/C: ");
            char response = toupper(res[0]);

            if (response == 'A')
            {
                players[0].attack[i] = true;
            }

            int pl = 0;
            int bt = 1;


            switch (botnum)
            {
                case 1:
                    tit4tat(i, players[pl].attack, players[bt].attack);
                    break;

                case 2:
                    random(i, players[pl].attack, players[bt].attack, &players[pl].score, &players[bt].score);
                    break;

                case 3:
                    tit4twotat(i, players[pl].attack, players[bt].attack);
                    break;

                case 4:
                    grudge(i, players[pl].attack, players[bt].attack);
                    break;

                case 5:
                    revenger(i, players[pl].attack, players[bt].attack, &players[pl].score, &players[bt].score);
                    break;

                case 6:
                    clutch(i, players[bt].attack, &players[bt].score, &players[pl].score);
                    break;

                case 7:
                    killer(i, players[bt].attack);
                    break;

                case 8:
                    aggressor(i, players[bt].attack, &players[bt].score, &players[pl].score);
                    break;

                case 9:
                    vengence(i, players[pl].attack, players[bt].attack, &players[pl].score, &players[bt].score);
                    break;

            }
            play(i, players[pl], players[bt], &players[pl].score, &players[bt].score);
        }
    }
    else if (BOTvBOT == true)
    {
        int botnum1, botnum2;
        botnum1 = displayBots();

        players[0].name = bots[botnum1 - 1].name;

        if(botnum1 == 10)
        {
            srand(time(NULL) + 55);
            botnum1 = rand() % 9 + 1;
        }

        botnum2 = displayBots();
        players[1].name = bots[botnum2 - 1].name;

        if(botnum2 == 10)
        {
            srand(time(NULL) + 99);
            botnum2 = rand() % 9 + 1;
        }

        for (int i = 0; i < MAX_ROUNDS; i++)
        {
            printf("\nRound %i:\n", i + 1);
            int pl = 1;
            int bt = 0;
            switch (botnum1)
            {
                case 1:
                    tit4tat(i, players[pl].attack, players[bt].attack);
                    break;

                case 2:
                    random(i, players[pl].attack, players[bt].attack, &players[pl].score, &players[bt].score);
                    break;

                case 3:
                    tit4twotat(i, players[pl].attack, players[bt].attack);
                    break;

                case 4:
                    grudge(i, players[pl].attack, players[bt].attack);
                    break;

                case 5:
                    revenger(i, players[pl].attack, players[bt].attack, &players[pl].score, &players[bt].score);
                    break;

                case 6:
                    clutch(i, players[bt].attack, &players[bt].score, &players[pl].score);
                    break;

                case 7:
                    killer(i, players[bt].attack);
                    break;

                case 8:
                    aggressor(i, players[bt].attack, &players[bt].score, &players[pl].score);
                    break;

                case 9:
                    vengence(i, players[pl].attack, players[bt].attack, &players[pl].score, &players[bt].score);
                    break;
            }

            pl = 0;
            bt = 1;
             switch (botnum2)
            {
                case 1:
                    tit4tat(i, players[pl].attack, players[bt].attack);
                    break;

                case 2:
                    random(i, players[pl].attack, players[bt].attack, &players[pl].score, &players[bt].score);
                    break;

                case 3:
                    tit4twotat(i, players[pl].attack, players[bt].attack);
                    break;

                case 4:
                    grudge(i, players[pl].attack, players[bt].attack);
                    break;

                case 5:
                    revenger(i, players[pl].attack, players[bt].attack, &players[pl].score, &players[bt].score);
                    break;

                case 6:
                    clutch(i, players[bt].attack, &players[bt].score, &players[pl].score);
                    break;

                case 7:
                    killer(i, players[bt].attack);
                    break;

                case 8:
                    aggressor(i, players[bt].attack, &players[bt].score, &players[pl].score);
                    break;

                case 9:
                    vengence(i, players[pl].attack, players[bt].attack, &players[pl].score, &players[bt].score);
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

    char play_again = get_char("Play again? (Y/N)? ");
    if (toupper(play_again) == 'Y')
    {
        goto restart;
    }
    else
    {
        goto quit;
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

    if((pos < MAX_ROUNDS / 5 && (rand() % 100 > 80)) || MAX_ROUNDS - 1 == pos)
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

void vengence(int pos, bool player[], bool bot[], int *player_score, int *bot_score)
{
    if(pos == MAX_ROUNDS - 1)
    {
        bot[pos] = true;
    }
    int copy_index = MAX_ROUNDS / 20;
    if(pos > MAX_ROUNDS / 30)
    {
        int doIt = 0;
        for (int i = MAX_ROUNDS / 30; i > 0; i--)
        {
            if(player[pos - i] == false)
            {
                doIt++;
            }
        }
        if (doIt == MAX_ROUNDS / 30)
        {
            bot[pos] = true;
        }
    }

    if(pos >= 2)
    {
        if(player[pos - 1] == true && player[pos - 2] == true)
        {
            bot[pos] = true;
        }
    }

    if (pos > 2 * copy_index && rand() % 100 > 25)
    {
        bot[pos] = player[pos - copy_index];
    }

}

int displayBots()
{
     int botnum;
     printf("\nBots List: \n");
        do
        {
            for(int i = 0; i < BOTS_NUM; i++)
            {
                printf("%i) %s - %s\n", i + 1, bots[i].name, bots[i].description);
            }
            botnum = get_int("\n\nChoose Bot: ");
            printf("\n");
        }
        while (botnum > BOTS_NUM || botnum < 1);
        return botnum;
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
