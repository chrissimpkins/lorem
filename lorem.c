
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "lorem.h"

int main(int argc, char **argv) {
	char c;
	while ( (c = getopt(argc, argv, "ahrsvi:n:o:") ) != -1) {
		switch (c) {
			case 'n':
				if (optarg == NULL){
					printf("Default to 1 paragraph of lorem ipsum text.  Enter a number with the -n option if you would like to include more.\n");
				}
				else{
					number_paragraph = atoi(optarg);
					if (number_paragraph == 0){
						printf("The number of paragraphs was not properly specified with the -n switch.\n");
						printf("Usage: lorem -n <number>");
						exit(EXIT_FAILURE);
					}
				}
				break;
			case 'o':
				if (optarg == NULL){
					//default to a file named lorem.txt defined in header
				}
				else{
					filename = optarg;  //assigns out file path
				}
				break;
			case 'a':
				append = 1;	//switch append flag to 1, now appends write to file rather than writing a new file
				break;
			case 'h':
				print_help();
				exit(EXIT_SUCCESS);
			case 'i':
				if (optarg == NULL){
					fprintf(stderr, "You did not enter a file path to the input file for the text replacement.");
					exit(EXIT_FAILURE);
				}
				else{
					in_filename = optarg;
				}
				break;
			case 'r':
				replace = 1;  //flag for replacement in a input file switched
				break;
			case 's':
				standard_out = 1; //flag for stream to standard out rather than write to file
				break;
			case 'v':
				print_version();
			 	exit(EXIT_SUCCESS);
			case '?':
				//handle command line errors
	            if (isprint (optopt)){
	            	fprintf (stderr, "Error with option `-%c' that was submitted in your command.\n", optopt);
	           		fprintf (stderr, "Get help : %s -h\n", argv[0]);	
	           	}
	            else {
	            	fprintf (stderr,
	                        "Unknown option character `\\x%x'.\n",
	                        optopt);
	            }
             	exit(EXIT_FAILURE);
		}
	}
	//concatenate strings to form number of paragraphs, includes newline between paragraphs, write to proper stream
	//test for request below the paragraph limit (defined in PARA_LIMIT in lorem.h)
	if (number_paragraph <= PARA_LIMIT && replace == 0) {
		make_write_string();
		//respond to user with total number of paragraphs written to file (if not standard out stream write)
		if (! standard_out){
		//format the response string sent to user after completion
		format_output();
		printf("Wrote %d %s of lorem text to '%s'\n", number_paragraph, paragraph_text, filename);
		//free the loremstring that was created to hold the loremstring
		free(loremstring);
	}
	}
	else if (number_paragraph <= PARA_LIMIT && replace == 1){
		get_replacement_strings();
		// Write out the string insertions in the file
		concat_write_replacement();
		printf("Inserted %d %s of lorem text in the file '%s'.\n", number_paragraph, paragraph_text, filename);
		/* free the memory we used for the strings */
		free(buffer);
		free(prestring);
		free(poststring);
		free(loremstring);
	}
	else {
		fprintf(stderr, "You requested %d lorem paragraphs.  The maximum is %d.\n", number_paragraph, PARA_LIMIT);
		exit(EXIT_FAILURE);
	}
}

void concat_write_replacement() {
	FILE* outfile;
	filename = in_filename;
	outfile = fopen(filename, "w");
	if (outfile == NULL) {
		fprintf(stderr, "Unable to write out to the file '%s'.", filename);
		exit(EXIT_FAILURE);
	}
	//Prestring insertion (before the <lorem> delimiter)
	fprintf(outfile, "%s", prestring);
	fseek(outfile, 0L, SEEK_END);
	//Loremstring insertion (at the <lorem> delimiter)
	if (number_paragraph > 1 && number_paragraph < 1000){
		concat_string(number_paragraph);
		fprintf(outfile, "%s", loremstring);
	}
	else if (number_paragraph > 999) {
		//large strings, write after each 1000 paragraphs
		paragraph_iter = number_paragraph;
		//write out in blocks of 1000 paragraphs
		//first block of 1000, then decrement the paragraph iterator
		concat_string(1000);
		fprintf(outfile, "%s", loremstring);
		paragraph_iter -= 1000;
		while((paragraph_iter - 1000) > 0) {
			fseek(outfile, 0L, SEEK_END);
			fprintf(outfile, "%s", loremstring);
			paragraph_iter -= 1000;
		}
		// if there are less than 1000 remaining paragraphs, then add the remaining paragraphs in single block
		if (paragraph_iter > 0) {
			fseek(outfile, 0L, SEEK_END);
			//make the new loremstring with the proper number of paragraphs
			concat_string(paragraph_iter);
			fprintf(outfile, "%s", loremstring);
		}

	}
	//Poststring insertion (after the <lorem> delimiter)
	fseek(outfile, 0L, SEEK_END);
	fprintf(outfile, "%s", poststring);
	fclose(outfile);
}

