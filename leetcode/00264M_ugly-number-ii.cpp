/*
https://leetcode.com/problems/ugly-number-ii

Runtime: 25ms (beats 39.66%)
Memory: 17.6MB (beats 35.02%)
*/

class Solution {
public:
  int nthUglyNumber(int n) {
    std::queue<unsigned long> two;
    std::queue<unsigned long> three;
    std::queue<unsigned long> five;

    int i = 1;
    int x = 1;
    while (i < n) {
      two.push(x);
      three.push(x);
      five.push(x);
      int x2 = two.front()   * 2;
      int x3 = three.front() * 3;
      int x5 = five.front()  * 5;
      if (x2 <= x3 && x2 <= x5) {
        x = x2;
        two.pop();
        if (x2 == x3) three.pop();
        if (x2 == x5) five.pop();
      } else if (x3 <= x2 && x3 <= x5) {
        x = x3;
        three.pop();
        if (x3 == x2) two.pop();
        if (x3 == x5) five.pop();
      } else {
        x = x5;
        five.pop();
        if (x5 == x2) two.pop();
        if (x5 == x3) three.pop();
      }
      ++i;
    }

    return x;
  }
};
