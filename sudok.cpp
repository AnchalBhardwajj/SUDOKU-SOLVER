#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int x = 0, y = 0, z = 0;
int sudoku[9][9] = {
    {4, 3, 1, 6, 7, 9, 5, 2, 8},
    {9, 6, 7, 2, 5, 8, 3, 4, 1},
    {5, 8, 2, 1, 4, 3, 9, 6, 7},
    {6, 5, 9, 8, 1, 7, 2, 3, 4},
    {3, 2, 8, 5, 6, 4, 1, 7, 9},
    {7, 1, 4, 9, 3, 2, 8, 5, 6},
    {8, 7, 3, 4, 2, 1, 6, 9, 5},
    {1, 4, 5, 3, 9, 6, 7, 8, 2},
    {2, 9, 6, 7, 8, 5, 4, 1, 1}};

/*Returns the current time in seconds*/
double get_time()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec + now.tv_nsec * 1e-9;
}

//Checking values in a row/
void *checkRows(void *param)
{
    for (int i = 0; i < 9; i++)
    {
        int visited[9] = {0};
        for (int j = 0; j < 9; j++)
        {
            if (visited[sudoku[i][j] - 1] == 1) // Number j occurs more than once in a row
            {
                x = 1;
                break;
            }
            else
            {
                visited[sudoku[i][j] - 1] = 1;
            }
        }
        if (x == 1)
        {
            break;
        }
    }
    // sleep(5) ;
    return NULL;
}

//Checking values in a column/
void *checkColumns(void *param)
{
    for (int j = 0; j < 9; j++)
    {
        int visited[9] = {0};
        for (int i = 0; i < 9; i++)
        {
            if (visited[sudoku[i][j] - 1] == 1) // Number j occurs more than once in a column
            {
                y = 1;
                break;
            }
            else
            {
                visited[sudoku[i][j] - 1] = 1;
            }
        }
        if (y == 1)
        {
            break;
        }
    }
    // sleep(5) ;
    return NULL;
}

void *checkSubGrids(void *param)
{
    for (int i = 0; i < 9; i += 3)//tra_r
    {
        for (int j = 0; j < 9; j += 3)//tr_c
        {
            int visited[9] = {0};//keep track of visited 
            for (int k = i; k < i + 3; k++)//iter_cell -subgrid
            {
                for (int l = j; l < j + 3; l++)//iter_cell -subgrid
                {
                    if (visited[sudoku[k][l] - 1] == 1) // Number j occurs more than once in a submatrix
                    {
                        z = 1;
                        break;
                    }
                    else
                    {
                        visited[sudoku[k][l] - 1] = 1;
                    }
                }
                if (z == 1)
                {
                    break;
                }
            }
            if (z == 1)
            {
                break;
            }
        }
        if (z == 1)
        {
            break;
        }
    }
    // sleep(5) ;
    return NULL;
}

int main()
{
    double time = get_time();
    pthread_t tid1, tid2, tid3;

    //Creating three threads for checking three conditions/
    pthread_create(&tid1, NULL, checkRows, NULL);
    pthread_create(&tid2, NULL, checkColumns, NULL);
    pthread_create(&tid3, NULL, checkSubGrids, NULL);

    //Waiting for the threads to complete/
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    if (x == 1 || y == 1 || z == 1) // If any of the conditions are violated
    {
        printf("Invalid solution. Please try again.\n");
    }
    else
    {
        printf("The given solution is valid.\n");
    }

    printf("time taken: %.6lf seconds\n", get_time() - time);
    return 0;
}