void make_write_string() {
	//for < 1000 paragraphs, simply concatenate string and write out
	if (number_paragraph > 1 && number_paragraph < 1000){
		concat_string(number_paragraph);
		write_string();
	}
	else if (number_paragraph > 999) {
		//large strings, write after each 1000 paragraphs
		paragraph_iter = number_paragraph;
		//write out in blocks of 1000 paragraphs
		//first block use file write
		concat_string(1000);
		// If user requested standard out stream write
		if (standard_out){
			printf("%s",loremstring);
			while ((paragraph_iter - 1000) > 0){
				//lorem string now has 1000 paragraphs, write them out in blocks of 1000 until number of remaining paragraphs < 1000
				printf("%s", loremstring);
				paragraph_iter -= 1000; //decrement by 1000 that just included
			}
			if (paragraph_iter > 0){
				//if < 1000 paragraphs left, then concatenate all remaining and append
				concat_string(paragraph_iter);
				printf("%s", loremstring);
			}
		}
		//otherwise it is a file stream write
		else {
			if (! append){
				//write a new file if user did not request append to an existing file
				FILE* loremfile;
				loremfile = fopen(filename, "w");
				fprintf(loremfile, "%s", loremstring);
				fclose(loremfile);
				paragraph_iter -= 1000; //decrement iter by 1000 that were written to file
			}
			// use append in subsequent blocks after initial write or if this was requested as an append to existing file
			FILE* loremappend;
			loremappend = fopen(filename, "a");
			while ((paragraph_iter - 1000) > 0){
				//lorem string now has 1000 paragraphs, write them out in blocks of 1000 until number of remaining paragraphs < 1000
				fprintf(loremappend, "%s", loremstring);
				paragraph_iter -= 1000; //decrement by 1000 that just included
			}
			if (paragraph_iter > 0){
				//if < 1000 paragraphs left, then concatenate all remaining and append
				concat_string(paragraph_iter);
				append_string();
			}
			fclose(loremappend);
		}
	}
	else{
		//Single paragraph write (handles std out writes in the function)
		write_string();
		}
}


//simple string write
void write_string() {
	if (standard_out){
		//write to standard out rather than to a file
		printf("%s", loremstring);
	}
	else{
		//write to user specified or default file name (lorem.txt)
		FILE* loremfile;
		if (append){
			loremfile = fopen(filename, "a");
		}
		else{
			loremfile = fopen(filename, "w");
		}
		if (loremfile){
			fprintf(loremfile, "%s", loremstring);
			fclose(loremfile);
		}
	}
}

void append_string() {
	FILE* loremfile;
	loremfile = fopen(filename, "a");
	if (loremfile){
		fprintf(loremfile, "%s", loremstring);
		fclose(loremfile);
	}
}

void concat_string(int para_number) {
	//create a temp lorem string copy to use for contcatenation of subsequent paragraphs
	size_t length = strlen(lorem) + 1;
	loremstring = (char*)calloc(length, sizeof(char));
	strcpy(loremstring, lorem);	
	for (int i = 0; i < (para_number - 1); ++i){
		strcat(loremstring, "\n");
		strcat(loremstring, lorem);
	}
	if (para_number == 1){
		//just add a newline to it
		strcat(loremstring, "\n");
	}
}

