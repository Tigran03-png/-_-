#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Использование: %s <имя файла>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r+");
    if (file == NULL) {
        printf("Не удалось открыть файл.\n");
        return 1;
    }

    int N, M;
    if (fscanf(file, "%d %d", &N, &M) != 2) {
        printf("Ошибка чтения размеров матрицы.\n");
        fclose(file);
        return 1;
    }

    int **matrix = (int **) malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int *) malloc(M * sizeof(int));
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {
                printf("Ошибка чтения элемента матрицы.\n");
                for (int k = 0; k < N; k++) {
                    free(matrix[k]);
                }
                free(matrix);
                fclose(file);
                return 1;
            }
        }
    }

    int *rowSums = (int *) malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        int sum = 0;
        for (int j = 0; j < M; j++) {
            sum += matrix[i][j];
        }
        rowSums[i] = sum;
    }

    printf("Массив сумм строк: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", rowSums[i]);
    }
    printf("\n");

    int max_in_row5;
    if (N >= 5) {
        max_in_row5 = matrix[4][0];
        for (int j = 1; j < M; j++) {
            if (matrix[4][j] > max_in_row5) {
                max_in_row5 = matrix[4][j];
            }
        }
        printf("Максимальный элемент в 5-й строке: %d\n", max_in_row5);

        if (N >= 3) {
            matrix[2][M - 1] = max_in_row5;
            printf("После замены последний элемент 3-й строки: %d\n", matrix[2][M - 1]);
        }
    } else {
        printf("Матрица содержит менее 5 строк, задача по поиску максимума в 5-й строке не выполнена.\n");
    }

    rewind(file);

    fprintf(file, "%d %d\n", N, M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(rowSums);

    fclose(file);
    return 0;
}
