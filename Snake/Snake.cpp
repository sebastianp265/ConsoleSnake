#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void set_cursor_to_left_top_corner() {
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void print_map(int width, int height, int snake_positions_x[], int snake_positions_y[], int snake_length) {
    set_cursor_to_left_top_corner();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            bool is_snake_on_xy = false;
            for (int i = 0; i < snake_length; i++) {
                if (snake_positions_x[i] == x && snake_positions_y[i] == y) {
                    is_snake_on_xy = true;
                    cout << "\033[42m"; // ustalenie koloru tla na zielony
                    break;
                }
            }
            
            if (!is_snake_on_xy) {
                if (y == 0 || x == 0 || y == height - 1 || x == width - 1) {
                    cout << "\033[43m"; // ustawienie koloru tła na żółty
                }
                else {
                    cout << "\033[0m"; // reset koloru
                }
            }
            cout << "  ";
        }
        cout << endl;
    }
}

void hide_cursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

int main()
{
    hide_cursor();

    const int map_height = 20;
    const int map_width = 20;

    int snake_length = 3;

    int snake_positions_x[map_width * map_height];
    int snake_positions_y[map_width * map_height];

    snake_positions_x[0] = 10;
    snake_positions_y[0] = 10;

    snake_positions_x[1] = 10;
    snake_positions_y[1] = 10;

    snake_positions_x[2] = 10;
    snake_positions_y[2] = 10;

    int snake_speed_x = 0;
    int snake_speed_y = 0;

    while (true) {
        if (_kbhit()) {
            char pressed_key = _getch();
            if (pressed_key == 'w') {
                snake_speed_y = -1;
                snake_speed_x = 0;
            }
            else if (pressed_key == 's') {
                snake_speed_y = 1;
                snake_speed_x = 0; 
            }
            else if (pressed_key == 'a') {
                snake_speed_x = -1;
                snake_speed_y = 0;
            }
            else if (pressed_key == 'd') {
                snake_speed_x = 1;
                snake_speed_y = 0;
            }
        }

        for (int i = snake_length - 1; i >= 1; i--) {
            snake_positions_x[i] = snake_positions_x[i - 1];
            snake_positions_y[i] = snake_positions_y[i - 1];
        }

        snake_positions_x[0] += snake_speed_x;
        snake_positions_y[0] += snake_speed_y;

        print_map(map_width, map_height, snake_positions_x, snake_positions_y, snake_length);

        if (snake_positions_x[0] == 0 || snake_positions_x[0] == map_width - 1 || snake_positions_y[0] == 0 || snake_positions_y[0] == map_height - 1) {
            cout << "\033[0m" << "\033[31m" << "You lost! Try again!";

            break;
        }
        Sleep(100);
    }

    cout << "\033[0m"; // reset koloru

    return 0;
}