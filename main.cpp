#include <iostream>
#include <fstream>

int** initMatrix(int size) {
    int** matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

void freeMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void printMatrix(int** matrix, int size) {
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}


int main() {
    std::ifstream infile("input.txt");

    if (!infile) {
        std::cerr << "Error: Unable to open the input file.";
        return 1;
    }

    int size;
    infile >> size;

    int** matrix = initMatrix(size);

    printMatrix(matrix, size);

    freeMatrix(matrix, size);

    infile.close();
    return 0;
}
