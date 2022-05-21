#include <stdbool.h>

typedef enum {typeCon, typeId, typeOpr} nodeEnum;
/*constants*/
typedef struct {
	union{
		int ival;
		double fval;
	};
	bool iORf; //true = int, false = float
} conNodeType; // <--------------- *con function refers tho this


/*identifiers*/
typedef struct {
	union{
		int iIndex;
		int fIndex;
	};
	bool iORf; // true = int, false = float
} idNodeType; //<---------- *id function refers tho this


/*operators*/
typedef struct{
	int oper;	//operand
	int nops;	//number of operands
	struct nodeTypeTag *op[1];	/*operands extended at runtime*/
} oprNodeType; //<----------- *opr function refers tho this



//return struct for ex function in mylangInterpreter.c to return int/double and a boolean variable
typedef struct{
	union{
		int inti;
		double floatie;
	};
	bool iORf;
} exReturn;



typedef struct nodeTypeTag{
	nodeEnum type;
	
	union{
		conNodeType con;
		idNodeType id;
		oprNodeType opr;
	};
} nodeType; // 
//nodeEnum type <------- type of token
//union <---- any one of the following
//either a constant
// variables id in the symbol table 
//or the type of operator it is (while, if, else, =, + etc)

extern int symInt[1400];
extern double symFloat[1200];


//HOW TO RUN
/*
bison -d mylang.y && flex mylang.l mylang.tab.h && gcc mylangInterpreter.c lex.yy.c mylang.tab.c

	a.exe < myFile.txt
*/