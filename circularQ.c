/**
 * circularQ.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear, size;
	// isFull(), isEmpty()의 조건 확인을 위해 큐에 저장된 데이터의 개수 size 변수 추가
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
int enQueue(QueueType *cQ, element item);
int deQueue(QueueType *cQ);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{	// 학번과 이름을 실행 결과 첫 줄에 출력
	printf("[----- [Kim Yejun]  [2020025051] -----]\n\n");

	QueueType *cQ = createQueue();
	element data;
	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);
		// 'q' 또는 'Q'입력할 때 까지 입력한 커맨드 별로 동작 수행
		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{	// 프로그램 시작 시 원형 큐 생성
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	cQ->size = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{	// 프로그램 종료 전 원형 큐 배열 메모리 동적 할당 해제
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

element getElement()
{	// 큐에 데이터를 넣기 전 해당 데이터를 입력 받음
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}

int isEmpty(QueueType *cQ)
{	// 원형큐가 비었는지 확인
	// cQ구조체 멤버변수 size와 front와 rear가 같은곳을 가리키는지 확인
	if(cQ->front == cQ->rear && cQ->size == 0) return 1;
	else return 0;
}

int isFull(QueueType *cQ)
{	// 원형큐가 가득 찼는지 확인
	// cQ구조체 멤버변수 size와 front와 rear가 같은곳을 가리키는지 확인
	if(cQ->front == cQ->rear && cQ->size == 4) return 1;
    else return 0;
}


int enQueue(QueueType *cQ, element item)
{   // 큐가 가득 찼는지 먼저 확인 후 가득 찼다면 가득 찼다는 메시지 출력
	if(isFull(cQ)) {
		printf("Queue is fully occupied!!!\n");
		return 0;
	}
	// rear 값을 한칸 옆으로 이동시킨 후 rear의 위치에 해당하는 큐 배열 위치에 데이터 추가
	cQ->rear= (cQ->rear+ 1) %4;
	cQ->queue[cQ->rear]= item;
	cQ->size++;
	// 데이터 개수 증가를 의미
	return 0;
}

int deQueue(QueueType *cQ)
{	// 큐가 이미 비어있는지 먼저 확인 후 비어있다면 이미 큐가 비어있다는 메시지 출력
	if(isEmpty(cQ)) {
		printf("Queue is already empty!!!\n");
		return 0;
	}
	// 큐의 제일 첫 데이터의 위치를 가리키는 front 변수를 증가시킴
	cQ->front= (cQ->front+ 1) %4;
	cQ->size--;
	// 데이터 개수 감소를 의미
    return 0;
}


void printQ(QueueType *cQ)
{	// size 변수의 크기만큼 큐의 데이터 출력
	int first, i= 0;
	// first 변수는 큐의 데이터 제일 앞 순서를 의미
	first = (cQ->front + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	while(i != cQ->size){
		printf("%3c", cQ->queue[first]);
		first = (first+ 1)% MAX_QUEUE_SIZE;
		i++;
	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{
	// front 변수의 데이터 크기를 이용해 큐에서 제일 앞에 해당하는 배열 위치에 front 출력
	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}