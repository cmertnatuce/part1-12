#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct list {
    int data;
    struct list* next;
};

typedef struct list ListNode;
typedef ListNode* ListNodePtr;

void insert(ListNodePtr*, int);
char del(ListNodePtr*, int);
int IsEmpty(ListNodePtr);
void printList(ListNodePtr);
void countList(ListNodePtr);
int findMax(ListNodePtr);
int findMin(ListNodePtr);
void removeDuplicates(ListNodePtr*);
void removeAllOccurrences(ListNodePtr*, int);

int main() {
    setlocale(LC_ALL,"RUS");
    ListNodePtr start = NULL;
    int choice=0, elem=0;

    do {
        printf("\nГлавное меню:\n");
        printf("1. Вставить элемент в список.\n");
        printf("2. Удалить элемент из списка.\n");
        printf("3. Посчитать количество элементов в списке.\n");
        printf("4. Найти максимальный элемент.\n");
        printf("5. Найти минимальный элемент.\n");
        printf("6. Удалить все дубликаты.\n");
        printf("7. Удалить все вхождения элемента.\n");
        printf("8. Вывести список на экран.\n");
        printf("9. Выход.\n");
        printf("Выберите действие: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("Введите элемент для вставки: ");
            scanf_s("%d", &elem);
            insert(&start, elem);
            break;
        case 2:
            if (!IsEmpty(start)) {
                printf("Введите элемент для удаления: ");
                scanf_s("%d", &elem);
                if (del(&start, elem))
                    printf("%d удален.\n", elem);
                else
                    printf("%d не найден.\n", elem);
            }
            else {
                printf("Список пуст.\n");
            }
            break;
        case 3:
            countList(start);
            break;
        case 4:
            if (!IsEmpty(start))
                printf("Максимальный элемент в списке: %d\n", findMax(start));
            else
                printf("Список пуст.\n");
            break;
        case 5:
            if (!IsEmpty(start))
                printf("Минимальный элемент в списке: %d\n", findMin(start));
            else
                printf("Список пуст.\n");
            break;
        case 6:
            if (!IsEmpty(start)) {
                removeDuplicates(&start);
                printf("Дубликаты удалены.\n");
            }
            else {
                printf("Список пуст.\n");
            }
            break;
        case 7:
            if (!IsEmpty(start)) {
                printf("Введите элемент, все вхождения которого нужно удалить: ");
                scanf_s("%d", &elem);
                removeAllOccurrences(&start, elem);
            }
            else {
                printf("Список пуст.\n");
            }
            break;
        case 8:
            printList(start);
            break;
        case 9:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор.\n");
        }
    } while (choice != 9);

    return 0;
}

void insert(ListNodePtr* s, int value) {
    ListNodePtr newP, previous, current;
    newP = (ListNodePtr)malloc(sizeof(ListNode));
    if (newP != NULL) {
        newP->data = value;
        newP->next = NULL;
        previous = NULL;
        current = *s;
        while (current != NULL && value > current->data) {
            previous = current;
            current = current->next;
        }
        if (previous == NULL) {
            newP->next = *s;
            *s = newP;
        }
        else {
            previous->next = newP;
            newP->next = current;
        }
    }
    else {
        printf("%d не вставлен. Недостаточно памяти.\n", value);
    }
}

char del(ListNodePtr* s, int value) {
    ListNodePtr previous, current, temp;
    if (value == (*s)->data) {
        temp = *s;
        *s = (*s)->next;
        free(temp);
        return value;
    }
    else {
        previous = *s;
        current = (*s)->next;
        while (current != NULL && current->data != value) {
            previous = current;
            current = current->next;
        }
        if (current != NULL) {
            temp = current;
            previous->next = current->next;
            free(temp);
            return value;
        }
    }
    return '\0';
}

int IsEmpty(ListNodePtr s) {
    return s == NULL;
}

void printList(ListNodePtr current) {
    if (current == NULL)
        printf("Список пуст.\n");
    else {
        printf("Список:\n");
        while (current != NULL) {
            printf("%d --> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }
}

void countList(ListNodePtr current) {
    int count = 0;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    printf("Количество элементов в списке: %d\n", count);
}

int findMax(ListNodePtr current) {
    int max = current->data;
    while (current != NULL) {
        if (current->data > max)
            max = current->data;
        current = current->next;
    }
    return max;
}

int findMin(ListNodePtr current) {
    int min = current->data;
    while (current != NULL) {
        if (current->data < min)
            min = current->data;
        current = current->next;
    }
    return min;
}

void removeDuplicates(ListNodePtr* s) {
    ListNodePtr current = *s;
    while (current != NULL && current->next != NULL) {
        if (current->data == current->next->data) {
            ListNodePtr temp = current->next;
            current->next = temp->next;
            free(temp);
        }
        else {
            current = current->next;
        }
    }
}

void removeAllOccurrences(ListNodePtr* s, int value) {
    ListNodePtr previous = NULL;
    ListNodePtr current = *s;

    while (current != NULL) {
        if (current->data == value) {
            if (previous == NULL) {
                *s = current->next;
                free(current);
                current = *s;
            }
            else {
                previous->next = current->next;
                free(current);
                current = previous->next;
            }
        }
        else {
            previous = current;
            current = current->next;
        }
    }
}