void format_output() {
	if (number_paragraph == 1){
		// formatting for the response to the user.  if single paragraph, use singular 'paragraph' instead of 'paragraphs'
		paragraph_text = "paragraph";
	}
}

void get_replacement_strings() {
	//read the full file string into full_input_string
	read_input_file();
	//process the string to get the pre and post strings around the <lorem> marker
	tokenize_string();
}

// read in the input file string
void read_input_file () {
	//CREATES buffer THAT NEEDS TO BE FREED
	FILE    *infile;
	long    numbytes;
	 
	/* open an existing file for reading */
	infile = fopen(in_filename, "r");
	 
	/* quit if the file does not exist */
	if(infile == NULL){
		fprintf(stderr, "Unable to open the input file.");
		exit(EXIT_FAILURE);
	}
	 
	/* Get the number of bytes */
	fseek(infile, 0L, SEEK_END);
	numbytes = ftell(infile);
	 
	/* reset the file position indicator to 
	the beginning of the file */
	fseek(infile, 0L, SEEK_SET);	
	 
	/* grab sufficient memory for the 
	buffer to hold the text */
	buffer = (char*)calloc(numbytes, sizeof(char));	
	 
	/* memory error */
	if(buffer == NULL){
		fprintf(stderr, "Unable to allocate sufficient memory for the input file.");
		exit(EXIT_FAILURE);
	}
	 
	/* copy all the text into the buffer */
	fread(buffer, sizeof(char), numbytes, infile);
	fclose(infile);
}

void tokenize_string(){
	// CREATES prestring & poststring THAT NEED TO BE FREED.
	char *p;
	//is the replacement token in the string from the input file?
	if(!(p = strstr(buffer, token))) {
		fprintf(stderr, "Unable to locate the replacement token '<lorem>' in the input file. Is it included?");
		exit(EXIT_FAILURE);
	}
	//if so, copy the portion of the string that precedes the token
	prestring = (char*)calloc(p - buffer, sizeof(char));
	strncpy(prestring, buffer, p - buffer);
	prestring[p - buffer] = '\0';
	poststring = (char*)calloc(*(p + 7), sizeof(char));
	strcpy(poststring, p + 7);
}

void print_help(){
	printf("\nlorem Help\n");
	printf("-----------\n\n");
	printf("Description: Create a user-specified number of dummy text paragraphs that you can write to a file, append to or insert at a specific replacement location in an existing file, or write to standard out.\n\n");
	printf("Usage: lorem [-ahinorsv] [<positional argument>]\n\n");
	printf("Options:\n");
	printf("\t-a : Append to a file rather than write to (or overwrite) a file.\n\t     Include the -o option with the existing file path.\n");
	printf("\t-h : lorem help\n");
	printf("\t-i : Input file path for lorem text replacements.\n\t     Include the -r option and the delimiter <lorem> in the file\n\t     at the replacement site.\n");
	printf("\t-n : Number of lorem paragraphs.\n\t     Include a number after the option. Default = 1\n");
	printf("\t-o : Output file path.\n\t     Include a file path after the option. Default = \"lorem.txt\" \n");
	printf("\t-r : Insert lorem text in an existing file.\n\t     Include the delimiter <lorem> in the file at the replacement site\n\t     and use the -i option with the input file path.\n");
	printf("\t-s : Write to standard out instead of a file\n");
	printf("\t-v : lorem version\n");
	printf("\nNotes:\n");
	printf("To insert dummy text at a specific location within a file, add the delimiter <lorem> at the replacement site.  lorem will insert the requested number of paragraphs at this location with a single newline character following each paragraph.\n");
	printf("\nThere is a one million paragraph limit on the amount of text that lorem generates.  This is ~447 MiB, ~1.9 million lines, & 69 million words of text. If you need more than that, use the -a option and append the remanining number (up to 1 million paragraphs with each append) to the existing file.  Include the -n option with the number of additional paragraphs that you would like to append and the -o option with the file path of the file to which you intend to append the lorem text.\n");
}

void print_version() {
	printf("\nlorem version %s\n", VERSION);
	printf("Copyright %s %s\n", YEAR, DEVELOPER);
	printf("%s\n", LICENSE);
}