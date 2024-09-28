#include <vector>
#include <iostream>

using namespace std;

int n, m, d, p;
vector<vector<int>> place;
vector<int> dx = {1, 1, 0, -1, -1, -1, 0, 1};
vector<int> dy = {0, -1, -1, -1, 0, 1, 1, 1};
vector<pair<int, int>> drugs;


int main();
// void print_place();
// void print_drugs();
void move_drug_and_grow();
void navigate_near();
void resetting();


int main(){
    cin >> n >> m;
    place.resize(n, vector<int>(n));
    drugs = {{n-2, 0}, {n-2, 1}, {n-1, 0}, {n-1, 1}};
    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
            cin >> place[i][j];
        }
    }
    // print_place();

    for (int i=0; i<m; ++i){
        cin >> d >> p;
        move_drug_and_grow();
        // print_place();
        // print_drugs();
        navigate_near();
        // print_place();
        resetting();
        // print_place();
    }
    
    int result = 0;
    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
            result += place[i][j];
        }
    }
    cout << result;
    return 0;
}

// void print_place(){
//     for (int i=0; i<n; ++i){
//         for (int j=0; j<n; ++j){
//             cout << place[i][j] << ' ';
//         }
//         cout << endl;
//     }
// }
// void print_drugs(){
//     for (auto drug: drugs){
//         cout << drug.first << drug.second << ' ';
//     }
//     cout << endl;
// }

void move_drug_and_grow(){
    for (auto& drug: drugs){
        drug.first = (drug.first + dy[d-1]*p + n) % n;
        drug.second = (drug.second + dx[d-1]*p + n) % n;
        place[drug.first][drug.second]++;
    }
}

void navigate_near(){
    vector<int> near_dy = {-1, -1, 1, 1};
    vector<int> near_dx = {-1, 1, -1, 1};
    for (auto& drug: drugs){
        for (int i=0; i<4; ++i){
            int r = drug.first + near_dy[i];
            int c = drug.second + near_dx[i];
            if (r>=0 && r<n && c>=0 && c<n && place[r][c] >= 1) place[drug.first][drug.second]++;
        }
    }
}

void resetting(){
    vector<pair<int, int>> new_drugs;

    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
            pair<int, int> check_druged = {i, j};
            if (place[i][j] >= 2){
                bool already_exists = false;
                for (auto drug : drugs){
                    if (check_druged == drug){
                        already_exists = true;
                        break;
                    }
                }
                if (!already_exists) {
                    place[i][j] -= 2;
                    new_drugs.push_back(check_druged);
                }
            }
        }
    }
    drugs = new_drugs;
}