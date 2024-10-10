#include <iostream>
using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    int **data;

public:
    Matrix() {
        rows = 3;
        cols = 3;
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = 0;
            }
        }
    }

    Matrix(int r, int c, int value = 0) {
        rows = r;
        cols = c;
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = value;
            }
        }
    }

    Matrix(int r, int c, int arr[][3]) {
        rows = r;
        cols = c;
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = arr[i][j];
            }
        }
    }


    void print() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Matrix mat1;
    cout << "Default Constructor" << endl;
    mat1.print();

    Matrix mat2(3, 3, 5);
    cout << "\nParameterized Constructor" << endl;
    mat2.print();


    int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
    Matrix mat3(2, 3, arr);
    cout << "\nConstructor from 2D Array" << endl;
    mat3.print();

    return 0;
}
