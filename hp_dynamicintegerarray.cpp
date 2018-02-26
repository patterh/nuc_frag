
#include "hp_dynamicintegerarray.h"


HPDynamicIntArray::HPDynamicIntArray(int size, int number)
{
delta = number;
upperlimit = size;
array = new int[upperlimit];
members = 0;
}

HPDynamicIntArray::~HPDynamicIntArray()
{
delete [] array;
}

HPDynamicIntArray::HPDynamicIntArray(const HPDynamicIntArray& passedobject)
{
delta = passedobject.delta;
upperlimit = passedobject.upperlimit;
members = passedobject.members;
array = new int[passedobject.upperlimit];
for(int x = 0; x < passedobject.members; x++)
	array[x] = passedobject.array[x];

}

int HPDynamicIntArray::AddInt(int number)
{

if(members+1 > upperlimit)
	{
	int* temp = new int[members];
	for(int x = 0; x < members; x++)
		temp[x] = array[x];
	delete [] array;
	array = new int[members+delta];
	upperlimit = members+delta;
	for(int y = 0; y < members; y++)
		array[y] = temp[y];
	array[members] = number;
	delete [] temp;
	}
else
	{
	array[members] = number;
	}
return(++members);
}

int HPDynamicIntArray::AddArray(HPDynamicIntArray* addarray)
{
int newmembers = addarray->GetMembers();
if(members+newmembers > upperlimit)
	{
	int* temp = new int[members];
	for(int x = 0; x < members; x++)
		temp[x] = array[x];
	delete [] array;
	upperlimit = members+delta*((newmembers+delta-1)/delta);
	array = new int[upperlimit];
	for(int y = 0; y < members; y++)
		array[y] = temp[y];
   for(int z = 0; z < newmembers; z++)
   	array[members+z] = addarray->GetEntry(z);
	delete [] temp;
	}
else
	{
	for(int z = 0; z < newmembers; z++)
   	array[members+z] = addarray->GetEntry(z);
	}
return(members += newmembers);
}

int HPDynamicIntArray::AddArray(int* addarray, int length)
{
int newmembers = length;
if(members+newmembers > upperlimit)
	{
	int* temp = new int[members];
	for(int x = 0; x < members; x++)
		temp[x] = array[x];
	delete [] array;
	upperlimit = members+delta*((newmembers+delta-1)/delta);
	array = new int[upperlimit];
	for(int y = 0; y < members; y++)
		array[y] = temp[y];
   for(int z = 0; z < newmembers; z++)
   	array[members+z] = addarray[z];
	delete [] temp;
	}
else
	{
	for(int z = 0; z < newmembers; z++)
   	array[members+z] = addarray[z];
	}
return(members += newmembers);
}

void HPDynamicIntArray::EmptyArray(int size)
{
delete [] array;
array = new int[size];
upperlimit = size;
members = 0;
}

int HPDynamicIntArray::GetEntry(int number)
{
if(number < members)
	return(array[number]);
else
	return(members);
}

void HPDynamicIntArray::OverWriteEntry(int new_number, int index)
{
if(index < members)
	{
   array[index] = new_number;
	}
}

void HPDynamicIntArray::DeleteEntry(int index)
{
if(index < members)
	{
	if(index < members-1)
   		{
		for(int x = index; x < members-1; x++)
			array[x] = array[x+1];
		array[members-1] = 0;
   		}
   else if(index == members-1)
   	array[index] = 0;
   members--;
   }
}

void HPDynamicIntArray::SortArray()
{
HPQuickSort* sortobject = new HPQuickSort();
sortobject->QuickSort(array, 0, members-1);
delete sortobject;
}

void HPDynamicIntArray::AddConstant(int constant)
{
for(int x = 0; x < members; x++)
	array[x] = array[x] + constant;
}

void HPDynamicIntArray::BlankArray()
{
for(int x = 0; x < members; x++)
	array[x] = 0;
}

void HPDynamicIntArray::SetEntry(int number, int index)
{
if(index < members)
	{
   array[index] = number;
	}
}

int HPDynamicIntArray::GetIndex(int entry)
{
int x = 0;
while(x < members && entry != array[x])
	x++;
if(x < members)
	return(x);
else
	return(members);
}

void HPDynamicIntArray::MakeBlankArray(int arraysize, int blanknumber)
{
if(array)
	delete [] array;
int res = arraysize%delta;
if(!res)
	upperlimit = arraysize;
else
	upperlimit = (1 + arraysize/delta)*delta;
array = new int[upperlimit];
for(int x = 0; x < arraysize; x++)
	array[x] = blanknumber;
members = arraysize;
}
