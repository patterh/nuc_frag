/*
 * main.cpp
 *
 *  Created on: 26 Sep 2012
 *      Author: patterh
 */
#include "main.h"

using namespace std;

int main() {
	/*
	 *	nucfrag -i input_file -o output_file -c ini_file [options]
	 *	sam input file -i
	 *	chromosome ini file -c
	 *
	 *		bin_array; -d
	 *		footprint_array; -f
	 *		average_bin_array; -a
	 *		size_array -s
	 *
	 *		output file prefix path -o
	 *
	 *		int minimum_fragment_size = 160; -n <value>
	 *		int maximum_fragment_size = 175; -x <value>
	 *		-h help
	 *
	 *		int window_size = 7; -s <value>
	 **
	 **
	 **

	 char* help_output = new char[1024];
	 strcpy(help_output, "Usage: nucfrag [options] -i input_file -o output_file -c ini file \n\n"
	 "-i filename\tinput file in SAM format (see http://samtools.sourceforge.net/)\n"
	 "-o filename\toutput file\n"
	 "-c filename\tchromosome info ini file\n\n"
	 "Options:\n\n"
	 "-n <value>\tminimum fragment length to use (default=145)\n"
	 "-x <value>\tmaximum fragment length to use (default=155)\n"
	 "-s <value>\tsmoothing window size (default=7)\n"
	 "-d\tsave dyad position file\n"
	 "-a\tsave average dyad position file (use -s flag for smoothing)\n"
	 "-f <value>\tsave footprint file using <value> for nucleosome size\n"
	 "-z\tsave size distribution file\n"
	 "-h\tdisplay this help message\n");
	 cout << help_output << endl;
	 return(0);


	 // When passing char arrays as parameters they must be pointers

	 if (argc < 7) // must be at least 7.
	 std::cout << help_output << endl; // Inform the user of how to use the program
	 else // if we got enough parameters...
	 {
	 char* input_filename, output_filename, chromosome_ini_filename;
	 int minimum_fragment_size = 160;
	 int maximum_fragment_size = 175;
	 int window_size = 7;
	 bool do_dyad, do_average, do_size, do_footprint = false;

	 for (int i = 1; i < argc; i++)
	 {		// We will iterate over argv[] to get the parameters stored inside.
	 // Note that we're starting on 1 because we don't need to know the
	 // path of the program, which is stored in argv[0]
	 if (i + 1 != argc) // Check that we haven't finished parsing already
	 if (argv[i] == "-i")
	 // We know the next argument *should* be the filename:
	 input_filename = argv[i + 1];
	 else if (argv[i] == "-o")
	 output_filename = argv[i + 1];
	 else if (argv[i] == "-c")
	 chromosome_ini_filename = argv[i + 1];
	 else if (argv[i] == "-n")
	 minimum_fragment_size = atoi(argv[i+1]);
	 else if (argv[i] == "-x")
	 maximum_fragment_size = atoi(argv[i+1]);
	 else if (argv[i] == "-s")
	 {
	 window_size = atoi(argv[i+1]);
	 window_size = window_size%2 ? window_size : window_size+1; // make sure window size is odd
	 }
	 else if (argv[i] == "-d")
	 do_dyad = true;
	 else if (argv[i] == "-z")
	 do_size = true;
	 else if (argv[i] == "-f")
	 do_footprint = true;
	 else if (argv[i] == "-a")
	 do_average = true;
	 std::cout << "Not enough or invalid arguments, please try again.\n";
	 exit(0);
	 }*/

	char* input_filename = new char[1024];
	char* output_filename = new char[1024];
	char* chromosome_ini_filename = new char[1024];

	strcpy(input_filename,"C:\\Users\\hpatterton\\Documents\\T_brucei\\427\\Genome_sequence\\Siegel EMBO J data\\Filtered map against masked genome.sam");
	strcpy(output_filename,
			"C:\\Users\\hpatterton\\Documents\\T_brucei\\427\\Genome_sequence\\Siegel EMBO J data\\Filtered map against masked genome");
	strcpy(chromosome_ini_filename,
			"C:\\Users\\hpatterton\\Documents\\T_brucei\\427\\Genome_sequence\\Siegel EMBO J data\\chromosomes.ini");

	int minimum_fragment_size = 0;
	int maximum_fragment_size = 500;
	int window_size = 7;
	bool do_dyad = true;
	bool do_average = true;
	bool do_footprint = true;
	bool do_size = true;
	int size = 160; // size of nucleosome for footprint

	// Read in all the chromosome data
// -i inifile

	HP_Chromosome_Ini_File* chromosome_ini_file = new HP_Chromosome_Ini_File();
	int number_of_chromosomes = chromosome_ini_file->Read_Chromosome_Ini_File(chromosome_ini_filename);
	if(!number_of_chromosomes){
		cout << "Chromosome ini file does  ot exist or is empty" << endl;
	}
	else{
		cout << "Number of chromosomes = " << number_of_chromosomes << endl;
		//cout << sizeof(unsigned int) << ", " << sizeof(size_t) << endl;
	}

	// Initialize the bin array
	//the bin array will contain the counts of dyad axes at each nucleotide position of each chromosome
	//the array below is specifically for T. brucei strain 427 taken from Genome Sequence version 4 (http://www.tritrypdb.org)

	int** bin_array;
	int** footprint_array;
	float** average_bin_array;
	bin_array = new int*[number_of_chromosomes];
	average_bin_array = new float*[number_of_chromosomes];
	footprint_array = new int*[number_of_chromosomes];
	int valid_dyad_positions = 0;
	int chromosome_size;
	for (int x = 0; x < number_of_chromosomes; x++) {
		chromosome_size = chromosome_ini_file->GetChromosomeSize(x);
		bin_array[x] = new int[chromosome_ini_file->GetChromosomeSize(x)];
		memset(bin_array[x], 0, chromosome_ini_file->GetChromosomeSize(x));
		average_bin_array[x] = new float[chromosome_ini_file->GetChromosomeSize(
				x)];
		memset(average_bin_array[x], 0,
				chromosome_ini_file->GetChromosomeSize(x));
		footprint_array[x] = new int[chromosome_ini_file->GetChromosomeSize(x)];
		memset(footprint_array[x], 0,
				chromosome_ini_file->GetChromosomeSize(x));
	}

// Initialise the array of sizes

	int number_of_fragment_sizes = maximum_fragment_size - minimum_fragment_size+1;
	int* size_distribution = new int[number_of_fragment_sizes];
	for (int x = 0; x < number_of_fragment_sizes; x++)
		size_distribution[x] = 0;

	//Read the Bowtie2 SAM file

	HP_ReadTextFile* samfile = new HP_ReadTextFile();
	char* buffer = 0;
	char** list_of_string_pointers = 0;
	int number_of_sam_entries = samfile->ReadSAMFormatFile(buffer,
			list_of_string_pointers, input_filename);
	cout << "Number an entries in SAM file = " << number_of_sam_entries << endl;

	// Step through all the entries

	char* temp_flag = new char[100];
	char* chromosome_name = new char[1024];
	int chromosome_number;
	int sambitflag;
	char* column2_start = 0;
	char* column2_end = 0;
	char* column3_start = 0;
	char* column3_end = 0;
	char* column4_start = 0;
	char* column4_end = 0;
	char* column8_start = 0;
	char* column8_end = 0;
	char* column9_start = 0;
	char* column9_end = 0;
	int position;
	int position_mate;
	int length;
	int start_nucleotide_index_1;
	int fragment_size;
	int dyad_nucleotide;
	int index = 0;
	while (index < number_of_sam_entries) {

		// Get the SAM bitflag
		memset(temp_flag, 0, 100);
		column2_start = strchr(list_of_string_pointers[index], '\t') + 1;
		column2_end = strchr(column2_start, '\t');
		memset(temp_flag,0,100);
		strncpy(temp_flag, column2_start, column2_end-column2_start);
		sambitflag = atoi(temp_flag);
		column3_start = column2_end + 1;
		column3_end = strchr(column3_start, '\t');
		memset(chromosome_name, 0, 1024);
		strncpy(chromosome_name, column3_start,
				column3_end - column3_start);
		chromosome_number =
				chromosome_ini_file->GetIndexOfChromosomeName(
						chromosome_name);
		column4_start = column3_end + 1;
		column4_end = strchr(column4_start, '\t');
		memset(temp_flag,0,100);
		strncpy(temp_flag, column4_start, column4_end - column4_start);
		position = atoi(temp_flag);
		column8_start = column4_end + 1;
		int loop_counter = 5;
		while (loop_counter++ < 8) {
			column8_start = strchr(column8_start, '\t') + 1;
		}
		column8_end = strchr(column8_start, '\t');
		memset(temp_flag,0,100);
		strncpy(temp_flag, column8_start,
				column8_end - column8_start + 1);
		position_mate = atoi(temp_flag);

		column9_start = column8_end + 1;
		column9_end = strchr(column9_start, '\t');
		memset(temp_flag,0,100);
		strncpy(temp_flag, column9_start,
				column9_end - column9_start + 1);
		length = atoi(temp_flag);

		/*
		 * Is this entry:
		 * read paired 1
		 * read mapped in proper pair 2
		 * first in pair 64
		 * and is the chromosome number mapped
		 * (is the sequence reference in the chromosome ini file?)
		 *
		 */

		if ((sambitflag & 67) && (length>=minimum_fragment_size) && (length<=maximum_fragment_size) && (chromosome_number>=0)) {
			// Is this read on the Forward strand:
			/*if (sambitflag & 32) {
				start_nucleotide_index_1 = position;
				fragment_size = length;
			} else {
				start_nucleotide_index_1 = position_mate;
				fragment_size = abs(length);
			}*/
			start_nucleotide_index_1 = (position <= position_mate) ? position : position_mate;
			fragment_size = abs(length);
			dyad_nucleotide = start_nucleotide_index_1+(fragment_size/2)-1;

			valid_dyad_positions++;

			// increment the nucleosome position array at the dyad position by one

			bin_array[chromosome_number][dyad_nucleotide - 1]++; // dyad_nucleotide-1 because the chromosome numbering starts at 1 not 0

			//increment the footprint array

			for (int x = 0; x < size; x++)
				footprint_array[chromosome_number][start_nucleotide_index_1 + x]++;

			// increment the size distribution array by one

			size_distribution[length-minimum_fragment_size]++;

		}
	index++;
	}

	delete [] temp_flag;
	delete [] chromosome_name;

	// write the results to disk
	// Each chromosome is written to a different file
	// the result file pre-fix is supplied by the user

	cout << "writing results to disk...";

	// Calculate the running window smoothed data set

	int offset = (window_size + 1) / 2;
	float value;
	for (int x = 0; x < chromosome_ini_file->GetNumberOfEntries(); x++)
		for (int y = 0; y <= chromosome_ini_file->GetChromosomeSize(x) - window_size; y++) {
			value = 0;
			for (int z = 0; z < window_size; z++)
				value += footprint_array[x][y + z];
			value = value / window_size;
			average_bin_array[x][y + offset - 1] = value;
		}

	char* filename = new char[1024];
	char* temp = new char[255];
	char* size_distribution_array_path = new char[1024];
	char* footprint_array_path = new char[1024];
	char* average_array_path = new char[1024];
	std::ofstream outfile;
	std::ofstream footprintfile;
	std::ofstream averagearrayfile;
	for (int x = 0; x < chromosome_ini_file->GetNumberOfEntries(); x++) {
		memset(filename, 0, 1024);
		memset(size_distribution_array_path, 0, 1024);
		memset(footprint_array_path, 0, 1024);
		memset(average_array_path, 0, 1024);
		strcpy(filename, output_filename); //argv[2]);
		strcpy(size_distribution_array_path, filename);
		strcat(size_distribution_array_path,
				"_size_distribution_array.txt");
		strcat(filename, "_");
		strcat(filename, chromosome_ini_file->GetChromosomeName(x));
		samfile->MakeValidWindowsPathName(filename);
		strcpy(footprint_array_path, filename);
		strcpy(average_array_path, filename);
		strcat(footprint_array_path, "_footprint_array.txt");
		strcat(average_array_path, "_average_array.txt");
		strcat(filename, "_dyads.txt");

		// write the dyad array to disk

		if (do_dyad) {
			outfile.open(filename, fstream::out);
			for (int y = 0; y < chromosome_ini_file->GetChromosomeSize(x); y++) {
				memset(temp, 0, 255);
				sprintf(temp, "%d", bin_array[x][y]);
				outfile << temp << endl;
			}
			outfile.close();
		}

		// write the average_array to disk
		if (do_average) {
			averagearrayfile.open(average_array_path, fstream::out);
			for (int y = 0; y < chromosome_ini_file->GetChromosomeSize(x); y++) {
				memset(temp, 0, 255);
				sprintf(temp, "%f", average_bin_array[x][y]);
				averagearrayfile.write(temp, strlen(temp));
				averagearrayfile.put(13);
			}
			averagearrayfile.close();
		}

		// write the footprint_array to disk
		if (do_footprint) {
			footprintfile.open(footprint_array_path, fstream::out);
			bool result = footprintfile.is_open();
			for (int y = 0; y < chromosome_ini_file->GetChromosomeSize(x); y++) {
				memset(temp, 0, 255);
				sprintf(temp, "%d", footprint_array[x][y]);
				//footprintfile << temp << endl;
				footprintfile.write(temp, strlen(temp));
				footprintfile.put('\n');
			}
			footprintfile.close();
		}
	}

	// write the size distribution array to disk
	if (do_size) {
		outfile.open(size_distribution_array_path, fstream::out);
		char* x_value = new char[255];
		for (int y = 0; y < number_of_fragment_sizes; y++) {
			memset(x_value, 0, 255);
			sprintf(x_value, "%d", minimum_fragment_size + y);
			memset(temp, 0, 255);
			sprintf(temp, "%d", size_distribution[y]);
			outfile.write(x_value, strlen(x_value));
			outfile.put('\t');
			outfile.write(temp, strlen(temp));
			outfile.put('\n');
		}
		outfile.close();
	}

	delete[] filename;
	delete[] temp;
	delete[] size_distribution_array_path;
	delete[] footprint_array_path;
	cout << endl << valid_dyad_positions << " valid dyad positions"
			<< endl;

	return 0;
}

