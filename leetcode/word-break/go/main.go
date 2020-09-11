package main

import "fmt"

func wordBreak(s string, wordDict []string) bool {
	wordDictSet := make(map[string]bool)

	for _, s := range wordDict {
		wordDictSet[s] = true
	}

	dp := make([]bool, len(s)+1)
	dp[0] = true

	for i := 1; i <= len(s); i++ {
		for j := 0; j < i; j++ {
			if dp[j] && wordDictSet[s[j:i]] {
				dp[i] = true
			}
		}
	}
	return dp[len(s)]
}

func main() {
	s := "leetcode"
	wordDict := []string{"leet", "code"}

	fmt.Println(wordBreak(s, wordDict))
}
