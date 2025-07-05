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

//#include <bits/stdc++.h>

using namespace std;

class Point {
    public:
        int x;
        int y;

        Point(int _x, int _y):x(_x), y(_y) {}

        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
};

namespace std {
    template <>
    struct hash<Point> {
        size_t operator()(const Point& p) const noexcept {
            return p.x * 100000 + p.y;
        }
    };
}

int count_houses(vector<vector<int>>& house_map, unordered_set<Point>& unsearched_houses, int n, int start_x, int start_y){
    int count = 0;
    queue<Point> q;

    q.push(Point(start_x, start_y));
    unsearched_houses.erase(Point(start_x, start_y));
    count++;

    int dy[] = {-1, 1, 0, 0};
    int dx[] = {0, 0, -1, 1};

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int ny = current.y + dy[i]; 
            int nx = current.x + dx[i];

            if (ny >= 0 && ny < n && nx >= 0 && nx < n) {
                Point neighbor(nx, ny);

                if (house_map[ny][nx] == 1 && unsearched_houses.count(neighbor)) {
                    q.push(neighbor);
                    unsearched_houses.erase(neighbor);
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    unordered_set<Point> unsearched_houses;
    vector<vector<int>> house_map;
    
    // 입력
    string temp;
    int h = 0;
    for(int y = 0; y < n; y++) {
        vector<int> axis_x_map;
        
        cin >> temp;
        for (int x = 0; x < n; x++) {
            h = temp[x] - '0';
            if (h == 1) {
                unsearched_houses.insert(Point(x, y));
            }
            axis_x_map.push_back(h);
        }
        
        house_map.push_back(axis_x_map);
    }
    
    vector<int> final_result;

    while(!unsearched_houses.empty()){
        Point a = *unsearched_houses.begin();
        // cout << a.x << ' ' << a.y << '\n';
        final_result.push_back(count_houses(house_map, unsearched_houses, n, a.x, a.y));
        // cout << final_result.back() << '\n';
    }
    // cout << '\n';

    sort(final_result.begin(), final_result.end());

    cout << final_result.size() << '\n';
    for(int r: final_result){
        cout << r << '\n';
    }

    return 0;
}