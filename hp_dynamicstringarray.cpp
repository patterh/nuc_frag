#include "hp_dynamicstringarray.h"

using namespace std;

HP_DynamicStringArray::HP_DynamicStringArray()
{
 number_of_strings = 0;
 array_of_pointers_to_pointer = 0;
}

HP_DynamicStringArray::~HP_DynamicStringArray()
{
  for(int x = 0; x < number_of_strings; x++)
    {
    delete [] array_of_pointers_to_pointer[x];
    }
  delete [] array_of_pointers_to_pointer;
}

HP_DynamicStringArray::HP_DynamicStringArray(HP_DynamicStringArray& object)
{
	number_of_strings = object.number_of_strings;
	array_of_pointers_to_pointer = new char*[number_of_strings];
	for(int x = 0; x < number_of_strings; x ++)
	{
		array_of_pointers_to_pointer[x] = new char[strlen(object.array_of_pointers_to_pointer[x])+1];
		memset(array_of_pointers_to_pointer[x], 0, strlen(object.array_of_pointers_to_pointer[x])+1);
		strncpy(array_of_pointers_to_pointer[x], object.array_of_pointers_to_pointer[x], strlen(object.array_of_pointers_to_pointer[x]));
	}


}


char* HP_DynamicStringArray::AddString(char* string)
{
number_of_strings++;

//If we dont have an initialized array_of_pointers_to_pointer yet, make one

if (array_of_pointers_to_pointer == 0)
    {
    array_of_pointers_to_pointer = new char*[1];
    }
else // Expand initialized array_of_pointers by one
    {
    char** temp_pointer = new char*[number_of_strings-1];
    for (int x = 0; x < number_of_strings-1; x++)
      {
      temp_pointer[x] =  array_of_pointers_to_pointer[x];
      }
    delete [] array_of_pointers_to_pointer;
    array_of_pointers_to_pointer = new char*[number_of_strings];
    for (int x = 0; x < number_of_strings-1; x++)
      {
      array_of_pointers_to_pointer[x] =  temp_pointer[x];
      }
    delete [] temp_pointer;
    }
int length_of_new_string = strlen(string);
array_of_pointers_to_pointer[number_of_strings-1] = new char[length_of_new_string+1]; // +1 for the zero
memset(array_of_pointers_to_pointer[number_of_strings-1], 0, length_of_new_string+1);
strcpy(array_of_pointers_to_pointer[number_of_strings-1], string);
return(array_of_pointers_to_pointer[number_of_strings-1]);
}

bool HP_DynamicStringArray::DeleteString(int index)
{
delete [] array_of_pointers_to_pointer[index];
array_of_pointers_to_pointer[index] = 0;
char** temp = new char*[number_of_strings-1];
for(int x = 0; x < index; x++)
  {
  temp[x] = array_of_pointers_to_pointer[x];
  }
for(int x = index; x < number_of_strings-1; x++)
  {
   temp[x] = array_of_pointers_to_pointer[x+1];
  }
delete [] array_of_pointers_to_pointer;
array_of_pointers_to_pointer = new char*[number_of_strings-1];
for(int x = 0; x < number_of_strings-1; x++)
  {
  array_of_pointers_to_pointer[x] = temp[x];
  }
delete [] temp;
number_of_strings--;
return(true);
}

char* HP_DynamicStringArray::GetString(char* &string, int index)
{
int length_of_new_string = strlen(array_of_pointers_to_pointer[index]);
string = new char[length_of_new_string+1];
memset(string, 0, length_of_new_string+1);
strcpy(string, array_of_pointers_to_pointer[index]);
return(string);
}

int HP_DynamicStringArray::GetNumberOfStrings()
{
return(number_of_strings);
}

// Remove character "strip_character" from the string at index "index" in the array of strings
char* HP_DynamicStringArray::StripCharacter(char strip_character, int index)
{
int length = strlen(array_of_pointers_to_pointer[index]);
char* temp = new char[length+1];
memset(temp, 0, length+1);
int new_string_counter = 0;
for(int x=0; x < length;x++)
  {
  if(array_of_pointers_to_pointer[index][x] != strip_character)
    {
     temp[new_string_counter] = array_of_pointers_to_pointer[index][x];
     new_string_counter++;
    }
  }
delete [] array_of_pointers_to_pointer[index];
int new_string_length = strlen(temp);
array_of_pointers_to_pointer[index] = new char[new_string_length+1];
memset(array_of_pointers_to_pointer[index],0,new_string_length+1);
strcpy(array_of_pointers_to_pointer[index], temp);
delete [] temp;
return(array_of_pointers_to_pointer[index]);
}

char* HP_DynamicStringArray::GetStringPointer(int index)
{
return(array_of_pointers_to_pointer[index]);
}

bool HP_DynamicStringArray::DeleteCharacterInString(int string_index, int character_index)
{
int old_string_length = strlen(array_of_pointers_to_pointer[string_index]);
char* temp =  new char[old_string_length+1];
memset(temp,0,old_string_length+1);
strcpy(temp,array_of_pointers_to_pointer[string_index]);
delete [] array_of_pointers_to_pointer[string_index];
array_of_pointers_to_pointer[string_index] = new char[old_string_length];
memset(array_of_pointers_to_pointer[string_index],0,old_string_length);
for(int x=0; x < character_index;x++)
  {
    array_of_pointers_to_pointer[string_index][x] = temp[x];
  }
for(int x=character_index; x < old_string_length-1; x++)
  {
    array_of_pointers_to_pointer[string_index][x] = temp[x+1];
  }
delete [] temp;
return(true);
}





