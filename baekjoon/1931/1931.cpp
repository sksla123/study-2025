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

    int n;
    cin >> n;

    vector<pair<int, int>> meeting_time_candidates;

    int start_time, end_time;
    for (int i = 0; i < n; i++) {
        cin >> start_time >> end_time;
        meeting_time_candidates.push_back(make_pair(end_time, start_time));
    }

    sort(meeting_time_candidates.begin(), meeting_time_candidates.end());

    int count = 0;
    int curr_meeting_end_time=-1;
    int curr_meeting_start_time=-1;

    int next_meeting_end_time, next_meeting_start_time;
    for(auto it: meeting_time_candidates){
        next_meeting_end_time = it.first;
        next_meeting_start_time = it.second;

        if (next_meeting_start_time >= curr_meeting_end_time) {
            count ++;
            curr_meeting_end_time = next_meeting_end_time;
            curr_meeting_start_time = next_meeting_start_time;
        }
    }

    cout << count;

    return 0;
}