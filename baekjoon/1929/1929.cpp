#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <iomanip>

//#include <bits/stdc++.h>

using namespace std;

// 에리스토테네스의 체 
void eratosthenes(vector<bool>& arr, int _m){
    arr[0] = false;
    arr[1] = false;

    // 2 부터 i^2까지만 진행
    // 어짜피 i^2 이후의 숫자 중 소수가 아닌 수는 이미 걸러짐
    for(int i = 2; i * i < _m; i++){
        if (!arr[i]) continue;
        // i^2 부터 진행 (이미 그 사이의 소수가 아닌 수들은 모두 제거됨.)
        // j += i == i의 배수
        for(int j = i * i; j < _m; j += i) {
            arr[j] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // 범위 받기
    int n, m;
    cin >> n >> m;

    // 배열 크기
    int _m = m+1;
    
    // 배열 생성
    vector<bool> arr(_m, true);

    eratosthenes(arr, _m);
    
    for(int i = n; i < _m; i++){
        if (arr[i]) cout << i << '\n';
    }

    return 0;
}