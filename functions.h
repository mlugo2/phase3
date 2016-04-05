#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <string.h>

// Symbol Table
typedef struct {
        char name[6];
        int address;
} Symtab;


// Opcode Table
typedef struct {
        char name[6];
        int code;
} Optab;
  
  Optab opcode [31] =
{ {"ADD\0", 24}, {"AND\0", 88},{"BYTE\0", 252}, {"COMP\0", 40}, {"DIV\0", 36}, {"END\0", 251}, {"J\0", 60},
  {"JEQ\0", 48}, {"JGT\0", 52}, {"JLT\0", 56}, {"JSUB\0", 72}, {"LDA\0", 0},
  {"LDCH\0", 80}, {"LDL\0", 8}, {"LDX\0", 4}, {"MUL\0", 32}, {"OR\0", 68}, {"RESB\0", 254},{"RESW\0", 255},
  {"RD\0", 216}, {"RSUB\0", 76}, {"STA\0", 12},{"START\0", 250}, {"STCH\0", 84}, {"STL\0", 20},
  {"STX\0", 16}, {"SUB\0", 28}, {"TD\0", 224}, {"TIX\0", 44}, {"WD\0", 220},{"WORD\0", 253} };


/* Prototypes for the functions */
char * s_gets(char * st, int n);
void clear(char[], int n);
void authenticator(char [], char [], char []);
void displayCommnads();
void welcomeMessage();

/* Directive functions */
void assemble(char []);

/* Directive dependencies */
void parameterFix(char [], char [], char []);
_Bool symtabSearch(char [], Symtab []);
_Bool optabSearch(char [], int *, int );
int errorChecker(char [], char [], char [], int);
_Bool byteOperandCheck(char [], int *);
_Bool hexCheck( char [] );


/********************************************************
*               authenticator()                         *
*                                                       *
*  This fucntion takes three char arrays as paramters.  *
*  Using embedded if/else statements it determines      *
*  which commands require paramaters as well as which   *
*  don't.                                               *
********************************************************/
void authenticator(char comm[], char p1[], char p2[])
{

        /* If no paramaters needed only parameter 1 is checked.
           If only one parameter is needed both parameters are checked.
           If two parameters are needed both are checked.
        */
        if(!strcmp(comm,"load"))
                 {
                        if(p1[0] == '\0')
                                printf("Error: Parameter needed.\n");
                        else if(p2[0] != '\0')
                                printf("Error: Second parameter not required.\n");
                        else
                                printf("Command is %s.\n", comm);
                }
        else if(!strcmp(comm,"execute"))
                {
                        if(p1[0] != '\0')
                                printf("Error: No parameters needed.\n");
                        else
                                printf("Command is %s.\n", comm);
                }
        else if(!strcmp(comm,"debug"))
                {
                        if(p1[0] != '\0')
                                printf("Error: No parameters needed.\n");
                        else
                                printf("Command is %s.\n", comm);
                }
        else if(!strcmp(comm,"dump"))
                {
                        if(p1[0] == '\0')
                                printf("Error: First parameter incorrect.\n");
                        else if(p2[0] == '\0')
                                printf("Error: Second parameter incorrect.\n");
                        else
                                printf("Command is %s.\n", comm);
                }
        else if(!strcmp(comm,"help"))
                {
                        if(p1[0] != '\0')
                                printf("Error: No parameters needed.\n");
                        else
                                displayCommnads();
                }
        else if(!strcmp(comm,"assemble"))
                {
                        if(p1[0] == '\0')
                                printf("Error: Parameter needed.\n");
                        else if(p2[0] != '\0')
                                printf("Error: Second parameter not required.\n");
                        else{
                               assemble(p1);
                        }
                }
        else if(!strcmp(comm,"directory"))
                system("ls");
        else if(!strcmp(comm,"exit"))
                 {
                        if(p1[0] != '\0')
                                printf("Error: No  needed.\n");
                }
        else
        {
               printf("Error: %s is not a valid command.\n", comm); // ¯\_(ツ)_/¯
               displayCommnads();
        }
}

_Bool byteOperandCheck(char operand[], int *locctr)
{
	int len;
	
	len = strlen(operand) - 1;
	
	int strOperand = 2;
	int lstOperand = len;
	
	if (operand[0] != 'C' && operand[0] != 'X' && operand[1] != '\'' &&  operand[len] != '\'')
	{
		return 1;
	}
	else if ( operand[0] == 'C' )
	{
		if ( (lstOperand - strOperand) > 30)
			return 1;
			
		*locctr += (lstOperand - strOperand);	
		return 0;
	}
	else 
	{
		if ( (lstOperand - strOperand)%2 != 0 )
			return 1;
			
		*locctr += (lstOperand - strOperand) / 2;
		return 0;
	}
	
}

