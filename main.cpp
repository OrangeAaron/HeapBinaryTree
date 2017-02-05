/*
Aaron Wilson
10/28/2016
BalancedBinaryHeap
*/
using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include "TimeFunctions.h"
#include "TreeFunctions.h"


void printList(ofstream& listOutward, vector<string> categoryList, string listName){
listOutward << endl << endl << listName << " list:" << endl << "    ";
  for (int i = 0; i<categoryList.size(); i++)
  {
    listOutward << categoryList.at(i) << " ";
  }
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

  printList(coutward, RE, "RE");
  printList(coutward, RI, "RI");
  printList(coutward, LE, "LE");
  printList(coutward, LI, "LI");
  printList(coutward, RERE, "RERE");
  printList(coutward, RERI, "RERI");
  printList(coutward, RELE, "RELE");
  printList(coutward, RELI, "RELI");
  printList(coutward, RIRE, "RIRE");
  printList(coutward, RIRI, "RIRI");
  printList(coutward, RILE, "RILE");
  printList(coutward, RILI, "RILI");
  printList(coutward, LERE, "LERE");
  printList(coutward, LERI, "LERI");
  printList(coutward, LELE, "LELE");
  printList(coutward, LELI, "LELI");
  printList(coutward, LIRE, "LIRE");
  printList(coutward, LIRI, "LIRI");
  printList(coutward, LILE, "LILE");
  printList(coutward, LILI, "LILI");

  coutward.close();
  return 0;
}


