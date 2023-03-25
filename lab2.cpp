#include <stdio.h>
#include <stdlib.h>

#define print_ans 1
#define print_AB 2

typedef struct Lnode {
    int coef = 0;
    int exp = 0;
    struct Lnode* next = NULL;
} L;
Lnode* p_A, * head_A;
Lnode* p_B, * head_B;
Lnode* ans_a, * head_ans_a;

int m = sizeof(L);
int COEF_B[65535] = {};
int EXP_B[65535] = {};
int COEF_A[65535] = {};
int EXP_A[65535] = {};
int A_num, B_num;

void In() {
    scanf("%d", &A_num);
    for (int i = 0; i < A_num; i++) {
        scanf("%d", &EXP_A[i]);
        scanf("%d", &COEF_A[i]);
    }
    printf("The A formula has been typed in.\n");

    scanf("%d", &B_num);
    for (int i = 0; i < B_num; i++) {
        scanf("%d", &EXP_B[i]);
        scanf("%d", &COEF_B[i]);
    }
    printf("The B formula has been typed in.\n");
}

void Build() {
    int i;
    head_A = (L*)malloc(m);
    head_B = (L*)malloc(m);
    head_ans_a = (L*)malloc(m);

    // A链表的创建
    p_A = head_A;
    for (i = 0; i < (A_num - 1); i++) {
        p_A->coef = COEF_A[i];
        p_A->exp = EXP_A[i];
        p_A->next = (L*)malloc(m);
        p_A = p_A->next;
    }
    //p_A->next = NULL; // 设置尾结点的next指针为NULL
    p_A->coef = COEF_A[i];
    p_A->exp = EXP_A[i];
    p_A->next = NULL;

    // B链表的创建
    p_B = head_B;
    for (i = 0; i < (B_num - 1); i++) {
        p_B->coef = COEF_B[i];
        p_B->exp = EXP_B[i];
        p_B->next = (L*)malloc(m);
        p_B = p_B->next;
    }
    p_B->coef = COEF_B[i];
    p_B->exp = EXP_B[i];
    p_B->next = NULL;

    // ans链表的初始化
    ans_a = head_ans_a;

    //添加了这里
    ans_a->next = NULL;  // 设置尾结点的next指针为NULL
}

