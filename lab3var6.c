#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Используйте: " << argv[0] << " <имя файла>\n";
        return 1;
    }

    string filename = argv[1];
    ifstream fin(filename);

    if (!fin) {
        cout << "Не удалось открыть файл: " << filename << endl;
        return 1;
    }

    int N, M;


    fin >> N >> M;


    vector<vector<int>> matrix(N, vector<int>(M));


    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fin >> matrix[i][j];
        }
    }

    fin.close();


    vector<int> rowSums(N, 0);
    for (int i = 0; i < N; i++) {
        int sum = 0;
        for (int j = 0; j < M; j++) {
            sum += matrix[i][j];
        }
        rowSums[i] = sum;
    }

    cout << "Массив сумм строк:\n";
    for (int i = 0; i < N; i++) {
        cout << "Строка " << i + 1 << ": " << rowSums[i] << endl;
    }


    if (N < 5) {
        cout << "В матрице менее 5 строк, задача невозможна.\n";
        return 1;
    }

    int maxInFifthRow = matrix[4][0];
    for (int j = 1; j < M; j++) {
        if (matrix[4][j] > maxInFifthRow) {
            maxInFifthRow = matrix[4][j];
        }
    }
    cout << "Максимальный элемент в 5-й строке: " << maxInFifthRow << endl;


    if (N < 3) {
        cout << "В матрице менее 3 строк, заменить нечего.\n";
        return 1;
    }
    matrix[2][M - 1] = maxInFifthRow;


    cout << "Обновленная матрица:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}