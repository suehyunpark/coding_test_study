class Solution {
    public int climbStairs(int n) {
        if (n == 1)
            return 1;
        int[] steps = new int[n+1];
        steps[1] = 1;
        steps[2] = 2;
        for (int i=3; i<=n; ++i)
            steps[i] = steps[i-1] + steps[i-2]; // either climb 1 step or 2 steps
        return steps[n];
    }
}