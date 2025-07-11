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
// #define INT_MAX 2147483647

//#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    long long n, m; // 나무의 개수, 필요한 나무 길이
    cin >> n >> m;

    map<long long, long long> trees;

    long long temp;
    for(int i =0; i < n; i++){
        cin >> temp;

        if (trees.count(temp) == 0) trees[temp] = 1;
        else trees[temp]++;
    }

    // 이진 탐색
    // 값은 0 ~ max
    long long highest_tree_height = trees.rbegin()->first; // map, set에서 max 뽑는 법: rbegin으로 가져오면 됨. (ordering 객체 특징)

    long long low = 0;
    long long high = highest_tree_height;
    long long mid;

    long long result = 0;

    // int count; // 방어 로직용
    while(low <= high){
        mid = low + (high - low) / 2;
        // cout << "현재 내가 자르는 나무 높이: " << mid << '\n'; // 디버그용

        auto it = trees.lower_bound(mid);
        long long total_cutted_part_height = 0;

        while(it != trees.end()){
            // cout << "현재 자르는 나무의 높이: " << it->first << ", 그러한 높이를 가지는 나무의 개수: " << it->second << '\n'; // 디버그용
            total_cutted_part_height += (it->first - mid) * it->second;
            it++;
        }

        // cout << "잘려진 나무 높이의 전체 합: " << total_cutted_part_height << '\n'; // 디버그용
        if (total_cutted_part_height == m) {
            result = mid;
            break;
        }
        else if (total_cutted_part_height < m) {
            high = mid - 1;
        }
        else {
            if (mid > result) result = mid;   
            low = mid + 1;
        }
        // cout << "현재 값 후보: " << result << '\n'; // 디버그용

        // 디버그 및 방어 로직
        // if (mid < 0 || mid > highest_tree_height || low > high || ++count >highest_tree_height) {
        //     cout << "error_occured\n";
        //     break;
        // }3
    }

    cout << result;

    return 0;
}