/********************************************************
*                       clear()                         *
*                                                       *
*  This fucntion takes any given char array and fills   * 
*  it with null characters to erase previous inputs.    *
********************************************************/
void clear( char string[], int n)
{
        int i;
        for (i = 0; i < n; i++)
                string[i] = '\0';

}

/********************************************************
*                  displayCommnads()                    *
*                                                       *
*  This fucntion displays all available commands and    *
*  parameters.                                          *
********************************************************/
void displayCommnads()
{

    printf("\nload filename: Loads the specified file.\n\n");
	printf(	"execute: Executes the program that was previously loaded in memory.\n\n");
	printf(	"debug: Executes in debug mode.\n\n");
	printf(	"dump start end: Calls the dump function, passing the values of start and end.\n\n");
	printf(	"help: Prints out a list of available commands.\n\n");
	printf(	"assemble filename: Assembles an SIC assembly language program into a load module and store it in a file.\n\n");
	printf(	"directory: Lists the files stored in the current directory.\n\n");
	printf(	"exit: Exit from the simulator.\n\n");

}

/********************************************************
*                     s_gets()                          *
*                                                       *
*  This fucntion takes in a char array and array length *
*  to get rid of any '\n'.								*
********************************************************/
char * s_gets(char * st, int n)
{
	char * ret_val;
	char * find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');		// Look for newline
		if(find)						// if the address is not NULL,
			*find = '\0';				// place a null character there
		else
			while (getchar() != '\n')
				continue;				//dispose of rest of line
	}
	return ret_val;
}

/********************************************************
*                       split()                         *
*                                                       *
*  This fucntion takes in the users input and divides   *
*  into the cammand and two parameters. Any more        *
*  parameters than two are placed in extra char array.  *
********************************************************/
void split( char line[], char comm[], char p1[], char p2[], char extra[])
{

	int i, j;

	i = 0;
	j = 0;

	// Traverses any spaces to the first character
	while ( line[i] == ' ' || line[i] == '\t' )
		i++;

	// Once a character is found copy into comm
	// until another space or null character.
	while( line[i] != '\0')
	{

		comm[j] = line[i];
                
		++j;
		++i;
 
		if (line[i] == ' ' || line[i] == '\0' || line[i] == '\t')
		{
			comm[j] = '\0';
			break;
		}
    
	}

	// Find the next string to be copied into first paramenter.
	while ( line[i] == ' ' || line[i] == '\t')
		i++;

	if ( line[i] != '\0' )
	{
		j = 0;
		while( line[i] != '\0')
		{

			p1[j] = line[i];

			++j;
			++i;

			if (line[i] == ' ' || line[i] == '\0' || line[i] == '\t')
			{
				p1[j] = '\0';
				break;
			}
		}
	}


	// Find the next string to be copied into second paramenter.
	while ( line[i] == ' ' || line[i] == '\t')
		i++;

	if ( line[i] != '\0' )
	{
		j = 0;
		while( line[i] != '\0')
		{

			p2[j] = line[i];

			++j;
			++i;

			if (line[i] == ' ' || line[i] == '\0' || line[i] == '\t')
			{
				p2[j] = '\0';
				break;
			}
		}
	}

	// Find the next string
	while ( line[i] == ' ' || line[i] == '\t')
		i++;

	if ( line[i] != '\0' )
	{
		j = 0;
		while( line[i] != '\0')
		{

			extra[j] = line[i];

			++j;
			++i;

			if ( line[i] == '\0')
			{
				extra[j] = '\0';
				break;
			}
		}

	}

}