void Display() {
#ifdef print_AB
    // A
    p_A = head_A;
    printf("A(x)        =:");

    if (p_A->exp == 0) {                 // 第一个元素
        printf("%d ", p_A->coef);
        p_A = p_A->next;
    }
    else if (p_A->exp == 1) {
        printf("%d", p_A->coef);
        printf("x ");
        p_A = p_A->next;
    }
    else {
        printf("%d", p_A->coef);
        printf("x^");
        printf("%d ", p_A->exp);
        p_A = p_A->next;
    }
    if (p_A == NULL) { printf("\n"); }
    while (p_A != NULL && p_A->next != NULL) {         // 后续元素
        if (p_A->coef == 0) {
            p_A = p_A->next;
        }
        else if (p_A->coef < 0) {
            printf("%d", p_A->coef);
            printf("x^");
            printf("%d ", p_A->exp);
            p_A = p_A->next;
        }
        else {
            if (p_A->exp == 1) {
                printf("+%d", p_A->coef);
                printf("x ");
                p_A = p_A->next;
            }
            else if (p_A->exp == 0) {
                printf("+%d", p_A->coef);
                p_A = p_A->next;
            }
            else {
                printf("+%d", p_A->coef);
                printf("x^");
                printf("%d ", p_A->exp);
                p_A = p_A->next;
            }
        }
    }

    if (p_A != NULL && p_A->coef < 0) {              // 最后一个元素
        printf("%d", p_A->coef);
        printf("x^");
        printf("%d\n", p_A->exp);
    }
    else {
        if (p_A != NULL) {
            if (p_A->exp == 0) {
                printf("%d\n", p_A->coef);
            }
            else if (p_A->exp == 1) {
                printf("+%d", p_A->coef);
                printf("x\n");
            }
            else {
                printf("+%d", p_A->coef);
                printf("x^");
                printf("%d\n", p_A->exp);
            }
        }
    }

    // B
    p_B = head_B;
    printf("B(x)        =:");

    if (p_B->exp == 0) {                 // 第一个元素
        printf("%d ", p_B->coef);
        p_B = p_B->next;
    }
    else if (p_B->exp == 1) {
        printf("%d", p_B->coef);
        printf("x ");
        p_B = p_B->next;
    }
    else {
        printf("%d", p_B->coef);
        printf("x^");
        printf("%d ", p_B->exp);
        p_B = p_B->next;
    }
    if (p_B == NULL) { printf("\n"); }
    while (p_B != NULL && p_B->next != NULL) {          // 后续元素
        if (p_B->coef == 0) {
            p_B = p_B->next;
        }
        else if (p_B->coef < 0) {
            printf("%d", p_B->coef);
            printf("x^");
            printf("%d ", p_B->exp);
            p_B = p_B->next;
        }
        else {
            if (p_B->exp == 1) {
                printf("+%d", p_B->coef);
                printf("x ");
                p_B = p_B->next;
            }
            else if (p_B->exp == 0) {
                printf("+%d", p_B->coef);
                p_B = p_B->next;
            }
            else {
                printf("+%d", p_B->coef);
                printf("x^");
                printf("%d ", p_B->exp);
                p_B = p_B->next;
            }
        }
    }

    if (p_B != NULL && p_B->coef < 0) {              // 最后一个元素
        printf("%d", p_B->coef);
        printf("x^");
        printf("%d\n", p_B->exp);
    }
    else {
        if (p_B != NULL) {
            if (p_B->exp == 0) {
                printf("%d\n", p_B->coef);
            }
            else if (p_B->exp == 1) {
                printf("+%d", p_B->coef);
                printf("x\n");
            }
            else {
                printf("+%d", p_B->coef);
                printf("x^");
                printf("%d\n", p_B->exp);
            }
        }
    }
#endif

#ifdef print_ans
    // ADD
    ans_a = head_ans_a;
    printf("A(x) + B(x) =:");

    if (ans_a->exp == 0) {                 // 第一个元素
        printf("%d ", ans_a->coef);
        ans_a = ans_a->next;
    }
    else if (ans_a->exp == 1) {
        printf("%d", ans_a->coef);
        printf("x ");
        ans_a = ans_a->next;
    }
    else {
        printf("%d", ans_a->coef);
        printf("x^");
        printf("%d ", ans_a->exp);
        ans_a = ans_a->next;

    }

    while (ans_a != NULL) {
        if (ans_a->coef == 0) {
            ans_a = ans_a->next;
        }
        else if (ans_a->coef < 0) {
            printf("%d", ans_a->coef);
            printf("x^");
            printf("%d ", ans_a->exp);
            ans_a = ans_a->next;
        }
        else {
            if (ans_a->exp == 1) {
                printf("+%d", ans_a->coef);
                printf("x ");
                ans_a = ans_a->next;
            }
            else {
                printf("+%d", ans_a->coef);
                printf("x^");
                printf("%d ", ans_a->exp);
                ans_a = ans_a->next;
            }
        }
    }



    if (ans_a != NULL && ans_a->coef < 0) {                  // 最后一个元素
        printf("%d", ans_a->coef);
        printf("x^");
        printf("%d\n", ans_a->exp);
        //        ans_a = ans_a->next;
    }
    else {
        if (ans_a != NULL) {
            printf("+%d", ans_a->coef);
            printf("x^");
            printf("%d\n", ans_a->exp);
            //            ans_a = ans_a->next;
        }
    }
#endif
}

