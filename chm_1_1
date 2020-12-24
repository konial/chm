#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define float double

using namespace std;

const float eps = 1e-3;

bool flag;

//прямой ход
int gausFirstStep(vector< vector <float> > &matrix, vector<float> &last_column) {
    int n = matrix.size();
    flag = false;
    for(int i = 0; i < n; ++i) {
        int j = i;
        while(j < n && matrix[j][i] == 0) {
            ++j;
        }
        if (j == n) return -1;
        if(j != i) {
            swap(matrix[j], matrix[i]);
            flag = !flag;
        }

        for(int j = i + 1; j < n; ++j) {
            float tmp = matrix[j][i] / matrix[i][i];
            for(int k = i; k < n; ++k) {
                matrix[j][k] -= matrix[i][k] * tmp;
                if(fabs(matrix[j][k]) < eps) matrix[j][k] = 0;
            }
            last_column[j] -= last_column[i] * tmp;
            if(fabs(last_column[j]) < eps) last_column[j] = 0;
        }
    }
    return 0;
}

// обратный ход
vector<float> gausSecondStep(vector< vector <float> > &matrix, vector<float> &last_column) {
    int n = matrix.size();
    vector<float> ans;
    for(int i = n - 1; i >= 0; --i) {
        float res = last_column[i];
        for(int j = i + 1; j < n; ++j) {
            res -= matrix[i][j] * ans[ans.size() - (j - i - 1) - 1];
        }
        res /= matrix[i][i];
        ans.push_back(res);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

// вычисление определителя
float calcDet(vector< vector <float> > &matrix) {
    int n = matrix.size();
    /*// проверка
    cout << endl;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }*/
    vector<float> buf;
    buf.resize(n);
    if(gausFirstStep(matrix, buf)) return 0;
    float det = 1;
    for(int i = 0; i < n; ++i) {
        det *= matrix[i][i];
    }
    if (flag) {
        det *= -1;
    }
    return det;
}

int main()
{
    setlocale(LC_ALL, "russian");
    int n = 2000;
    cout << "Введите порядок СЛАУ: ";
    //cin >> n;
    int mode = 2;
    while(mode > 2 || mode < 1) {
        system("cls");
        cout << "Введите порядок СЛАУ: " << n << endl;
        cout << "Выберите режим заполнения: 1 - вручную, 2 - через формулы: ";
        cin >> mode;
        cout << endl;
    }

    vector< vector <float> > matrix;
    vector<float> row;
    row.resize(n);
    vector<float> last_column;
    last_column.resize(n);

    // заполнение матрицы путем ввода на клавиатуре
    if(mode == 1) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                cin >> row[j];
            }
            matrix.push_back(row);
            row.erase(row.begin(), row.end());
            row.resize(n);
        }
        // заполнение свободного столбца
        for(int i = 0; i < n; ++i) {
            cin >> last_column[i];
        }
    }

    // заполнение матрицы через формулы
    if(mode == 2) {
        float x = 1;
        cout << "Введите параметр x: ";
        //cin >> x;
        float q = 1.001 - 2 * 4 * 1e-3;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(j != i) row[j] = pow(q, i + j + 2) + 0.1 * (j - i);
                else row[j] = pow(q - 1, i + j + 2);
            }
            matrix.push_back(row);
            row.erase(row.begin(), row.end());
            row.resize(n);
        }
        // заполнение свободного столбца
        for(int i = 0; i < n; ++i) {
            last_column[i] = 100 * exp(x / (i + 1)) * cos(x);
        }
    }

    // промежуточная матрица для вычислений
    vector< vector <float> > buf_matrix = matrix;

    if(gausFirstStep(buf_matrix, last_column)) {
        cout << endl << "Ошибка: Det(A) = 0" << endl;
        return 0;
    }

    vector<float> ans = gausSecondStep(buf_matrix, last_column);
    /*cout << endl << "Вектор-решение {x} = (";
    for(vector<float>::iterator it = ans.begin(); it != ans.end(); ++it) {
        cout << *it;
        if(it != ans.end() - 1) cout << ", ";
    }
    cout << ")" << endl;

    float det = calcDet(buf_matrix);
    cout << endl << "Определитель матрицы det(A) = " << det << endl;*/

    /*// вычисление обратной матрицы
    vector< vector <float> > inv_matrix = matrix;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            float val = 1;
            if((i + j) % 2) val *= -1;
            vector< vector <float> > minor_matrix;
            for(int k = 0; k < n; ++k) {
                if(k == i) continue;
                vector<float> row = matrix[k];
                row.erase(row.begin() + j);
                minor_matrix.push_back(row);
            }
            float minor_det = calcDet(minor_matrix);
            inv_matrix[j][i] = val * minor_det / det;
        }
    }

    // проверка
    cout << endl;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cout << inv_matrix[i][j] << ' ';
        }
        cout << endl;
    }

    // вычисление числа обусловленности
    double max_sum = 0;
    for(int i = 0; i < n; ++i) {
        float sum = 0;
        for(int j = 0; j < n; ++j) {
            sum += fabs(matrix[i][j]);
        }
        if(sum > max_sum) max_sum = sum;
    }
    double max_inv_sum = 0;
    for(int i = 0; i < n; ++i) {
        float sum = 0;
        for(int j = 0; j < n; ++j) {
            sum += fabs(inv_matrix[i][j]);
        }
        if(sum > max_inv_sum) max_inv_sum = sum;
    }
    double index = max_sum * max_inv_sum;
    cout << endl << "Число обусловленности матрицы М = " << index << endl;*/
    return 0;
}

/*
2 -2 0 1
2 3 1 -3
3 4 -1 2
1 3 1 -1
-3 -6 0 2

1 3 2 1
2 -1 3 -2
3 -5 4 -3
1 17 4 -23
0 0 0 0

3 -1 1
1 1 1
4 -1 4
3 5 5

45 -28 34 -52
36 -23 29 -43
47 -32 36 -48
27 -19 22 -35
9 3 -17 6
*/
