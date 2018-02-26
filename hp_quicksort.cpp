
#include "hp_quicksort.h"


HPQuickSort::HPQuickSort()
{
}

HPQuickSort::~HPQuickSort()
{
}

void HPQuickSort::QuickSort(int* array, int left, int right)
{
int i;
int j;
int v;
if(right > left)
	{
   v = array[right];
   i = left-1;
   j = right;
   for(;;)
   	{
      while(array[++i] < v);
      while ( --j >= left && array[j] > v);
      if(i >= j)
      	break;
      Swap(array, i, j);
      }
   Swap(array, i, right);
   QuickSort(array, left, i-1);
   QuickSort(array, i+1, right);
	}
}

void HPQuickSort::IndirectQuickSort(int* indexes, int* array, int left, int right)
{
int i;
int j;
int v;
if(right > left)
	{
   v = array[indexes[right]];
   i = left-1;
   j = right;
   for(;;)
   	{
      while(array[indexes[++i]] < v);
      while ( --j >= left && array[indexes[j]] > v);
      if(i >= j)
      	break;
      IndirectSwap(indexes, i, j);
      }
   IndirectSwap(indexes, i, right);
   IndirectQuickSort(indexes, array, left, i-1);
   IndirectQuickSort(indexes, array, i+1, right);
	}
}


void HPQuickSort::Swap(int* array, int leftelement, int rightelement)
{
int temp = array[leftelement];
array[leftelement] = array[rightelement];
array[rightelement] = temp;
}

void HPQuickSort::IndirectSwap(int* indexes, int leftelement, int rightelement)
{
int temp = indexes[leftelement];
indexes[leftelement] = indexes[rightelement];
indexes[rightelement] = temp;
}
