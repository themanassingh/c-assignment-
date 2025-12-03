#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void clear_screen_fast() {
    system("cls");
}

int main() {
    srand(time(0));

    printf("SHOOTER GAME\n");
    printf("-----------------------\n");
    printf("Press any key to start\n");
    _getch();

    int x, score, step;
    int obstacleCount, obstacles[2];
    char obstacleChar = '*';
    char playerChar = 'A';
    int speed;

start_game:
    x = 1;
    score = 0;
    step = 0;
    speed = 120;

    obstacleCount = (rand() % 2) + 1;
    for (int i = 0; i < obstacleCount; i++)
        obstacles[i] = rand() % 3;

    while (1) {
        if (_kbhit()) {
            char key = _getch();
            if (key == 0 || key == 224)
                key = _getch();

            if (key == 75 && x > 0) x--;
            if (key == 77 && x < 2) x++;
        }

        clear_screen_fast();
        printf("SHOOTER GAME SCORE: %d\n", score);
        printf("-------------------------------\n");

        for (int i = 0; i < 10; i++) {
            if (i == step) {
                char lane[3] = {' ', ' ', ' '};
                for (int j = 0; j < obstacleCount; j++)
                    lane[obstacles[j]] = obstacleChar;
                printf("|  %c    %c    %c  |\n", lane[0], lane[1], lane[2]);
            } else {
                printf("|                 |\n");
            }
        }

        if (x == 0)
            printf("|  %c              |\n", playerChar);
        else if (x == 1)
            printf("|       %c         |\n", playerChar);
        else
            printf("|             %c   |\n", playerChar);

        if (step == 10) {
            int hit = 0;
            for (int i = 0; i < obstacleCount; i++)
                if (x == obstacles[i])
                    hit = 1;

            if (hit) {
                printf("\nGAME OVER!\nPress R to restart or Q to quit\n");
                while (1) {
                    if (_kbhit()) {
                        char c = _getch();
                        if (c == 'r' || c == 'R') goto start_game;
                        if (c == 'q' || c == 'Q') return 0;
                    }
                }
            }
        }

        Sleep(speed);
        step++;

        if (step > 10) {
            score++;
            step = 0;

            obstacleCount = (rand() % 2) + 1;
            for (int i = 0; i < obstacleCount; i++)
                obstacles[i] = rand() % 3;

            if (speed > 40)
                speed -= 2;
        }
    }

    return 0;
}
