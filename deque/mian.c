#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef int element;
typedef struct { // 큐 타입
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} DequeType;
// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 초기화
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 원형큐 출력 함수
void deque_print(DequeType* q)
{
	printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}
// 삽입 함수
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// 삭제 함수
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
// 삭제 함수
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}
element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[q->rear];
}
int palindrome_check(DequeType* q) {
	while (!is_empty(q)) {
		if (delete_front(q) != delete_rear(q)) {
			return 0;
		}
		else {
			return 1;
		}
	}
	return 1;
}

int main(void)
{
	DequeType dq;
	char str[MAX_QUEUE_SIZE];

	while (1) {
		printf("문자열을 입력하세오(프로그램 종료를 원하면 'exit'를 입력하세요): ");
		gets_s(str, MAX_QUEUE_SIZE);

		if (strcmp(str, "exit") == 0) {
			printf("프로그램을 종료합니다.\n\n");
			break;
		}

		if (strlen(str) == 0) {
			printf("다시 입력해주세요.\n\n");
			continue;
		}

		int len = strlen(str);
		init_deque(&dq);

		for (int i = 0; i < len; i++) {
			// 띄어쓰기, 쉼표, 어퍼스트로피는 건너뜀
			if (str[i] == ' ' || str[i] == ',' || str[i] == '\'') {
				continue;
			}
			// 대문자를 소문자로 바꿔서 저장
			else if ('A' <= str[i] && str[i] <= 'Z') {
				add_rear(&dq, str[i] - ('A' - 'a'));
			}
			else {
				add_rear(&dq, str[i]);
			}
		}

		if (palindrome_check(&dq)) {
			printf("회문입니다\n");
		}
		else {
			printf("회문이 아닙니다\n");
		}
		printf("\n");
	}
	

	system("pause");
	return 0;
}