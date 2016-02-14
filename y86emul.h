/*
 * y86emul.h
 *
 *  Created on: Jul 31, 2015
 *      Author: Jon
 */

#ifndef Y86EMUL_H_
#define Y86EMUL_H_

/*
 * Typedef definition for the "bitField" struct. It is of type "void" and takes a "char *" and an "int" as arguments.
 */

typedef struct {

	unsigned char upperHalf: 4; /*The upper half of the bitfield (the first four bits)*/
	unsigned char lowerHalf: 4; /*The lower half of the bitfield (the last four bits)*/

} bitField;

/*
 * Typedef definition for the "state" enum. It contains three "states".
 */

typedef enum {

	AOK, /*Everything is fine; no errors*/
	HLT, /*Halt instruction has occurred; program ends normally*/
	ERR /*Error has occurred*/

	} state;
	state status;

/*
 * Prototype definition for the executeNOP() function. It is of type "void" and takes an "unsigned char *" as an argument.
 */

void executeNOP(unsigned char *byte);

/*
 * Prototype definition for the executeRRMOVL() function. It is of type "void" and takes an "unsigned char *" as an argument.
 */

void executeRRMOVL(unsigned char *byte);

/*
 * Prototype definition for the executeIRMOVL() function. It is of type "void" and takes an "unsigned char *" as an argument.
 */

void executeIRMOVL(unsigned char *byte);

/*
 * Prototype definition for the executeRMMOVL() function. It is of type "void" and takes an "unsigned char *" as an argument.
 */

void executeRMMOVL(unsigned char *byte);

/*
 * Prototype definition for the executeMRMOVL() function. It is of type "void" and takes an "unsigned char *" as an argument.
 */

void executeMRMOVL(unsigned char *byte);

/*
 * Prototype definition for the executeOP1() function. It is of type "void" and takes an "unsigned char *" as an argument.
 */

void executeOP1(unsigned char *byte);

/*
 * Prototype definition for the executeJump() function. It is of type "void" and takes an "unsigned char *" as an argument.
 */

void executeJump(unsigned char *byte);

/*
 * Prototype definition for the executeCall() function. It is of type "void" and takes an "unsigned char *" as an argument.
 */

void executeCall(unsigned char *byte);

/*
 * Prototype definition for the executeReturn() function. It is of type "void" and takes an "unsigned char *" as an argument.
 */

void executeReturn(unsigned char *byte);

/*
 * Prototype definition for the executePush() function. It is of type "void" and takes an "int" as an argument.
 */

void executePush(int registerIndex);

/*
 * Prototype definition for the executePop() function. It is of type "void" and takes an "int" as an argument.
 */

void executePop(int registerIndex);

/*
 * Prototype definition for the executeRead() function. It is of type "void" and takes an "unsigned char *" as an argument.
 */

void executeRead(unsigned char *byte);

/*
 * Prototype definition for the executeWrite() function. It is of type "void" and takes an "unsigned char *" as an argument.
 */

void executeWrite(unsigned char *byte);

/*
 * Prototype definition for the decode() function. It is of type "void" and takes an "unsigned char *" as an argument.
 */

void decode(unsigned char *byte);

/*
 * Prototype definition for the fetch() function. It is of type "void" and takes a "char *" as an argument.
 */

void fetch(char * memory);

/*
 * Prototype definition for the fillInText() function. It is of type "void" and takes a "char *" and an "int" as arguments.
 */

void fillInText(char *textString, int index);

/*
 * Prototype definition for the fillInByte() function. It is of type "void" and takes a "char *" and an "int" as arguments.
 */

void fillInByte (char *byteString, int index);

/*
 * Prototype definition for the fillInLong() function. It is of type "void" and takes a "char *" and an "int" as arguments.
 */

void fillInLong (char *longString, int index);

/*
 * Prototype definition for the fillInString() function. It is of type "void" and takes a "char *" and an "int" as arguments.
 */

void fillInString (char *string, int index);


#endif /* Y86EMUL_H_ */
