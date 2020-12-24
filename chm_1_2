#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

int main() {
    int n;
    double eps, w;
    cin >> n >> eps >> w;

    vector< vector <double> > matrix;
    vector<double> row;
    row.resize(n);
    vector<double> last_column;
    last_column.resize(n);

    // заполнение матрицы
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> row[j];
        }
        // столбец свободных коэффициентов
        cin >> last_column[i];
        matrix.push_back(row);
        row.erase(row.begin(), row.end());
        row.resize(n);
    }

    // проверка
    cout << endl;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }

    // метод верхней релаксации
    for(w = 1; w < 2; w += 0.1) {
        vector<double> x, tmp;
        x.resize(n), tmp.resize(n);
        int cnt = 0;
        double norm;
        do {
            for (int i = 0; i < n; ++i) {
                double sub_1 = 0, sub_2 = 0;
                for (int j = 0; j < i; j++) {
                    sub_1 += matrix[i][j] * tmp[j];
                }
                for (int j = i; j < n; ++j) {
                    sub_2 += matrix[i][j] * x[j];
                }
                tmp[i] = x[i] + w / matrix[i][i] * (last_column[i] - sub_1 - sub_2);
            }
            norm = 0;
            for (int i = 0; i < n; ++i) {
                norm += (x[i] - tmp[i]) * (x[i] - tmp[i]);
            }
            norm = sqrt(norm);
            for (int i = 0; i < n; ++i) {
                x[i] = tmp[i];
            }
            ++cnt;
        }
        while(norm >= eps);
        cout << "Iteration count: " << cnt << ' ' << " w: " << w << endl;
    }


    /*//Выводим решения
    ofstream out ("answer.txt");
    cout <<endl <<"Answer" <<endl;
    for (int i = 0; i < n; i++) {
        cout << x[i] << " ";
        out << x[i] << ' ';
    }
    out.close();*/
    return 0;
}

/*
3
1
1.6
0.0001
1 2 3
2 3 4
3 4 6
14 20 29

2
1
1.5
0.0001
1 1
1 3
3 7
*/
