#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, B;
    cin >> N >> B;
    vector<int> bulbs(N);
    vector<int> next_bulbs(N);
    for (int i=0; i<N; i++){
       cin >> bulbs[i];
    }
    next_bulbs = bulbs;

    for (int i=0; i<B; i++){
        for (int j=0; j<N; j++){
            if (j == 0){
                if (bulbs[N-1] == 1){
                    if (bulbs[j] == 0) next_bulbs[j] = 1;
                    else next_bulbs[j] = 0;
                }
            } 
            else if (bulbs[j-1] == 1){
                if (bulbs[j] == 0) next_bulbs[j] = 1;
                else next_bulbs[j] = 0;
            }
        }
        bulbs = next_bulbs;
    }
    
    for (int i=0; i<N; i++){
        cout << bulbs[i] << endl;
    }
    
    return 0;
}