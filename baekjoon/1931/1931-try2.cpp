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

    // 회의 개수 n 입력
    int n;
    cin >> n;

    // map과 set은 자동 정렬, 중복 제거라는 장점이 있음(물론 입출력 오버헤드가 있긴한데, 여긴 정렬을 많이 해야하니 상관없을듯?)
    map<int, set<int>> meeting_time_candidates; // 시작 - 끝 맵

    int start_time;
    int end_time;
    for(int i = 0; i < n; i++) {
        cin >> start_time >> end_time;
        meeting_time_candidates[end_time].insert(start_time);
    }

    int cnt = 0;
    int curr_end_time = -5;
    int curr_start_time = -5;

    // 디버그용 정렬 출력
    // for(auto it: meeting_time_candidates){
    //     int _e = it.first;
    //     for(int _s: it.second){
    //         cout << '(' << _s << ", " << _e << ")\n";
    //     }
    // }
    
    // cout << "\n(" << curr_start_time << ", " << curr_end_time << ")"; // 디버그용
    // 정렬되어 있으므로 iterator로 접근해도 됨.
    for(auto it: meeting_time_candidates){
        int _e = it.first;

        for(int _s: it.second){
            if (_s >= curr_end_time) {
                curr_start_time = _s;
                curr_end_time = _e;
                cnt++;

                // cout << " -> (" << curr_start_time << ", " << curr_end_time << ")"; // 디버그용
            }
        }
    }
    // cout << "\n\n"; // 디버그용
    cout << cnt;

    return 0;
}