void Add() {
    p_A = head_A;
    p_B = head_B;
    int flag_a = 0;
    int flag_b = 0;
    while (p_A->next && p_B->next) {
        if (p_A->exp == p_B->exp) {
            ans_a->exp = p_A->exp;
            ans_a->coef = p_A->coef + p_B->coef;
            ans_a->next = (L*)malloc(m);
            ans_a = ans_a->next;
            p_A = p_A->next;
            p_B = p_B->next;
        }
        else if (p_A->exp < p_B->exp) {
            ans_a->exp = p_A->exp;
            ans_a->coef = p_A->coef;
            ans_a->next = (L*)malloc(m);
            ans_a = ans_a->next;
            p_A = p_A->next;
        }
        else {
            ans_a->exp = p_B->exp;
            ans_a->coef = p_B->coef;
            ans_a->next = (L*)malloc(m);
            ans_a = ans_a->next;
            p_B = p_B->next;
        }
    }
    if (p_A != NULL && p_A->next == NULL) {
        if (p_A->exp == p_B->exp) {
            ans_a->exp = p_B->exp;
            ans_a->coef = p_B->coef + p_A->coef;
            p_B = p_B->next;
            while (p_B != NULL) {
                ans_a->next = (L*)malloc(m);
                ans_a = ans_a->next;
                ans_a->exp = p_B->exp;
                ans_a->coef = p_B->coef;
                p_B = p_B->next;
            }
        }
        else {

            if(p_A->exp < p_B->exp) {
                ans_a->exp = p_A->exp;
                ans_a->coef = p_A->coef;
                while (p_B != NULL) {
                    ans_a->next = (L*)malloc(m);
                    ans_a = ans_a->next;
                    ans_a->exp = p_B->exp;
                    ans_a->coef = p_B->coef;
                    p_B = p_B->next;
                }
            }
            else {
                ans_a->exp = p_B->exp;
                ans_a->coef = p_B->coef;
                p_B = p_B->next;
                while (p_B != NULL) {
                    ans_a->next = (L*)malloc(m);
                    ans_a = ans_a->next;
                    if(p_A->exp < p_B->exp) {
                        ans_a->exp = p_A->exp;
                        ans_a->coef = p_A->coef;
                        flag_a = 1;
                        ans_a->next = (L*)malloc(m);
                        ans_a = ans_a->next;
                        ans_a->exp = p_B->exp;
                        ans_a->coef = p_B->coef;
                        p_B = p_B->next;
                    }
                    else if(p_A->exp == p_B->exp) {
                        ans_a->exp = p_B->exp;
                        ans_a->coef = p_A->coef + p_B->coef;
                        p_B = p_B->next;
                        flag_a = 1;
                    }
                    else {
                        ans_a->exp = p_B->exp;
                        ans_a->coef = p_B->coef;
                        p_B = p_B->next;
                    }
                }
                if(flag_a == 0) {
                    ans_a->next = (L*)malloc(m);
                    ans_a = ans_a->next;
                    ans_a->exp = p_A->exp;
                    ans_a->coef = p_A->coef;
                }
            }
        }
    }

    if (p_B != NULL && p_B->next == NULL) {

        if (p_A->exp == p_B->exp) {
            ans_a->exp = p_A->exp;
            ans_a->coef = p_A->coef + p_B->coef;
            p_A = p_A->next;
            while (p_A != NULL) {
                ans_a->next = (L*)malloc(m);
                ans_a = ans_a->next;
                ans_a->exp = p_A->exp;
                ans_a->coef = p_A->coef;
                p_A = p_A->next;
            }
        }

        else {

            if(p_B->exp < p_A->exp) {
                ans_a->exp = p_B->exp;
                ans_a->coef = p_B->coef;
                while (p_A != NULL) {
                    ans_a->next = (L*)malloc(m);
                    ans_a = ans_a->next;
                    ans_a->exp = p_A->exp;
                    ans_a->coef = p_A->coef;
                    p_A = p_A->next;
                }
            }
            else {
                ans_a->exp = p_A->exp;
                ans_a->coef = p_A->coef;
                p_A = p_A->next;
                while (p_A != NULL) {
                    ans_a->next = (L*)malloc(m);
                    ans_a = ans_a->next;
                    if(p_B->exp < p_A->exp && flag_b == 0) {
                        ans_a->exp = p_B->exp;
                        ans_a->coef = p_B->coef;
                        flag_b = 1;
                        ans_a->next = (L*)malloc(m);
                        ans_a = ans_a->next;
                        ans_a->exp = p_A->exp;
                        ans_a->coef = p_A->coef;
                        p_A = p_A->next;
                    }
                    else if(p_A->exp == p_B->exp) {
                        ans_a->exp = p_A->exp;
                        ans_a->coef = p_A->coef + p_B->coef;
                        p_A = p_A->next;
                        flag_b = 1;
                    }
                    else {
                        ans_a->exp = p_A->exp;
                        ans_a->coef = p_A->coef;
                        p_A = p_A->next;
                    }
                }
                if(flag_b == 0) {
                    ans_a->next = (L*)malloc(m);
                    ans_a = ans_a->next;
                    ans_a->exp = p_B->exp;
                    ans_a->coef = p_B->coef;
                }
            }
        }
    }
    ans_a->next = NULL;
}

int main() {
    In();
    Build();
    Add();
    Display();
    return 0;
}