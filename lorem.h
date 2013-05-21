
//FUNCTION VARIABLES  
char* loremstring;		//used to make the lorem string
char* in_filename;
char* buffer;
char* prestring; 		//from input file - precedes the insertion site of lorem text
char* poststring; 		//from input file - after the insertion site of the lorem text
char* paragraph_text = "paragraphs";
int paragraph_iter = 0;

//DEFAULTS
int number_paragraph = 1;       // Default number of paragraphs
char* filename = "lorem.txt";   // Default out file path
char* token = "<lorem>";		// Default replacement token. Inserted in an in file string as site of lorem replacement

//FLAGS
int standard_out = 0;           //flag for print to stdout rather than a file
int append = 0;					//flag for append to file rather than overwrite file
int replace = 0;

//CONSTANTS
#define VERSION ("0.2.2")
#define DEVELOPER ("Christopher Simpkins")
#define YEAR ("2013")
#define LICENSE ("MIT License")
#define PARA_LIMIT (int)1000000
const char* lorem = "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
const char* lorem_n = "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.\n";

//FUNCTION DECLARATIONS
void print_help();
void print_version();
void make_write_string();
void format_output();
void write_string();
void append_string();
void concat_string();
void get_replacement_strings();
void read_input_file ();
void tokenize_string();
void concat_write_replacement();

