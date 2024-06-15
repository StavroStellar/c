#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>
#include <Windows.h>


#define MAX_X 15
#define MAX_Y 15
#define MIN_X 0
#define MIN_Y 0
#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4
#define RED FOREGROUND_RED
#define GREEN FOREGROUND_GREEN
#define BLUE FOREGROUND_BLUE
#define CYAN FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE
#define YELLOW FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
#define WHITE FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE


typedef struct drone_t
{
    char x;
    char y;
    char direction;
    char speed;
    char battery;
    char payload;
} drone_t;

typedef struct pumpkin_t
{
    char x;
    char y;
    char ripeness;
} pumpkin_t;

typedef struct cart_t
{
    char x;
    char y;
    char capacity;
    char pumpkins;
} cart_t;

int getRand()
{
    return rand() % MAX_X;
}

// Создание первого дрона
struct drone_t initDrone()
{
    srand(time(NULL));
    struct drone_t drone;
    drone.x = getRand();
    drone.y = getRand();
    drone.direction = LEFT;
    drone.speed = 1;
    drone.battery = 100;
    drone.payload = 0;
    return drone;
}

// Создание первой тыквы
struct pumpkin_t initPumpkin()
{
    srand(time(NULL));
    struct pumpkin_t pumpkin;
    pumpkin.x = getRand();
    pumpkin.y = getRand();
    pumpkin.ripeness = 0;
    return pumpkin;
}

// Создание первой тележки
struct cart_t initCart()
{
    srand(time(NULL));
    struct cart_t cart;
    cart.x = getRand();
    cart.y = getRand();
    cart.capacity = 10;
    cart.pumpkins = 0;
    return cart;
}

// Перекладывание тыквы на новое место. С учетом свободного места на карте.
pumpkin_t transferPumpkin(pumpkin_t pumpkin, drone_t drone, char matrix[MAX_X][MAX_Y])
{
    if (((drone.x == pumpkin.x) && (drone.y == pumpkin.y)) && (pumpkin.ripeness == 1))
    {
        while (matrix[(int)pumpkin.x][(int)pumpkin.y] != ' ')
        {
            pumpkin.x = getRand();
            pumpkin.y = getRand();
        }
        pumpkin.ripeness = 0;
    }

    return pumpkin;
}


// Обновление карты с появлением новых зрелых тыкв.
pumpkin_t updateMap(pumpkin_t pumpkin, char matrix[MAX_X][MAX_Y])
{
    srand(time(NULL));
    pumpkin.x = getRand();
    pumpkin.y = getRand();
    pumpkin.ripeness = 1;
    matrix[(int)pumpkin.x][(int)pumpkin.y] = 'P';


    return pumpkin;
}

