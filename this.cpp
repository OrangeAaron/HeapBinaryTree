
using namespace std;
#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include "TimeFunctions.h"
#include <algorithm>


string lastWord;
unsigned char firstCategory, secondCategory;

int getLeftChildIndex(int index)
{

    return (2*index)+1;
}

int getRightChildIndex(int index)
{
    return (2*index)+2;
}
int getParentIndex(int index)
{
    return (index-1)/2;
}
void padString(string &Tree, int index)
{
    Tree.resize(index);
    Tree += std::string(Tree.size() - index, '\0');
}

unsigned char insertOrderedPoint(string &Tree, char CharToInsert, int index)
{
    //calculate and add needed space to string
    padString(Tree, index);
    unsigned char category = 0;
    if(Tree[index] == '\0')
    {
        Tree[index] = CharToInsert;
    }
    else if (CharToInsert < Tree[index])
    {
        insertOrderedPoint(Tree, CharToInsert, getLeftChildIndex(index));
    }
    else
    {
        insertOrderedPoint(Tree, CharToInsert, getRightChildIndex(index));
    }
    // category = balance(Tree, index);
    return category;
}
    unsigned char insertToTree(string &Tree, char CharToInsert)
    {
        unsigned char category = 0;
        if(Tree.empty())
        {
            Tree += CharToInsert;
        }
        else
        {
            category = insertOrderedPoint(Tree, CharToInsert, 0);
        }
        return category;
    }

//To insert each character in the string one at a time into the heap
    unsigned char BuildTree(string word)
    {
        int category = 0;
        string Tree, charList;
        for(int i = 0; i < word.length(); i++)
        {
            if(word[i] != '\'' && charList.find(word[i])==string::npos)
            {
                word[i] = tolower(word[i]);
                charList += word[i];
            }
        }
        if(lastWord==charList)
        {
            return category;
        }
        for(int i = 0; i < charList.length(); i++)
        {
            category = insertToTree(Tree, charList[i]);
        }
        balanceNbrCheck = 0;
        lastWord = charList;
        return category;
    }



int main()
{
    //reading in each word
    ifstream dictionary;
    string word;
    dictionary.open("american");
    while(getline(dictionary, word))
    {
        unsigned char category = BuildTree(word);
        firstCategory = 0;
        secondCategory = 0;
    }
    dictionary.close();

    return 0;
}


