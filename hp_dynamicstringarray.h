#ifndef _HP_DYNAMICSTRINGARRAY_H
#define _HP_DYNAMICSTRINGARRAY_H


#include <cstring>

class HP_DynamicStringArray
{
public:

HP_DynamicStringArray();
~HP_DynamicStringArray();
HP_DynamicStringArray(HP_DynamicStringArray& object);

char* AddString(char* string);
bool DeleteString(int index);
char* GetString(char* &string, int index);
char* GetStringPointer(int index);
int GetNumberOfStrings();
char* StripCharacter(char strip_character, int index);
bool DeleteCharacterInString(int string_index, int character_index);

protected:

char** array_of_pointers_to_pointer;
int number_of_strings;

};

#endif
