#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
struct Dice{
    pair<int, int> location = {0, 1};
    int direction = 0;
    vector<int> info = {4, 2, 1};
}; Dice dice;
vector<vector<int>> place;


int main();
void define_direction();
void rotation_dice();
void move_dice();
int count_score();

int main(){
    cin >> n >> m;
    int count = m-1;
    int result = 0;
    place.resize(n, vector<int>(n));

    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
            cin >> place[i][j];
        }
    }
    result = count_score();
    while (count > 0){
        define_direction();
        rotation_dice();
        move_dice();
        result += count_score();
        count--;
    }
    cout << result << endl;;

}


void define_direction(){
    int r = dice.location.first;
    int c = dice.location.second;
    int bottom = 7 - dice.info[0];

    if (bottom > place[r][c]){
        dice.direction = (dice.direction + 1 + 4) % 4;
    }
    else if (bottom < place[r][c]){
        dice.direction = (dice.direction - 1 + 4) % 4;
    }
    else {
        dice.direction = (dice.direction + 4) % 4;
    }
    
}

void rotation_dice(){
    int up = dice.info[0];
    int front = dice.info[1];
    int right = dice.info[2];
    
    if (dice.direction == 0) dice.info = {7-right, front, up};
    else if (dice.direction == 1) dice.info = {7-front, up, right};
    else if (dice.direction == 2) dice.info = {right, front, 7-up};
    else dice.info = {front, 7-up, right};
}

void move_dice() {
    static const vector<pair<int, int>> moves = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int r = dice.location.first + moves[dice.direction].first;
    int c = dice.location.second + moves[dice.direction].second;

    dice.location = {r, c};

    if (r < 0) {
        dice.location.first = 0;
        dice.direction = 1;
    } else if (r >= n) {
        dice.location.first = n - 1;
        dice.direction = 3;
    }

    if (c < 0) {
        dice.location.second = 0;
        dice.direction = 0;
    } else if (c >= n) {
        dice.location.second = n - 1;
        dice.direction = 2;
    }
}

int count_score(){
    vector<int> dy = {0, 0, 1, -1};
    vector<int> dx = {1, -1, 0, 0};
    int score = place[dice.location.first][dice.location.second];
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    queue<pair<int, int>> q;
    q.push({dice.location.first, dice.location.second});
    visited[dice.location.first][dice.location.second] = true;

    while (!q.empty()){
        pair<int, int> curr_pos = q.front();
        int r = curr_pos.first;
        int c = curr_pos.second;
        q.pop();

        for (int i=0; i<4; ++i){
            int nr = r + dy[i];
            int nc = c + dx[i];
            if (nr>=0 && nr<n && nc>=0 && nc<n && !visited[nr][nc] && place[nr][nc] == place[r][c]){
                q.push({nr, nc});
                visited[nr][nc] = true;
                score += place[r][c];
            }
        }
    }
    return score;
}