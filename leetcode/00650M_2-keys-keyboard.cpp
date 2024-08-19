/*
https://leetcode.com/problems/2-keys-keyboard

Runtime: 13ms (beats 39.85%)
Memory: 11.93MB (beats 25.27%)
*/

#define MAX_N 1000

class Solution {
public:
    int minSteps(int n) {
        if (n == 1) return 0;

        // dp[X][Y] = N
        // X - size of the clipboard
        // Y - number of As on the screen
        // N - # of ops to get here
        int dp[MAX_N+1][MAX_N+1] = {};
        dp[0][1] = 0;
        dp[1][1] = 1;

        for (int cb = 1; cb <= n; ++cb) {
            int N = cb;
            int ops = dp[cb][N];
            // if (ops == 0) throw std::invalid_argument("must be impossible");
            while (N <= n) {
                if (dp[cb][N] == 0 || dp[cb][N] > ops) dp[cb][N] = ops;
                if (dp[N][N] == 0 || dp[N][N] > ops + 1) dp[N][N] = ops + 1;

                N += cb;
                ops += 1;
            }
        }

        int min = std::numeric_limits<int>::max();
        for (int cb = 1; cb <= n; ++cb) {
            int x = dp[cb][n];
            if (x > 0 && x < min) min = x;
        }
        return min;
    }
};
