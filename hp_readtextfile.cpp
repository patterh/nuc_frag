/*
 * temp.cpp
 *
 *  Created on: 27 Sep 2012
 *      Author: patterh
 */

#include "hp_readtextfile.h"

using namespace std;

HP_ReadTextFile::HP_ReadTextFile()
{
array_of_strings = new HP_DynamicStringArray();
number_of_lines = 0;
}

HP_ReadTextFile::~HP_ReadTextFile()
{
delete array_of_strings;
}

int HP_ReadTextFile::ReadNucleosomeDyadFile(char*& buffer, char**& list_of_string_pointers, char* filename)
{
fstream filestr;
filestr.open(filename, fstream::in | fstream::binary);
filestr.seekg (0, filestr.end);
int length = filestr.tellg();
filestr.seekg (0, filestr.beg);
buffer = new char[length+1];
memset(buffer, 0, length+1);
list_of_string_pointers = new char*[length+1];
filestr.read(buffer, length);
filestr.close();
char* start;
int entry = 0;
start = strtok(buffer,"\r\n");
while (start != 0)
	{
	list_of_string_pointers[entry++] = start;
	start = strtok (0,"\r\n");
	}
return(entry);
}

int HP_ReadTextFile::ReadNucleosomeDyadFile(float*& dyad_values, char* filename)
{
fstream filestr;
filestr.open(filename, fstream::in | fstream::binary);
filestr.seekg (0, filestr.end);
int length = filestr.tellg();
filestr.seekg (0, filestr.beg);
char* buffer = new char[length+1];
memset(buffer, 0, length+1);
dyad_values = new float[length];
filestr.read(buffer, length);
filestr.close();
char* start;
int entry = 0;
start = strtok(buffer,"\r\n");
while (start != 0)
	{
	dyad_values[entry++] = atof(start);
	start = strtok (0,"\r\n");
	}
delete [] buffer;
return(entry);
}

int  HP_ReadTextFile::ReadSequenceFile(char*& sequence, char* filename)
{
	fstream filestr;
	filestr.open(filename, fstream::in | fstream::binary);
	filestr.seekg (0, filestr.end);
	int length = filestr.tellg();
	filestr.seekg (0, filestr.beg);
	char* buffer = new char[length+1];
	memset(buffer, 0, length+1);
	sequence = new char[length+1];
	memset(sequence, 0, length+1);
	filestr.read(buffer, length);
	filestr.close();
	char* pointer = strstr(buffer,"\r\n");
	char* start = strtok(pointer,"\r\n");
	while (start != 0)
		{
		strcat(sequence, start);
		start = strtok (0,"\r\n");
		}
	return(strlen(sequence));
}

void HP_ReadTextFile::ReadFastaFile(char* filename)
{
fstream filestr;
filestr.open(filename, fstream::in);
char* temp = 0;
while(filestr.eof() != true)
  {
          temp = new char[1024];
          memset(temp,0,1024);
          filestr.getline(temp,1024);
          array_of_strings->AddString(temp);
          delete [] temp;
  }
}

int HP_ReadTextFile::ReadFileofGenomicPositions(HPDynamicIntArray* chromosome_number, HPDynamicIntArray* genomic_position, HP_DynamicStringArray* strand,  char* filename)
{
fstream filestr;
filestr.open(filename, fstream::in | fstream::binary);
filestr.seekg (0, filestr.end);
int length = filestr.tellg();
filestr.seekg (0, filestr.beg);
char* buffer = new char[length+1];
memset(buffer, 0, length+1);
filestr.read(buffer, length);
filestr.close();
char* start;;
char* second_entry;
char* third_entry;
int entry = 0;
start = strtok(buffer,"\r\n");
while (start != 0)
	{
	chromosome_number->AddInt(atoi(start));
	second_entry = strchr(start,'\t');
	genomic_position->AddInt(atoi(second_entry+1));
	third_entry = strchr(second_entry+1, '\t');
	strand->AddString(third_entry+1);
	start = strtok (0,"\r\n");
	entry++;
	}
delete [] buffer;
return(entry);

}



int HP_ReadTextFile::ReadTextFile(char*& buffer, char**& list_of_string_pointers, char* filename)
{
fstream filestr;
filestr.open(filename, fstream::in | fstream::binary);
filestr.seekg (0, filestr.end);
int length = filestr.tellg();
filestr.seekg (0, filestr.beg);
buffer = new char[length+1];
memset(buffer, 0, length+1);
list_of_string_pointers = new char*[length+1];
/*int entry = 0;
char* temp = 0;
while(!filestr.eof())
{
	temp = new char[30];
	filestr.getline(temp, 1024, '\n');
	list_of_string_pointers[entry++] = temp;
}*/


filestr.read(buffer, length);
filestr.close();
char* start;
int entry = 0;
start = strtok(buffer,"\n");
while (start != 0)
	{
	list_of_string_pointers[entry++] = start;
	start = strtok (0,"\n");
	}
return(entry);
}



