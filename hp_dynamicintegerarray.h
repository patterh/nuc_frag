
#ifndef _DYNINTAR_H
#define _DYNINTAR_H

#include <cstring>
#include "hp_quicksort.h"

using namespace std;

class HPDynamicIntArray
{
public:
HPDynamicIntArray(int size = 10, int delta = 10);// size is initial size
HPDynamicIntArray(const HPDynamicIntArray&);     // delta is by how much array grows
~HPDynamicIntArray();

int* GetArray();
int GetArrayLength();
int GetEntry(int index);
int GetIndex(int entry);
int AddInt(int number);
int AddArray(HPDynamicIntArray* addarray);
int AddArray(int* addarray, int length);
void OverWriteEntry(int new_number, int index);
void DeleteEntry(int index);
int GetMembers();
void EmptyArray(int size); // size is the new upperlimit of the emptied array
void SortArray();
void AddConstant(int constant); // Add constant int to each entry
void BlankArray(); // sets each member of array to 0
void MakeBlankArray(int arraysize, int blanknumber);
void SetEntry(int number, int index); // set entry at index to number (same as OverWriteEntry())

protected:
int* array;
int members;
int delta;
int upperlimit;

private:

HPDynamicIntArray& operator=(const HPDynamicIntArray&);
};

// Inlines

inline int HPDynamicIntArray::GetMembers()
{
return(members);
}

inline int HPDynamicIntArray::GetArrayLength()
{
return(members);
}

inline int* HPDynamicIntArray::GetArray()
{
return(array);
}

#endif
