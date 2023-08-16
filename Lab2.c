#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// ************************************************************ 栈 ************************************************************
// 定义一个栈，包含头指针、尾指针和数据
typedef struct{
    char data[100];
    int top;
    int bottom;
}stack;

// 栈的创建
stack *StackCreate() {
    stack *p = (stack*)malloc(sizeof(stack));
    if(p == NULL) { return 0; }
    p->bottom = p->top = 0;
    return p;
}

// 输出栈顶元素
void StackPrintTop(stack *p) {
    printf("=:%c\n", p->data[p->top - 1]);
}

// 入栈
void StackInput(stack *p, char str) {
    p->data[p->top] = str;
    p->top++;
}

// 出栈
void StackPop(stack *p) {
    if(p->top == 0) {
//        printf("=:No data!\n");
        return;
    }
    printf("=:%c\n", p->data[p->top - 1]);
    p->top--;
}

// ************************************************************ 队列 ************************************************************
typedef char QDateType;//队列存储数据类型

typedef struct QueueNode //队列元素节点
{
    QDateType val;
    struct QueueNode* next;
}QueueNode;

typedef	struct Queue //队列
{
    QueueNode* head;
    QueueNode* tail;
}Queue;

void QueueInit(Queue* pq)
{
    assert(pq);
    pq->head = pq->tail = NULL;
}

void QueuePush(Queue* pq, QDateType x)
{
    assert(pq);

    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (NULL == newNode)
    {
        printf("malloc error\n");
        exit(-1);
    }
    newNode->val = x;
    newNode->next = NULL;

    if (pq->tail == NULL)
    {
        assert(pq->head == NULL);
        pq->head = pq->tail = newNode;
    }
    else
    {
        pq->tail->next = newNode;
        pq->tail = newNode;
    }

}

void QueuePop(Queue* pq)
{
    assert(pq);
    assert(pq->head && pq->tail);
    if (pq->head->next == NULL)
    {
        free(pq->head);
        pq->head = pq->tail = NULL;
    }
    else
    {
        QueueNode* next = pq->head->next;
        free(pq->head);
        pq->head = next;
    }
}

QDateType QueueFront(Queue* q)
{
    assert(q);
    assert(q->head);
    return q->head->val;
}

QDateType QueueBack(Queue* q) {
    assert(q);
    return q->tail->val;
}

int QueueEmpty(Queue* q)
{
    assert(q);
    return q->head == NULL;
}

void QueuePrint(Queue* q) {
    printf("=:");
    while (!QueueEmpty(q))
    {
        printf("%c", QueueFront(q));
        QueuePop(q);
    }
}
// ************************************************************ main ************************************************************
int main() {
    char inst[20];
    stack *p = 0;
    p = StackCreate();
    while(1) {
        scanf("%s", &inst);
        if(inst[0] == 'p' && inst[1] == 'u' && inst[2] == 's' && inst[3] == 'h') {
//            printf("Push %c!\n", inst[5]); // 此时为push操作，根据指令格式，可知（）之间的元素为需要入栈的元素
            int i = 0;
            char pin;
            while(1) {
                if(inst[i] != ')') {
                    pin = inst[i];  // 仅支持入栈单个字符
                    i++;
                }
                else {
                    StackInput(p, pin);
                    break;
                }
            }
        }
        if(strcmp(inst, "pop") == 0) {
//            printf("Pop!\n");
            StackPop(p);
        }
        if(strcmp(inst, "gettop()") == 0) {
            StackPrintTop(p);
        }
        if(strcmp(inst, "end") == 0) {
//            printf("end!\n");
            break;
        }
    }

    // 在队列操作部分，和栈操作不同的地方在于头和尾的功能的变化
    Queue q;
    char data[20];
    int num;
    QueueInit(&q);
    while(1) {
        int n = 0;
        if(scanf("%s", &data)) {         // 输入“abcd”，需要拆分成a, b, c, d来入队
            while(data[n] != '\0') {
                QueuePush(&q, data[n]);
                n++;
            }
        }
        if(scanf("%d", &num)) {
            for(int i = 0; i < n-num; i++) {
                QueuePop(&q);
            }
            break;
        }
    }
    QueuePrint(&q);
    return 0;
}