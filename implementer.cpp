#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>

#include "utilities.hpp"

using namespace std;



void Stack::delete_memory(Stack **pre){
	
	//delete memory is a function for deallocating memory of stack that was created using a double pointer
	
	for(int i=0;i<max_size;i++){
	
		free(((*pre)->items)[i]);
		(*pre)->items[i]=NULL;
	}

	free((*pre)->items);
	(*pre)->items=NULL;


}

void Stack::set_max_size(int size){

	//set_max_size is a function that sets the value for the maximum number of tokens present in a query (tokens include add,multiply and numbers). This is used for malloc for stack setup
	
	max_size=size;
}
void Stack::set_max_token_size(int size){

	//set_token_size is a function that sets the value for maximum size that is exhibited by in all of the token set. This is used for malloc for stack setup

	max_token_size=size;
}

void Stack::create_stack_setup(Stack **pre,vector<char*> v1){

	//create_stack_setup is a function where the memory is allocated to setup the stack and the token values are pushed into the stack
	


	(*pre)->items=(char**)malloc(max_size*sizeof(char*));
	

	for(int i=0;i<max_size;i++){
		
		((*pre)->items)[i]=(char*)malloc((max_token_size+1)*sizeof(char));
		
	}
	for(auto &i:v1){
		
		(*pre)->push(i,pre);

	}



}



long int Preprocessor::pass_tokens_to_queue(Stack **pre,Queue **q,Preprocessor **p){
	
	/*
	 * This function is about popping the tokens from stack and sending them into queue implemented in the form of a linked list.
	 * Then the peek function in the stack checks whether the top of the stack has multiply or add.
	 * Based on the peek result,elements in the linkedlist are then dequeued from the front and each element is then add or multiply based on the peek function result in the stack.
	 */


	long int elem=0;
	char *temp_elem=(char*)malloc(max_token_size*sizeof(char));


	while((strcmp((*pre)->peek(pre),"multiply")!=0 || strcmp((*pre)->peek(pre),"add")!=0) && !((*pre)->isempty_stack(pre))){
	
		char *v=(*pre)->pop(pre);
		int temp=atoi(v);
		//cout<<"temp value is"<<temp<<endl;	
		(*q)->enqueue(temp,q);

		if(strcmp((*pre)->peek(pre),"multiply")==0){
			elem=1;
		}else if(strcmp((*pre)->peek(pre),"add")==0){
		
			elem=0;
		}

		
		while(!((*q)->isEmpty(q)) && (strcmp((*pre)->peek(pre),"multiply")==0 || strcmp((*pre)->peek(pre),"add")==0)){ 		
		
			if(strcmp((*pre)->peek(pre),"multiply")==0){
				elem*=(*q)->dequeue(q);
				(*p)->set_result(elem,p);

				//cout<<"element check during dequeue is "<<elem<<endl;

			
			}else if(strcmp((*pre)->peek(pre),"add")==0){
	
				elem+=((*q)->dequeue(q));
				(*p)->set_result(elem,p);
				//cout<<"element check during dequeue is "<<elem<<endl;
			}
		}
		
		if((*pre)->top>0){

			if(strcmp((*pre)->peek(pre),"multiply")==0 || strcmp((*pre)->peek(pre),"add")==0){

				(*pre)->pop(pre);
				long int temp_val=(*p)->get_result(p);
				sprintf(temp_elem,"%ld",temp_val);
				(*pre)->push(temp_elem,pre);
				
			}			
		}else if((*pre)->top<=0){
		
			(*pre)->pop(pre); //removes the last token in the stack
		}	
		
	}
	
	long int temp_val=(*p)->get_result(p);
	free(temp_elem);
	return temp_val;
		
}




void Stack::push(char *data,Stack **s){

	//Push the tokens into stack

	if(((*s)->top)>max_size){
		printf("%s","overflow");
	}else{
	
		strcpy((*s)->items[((*s)->top)++],data);
		
	}

}

char* Stack::pop(Stack **s){

	//Pop the tokens from the stack


	if(((*s)->top)<=-1){
		printf("%s","underflow");
		return(0);
	}else{	
		(*s)->top=(*s)->top-1;
		char *val=((*s)->items)[(*s)->top];
		return val;
	}
}

char* Stack::peek(Stack **s){
	//Return the element at the top of the stack
	
	if ((*s)->top>0){

		return (*s)->items[((*s)->top)-1];
	}else{
	
		return "empty stack";
	}
}
bool Stack::isempty_stack(Stack **s){
	
	//Check whether the stack is empty or not

	if((*s)->top<0){
		return true;
	}else{
	
		return false;
	}

}




Node** Queue::getMover(Queue **q){
	
	//This function is used to move the tail pointer of the linkedlist

	return (*q)->mover;

}

Node* Queue::getTail(Queue **q){
	// This function return the tail node of the linkedlist

	return (*q)->tail;

}

Node** Queue::getInitial(Queue **q){
	//This function moves the front pointer of the linkedlist

	return (*q)->initial_node;
}
Node* Queue::getFront(Queue **q){
	//This function returns the front pointer of the linkedlist

	return (*q)->front;
}


