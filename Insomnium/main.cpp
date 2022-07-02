
#include <iostream>
#include <string>
#include "raylib.h"

typedef enum GameScreen { TITLE, ROOM_1, ROOM_2, ROOM_3, ENDING } GameScreen;

int main(void)
{
    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sample Text 279");

    GameScreen currentScreen = TITLE;

    Vector2 personPosition = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };
    Vector2 personSize = { 100.0f, 200.0f };

    Vector2 transitionToRoom1 = { 50.0f, 200.0f };
    Vector2 transitionToRoom2 = { 50.0f, 200.0f };
    Vector2 transitionToRoom3 = { 50.0f, 200.0f };


    int xPos = personPosition.x;
    int yPos = personPosition.y;


    SetTargetFPS(100);

    //Main Game Loop
    while (!WindowShouldClose())
    {

        // Screen switching mechanic
        // I will change the conditions to colliding with like a door later

        switch (currentScreen)
        {
        case TITLE:
        {
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            {
                personPosition = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };

                currentScreen = ROOM_1;
            }
        }
        break;
        case ROOM_1:
        {
            if (personPosition.y <= 0)
            {
                personPosition = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };

                currentScreen = ROOM_2;
            }
            else if (personPosition.y >= (1080 - personSize.y))
            {
                personPosition = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };

                currentScreen = ROOM_3;
            }

            else if (personPosition.x < 100 || personPosition.x >(1920 - 100 - personSize.x))
            {
                DrawText("There is nothing here...", ((7 * SCREEN_HEIGHT) / 8), (SCREEN_WIDTH / 2), 64, DARKGREEN);
            }
        }
        break;
        case ROOM_2:
        {
            if (personPosition.y >= (1080 - personSize.y))
            {
                personPosition = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };

                currentScreen = ROOM_1;
            }
            else if(personPosition.x < 100  || personPosition.y < 100 || personPosition.x > (1920 - 100 - personSize.x))
            {
                DrawText("There is nothing here...", ((7 * SCREEN_HEIGHT) / 8), (SCREEN_WIDTH / 2), 64, DARKGREEN);
            }

        }
        break;
        case ROOM_3:
        {
            if (personPosition.y <= 0)
            {
                personPosition = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };

                currentScreen = ROOM_1;
                
            }

            else if (personPosition.y >= (1080 - personPosition.y))
            {
                currentScreen = ENDING;
            }

            else if (personPosition.x < 100 || personPosition.x > (1920 - 100 - personSize.x))
            {
                DrawText("There is nothing here...", ((7 * SCREEN_HEIGHT) / 8), (SCREEN_WIDTH / 2), 64, DARKGREEN);
            }
        }
        break;
        case ENDING:
        {
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            {
                currentScreen = TITLE;
                
            }
        }
        break;

        default:
            break;

        }


        if (IsKeyDown(KEY_RIGHT)) personPosition.x += 3.0f;
        if (IsKeyDown(KEY_LEFT)) personPosition.x -= 3.0f;
        if (IsKeyDown(KEY_UP)) personPosition.y -= 3.0f;
        if (IsKeyDown(KEY_DOWN)) personPosition.y += 3.0f;


        //----------------------------------------------------------------------------------
        // Draw
        // ----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);

        // Actually loads the contents of the screen
        // Later I will have to add a way to store data so that it doesn't always reset upon reentering the room

        switch(currentScreen)
        {
        case TITLE:
        {
            // TODO: Draw LOGO screen here!
            DrawText("TITLE SCREEN", 20, 20, 40, GREEN);
            DrawText("Press Enter to Start", 20, 60, 40, GREEN);

        } break;
        case ROOM_1:
        {
            // TODO: Draw TITLE screen here!
            
            DrawText("ROOM 1", 20, 20, 40, GRAY);
            DrawRectangleV(personPosition, personSize, WHITE);

        } break;
        case ROOM_2:
        {
            // TODO: Draw GAMEPLAY screen here!

            DrawText("ROOM 2", 20, 20, 40, WHITE);
            DrawRectangleV(personPosition, personSize, BLUE);

        } break;
        case ROOM_3:
        {
            // TODO: Draw GAMEPLAY screen here!

            DrawText("ROOM 3", 20, 20, 40, BLUE);
            DrawRectangleV(personPosition, personSize, RED);

        } break;
        case ENDING:
        {
            // TODO: Draw ENDING screen here!

            DrawText("ENDING SCREEN", 20, 20, 40, RED);

        } break;
        default: break;
        }


        // Player Collision against the borders of the window

        // Y position
        if (personPosition.y <= 0)
        {
            personPosition.y = 0;
        }
        else if (personPosition.y >= (1080 - personSize.y))
        {
            personPosition.y = (1080 - personSize.y);
        }

        // X Position
        if (personPosition.x <= 0)
        {
            personPosition.x = 0;
        }
        else if (personPosition.x >= (1920 - personSize.x))
        {
            personPosition.x = (1920 - personSize.x);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
        // End Draw
        // ----------------------------------------------------------------------------------

    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;

}

