#ifndef _hpqcksrt_h
#define _hpqcksrt_h

class HPQuickSort
{
public:
HPQuickSort();
~HPQuickSort();

void QuickSort(int* array, int left, int right);
void IndirectQuickSort(int* indexes, int* array, int left, int right);

protected:
void Swap(int* array, int leftelement, int rightelement);
void IndirectSwap(int* indexes, int leftelement, int rightelement);
};

#endif