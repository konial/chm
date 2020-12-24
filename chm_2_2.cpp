#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iomanip>

#define float double

using namespace std;

const float eps = 1e-3;
const double e = 2.718281828;

//прямой ход
int gausFirstStep(vector< vector <float> > &matrix, vector<float> &last_column) {
    int n = matrix.size();
    for(int i = 0; i < n; ++i) {
        int j = i;
        while(j < n && matrix[j][i] == 0) {
            ++j;
        }
        if (j == n) return -1;
        swap(matrix[j], matrix[i]);
        for(int j = i + 1; j < n; ++j) {
            float tmp = matrix[j][i] / matrix[i][i];
            for(int k = i; k < n; ++k) {
                matrix[j][k] -= matrix[i][k] * tmp;
                if(fabs(matrix[j][k]) < eps) matrix[j][k] = 0;
            }
            last_column[j] -= last_column[i] * tmp;
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

double P(double x) {
    return exp(x);
}

double Q(double x) {
    return x / 2;
}

double F(double x) {
    return x * x;
}

int main() {
    setlocale(LC_ALL, "Russian");
    double a = 0.1, b = 1.1, h = 0.01;
    int n = ceil((b - a) / h);
    double c1 = 1, c2 = -1.2, c = 0, d1 = 2, d2 = -2.5, d = -4;

    vector< vector <float> > matrix;
    vector<float> row;
    row.resize(n);
    vector<float> last_column;
    last_column.resize(n);
    row[0] = c1 * h - c2;
    row[1] = c2;
    matrix.push_back(row);
    row.erase(row.begin(), row.end());
    row.resize(n);
    last_column[0] = c * h;

    for(int i = 1; i < n - 1; ++i) {
        float x = a + i * h;
        float p = P(x);
        float q = Q(x);
        float f = F(x);
        row[i - 1] = 1 - p * h / 2;
        row[i] = q * h * h - 2;
        row[i + 1] = 1 + p * h / 2;
        matrix.push_back(row);
        row.erase(row.begin(), row.end());
        row.resize(n);
        last_column[i] = f * h * h;
    }

    row[n - 2] = -d2;
    row[n - 1] = d1 * h + d2;
    matrix.push_back(row);
    row.erase(row.begin(), row.end());
    row.resize(n);
    last_column[n - 1] = d * h;

    // промежуточная матрица для вычислений
    vector< vector <float> > buf_matrix = matrix;

    if(gausFirstStep(buf_matrix, last_column)) {
        cout << endl << "Ошибка: Det(A) = 0" << endl;
        return 0;
    }

    vector<float> ans = gausSecondStep(buf_matrix, last_column);
    cout << endl << "Вектор-решение {x} = (";
    for(vector<float>::iterator it = ans.begin(); it != ans.end(); ++it) {
        cout << *it;
        if(it != ans.end() - 1) cout << ", ";
    }
    cout << ")" << endl;
    ofstream out("answer.txt");
    for(int i = 0; i < n; ++i) {
        float x = a + i * h;
        out << "(" << x << ", " << ans[i] << ")";
        if(i != n - 1) out << ",";
    }
    out << endl;
    return 0;
}
