#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // Edge Case: If start or end contains a thief, safeness factor is 0
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
            return 0;
        }
        
        // Step 1: Multi-Source BFS to compute minimum distance to any thief
        vector<vector<int>> dist(n, vector<int>(n, 1e9));
        queue<pair<int, int>> q;
        
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 1) {
                    dist[r][c] = 0;
                    q.push({r, c});
                }
            }
        }
        
        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            
            for (auto& [dr, dc] : directions) {
                int nr = r + dr;
                int nc = c + dc;
                
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && dist[nr][nc] == 1e9) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
        
        // Step 2: Modified Dijkstra using a Max-Heap
        // priority_queue in C++ acts as a Max-Heap by default
        priority_queue<vector<int>> pq; 
        pq.push({dist[0][0], 0, 0}); // stores: {safeness, r, c}
        
        vector<vector<int>> maxSafenessTo(n, vector<int>(n, -1));
        maxSafenessTo[0][0] = dist[0][0];
        
        while (!pq.empty()) {
            auto curr = pq.top();
            pq.pop();
            
            int currSafe = curr[0];
            int r = curr[1];
            int c = curr[2];
            
            if (r == n - 1 && c == n - 1) {
                return currSafe;
            }
            
            for (auto& [dr, dc] : directions) {
                int nr = r + dr;
                int nc = c + dc;
                
                if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                    int nextSafe = min(currSafe, dist[nr][nc]);
                    
                    if (nextSafe > maxSafenessTo[nr][nc]) {
                        maxSafenessTo[nr][nc] = nextSafe;
                        pq.push({nextSafe, nr, nc});
                    }
                }
            }
        }
        
        return 0;
    }
};