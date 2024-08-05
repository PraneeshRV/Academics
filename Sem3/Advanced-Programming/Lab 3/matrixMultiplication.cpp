#include <iostream>
using namespace std;

class Matrix {
    private:
    int row;
    int col;
    int **data;

    public:
    Matrix(int r, int c) {
        row = r;
        col = c;
        data = new int*[r];
        for (int i = 0; i < r; ++i) {
            data[i] = new int[c];
            for (int j = 0; j < c; ++j) {
                data[i][j] = 0;
            }
        }
    }

    void setvalue(int r, int c, int value) {
        data[r][c] = value;
    }

    Matrix operator*(const Matrix& other) const {
        if (col != other.row) {
            cout<<"Matrix dimensions are not compatible for multiplication."<<endl;
        }
        
        Matrix result(row, other.col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < other.col; j++) {
                for (int k = 0; k < col; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    void print() {
        for (int k = 0; k < row; k++) {
            for (int l = 0; l < col; l++) {
                cout << data[k][l] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int rows1, cols1, rows2, cols2;

    cout << "Enter dimensions for matrix 1 (rows columns): ";
    cin >> rows1 >> cols1;
    cout << "Enter dimensions for matrix 2 (rows columns): ";
    cin >> rows2 >> cols2;

    if (cols1 != rows2) {
        cout << "Error: The number of columns in the first matrix must equal the number of rows in the second matrix." << endl;
        return 1;
    }

    Matrix m1(rows1, cols1);
    Matrix m2(rows2, cols2);

    cout << "Enter values for matrix 1:" << endl;
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            int value;
            cout << "Enter value for m1[" << i << "][" << j << "]: ";
            cin >> value;
            m1.setvalue(i, j, value);
        }
    }

    cout << "Enter values for matrix 2:" << endl;
    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            int value;
            cout << "Enter value for m2[" << i << "][" << j << "]: ";
            cin >> value;
            m2.setvalue(i, j, value);
        }
    }


        Matrix m3 = m1 * m2;
        cout << "Result of matrix multiplication:" << endl;
        m3.print();

    return 0;
}