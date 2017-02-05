#ifndef TIMEFUNCTIONS_H_INCLUDED
#define TIMEFUNCTIONS_H_INCLUDED
#include <fstream>
#include <iomanip>
#include <time.h>     // for the clock function


float getTime ()
{
   float time;
   time = clock();  // returns # of CPU ticks since process began
   time=time / CLOCKS_PER_SEC; // Convert to # of seconds
   return time;
}


void printTime(string sortName, float start, float finish, ofstream &outman) {
      float diff;
      outman << setw(18) << left << sortName;
      diff = finish - start;
      outman << " " << left << setw(12) << showpoint <<setprecision(8) << diff << " " << endl;
}

#endif // TIMEFUNCTIONS_H_INCLUDED
