#include "mines.h"


void check_game_status(game_state * game_ptr)
{
    uint8_t flags_count = 0;
    uint8_t clicks_count = 0;
    for(uint8_t i = 0; i < SIDES; i++)
    {
        for (uint8_t j = 0; j < SIDES; j++)
        {
            if(game_ptr->field[i][j] == -1  && game_ptr->clicked[i][j] == 1)
            {
                game_ptr->status = LOSS;
                // printf("Game Loss\n");
                break;
            }
            else if (game_ptr->clicked[i][j] == 2)
            {
                flags_count++;
            }
            else if (game_ptr->clicked[i][j] == 1)
            {
                clicks_count++;
            }
        }
    }
    if (flags_count == TOTAL_BOMBS && clicks_count == ((SIDES*SIDES)-TOTAL_BOMBS))
    {
        // printf("Game Won\n");
        game_ptr->status = WIN;
    }
}

void draw_field(game_state * game_ptr)
{
    uint8_t offset = 2;
    uint16_t width = GetScreenWidth();
    uint16_t height = GetScreenHeight();
    uint16_t box_size_x = (width/SIDES);
    uint16_t box_size_y = (height/SIDES);

    for(uint8_t i = 0; i < SIDES; i++)
    {
        for (uint8_t j = 0; j < SIDES; j++)
        {
            uint16_t rect_row_pos = (j*box_size_x)+offset;
            uint16_t rect_col_pos = (i*box_size_y)+offset;
            uint16_t text_row_pos = (j*box_size_x)+(box_size_x*0.25);
            uint16_t text_col_pos = (i*box_size_y)+(box_size_y*0.1);

            DrawRectangle(rect_row_pos, rect_col_pos, box_size_x-offset, box_size_y-offset, BLACK);

            if (game_ptr->clicked[i][j] == 2)
            {
                DrawText("F",text_row_pos,text_col_pos, (box_size_x < box_size_y?box_size_x:box_size_y)-(offset*10),RED);
            }
            else if(game_ptr->field[i][j] == -1)
            {
                DrawText("*",text_row_pos,text_col_pos, (box_size_x < box_size_y?box_size_x:box_size_y)-(offset*10),game_ptr->clicked[i][j]?RED:BLACK);
            }
            else
            {
            DrawText(TextFormat("%d",game_ptr->field[i][j]),text_row_pos,text_col_pos, (box_size_x < box_size_y?box_size_x:box_size_y)-(offset*10),game_ptr->clicked[i][j]?GREEN:BLACK);
            }
        }
    }
}

void open_all_zeros(game_state * game_ptr, int8_t row, int8_t col)
{
    if (row < 0 || row > SIDES-1 || col < 0 || col > SIDES-1 || game_ptr->field[row][col] == -1 || game_ptr->clicked[row][col])
    {
        return;
    }
    else if (game_ptr->field[row][col] >  0)
    {
        game_ptr->clicked[row][col] = 1;
        return;
    }
    
    game_ptr->clicked[row][col] = 1;
    
    open_all_zeros(game_ptr, row-1, col);
    open_all_zeros(game_ptr, row-1, col-1);
    open_all_zeros(game_ptr, row-1, col+1);  
    open_all_zeros(game_ptr, row+1, col+1);
    open_all_zeros(game_ptr, row+1, col);
    open_all_zeros(game_ptr, row+1, col-1);
    open_all_zeros(game_ptr, row, col-1);
    open_all_zeros(game_ptr, row, col+1);
}

void _insert_hint(game_state * game_ptr)
{
    for(uint8_t i = 0; i < SIDES; i++)
    {
        for (uint8_t j = 0; j < SIDES; j++)
        {
            if (game_ptr->field[i][j] == -1)continue;
            uint8_t count = 0;
            if (i+1 < SIDES) 
            {
                if(game_ptr->field[i+1][j] == -1)
                {
                    count++;
                }
                if((j+1 < SIDES) && (game_ptr->field[i+1][j+1] == -1))
                {
                    count++;
                }
                if((j-1 >= 0) && (game_ptr->field[i+1][j-1] == -1))
                {
                    count++;
                }
            }
            if (i-1 >= 0)
            {
                if (game_ptr->field[i-1][j] == -1)
                {
                    count++;
                }
                if((j-1 >= 0) && (game_ptr->field[i-1][j-1] == -1))
                {
                    count++;
                }
                if((j+1 < SIDES) && (game_ptr->field[i-1][j+1] == -1))
                {
                    count++;
                }
            }
            if ((j+1 < SIDES) && (game_ptr->field[i][j+1] == -1))
            {
                count++;
            }
            if ((j-1 >= 0) && (game_ptr->field[i][j-1] == -1))
            {
                count++;
            }
            game_ptr->field[i][j] = count;
        }
    }
}

void _insert_field(game_state * game_ptr)
{
    uint8_t bombs_placed = 0;
    for(uint8_t i = 0; i < SIDES; i++)
    {
        for (uint8_t j = 0; j < SIDES; j++)
        {
            uint8_t value = rand() % (TOTAL_BOMBS/2);
            if (!value) 
            {
                if (bombs_placed < TOTAL_BOMBS)
                {
                    bombs_placed++;
                    game_ptr->field[i][j] = -1;
                }
                else
                {
                    game_ptr->field[i][j] = 0;
                }
            }
            else if ((TOTAL_BOMBS-bombs_placed) == ((SIDES*SIDES)-((i*SIDES)+j)))
            {
                
                if (bombs_placed < TOTAL_BOMBS)
                {
                    bombs_placed++;
                    game_ptr->field[i][j] = -1;
                }
                else
                {
                    game_ptr->field[i][j] = 0;
                }
            }
            else
            {
                game_ptr->field[i][j] = 0;
            }   
        }
    }
}

void _init_clicks(game_state * game_ptr)
{
    for(uint8_t i = 0; i < SIDES; i++)
    {
        for (uint8_t j = 0; j < SIDES; j++)
        {
            game_ptr->clicked[i][j] = 0;
        }
    }
}

void init_game(game_state * game_ptr)
{
    game_ptr->status = LOADING;
    _insert_field(game_ptr);
    _insert_hint(game_ptr);
    _init_clicks(game_ptr);
}

//For debug only
void print_field(int8_t field[][SIDES])
{
    for(uint8_t i = 0; i < SIDES; i++)
    {
        for (uint8_t j = 0; j < SIDES; j++)
        {
            if(field[i][j] == -1)
            {
                printf("X ");
            }
            else
            {
                printf("%d ",field[i][j]);
            }
        }
        printf("\n");
    }
}
