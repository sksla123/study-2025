# 1929 소수 구하기
문제 링크 https://www.acmicpc.net/problem/1929


## 알고리즘
에라토스테네스의 체를 사용하면 됨

## 시행착오
1. 에라토스테네스의 단순 반복문 구현 <- 속도로 인한 실패 
```
모든 수에 대해서 단순 반복문 적용

void eratosthenes(vector<bool>& arr, int _m){
    arr[0] = false;
    arr[1] = false;

    for(int i = 2; i < _m; i++){ <- 실패원인
        if (!arr[i]) continue;
        for(int j = i+1; j < _m; j ++) { <- 실패원인
            if (j%i == 0) arr[j] = false;
        }
    }
}
```

### 해결
```
void eratosthenes(vector<bool>& arr, int _m){
    arr[0] = false;
    arr[1] = false;

    // 전체가 아닌 i * i로 변경 
    // 이유: i이하의 소수에 의해 i 이후의 모든 소수가 아닌 값들은 이미 지워짐. 
    // 더 이상 반복문 불필요
    for(int i = 2; i * i < _m; i++){ 
        if (!arr[i]) continue;

        // 만약 i가 3일 때, 3 * 2는 이미 지워진 상태
        // 즉 i * i 이전의 녀석들은 이미 지워졌으므로 보지 않아도 됨.
        // j ++ -> j+=i로 변경한 이유도 마찬가지임
        for(int j = i * i; j < _m; j += i) {
            arr[j] = false;
        }
    }
}
```