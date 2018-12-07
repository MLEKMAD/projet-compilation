#include "analyseur_synthaxique.h"




/*
 * IF_STATEMENT ::= if CONDITION then SEQUENCE_OF_STATEMENT {elseif CONDITION then SEQUENCE_OF_STATEMENT} [else SEQUENCE_OF_STATEMENT] end if;
 */
 
static boolean IF_STATEMENT(){
	
	if(current_symbol.code!=IF_TOKEN) return false;
	next_symbol();
	
	CONDITION();
	
	if(current_symbol.code!=THEN_TOKEN) 
		// TODO raise_error(error_code);
	next_symbol();
	
	SEQUENCE_OF_STATEMENT();
	
	
	// {elseif CONDITION then SEQUENCE_OF_STATEMENT}

	while(current_symbol.code==ELSIF_TOKEN){
		next_symbol();

		CONDITION();
		
		if(current_symbol.code!=THEN_TOKEN) 
			// TODO raise_error(error_code);
		
		next_symbol();
		
	
	}

	if(current_symbol.code == ELSE_TOKEN) {
		next_symbol();
		SEQUENCE_OF_STATEMENT();
	}
		
	if(current_symbol.code!=END_TOKEN) 
		// TODO raise_error(error_code);
	next_symbol();
	
	if(current_symbol.code!=IF_TOKEN) 
		// TODO raise_error(error_code);
	next_symbol();

	if(current_symbol.code!=SEMICOLON_TOKEN) 
		// TODO raise_error(error_code);
	next_symbol();
	

	return true;
	
	
		

}

/*
 * EXPRESSION ::= RELATION { and RELATION } | RELATION { or RELATION } | RELATION { xor RELATION }
 */

static boolean EXPRESSION(){
	
	if(!RELATION()) return false;	
	
	// { and RELATION }
	if(current_symbol.code==AND_TOKEN) {

		while (current_symbol.code==AND_TOKEN){
			next_symbol();
			if(!RELATION()) return false;	
			
		}
	
	}

	// { or RELATION }
	else if(current_symbol.code==OR_TOKEN) {
		while (current_symbol.code==OR_TOKEN){
			next_symbol();
			if(!RELATION()) return false;	
			
		}
	
	}

	//{ xor RELATION }
	else if (current_symbol.code==XOR_TOKEN) {
		while (current_symbol.code==XOR_TOKEN){
			next_symbol();
			if(!TRELATION()) return false;	
			
		}

	}

	return true;
	
	
}

/*
 * RELATION ::= SIMPLE_EXPRESSION [ RELATION_OPERATOR SIMPLE_EXPRESSION ] 
 */

static boolean RELATION(){

	if(!SIMPLE_EXPRESSION()) return false;
		
	if (RELATION_OPERATOR() ){
		next_symbol();
		if(!SIMPLE_EXPRESSION()) return false;	
			
	}
	

	return true;
	
	
}

/*
 * SIMPLE_EXPRESSION ::= [ UNARY_ADDING_OPERATOR ] TERM { BINARY_ADDING_OPERATOR TERM }
 */

static boolean SIMPLE_EXPRESSION(){
	
	if(UNARY_ADDING_OPERATOR()){
		next_symbol();
	}
	if(!TERM()) return false;

	while (BINARY_ADDING_OPERATOR()){
		next_symbol();
		if(!TERM()) return false;	
			
	}
	

	
	return true;
	
}

/*
 * TERM ::= FACTOR { MULTIPLYING_OPERATOR FACTOR } 
 */

static boolean TERM(){
	if(!FACTOR()) return false;
		
	while (MULTIPLYING_OPERATOR()){
		next_symbol();
		if(!FACTOR()) return false;	
			
	}
	

	return true;
	
	
}

/*
 * FACTOR ::= PRIMARY [** PRIMARY] 
 */

static boolean FACTOR() {
	if(!PRIMARY()) return false;
		
	//TODO  [** PRIMARY] 
	/*
	if(current_symbol.code==exponentiate){
		next_symbol();
		if(!PRIMARY()) return false;		
	}
	*/

	return true;
	
}

/*
 * PRIMARY ::= READ_NUMBER  | null | name | STRING_LITERAL | (EXPRESSION) 
 */

static boolean PRIMARY(){

	if(current_symbol.code==INTEGER_TOKEN || current_symbol.code==REAL_NUMBER_TOKEN) { next_symbol(); return true;}
	else if(current_symbol.code==NULL_TOKEN) { next_symbol(); return true;}
	else if(current_symbol.code==ID_TOKEN) { next_symbol(); return true;}
	else if(current_symbol.code==STRING_TOKEN) { next_symbol(); return true;}

	else if(current_symbol.code==OPEN_PARENTHESIS_TOKEN) { 
		next_symbol(); 
		if(EXPRESSION() && current_symbol.code==CLOSE_PARENTHESIS_TOKEN){
			next_symbol();
			return true;
		}
		else return false;
	}

	else return false;
	
}

/*
 * UNARY_ADDING_OPERATOR ::= + | -
 */

static boolean UNARY_ADDING_OPERATOR(){

	if(current_symbol.code==PLUS_TOKEN) { return true;}
	else if(current_symbol.code==SUBSTRACT_TOKEN) { return true;}
	else return false;
}

/*
 * BINARY_ADDING_OPERATOR ::= + | - | &
 */

static boolean BINARY_ADDING_OPERATOR(){
	
	if(current_symbol.code==PLUS_TOKEN) { return true;}
	else if(current_symbol.code==SUBSTRACT_TOKEN) { return true;}
	// TODO FIND THE THE NAME OF TOKEN &   else if(current_symbol.code=="&") { return true;}
	else return false;

}

/*
 * MULTIPLYING_OPERATOR ::= * | / | mod / rem
 */

static boolean MULTIPLYING_OPERATOR(){

	if(current_symbol.code==MULTIPLY_TOKEN) {  return true;}
	else if(current_symbol.code==DIVIDE_TOKEN) {  return true;}
	else if(current_symbol.code==MOD_TOKEN) {  return true;}
	else if(current_symbol.code==REM_TOKEN) {  return true;}
	else return false;
	
}

/*
 * CONDITION ::= EXPRESSION
 */
static boolean  CONDITION() {
	
	return EXPRESSION();

}


/*
 * RELATION_OPERATOR ::=  = | /=  | < | <= | > | >=
 */

static boolean  RELATION_OPERATOR(){

	if(current_symbol.code==EQUAL_TOKEN) { return true;}
	// TODO FIND THE THE NAME OF TOKEN /=       else if(current_symbol.code=="/=") { return true;}
	else if(current_symbol.code==LESS_TOKEN) { return true;}
	else if(current_symbol.code==LESS_EQUAL_TOKEN,) { return true;}
	else if(current_symbol.code==GREATER_TOKEN) {  return true;}
	else if(current_symbol.code==GREATER_EQUAL_TOKEN,) {  return true;}
	else return false;
	
}
static boolean  _NAME(){return false;}
