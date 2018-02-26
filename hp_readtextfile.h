/*
 * HP_ReadTextFile.h
 *
 *  Created on: 27 Sep 2012
 *      Author: patterh
 */

#ifndef HP_READTEXTFILE_H_
#define HP_READTEXTFILE_H_

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include "hp_dynamicstringarray.h"
#include "hp_dynamicintegerarray.h"

using namespace std;

class HP_ReadTextFile
{
public:

HP_ReadTextFile();
~HP_ReadTextFile();
//ReadFastqFile(char* filename, HP_DynamicStringArray* string_array);
void ReadFastaFile(char* filename);
int ReadFileofGenomicPositions(HPDynamicIntArray* chromosome_number, HPDynamicIntArray* genomic_position, HP_DynamicStringArray* strand,  char* filename);
int ReadNucleosomeDyadFile(char*& buffer, char**& list_of_string_pointers, char* filename);
int ReadNucleosomeDyadFile(float*& dyad_values, char* filename);
int ReadTextFile(char*& buffer, char**& list_of_string_pointers, char* filename);
int  ReadSequenceFile(char*& sequence, char* filename);
int NumberOfEntries();
int NumberOfLines();
int LengthOfLine(int index);
char* GetLine(char*& line, int index);
char* GetLinePointer(int index);
int  GetLineForEntryNumber(int index);
HP_DynamicStringArray* GetWholeEntry(HP_DynamicStringArray*& strings, int index);
char* CombineStringsInEntry(char*& temp, int index);
int ReadFileofFileNames(char* filename, HP_DynamicStringArray* dynamic_string_array);
bool IsTextFileofFloatValues();
char* StripFileExtension(char*& modified_string, char* full_path);
int ReadSAMFormatFile(char*& buffer, char**& list_of_string_pointers, char* filename);
char* MakeValidWindowsPathName(char*& pathname);


protected:

HP_DynamicStringArray* array_of_strings;
int number_of_lines;

};


#endif /* HP_READTEXTFILE_H_ */
