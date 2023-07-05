#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    printf("\nZOMBIE DICE by bryanGD:\n");

    int player_amount;

    while (1)
    {
        printf("\nType the number of player_names (min: 2 / max: 99):");
        if (scanf("%d", &player_amount) == 1 && player_amount >= 2 && player_amount <= 99)
        {
            break;
        }
        while (getchar() != '\n')
            ;
        printf("\nInvalid value.");
    }

    char player_names[player_amount][99];
    printf("\n");

    int i, j;

    for (i = 0; i < player_amount; i++)
    {
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

    printf("\nPress any key to draw first move.\n\n");
    getch();

    int player_turn = rand() % player_amount;

    struct Dice
    {
        char color[7];
        char sides[7];
    };

    struct Dice tube[13];
    struct Dice tube_reset[13];
    struct Dice hand[3];

    struct Dice Red = {"Red", "SFSBFS"};
    struct Dice Green = {"Green", "BFBSFB"};
    struct Dice Yellow = {"Yellow", "SFBSFB"};

    int full_index = 0;

    for (i = 0; i < 3; i++)
    {
        tube[full_index] = Red;
        tube_reset[full_index] = Red;
        full_index++;
    }
    for (i = 0; i < 6; i++)
    {
        tube[full_index] = Green;
        tube_reset[full_index] = Green;
        full_index++;
    }
    for (i = 0; i < 4; i++)
    {
        tube[full_index] = Yellow;
        tube_reset[full_index] = Yellow;
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

        printf("\n. -_ _  _\nScoreboard. ");
        if (player_amount == 2)
        {
            printf("[[%s]- %d] vs [[%s]-%d]\n_.- -\n\n\n", player_names[0], brain_total[0], player_names[1], brain_total[1]);
        }
        else
        {
            for (i = 0; i < player_amount - 1; i++)
            {
                printf("[[%s]- %d], ", player_names[i], brain_total[i]);
            }
            printf("[[%s]- %d]\n_ . -\n\n\n", player_names[player_amount - 1], brain_total[player_amount - 1]);
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
                printf("%s randomly selected: [%s] - ", player_names[player_turn], random_dice.color);
                if (final_side == 'S')
                {
                    printf("You got SHOT!\n");
                    shotgun++;
                    shotgun_total++;
                }
                else if (final_side == 'B')
                {
                    printf("You ate a BRAIN.\n");
                    brain_on_turn++;
                }
                else
                {
                    printf("This victim has ESCAPED!\n");
                    footprint++;
                    hand[hand_index] = random_dice;
                    hand_index++;
                }
                tube_size--;
            }

        }
        else if (replay == 1)
        {

            printf("%s continues to play...\n\n\n", player_names[player_turn]);

            for (i = 0; i < hand_index; i++)
            {
                int side_length = strlen(hand[i].sides);
                int random_side = rand() % side_length;
                char final_side = hand[i].sides[random_side];
                printf("%s previously selected: [%s] - ", player_names[player_turn], hand[i].color);
                if (final_side == 'S')
                {
                    printf("You got SHOT!\n");
                    shotgun++;
                    shotgun_total++;
                }
                else if (final_side == 'B')
                {
                    printf("You ate a BRAIN.\n");
                    brain_on_turn++;
                }
                else
                {
                    printf("This victim has ESCAPED!\n");
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
                printf("%s randomly selected: [%s] - ", player_names[player_turn], random_dice.color);
                if (final_side == 'S')
                {
                    printf("You got SHOT!\n");
                    shotgun++;
                    shotgun_total++;
                }
                else if (final_side == 'B')
                {
                    printf("You ate a BRAIN.\n");
                    brain_on_turn++;
                }
                else
                {
                    printf("This victim has ESCAPED!\n");
                    footprint++;
                    hand[next_hand_index] = random_dice;
                    next_hand_index++;
                }
                tube_size--;
            }

            if(footprint > 0){
                hand_index = next_hand_index;
                next_hand_index = 0;
            }else{
                hand_index = 0;
                next_hand_index = 0;
            }
        }
        if (shotgun_total >= 3)
        {
            printf("\nYou got shot 3 times and fell down, loosing all of your recently accumulated precious brains.\n\n\n");
            brain_on_turn = 0;
            brain_at_risk = 0;
            shotgun = 0;
            shotgun_total = 0;
            shotgunned = 1;
            footprint = 0;
            for (i = 0; i < hand_index; i++)
                    {
                        free(hand[i].color);
                        free(hand[i].sides);
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
        }else{
            printf("\nIn this turn, %s has eaten %d brains(s) and got shot %d time(s) while %d victim(s) have escaped... ", player_names[player_turn], brain_on_turn, shotgun, footprint);
            printf("\n%s has been shot a total of %d time(s). \n\nClaim %d brain(s) before getting shot 3 times by passing your turn!\n", player_names[player_turn], shotgun_total, brain_on_turn + brain_at_risk);

            printf("\n\nRemains in tube:\n[");
            for (i = 0; i < tube_size - 1; i++)
            {
                printf("%s, ", tube[i].color);
            }
            printf("%s]\n\n", tube[tube_size - 1].color);
        }
        if (brain_total[player_turn] + brain_at_risk + brain_on_turn >= 10)
        {
            printf("\nYou ate 10 brain_on_turns. You are the TOPDOG, congratulations %s", player_names[player_turn]);
            end = 1;
        }
        if (end == 0 && shotgunned == 0)
        {
            while (1)
            {
                printf("\n\nDo you wish to continue? (y/n): ");
                int c = getchar();
                if (c == 'y' || c == 'Y')
                {
                    printf("\n\n\n%s CHOSE TO CONTINUE:", player_names[player_turn]);
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
                        free(hand[i].color);
                        free(hand[i].sides);
                        }
                        hand_index = 0;
                        next_hand_index = 0;   
                    }
                    footprint = 0;       
                    break;
                }
                else if (c == 'n' || c == 'N')
                {
                    printf("\n\n\n%s CHOSE TO STOP., player_names[player_turn]);
                    brain_at_risk += brain_on_turn;
                    brain_total[player_turn] += brain_at_risk;
                    brain_on_turn = 0;
                    brain_at_risk = 0;
                    shotgun = 0;
                    shotgun_total = 0;
                    footprint = 0;
                    for (i = 0; i < hand_index; i++)
                    {
                        free(hand[i].color);
                        free(hand[i].sides);
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
                    break;
                }
            }
        }
        else if (end == 1)
            while (1)
            {
                {
                    printf("PLAY AGAIN? (y/n): ");
                    int z = getchar();
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
                        free(hand[i].color);
                        free(hand[i].sides);
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