#include <stdio.h>
#include <stdlib.h>
/** Lec 10 Ass 1,2*/

void terminate(char* msg)
{
	printf("%s\n",msg);
	// exit(1);
	// return;
}

struct Node
{
	int Data;
	struct Node* Next;
	struct Node* Prev;
};

typedef struct Node Node;

struct LinkedList
{
	// LinkedList *List;
	Node* Head;
	Node* Tail;
	size_t Size;
};

typedef struct LinkedList	LinkedList;

LinkedList* List_CreateList(void)
{
	LinkedList* list = calloc(1,sizeof(LinkedList));
	list->Head = NULL;
	list->Tail = NULL;
	list->Size = 0;
	return list;
}

Node* List_CreateNode(int value)
{
	Node* newNode = calloc(1,sizeof(Node));
	newNode->Data = value;
	newNode->Next = NULL;
	newNode->Prev = NULL;
	return newNode;
}

void List_AddNodeAtLast(LinkedList* list, int value)
{
	Node* newNode = List_CreateNode(value);
	
	/** check if list exist or not */
	if(list != NULL)
	{
		/** if no nodes in list */
		if(list->Head == NULL)
		{
			list->Head = newNode;
			list->Tail = newNode;
			list->Size ++;
		}
		/** if there is nodes in list */
		else
		{
			newNode->Prev = (Node*)list->Tail;
			list->Tail->Next = newNode;
			list->Tail = newNode;
			list->Size ++;
		}
	}
	else 
	{
		terminate("Error List_AddNode: please Create List first");
	}
}


void List_AddNodeAtIdx(LinkedList* list, int value , int idx)
{
	if(list != NULL)
	{
		if(list->Size < idx || list->Size == 0)
		{
			List_AddNodeAtLast(list,value);
		}
		else if(list->Size == idx)
		{
			Node* newNode = List_CreateNode(value);
			
			newNode->Prev = list->Tail;
			list->Tail->Next = newNode;
			list->Tail = newNode;
			
			list->Size ++;
		}
		else if(idx == 0)
		{
			Node* newNode = List_CreateNode(value);
			
			newNode->Next = list->Head;
			newNode->Prev = NULL;
			list->Head = newNode;
			
			list->Size ++;
		}
		else
		{
			Node* newNode = List_CreateNode(value) ;
			Node* tmp = list->Head;
			while(idx != 1)
			{
				tmp = tmp->Next;
				idx --;
			}
			
			newNode->Next = tmp->Next;
			newNode->Prev = tmp;
			tmp->Next->Prev = newNode;
			tmp->Next = newNode;
			
			list->Size ++;
		}
	}
}


void List_Print(LinkedList* list)
{
	Node* tmp = list->Head;
	int i=0;
	printf("-------------------------\n");
	if(tmp == NULL) 
	{
		printf("List is Empty\n");
	}
	while(tmp != NULL)
	{
		printf("Node Number %d = %d\n",i,tmp->Data);
		tmp = tmp->Next;
		i++;
	}
	printf("-------------------------\n");
}

int List_DeleteNode(LinkedList* list,int value)
{
	// #error " Not Compelete yet"
	printf("Size:%d\n",list->Size);
	if(list != NULL)
	{
		Node* DeletedNode = list->Head ;
		
		if(list->Size == 0)
		{
			terminate("Error List_DeleteNode: List is Empty");
			return 1;	
		}
		Node* nextDeletedNode = list->Head->Next;
		
		/** Deleted Node is only Node in list */
		if(list->Size == 1 )
		{
			list->Head = NULL;
			list->Tail = NULL;
			list->Size = 0;
			return 0;
		}
		/** Deleted Node is the first node */
		else if(DeletedNode->Data == value)
		{
			list->Head = DeletedNode->Next;
			DeletedNode->Prev = NULL;
			list->Size --;
			
			free(DeletedNode);
			DeletedNode = NULL;
			return 0;
		}
		/** Deleted Node is not first and last node */
		while(DeletedNode->Next != NULL)
		{
			nextDeletedNode = DeletedNode->Next;
			if(DeletedNode->Data == value)
			{
				DeletedNode->Prev->Next = DeletedNode->Next;
				DeletedNode->Next->Prev = DeletedNode->Prev;
				list->Size --;
				
				free(DeletedNode);
				DeletedNode = NULL;
				return 0;
			}
			DeletedNode = nextDeletedNode;
		}
		/** if Deleted Node is last Node */
		if(DeletedNode->Next == NULL)
		{
			if(DeletedNode->Data == value)
			{
				list->Tail = DeletedNode->Prev; // list->Tail = Tail->Prev;
				list->Tail->Next = NULL;
			
				list->Size --;
				free(DeletedNode);
				DeletedNode = NULL;
				return 0;
			}
		}
		return 1;
	}
	terminate("Error List_DeleteNode: List is not create yet");
	return 1;
}

 int main()
{
	LinkedList* list = List_CreateList();
	int choice = 0;
	int value=0,loc=0;
	
	while(1)
	{
		printf("-------------------------------------\n");
		printf("1-Add Node At Last \n");
		printf("2-Add Node At Position\n");
		printf("3-Delete Node\n");
		printf("4-Print List\n");
		printf("5-Exit\n");
		printf("Enter Your Choice:");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1:
			printf("Please Enter Node Value: ");
			scanf(" %d",&value);
			List_AddNodeAtLast(list,value);
			printf("Node Added Thank You\n");
			break;
			
			case 2:
			printf("Please Enter Node [Value Location]: ");
			scanf(" %d %d",&value,&loc);
			List_AddNodeAtIdx(list,value,loc);
			printf("Node Added Thank You\n");
			break;
			
			case 3:
			printf("Please Enter Node Value to Delete: ");
			scanf(" %d",&value);
			while(List_DeleteNode(list,value) == 0);
			break;
			
			case 4:
			List_Print(list);
			break;
			
			case 5:
			exit(0);
			break;
		}
	}
	return 0;
}
