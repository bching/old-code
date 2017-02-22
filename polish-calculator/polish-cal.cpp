//You will need to use a register to keep track of the current operand stack top (or a count of the number of valid items currently in the stack). You are also required to write and use each of the following methods for manipulating the contents of this stack
/*
Empty(S) – returns true if the operand stack S is empty.
Full (S) – returns true if the operand stack S is full.
Push (S, ITEM) – pushes ITEM onto stack S.
Pop (S) – pops the top of stack S and returns its value.

Your main program will also call subroutine applyOperator, which will apply a given operator to the operands on the user-defined stack as follows:
	error = false;
Pop (S, Opnd2);
Pop (S, Opnd1);
switch (operator)
{
	case ‘+’:	result = Opnd1 + Opnd2;
			break;
	case ‘-‘:	result = Opnd1 - Opnd2;
			break;
	case ‘*’:	result = Opnd1 * Opnd2;
			break;
	case ‘/’:	if (Opnd2 == 0)
			{
				print (“Divide by zero!”);
				error = true;
			}
			else
				result = Opnd1 / Opnd2;
}
if (not error)
	Push (S, result);
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <math.h>

const int SIZE = 64;
char buffer[SIZE];
int buffer_index = 0;
char input[SIZE]; 	
bool again = true;

//int result[SIZE];
int operand_stack[SIZE];
int op_index = 0;
int operand_1 = 0;
int operand_2 = 0;

int operand_cnt = 0;
int operator_cnt = 0;

void putString(char *input_){
	char c;
	printf("Your expressions is: ");
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
	printf("Loading into buffer: ");
	while(*input_ != NULL){
		buffer[buffer_index] = *input_;
		printf("%c", buffer[buffer_index]);
		*input_++;
		buffer_index++;
	}
	printf(" Count of objects in buffer: %i\n", buffer_index);
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
			*input_++;
		}
		else{
			*input_++;
			//printf("Operand: %i, Operator: %i\n", operand_cnt, operator_cnt);
		}
	}
	int count = operand_cnt - operator_cnt;
	//printf("Your count is: %i operand %i\n", count, operand_cnt);
	if(count > 1){
		return true;
	}
	printf("Operand: %i, Operator: %i\n", operand_cnt, operator_cnt);
	return false;
}

/*
Your main program should call subroutine getNumber, which assembles each decimal integer in the
expression one character at a time, according to the following algorithm:
number = 0;
I = 0;
while (STRING[I] != ‘ ‘ && STRING[I] != NULL)
{
	number = 10 * number + ASCII(STRING[I]) – ASCII(‘0’);
	I++;
}
where ASCII(c) is the 8-bit ASCII code for character value c. Each assembled integer should be pushed onto the operand stack. NOTE: if a number string begins with a minus sign (‘-‘), assemble the magnitude of that number first, and then negate the result.
*/

bool full(){
	if(op_index == 64)
		return true;
	else
		return false;
}

bool empty(){
	if(op_index == 0)
		return true;
	else
		return false;
}

int pop(int op_stack[]){
	if(!empty()){ //DEFINE A METHOD FOR EMPTY
		int top_stack = op_stack[op_index];
		op_stack[op_index] = 0;
		op_index--;
		printf("Popped %i off of stack\n", top_stack);
		return top_stack;
	}
}

void push(int op_stack[], int result_){
	if(!full()){
		op_index++;
		op_stack[op_index] = result_;
		printf("Pushed %i onto stack\n", result_);
	}
	else{
		printf("Operand stack is full! Program exiting...\n");
		exit(0);
	}
}

void applyOperand(int op_stack[], char oprtor){
	printf("Applying operands...\n");
	bool error = false;
	int result = 0;
	operand_2 = pop(op_stack);
	operand_1 = pop(op_stack);
	switch(oprtor){
		case '+': result = operand_1 + operand_2;
							break;
		case '-': result = operand_1 - operand_2;
							break;
		case '*': result = operand_1 * operand_2;
							break;
		case '/': if(operand_2 == 0){
								printf("Division by zero!");
								error = true;
								break;
							}
							else{
								result = operand_1 / operand_2;
								break;
							}
	}
	if(!error){
		printf("After %c operation result = %i\n", oprtor, result);
		push(op_stack, result);
		operand_1 = 0;
		operand_2 = 0;
		operand_cnt--;
	}
}

void getNumber(char buffer[]){
	int number = 0;
	int num_index = 0;
	while(buffer[num_index] != ' ' && buffer[num_index] != NULL){
		printf("Calculating numbers from string...\n");
		if(buffer[num_index] == '*' || buffer[num_index] == '/'
				|| buffer[num_index] == '+' || buffer[num_index] == '-'){
			applyOperand(operand_stack, buffer[num_index]);
			number = 0;
			num_index++;
			if(operand_cnt == 1){
				break;
			}
		}
		
		//int num_index = 0;
		//while((int)buffer[num_index] >= 48 || (int)buffer[num_index] <= 57){
		printf("current number is <%c>", buffer[num_index]);
		number = 10 * number + buffer[num_index] - 48;
		printf("Building number...%i\n", number);
			//num_index++;
		//}
		//check if more than one digit
	//	char *next = &(*input_);
	//	if(*next == ' ' || *next == NULL){
	//		printf("Next is == %i", *next);
	//		number = 10 * number + (int)*next - 48;
	//		number_builder[num_index] = number;
		num_index++;
		printf("now pointing at...<%c>\n", buffer[num_index]);
		if(buffer[num_index] == ' '){
			push(operand_stack, number);
			number = 0;
			num_index++;
			printf("move num_index by one, now pointing at <%c>\n", buffer[num_index]);
		}
	}
	//operand_stack[index] = number;
	//push(operand_stack, number);
	//printf("Added %i to operand_stack", operand_stack[index]);
}

int main(){
	
	while(again == true){
		//RESET
		bool syntax = true;
		for(int i = 0; i < SIZE - 1; i++){
			buffer[i] = '\0';
			input[i] = '\0';
//			result[i] = 0;
			operand_stack[i] = 0;
		}
		operand_cnt = 0;
		operator_cnt = 0;
		buffer_index = 0;
		op_index = 0;
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

		char buffer_val;
		//for(int i = 0; buffer_val != NULL; i++){
		//while(buffer_val != NULL){
		//	buffer_val = buffer[num_index];
		//	if(buffer_val == '*' || buffer_val == '/' 
		//			|| buffer_val == '+' || buffer_val == '-'){
		//		printf("Detected operator %c\n", buffer_val);
		//		applyOperand(operand_stack, buffer_val);
		//	}
			getNumber(buffer);
		//}


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
