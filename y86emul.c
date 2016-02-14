#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y86emul.h"

int registers[9]; /*Declares register array*/

int programCounter; /*Declares program counter*/

char *memoryArray; /*Declares memory array*/

int ZF, OF, SF; /*Declares zero flag, overflow flag, and sign flag*/

/*
 * Increments the program counter by 1.
 */

void executeNOP(unsigned char *byte) {

	programCounter += 1;

}

/*
 * Puts the value stored in one register into another.
 */

void executeRRMOVL(unsigned char *byte) {

	bitField *newBitField = (bitField *)(memoryArray+programCounter+1);

	int registerIndexUpper = newBitField->upperHalf;
	int registerIndexLower = newBitField->lowerHalf;


	if ((registerIndexUpper >= 0 && registerIndexUpper <= 8) && (registerIndexLower >= 0 && registerIndexLower <= 8)) {

		registers[registerIndexUpper] = registers[registerIndexLower];

		programCounter += 2;

	}

	else {

		status = ERR;

	}

}

/*
 * Puts an immediate value into a register.
 */

void executeIRMOVL(unsigned char *byte) {

	bitField *newBitField = (bitField *)(memoryArray+programCounter+1);

	int registerIndex = newBitField->upperHalf;

	if ((newBitField->lowerHalf == 0xf) && (registerIndex >= 0 && registerIndex <= 8)) {

		int *num = (int *)(memoryArray+programCounter+2);

		registers[registerIndex] = *num;

		programCounter += 6;

	}

	else {

		status = ERR;

	}

}

/*
 * Stores the value of a register in memory.
 */

void executeRMMOVL(unsigned char *byte) {

	bitField *newBitField = (bitField *)(memoryArray+programCounter+1);

	int *num = (int *)(memoryArray+programCounter+2);

	int registerIndexUpper = newBitField->upperHalf;
	int registerIndexLower = newBitField->lowerHalf;


	if ((registerIndexUpper >= 0 && registerIndexUpper <= 8) && (registerIndexLower >= 0 && registerIndexLower <= 8)) {

		int valueOfUpperRegister = registers[registerIndexUpper];
		int valueOfLowerRegister = registers[registerIndexLower];

		int address = valueOfUpperRegister+*num;

		int *memArray = (int *)(memoryArray+address);

		*memArray = valueOfLowerRegister;

		programCounter += 6;

	}

	else {

		status = ERR;

	}

}

/*
 * Stores a value in memory in a register.
 */

void executeMRMOVL(unsigned char *byte) {

	bitField *newBitField = (bitField *)(memoryArray+programCounter+1);

	int *num = (int *)(memoryArray+programCounter+2);

	int registerIndexUpper = newBitField->upperHalf;
	int registerIndexLower = newBitField->lowerHalf;


	if ((registerIndexUpper >= 0 && registerIndexUpper <= 8) && (registerIndexLower >= 0 && registerIndexLower <= 8)) {

		int valueOfUpperRegister = registers[registerIndexUpper];

		int address = valueOfUpperRegister+*num;

		int *memArrayAddress = (int *)(memoryArray+address);

		registers[registerIndexLower] = *memArrayAddress;

		programCounter += 6;

	}

	else {

		status = ERR;

	}

}

/*
 * Performs the addl, subl, andl, xorl, and mull operations,
 * updating (or not updating) the flags accordingly.
 */

