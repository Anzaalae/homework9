#include <stdio.h>
#include <malloc.h>
#include <time.h>

void free_matrix(int **matrix, int row)
{
    for(int i= 0; i< row; i++)
    {// 각 행에 대해 먼저 메모리 할당 해제 후 이중 포인터 메모리 할당 해제
        free(matrix[i]);
    }
    free(matrix);
}

void print_matrix(int **matrix, int row, int col)
{ // 행렬의 행과 열을 이용해 이중 반복문을 통해 행렬을 출력
    for(int i= 0; i< row; i++)
    { // 각 행에 대한 반복
        for(int j= 0; j< col; j++)
        { // 각 열에 대한 반복
            printf("%-10d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void addition_matrix(int **output, int **matrixA, int **matrixB, int row, int col)
{ // 각 행렬의 행과 열을 이용해 이중 반복문을 통해 행렬 덧셈 수행
    for(int i= 0; i< row; i++)
    { // 각 행에 대한 반복
        for(int j= 0; j< col; j++)
        { // 각 열에 대한 반복
            output[i][j]= matrixA[i][j]+ matrixB[i][j];
        }
    }

    print_matrix(output, row, col);
    free_matrix(output, row);
}

void subtraction_matrix(int **output, int **matrixA, int **matrixB, int row, int col)
{ // 각 행렬의 행과 열을 이용해 이중 반복문을 통해 행렬 덧셈 수행
    for(int i= 0; i< row; i++)
    { // 각 행에 대한 반복
        for(int j= 0; j< col; j++)
        { // 각 열에 대한 반복
            output[i][j]= matrixA[i][j]- matrixB[i][j];
        }
    }

    print_matrix(output, row, col);
    free_matrix(output, row);
}

void transpose_matrix(int **output, int **matrix, int row, int col)
{ // 행렬의 열과 행을 바꿔 새로운 행렬 초기화
    for(int i= 0; i< row; i++)
    { // 기존 행렬의 행, 전치행렬의 열
        for(int j= 0; j< col; j++)
        { // 기존 행렬의 열, 전치행렬의 행
            output[j][i]= matrix[i][j];
        }
    }

    print_matrix(output, col, row);
    free_matrix(output, col);
}

void multiply_matrix(int **output, int **matrixA, int **matrixB, int row, int col1, int col2)
{ // A 행렬의 행과 B행렬의 열, 겹치는 A행렬의 열과 B행렬의 행을 이용해 행렬곱 계산
    int temp= 0;
    for(int i= 0; i< row; i++)
    { // A행렬의 행을 의미
        for(int j= 0; j< col2; j++)
        { // B행렬의 열을 의미
            for(int k= 0; k< col1; k++)
            { // A행렬의 열과 B행렬의 행을 의미
                temp+= matrixA[i][k]* matrixB[k][j];
            }
            output[i][j]= temp;
            temp= 0;
        }
    }
    print_matrix(output, row, col2);
    free_matrix(output, row);
}


int main()
{// 이름과 학번 출력
    printf("[----- [Kim Yejun] [2020025051] -----]\n\n");
    
    int row1, col1, row2, col2; // A행렬과 B행렬의 각각 행과 열의 크기를 입력받음
    printf("Input Matrix A's row and column: ");
    scanf("%d %d", &row1, &col1);
    printf("Input Matrix B's row and column: ");
    scanf("%d %d", &row2, &col2);
    
    int **p1, **p2; // 이중포인터 P1과 P2를 이용해 행렬 A와 행렬 B를 생성

    p1= (int**)malloc(sizeof(int*)* row1); // malloc 함수를 이용해 2차원 배열 동적할당
    for(int i= 0; i< row1; i++) p1[i]= (int*) malloc(sizeof(int)* col1);

    p2= (int**)malloc(sizeof(int*)* row2);
    for(int i= 0; i< row2; i++) p2[i]= (int*) malloc(sizeof(int)* col2);


    srand(time(NULL)); // 임의의 값으로 행렬의 각 요소들을 초기화(값은 0~100)
    for(int i= 0; i< row1; i++)
    {
        for(int j= 0; j< col1; j++)
        {
            p1[i][j]= rand()% 101;
        }
    }
    for(int i= 0; i< row2; i++)
    {
        for(int j= 0; j< col2; j++)
        {
            p2[i][j]= rand()% 101;
        }
    }

    printf("Matrix A: \n"); // 행렬 A와 행렬 B를 출력
    print_matrix(p1, row1, col1);
    printf("Matrix B:\n");
    print_matrix(p2, row2, col2);

    if(row1==row2 && col1==col2)
    { // 행렬의 덧셈과 뺄셈을 수행, 행과 열의 크기가 같은지 확인 후 연산
        int **addition= (int**)malloc(sizeof(int*)* row1);
        for(int i= 0; i< row1; i++) addition[i]= (int*) malloc(sizeof(int)* col1);
        
        printf("Result of Matrix A + Matrix B\n"); // 행렬의 덧셈 수행
        addition_matrix(addition, p1, p2, row1, col1);

        int **subtraction= (int**)malloc(sizeof(int*)* row1);
        for(int i= 0; i< row1; i++) subtraction[i]= (int*) malloc(sizeof(int)* col1);

        printf("Result of Matrix A - Matrix B\n"); // 행렬의 뺄셈 수행
        subtraction_matrix(subtraction, p1, p2, row1, row2);
    }
    else printf("can not calculate Matrix A +- Matrix B...\n\n"); // 계산이 불가능한 경우

    int **transpose= (int**)malloc(sizeof(int*)* col1); // 행렬A의 전치행렬
    for(int i= 0; i< col1; i++) transpose[i]= (int*) malloc(sizeof(int)* row1);

    printf("Matrix A's transpose Matrix is...\n");
    transpose_matrix(transpose, p1, row1, col1);

    if(col1==row2)
    { // 행렬 곱을 위한 조건 확인 후 행렬 A와 행렬 B의 곱을 계산
        int **multiply= (int**)malloc(sizeof(int*)* row1);
        for(int i= 0; i< row1; i++) multiply[i]= (int*) malloc(sizeof(int)* col2);

        printf("Result of Matrix A * B\n"); // 행렬 곱을 수행
        multiply_matrix(multiply, p1, p2, row1, col1, col2);
    }
    else printf("can not calculate Matrix A * Matrix B...\n\n"); // 행렬 곱셈이 불가능한 경우

    free_matrix(p1, row1); // 행렬 A와 행렬 B 데이터 메모리 할당 해제
    free_matrix(p2, row2);
}