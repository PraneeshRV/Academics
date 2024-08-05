#include <iostream>
using namespace std;

class Matrix{
    private:
    int row;
    int col;
    int a,b;
    int **data;

    public:
    Matrix(int r,int c){
        row=r;
        col=c;
        data = new int*[r];
        for(int i =0;i< r ; ++i){
            data[i] = new int[c];
            for(int j = 0;j<c;++j){
                data[i][j] = 0;
            }
        }
    }

    void setvalue(int r,int c, int value){
        data[r][c]=value;
    }

    Matrix operator*(Matrix const &other){
        Matrix result(row,col);
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++)
            {
                for(int k = 0; k < row; k++)
                {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;

    }
    void print(){
    for(int k = 0; k < row; k++ )
    {
        for(int l = 0; l < col; l++)
        {
            cout<<data[k][l]<<" ";
        }
        cout<<endl;
    }
    }

};

int main(){
    Matrix m1(2,2);
    Matrix m2(2,2);
    m1.setvalue(0,0,2);
    m1.setvalue(0,1,3);
    m1.setvalue(1,0,5);
    m1.setvalue(1,1,2);

    m2.setvalue(0,0,5);
    m2.setvalue(0,1,3);
    m2.setvalue(1,0,2);
    m2.setvalue(1,1,1);

    Matrix m3 = m1*m2;
    m3.print();
    return 0;
}