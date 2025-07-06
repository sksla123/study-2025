#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <unordered_set>
#include <queue>
#include <cmath>
#include <iomanip>
#define INT_MAX 2147483647

//#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // 맵 크기 입력
    int n, m; 
    cin >> n >> m;

    // 시작 위치
    int r, c; // row, col
    cin >> r >> c;

    // 시작 시 로봇청소기가 바라보는 방향 {0, 1, 2, 3} (북동남서)
    int d;
    cin >> d;

    // 맵 입력
    vector<vector<int>> room_map;

    int temp;
    for(int i = 0; i < n; i++) {
        vector<int> temp_row;
        for(int j = 0; j < m; j ++) {
            cin >> temp;
            temp_row.push_back(temp);
        }
        room_map.push_back(temp_row);
    }

    // 로봇청소기 로직
    // 1. 현재 칸이 아직 청소되지 않은 경우, 현재 칸을 청소한다.
    // 2. 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 없는 경우,
    //     1). 바라보는 방향을 유지한 채로 한 칸 후진할 수 있다면 한 칸 후진하고 1번으로 돌아간다.
    //     2). 바라보는 방향의 뒤쪽 칸이 벽이라 후진할 수 없다면 작동을 멈춘다. <- break 조건
    // 3. 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 있는 경우
    //     1). 반시계 방향으로 90도 회전한다.
    //     2). 바라보는 방향을 기준으로 앞쪽 칸이 청소되지 않은 빈 칸인 경우 한 칸 전진한다. <- 아니면 그냥 1번 가면 되니까 ㅇㅇ
    //     3). 1번으로 돌아간다.
    // 시간 2초라 널널해서 알고리즘 구현만 하면 될 듯?
    // map 상태 지정
    // 0 : 청소되지 않은 바닥, 이동 가능
    // 1 : 벽, 이동 불가
    // 2 : 청소된 바닥, 이동 가능
    // 출력문 조건: 청소한 횟수
    
    int clean_cnt = 0;
    
    // 북동남서
    int delta_row[4] = {-1, 0, 1, 0}; 
    int delta_col[4] = {0, 1, 0, -1};
    
    bool uncleaned_neighbor_spaces = false;
    
    int _r, _c;
    while(true) {
        // 1. 현재 칸이 아직 청소되지 않은 경우, 현재 칸을 청소한다.
        if (room_map[r][c] == 0) {
            room_map[r][c] = 2;
            clean_cnt++;
        }

        // 주변 4칸 확인 (분기 조건)
        uncleaned_neighbor_spaces = false;
        for(int i = 0; i < 4; i++) {
            _r = r + delta_row[i];
            _c = c + delta_col[i];

            if (_r < n && _r >= 0 && _c < m && _c >= 0) { // 이동 조건. 맵 안에 있을 것
                if (room_map[_r][_c] == 0) uncleaned_neighbor_spaces = true; // 분기 조건. 청소되지 않은 칸일 것.
            }
            if (uncleaned_neighbor_spaces) break;
        }

        // 3. 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 있는 경우
        if (uncleaned_neighbor_spaces) {
            // 3-1). 반시계방향 회전 (북->서->남->동)
            d = (d + 3) % 4;
            
            // 3-2). 바라보는 방향을 기준으로 앞쪽 칸이 청소되지 않은 빈 칸인 경우 한 칸 전진한다.
            _r = r + delta_row[d];
            _c = c + delta_col[d];
            if (_r < n && _r >= 0 && _c < m && _c >= 0) { // 전진 조건 1. 맵 안에 있을 것
                if (room_map[_r][_c] == 0) { // 전진 조건 2. 청소되지 않은 칸일 것.
                    r = _r;
                    c = _c;
                }
            }
            // 3-3). 1번으로 되돌아간다.
            continue;
        }
        // 2. 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 없는 경우
        else {
            // 후진 가능 여부 판단
            _r = r - delta_row[d];
            _c = c - delta_col[d];
            if (_r < n && _r >= 0 && _c < m && _c >= 0) { // 후진 조건 1. 맵 안에 있을 것.
                if (room_map[_r][_c] != 1) { // 후진 조건 2. 벽이 아닐 것.
                    // 2-1). 바라보는 방향을 유지한 채로 한 칸 후진할 수 있다면 한 칸 후진하고 1번으로 돌아간다.
                    r = _r;
                    c = _c;
                    continue;
                }
            }
            // 2-2). 바라보는 방향의 뒤쪽 칸이 벽이라 후진할 수 없다면 작동을 멈춘다. <- break 조건
            break;
        }
    }

    cout << clean_cnt;

    return 0;
}