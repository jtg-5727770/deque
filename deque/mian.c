#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef int element;
typedef struct { // ť Ÿ��
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} DequeType;
// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// �ʱ�ȭ
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}
// ��ȭ ���� ���� �Լ�
int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// ����ť ��� �Լ�
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
// ���� �Լ�
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// ���� �Լ�
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
// ���� �Լ�
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}
element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
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
		printf("���ڿ��� �Է��ϼ���(���α׷� ���Ḧ ���ϸ� 'exit'�� �Է��ϼ���): ");
		gets_s(str, MAX_QUEUE_SIZE);

		if (strcmp(str, "exit") == 0) {
			printf("���α׷��� �����մϴ�.\n\n");
			break;
		}

		if (strlen(str) == 0) {
			printf("�ٽ� �Է����ּ���.\n\n");
			continue;
		}

		int len = strlen(str);
		init_deque(&dq);

		for (int i = 0; i < len; i++) {
			// ����, ��ǥ, ���۽�Ʈ���Ǵ� �ǳʶ�
			if (str[i] == ' ' || str[i] == ',' || str[i] == '\'') {
				continue;
			}
			// �빮�ڸ� �ҹ��ڷ� �ٲ㼭 ����
			else if ('A' <= str[i] && str[i] <= 'Z') {
				add_rear(&dq, str[i] - ('A' - 'a'));
			}
			else {
				add_rear(&dq, str[i]);
			}
		}

		if (palindrome_check(&dq)) {
			printf("ȸ���Դϴ�\n");
		}
		else {
			printf("ȸ���� �ƴմϴ�\n");
		}
		printf("\n");
	}
	

	system("pause");
	return 0;
}