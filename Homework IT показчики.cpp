#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

void fill(int** arr, int rows, int cols) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            arr[i][j] = rand() % 101 - 50;
}

void print(int** arr, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            cout << arr[i][j] << '\t';
        cout << '\n';
    }
}

void rowColSums(int** arr, int rows, int cols) {
    cout << "Row sums: ";
    for (int i = 0; i < rows; ++i) {
        int sum = 0;
        for (int j = 0; j < cols; ++j) sum += arr[i][j];
        cout << sum << ", ";
    }
    cout << "\nColumn sums: ";
    for (int j = 0; j < cols; ++j) {
        int sum = 0;
        for (int i = 0; i < rows; ++i) sum += arr[i][j];
        cout << sum << ", ";
    }
    cout << "\n";
}

int* minInRows(int** arr, int rows, int cols) {
    int* mins = new int[rows];
    for (int i = 0; i < rows; ++i) {
        mins[i] = *min_element(arr[i], arr[i] + cols);
    }
    return mins;
}

void transpose(int** arr, int rows, int cols) {
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            cout << arr[j][i] << "\t";
        }
        cout << "\n";
    }
}

double avgPositives(int** arr, int rows, int cols) {
    int sum = 0, count = 0;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (arr[i][j] > 0) { sum += arr[i][j]; count++; }
    return count == 0 ? -1 : static_cast<double>(sum) / count;
}

int maxInArray(int** arr, int rows, int cols) {
    int maxVal = arr[0][0];
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (arr[i][j] > maxVal) maxVal = arr[i][j];
    return maxVal;
}

int maxConsecutivePositives(int* row, int cols) {
    int maxCount = 0, count = 0;
    for (int j = 0; j < cols; ++j) {
        if (row[j] > 0) count++;
        else { maxCount = max(maxCount, count); count = 0; }
    }
    return max(maxCount, count);
}

int** increaseByMax(int** arr, int rows, int cols) {
    int maxVal = maxInArray(arr, rows, cols);
    int** increased = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        increased[i] = new int[cols];
        for (int j = 0; j < cols; ++j)
            increased[i][j] = arr[i][j] + maxVal;
    }
    return increased;
}

int main() {
    srand(time(0));
    int rows, cols;
    cout << "Rows: "; cin >> rows;
    cout << "Cols: "; cin >> cols;

    int** arr = new int* [rows];
    for (int i = 0; i < rows; ++i) arr[i] = new int[cols];

    fill(arr, rows, cols);
    cout << "Array:\n"; print(arr, rows, cols);
    rowColSums(arr, rows, cols);

    int* mins = minInRows(arr, rows, cols);
    cout << "Min elements: ";
    for (int i = 0; i < rows; ++i) cout << mins[i] << " ";
    cout << "\n";
    delete[] mins;

    cout << "Transposed:\n"; transpose(arr, rows, cols);

    double avg = avgPositives(arr, rows, cols);
    if (avg >= 0) cout << "Avg positives: " << avg << "\n";

    cout << "Even indices: ";
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (arr[i][j] % 2 == 0) cout << "(" << i << ", " << j << ") ";
    cout << "\n";

    int** increased = increaseByMax(arr, rows, cols);
    cout << "Increased array:\n"; print(increased, rows, cols);

    for (int i = 0; i < rows; ++i) {
        cout << "Max consecutive positives in row " << i << ": " << maxConsecutivePositives(arr[i], cols) << "\n";
    }

    for (int i = 0; i < rows; ++i) {
        delete[] arr[i];
        delete[] increased[i];
    }
    delete[] arr;
    delete[] increased;

    return 0;
}