/********************************************************
*              welcomeMessage()                         *
*                                                       *
*  This fucntion displays a welcome message to the user *
*  as well as which command to start with.		*
********************************************************/
void welcomeMessage()
{
        static unsigned char asciipic_txt[] = {                                                
        0x20, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x20, 0x5f, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5f, 0x5f, 0x5f,
        0x5f, 0x5f, 0x20, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x20, 0x0a, 0x2f, 0x20,
        0x20, 0x5f, 0x5f, 0x5f, 0x28, 0x5f, 0x29, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x7c, 0x20, 0x20, 0x5f, 0x20, 0x20,
        0x2f, 0x20, 0x20, 0x5f, 0x5f, 0x5f, 0x7c, 0x0a, 0x5c, 0x20, 0x60, 0x2d,
        0x2d, 0x2e, 0x20, 0x5f, 0x20, 0x5f, 0x20, 0x5f, 0x5f, 0x20, 0x5f, 0x5f,
        0x5f, 0x20, 0x20, 0x20, 0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x20, 0x5c, 0x20,
        0x60, 0x2d, 0x2d, 0x2e, 0x20, 0x0a, 0x20, 0x60, 0x2d, 0x2d, 0x2e, 0x20,
        0x7c, 0x20, 0x7c, 0x20, 0x27, 0x5f, 0x20, 0x60, 0x20, 0x5f, 0x20, 0x5c,
        0x20, 0x20, 0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x60, 0x2d, 0x2d,
        0x2e, 0x20, 0x5c, 0x0a, 0x2f, 0x5c, 0x5f, 0x5f, 0x2f, 0x20, 0x7c, 0x20,
        0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x20,
        0x5c, 0x20, 0x5c, 0x5f, 0x2f, 0x20, 0x2f, 0x5c, 0x5f, 0x5f, 0x2f, 0x20,
        0x2f, 0x0a, 0x5c, 0x5f, 0x5f, 0x5f, 0x5f, 0x2f, 0x7c, 0x5f, 0x7c, 0x5f,
        0x7c, 0x20, 0x7c, 0x5f, 0x7c, 0x20, 0x7c, 0x5f, 0x7c, 0x20, 0x20, 0x5c,
        0x5f, 0x5f, 0x5f, 0x2f, 0x5c, 0x5f, 0x5f, 0x5f, 0x5f, 0x2f, 0x0a

        };

        system("clear");
        printf("%s\n", asciipic_txt);
        printf("Welcome to Sim OS 2.0\n");
        printf("For supported commands type: help\n\n");

} 

// This is the fucntion for the assmble directive