void executeOP1(unsigned char *byte) {

	bitField *newBitField = (bitField *)(memoryArray+programCounter+1);
	int registerIndexUpper = newBitField->upperHalf;
	int registerIndexLower = newBitField->lowerHalf;

		switch (*byte) {

		case 0x60:
			if ((registerIndexUpper >= 0 && registerIndexUpper <= 8) && (registerIndexLower >= 0 && registerIndexLower <= 8)) {

				int valueOfUpperRegister = registers[registerIndexUpper];
				int valueOfLowerRegister = registers[registerIndexLower];

				int sum = valueOfUpperRegister + valueOfLowerRegister;

				registers[registerIndexUpper] = sum;

				if (sum == 0) {

					ZF = 1;

				}

				else {

					ZF = 0;

				}

				if ((valueOfLowerRegister > 0 && valueOfUpperRegister > 0 && sum < 0) || (valueOfLowerRegister < 0 && valueOfUpperRegister < 0 && sum > 0)) {

					OF = 1;

				}

				else {

					OF = 0;

				}

				if (sum < 0) {

					SF = 1;

				}

				else {

					SF = 0;

				}

				programCounter += 2;

			}

			else {

				status = ERR;

			}

			break;

		case 0x61:
			if ((registerIndexUpper >= 0 && registerIndexUpper <= 8) && (registerIndexLower >= 0 && registerIndexLower <= 8)) {

				int valueOfUpperRegister = registers[registerIndexUpper];
				int valueOfLowerRegister = registers[registerIndexLower];

				int difference = valueOfUpperRegister - valueOfLowerRegister;

				registers[registerIndexUpper] = difference;

				if (difference == 0) {

					ZF = 1;

				}

				else {

					ZF = 0;

				}

				if ((valueOfLowerRegister < 0 && valueOfUpperRegister > 0 && difference < 0) || (valueOfLowerRegister > 0 && valueOfUpperRegister < 0 && difference > 0)) {

					OF = 1;

				}

				else {

					OF = 0;

				}

				if (difference < 0) {

					SF = 1;

				}

				else {

					SF = 0;

				}

				programCounter += 2;

			}

			else {

				status = ERR;

			}

			break;

		case 0x62:
			if ((registerIndexUpper >= 0 && registerIndexUpper <= 8) && (registerIndexLower >= 0 && registerIndexLower <= 8)) {

				int valueOfUpperRegister = registers[registerIndexUpper];
				int valueOfLowerRegister = registers[registerIndexLower];

				int and = valueOfUpperRegister & valueOfLowerRegister;

				registers[registerIndexUpper] = and;

				if (and == 0) {

					ZF = 1;

				}

				else {

					ZF = 0;

				}

				if (and < 0) {

					SF = 1;

				}

				else {

					SF = 0;

				}

				OF = 0;

				programCounter += 2;

			}

			else {

				status = ERR;

			}

			break;

		case 0x63:
			if ((registerIndexUpper >= 0 && registerIndexUpper <= 8) && (registerIndexLower >= 0 && registerIndexLower <= 8)) {

				int valueOfUpperRegister = registers[registerIndexUpper];
				int valueOfLowerRegister = registers[registerIndexLower];

				int xor = valueOfUpperRegister ^ valueOfLowerRegister;

				registers[registerIndexUpper] = xor;

				if (xor == 0) {

					ZF = 1;

				}

				else {

					ZF = 0;

				}

				if (xor < 0) {

					SF = 1;

				}

				else {

					SF = 0;

				}

				OF = 0;

				programCounter += 2;

			}

			else {

				status = ERR;

			}

			break;

		case 0x64:
			if ((registerIndexUpper >= 0 && registerIndexUpper <= 8) && (registerIndexLower >= 0 && registerIndexLower <= 8)) {

				int valueOfUpperRegister = registers[registerIndexUpper];
				int valueOfLowerRegister = registers[registerIndexLower];

				int product = valueOfUpperRegister * valueOfLowerRegister;

				registers[registerIndexUpper] = product;

				if (product == 0) {

					ZF = 1;

				}

				else {

					ZF = 0;

				}

				if ((valueOfLowerRegister > 0 && valueOfUpperRegister > 0 && product < 0) || (valueOfLowerRegister < 0 && valueOfUpperRegister < 0 && product < 0) || (valueOfLowerRegister < 0 && valueOfUpperRegister > 0 && product > 0) || (valueOfLowerRegister > 0 && valueOfUpperRegister < 0 && product > 0)) {

					OF = 1;

				}

				else {

					OF = 0;

				}

				if (product < 0) {

					SF = 1;

				}

				else {

					SF = 0;

				}

				programCounter += 2;

			}

			else {

				status = ERR;

			}

			break;

		default:
			status = ERR;
			break;

		}

}

/*
 * Performs the jmp, jle, jl, je, jne, jge, and jg operations,
 * updating (or not updating) the flags accordingly.
 */

