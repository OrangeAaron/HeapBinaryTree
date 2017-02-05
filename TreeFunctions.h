#ifndef TREEFUNCTIONS_H_INCLUDED
#define TREEFUNCTIONS_H_INCLUDED

#include <algorithm>
#include <math.h>
#include <vector>
#include <string>
string lastWord;
int balanceNbrCheck = 0;
unsigned char firstCategory, secondCategory;
string copyTree(1000, ' ');

int getLeftChildIndex(int index)
{

  return (2 * index) + 1;
}

int getRightChildIndex(int index)
{
  return (2 * index) + 2;
}

int getParentIndex(int index)
{
  return (index - 1) / 2;
}


//Allocating space for the characters to be inserted in the heap
void padString(string &Tree, int index)
{
    while (index > Tree.size()-1)
    {
      Tree += ' ';
    }
}

void moveTreeDownLeft(string &Tree, int fromIndex)
{
  if (Tree[fromIndex] != ' ')
  {
    padString(Tree, getRightChildIndex(fromIndex));
    if (Tree[getLeftChildIndex(fromIndex)] == ' ' && Tree[getRightChildIndex(fromIndex)] == ' ')
    {
      Tree[fromIndex + (pow(2, floor(log2(fromIndex + 1))))] = Tree[fromIndex];
    }
    else
    {
      moveTreeDownLeft(Tree, getLeftChildIndex(fromIndex));
      moveTreeDownLeft(Tree, getRightChildIndex(fromIndex));
      Tree[fromIndex + (pow(2, floor(log2(fromIndex + 1))))] = Tree[fromIndex];
    }
  }
}
void moveTreeDownRight(string &Tree, int fromIndex)
{
  if (Tree[fromIndex] != ' ')
  {

    int crazyMath = fromIndex + (pow(2, (floor(log2(fromIndex + 1))) + 1));
    padString(Tree, crazyMath);
    if (Tree[getLeftChildIndex(fromIndex)] == ' ' && Tree[getRightChildIndex(fromIndex)] == ' ')
    {
      Tree[crazyMath] = Tree[fromIndex];
    }
    else
    {
      moveTreeDownRight(Tree, getRightChildIndex(fromIndex));
      moveTreeDownRight(Tree, getLeftChildIndex(fromIndex));
      Tree[fromIndex + (pow(2, (floor(log2(fromIndex + 1)) + 1)))] = Tree[fromIndex];
    }
  }
}
void moveTreeUpLeft(string &Tree, int fromIndex)
{
  padString(Tree, getRightChildIndex(fromIndex));
  if (Tree[fromIndex] != ' ')
  {
    Tree[(fromIndex / 2) - 1] = Tree[fromIndex];
    Tree[fromIndex] = ' ';
    moveTreeUpLeft(Tree, getLeftChildIndex(fromIndex));
    moveTreeUpLeft(Tree, getRightChildIndex(fromIndex));
  }
}
void moveTreeUpRight(string &Tree, int fromIndex)
{

  padString(Tree, getRightChildIndex(fromIndex));
  if (Tree[fromIndex] != ' ')
  {
    Tree[(fromIndex / 2)] = Tree[fromIndex];
    Tree[fromIndex] = ' ';
    moveTreeUpRight(Tree, getLeftChildIndex(fromIndex));
    moveTreeUpRight(Tree, getRightChildIndex(fromIndex));
  }
}
void swapPoint(string &Tree, int first, int second)
{
  while((second > Tree.length()) || first > Tree.length()) {
    Tree += ' ';
  }
    char t = Tree[first];
    Tree[first] = Tree[second];
    Tree[second] = t;
}




// rotates (t) -- rotate the tree anchored at `t'
void rotateLeftLeft(string &Tree, int pivotIndex)
{
  padString(Tree, getRightChildIndex(pivotIndex));
  moveTreeDownRight(Tree, getRightChildIndex(pivotIndex)); //move h down
  Tree[getRightChildIndex(pivotIndex)] = Tree[pivotIndex]; // move g down
  swapPoint(Tree, getRightChildIndex(getLeftChildIndex(pivotIndex)), getRightChildIndex(getLeftChildIndex(pivotIndex)) + 1);  // move n over
  moveTreeUpRight(Tree, getLeftChildIndex(pivotIndex));

}
void rotateRightRight(string &Tree, int pivotIndex)
{
  moveTreeDownLeft(Tree, getLeftChildIndex(pivotIndex));  // move a down
  padString(Tree, getLeftChildIndex(pivotIndex));
  Tree[getLeftChildIndex(pivotIndex)] = Tree[pivotIndex];   // move d down
  swapPoint(Tree, getLeftChildIndex(getRightChildIndex(pivotIndex)), getLeftChildIndex(getRightChildIndex(pivotIndex)) - 1);  // move n over
  moveTreeUpLeft(Tree, getRightChildIndex(pivotIndex));
}
void rotateLeftRight(string &Tree, int pivotIndex)
{
  rotateRightRight(Tree, getLeftChildIndex(pivotIndex));
  rotateLeftLeft(Tree, pivotIndex);
}
void rotateRightLeft(string &Tree, int pivotIndex)
{
  rotateLeftLeft(Tree, getRightChildIndex(pivotIndex));
  rotateRightRight(Tree, pivotIndex);
}



