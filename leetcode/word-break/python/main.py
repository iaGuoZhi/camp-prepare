from typing import List

class Solution:
    def wordBreak(self, s:str, wordDict: List[str]) -> bool:
        dp= [False]*(len(s)+1)
        dp[0]=True

        for i in range(len(s)+1):
            for j in range(i):
                if dp[j] and s[j:i] in wordDict:
                    dp[i]=True

        return dp[len(s)]

if __name__ == "__main__":
    s="leetcode"
    wordDict= {"leet","code"}
    print(Solution.wordBreak(s, wordDict))
    pass