// Проверка столкновения начала цепочки тележек с концом.
int checkCollision(cart_t cart, char matrix[MAX_X][MAX_Y])
{
     if (cart.x >= 0 && cart.x < MAX_X && cart.y >= 0 && cart.y < MAX_Y && matrix[(int)cart.x][(int)cart.y] == 'C')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Режим автопилота: искусственный интеллект управляет дроном по заданному маршруту.
drone_t autopilot(drone_t drone, pumpkin_t pumpkin, cart_t cart, char matrix[MAX_X][MAX_Y])
{
    // Реализация искусственного интеллекта для управления дроном.

    return drone;
}

// Кооперативный режим автопилота.
drone_t cooperativeAutopilot(drone_t drone1, drone_t drone2, pumpkin_t pumpkin, cart_t cart, char matrix[MAX_X][MAX_Y])
{
    // Реализация кооперативного искусственного интеллекта для управления несколькими дронами.

    return drone1;
}

// Функция заполнения матрицы для игры с ИИ
void fillMatrixAiGame(char matrix[MAX_X][MAX_Y], struct drone_t *drone1, struct drone_t *drone2, pumpkin_t pumpkin)
{
    for (int i = 0; i < MAX_X; i++)
    {
        for (int j = 0; j < MAX_Y; j++)
        {
            if (i == 0 || i == MAX_Y - 1)
            {
                matrix[j][i] = '-';
            }
            else if (j == 0 || j == MAX_X - 1)
            {
                matrix[j][i] = '|';
            }
            else
            {
                matrix[j][i] = ' ';
            }
        }
    }
    matrix[(int)drone1->x][(int)drone1->y] = '@';
    matrix[(int)drone2->x][(int)drone2->y] = '#';
    matrix[(int)pumpkin.x][(int)pumpkin.y] = 'o';
}

// Функция печати заполненой матрицы. Одиночная игра.
void printMatrixsingleMode(char matrix[MAX_X][MAX_Y], struct drone_t *drone, pumpkin_t pumpkin)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int j = 0; j < MAX_Y; j++)
    {
        for (int i = 0; i < MAX_X; i++)
        {
            if (j == pumpkin.y && i == pumpkin.x)
            {
                SetConsoleTextAttribute(hStdOut, GREEN);
                printf("%c", matrix[i][j]);
                SetConsoleTextAttribute(hStdOut, RESETDEV);
            }
            else if (j == drone->y && i == drone->x)
            {
                SetConsoleTextAttribute(hStdOut, WHITE);
                printf("%c", matrix[i][j]);
                SetConsoleTextAttribute(hStdOut, RESETDEV);
            }

            else
            {
                printf("%c", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

// Функция печати заполненой матрицы. Игра с ИИ.
void printMatrixAiGame(char matrix[MAX_X][MAX_Y], struct drone_t *drone1, struct drone_t *drone2, pumpkin_t pumpkin)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int j = 0; j < MAX_Y; j++)
    {
        for (int i = 0; i < MAX_X; i++)
        {
            if (j == pumpkin.y && i == pumpkin.x)
            {
                SetConsoleTextAttribute(hStdOut, GREEN);
                printf("%c", matrix[i][j]);
                SetConsoleTextAttribute(hStdOut, RESETDEV);
            }
            else if (j == drone1->y && i == drone1->x)
            {
                SetConsoleTextAttribute(hStdOut, WHITE);
                printf("%c", matrix[i][j]);
                SetConsoleTextAttribute(hStdOut, RESETDEV);
            }
            else if (j == drone2->y && i == drone2->x)
            {
                SetConsoleTextAttribute(hStdOut, WHITE);
                printf("%c", matrix[i][j]);
                SetConsoleTextAttribute(hStdOut, RESETDEV);
            }
            else
            {
                printf("%c", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

// Функция роста змейки при условии попадания на точку с едой.
// Удалена, так как в новой программе нет необходимости выращивать дронов.

int checkDirection(drone_t *drone, int key)
{
    if (key == LEFT)
    {
        if (drone->direction == RIGHT)
        {
            return 0;
        }
        else
        {
            drone->direction = LEFT;
        }
    }
    else if (key == UP)
    {
        if (drone->direction == DOWN)
        {
            return 0;
        }
        else
        {
            drone->direction = UP;
        }
    }
    else if (key == RIGHT)
    {
        if (drone->direction == LEFT)
        {
            return 0;
        }
        else
        {
            drone->direction = RIGHT;
        }
    }
    else if (key == DOWN)
    {
        if (drone->direction == UP)
        {
            return 0;
        }
        else
        {
            drone->direction = DOWN;
        }
    }
    return 1;
}



// Функция паузы.
void userPause()
{
    system("cls");
    for (int i = 0; i < MAX_X - 1; ++i)
    {
        if (i == 7)
        {
            printf("             PAUSE          \n");
        }
        printf("               \n");
    }
    printf("To return to the game, press <p>\n");
    char pch;
    while (1)
    {
        if ((pch = getch()) == 'p')
        {
            break;
        }
    }
}

// Обработка нажатия клавиши
int keyProcessing(drone_t drone)
{
    char ch = getch();
    fflush(stdin);
    if (ch == 'w' || ch == 'W')
    {
        if (checkDirection(&drone, UP))
        {
            return UP;
        }
        else
            return drone.direction;
    }
    if (ch == 's' || ch == 'S')
    {
        if (checkDirection(&drone, DOWN))
        {
            return DOWN;
        }
        else
            return drone.direction;
    }
    if (ch == 'a' || ch == 'A')
    {
        if (checkDirection(&drone, LEFT))
        {
            return LEFT;
        }
        else
            return drone.direction;
    }
    if (ch == 'd' || ch == 'D')
    {
        if (checkDirection(&drone, RIGHT))
        {
            return RIGHT;
        }
        else
            return drone.direction;
    }
    if (ch == 'p' || ch == 'P')
    {
        userPause();
        return drone.direction;
    }
    if (ch == 'q' || ch == 'Q')
    {
        exit(0);
    }
    return drone.direction;
}
// Функция движения дрона
void moveDrone(drone_t *drone, int key)
{
    if (checkDirection(drone, key))
    {
        if (drone->direction == LEFT)
        {
            drone->x -= drone->speed;
        }
        else if (drone->direction == UP)
        {
            drone->y -= drone->speed;
        }
        else if (drone->direction == RIGHT)
        {
            drone->x += drone->speed;
        }
        else if (drone->direction == DOWN)
        {
            drone->y += drone->speed;
        }
    }
}



// Функция печати информации
void printLevel(int level)
{
    if (level <= 19)
    {
        printf("Level : %d    Speed : %d%% \n", level, 5 + 5 * level);
    }
    else
    {
        printf("Level : %d    Max Speed\n", level);
    }
    printf("Control : <w> <a> <s> <d>\n");
    printf("Pause : <p>    Exit : <q>\n");
}

// Функция увеличения скорости
int speedBoost(int level)
{
    if (level <= 20)
    {
        return 1000 - 50 * level;
    }
    else
    {
        return 1;
    }
}

void autoChangeDirection(drone_t *drone, pumpkin_t pumpkin)
{

    if ((drone->direction == RIGHT || drone->direction == LEFT) && (drone->y != pumpkin.y)) // горизонтальное движение
    {
        drone->direction = (pumpkin.y > drone->y) ? DOWN : UP;
    }
    else if ((drone->direction == DOWN || drone->direction == UP) && (drone->x != pumpkin.x)) // вертикальное движение
    {
        drone->direction = (pumpkin.x > drone->x) ? RIGHT : LEFT;
    }
}



void singleMode()
{
    char matrix[MAX_X][MAX_Y];
    drone_t drone1 = initDrone();
    drone_t drone2 = initDrone();
    pumpkin_t pumpkin = initPumpkin();
    int level = 1;

    fillMatrixAiGame(matrix, &drone1, &drone2, pumpkin);
    printMatrixAiGame(matrix, &drone1, &drone2, pumpkin);
    printLevel(level);
    int key = LEFT;
    while (1)
    {
        clock_t begin = clock();
        if (kbhit())
        {
            key = keyProcessing(drone1);
        }
        
        moveDrone(&drone1, key);
        autoChangeDirection(&drone2, pumpkin);
        moveDrone(&drone2, drone2.direction);

        pumpkin = transferPumpkin(pumpkin, drone1, matrix);
        Sleep(speedBoost(level));
        fillMatrixAiGame(matrix, &drone1, &drone2, pumpkin);
        system("cls");
        printMatrixAiGame(matrix, &drone1, &drone2, pumpkin);
        printLevel(level);
    }
}
char startMenu()
{
    printf("     PUMPKIN     \n");
    printf("Mode selection \n");
    printf("1 - Single mode \n");
    printf("Enter your choice : \n");
    char sch;

    while (1)
    {
        if (((sch = getch()) == '1') || ((sch = getch()) == '2'))
        {
            break;
        }
        else
        {
            printf("Enter the number of the mode (1 or 2)\n");
        }
    }
    return sch;
}

int main()
{
    char startChoice = startMenu();
    switch (startChoice)
    {
    default:
		singleMode();
    }

    return 0;
}