int getHeight(string &Tree, int index)
{
  if (index > Tree.length() || Tree[index] == ' ')
  {
    return -1;
  }
  else
  {
    return max(getHeight(Tree, getLeftChildIndex(index)), getHeight(Tree, getRightChildIndex(index))) + 1;
  }
}

unsigned char balance(string &Tree, int index)
{
  if (Tree[index] == ' ')
  {
    return 0;
  }
  int height = getHeight(Tree, index);
  int lheight = getHeight(Tree, getLeftChildIndex(index));
  int rheight = getHeight(Tree, getRightChildIndex(index));
  if (lheight - rheight > 1)   //
  {
    if (getHeight(Tree, getLeftChildIndex(getLeftChildIndex(index)))  > getHeight(Tree, getRightChildIndex(getLeftChildIndex(index))))
    {
      rotateLeftLeft(Tree, index); // single rotate
      ++balanceNbrCheck;
      return 3;
    }
    else
    {
      rotateLeftRight(Tree, index);  // double rotate
      ++balanceNbrCheck;
      return 4;
    }
  }
  else if (rheight - lheight > 1)
  {
    if (getHeight(Tree, getRightChildIndex(getRightChildIndex(index)))  > getHeight(Tree, getLeftChildIndex(getRightChildIndex(index))))
    {
      rotateRightRight(Tree, index);        // single rotate
      ++balanceNbrCheck;
      return 1;
    }
    else
    {
      rotateRightLeft(Tree, index);   // double rotate
      ++balanceNbrCheck;
      return 2;
    }
  }
  else
  {
    return 0;
  }
}





//inserting the character at the correct place in the binary heap
unsigned char insertOrderedPoint(string &Tree, char CharToInsert, int index)
{
  //calculate and add needed space to string
  padString(Tree, index);
  unsigned char category = 0;
  if (balanceNbrCheck < 2)
  {
    if (Tree[index] == ' ')
    {
      Tree[index] = CharToInsert;
    }
    else if (CharToInsert < Tree[index])
    {
      category = insertOrderedPoint(Tree, CharToInsert, getLeftChildIndex(index));
    }
    else
    {
      category = insertOrderedPoint(Tree, CharToInsert, getRightChildIndex(index));
    }
    if (balanceNbrCheck == 2) {
      if (category == 0) return 21;
      return category;
    }
    if (balanceNbrCheck < 2)
    {
      category = balance(Tree, index);
      if (category != 0)
      {
        if (balanceNbrCheck == 1)firstCategory = category;
        if (balanceNbrCheck == 2)
        {
          secondCategory = category;
          if (firstCategory == 1)
          {
            if (secondCategory == 1) return 5;
            else if (secondCategory == 2) return 6;
            else if (secondCategory == 3) return 7;
            else return 8;
          }
          else if (firstCategory == 2)
          {
            if (secondCategory == 1) return 9;
            else if (secondCategory == 2) return 10;
            else if (secondCategory == 3) return 11;
            else return 12;
          }
          else if (firstCategory == 3)
          {
            if (secondCategory == 1) return 13;
            else if (secondCategory == 2) return 14;
            else if (secondCategory == 3) return 15;
            else return 16;
          }
          else
          {
            if (secondCategory == 1) return 17;
            else if (secondCategory == 2) return 18;
            else if (secondCategory == 3) return 19;
            else return 20;
          }
        }
      }
      return category;
    }
  }
  return 21;
}


//To insert each character in the string one at a time into the heap
unsigned char BuildTree(string word)
{
  int category = 0;
  string Tree = copyTree;
  string charList = word;
  charList.erase(unique(charList.begin(), charList.end()), charList.end());
  for (int i = 0; i < charList.length(); i++)
  {
      charList[i] = tolower(charList[i]);
  }
  if (lastWord == charList)
  {
    return category;
  }
  for (int i = 0; i < charList.length(); i++)
  {
    category = insertOrderedPoint(Tree, charList[i], 0);
  }
  balanceNbrCheck = 0;
  lastWord = charList;
  return category;
}


#endif // TREEFUNCTIONS_H_INCLUDED
