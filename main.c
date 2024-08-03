#include "mines.h"
#define RAYGUI_IMPLEMENTATION
#include "../raylib/raygui.h"

int main(void)
{
    srand(time(NULL));
    game_state game = {0};
    uint8_t showMessageBox = false;
    uint8_t frames = 0;
    init_game(&game);
    InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"Minesweeper Revived");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    // print_field(game.field);
    while(!WindowShouldClose())
    {
        uint16_t width = GetScreenWidth();
        uint16_t height = GetScreenHeight();
        if (game.status != LOSS && game.status != WIN )
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                Vector2 mousePosition = GetMousePosition();
                // printf("%0.3f,%0.3f\n",mousePosition.x, mousePosition.y);
                uint16_t box_size_x = (width/SIDES);
                uint16_t box_size_y = (height/SIDES);
                uint8_t row = mousePosition.y/box_size_y;
                uint8_t col = mousePosition.x/box_size_x;
                // printf("%d,%d,%d\n",row,col,game.field[row][col]);
                if (!game.clicked[row][col])
                {
                    if (game.field[row][col] == 0)
                    {
                        open_all_zeros(&game, row, col);
                    }
                    else
                    {
                        game.clicked[row][col] = 1;
                    }
                }
                check_game_status(&game);    
            }
            else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            {
                Vector2 mousePosition = GetMousePosition();
                // printf("%0.3f,%0.3f\n",mousePosition.x, mousePosition.y);
                uint16_t box_size_x = (width/SIDES);
                uint16_t box_size_y = (height/SIDES);
                uint8_t row = mousePosition.y/box_size_y;
                uint8_t col = mousePosition.x/box_size_x;
                // printf("%d,%d,%d\n",row,col,game.field[row][col]);
                if (!game.clicked[row][col])
                { 
                    game.clicked[row][col] = 2;
                }
                else if (game.clicked[row][col] == 2)
                {
                    game.clicked[row][col] = 0;
                }
                check_game_status(&game);    
            }
        }

        BeginDrawing();
            if (frames <= 1 || (game.status != LOSS && game.status != WIN) )
            {
                ClearBackground(RAYWHITE);
                draw_field(&game);
                if (game.status == LOSS && frames++) showMessageBox = true;
                else if (game.status == WIN && frames++) showMessageBox = true;
            } 
            else
            {
                if (showMessageBox) 
                {
                    char * text = game.status == WIN ? "Congratulations! You Won!":"Game Over! Try again!";
                    int8_t result = GuiMessageBox((Rectangle){ width/3, height/3, 250, 100 },
                    "#191#Minesweeper Revived", text, "Retry;Exit");

                    if (result == 2) break;
                    if (result == 0)
                    { 
                        showMessageBox = false;
                    }
                    else if (result == 1)
                    {
                        frames = 0;
                        init_game(&game);
                        showMessageBox = false;
                    }

                }
                else
                {
                    ClearBackground(RAYWHITE);
                    draw_field(&game);
                }
            }
            
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

