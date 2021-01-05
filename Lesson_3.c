#include <stdio.h>
#include <math.h>

#define MAX_BOARD_SIZE_X 8
#define MAX_BOARD_SIZE_Y 8
//----------funcs for binary counter-------------//
void binary(int num, int *res){
    if (num <= 0)
        return;
    binary(num / 2, res);
    if (num % 2 == 0)
        *(res + get_binary_lenght(num)) = 0;
    else
        *(res + get_binary_lenght(num)) = 1;
}

void show_binary(int num, int *arr, int min_lengh){
    int lengh = get_binary_lenght(num);
    if (lengh < min_lengh){
        for (int i = 0; i < min_lengh - lengh; i ++)
            printf("0 ");
    }
    for (int i = 1; i <= lengh; i++){
        printf("%d ",*(arr + i));
    }
    printf("\n");
}

int get_binary_lenght(int num)
    {
        int lengh = log(num) / log(2); // essentially log num to base of 2 rounded to integer;
        if (pow (2, lengh) <= num)
            lengh++;
        return lengh;
    }
//----------funcs for pow-------------//
int recure_pow(int num, int pow)
{
    if (pow == 1)
        return num;
    return recure_pow(num, pow -1) * num;
}

int recure_fast_pow(int num, int pow) {
    if (pow <= 0)
        return 1;
    if (pow % 2 == 0)
        return recure_fast_pow(num * num, pow / 2);
    else
        return num * recure_fast_pow(num, pow - 1);
}
//----------funcs for King-------------//
    int X = 5;
    int Y = 5;
    int board_template[MAX_BOARD_SIZE_Y][MAX_BOARD_SIZE_X] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    };
    int board[MAX_BOARD_SIZE_Y][MAX_BOARD_SIZE_X];

int routes(int x, int y, int used_moves[][2], int last_id){

    for (int i = 0; i < last_id; i++)
        if (used_moves[i][0] == x &&
            used_moves[i][1] == y )
            return 0;

    if ((board[x][y] == 1) ||
        x > X || y > Y || x < 0 || y < 0)
        return 0;
    else if (x == 0 && y == 0)
    {
        printf("Found the path:\n");
        print_succ_path(used_moves, last_id);
        return 1;
    }
    else
    {
        //printf("%d %d\n", x, y);
        used_moves[last_id][0] = x;
        used_moves[last_id][1] = y;
        last_id++;
        int ret =   routes(x, y - 1, used_moves, last_id) +
                    routes(x - 1, y, used_moves, last_id) +
                    routes(x + 1, y, used_moves, last_id) +
                    routes(x, y + 1, used_moves, last_id);
        return ret;
    }
}
void print_board(){
    for (int x = 0; x <= X; x++)
    {
        for ( int y = 0; y <= Y; y++)
            printf("%2d ",board[x][y]);
        printf("\n\n");
    }
    printf("---------------\n");
}
void print_succ_path(int used_path[][2], int last_id)
{
    clear_board();
    for (int i = 0; i < last_id; i++){
        board[used_path[i][0]][used_path[i][1]] = 2 + i;
    }
    board[0][0] = last_id + 2;
    print_board();
    clear_board();

}
void clear_board(){
    for (int i = 0; i < MAX_BOARD_SIZE_Y; i++)
        for (int t = 0; t < MAX_BOARD_SIZE_X; t++)
            board[i][t] = board_template[i][t];
}


int main(){

//------------------------------Part 1------------------------------//
    printf("1. Реализовать функцию перевода чисел из десятичной...\n");
    printf("\nDemontration, counting 1 to 10 in binary:\n");
    static int *binary_store[255];
    int arr_ind = 0;
    for (int i = 1; i < 11; i++)
    {
        int lengh = get_binary_lenght(i);
        binary(i, (binary_store + arr_ind));
        printf("%2d: ",i);
        show_binary(i, (binary_store + arr_ind), 6);
        arr_ind += lengh + 1;
    }
    int test;
    while (1){
        if (arr_ind > 240)
        {
            for (int i = 1; i < 255; i++)
                *(binary_store + i) = 0;
            arr_ind = 0;
        }

        printf("You may enter an integer to test the function. Enter -1 to exit.\n");
        scanf("%d", &test);
        if (test == -1)
            break;
        else if (test < 0)
            printf("Error. Entered negative number.\n");
        else {
            binary(test, (binary_store + arr_ind));
            show_binary(test, (binary_store + arr_ind), -1);
            arr_ind += get_binary_lenght(test) + 1;
        }
    }

//-------------------------Part 2---------------------------------//
    printf("2. Реализовать функцию возведения числа [a] в степень [b]...\n");
    printf("Demontration. Powing 2 up to 10th degree by both functions:\n");
    for (int i = 1; i < 11; i++){
        printf("%2d: %4d    %4d\n",i, recure_pow(2,i), recure_fast_pow(2,i));
    }
    while (1){
        printf("You may enter an integer and pow to test the function. Enter -1 to exit.\n");
        scanf("%d", &test);
        if (test == -1)
            break;
        scanf("%d", &arr_ind);
        if (arr_ind < 0)
            printf("Error. Entered negative pow.\n");
        else {
            printf("Result is: %d   %d\n",recure_pow(test, arr_ind),recure_fast_pow(test, arr_ind));
        }
    }

//-----------------------------Part 3----------------------------------//

    printf("\n3. Реализовать нахождение количества маршрутов шахматного короля...\n");
    printf("\nDemonstration. Path-finding with obstacles on 5x5 map:\n");
    printf("\nLegend:\n0 - free space\n1 - obstacle\nother - found path\nroutes calculated from bottom-right corner to the top-left corner\n\n");
    clear_board();
    int arr[255][2];
    X = 4;
    Y = 4;
    printf("\nStarting board:\n");
    print_board();
    printf("Total routes: %d\n",routes(X, Y, arr,0));
    clear_board();
    printf("You may edit 'board_template' global variable to make another map and\nchange 'X' and 'Y' variables in 'main' to change map boards\n");
}
