#include "hp_chromosome_ini_file.h"
using namespace std;

HP_Chromosome_Ini_File::HP_Chromosome_Ini_File()
{
chromosome_names = new HP_DynamicStringArray();
chromosome_size = new HPDynamicIntArray();
number_of_entries = 0;
}

HP_Chromosome_Ini_File::~HP_Chromosome_Ini_File()
{
delete chromosome_names;
delete chromosome_size;
}

int HP_Chromosome_Ini_File::Read_Chromosome_Ini_File(char* filename)
{
// Read in all the chromosome data
// -i inifile
char* temp = 0;
std::ifstream filestr(filename);
if (!filestr.is_open())
	return (0);
temp = new char[1024];
int counter = 0;
while (filestr.eof() != true)
	{
	memset(temp, 0, 1024);
	filestr.getline(temp, 1024);
	if(temp[0] != 0){
		Add_Entry(temp);
		counter++;
	}
	}
delete[] temp;
filestr.close();
number_of_entries=counter;
return(number_of_entries);
}

bool HP_Chromosome_Ini_File::Add_Entry(char* entry)
{
char* temp = new char[1024];
memset(temp,0,1024);
char* start = entry;
char* end = strchr(start,'\t');
strncpy(temp, start, end-start);
chromosome_names->AddString(temp);
start=end+1;
strcpy(temp, start);
chromosome_size->AddInt(atoi(temp));
delete [] temp;
return(true);
}

char* HP_Chromosome_Ini_File::GetChromosomeName(int index)
{
return(chromosome_names->GetStringPointer(index));
}

int HP_Chromosome_Ini_File::GetChromosomeSize(int index)
{
return(chromosome_size->GetEntry(index));
}

int HP_Chromosome_Ini_File::GetIndexOfChromosomeName(char* name)
{
int index = 0;
while((index < number_of_entries) && (strcmp(name,chromosome_names->GetStringPointer(index)))){
	index++;
}
if(index >= number_of_entries)
	return(-1);
else
	return(index);
}

int HP_Chromosome_Ini_File::GetNumberOfEntries()
{
return(number_of_entries);
}
