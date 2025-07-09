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

static int depth_limit_count = 0;

class Node {
public:
    int start_time;
    int end_time;
    int node_type; // 0 -> 일반 회의 노드, 1 -> start 노드, 2-> end 노드
    vector<Node*> parent_nodes;
    vector<Node*> child_nodes;
    // Node* next_node;
    int max_available_meeting_counts = 0;
    
    Node(int start_time, int end_time, int node_type=0): start_time(start_time), end_time(end_time), node_type(node_type) {}

    void bottom_up(){
        if (this->parent_nodes.empty()) return;
        
        for (Node* parent_node : this->parent_nodes){
            int next_counts = this->max_available_meeting_counts;
            if (this->node_type != 2) next_counts++;
            parent_node->max_available_meeting_counts = max(parent_node->max_available_meeting_counts, next_counts);
            // if (parent_node->max_available_meeting_counts < next_counts) {
            //     parent_node->max_available_meeting_counts = next_counts;
            //     parent_node->next_node = this; // 디버그용
            // }
            parent_node->bottom_up();
        }
    }

    // 디버그 함수
    // void print_complete_dir(){
    //     if (depth_limit_count > 20) {
    //         cout << "\n\n재귀적 무한 루프 발생";
    //         return;
    //     }
    //     // cout << this->node_type;
    //     if (this->node_type != 1 and this->node_type != 2) cout << '(' << this->start_time << ", " << this->end_time << ") ";
    //     depth_limit_count ++;
    //     if (this->next_node->node_type != 2) {
    //         cout << " -> ";
    //         this->next_node->print_complete_dir();
    //     }
    // }
};

void set_relation(Node* parent_node, Node* child_node) {
    parent_node->child_nodes.push_back(child_node);
    child_node->parent_nodes.push_back(parent_node);
}

// start, end 노드 만들고 단방향 그래프 만든 뒤 end 노드부터 위로 올리면 될 거 같은데용
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Node* start_node = new Node(0,0,1); // 시작 노드
    Node* end_node = new Node(0,0,2);

    set<int> known_end_times;
    map<int, vector<Node*>> end_time_to_nodes;
    // vector<Node*> nodes;

    // 노드가 추가될 때마다, 어떤 노드의 자식이 될 수 있는지 확인
    // 인덱스 접근 가능한 map(end_time => vector, 끝나는 시간을 키로 하여 끝나는 시간이 같은 노드끼리 모아둔 map)에 접근
    // 알고리즘
    // 대충 새로 생긴 Node의 시작 시간을 보고 배열 인덱스가 start_time과 같거나 작은 모든 노드에 대해 새로 생긴 Node의 자식이 됨
    int n;
    cin >> n;

    int start_time;
    int end_time;

    for(int i = 0; i < n; i++) {
        cin >> start_time >> end_time;
        Node* temp = new Node(start_time, end_time);
        // temp->next_node = end_node;
        set_relation(start_node, temp);
        set_relation(temp, end_node);
        known_end_times.insert(end_time);
        end_time_to_nodes[end_time].push_back(temp);
        // nodes.push_back(temp);
    }

    for(auto it: end_time_to_nodes){
        vector<Node*> nodes = it.second;
        for(Node* node: nodes){
            start_time = node->start_time;
            for(int e: known_end_times){
                if (e > start_time) break;
                for(Node* parent_node: end_time_to_nodes[e]) {
                    set_relation(parent_node, node);
                }
            }
        }
    }

    end_node->bottom_up();
    cout << start_node->max_available_meeting_counts;

    //디버그용
    // cout << "\n\n";
    // start_node->next_node->print_complete_dir();

    for(auto it: end_time_to_nodes){
        vector<Node*> nodes = it.second;
        for(Node* node: nodes){
            delete node;
        }
    }
    delete start_node;
    delete end_node;

    return 0;
}