void executeJump(unsigned char *byte) {

	int *num = (int *)(memoryArray+programCounter+1);

	switch (*byte) {

	case 0x70:
		programCounter = *num;
		break;

	case 0x71:
		if (((SF ^ OF) | ZF) == 1) {

			programCounter = *num;

		}

		else {

			programCounter += 5;

		}

		break;

	case 0x72:
		if ((SF ^ OF) == 1) {

			programCounter = *num;

		}

		else {

			programCounter += 5;

		}

		break;

	case 0x73:
		if (ZF == 1) {

			programCounter = *num;

		}

		else {

			programCounter += 5;

		}

		break;

	case 0x74:
		if (ZF == 0) {

			programCounter = *num;

		}

		else {

			programCounter += 5;

		}

		break;

	case 0x75:
		if ((SF ^ OF) == 0) {

			programCounter = *num;

		}

		else {

			programCounter += 5;

		}

		break;

	case 0x76:
		if (((SF ^ OF) & ZF) == 0) {

			programCounter = *num;

		}

		else {

			programCounter += 5;

		}

		break;

	default:
		status = ERR;
		break;

	}

}

/*
 * Stores the value of the instruction following "call"
 * in an eighth register and pushes that register. The
 * program counter is set to be the value following "call".
 */

void executeCall(unsigned char *byte) {

	int *num = (int *)(memoryArray+programCounter+1);

	registers[8] = programCounter+5;

	executePush(8);

	programCounter = *num;

}

/*
 * Pops the eighth register and sets the program counter
 * to be equal to the value of it.
 */

void executeReturn(unsigned char *byte) {

	executePop(8);

	programCounter = registers[8];

}

/*
 * Decrements %esp by four and stores the value of the
 * pushed register in the decremented %esp's place in memory.
 * Updates %esp and increments the program counter by two.
 */

void executePush(int registerIndex) {

		int valueOfRegister = registers[registerIndex];

		int decrementedESP = registers[4]-4;

		int *memArray = (int *)(memoryArray+decrementedESP);

		*memArray = valueOfRegister;

		registers[4] = decrementedESP;

		programCounter += 2;

}

/*
 * Increments %esp by four and stores the value of the
 * popped register in the incremented %esp's place in memory.
 * Updates %esp and increments the program counter by two.
 */

void executePop(int registerIndex) {

		int valueOfESP = registers[4];

		int incrementedESP = valueOfESP+4;

		int *memArray = (int *)(memoryArray+valueOfESP);

		registers[4] = incrementedESP;

		registers[registerIndex] = *memArray;

		programCounter += 2;

}

/*
 * Performs the readb and readl operations,
 * updating (or not updating) the flags accordingly.
 */

void executeRead(unsigned char *byte) {

	bitField *newBitField = (bitField *)(memoryArray+programCounter+1);
	int registerIndexLower = newBitField->lowerHalf;
	int *num = (int *)(memoryArray+programCounter+2);

	unsigned char inputChar;
	int inputNum;

	switch (*byte) {

	case 0xc0:
		if ((newBitField->upperHalf == 0xf) && (registerIndexLower >= 0 && registerIndexLower <= 8)) {

			OF = 0;
			SF = 0;

			if (scanf("%c", &inputChar) == EOF) {

				ZF = 1;

			}

			else {

				unsigned char *byteToRead = (unsigned char *)(memoryArray+registers[registerIndexLower]+*num);

				ZF = 0;

				*byteToRead = inputChar;

			}

			programCounter += 6;

		}

		else {

			status = ERR;

		}

		break;

	case 0xc1:
		if ((newBitField->upperHalf == 0xf) && (registerIndexLower >= 0 && registerIndexLower <= 8)) {

			OF = 0;
			SF = 0;

			if (scanf("%d", &inputNum) == EOF) {

				ZF = 1;

			}

			else {

				int *longToRead = (int *)(memoryArray+registers[registerIndexLower]+*num);

				ZF = 0;

				*longToRead = inputNum;

			}

			programCounter += 6;

		}

		else {

			status = ERR;

		}

		break;

	default:
		status = ERR;
		break;

	}

}

/*
 * Performs the writeb and writel operations,
 * updating (or not updating) the flags accordingly.
 */

void executeWrite(unsigned char *byte) {

	bitField *newBitField = (bitField *)(memoryArray+programCounter+1);
	int registerIndexLower = newBitField->lowerHalf;
	int *num = (int *)(memoryArray+programCounter+2);

	switch (*byte) {

	case 0xd0:
		if ((newBitField->upperHalf == 0xf) && (registerIndexLower >= 0 && registerIndexLower <= 8)) {

			unsigned char *byteToWrite = (unsigned char *)(memoryArray+registers[registerIndexLower]+*num);

			printf("%c", *byteToWrite);

			programCounter += 6;

		}

		else {

			status = ERR;

		}

		break;

	case 0xd1:
		if ((newBitField->upperHalf == 0xf) && (registerIndexLower >= 0 && registerIndexLower <= 8)) {

			int *longToWrite = (int *)(memoryArray+registers[registerIndexLower]+*num);

			printf("%d", *longToWrite);

			programCounter += 6;

		}

		else {

			status = ERR;

		}

		break;

	default:
		status = ERR;
		break;

	}

}

