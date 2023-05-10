#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int parent[MAX_N];  
int rank[MAX_N];    

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}


void merge(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px != py) {
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else {
            parent[py] = px;
            if (rank[px] == rank[py]) {
                rank[px]++;
            }
        }
    }
}

int makeConnected(int n, int** connections, int connectionsSize, int* connectionsColSize){
    if (connectionsSize < n - 1) {
        return -1;  
    }
    
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    
    for (int i = 0; i < connectionsSize; i++) {
        int x = connections[i][0];
        int y = connections[i][1];
        merge(x, y);
    }
   
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (parent[i] == i) {
            count++;
        }
    }
    
    return count - 1;
}

int main() {
    int n = 4;
    int connectionsSize = 3;
    int connections[3][2] = {{0,1}, {0,2}, {1,2}};
    int* connectionsPtr[3] = {connections[0], connections[1], connections[2]};
    int connectionsColSize[3] = {2, 2, 2};
    int minCables = makeConnected(n, connectionsPtr, connectionsSize, connectionsColSize);
    printf("%d\n", minCables); 
    return 0;
}