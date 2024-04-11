#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 행렬을 생성하고 랜덤 값으로 초기화하는 함수
int** create_matrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *)); // 행의 수만큼 포인터를 가진 배열을 동적으로 할당
    for(int i=0; i<rows; i++) { // 행의 수만큼 반복
        matrix[i] = (int *)malloc(cols * sizeof(int)); // 열의 수만큼의 정수를 저장할 수 있는 배열을 동적으로 할당
        for(int j=0; j<cols; j++) { // 열의 수만큼 반복
            matrix[i][j] = rand() % 100; // 0~99 사이의 랜덤 값으로 초기화
        }
    }
    return matrix; // 생성된 행렬 반환
}

// A와 B 행렬을 출력하는 함수
void print_matrix(int **matrix, int rows, int cols) {
    for(int i=0; i<rows; i++) { 
        for(int j=0; j<cols; j++) {
            printf("%d ", matrix[i][j]); // 행렬의 원소 출력
        }
        printf("\n"); // 행렬의 행이 바뀔 때마다 줄 바꿈
    }
}

// A+B를 구현하는 함수
int** addition_matrix(int **A, int **B, int rows, int cols) {
    int **result = create_matrix(rows, cols); // 결과 행렬 생성
    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            result[i][j] = A[i][j] + B[i][j]; // A와 B의 같은 위치의 원소를 더한 값을 결과 행렬에 저장
        }
    }
    return result; // 결과 행렬 반환
}

// A-B를 구현하는 함수
int** subtraction_matrix(int **A, int **B, int rows, int cols) {
    int **result = create_matrix(rows, cols); // 결과 행렬 생성
    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            result[i][j] = A[i][j] - B[i][j]; // A와 B의 같은 위치의 원소를 뺀 값을 결과 행렬에 저장
        }
    }
    return result; // 결과 행렬 반환
}

// A의 전치행렬 T를 구현하는 함수
int** transpose_matrix(int **A, int rows, int cols) {
    int **result = create_matrix(cols, rows); // 결과 행렬 생성(행과 열 바뀜)
    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            result[j][i] = A[i][j]; // 원래 행렬의 해당 요소를 결과 행렬의 전치된 위치에 저장
        }
    }
    return result; // 전치 행렬 반환
}

// A X B를 구현하는 함수
int** multiply_matrix(int **A, int **B, int rowsA, int colsA, int rowsB, int colsB) {
    if(colsA != rowsB) { // 첫 번째 행렬의 열의 수와 두 번째 행렬의 행의 수가 같지 않으면
        printf("행렬의 곱셈이 불가능합니다.\n"); // 행렬의 곱셈 불가능
        return NULL; // NULL 반환
    }
    int **result = create_matrix(rowsA, colsB); // 결과 행렬 생성
        for(int i=0; i<rowsA; i++) { // 행렬 A의 행만큼 반복
            for(int j=0; j<colsB; j++) { // 행렬 B의 열만큼 반복
                result[i][j] = 0; // 결과 행렬의 해당 요소를 0으로 초기화
                for(int k=0; k<colsA; k++) { // 행렬 A의 열만큼 반복
                    result[i][j] += A[i][k] * B[k][j]; // 결과 행렬의 해당 요소에 A와 B의 곱을 더함
            }
        }
    }
    return result; // 결과 행렬 반환

}

// 행렬을 동적으로 할당 해제하는 함수
void free_matrix(int **matrix, int rows) {
    for(int i=0; i<rows; i++) {
        free(matrix[i]); // 해당 행의 메모리 할당 해제
    }
    free(matrix); // 행렬을 메모리에서 해제
}


int main() {
    int rows, cols; // 행과 열 변수 선언
    srand(time(NULL)); // random seed 설정
    scanf("%d %d", &rows, &cols); // 행과 열 입력

    int **A = create_matrix(rows, cols); // 행렬 A 생성
    int **B = create_matrix(rows, cols); // 행렬 B 생성

    printf("---------[한강민] [2023078040]---------\n");

    printf("Matrix A: \n");
    print_matrix(A, rows, cols); // 행렬 A 출력
    printf("Matrix B: \n");
    print_matrix(B, rows, cols); // 행렬 B 출력
 
    int **addition_result = addition_matrix(A, B, rows, cols); // 두 행렬을 더한 결과 계산
    printf("A + B: \n");
    print_matrix(addition_result, rows, cols); // A+B 출력

    int **subtraction_result = subtraction_matrix(A, B, rows, cols); // 두 행렬을 뺀 결과 계산
    printf("A - B: \n");
    print_matrix(subtraction_result, rows, cols); // A - B 출력

    int **transpose_result = transpose_matrix(A, rows, cols); // A의 전치행렬 계산
    printf("Transpose of A: \n");
    print_matrix(transpose_result, cols, rows); // A의 전치행렬 출력

    int **multiply_result = multiply_matrix(A, B, rows, cols, rows, cols); // 두 행렬을 곱한 결과 계산
    if(multiply_result != NULL) { // 행렬의 곱셈이 가능하면 (multiply_matrix의 반환값이 NULL이 아니면)
        printf("A * B: \n");
        print_matrix(multiply_result, rows, cols); // A * B 출력
    }

    free_matrix(A, rows); // 행렬 A 메모리 할당 해제
    free_matrix(B, rows); // 행렬 B 메모리 할당 해제
    free_matrix(addition_result, rows); // addition 결과 행렬 메모리 할당 해제
    free_matrix(subtraction_result, rows); // subtraction 결과 행렬 메모리 할당 해제
    free_matrix(transpose_result, cols); // transpose 결과 행렬 메모리 할당 해제
    if(multiply_result != NULL) { // 행렬의 곱셈이 가능하면
        free_matrix(multiply_result, rows); // multiply 결과 행렬 메모리 할당 해제
    }

    return 0;
}   