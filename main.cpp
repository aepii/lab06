#include <iostream>
#include <fstream>

// Function to initialize a square matrix with zeros.
int** initMatrix(int size){
    int** matrix = new int*[size];
    for (int i = 0; i < size; i++){
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++){
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

// Function to deallocate the memory of a matrix.
void freeMatrix(int** matrix, int size){
    for (int i = 0; i < size; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Function to print out a matrix.
void printMatrix(int** matrix, int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

// Function that reads a file and populates the matrix with elements retrieved from a file.
void populateMatrix(std::ifstream& infile, int** matrix, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (!(infile >> matrix[i][j])){
                std::cerr << "Error reading from file.";
                freeMatrix(matrix, size);
                infile.close();
                exit(1);
            }
        }
    }
}


// Function that calculates the sum of two matrices. Returns a matrix.
int** matrixSum(int** matrix1, int** matrix2, int size){
    int** matrix = initMatrix(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            matrix[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return matrix;
}

// Function that calculates the product of two matrices. Returns a matrix.
int** matrixProduct(int** matrix1, int** matrix2, int size){
    int** matrix = initMatrix(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            for(int k = 0; k < size; k++){
                matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return matrix;
}

// Function that calculates the difference of two matrices. Returns a matrix.
int** matrixDifference(int** matrix1, int** matrix2, int size){
    int** matrix = initMatrix(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            matrix[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    return matrix;
}

// Function that returns the max element of a matrix.
int getMaxElement(int** matrix, int size) {
    int maxElement = matrix[0][0]; 
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] > maxElement) { 
                maxElement = matrix[i][j];
            }
        }
    }
    return maxElement;
}

// Function that updates an element of a matrix with provided indices.
void updateElement(int** matrix, int size, int row, int col, int value) {
    if (row >= size || col >= size) {
        std::cerr << "Out of bounds.";
        freeMatrix(matrix, size);
        exit(1);
    }
    matrix[row][col] = value;
}

// Function that transposes a matrix in-place.
void transposeMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}

// Main entry point of program.
int main() {
    std::ifstream infile("matrix_input.txt");

    if (!infile) {
        std::cerr << "Error: Unable to open the input file.";
        return 1;
    }

    int size;
    infile >> size;

    int** matrix1 = initMatrix(size);
    int** matrix2 = initMatrix(size);

    populateMatrix(infile, matrix1, size);
    populateMatrix(infile, matrix2, size);

    std::cout << "Matrix 1:\n";
    printMatrix(matrix1, size);
    std::cout << "\nMatrix 2:\n";
    printMatrix(matrix2, size);

    std::cout << "\nSum of Matrix 1 and Matrix 2:\n";
    int** matrix3 = matrixSum(matrix1, matrix2, size);
    printMatrix(matrix3, size);

    std::cout << "\nProduct of Matrix 1 and Matrix 2:\n";
    int** matrix4 = matrixProduct(matrix1, matrix2, size);
    printMatrix(matrix4, size);

    std::cout << "\nDifference of Matrix 1 and Matrix 2:\n";
    int** matrix5 = matrixDifference(matrix1, matrix2, size);
    printMatrix(matrix5, size);

    std::cout << "\nChange (1,1) of Matrix 1 to 100:\n";
    updateElement(matrix1, size, 1, 1, 100);
    printMatrix(matrix1, size);

    std::cout << "\nMax Element of Matrix 1:\n";
    int maxElement = getMaxElement(matrix1, size); 
    std::cout << maxElement << std::endl; 

    std::cout << "\nTransposition of Matrix 1:\n";
    transposeMatrix(matrix1, size);
    printMatrix(matrix1, size);

    freeMatrix(matrix1, size);
    freeMatrix(matrix2, size);
    freeMatrix(matrix3, size);
    freeMatrix(matrix4, size);
    freeMatrix(matrix5, size);

    infile.close();
    return 0;
}
