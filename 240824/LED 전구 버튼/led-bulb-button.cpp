#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, B;
    cin >> N >> B;
    vector<int> bulbs(N);

    for (int i = 0; i < N; i++) {
        cin >> bulbs[i];
    }

    for (int i = 0; i < B; i++) {
        vector<int> next_bulbs = bulbs;
        for (int j = 0; j < N; j++) {
            int left = (j == 0) ? bulbs[N - 1] : bulbs[j - 1];
            if (left == 1) {
                next_bulbs[j] = 1 - bulbs[j];
            }
        }
        bulbs = next_bulbs;
    }

    for (int i = 0; i < N; i++) {
        cout << bulbs[i] << endl;
    }

    return 0;
}