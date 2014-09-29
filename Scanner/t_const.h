#ifndef T_CONST_H_
#define T_CONST_H_

/* Endzustände */

#define TTYPE_LONG_RANGE_ERROR	97
#define TTYPE_FILE_END 			98
#define TTYPE_UNKNOWN_LETTER	99

#define TTYPE_TOKEN_TYPES		100

#define TTYPE_INT 				101 // 0, 12, ...
#define TTYPE_IDENTIFIER  		102 // x, x1, x123, x1y2, myArr, var, ...
#define TTYPE_PLUS 				103 // +
#define TTYPE_MINUS 			104 // -
#define TTYPE_DIV 				105	// /
#define TTYPE_MULT 				106	// *
#define TTYPE_GREATER 			107	// >
#define TTYPE_LESS 				108 // <
#define TTYPE_EQUALS 			109 // =
#define TTYPE_NOT    			110	// !
#define TTYPE_AEQUI 			111	// <=> (same as negating the = operator: a<=>b, !(a=b))
#define TTYPE_AMP 				112	// &
#define TTYPE_SEMI 				113 // ;
#define TTYPE_R_B_O 			114 // (
#define TTYPE_R_B_C 			115 // )
#define TTYPE_S_B_O 			116 // [
#define TTYPE_S_B_C 			117 // ]
#define TTYPE_C_B_O 			118 // {
#define TTYPE_C_B_C 			119 // }
#define TTYPE_KEYWORD 			121 // print, while, if, else, ...
#define TTYPE_ARRAY 			201 // a[n]

#define TTYPE_EXISTING_IDENTIFIER	999
#define TTYPE_CONFIRMED_IDENTIFIER	1000

#endif
