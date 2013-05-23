/*------------------------------------------------------
*  lorem.c
*  Copyright 2013. Christopher Simpkins
*  MIT License
-------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "lorem.h"

int main(int argc, char **argv) {
	char c;
	while ( (c = getopt(argc, argv, "ahrsvb:e:i:n:o:t:") ) != -1) {
		switch (c) {
			case 'n':
				if (optarg == NULL){
					printf("Default to 1 paragraph of lorem ipsum text.  Enter a number with the -n option if you would like to include more.\n");
				}
				else{
					number_paragraph = atoi(optarg);
					if (number_paragraph == 0){
						printf("The number of paragraphs was not properly specified with the -n option.\n");
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
			case 'b':
				user_tagged = 1;
				if (optarg == NULL) {
					fprintf(stderr, "You did not enter a string to insert at the beginning of the paragraph.\n");
					exit(EXIT_FAILURE);
				}
				else {
					user_begin_tag = optarg; //the tag to be prepended to the paragraph (optional, defaults to end tag if included)
				}
				break;
			case 'e':
				user_tagged = 1;
				if (optarg == NULL) {
					fprintf(stderr, "You did not enter a string to insert at the end of the paragraph.\n");
					exit(EXIT_FAILURE);
				}
				else {
					user_end_tag = optarg; //the tag to be appended to the paragraph (optional, defaults to begin tag if it is included)
				}
				break;
			case 'h':
				print_help();
				exit(EXIT_SUCCESS);
			case 'i':
				if (optarg == NULL){
					fprintf(stderr, "You did not enter a file path to the input file for the text replacement.\n");
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
			case 't':
				user_insert_text = 1;
				if (optarg == NULL) {
					fprintf(stderr, "You did not enter a file path for the file that contains the text that you want to insert.");
					exit(EXIT_FAILURE);
				}
				else {
					insert_filename = optarg;
				}
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
	//concatenate strings to form number of paragraphs, write to proper stream
	//test for request below the paragraph limit (defined in PARA_LIMIT in lorem.h)
	if (number_paragraph <= PARA_LIMIT && replace == 0) {
		make_write_string();
		free(loremstring);
		//respond to user with total number of paragraphs written to file (if not standard out stream write)
		if (! standard_out){
			//format the response string sent to user after completion
			format_output();
			printf("Wrote %d %s of text to '%s'\n", number_paragraph, paragraph_text, filename);
			//free the loremstring that was created to hold the loremstring
		}
	}
	else if (number_paragraph <= PARA_LIMIT && replace == 1){
		get_replacement_strings();
		// Write out the string insertions in the file
		concat_write_replacement();
		printf("Inserted %d %s of text in the file '%s'.\n", number_paragraph, paragraph_text, filename);
		/* free the memory we used for the strings */
		free(buffer);
		free(prestring);
		free(poststring);
		free(loremstring);
	}
	else {
		fprintf(stderr, "You requested %d text paragraphs.  The maximum is %d.\n", number_paragraph, PARA_LIMIT);
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
	if (number_paragraph < 1000){
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
	if (number_paragraph > 0 && number_paragraph < 1000){
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
	if (sizeof(loremstring) > 0){
		free(loremstring);
	}
	//if user providing own text rather than the lorem text, read it in to insert_buffer
	if (user_insert_text) {
		read_user_insert_text();  // release insert_buffer at the end of use in this function below
	}
	// user requested a prepended and appended string for the paragraph
	if (user_tagged == 1){
		// assign the end to begin or begin to end if only specified one tag
		if (user_end_tag == NULL && user_begin_tag != NULL){
			user_end_tag = user_begin_tag;
		}
		else if (user_begin_tag == NULL && user_end_tag != NULL) {
			user_begin_tag = user_end_tag;
		}
		// determine size based on whether user provided text or using lorem text
		size_t length;
		if (user_insert_text) {
			length = strlen(insert_buffer) + strlen(user_begin_tag) + strlen(user_end_tag) + strlen("\n");
		}
		else {
			length = strlen(lorem) + strlen(user_begin_tag) + strlen(user_end_tag) + strlen("\n");
		}
		loremstring = (char*)calloc(((length*para_number) + 1), sizeof(char));
		char* tempstring = (char*)malloc(length);
		if (loremstring == NULL || tempstring == NULL) {
			fprintf(stderr, "Error allocating memory for the text.");
			exit(EXIT_FAILURE);
		}
		//add beginning tag
		strcpy(tempstring, user_begin_tag);
		//append text
		if (user_insert_text){
			strcat(tempstring, insert_buffer);
			//done with insert_buffer, free it
			free(insert_buffer);
		}
		else {
			strcat(tempstring, lorem);	
		}
		//append end tag
		strcat(tempstring, user_end_tag);
		//append a newline to make it legible when printed
		strcat(tempstring, "\n");
		//add first tagged paragraph to the loremstring variable
		strcpy(loremstring, tempstring);
		//then concatenate the remaining paragraphs
		for (int i = 0; i < (para_number - 1); ++i){
			strcat(loremstring, tempstring);
		}
		//release the tempstring memory and keep loremstring in memory to write to file
		free(tempstring);
	}
	// did not request tags appended / prepended to the paragraph
	else {
		//calculate size of either user specified text or the lorem text
		size_t length;
		if (user_insert_text){
			length = strlen(insert_buffer);
		}
		else {
			length = strlen(lorem_n);
		}
		loremstring = (char*)calloc(((length*para_number) + 1), sizeof(char));
		if (loremstring == NULL){
			fprintf(stderr, "Error allocating memory for the text.");
			exit(EXIT_FAILURE);
		}
		//copy the appropriate string to the loremstring string variable
		if (user_insert_text){
			strcpy(loremstring, insert_buffer);
			for (int i = 0; i < (para_number - 1); ++i){
				strcat(loremstring, insert_buffer);
			}
			//done with insert_buffer, free it
			free(insert_buffer);
		}
		else {
			strcpy(loremstring, lorem_n);
			for (int i = 0; i < (para_number - 1); ++i){
				strcat(loremstring, lorem_n);
			}
		}
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
		fprintf(stderr, "Unable to open the file in order to insert the text.\n");
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
		fprintf(stderr, "Unable to allocate sufficient memory for the file where you want the text to be inserted.\n");
		exit(EXIT_FAILURE);
	}
	 
	/* copy all the text into the buffer */
	fread(buffer, sizeof(char), numbytes, infile);
	fclose(infile);
}

void read_user_insert_text() {
	//CREATES insert_buffer THAT NEEDS TO BE FREED (released in the concat_string() function where it is called)
	FILE    *infile;
	long    numbytes;
	 
	/* open an existing file for reading */
	infile = fopen(insert_filename, "r");
	 
	/* quit if the file does not exist */
	if(infile == NULL){
		fprintf(stderr, "Unable to open the file that contains your insertion text.  Please check the file path and confirm that the file exists.\n");
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
	insert_buffer = (char*)calloc(numbytes, sizeof(char));
	 
	/* memory error */
	if(insert_buffer == NULL){
		fprintf(stderr, "Unable to allocate sufficient memory for the text that you wanted to insert.\n");
		exit(EXIT_FAILURE);
	}
	 
	/* copy all the text into the buffer */
	fread(insert_buffer, sizeof(char), numbytes, infile);
	fclose(infile);
}

void tokenize_string(){
	// CREATES prestring & poststring THAT NEED TO BE FREED.
	char *p;
	//is the replacement token in the string from the input file?
	if(!(p = strstr(buffer, token))) {
		fprintf(stderr, "Unable to locate the replacement token '<lorem>' in the input file. Is it included?\n");
		exit(EXIT_FAILURE);
	}
	size_t postsize = strlen((p+7)) + 1;
	//if so, copy the portion of the string that precedes the token
	if (sizeof(prestring) > 0) {
		free(prestring);
	}
	prestring = (char*)calloc((p - buffer), sizeof(char));
	if (prestring == NULL){
		fprintf(stderr, "Error allocating memory to perform the text replacement.\n");
		exit(EXIT_FAILURE);
	}

	strncpy(prestring, buffer, p - buffer);
	prestring[(p - buffer)] = '\0';
	if (sizeof(poststring) > 0) {
		free(poststring);
	}
	poststring = (char*)calloc(postsize, sizeof(char));
	if (poststring == NULL){
		fprintf(stderr, "Error allocating memory to perform the text replacement.\n");
		exit(EXIT_FAILURE);
	}
	strcpy(poststring, p + 7);
}

void print_help(){
	printf("\nLorem Help\n");
	printf("version %s\n", VERSION);
	printf("------------------------\n\n");
	printf("Description: Create a user-specified number of dummy text paragraphs that you can write to a file, append to or insert at a specific replacement location in an existing file, or write to standard out.\n\n");
	printf("Usage: lorem [-abehinortsv] [<positional argument>]\n\n");
	printf("Options:\n");
	printf("\t-a : Append to a file rather than write to (or overwrite) a file.\n\t     Include the -o option with the existing file path.\n");
	printf("\t-b : String or character to insert at the beginning of the paragraph.\n\t     Include the string as the argument & quotes around html tags.\n\t     Defaults to the end tag if not specified.\n");
	printf("\t-e : String or character to insert at the end of the paragraph.\n\t     Include the string as the argument & quotes around html tags\n\t     Defaults to the begin tag if not specified.\n");
	printf("\t-h : lorem help\n");
	printf("\t-i : Input file path for the file where text replacements take place.\n\t     Include the -r option and the delimiter <lorem> in the file\n\t     at the replacement site.\n");
	printf("\t-n : Number of text paragraphs.\n\t     Include a number after the option. Default = 1\n");
	printf("\t-o : Output file path.\n\t     Include a file path after the option. Default = \"lorem.txt\" \n");
	printf("\t-r : Insert text in an existing file.\n\t     Include the delimiter <lorem> in the file at the replacement site\n\t     and use the -i option with the input file path.\n");
	printf("\t-s : Write to standard out instead of to a file\n");
	printf("\t-t : Input file path for user-supplied text (to replace built-in lorem).\n\t     Include the file path to an existing file that includes the text.\n");
	printf("\t-v : lorem version\n");
	printf("\nNotes:\n");
	printf("To insert text at a specific location within a file, add the delimiter <lorem> at the replacement site.  lorem will insert the requested number of paragraphs at this location with a single newline character following each paragraph.\n");
	printf("\nUse quotes around arguments that include characters like \' \" < > etc. For instance, you should enter the html p tag with a class like this: \"<p class='theclass'>\". To include quotes, enter them like this: '\"'\n");
	printf("\nIf you specify a beginning and end string to add to the paragraph(s), they will be inserted as entered with a newline character following the last character of the appended string.  If you indicate an insertion string for the beginning of the paragraph without specifying one for the end, the beginning tag will be added at the end as well.  If you specify only an insertion string for the end of the paragraph, then it will be inserted at the beginning as well.\n");
	printf("\nThere is a one million paragraph limit on the amount of text that lorem generates.  This is ~447 MiB, ~1 million lines, & 69 million words of text. If you need more than that, use the -a option and append the remanining number (up to 1 million paragraphs with each append) to the existing file.  Include the -n option with the number of additional paragraphs that you would like to append and the -o option with the file path of the file to which you intend to append the lorem text.\n");
}

void print_version() {
	printf("\nlorem version %s\n", VERSION);
	printf("Copyright %s %s\n", YEAR, DEVELOPER);
	printf("%s\n\n", LICENSE);
}