void assemble(char fileName [])
{

	char outName[64];
	char line[256];
	FILE *in, *out;
    int locctr;
    int error = 0;
    int index, opIndex;
	int intOperand = 0;	// Used when the operand is a number
	
	Symtab symbolTable[500] = {0};
	Symtab specialTable[5] = {0};
	
	// Variables for split
    char label[50], instruction[50], operand[50];
    char * pch;

    // initialize
    label[0], instruction[0], operand[0] = '\0';

	// get file names from user
	strcpy(outName, "intermediate");

	// open input and output files
    out = fopen (outName, "w");

	if ( (in = fopen(fileName, "r")) == NULL  )
	{
		printf("Can't open %s for reading.\n", fileName);
		return;
	}
    else {
                /************************************************
                *                   PASS 1                      *
                ************************************************/
				
                // Traverses any comments
                while (fgets(line, sizeof(line), in) && line[0] == '.' )
					continue;

                // The first line is a special case
                sscanf(line,"%s %s %s %*s", label, instruction, operand);
                
                if ( strcmp(instruction, "START") == 0)
                {
                        // Saving program name and starting address
                        strcpy(specialTable[0].name, label);
                        sscanf(operand, "%d", &specialTable[0].address);

                        // Initialize LOCCTR to starting address
                        sscanf(operand, "%x", &locctr);

                        // Write line to intermediate file
                        fprintf(out, "%s", line);
                        
                        // Error checking
                        error = errorChecker(label, instruction, operand, error);

						fprintf(out, "%d\n", error);
                }
                else
                {
                        locctr = 0;
                }
                
                // Read next line
                fgets(line, sizeof(line), in);
                
                // Split read line
                sscanf(line,"%s %s %s %*s", label, instruction, operand);
                parameterFix(label, instruction, operand);

                index = 0;
             	while ( strcmp(instruction, "END") != 0 )
	        {
						// Get string length to check blank lines
						int lineLength = strlen(line) - 1;

                        // If line is not a comment
                        if(line[0] != '.' && lineLength > 0)
                        {
							// Reinitialize error
							error = 0;
								
                                // Write line to intermediate file
								fprintf(out, "%s", line);

                                // If there is a label in instructions
                                if ( label[0] != '\0')
                                {
                                        // Search SYMTAB for lable
                                        if(symtabSearch(label, symbolTable))
                                                // set error flag for duplicate label
                                                error = error | 1;
                                        else
                                        {
                                                // Inserting label and locctr into SYMTAB
                                                strcpy(symbolTable[index].name, label);
                                                symbolTable[index].address = locctr;
                                        }
                                        
                                        // Update index for SYMTAB
										index ++;
                                
                                } // end if symbol

                                // Search for OPCODE in OPTAB
                                if(optabSearch(instruction, &opIndex, 1))
                                {
									// Error checking blank operand (4)
									if ( strcmp(instruction, "RSUB") == 0 )
									{	
										if ( operand[0] != '\0')
											error = error | 4;
									}
									else if (operand[0] == '\0')
											error = error | 4;

									fprintf(out, "%x\n", locctr);
									locctr += 3;
								}
								else if( strcmp(instruction, "WORD") == 0)
								{
									// Error checking blank operand
									if ( operand[0] == '\0' || !hexCheck(operand))
										error = error | 8;
									
									fprintf(out, "%x\n", locctr);
									locctr += 3;
								}
								else if ( strcmp(instruction, "RESW") == 0)
								{
									// Error checking blank operand
									if ( operand[0] == '\0'|| !hexCheck(operand))
										error = error | 8;
										
									fprintf(out, "%x\n", locctr);
									sscanf(operand, "%d", &intOperand);
									locctr += 3*intOperand;
								}
								else if ( strcmp(instruction, "RESB") == 0)
								{
									// Error checking blank operand
									if ( operand[0] == '\0'|| !hexCheck(operand))
										error = error | 8;
										
									fprintf(out, "%x\n", locctr);
									sscanf(operand, "%d", &intOperand);
									locctr += intOperand;
								}
								else if ( strcmp(instruction, "BYTE") == 0)
									{
										// Check operand for BYTE directive
										if ( byteOperandCheck(operand, &locctr))
										{
												error = error | 8;
										}
											
										fprintf(out, "%x\n", locctr);
											
									}
								else
								{
									// Set error flag for missing instruction (256)
									error = error | 256;
								}
								             
								// Check too many symbols
								if ( index > 499 )
								           error = error | 64;
								       
								// Check for remaining errors
								error = errorChecker(label, instruction, operand, error);  
									
								// Write to file
								fprintf(out, "%x\n", opcode[opIndex].code);
								fprintf(out, "%s\n", operand);
								fprintf(out, "%d\n", error);
				
								// Clear for next line to be read
								clear(label, 50);
								clear(instruction, 50);
								clear(operand, 50);
									
                        } // end if not a comment
                
                // Read next line and check for end of file
                if (fgets(line, sizeof(line), in) == NULL)
					break;
                
                // Split read line
                sscanf(line,"%s %s %s %*s", label, instruction, operand);
                parameterFix(label, instruction, operand);         
                
	        } // end while not END
	        
	        if ( strcmp(instruction, "END") == 0)
            {
				int programLength = locctr + 3 - specialTable[0].address;
	        
				error = 0;
	        
				// Write line to intermediate file
				fprintf(out, "%s %s %s\n", label, instruction, operand);
			
				// Retrieve the opcode
				optabSearch(instruction, &opIndex, 3);
			
				if(!symtabSearch(label, symbolTable))
					error = error | 32;
				
				if ( programLength > 32000)
					error = error | 128;
					
				error = errorChecker(label, instruction, operand, error);
			
				// Write lines to intermediate file
				fprintf(out, "%x\n", locctr);
				fprintf(out, "%x\n", opcode[opIndex].code);
				fprintf(out, "%s\n", operand);
				fprintf(out, "%d\n", error);	
			}
	        
        }// end Pass 1
	
	fclose(in);
	fclose(out);
	
	//--------------------------------------------------------------------------------
	
	void readIntermediateLine(char statement[], char strAddress[], char strOpcode[], char operand[], char strError[],int *,int *,int *, FILE *in );
	
	// String varibles for input from intermediate file
	char statement[256], strAddress[7], strError[16], strOpcode[4];
	
	statement[0] = '\0';
	
	// Integer varibles for conversion from string
	int intAddress, intError, intOpcode;
	
	clear(label, 50);
    clear(instruction, 50);
	clear(operand, 50);
	clear(fileName, 64);
	clear(outName, 64);
	strcpy(fileName, "intermediate");
	strcpy(outName, "objectfile");
	
	// Open input and output file
	out = fopen (outName, "w");
	
	if( (in = fopen(fileName, "r")) == NULL){
		
		printf("Can't open %s for reading.\n", fileName);
		return;
	}
	else
	{
		/************************************************
        *                   PASS 2                      *
		************************************************/
		
		// Read first line from intermediate file
		fgets(line, sizeof(line), in);
		
		printf("Line: %s", line);
		
		// Split read line
        sscanf(line,"%s %s %s %*s", label, instruction, operand);
        parameterFix(label, instruction, operand);
        
        // Search for opcode
        optabSearch(instruction, &opIndex, 2);
        
        // If opcode is start
        if (opcode[opIndex].code == 250)
		{
			puts("it is start\n");
			// Check for error
			fgets(line, sizeof(line), in);
			
			// Read next line
			readIntermediateLine( statement, strAddress, strOpcode, operand, strError, &intAddress, &intError, &intOpcode,in );
			
			printf("statement: %s", statement);
			printf("address: %d\n", intAddress);
			printf("opcode: %d\n", intOpcode);
			printf("operand: %s", operand);
			printf("error: %d\n", intError);
			
		}
		
	}// end Pass 2
		
	fclose(in);
	fclose(out);
	
	puts("File assembled.");

}