/*
 * Determines what the instruction is based on its opcode.
 */

void decode(unsigned char *byte) {

	switch (*byte) {

	case 0x00:
		executeNOP(byte);
		break;

	case 0x10:
		status = HLT;
		break;

	case 0x20:
		executeRRMOVL(byte);
		break;

	case 0x30:
		executeIRMOVL(byte);
		break;

	case 0x40:
		executeRMMOVL(byte);
		break;

	case 0x50:
		executeMRMOVL(byte);
		break;

	case 0x60:
		executeOP1(byte);
		break;
	case 0x61:
		executeOP1(byte);
		break;
	case 0x62:
		executeOP1(byte);
		break;
	case 0x63:
		executeOP1(byte);
		break;
	case 0x64:
		executeOP1(byte);
		break;

	case 0x70:
		executeJump(byte);
		break;
	case 0x71:
		executeJump(byte);
		break;
	case 0x72:
		executeJump(byte);
		break;
	case 0x73:
		executeJump(byte);
		break;
	case 0x74:
		executeJump(byte);
		break;
	case 0x75:
		executeJump(byte);
		break;
	case 0x76:
		executeJump(byte);
		break;

	case 0x80:
		executeCall(byte);
		break;

	case 0x90:
		executeReturn(byte);
		break;

	case 0xa0:
	{
		bitField *newBitField = (bitField *)(memoryArray+programCounter+1);
		int registerIndex = newBitField->lowerHalf;

		if ((newBitField->upperHalf == 0xf) && (registerIndex >= 0 && registerIndex <= 8)) {

			executePush(registerIndex);

		}

		else {

			status = ERR;

		}
		break;
	}

	case 0xb0:
	{
		bitField *newBitField = (bitField *)(memoryArray+programCounter+1);
		int registerIndex = newBitField->lowerHalf;

		if ((newBitField->upperHalf == 0xf) && (registerIndex >= 0 && registerIndex <= 8)) {

			executePop(registerIndex);

		}

		else {

			status = ERR;

		}
		break;
	}

	case 0xc0:
		executeRead(byte);
		break;
	case 0xc1:
		executeRead(byte);
		break;

	case 0xd0:
		executeWrite(byte);
		break;
	case 0xd1:
		executeWrite(byte);
		break;

	default:
		status = ERR;
		break;

	}

}

/*
 * Retrieves the instruction.
 */

void fetch(char * memory) {

	while (status == AOK) { /*While everything is fine*/

		unsigned char *curr_byte;

		curr_byte = (unsigned char *)(memory+programCounter);

		decode(curr_byte);

	}

	if (status == HLT) { /*If a halt instruction has occurred*/

		exit(0);

	}

	else { /*If there is an error*/

		fprintf(stderr, "ERROR: Invalid instruction or address.");

		exit(1);

	}

}

/*
 * Stores the .text directive in the memory array.
 */

void fillInText(char *textString, int index) {

	int tokenIndex = 0;

	int curr_index = index;

	int len = strlen(textString);

	while (tokenIndex < len) {

		bitField *newBitField = (bitField *)memoryArray+curr_index;

		char *upper = (char *) malloc(1);
		char *lower = (char *) malloc(1);

		strncpy(upper, textString+tokenIndex+1, 1);
		strncpy(lower, textString+tokenIndex, 1);

		newBitField->upperHalf = strtol(upper, NULL, 16);

		newBitField->lowerHalf = strtol(lower, NULL, 16);

		free(upper);
		free(lower);

		tokenIndex += 2;

		curr_index++;

	}

}

/*
 * Stores the .byte directive in the memory array.
 */

void fillInByte (char *byteString, int index) {

	int num;
	char numChar;

	sscanf(byteString, "%2x", &num); /*Takes the value of a single char in the token, and stores it in "num"*/

	numChar = num;

	memoryArray[index] = numChar;


}

/*
 * Stores the .long directive in the memory array.
 */

void fillInLong (char *longString, int index) {

	int num;

	sscanf(longString, "%d", &num); /*Takes the value of a single char in the token, and stores it in "num"*/

	memoryArray[index] = num;

}