void Queue::enqueue(int data,Queue **q){

	//This function enqueues tokens popped from the stack and into the linkedlist

	Node **currentMover=(*q)->getMover(q);
	Node **fro=(*q)->getInitial(q);
	Node *newNode=(struct Node *)malloc(sizeof(struct Node));
	if((*currentMover)==NULL){

		newNode->data=data;
		newNode->next=NULL;
		*currentMover=newNode;
		*fro=newNode;

	}else{
		newNode->data=data;
		(*currentMover)->next=newNode;
		newNode->next=NULL;
		*currentMover=newNode;

	}


}

int Queue::dequeue(Queue **q){

	//This function dequeues tokens from the linkedlist and deallocates memory allotted to that node

	Node **init_node=(*q)->getInitial(q);
	Node **rear_node=(*q)->getMover(q);
	Node *next_node=(*init_node)->next;
	int data=(*init_node)->data;
	
	if((*rear_node)==(*init_node)){

		
		free(*init_node);
		*init_node=NULL;
		*rear_node=NULL;

	
	}else{
	
		free(*init_node);
		*init_node=NULL;
		*init_node=next_node;
	}
	return data;

}

bool Queue::isEmpty(Queue **q){
	
	//This function checks whether the queue implemented as a linkedlist is empty or not

	Node **front=(*q)->getInitial(q);
	if((*front)==NULL){
		return true;
	}else{
		return false;
	}
}

vector<char*> Preprocessor::stringParser(char *argv,Stack **s,char delim[]){
	
	/*This function takes the input query and return a vectors that stores the tokens based on the delim sent from the main function
	 * Delim is basically an character array that tells the strtok function and what characters to be removed with respect to the query
	 */ 

	char *ppa=strtok(argv,delim);
	int count=0;
	vector<char*>v1;
	unsigned int max_val=0;
	
	while(ppa!=NULL){


		size_t len= strlen(ppa);
	
		if(max_val<len){
			max_val=len;
		}
		


		count++;
		
		
		
		v1.push_back(ppa);
		
		ppa=strtok(NULL,delim);
		
	}

	(*s)->set_max_size(count);
	(*s)->set_max_token_size(max_val);

	return v1;
	
}

vector<char*> Preprocessor::re_organize(vector<char*> v1,vector<char*> v2){
	
	/* This function is written as an add-on. In other words because we are implementing a stack , we prefer query such as (add 3 4 2 (multiply 4 5 6 (multiply 2 3 1))) where numbers are followed after function.
	 * But because the input requirements demand query such as (add 3 4 2 (multiply (multiply 2 3) 4)) where the integer for the first multiply function comes after the second multiply function
	 * In order to support such queries this function re-organizes it to (add 3 4 2 (multiply 4 (multiply 2 3))) that way our implementation can support the query and be able to provide correct results
	 */


	vector<char*> v3;

	vector<char*>v_rev(v1.rbegin(),v1.rend());
	
	reverse(v2.begin(),v2.end());
	

	for(unsigned int i=0;i<v1.size();i++){
		
		bool checker=true;

		if(strcmp(v1[i],"add")==0 || strcmp(v1[i],"multiply")==0){
			
			v3.push_back(v1[i]);


			if(strcmp(v1[i+1],"add")==0 || strcmp(v1[i+1],"multiply")==0){
				

//				cout<<"v_rev_check "<<v_rev[0]<<endl;
				v3.push_back(v_rev[0]);
				v_rev.erase(v_rev.begin());
				v2.erase(v2.begin());
				v1.pop_back();
				unsigned int j=0;
				while(j<v2.size()){
					
					char *temp=v2[j];

					while((*temp)!='\0'){
						
						if((*temp)==')'){
							
							checker=false;			
							
						}
						temp++;
					}

					if(checker){
						v1.pop_back();
						v3.push_back(v_rev[0]);
					}else{
						break;
					}

					j++;
				}
			
			}

		}else{
		
			v3.push_back(v1[i]);
		}
		
	}
	
//Token set
/*	
	for(auto &i:v3){
	
		cout<<i<<endl;
	}
*/	

	return v3;
	
	
}


long int Preprocessor::get_result(Preprocessor **pre){
	
	//Gets the final result after calculation
	
	return (*pre)->result;
}

void Preprocessor::set_result(long int res,Preprocessor **pre){
	
	//Set the results to the result variable after calculation
	
	(*pre)->result=res;
}




int main(int argc, char *argv[]){

	//main function

	Preprocessor *p=new Preprocessor();
	Stack *s;
	s=(struct Stack*)malloc(sizeof(struct Stack));
	Queue *q=new Queue();
	char delim_one[]="()' '";
	char delim_two[]="' '";
	size_t length=strlen(argv[1]);
	char argv_two[length];
	strncpy(argv_two,argv[1],length+1);
	vector<char*> v1=p->stringParser(argv[1],&s,delim_one);
	vector<char*> v2=p->stringParser(argv_two,&s,delim_two);
	vector<char*> v3=p->re_organize(v1,v2);

	
	s->create_stack_setup(&s,v3);

	if(v1.size()>1 && v2.size()>1){


		long int val=p->pass_tokens_to_queue(&s,&q,&p);
	
	//Result variable
	
		cout<<val<<endl;
	}else{
	
		cout<<v1[0]<<endl;
	}
	
	s->delete_memory(&s);
	free(s);
	delete q;
	delete p;
	return(0);
}
	
	