int HP_ReadTextFile::NumberOfEntries()
{
int number_of_lines = NumberOfLines();
int count = 0;
for(int x = 0; x < number_of_lines; x++)
  {
  if(array_of_strings->GetStringPointer(x)[0] == '>')
    {
    count++;
    }
  }
return(count);
}

int HP_ReadTextFile::NumberOfLines()
{
 return(array_of_strings->GetNumberOfStrings());
}

int HP_ReadTextFile::LengthOfLine(int index)
{
return(strlen(array_of_strings->GetStringPointer(index)));
}

HP_DynamicStringArray* HP_ReadTextFile::GetWholeEntry(HP_DynamicStringArray*& strings, int index)
{
  int number_of_lines = NumberOfLines();
  int start = GetLineForEntryNumber(index);
  int end = GetLineForEntryNumber(index+1);
  if (end < number_of_lines)
    end-=2;
  strings = new HP_DynamicStringArray();
  for(int x = start; x < end; x++)
    strings->AddString(array_of_strings->GetStringPointer(x));
return(strings);
}

char* HP_ReadTextFile::GetLine(char*& line, int index)
{
int linelength =  LengthOfLine(index);
line = new char[linelength+1];
memset(line,0,linelength+1);
strncpy(line, array_of_strings->GetStringPointer(index),linelength);
return(line);
}

char* HP_ReadTextFile::GetLinePointer(int index)
{
  return(array_of_strings->GetStringPointer(index));
}

int  HP_ReadTextFile::GetLineForEntryNumber(int index)
{
int line = 0;
int count = 0;
int number_of_lines = NumberOfLines();
while((line < number_of_lines) && (count <= index))
  {
  if(array_of_strings->GetStringPointer(line)[0] == '>')
    {
    count++;
    line++;
    }
  else
    {
    line++;
    }
  }
return(line);
}

char* HP_ReadTextFile::CombineStringsInEntry(char*& temp, int index)
{
  HP_DynamicStringArray* entry = 0;
  GetWholeEntry(entry, index);
  int number_of_strings = entry->GetNumberOfStrings();
  int length = 0;
  for(int x = 0; x < number_of_strings; x++)
    {
      length += strlen(entry->GetStringPointer(x));
    }
  temp = new char[length+1];
  memset(temp, 0, length+1);
  char* pointer = temp;
  for(int x = 0; x < number_of_strings; x++)
    {
      strcpy(pointer, entry->GetStringPointer(x));
      pointer += strlen(entry->GetStringPointer(x));
    }
return(temp);
}

int HP_ReadTextFile::ReadFileofFileNames(char* filename, HP_DynamicStringArray* dynamic_string_array)
{
char* temp = 0;
std::fstream inputfile;
inputfile.open(filename, std::fstream::in);
while (inputfile.eof() != true)
	{
	temp = new char[1024];
	memset(temp, 0, 1024);
	inputfile.getline(temp, 1024);
	dynamic_string_array->AddString(temp);
	}
inputfile.close();
int number_of_entries = dynamic_string_array->GetNumberOfStrings();
return(number_of_entries-1);
}

bool HP_ReadTextFile::IsTextFileofFloatValues()
{
if(strchr(GetLinePointer(0), '.'))
	return(true);
else
	return(false);
}

char* HP_ReadTextFile::StripFileExtension(char*& modified_string, char* full_path)
{
char* point = strchr(full_path, '.');
int full_string_length = strlen(full_path);
int extension_string_length = strlen(point);
modified_string = new char[1024];
memset(modified_string, 0, 1024);
strncpy(modified_string, full_path, full_string_length-extension_string_length);
return(modified_string);
}

int HP_ReadTextFile::ReadSAMFormatFile(char*& buffer, char**& list_of_string_pointers, char* filename)
{
std::ifstream filestr(filename);
if(!filestr.is_open())
	return(0);
filestr.seekg (0, filestr.end);
unsigned int length = filestr.tellg();
filestr.seekg (0, filestr.beg);
buffer = new char[length+1];
memset(buffer, 0, length+1);
list_of_string_pointers = new char*[length+1];
filestr.read(buffer, length);
filestr.close();
char* start;
int entry = 0;
start = strtok(buffer,"\n");
while (start != 0)
	{
	list_of_string_pointers[entry++] = start;
	start = strtok (0,"\n");
	}
return(entry);
}

char* HP_ReadTextFile::MakeValidWindowsPathName(char*& pathname)
{
char* exceptionstring = new char[10];
strcpy(exceptionstring,"<>:\"/|?*");
char* pointer = pathname;
int count = 0;
pointer = strpbrk(pointer,exceptionstring);
while(pointer){
	if((pointer[0] == ':')&&(count == 0)){
		count++;
		pointer++;
	}
	else{
	pointer[0] = '_';
	pointer++;
	}
pointer = strpbrk(pointer,exceptionstring);
}
return(pathname);
}
  
