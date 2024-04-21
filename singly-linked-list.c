/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

// 연결리스트 구조체
typedef struct Node {
	int key;
	struct Node* link;
} listNode;

// 연결리스트 headNode 구조체
typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);		// 연결리스트 초기화
int freeList(headNode* h);				// 연결리스트 메모리 할당 해제

int insertFirst(headNode* h, int key);	// 노드를 연결리스트 제일 앞에 추가
int insertNode(headNode* h, int key);	// 연결리스트에 key값 보다 큰 값 앞에 노드 삽입
int insertLast(headNode* h, int key);	// 연결리스트의 마지막에 노드 추가

int deleteFirst(headNode* h);			// 연결리스트 제일 앞 부분 노드 제거
int deleteNode(headNode* h, int key);	// 연결리스트 key값을 찾아 제거
int deleteLast(headNode* h);			// 연결리스트 제일 뒷 부분 노드 제거
int invertList(headNode* h);			// 연결리스트 뒤집기

void printList(headNode* h);			// 연결리스트 출력

int main()
{	// 프로그램 시작시 학번과 이름을 출력
	printf("[----- [Kim Yejun]  [2020025051] -----]\n\n");


	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
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
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;
	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	// 키 값의 링크를 헤드에 연결
	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node= (listNode*)malloc(sizeof(listNode));
    node->key= key;

    listNode* current= h->first; // 탐색할 현재 노드
    listNode* prev= NULL;		 // 탐색할 이전 노드

    // 리스트의 끝에 갈 때까지 키 값보다 큰 값 가진 리스트 검색하는 방식으로 탐색
    while (current!= NULL && current->key< key) {
        prev= current;
        current= current->link;
    }

    if (prev == NULL) {
        // 키 값이 제일 작은 경우
        node->link= h->first;
        h->first= node;
    } else {
		// 그외의 경우
        prev->link= node;
        node->link= current;
    }

    return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* node= (listNode*)malloc(sizeof(listNode));
    node->key= key;

    if (h->first == NULL) {
        // 리스트가 비어있을 경우
        h->first= node;
		node->link= NULL;
    } else {
        listNode* current= h->first;
        while (current->link != NULL) {
		// 마지막 노드까지 연결리스트 탐색하기
            current= current->link;
        }
		// 마지막에 값 대입
        current->link= node;
		node->link= NULL;
    }

    return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	if (h->first != NULL) {
	// 리스트의 첫번째 값 다은 주소로 연결해주고 메모리 할당 해제
		listNode* temp= h->first;
		h->first= h->first->link;
		free(temp);
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

    listNode* current= h->first; // 탐색할 현재 노드
    listNode* prev= NULL;		 // 탐색할 이전 노드

    // 입력받은 키 값을 가지는 노드 찾기
    while (current != NULL && current->key != key) {
        prev= current;
        current= current->link;
    }

    if (current == NULL) {
        // 입력받은 키값을 가진 노드가 없는 경우
        printf("given key is not in list!\n");
        return 0;
    }

    // 삭제 부분
    if (prev == NULL) {
        // 첫 번째 노드를 삭제해야하는 경우
        h->first= current->link;
    } else {
        // 그 외의 노드를 삭제하는 경우
        prev->link= current->link;
    }

    free(current); // 삭제한 노드 메모리 할당 해제
    return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	// 노드가 비어있는 경우
    if (h->first == NULL) {
        printf("list already empty!\n");
        return 0;
    }

    listNode* current= h->first; // 탐색할 노드의 현재 위치
    listNode* prev= NULL;		 // 탐색할 노드의 이전 위치

    // 마지막 노드까지 탐색
    while (current->link != NULL) {
        prev= current;
        current= current->link;
    }

    // 마지막 노드 삭제
    if (prev == NULL) {
        // 리스트에 노드가 하나만 있을 경우
        h->first= NULL;
    } else {
		// 그 외의 경우
        prev->link= NULL;
    }

    free(current); // 삭제한 노드 메모리 할당 해제

    return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

    listNode* prev= NULL;
    listNode* current= h->first;
    listNode* next= NULL;

	// 한 칸씩 이동하면서 현재 노드와 이전 노드의 링크를 반대로 바꿔줌
    while (current != NULL) {
        next= current->link;
        current->link= prev;
        prev= current;
        current= next;
    }

    h->first= prev; // 마지막으로 헤드가 기존 마지막 노드를 가리키도록 

    return 0;
}


void printList(headNode* h) {
	int i= 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p= h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p= p->link;
		i++;
	}

	printf("  items = %d\n", i);
}