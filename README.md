# HeapBinaryTree
A self-balancing binary tree that sorts all the words from a dictionary, and then organizes them into categories based on the 
rotations that were necessary. 


It uses a heap to implement a binary search tree, as elements are inserted and the tree becomes imbalanced, it balances itself.

Input: It takes in a dictionary of words, seperated by a word per line. 

Output: It outputs the total time it took the program to run, as well as every word that took specific rotations to balance in seperate lists.  It outputs a word in a list if it took one right exterior, left exterior, right interior, or left interior rotation. As well as any combination of 2 rotations.  Not listed is words that needed no rotations, or words that needed more than two rotations.
