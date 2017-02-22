//DIVIDE BY ZERO: If the top operand on the stack is a 0 when the / operator is detected, then a divide-by-zero error will occur. This error is difficult to detect prior to evaluation of the expression.
/*
putString (S) – displays the given null-terminated string to the screen.
getString(S) – reads a null-terminated string into a buffer S
badSyntax(S) – returns true iff a given null-terminated string S contains any syntax errors (error condition 1)
stackUnderflow(S) – returns true iff the evaluation of a given postfix expression S will result in stack underflow (error
condition 2)
tooManyOperands (S) – returns true iff a given postfix expression S contains too may operands (error condition 3)
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>

const int SIZE = 64;
char buffer[SIZE];
int buffer_index = 0;
char input[SIZE]; 	
//int index = 0;
bool again = true;
int result[SIZE];

int operand_cnt = 0;
int operator_cnt = 0;

void putString(char *input_){
	char c;
	while(*input_ != NULL){
		c = *input_;
		printf("%c", c);
		//printf("-");
		*input_++;
	}
	std::cout << std::endl;
}

//Load string into buffer; entities separated by white space 
void getString(char *input_){
	while(*input_ != NULL){
		buffer[buffer_index] = *input_;
		printf("%c", buffer[buffer_index]);
		*input_++;
		buffer_index++;
	}
	printf("Count of objects in buffer: %i\n", buffer_index);
}

//Check error cond. 1 
bool badSyntax(char *input_){
	while(((int)*input_ >= 48 && (int)*input_ <= 57) //0 && 9
			|| (int)*input_ == 42 || (int)*input_ == 43	// * || +
			|| (int)*input_ == 45 || (int)*input_ == 47 // - || /
			|| (int)*input_ == 32){ // || SPACE
		if((int)*input_ == 43){  //PLUS SIGN SAFE-CHECK
			char *next = &(*input_) + 1;
			//std::cout << (int)*next << std::endl; //next is pointing to next address of *input_
			//std::cout << (int)*input_<< std::endl; //*input_ is the previous one of next i.e. '+' 
			if((int)*next != 32 && (int)*next != 0){
				return true;
			}
		}
		std::cout << *input_ << std::endl;
		*input_++;
		if(*input_ == NULL){
			std::cout << "END OF EXPRESSION: HIT NULL" << std::endl;
			return false;
		}
	}
	return true;	//if it pops out of while then badSyntax
}

//Check for div-by-0 condition here
bool stackUnderflow(char *input_){
	printf("StackUnderflow Check\n");
	while(*input_ != NULL){
		if((int)*input_ >= 48 && (int)*input_ <= 57){
			char *next_div = &(*input_) + 2; // "0 /" expression?
			printf("Input == %c\n", *input_);
			printf("Dividing by zero? next_div == %c\n", *next_div);
			if((int)*input_ == 48 && (int)*next_div == 47){
				printf("ERROR: Next == %c", *next_div);
				exit(0);
			}
			else{
				char *next = &(*input_);
				int next_cnt = 0;
				while((int)*next != 32 && (int)*next != 0){
					printf("next: %c\n", *next);
					*next++;
					next_cnt++;
				}
				if(next_cnt > 0)
					*(input_ += next_cnt);
				operand_cnt++;
				printf("Operand: %i, %c\n", operand_cnt, *input_);
			}
		}
		else if((int)*input_ == 42 || (int)*input_ == 43
				|| (int)*input_ == 45 || (int)*input_ == 47){
			operator_cnt++;
			printf("Operator: %i, %c\n", operator_cnt, *input_);
			if(operator_cnt >= operand_cnt){
				return true;
			}
			*input_++;
		}
		else{
			*input_++;
			printf("Operand: %i, Operator: %i\n", operand_cnt, operator_cnt);
		}
	}
	return false;
}

//VALID: 3 4 + --> operand_cnt == 2 by the time it reaches '+'
//Therefore some type of order is messed up and need to fix
bool tooManyOperands(char *input_){
	printf("TooManyOperands Check\n");
	while(*input_ != NULL){
		if((int)*input_ >= 48 && (int)*input_ <=57){
			char *next = &(*input_);
			int next_cnt = 0;
			//printf("next: %c", *next);
			while((int)*next != 32 && (int)*next != 0){
				//printf("next: %c\n", *next);
				*next++;
				next_cnt++;
			}
			if(next_cnt > 0)
				*(input_ += next_cnt);
			operand_cnt++;
			//printf("Operand: %i, %c\n", operand_cnt, *input_);
		}
		else if((int)*input_ == 42 || (int)*input_ == 43
				|| (int)*input_ == 45 || (int)*input_ == 47){
			operator_cnt++;
			//printf("Operator: %i, %c\n", operator_cnt, *input_);
			if((operand_cnt - operator_cnt) > 1){
				return true;
			}
			*input_++;
		}
		else{
			*input_++;
			printf("Operand: %i, Operator: %i\n", operand_cnt, operator_cnt);
		}
	}
	return false;
}

int main(){
	
	while(again == true){
		//RESET
		bool syntax = true;
		for(int i = 0; i < SIZE - 1; i++){
			buffer[i] = '\0';
			input[i] = '\0';
			result[i] = 0;
		}
		operand_cnt = 0;
		operator_cnt = 0;
		buffer_index = 0;
		//END RESET
		//"12 -23 4 9 + - 32 * 4 /"
		printf("Input expression separated by spaces to calculate: ");
		std::cin.get(input, SIZE);
		if(badSyntax(input) == true){
			printf("Expression Syntax error!");
			exit(0);
		}
		if(stackUnderflow(input) == true){
			printf("Stack underflow/operator error!");
			exit(0);
		}
		operand_cnt = 0;
		operator_cnt = 0;
		if(tooManyOperands(input) == true){
			printf("Too many operands!");
			exit(0);
		}
		putString(input);
		getString(input);

		std::cout << "Play again? y/n" << std::endl;
		char in;
		std::cin >> in;
		if(in == 'n'){
			again = false;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');		
	}

	return 0;
}
