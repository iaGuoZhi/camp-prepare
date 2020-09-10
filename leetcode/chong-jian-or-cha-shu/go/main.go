package main

import "fmt"

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func buildTree(preorder []int, inorder []int) *TreeNode {
	for k := range inorder {
		if inorder[k] == preorder[0] { //中序遍历 root (index=k)
			return &TreeNode{
				Val: preorder[0],
				//Val: inorder[root],
				Left:  buildTree(preorder[1:k+1], inorder[0:k]),
				Right: buildTree(preorder[k+1:], inorder[k+1:]),
			}
		}
	}
	return nil
}

func main() {
	arr1 := []int{3, 9, 20, 15, 7}
	arr2 := []int{9, 3, 15, 20, 7}
	tree := buildTree(arr1, arr2)
	fmt.Println(tree.Val)
}