void readIntermediateLine(char statement[], char strAddress[], char strOpcode[], char operand[], char strError[], int *intAddress, int *intError, int *intOpcode, FILE *in ){
	
	char line[256];
	line[0] = '\0';
	
	fgets(line, sizeof(line), in);
	strcpy(statement, line);
	fgets(line, sizeof(line), in);
	strcpy(strAddress, line);
	fgets(line, sizeof(line), in);
	strcpy(strOpcode, line);
	fgets(line, sizeof(line), in);
	strcpy(operand, line);
	fgets(line, sizeof(line), in);
	strcpy(strError, line);
	
	sscanf(strAddress, "%d", intAddress);
	sscanf(strOpcode, "%d", intOpcode);
	sscanf(strError, "%d", intError);
	
	
}

void parameterFix(char p1[], char p2[], char p3[])
{
        _Bool found = 0;
        int i;

        // Check to see if label is a mnemonic
        for( i = 0; i < 30; i++)
                if(strcmp(p1, opcode[i].name) == 0)
                {       
                        found = 1;
                        break;
                }

        // If label is a mnemonic place in correct parameter
        if (found == 1)
        {
                clear(p3, 50);
                strcpy(p3, p2);
                clear(p2, 50);
                strcpy(p2, p1);
                clear(p1, 50);

                // Special case for RSUB
                if(strcmp(p2, "RSUB") == 0)
                        clear(p3, 50);
        }

}

_Bool symtabSearch(char key[], Symtab symtab[])
{

        int min = 0;
        int max = 499;
        
        while ( min <= max)
        {
                
                int mid = (min + max) /2;
                if ( strcmp(symtab[mid].name, key) == 0) return 1;
                else if (strcmp(symtab[mid].name, key) < 0) min = mid + 1;
                else max = mid -1;
                
        }

       return 0;      
}

_Bool optabSearch(char key[], int  *n, int code)
{
		if (key[0] == '\0')
			return 0;
	
		int min = 0;
		int max = 30;
        
        while ( min <= max)
        {

                int mid = (min + max) /2;                
                if ( strcmp(opcode[mid].name, key) == 0){
					 *n = mid;
					 return 1;
				 }
                else if (strcmp(opcode[mid].name, key) < 0) min = mid + 1;
                else max = mid -1;
                
        }

       return 0;
}

int errorChecker(char label[], char instruction[], char operand[], int error)
{
	int index = 0;
	int intLable;
	int operandLength = strlen(operand);
	
	// Check for all/any errors with label
	int strLength = strlen(label);
	if ( strLength > 6 )	// Label too long (2)
		error = error | 2;
		 
	// Check label for leading digits
	if ( isdigit(label[0]) )
		error = error | 2;
		
	// Check label and operands for reserved words(4)
	if( optabSearch(label, &index, 3) || optabSearch(operand, &index, 3) )
		error = error | 4;
	
	if ( strcmp( instruction, "START") == 0 )
	{
		// Check for all/any errors with label
		int strLength = strlen(label);
		if ( strLength > 6 )	// Label too long (2)
			error = error | 2;	
			
		// Operand for START should be hex
		// if hex should start with '0'
		// if begin 'A' - 'Z'
		if ( !hexCheck(operand))
			error = error | 16;
			
		return error;	
	}
	else if ( strcmp ( instruction, "END") == 0 )
	{
		if ( isdigit(operand[0]) || operand[0] == '\0')
			error = error | 32;

		return error;
	}
	else
	{
		// Check hex are 'A' - 'Z'	
		if (!isalpha(operand[0]) && !hexCheck(operand) && operand[0] != '\0')
			error = error | 4;
		
		return error;
	}

}

_Bool hexCheck( char num[])
{
		int numLength = strlen(num);
		if ( isdigit(num[0]) && numLength > 0)
		{
			int i;
			for ( i = 1; i < numLength; i++)
			{
				if ( isalpha(num[i]) && ( num[i] < 'A' || num[i] > 'F'))
					return 0;
			}
		}
		else
			return 0;
			
		return 1;
}

#endif