/*
 * Stores the .string directive in the memory array.
 */

void fillInString (char *string, int index) {

	while (*string != '\0') { /*Goes through the string character by character*/

		memoryArray[index] = *string;
		index++;
		string++;

	}

}

/*
 * Reads through the entire file, line by line, storing its contents in the memory array
 * based on the directives.
 */

int main (int argc, char ** argv) {

	if (argc != 2) { /*If there are not 2 arguments*/

		fprintf(stderr, "Error: You must have 2 arguments.\n");

		exit(1);

	}

	else { /*If there are 2 arguments*/

		if (strcmp(argv[1], "-h") == 0) {

			printf("Usage: y86emul <y86 input file>\n");

			exit(0);

		}

		else {

			int curr_line = 0; /*Sets the current line equal to 0*/

			FILE *file = fopen(argv[1], "r"); /*Opens the input, which is a file, for reading*/

			if (file == NULL) { /*If there is no file*/

				fprintf(stderr, "ERROR: The file does not exist.\n");

				exit(1);

			}

			else { /*If there is a file*/

				char line[1500]; /*Initializes line array*/
				char str[6]; /*Initializes string array*/
				int size; /*Declares size*/
				int index; /*Declares index*/
				char *token; /*Declares token*/

				while (fgets(line, 1500, file) != NULL) { /*While the line in the file is not null*/

					if (curr_line == 0) { /*If the line is the first line in the file*/

						sscanf(line, "%s %x\n", str, &size); /*Scans the line and assigns its members to variables*/

						memoryArray = (char *) malloc(sizeof(char)*size);

					}

					else { /*If the line is not the first line in the file*/

						token = strtok(line, " \t\n\f\v\r"); /*Splits the line's members into tokens, delimited by white-spaces*/

						if (strcmp(token, ".text") == 0) { /*If the directive is ".text"*/

							token = strtok(NULL, " \t\n\f\v\r"); /*Moves to the next member and makes it a token*/

							sscanf(token, "%x", &index); /*Assigns the next member to an int variable, "index"*/

							programCounter = index;

							token = strtok(NULL, " \t\n\f\v\r"); /*Moves to the next member and makes it a token*/

							fillInText(token, index);

						}

						else if (strcmp(token, ".byte") == 0) { /*If the directive is ".byte"*/

							token = strtok(NULL, " \t\n\f\v\r"); /*Moves to the next member and makes it a token*/

							sscanf(token, "%x", &index); /*Assigns the next member to an int variable, "index"*/

							token = strtok(NULL, " \t\n\f\v\r"); /*Moves to the next member and makes it a token*/

							fillInByte(token, index);

						}

						else if (strcmp(token, ".long") == 0) { /*If the directive is ".long"*/

							token = strtok(NULL, " \t\n\f\v\r"); /*Moves to the next member and makes it a token*/

							sscanf(token, "%x", &index); /*Assigns the next member to an int variable, "index"*/

							token = strtok(NULL, " \t\n\f\v\r"); /*Moves to the next member and makes it a token*/

							fillInLong(token, index);

						}

						else if (strcmp(token, ".string") == 0) {

							token = strtok(NULL, " \t\n\f\v\r"); /*Moves to the next member and makes it a token*/

							sscanf(token, "%x", &index); /*Assigns the next member to an int variable, "index"*/

							token = strtok(NULL, " \t\n\f\v\r"); /*Moves to the next member and makes it a token*/

							token++;

							while (token != NULL) { /*Goes through the entire string*/

								char *nextToken = strtok(NULL, " \t\n\f\v\r");

								int len;

								if (nextToken != NULL) {

									len = strlen(token); /*Assigns the length of the string to a variable*/

									fillInString(token, index);

									index += len;

									memoryArray[index] = ' ';

									index++;

									token = nextToken;

								}

								else {

									int lastChar = strlen(token)-1;

									token[lastChar] = '\0';

									len = strlen(token);

									fillInString(token, index);

									index += len;

									index++;

									memoryArray[index] = '\0';

									break;

								}

							}

						}

						else { /*If the directive is anything else*/

							fprintf(stderr, "ERROR: Invalid directive.\n");

							exit(1);

						}

					}

					curr_line++;

				}

				fclose(file);

				status = AOK;

				fetch(memoryArray);

			}

		}

	}

	return 0;

}
