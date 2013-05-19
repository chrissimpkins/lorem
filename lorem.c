
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "lorem.h"

int main(int argc, char **argv) {
	char c;
	while ( (c = getopt(argc, argv, "ahsvn:o:") ) != -1) {
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
					// TO DO: set maximum number of paragraphs
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
	if (number_paragraph <= PARA_LIMIT) {
		make_write_string();
	}
	else {
		fprintf(stderr, "You requested %d lorem paragraphs.  The maximum is %d.\n", number_paragraph, PARA_LIMIT);
		exit(EXIT_FAILURE);
	}
	//respond to user with total number of paragraphs written to file (if not standard out stream write)
	if (! standard_out){
		//format the response string sent to user after completion
		format_output();
		printf("Wrote %d %s of lorem text to %s\n", number_paragraph, paragraph_text, filename);
	}

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
		if (! append){
			//write a new file if user did not request append to an existing file
			FILE* loremfile;
			loremfile = fopen(filename, "w");
			fprintf(loremfile, loremstring);
			fclose(loremfile);
			paragraph_iter -= 1000; //decrement iter by 1000 that were written to file
		}
		// use append in subsequent blocks after initial write or if this was requested as an append to existing file
		FILE* loremappend;
		loremappend = fopen(filename, "a");
		while ((paragraph_iter - 1000) > 0){
			//lorem string now has 1000 paragraphs, write them out in blocks of 1000 until number of remaining paragraphs < 1000
			fprintf(loremappend, loremstring);
			paragraph_iter -= 1000; //decrement by 1000 that just included
		}
		if (paragraph_iter > 0){
			//if < 1000 paragraphs left, then concatenate all remaining and append
			concat_string(paragraph_iter);
			append_string();
		}

	}
	else{
		//one paragraph, write the loremstring as is
		write_string();
	}

}

//simple string write
void write_string() {
	if (standard_out){
		//write to standard out rather than to a file
		printf(loremstring);
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
			fprintf(loremfile, loremstring);
			fclose(loremfile);
		}
	}
}

void append_string() {
	FILE* loremfile;
	loremfile = fopen(filename, "a");
	if (loremfile){
		fprintf(loremfile, loremstring);
		fclose(loremfile);
	}
}

void concat_string(int para_number) {
	//create a temp lorem string copy to use for contcatenation of subsequent paragraphs
	asprintf(&loremstring, lorem);
	for (int i = 0; i < (para_number - 1); ++i){
		strcat(loremstring, "\n");
		strcat(loremstring, lorem);
	}
}

void format_output() {
	if (number_paragraph == 1){
		// formatting for the response to the user.  if single paragraph, use singular 'paragraph' instead of 'paragraphs'
		paragraph_text = "paragraph";
	}
}

void print_help(){
	printf("\nlorem Help\n");
	printf("-----------\n\n");
	printf("Description: Create a user-specified number of dummy text paragraphs that you can write to a file, append to a file, or write to standard out.\n\n");
	printf("Usage: lorem [-ahnosv] [<positional argument>]\n\n");
	printf("Options:\n");
	printf("\t-a : Append to a file rather than write to (or overwrite) a file.\n\t     Include the -o option with the existing file path.\n");
	printf("\t-h : lorem help\n");
	printf("\t-n : Number of lorem paragraphs.\n\t     Include a number after the option. Default = 1\n");
	printf("\t-o : Output file path.\n\t     Include a file path after the option. Default = \"lorem.txt\" \n");
	printf("\t-s : Write to standard out instead of a file\n");
	printf("\t-v : lorem version\n");
	printf("\n\nNotes:\nThere is a one million paragraph limit on the amount of text that lorem generates.  This is ~447 MiB, ~1.9 million lines, & 69 million words of text. If you need more than that, use the -a option and append the remanining number (up to 1 million paragraphs with each append) to the existing file.  Include the -n option with the remaining number of paragraphs and the -o option with the existing file path.\n");
}

void print_version() {
	printf("\nlorem version %s\n", VERSION);
	printf("Copyright %s %s\n", YEAR, DEVELOPER);
	printf("%s\n", LICENSE);
}