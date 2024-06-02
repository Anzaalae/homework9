#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int vertex;
    struct node *edge;
} Node;

typedef struct queue {
    int vertex;
    struct queue* next;
} Queue;

void initializeGraph(Node ** h);                            // 그래프를 초기화 한다.
int insertVertex(Node *head, int key);                      // 그래프에 정점을 추가한다.
int insertEdge(Node *head, int vertex1, int vertex2);       // 그래프에 간선을 추가한다.
void printGraph(Node *head);                                // 그래프를 출력한다.
void depthFirstSearch(Node *head, int key, int *visited);   // 그래프 깊이 우선 탐색을 수행한다.
void enqueue(Queue **front, Queue **last, int key);         // 너비 우선 탐색에 사용할 큐 삽입 함수이다.
int dequeue(Queue **front, Queue **last);                   // 너비 우선 탐색에 사용할 큐 삭제 함수
void breathFirstSearch(Node *head, int key, int *visited); // 그래프 너비 우선 탐색을 수행한다.
void freeGraph(Node *head);                                 // 그래프의 동적 메모리 할당을 해제한다.

int main()
{
	char command;
	int key;
    int vertex[2];
    int visited[10];
    Node *head= NULL;

	do{
		printf("\n\n");
		printf("            [----- [Kim Yejun]  [2020025051] -----]             \n"); // 이름과 학번을 출력
		printf("----------------------------------------------------------------\n");
		printf("                          Graph Search                          \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v      Insert Edge                 = e \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
            initializeGraph(&head);
			break;
		case 'q': case 'Q':
			freeGraph(head);
			break;
		case 'v': case 'V':
			printf("Your Key = ");
			scanf("%d", &key);
            if(key < 0 || key > 9) {
                printf("this key has invalid value, retry please...\n");
                break;    
            }
			insertVertex(head, key);
			break;
		case 'e': case 'E':
			printf("input two vertex that edge has: ");
			scanf("%d %d", &vertex[0], &vertex[1]);
            if(vertex[0] < 0 || vertex[0] > 9 || vertex[1] < 0 || vertex[1] > 9) {
                printf("this key has invalid value, retry please...\n");
                break;
            }
			insertEdge(head, vertex[0], vertex[1]);
			break;
		case 'd': case 'D':
            printf("input start vertex for search graph: ");
            scanf("%d", &key);
            if(key < 0 || key > 9 || (head + key)->vertex == 9999) {
                printf("this key has invalid value, retry please...\n");
                break;   
            }
            for(int i= 0; i< 10; i++) visited[i]= 0;
            visited[key]= 1;
			depthFirstSearch(head, key, visited);
			break;
		case 'b': case 'B':
            printf("input start vertex for search graph: ");
            scanf("%d", &key);
            if(key < 0 || key > 9 || (head + key)->vertex == 9999) {
                printf("this key has invalid value, retry please...\n");
                break;   
            }
            for(int i= 0; i< 10; i++) visited[i]= 0;
            visited[key]= 1;
			breathFirstSearch(head, key, visited);
			break;
		case 'p': case 'P':
			printGraph(head);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void initializeGraph(Node **h) { // 그래프를 초기화 하는 함수
    if(*h != NULL)
        // 만약 그래프가 이미 초기화 되어있다면 메모리 할당 해제 후 다시 초기화
        freeGraph(*h);
    
    /*10개의 정점을 위한 메모리 공간 확보*/
    *h= (Node*)malloc(sizeof(Node)* 10); // 정점의 최대 개수가 10개인 것을 고려해 크기가 10인 Node에 대해 동적 메모리 할당

    for(int i= 0; i< 10; i++) {
        // 각각의 노드의 정점은 9999, 간선은 NULL로 초기화
        (*h+ i)->vertex= 9999;
        (*h+ i)->edge= NULL;
    }
}

int insertVertex(Node *head, int key) { // 그래프에 정점을 추가하는 함수
    if((head+key)->vertex == key) {
        // 만약 입력 받은 key 값이 이미 그래프에 있다면 메시지 출력 후 함수 종료
        printf("Given key is already in Graph!\n");
        return 0;
    }
    
    (head+key)->vertex= key; // head의 위치에 맞게 정점에 key값 대입
    return 0;
}

int insertEdge(Node *head, int vertex1, int vertex2) { // 그래프에 간선을 추가하는 함수
    if((head+vertex1)->vertex== 9999 || (head+vertex2)->vertex== 9999) {
        // 만약 입력받은 두 정점의 값이 그래프에 없는 정점이라면 메시지를 출력 후 함수 종료
        printf("Graph has not your input vertex...\n");
        return 0;
    }

    Node *now= (head+ vertex1)->edge;
    Node *last= NULL;
    
    while(now != NULL && now->vertex < vertex2) {
        // 각각의 정점에 대해 오름차순으로 간선을 추가하기 위해
        // 두 번째로 입력받은 정점보다 작은 값을 가지는 간선을 탐색
        last= now;
        now= now->edge;
    }

    if(now != NULL && now->vertex == vertex2) {
        // 만약 그래프에 이미 존재하는 간선이라면 메시지를 출력한 후 함수를 종료
        printf("Given edge is already in graph!\n");
        return 0;
    }

    // 입력할 새 간선
    Node *NewNode= (Node *)malloc(sizeof(Node));
    NewNode->vertex= vertex2;
    NewNode->edge= now;

    if(!last) {
        // 만약 입력해야 할 간선이 해당 정점의 첫 간선일 경우
        (head+ vertex1)->edge= NewNode;
    } else {
        last->edge= NewNode;
    }

    return 0;
}

void depthFirstSearch(Node *head, int key, int *visited) { // 그래프 깊이 우선 탐색을 수행하는 함수
    Node *temp= (head + key)->edge;
    printf("[%d] ", key); // 방문하는 정점을 출력
    while(temp) {
        // 정점의 간선들을 순차적으로 탐색하여 방문하지 않은 정점이라면 재귀적으로 함수 호출
        if(visited[temp->vertex] == 0) {
            visited[temp->vertex]= 1;
            depthFirstSearch(head, temp->vertex, visited);
        }
        temp= temp->edge;
    }

    for(int i= 0; i< 10; i++) {
        // 입력받은 정점의 모든 간선에 대한 재귀 호출을 마쳤으면 방문하지 않은 정점들에 대해 순차적으로 방문
        if(visited[i] == 0 && (head + i)->vertex != 9999) {
            visited[i]= 1;
            depthFirstSearch(head, i, visited);
        }
    }
}

void enqueue(Queue **front, Queue **last, int key) { // 그래프 너비 우선 탐색을 수행하는데 필요한 큐 삽입 함수
    // 새로 삽입할 큐
    Queue *New= (Queue*)malloc(sizeof(Queue));
    New->vertex= key;
    New->next= NULL;

    if(*front == NULL) {
        // 큐가 비어있었다면 큐의 앞 부분과 뒷 부분이 같은 위치를 가리킴
        *front= New;
        *last= New;
    } else {
        // 큐가 안 비어있는 경우 큐의 마지막 다음에 연결해준 후 마지막을 재참조
        (*last)->next= New;
        *last= New;
    }
}

int dequeue(Queue **front, Queue **last) { // 그래프 너비 우선 탐색을 수행하는데 필요한 큐 삭제 함수
    int result= (*front)->vertex; // 반환해줄 정점 값

    // 큐의 앞 부분 동적 메모리 할당 해제 후 재참조
    Queue *temp= *front;
    *front= (*front)->next;
    free(temp);

    if(*front== NULL) *last= NULL; // 큐가 비게 된다면 큐의 앞, 뒤 참조를 NULL로 초기화
    return result;
}

void breathFirstSearch(Node *head, int key, int *visited) { // 그래프 너비 우선 탐색을 수행하는 함수
    Queue *front= NULL; // 큐의 앞과 뒤를 가리키는 함수
    Queue *last= NULL;

    enqueue(&front, &last, key); // 큐에 입력받은 정점 삽입

    while(front) {
        // 큐가 빌 때까지 큐에 있는 그래프의 정점을 iterative하게 순차적으로 탐색
        int now= dequeue(&front, &last); // 큐의 제일 앞에 있는 정점값 삭제 및 출력
        printf("[%d] ", now);

        Node *temp= (head+ now)->edge;
        while(temp) {
            // 정점의 각 edge에 연결된 정점들을 순서대로 삽입
            if(visited[temp->vertex]== 0) {
                visited[temp->vertex]= 1;
                enqueue(&front, &last, temp->vertex);
            }
            temp= temp->edge;
        }
    }

    for(int i= 0; i< 10; i++) {
        // 방문하지 않은 정점들에 대해 순서대로 탐색하여 재귀적으로 함수 호출
        if(visited[i] == 0 && (head+ i)->vertex != 9999) {
            visited[i]= 1;
            breathFirstSearch(head, i, visited);
        }
    }
}

void printGraph(Node *head) { // 현재 그래프를 출력
    for(int i= 0; i< 10; i++) {
        // 모든 정점을 탐색
        if((head+i)->vertex != 9999) {
            // 정점이 존재한다면 해당 정점을 출력
            printf("Vertex %d\n", i);
            Node *now= (head+i)->edge;
            
            while(now) {
                // 정점에 대한 간선들을 탐색하여 해당 간선들을 출력
                printf("    %d -> %d\n", i, now->vertex);
                now= now->edge;
            }
        }
    }
}

void freeGraph(Node *head) {
    for(int i= 0; i< 10; i++) {
        // 모든 정점들을 탐색
        Node *now= (head+i)->edge;
        while(now) {
            // 해당 정점의 간선들을 탐색하면서 순차적으로 동적 메모리 할당 해제
            Node *temp= now;
            now= now->edge;
            free(temp);
        }
    }
    free(head);
}