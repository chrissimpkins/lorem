
//FUNCTION VARIABLES
char* loremstring = NULL;
char* paragraph_text = "paragraphs";
int paragraph_iter = 0;

//DEFAULTS
int number_paragraph = 1;       // Default number of paragraphs
char* filename = "lorem.txt";   // Default out file path

//FLAGS
int standard_out = 0;           //flag for print to stdout rather than a file
int append = 0;					//flag for append to file rather than overwrite file

//CONSTANTS
#define VERSION ("0.1.8")
#define DEVELOPER ("Christopher Simpkins")
#define YEAR ("2013")
#define LICENSE ("MIT License")
#define PARA_LIMIT (int)1000000
const char* lorem = "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.\n";

//FUNCTION DECLARATIONS
void print_help();
void print_version();
void make_write_string();
void format_output();
void write_string();
void append_string();
void concat_string();

