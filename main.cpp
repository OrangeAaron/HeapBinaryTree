/*
Aaron Wilson
10/28/2016
BalancedBinaryHeap
*/
using namespace std;
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <fstream>
#include "TimeFunctions.h"
#include <algorithm>
#include <math.h>

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




int main()
{
  float start, finish;
  start = getTime();
  //Declaring a list of tree categories
  //             rr   rl  ll  lr
  //              1   2   3   4   5     6     7     8     9     10    11     12   13     14    15   16    17    18   19     20
  vector<string> RE, RI, LE, LI, RERE, RERI, RELE, RELI, RIRE, RIRI, RILE, RILI, LERE, LERI, LELE, LELI, LIRE, LIRI, LILE, LILI;
  //reading in each word
  unsigned char category;
  string word;
  ifstream dictionary;
  dictionary.open("american");
  while (getline(dictionary, word))
  {
    category = BuildTree(word);
    switch (category)
    {
    case 1:
      RE.push_back(word);
      break;
    case 2:
      RI.push_back(word);
      break;
    case 3:
      LE.push_back(word);
      break;
    case 4:
      LI.push_back(word);
      break;
    case 5:
      RERE.push_back(word);
      break;
    case 6:
      RERI.push_back(word);
      break;
    case 7:
      RELE.push_back(word);
      break;
    case 8:
      RELI.push_back(word);
      break;
    case 9:
      RIRE.push_back(word);
      break;
    case 10:
      RIRI.push_back(word);
      break;
    case 11:
      RILE.push_back(word);
      break;
    case 12:
      RILI.push_back(word);
      break;
    case 13:
      LERE.push_back(word);
      break;
    case 14:
      LERI.push_back(word);
      break;
    case 15:
      LELE.push_back(word);
      break;
    case 16:
      LELI.push_back(word);
      break;
    case 17:
      LIRE.push_back(word);
      break;
    case 18:
      LIRI.push_back(word);
      break;
    case 19:
      LILE.push_back(word);
      break;
    case 20:
      LILI.push_back(word);
      break;
    }
    firstCategory = 0;
    secondCategory = 0;
  }
  dictionary.close();
  finish = getTime();
  ofstream coutward ("classified.dat");
  printTime("Records balanced and sorted", start, finish, coutward);
  coutward << endl << endl << "RE list:" << endl << "    ";
  for (int i = 0; i<RE.size(); i++)
  {
    coutward << RE.at(i) << " ";
  }
  coutward << endl << endl << "RI list:" << endl << "    ";
  for (int i = 0; i<RI.size(); i++)
  {
    coutward << RI.at(i) << " ";
  }
  coutward << endl << endl << "LE list:" << endl << "    ";
  for (int i = 0; i<LE.size(); i++)
  {
    coutward << LE.at(i) << " ";
  }
  coutward << endl << endl << "LI list:" << endl << "    ";
  for (int i = 0; i<LI.size(); i++)
  {
    coutward << LI.at(i) << " ";
  }
  coutward << endl << endl << "RERE list:" << endl << "    ";
  for (int i = 0; i<RERE.size(); i++)
  {
    coutward << RERE.at(i) << " ";
  }
  coutward << endl << endl << "RERI list:" << endl << "    ";
  for (int i = 0; i<RERI.size(); i++)
  {
    coutward << RERI.at(i) << " ";
  }
  coutward << endl << endl << "RELE list:" << endl << "    ";
  for (int i = 0; i<RELE.size(); i++)
  {
    coutward << RELE.at(i) << " ";
  }
  coutward << endl << endl << "RELI list:" << endl << "    ";
  for (int i = 0; i<RELI.size(); i++)
  {
    coutward << RELI.at(i) << " ";
  }
  coutward << endl << endl << "RIRE list:" << endl << "    ";
  for (int i = 0; i<RIRE.size(); i++)
  {
    coutward << RIRE.at(i) << " ";
  }
  coutward << endl << endl << "RIRI list:" << endl << "    ";
  for (int i = 0; i<RIRI.size(); i++)
  {
    coutward << RIRI.at(i) << " ";
  }
  coutward << endl << endl << "RILE list:" << endl << "    ";
  for (int i = 0; i<RILE.size(); i++)
  {
    coutward << RILE.at(i) << " ";
  }
  coutward << endl << endl << "RILI list:" << endl << "    ";
  for (int i = 0; i<RILI.size(); i++)
  {
    coutward << RILI.at(i) << " ";
  }
  coutward << endl << endl << "LERE list:" << endl << "    ";
  for (int i = 0; i<LERE.size(); i++)
  {
    coutward << LERE.at(i) << " ";
  }
  coutward << endl << endl << "LERI list:" << endl << "    ";
  for (int i = 0; i<LERI.size(); i++)
  {
    coutward << LERI.at(i) << " ";
  }
  coutward << endl << endl << "LELE list:" << endl << "    ";
  for (int i = 0; i<LELE.size(); i++)
  {
    coutward << LELE.at(i) << " ";
  }
  coutward << endl << endl << "LELI list:" << endl << "    ";
  for (int i = 0; i<LELI.size(); i++)
  {
    coutward << LELI.at(i) << " ";
  }
  coutward << endl << endl << "LIRE list:" << endl << "    ";
  for (int i = 0; i<LIRE.size(); i++)
  {
    coutward << LIRE.at(i) << " ";
  }
  coutward << endl << endl << "LIRI list:" << endl << "    ";
  for (int i = 0; i<LIRI.size(); i++)
  {
    coutward << LIRI.at(i) << " ";
  }
  coutward << endl << endl << "LILE list:" << endl << "    ";
  for (int i = 0; i<LILE.size(); i++)
  {
    coutward << LILE.at(i) << " ";
  }
  coutward << endl << endl << "LILI list:" << endl << "    ";
  for (int i = 0; i<LILI.size(); i++)
  {
    coutward << LILI.at(i) << " ";
  }
  coutward.close();
  return 0;
}


