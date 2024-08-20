/*
https://leetcode.com/problems/stone-game-ii

Runtime: 118ms (beats 12.34%)
Memory: 17.18MB (beats 39.33%)
*/

#define MAX(a, b) (a < b ? b : a)

class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int N = piles.size();
        vector<int> pPiles(N + 1, 0);
        pPiles[1] = piles[0];
        for (int i = 1; i != N; ++i) {
            pPiles[i+1] = pPiles[i] + piles[i];
        }

        std::map<std::pair<int, int>, int> cache;

        std::function<int(int, int)> minmax = [&minmax, &pPiles, N, &cache](
            int pilesTaken,
            int M
        ) -> int {
            int pilesLeft = N - pilesTaken;

            if (pilesLeft == 0) return 0;

            const auto cacheKey = std::make_pair(pilesTaken, M);
            if (cache.contains(cacheKey)) {
                return cache[cacheKey];
            }

            int playerBest = -1;
            for (int x = 1; x <= 2*M && (pilesLeft - x) >= 0; ++x) {
                int stones = pPiles[pilesTaken + x] - pPiles[pilesTaken];
                int otherBest = minmax(pilesTaken + x, MAX(x, M));
                int newBest = stones + (pPiles[N] - pPiles[pilesTaken+x] - otherBest);

                if (newBest > playerBest) {
                    playerBest = newBest;
                }
            }

            cache[cacheKey] = playerBest;
            return playerBest;
        };

        return minmax(0, 1);
    }
};
