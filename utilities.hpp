#ifndef UTILITIES
#define UTILITIES

#include<stddef.h>
#include<vector>

extern int max_size=0;
extern int max_token_size=0;

struct Stack{
	char **items;
	int top;
	Stack(){
		top=0;
	}
	void push(char *data,Stack**);
	char* pop(Stack**);
	void set_max_size(int);
	void set_max_token_size(int);
	char* peek(Stack**);
	void delete_memory(Stack**);
	void create_stack_setup(Stack**,std::vector<char*>);
	bool isempty_stack(Stack **);
};

struct Node{

	Node *next;
	int data;
};

class Queue{
	public:

		Node *front;
		Node *tail;
		Node **mover;
		Node **initial_node;
		Queue():front(NULL),tail(NULL),mover(&tail),initial_node(&front){

		}
		void enqueue(int data,Queue**);
		int dequeue(Queue**);
		bool isEmpty(Queue**);
		Node* getTail(Queue**);
		Node* getFront(Queue**);
		Node** getMover(Queue**);
		Node** getInitial(Queue**);
};

class Preprocessor:public Stack,Queue{
	public:
		long int result;
		std::vector<char*> stringParser(char*,Stack**,char[]);
		long int pass_tokens_to_queue(Stack**,Queue**,Preprocessor**);
		long int get_result(Preprocessor**);
		std::vector<char*> re_organize(std::vector<char*>,std::vector<char*>);
		void set_result(long int,Preprocessor**);
		

};


#endif

