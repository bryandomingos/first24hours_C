#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    fflush(stdout);
    usleep(200000);
    printf("\nZOMBIE DICE by bryanGD");
    fflush(stdout);
    sleep(1);

    int player_amount;

    while (1)
    {
        printf("\n\n");
        fflush(stdout);
        usleep(200000);
        printf("Type the number of player_names (min: 2 / max: 99):");
        if (scanf("%d", &player_amount) == 1 && player_amount >= 2 && player_amount <= 99)
        {
            break;
        }
        while (getchar() != '\n')
            ;
        printf("\n\nInvalid value.");
    }

    char player_names[player_amount][99];
    printf("\n");

    int i, j;

    for (i = 0; i < player_amount; i++)
    {
        fflush(stdout);
        usleep(200000);
        printf("Type Player %d name: ", i + 1);
        scanf("%s", player_names[i]);

        for (j = i - 1; j >= 0; j--)
        {
            if (strcmp(player_names[i], player_names[j]) == 0)
            {
                printf("Name '%s' already in use by Player %d\n", player_names[i], j + 1);
                i--;
                break;
            }
        }
    }

    printf("\n\n\t\tPRESS ENTER FOR RANDOMIZED START\n");
    int q;
    while ((q = getchar()) != '\n' && q != EOF)
    {
    }
    getchar();

    int player_turn = rand() % player_amount;

    struct Dice
    {
        char color[7];
        char sides[7];
    };

    struct Dice tube[13];
    struct Dice hand[3];

    struct Dice Red = {"Red", "SFSBFS"};
    struct Dice Green = {"Green", "BFBSFB"};
    struct Dice Yellow = {"Yellow", "SFBSFB"};

    int full_index = 0;

    for (i = 0; i < 3; i++)
    {
        tube[full_index] = Red;
        full_index++;
    }
    for (i = 0; i < 4; i++)
    {
        tube[full_index] = Yellow;
        full_index++;
    }
    for (i = 0; i < 6; i++)
    {
        tube[full_index] = Green;
        full_index++;
    }

    int replay = 0;
    int end = 0;
    int tube_size = 13;
    int shotgun = 0;
    int shotgun_total = 0;
    int brain_on_turn = 0;
    int brain_at_risk = 0;
    int footprint = 0;
    int *brain_total = malloc(player_amount * sizeof(int));
    for (i = 0; i < player_amount; i++)
    {
        brain_total[i] = 0;
    }

    int hand_index = 0;
    int next_hand_index = 0;

    while (1)
    {
        int shotgunned = 0;

        fflush(stdout);
        usleep(300000);
        printf("\n. -_ _  _\n");
        fflush(stdout);
        usleep(300000);
        printf("Scoreboard");
        fflush(stdout);
        usleep(200000);
        printf(": ");
        fflush(stdout);
        usleep(200000);

        if (player_amount == 2)
        {
            printf("[[%s]- %d] vs [[%s]- %d]", player_names[0], brain_total[0], player_names[1], brain_total[1]);
            fflush(stdout);
            usleep(100000);
            printf("\n _ . -");
            for (i = 0; i < 3; i++)
            {
                fflush(stdout);
                usleep(200000);
                printf("\n|");
            }
        }
        else
        {
            for (i = 0; i < player_amount - 1; i++)
            {
                printf("[[%s]- %d], ", player_names[i], brain_total[i]);
            }
            printf("[[%s]- %d]", player_names[player_amount - 1], brain_total[player_amount - 1]);
            fflush(stdout);
            usleep(100000);
            printf("\n _ . -");
            for (i = 0; i < 3; i++)
            {
                fflush(stdout);
                usleep(200000);
                printf("\n|");
                fflush(stdout);
            }
        }
        if (replay == 0)
        {
            for (i = 0; i < 3; i++)
            {
                int random_index = rand() % tube_size;
                struct Dice random_dice = tube[random_index];
                for (j = random_index; j < tube_size - 1; j++)
                {
                    tube[j] = tube[j + 1];
                }
                int side_length = strlen(random_dice.sides);
                int random_side = rand() % side_length;
                char final_side = random_dice.sides[random_side];
                fflush(stdout);
                usleep(543210);
                printf("\n%s randomly selected: [%s] - ", player_names[player_turn], random_dice.color);
                if (final_side == 'S')
                {
                    printf("You got SHOT!");
                    shotgun++;
                    shotgun_total++;
                }
                else if (final_side == 'B')
                {
                    printf("You ate a BRAIN.");
                    brain_on_turn++;
                }
                else
                {
                    printf("This victim has ESCAPED!");
                    footprint++;
                    hand[hand_index] = random_dice;
                    hand_index++;
                }
                tube_size--;
            }
        }
        else if (replay == 1)
        {
            for (i = 0; i < hand_index; i++)
            {
                int side_length = strlen(hand[i].sides);
                int random_side = rand() % side_length;
                char final_side = hand[i].sides[random_side];
                fflush(stdout);
                usleep(543210);
                printf("\n%s previously selected: [%s] - ", player_names[player_turn], hand[i].color);
                if (final_side == 'S')
                {
                    printf("You got SHOT!");
                    shotgun++;
                    shotgun_total++;
                }
                else if (final_side == 'B')
                {
                    printf("You ate a BRAIN.");
                    brain_on_turn++;
                }
                else
                {
                    printf("This victim has ESCAPED!");
                    footprint++;
                    hand[next_hand_index] = hand[i];
                    next_hand_index++;
                }
            }
            for (i = 0; i <= 2 - hand_index; i++)
            {
                int random_index = rand() % tube_size;
                struct Dice random_dice = tube[random_index];
                for (j = random_index; j < tube_size - 1; j++)
                {
                    tube[j] = tube[j + 1];
                }
                int side_length = strlen(random_dice.sides);
                int random_side = rand() % side_length;
                char final_side = random_dice.sides[random_side];
                fflush(stdout);
                usleep(543210);
                printf("\n%s randomly selected: [%s] - ", player_names[player_turn], random_dice.color);
                if (final_side == 'S')
                {
                    printf("You got SHOT!");
                    shotgun++;
                    shotgun_total++;
                }
                else if (final_side == 'B')
                {
                    printf("You ate a BRAIN.");
                    brain_on_turn++;
                }
                else
                {
                    printf("This victim has ESCAPED!");
                    footprint++;
                    hand[next_hand_index] = random_dice;
                    next_hand_index++;
                }
                tube_size--;
            }

            if (footprint > 0)
            {
                hand_index = next_hand_index;
                next_hand_index = 0;
            }
            else
            {
                hand_index = 0;
                next_hand_index = 0;
            }
            sleep(1);
        }
        if (shotgun_total >= 3)
        {
            printf("\n\n\t%s GOT SHOT 3 TIMES AND FELL DOWN, loosing all of his recently accumulated precious brains.\n\n\n", player_names[player_turn]);
            brain_on_turn = 0;
            brain_at_risk = 0;
            shotgun = 0;
            shotgun_total = 0;
            shotgunned = 1;
            footprint = 0;
            for (i = 0; i < hand_index; i++)
            {
                memset(hand, 0, sizeof(hand));
            }
            hand_index = 0;
            next_hand_index = 0;
            if (player_turn + 2 > player_amount)
            {
                player_turn = 0;
            }
            else
            {
                player_turn = player_turn + 1;
            }
            sleep(2);
        }
        else
        {
            fflush(stdout);
            usleep(1000000);
            printf("\n|");
            fflush(stdout);
            usleep(500000);
            printf("\n - ");
            fflush(stdout);
            usleep(500000);
            printf("Claim %d brain(s) before getting shot %d more time(s) by passing your turn!", brain_on_turn + brain_at_risk, 3 - shotgun_total);
            fflush(stdout);
            usleep(1500000);

            if ((hand_index + tube_size) <= 3)
            {
                printf("\n%d", hand_index + tube_size);
                printf("\n%d", next_hand_index + tube_size);

                full_index = 0;
                if (next_hand_index > hand_index)
                {
                    tube_size = 12 - next_hand_index;
                }
                else
                {
                    tube_size = 12 - hand_index;
                }

                int has_red = 0;
                int has_yellow = 0;
                int has_green = 0;

                for (i = 0; i < 3; i++)
                {
                    if (strcmp(hand[i].color, "Red") == 0)
                    {
                        has_red++;
                    }
                    if (strcmp(hand[i].color, "Yellow") == 0)
                    {
                        has_yellow++;
                    }
                    if (strcmp(hand[i].color, "Green") == 0)
                    {
                        has_green++;
                    }
                }

                memset(&tube, 0, sizeof(struct Dice));

                for (i = 0; i < 3 - has_red; i++)
                {
                    tube[full_index] = Red;
                    full_index++;
                }
                for (i = 0; i < 4 - has_yellow; i++)
                {
                    tube[full_index] = Yellow;
                    full_index++;
                }
                for (i = 0; i < 6 - has_green; i++)
                {
                    tube[full_index] = Green;
                    full_index++;
                }

                printf("\n\n\tThe tube has ran out of dice...\n\tYou put the dice out of your hand back inside.\n");
                sleep(1);
                fflush(stdout);
            }

            printf("\n\n\tRemains in tube:\n");
            fflush(stdout);
            usleep(567899);
            printf("\t\t\t");
            for (i = 0; i < tube_size - 1; i++)
            {
                printf("%s, ", tube[i].color);
            }
            printf("%s\n\n", tube[tube_size - 1].color);
            sleep(2);
        }
        if (brain_total[player_turn] + brain_at_risk + brain_on_turn >= 13)
        {
            printf("\n%s ate 10 brains. You are the TOPDOG, congratulations!", player_names[player_turn]);
            end = 1;
            sleep(2);
        }
        if (end == 0 && shotgunned == 0)
        {
            while (1)
            {
                printf("\n\n%s, do you wish to continue? (y/n): ", player_names[player_turn]);
                char c;
                scanf(" %c", &c);
                if (c == 'y' || c == 'Y')
                {
                    printf("\n\n\n\t\t%s CHOSE TO CONTINUE:\n", player_names[player_turn]);
                    brain_at_risk += brain_on_turn;
                    brain_on_turn = 0;
                    shotgun = 0;
                    if (footprint > 0)
                    {
                        replay = 1;
                    }
                    else
                    {
                        replay = 0;
                        for (i = 0; i < hand_index; i++)
                        {
                            memset(hand, 0, sizeof(hand));
                        }
                        hand_index = 0;
                        next_hand_index = 0;
                    }
                    footprint = 0;
                    break;
                }
                else if (c == 'n' || c == 'N')
                {
                    printf("\n\n\n\t\t%s CHOSE TO STOP.\n", player_names[player_turn]);
                    brain_at_risk += brain_on_turn;
                    brain_total[player_turn] += brain_at_risk;
                    brain_on_turn = 0;
                    brain_at_risk = 0;
                    shotgun = 0;
                    shotgun_total = 0;
                    footprint = 0;
                    for (i = 0; i < hand_index; i++)
                    {
                        memset(hand, 0, sizeof(hand));
                    }
                    hand_index = 0;
                    next_hand_index = 0;
                    tube_size = 13;
                    memset(&tube, 0, sizeof(struct Dice));
                    full_index = 0;
                    for (i = 0; i < 3; i++)
                    {
                        tube[full_index] = Red;
                        full_index++;
                    }
                    for (i = 0; i < 4; i++)
                    {
                        tube[full_index] = Yellow;
                        full_index++;
                    }
                    for (i = 0; i < 6; i++)
                    {
                        tube[full_index] = Green;
                        full_index++;
                    }
                    if (player_turn + 2 > player_amount)
                    {
                        player_turn = 0;
                    }
                    else
                    {
                        player_turn = player_turn + 1;
                    }
                    break;
                }
            }
        }
        else if (end == 1)
            while (1)
            {
                {
                    printf("PLAY AGAIN? (y/n): ");
                    char z;
                    scanf(" %c", &z);
                    if (z == 'y' || z == 'Y')
                    {
                        end = 0;
                        replay = 0;
                        brain_on_turn = 0;
                        brain_at_risk = 0;
                        shotgun = 0;
                        shotgun_total = 0;
                        footprint = 0;
                        for (i = 0; i < player_amount; i++)
                        {
                            brain_total[i] = 0;
                        }
                        for (i = 0; i < hand_index; i++)
                        {
                            memset(hand, 0, sizeof(hand));
                        }
                        break;
                    }
                    else if (z == 'n' || z == 'N')
                    {
                        end = 2;
                        break;
                    }
                }
            }
        if (end == 2)
        {
            printf("\n\n\nGAME OVER\n\n\n");
            break;
        }
    }
    return 0;
}