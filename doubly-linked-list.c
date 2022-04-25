/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	if(*h != NULL)
		freeList(*h);							//headnode가 NULL이 아니면 메모리 해제

	*h = (headNode*)malloc(sizeof(headNode));	//포인터 headnode에 대한 메모리 할당
	(*h)->first = NULL;							//포인터 headnode의 first를 NULL값으로 초기화
	return 1;
}

int freeList(headNode* h){
	
	listNode* p = h->first;						//포인터 p를 first가 가리키는 곳이 되게함

	listNode* prev = NULL;						//이전 node를 가리키는 포인터 prev를 NULL로 초기화
	while(p != NULL) {							
		prev = p;								//prev가 p가 되게 하고 
		p = p->rlink;							//p를 다음 node가 되게 하면서
		free(prev);								//이전 node들을 메모리 해제
	}
	free(h);									//마지막으로 headnode 메모리 해제
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");			//node가 없으면 출력할게 없다고 출력
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);			//list의 첫 node부터 끝 node까지 출력
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}



int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));				//새로운 node에 메모리 할당
	node->key = key;													//node에 값 초기화
	node->rlink = NULL;													//rlink를 NULL로 초기화
	node->llink = NULL;													//llink를 NULL로 초기화

	if (h->first == NULL)												//node가 아무것도 없으면 first가 node를 가리키게 함
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;												//n을 first가 가리키는 곳이 되게 함
	while(n->rlink != NULL) {											//n의 rlink가 NULL을 가리킬떄 까지 n을 마지막 node로 옮김
		n = n->rlink;
	}
	n->rlink = node;													//n의 rlink를 node를 가리키게 하고 
	node->llink = n;													//node의 link를 n을 가리키게 함 여기서 rlink는 애초에 NULL을 가리키고 있었기 때문에 새로 초기화 해줄 필요가 없음
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {


	if (h->first == NULL)
	{
		printf("nothing to delete.\n");										//전처리기
		return 0;
	}

	listNode* n = h->first;													//n을 first가 가리키는 곳이 되게 함
	listNode* trail = NULL;													//n을 삭제하고나면 마지막 node가 될 trail 선언

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) {													//node가 하나만 있을경우는 first를 NULL을 가리키게 하고 n을 해제
		h->first = NULL;
		free(n);
		return 0;
	}
    /* 마지막 노드까지 이동 */
	while(n->rlink != NULL) {												//n이 마지막 node가 되게끔 하고 trail이 마지막 바로 전 node가 되게 함
		trail = n;
		n = n->rlink;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL;													//이제는 trail이 마지막 node이므로 trail의 rlink가 NULL을 가리키게 함
	free(n);																//그리고 마지막 node였던 n을 해제

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));					
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL)
	{
		h->first = node;
		return 1;
	}

	node->rlink = h->first;													//first가 첫 node를 가리키고 있는데 이제는 새로운 node의 rlink가 첫 node를 가리키게 함
	node->llink = NULL;														//새로운 node가 첫 node가 되었으니 새로운 node의 llink를 NULL로 초기화

	listNode *p = h->first;													//두 번째 node도 새로운 node를 가리키게 해주고 first가 이제는 새로운 node를 가리키게 함
	p->llink = node;
	h->first = node;

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");										//전처리기
		return 0;
	}
	listNode* n = h->first;													//첫 번째 node의 rlink가 가리키던 곳을 first가 가리키게 하고 첫 번째 node인 n은 해제
	h->first = n->rlink;	

	free(n);

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle;														//middle의 rlink를 middle node의 전 node인 trail을 가리키게 하고 middle의 llink를 middle node의 다음 node인 n을 가리키게 해서 방향을 바꿈
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->first = middle;														//middle이 마지막 node가 되었을때 first를 middle을 가리키게 하면서 마무리

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));					//새로운 node를 메모리할당함
	node->key = key;														//새로운 node의 key값을 입력받은 key값으로 초기화
	node->llink = node->rlink = NULL;										//node의 rlink와 llink를 NULL값으로 초기화

	if (h->first == NULL)													//first가 가리키는 값이 NULL이면 아직 node가 없다는 뜻
	{
		h->first = node;													//first가 node를 가리키게 함
		return 0;
	}

	listNode* n = h->first;													//node가 있을 경우에는 listNode의 포인터 n을 first가 가리키는 노드가 되게 함

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {														
		if(n->key >= key) {													//원래 있던 node의 key값이 받은 key값 보다 크거나 같을 경우
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {												//n이 first가 가리키는 곳과 같다면 사실상 새로운 node를 첫번째로 넣는것과 같아서 insertFirst함수를 호출
				insertFirst(h, key);
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;											//node의 rlink를 n을 가리키게 하고
				node->llink = n->llink;										//node의 llink를 원래 n의 llink가 가리키던 노드를 가리키게 함
				n->llink->rlink = node;										//n의 llink의 rlink, 즉 n node와 그 전 node 사이에 새로운 node를 넣는 것이므로 n node의 전 node의 rlink를 새로운 node를 가리키게 함
				n->llink = node;											//마지막으로 n의 llink를 node를 가리키게 함
			}
			return 0;
		}

		n = n->rlink;														//새로운 노드의 key값이 n의 key값보다 큰 경우엔 n을 다음 node가 되게 함
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");										//전처리기
		return 1;
	}

	listNode* n = h->first;													

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { /* 첫 노드째 노드 인경우 */						
				deleteFirst(h);			//deleteFirst 함수 호출
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h);			//deleteLast 함수 호출
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;									//원래 n의 llink의 rlink는 다시 n을 가리키는 거였지만 그걸 n의 rlink가 가리키는 곳으로 바꿔줌
				n->rlink->llink = n->llink;									//이것도 다시 n을 가리키는 것을 n의 llink가 가리키는 곳으로 바꾸면서 n을 가리키는 node가 없게 함
				free(n);													//그리고 n 해제
			}
			return 1;
		}

		n = n->rlink;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


