/*
This is a classic problem that seems tricky at first due to the size of n (up to 10⁹), 
but the key is to navigate a virtual lexicographical tree (prefix tree / trie) rather 
than actually sorting or storing all values.


Imagine all numbers from 1 to n are organized in lexicographical order, like a tree:

        ""
     /  |  \  ...
    1   2   3  ...
   /|\  |
 10 11 12...

*/ 



#include <bits/stdc++.h>
using namespace std;

class Solution {
    private:
    // Function to count how many numbers are in the range [1, n] that start with prefix curr
    int countSteps(long long prefix, long long n) {
        long long steps = 0;
        long long curr = prefix;
        long long next = prefix + 1; // next prefix
        while(curr <= n) {
            // Count how many numbers are in the range [curr, next) that are <= n
            steps += min(n + 1L, next) - curr;
            curr *= 10; // move to the next level in the trie
            next *= 10; // next prefix at this level
        }
        return steps;
    }

    public:
        int findKthNumber(int n, int k) {
            int curr = 1;
            k -= 1; //since we start from 1, we need to adjust k

            while(k > 0) {   
                int steps = countSteps(curr, n);
                if(steps <= k) {
                    curr++;
                    k -= steps; // move to the next prefix
                } else {
                    curr *= 10; // go deeper in the trie
                    k--; // we are using one step to go deeper
                }
            }
            return curr;
    }
};
int main()
{
}
