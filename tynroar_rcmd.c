#include <string.h>

#include "raylib.h"
#include "tynroar_lib.h"

typedef enum { MODE_INITIAL, MODE_CONSOLE } MODE;

#define CONSOLE_HEIGHT          10
#define CONSOLE_LINE_HEIGHT     20
#define CONSOLE_MAX_CHARS       20
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    bool inputonce = true;
    MODE mode = MODE_INITIAL;
    char inputstring[CONSOLE_MAX_CHARS + 1] = "\0";
    char inputcommand[CONSOLE_MAX_CHARS + 1] = "\0";
    int inputlength = 0;
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        bool inputed = false;
       
        if (isAnyKeyPressed(1, KEY_TAB))
        {
          inputed = true;
        }
        else
        {
          inputonce = true;
        }
        
        if (inputonce)
        {
            if (IsKeyDown(KEY_TAB))
            {
                mode = mode == MODE_INITIAL ? MODE_CONSOLE : MODE_INITIAL;
            }
        }
        
        if (inputed)
        {
          inputonce = false;
        }
        
        if (mode == MODE_CONSOLE) {
            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (inputlength < CONSOLE_MAX_CHARS))
                {
                    inputstring[inputlength] = (char)key;
                    inputstring[inputlength+1] = '\0'; // Add null terminator at the end of the string.
                    inputlength++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                inputlength--;
                if (inputlength < 0) inputlength = 0;
                inputstring[inputlength] = '\0';
            }
            
            if (IsKeyPressed(KEY_ENTER)) {
                strcpy(inputcommand, inputstring);
                inputstring[0] = '\0';
                inputlength = 0;
            }
        }
       
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText(
                TextFormat("MODE: %s", mode == MODE_INITIAL ? "initial" : "console"), 
                190, 200, 20, LIGHTGRAY
            );
            DrawText(
                TextFormat("command: %s", inputcommand), 
                190, 240, 20, LIGHTGRAY
            );
            
            if (mode == MODE_CONSOLE) {
                DrawRectangle(
                    1, 1, 
                    GetScreenWidth() - 2, CONSOLE_LINE_HEIGHT * CONSOLE_HEIGHT, 
                    GRAY
                );
                DrawRectangleLines(
                    1, 1 + CONSOLE_LINE_HEIGHT * (CONSOLE_HEIGHT - 1), 
                    GetScreenWidth() - 2, CONSOLE_LINE_HEIGHT, 
                    GREEN
                );
                DrawText(
                    TextFormat("> %s", inputstring), 
                    5, CONSOLE_LINE_HEIGHT * (CONSOLE_HEIGHT - 1) + 2, 
                    CONSOLE_LINE_HEIGHT, WHITE
                );
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}