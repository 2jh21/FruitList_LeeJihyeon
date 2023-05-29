#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];
} element;

typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
    return;
}

ListNode* search_list(ListNode* head, element value) {
    ListNode* p = head;
    while (p != NULL) {
        if (strcmp(p->data.name, value.name) == 0)
            return p;
        p = p->link;
    }
    return NULL;
}

ListNode* insert_first(ListNode* head, element value){
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}

ListNode* insert(ListNode* head, ListNode* pre, element value){
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

ListNode* delete_first(ListNode* head){
    ListNode* removed;
    if (head == NULL) return NULL;
    removed = head;
    head = removed->link;
    removed->link = NULL; 
    return head;
}

ListNode* delete(ListNode* head, ListNode* pre){
    ListNode* removed;
    removed = pre->link;
    pre->link = removed->link;
    removed->link = NULL;
    return head;
}

void print_list(ListNode* head) {
    printf("\nfruit list: ");
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%s->", p->data.name);
    printf("NULL \n");
}

void delete_print(ListNode* head) {
    printf("List of deleted fruits: ");
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    ListNode* p;
    for (p = head; p->link != NULL; p = p->link)
        printf("%s->", p->data.name);
    printf("%s->NULL\n", p->data.name);
}

void print_menu(void) {
    printf("\nMenu\n");
    printf("1. Insert new fruit\n");
    printf("2. Delete a fruit\n");
    printf("3. Print the deleted list\n");
    printf("4. Exit\n");
    printf("Enter the menu: ");
}

int main() {
    ListNode* head = NULL;
    ListNode* deleted = NULL;
    int choice;
    element value;

    element fruit_list[] = {
    {"Mango"}, {"Orange"}, {"Apple"}, {"Grape"}, {"Cherry"},
    {"Plum"}, {"Guava"}, {"Raspberry"}, {"Banana"}, {"Peach"}
    };

    int num_fruits = sizeof(fruit_list) / sizeof(element);

    for (int i = 0; i < num_fruits; i++) {
        if (head == NULL) {
            head = insert_first(head, fruit_list[i]);
        }
        else {
            ListNode* current = head;
            while (current->link != NULL) {
                current = current->link;
            }
            insert(head, current, fruit_list[i]);
        }
    }

    while (1) {
        print_menu();
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("Fruit name to add: ");
            scanf_s("%s", value.name, 100);
            if (search_list(head, value) != NULL) {
                printf("%s already exists in the list.\n", value.name);
            }
            else {
                ListNode* current = head;
                while (current->link != NULL) {
                    current = current->link;
                }
                head = insert(head, current, value);
                printf("%s has been added.\n", value.name);
            }
            print_list(head);
            break;


        case 2:
            printf("Fruit name to delete: ");
            scanf_s("%s", value.name, 100);
            ListNode* found = search_list(head, value);
            if (found != NULL) {
                if (found == head) {
                    head = delete_first(head);
                }
                else {
                    ListNode* prev = head;
                    while (prev->link != found)
                        prev = prev->link;
                    head = delete(head, prev);
                }
                if (deleted == NULL) {
                    deleted = insert_first(deleted, found->data);
                }
                else {
                    ListNode* current = deleted;
                    while (current->link != NULL)
                        current = current->link;
                    insert(deleted, current, found->data);
                }
                printf("%s has been deleted.\n", value.name);
            }
            else {
                printf("%s is not in the list.\n", value.name);
            }
            print_list(head);
            break;

        case 3:
            delete_print(deleted);
            print_list(head);
            break;

        case 4:
            printf("Exit the program.\n");
            exit(0);

        default:
            printf("Invalid Menu. Please select again. \n");
            while (getchar() != '\n');
            break;
        }
    }
    return 0;
}
