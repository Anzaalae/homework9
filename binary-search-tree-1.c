/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("            [----- [Kim Yejun]  [2020025051] -----]\n"); // 이름과 학번을 출력
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	// 왼쪽 자식 노드와 오른쪽 자식 노드에 대해 재귀호출을 수행하면서 leaf 노드까지 탐색
	if(ptr->left) inorderTraversal(ptr->left);
	
	// inorder traversal 이므로 왼쪽 자식에 대한 재귀 호출을 마친 뒤 현재 노드의 key값 출력
	printf("[%d] ", ptr->key);
	if(ptr->right) inorderTraversal(ptr->right);
}

void preorderTraversal(Node* ptr)
{
	// 왼쪽 자식 노드와 오른쪽 자식 노드에 대해 재귀호출을 수행하면서 leaf 노드까지 탐색
	// preorder traversal 이므로 현재 노드의 key값을 출력한 뒤
	// 왼쪽 자식 노드, 오른쪽 자식 노드의 key값을 재귀적으로 출력
	printf("[%d] ", ptr->key);
	if(ptr->left) preorderTraversal(ptr->left);
	if(ptr->right) preorderTraversal(ptr->right);
}

void postorderTraversal(Node* ptr)
{
	// 왼쪽 자식 노드와 오른쪽 자식 노드에 대해 재귀호출을 수행하면서 leaf 노드까지 탐색
	if(ptr->left) postorderTraversal(ptr->left);
	if(ptr->right) postorderTraversal(ptr->right);

	// postorder traversal 이므로 왼쪽 자식과 오른쪽 자식 노드에 대해 재귀 호출을 마친 후
	// 현재 노드의 key값을 출력한다.
	printf("[%d] ", ptr->key); 
}


int insert(Node* head, int key)
{
	if(!head->left) {
		// 루트 노드가 비어있는 경우 루트 노드에 입력 받은 key값 삽입
		Node *temp = (Node*)malloc(sizeof(Node));
		temp->key= key;
		temp->left= NULL;
		temp->right= NULL;
		
		head->left= temp;
		return 0;
	}

	Node *prev= head;
	Node *now= head->left;

	while(now) {
		// leaf 노드가 가리키는 NULL인 노드까지 트리를 탐색
		if(now->key == key) {
			printf("your key is already in tree!\n");
			return 0;
		}
		
		prev= now;

		// 입력 받은 현재 key값 현재 노드의 key값을 비교하여
		// 현재 노드의 왼쪽 자식을 탐색할지 오른쪽 자식을 탐색할지 결정
		if(key < now->key) {
			now= now->left;
		}
		else if(key > now->key) {
			now= now->right;
		}
	}

	// 입력해야하는 leaf 노드까지 탐색했다면 해당 노드 key값과 비교하여 자식 노드에 새 노드 insert
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->key= key;
	temp->left= NULL;
	temp->right= NULL;

	if(key< prev->key) prev->left= temp;
	else if(key> prev->key) prev->right= temp;

	return 0;	
}

int deleteLeafNode(Node* head, int key)
{
	if(head->left == NULL) {
		// 루트 노드가 비어있다면 이미 트리가 비어있다는 메시지 출력
		printf("tree is already empty! \n");
		return 0;
	}

	Node *prev= head;
	Node *now= head->left;

	while(now) {
		// 찾고자 하는 key값과 현재 노드의 key값이 같은 경우
		if(now->key == key) {
			// 현재 노드가 leaf노드인 경우 해당 노드를 메모리 할당 해제
			if(now->left == NULL && now->right == NULL) {
				if(prev->left == now) prev->left= NULL;
				else if(prev->right == now) prev->right= NULL;

				free(now);
				return 0;
			} else {
			// 현재 노드가 leaf노드가 아닌 경우 입력받은 key값이 leaf노드가 아니라는 메시지 출력
				printf("the node [%d] is not a leaf \n", now->key);
				return 0;
			}
		}

		// 찾고자 하는 key값과 현재 노드의 key값이 다른 경우
		// 현재 노드의 key값과 비교하여 다음 자식 노드를 탐색
		prev= now;
		if(key < now->key) now= now->left;
		else if(key > now->key) now= now->right;
	}

	// 만약 트리를 전부 탐색했는데 입력받은 key값을 찾지 못 한 경우
	// 입력받은 key값이 트리에 없다는 메시지 출력
	printf("can't find your key in tree!\n");
	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	// 찾고자 하는 key값을 가진 노드를 찾거나 결국 찾지 못하고 leaf노드 까지 방문 한 경우
	// 해당 노드 반환
	if(ptr == NULL || ptr->key == key) return ptr;

	// 찾고자 하는 key값과 현재 노드의 key값을 비교하여 자식 노드를 재귀적으로 탐색
	else if(key < ptr->key) searchRecursive(ptr->left, key);
	else if(key > ptr->key) searchRecursive(ptr->right, key);
}

Node* searchIterative(Node* head, int key)
{
	// 루트 노드가 없는 경우(트리가 비어있는 경우)
	// NULL 값을 반환
	if(!head->left) {
		return NULL;
	}

	Node *now= head->left;

	while(now) {
		// 현재 노드의 key값과 찾고자 하는 key값을 비교하여
		// 동일한 값이면 현재 노드를 반환해주고
		if(key== now->key) return now;

		// 다르면 현재 노드의 key값과 비교하여 자식 노드를 탐색
		if(key< now->key) now= now->left;
		else if(key> now->key) now= now->right;
	}

	// 트리의 leaf노드까지 탐색했는데 입력받은 key값을 찾지 못한 경우
	return NULL;
}


int freeBST(Node* head)
{
	// 왼쪽 자식 노드와 오른쪽 자식 노드를 방문해서 동적 메모리 할당 해제 해준 후
	if(head->left) freeBST(head->left);
	if(head->right && head->right != head) freeBST(head->right);

	// 현재 노드의 동적 메모리 할당 해제
	free(head);
	return 0;
}