/*
 * hp_chromosome_ini_file.h
 *
 *  Created on: Jul 14, 2016
 *      Author: hpatterton
 */

#ifndef HP_CHROMOSOME_INI_FILE_H_
#define HP_CHROMOSOME_INI_FILE_H_

#include "hp_readtextfile.h"
#include "hp_dynamicstringarray.h"
#include "hp_dynamicintegerarray.h"

class HP_Chromosome_Ini_File
{
public:
HP_Chromosome_Ini_File();
~HP_Chromosome_Ini_File();
int Read_Chromosome_Ini_File(char* filename);
bool Add_Entry(char* entry);
char* GetChromosomeName(int index);
int GetChromosomeSize(int index);
int GetIndexOfChromosomeName(char* name);
int GetNumberOfEntries();

protected:
HP_DynamicStringArray* chromosome_names;
HPDynamicIntArray* chromosome_size;
int number_of_entries;

};



#endif /* HP_CHROMOSOME_INI_FILE_H_ */
