#include <stdio.h>
#include <stdlib.h>

#define PLAYER_ONE 'X'
#define PLAYER_TWO 'O'
#define NO_WINNER  'N'

#define CELL_BUSY 0xFE
#define INVALID_CELL 0xFF


char playground[3][3]= {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

void render_playground(void);
int get_player_input(void);
char judge(void);

int main()
{
    unsigned int num_of_empty_cells= 9;
    char winner;
    char current_player= PLAYER_ONE;
    int choice;
    int msg= 0;
    
    while(num_of_empty_cells != 0)
    {
        winner= judge();
        render_playground();
        if(msg == CELL_BUSY)
        {
            printf("The selected cell is already selected before. Please try another cell\n");
        }
        else if (msg == INVALID_CELL)
        {
            printf("The selected cell is invalid. Please try another cell number\n");
        }
        if (winner != NO_WINNER)
        {
            printf("%c has won the game !\n", winner);
            return 0;
        }
        msg = 0;
        choice = get_player_input();

        if ((choice == CELL_BUSY) || (choice == INVALID_CELL)) 
        {
            msg = choice;
        }
        else
        {
            int row= choice / 10 - 1;
            int col= choice % 10 - 1;
            playground[row][col]= current_player;
            if(current_player == PLAYER_ONE)
            {
                current_player= PLAYER_TWO;
            }
            else
            {
                current_player= PLAYER_ONE;
            }
            num_of_empty_cells--;
        }
    }

}

void render_playground(void)
{
    unsigned int index_i= 0;
    system("cls");
    printf("\n");
    for(index_i= 0; index_i < 3; index_i++)
    {
        printf("%c | %c | %c\n", playground[index_i][0], playground[index_i][1], playground[index_i][2]);
    }
}

int get_player_input(void)
{
    int choice;
    printf("Enter your input: ");
    scanf("%d", &choice);
    int row= choice / 10 - 1;
    int col= choice % 10 - 1;
    switch (choice)
    {
    case 11:
    case 12:
    case 13:
    case 21:
    case 22:
    case 23:
    case 31:
    case 32:
    case 33:
        if(playground[row][col] != ' ')
        {
            return CELL_BUSY;
        }
        break;
    default:
        return INVALID_CELL;
        break;

    }

    return choice;
}

char judge(void)
{
    unsigned int index_i= 0;

    if((playground[0][0] == playground[1][1]) && (playground[1][1] == playground[2][2]))
    {
        if(playground[0][0] != ' ')
        {
            return playground[0][0];
        }
    }

    if((playground[0][2] == playground[1][1]) && (playground[1][1] == playground[2][0]))
    {
        if(playground[1][1] != ' ')
        {
            return playground[1][1];
        }
    }

    for(index_i= 0; index_i < 3; index_i++)
    {
        if((playground[index_i][0] == playground[index_i][1]) && (playground[index_i][1] == playground[index_i][2]))
        {
            if(playground[index_i][0] != ' ')
            {
                return playground[index_i][0];
            }
        }

        if((playground[0][index_i] == playground[1][index_i]) && (playground[1][index_i] == playground[2][index_i]))
        {
            if(playground[0][index_i] != ' ')
            {
                return playground[0][index_i];
            }
        }

    }

    return NO_WINNER;
}