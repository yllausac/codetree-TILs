#include <iostream>
#include <vector>

using namespace std;

vector<int> multiply(const vector<vector<int>>& mat, const vector<int>& vec, int N) {
    vector<int> result(N, 0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i] ^= (mat[i][j] * vec[j]);  // XOR 연산을 사용하여 상태 전이
        }
    }
    return result;
}

vector<vector<int>> multiplyMatrices(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2, int N) {
    vector<vector<int>> result(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                result[i][j] ^= (mat1[i][k] * mat2[k][j]);  // XOR 연산을 사용
            }
        }
    }
    return result;
}

vector<vector<int>> matrixPower(vector<vector<int>>& mat, long long exp, int N) {
    vector<vector<int>> result(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        result[i][i] = 1;  // 단위 행렬
    }

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = multiplyMatrices(result, mat, N);
        }
        mat = multiplyMatrices(mat, mat, N);
        exp /= 2;
    }

    return result;
}

int main() {
    int N;
    long long B;
    cin >> N >> B;
    vector<int> bulbs(N);

    for (int i = 0; i < N; i++) {
        cin >> bulbs[i];
    }

    // 상태 전이 행렬 구성
    vector<vector<int>> transitionMatrix(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        transitionMatrix[i][i] = 1;  // 현재 전구의 상태 유지
        transitionMatrix[i][(i + N - 1) % N] = 1;  // 왼쪽 전구에 의한 상태 변경
    }

    // B번의 상태 전이를 행렬 제곱으로 계산
    vector<vector<int>> finalMatrix = matrixPower(transitionMatrix, B, N);

    // 초기 상태에 최종 행렬을 곱해 최종 상태를 계산
    vector<int> finalState = multiply(finalMatrix, bulbs, N);

    for (int i = 0; i < N; i++) {
        cout << finalState[i] << endl;
    }

    return 0;
}