#include <stdio.h>
#include <stdlib.h>

#define PROB 1
#define MAX_LIST_SIZE 100

#if PROB == 1

typedef int element;

typedef struct arraylist {
	element list[MAX_LIST_SIZE];
	int count;
} Alist;

element add(Alist* list, element item);
int delete(Alist* list, element item);
void clear(Alist* list);
int is_in_list(Alist* list, element item);
int get_length(Alist* list);
int is_empty(Alist* list);
int is_full(Alist* list);
void display(Alist* list);
element get_entry(Alist* list, int n);

int main() {

	element item;
	Alist list;
	char ch;

	clear(&list);

	srand(100);

	while (1) {

		item = rand();

		add(&list, item);

		display(&list);
		ch = getch();

		if (ch == 'q') break;
	}

	printf("get_length : %d \n", get_length(&list));
	printf("is_empty : %d, is_full : %d \n",
		is_empty(&list), is_full(&list));
	printf("get_entry : %d위치의 데이터는 %d\n", 5, get_entry(&list, 5));
	printf("is_in_list : %d의 위치는 %d \n", 5415, is_in_list(&list, 5415));
	printf("is_in_list : %d의 위치는 %d \n", 10, is_in_list(&list, 10));
	printf("delete : %d의 위치는 %d \n", 5415, delete(&list, 5415));

	display(&list);

	printf("call clear\n");
	clear(&list);

	display(&list);
	printf("리스트 길이 %d \n", get_length(&list));

	return 0;
}

element add(Alist* list, element item) {

	if (is_full(list)) return -1;

	else {
		if (is_empty(list)) {
			list->list[0] = item;
			list->count++;
			return 0;
		}

		else {
			int temp_count = 0;
			while (item >= list->list[temp_count]&&temp_count < list->count ) {
				++temp_count;
			}

			for (int i = list->count - 1; i >= temp_count; i--) {
				list->list[i + 1] = list->list[i];
			}

			list->list[temp_count] = item;
			list->count++;
			return temp_count;
		}
	}
}

int delete(Alist* list, element item) {
	if (is_empty(list)) return -1;

	else {
		for (int i = 0; i < list->count; i++) {
			if (list->list[i] == item) {
				for (int j = i; j < list->count; j++) {
					list->list[j] = list->list[j + 1];
				}
				--list->count;
				return i;
			}
		}

		return -1;
	}
}

void clear(Alist* list) {
	list->count = 0;
}

int is_in_list(Alist* list, element item) {
	if (is_empty(list)) return -1;

	else {
		for (int i = 0; i < list->count;i++) {
			if (list->list[i] == item) {
				return i;
			}
		}

		return -1;
	}
}

int get_length(Alist* list) {
	return list->count;
}

int is_empty(Alist* list) {
	return list->count == 0;
}

int is_full(Alist* list) {

	return list->count == MAX_LIST_SIZE;
}

void display(Alist* list) {
	for (int i = 0; i < list->count; i++) {
		if (i < list->count - 1) {
			printf("%d->", list->list[i]);
		}

		else printf("%d\n", list->list[i]);
	}
}

element get_entry(Alist* list, int n) {
	if (n <1 || n >list->count) return -1;

	else return list->list[n - 1];
}

#elif PROB == 2

typedef int element;

typedef struct NodeList {
	element data;
	struct NodeList* link;
} Nlist;

void add(Nlist** list, element item);
int delete(Nlist* list, element item);
void clear(Nlist** list);
int is_in_list(Nlist* list, element item);
int get_length(Nlist* list);
element get_entry(Nlist* list, int pos);
int is_empty(Nlist* list);
int is_full(Nlist* list);
void display(Nlist* list);

int main() {
	Nlist* list = NULL;
	int item;
	char ch;
	
	srand(100);

	while (1) {
		item = rand();

		add(&list, item);

		display(list);

		ch = getch();
		if (ch == 'q') break;
	}

	printf("get_length : %d \n", get_length(list));
	printf("is_empty : %d, is_full : %d \n",
		is_empty(list), is_full(list));
	printf("get_entry : %d위치의 데이터는 %d\n", 5, get_entry(list, 5));
	printf("is_in_list : %d의 위치는 %d \n", 5415, is_in_list(list, 5415));
	printf("is_in_list : %d의 위치는 %d \n", 10, is_in_list(list, 10));
	printf("delete : %d의 위치는 %d \n", 5415, delete(list, 5415));
	display(list);
	printf("call clear\n");
	clear(&list);
	display(list);
	printf("리스트 길이 %d \n", get_length(list));
}

void add(Nlist** list, element item) {
	Nlist* newnode = (Nlist*)malloc(sizeof(Nlist));
	Nlist* p;
	Nlist* temp;

	if(*list == NULL) {
		*list = newnode;
		p = *list;
		p->data = item;
		p->link = NULL;
	}

	else {
		p = *list;
		while(p->link != NULL) {
			temp = p->link;
			if (temp->data > item) break;
			p = p->link;
		}

		if (p->link == NULL) {
			p->link = newnode;
			newnode->data = item;
			newnode->link = NULL;
		}

		else {
			newnode->link = p->link;
			p->link = newnode;
			newnode->data = item;
		}
	}
}

int delete(Nlist* list, element item) {
	Nlist* p;
	Nlist* prev = NULL;
	Nlist* target;
	int result=0;
	p = list;

	while(p->link != NULL) {
		result++;
		if(p->data == item ) break;
		prev = p;
		p = p->link;
	}

	if(p->data != item) return -1;

	else {
		target = p;
		prev->link = target->link;
		free(target);
		return result;
	}
}

void clear(Nlist** list) {
	Nlist* p;
	Nlist* head;
	
	head = *list;
	*list = NULL;

	while(head != NULL) {
		p = head;
		head = head->link;
		free(p);
	}

}

int is_in_list(Nlist* list, element item) {
	Nlist* p;
	int result = 0;
	p = list;

	if(p == NULL ) return -1;

	while(p != NULL) {
		result++;
		if(p->data == item) break;
		p = p->link;
	}

	if (p != NULL && p->data == item) return result;

	else return -1;
}

int get_length(Nlist* list) {
	Nlist* p;
	p = list;
	int result = 0;

	if (p == NULL) return 0;

	while(p->link !=NULL) {
		result++;
		p = p->link;
	}

	return ++result;
}

int is_empty(Nlist* list) {
	if(list == NULL) return 1;

	else return 0;
}

int is_full(Nlist* list) {
	return 0;
}

void display(Nlist* list) {
	Nlist* p;
	p = list;
	if (list != NULL) {
		while (p->link != NULL) {
			printf("%d->", p->data);
			p = p->link;
		}

		printf("%d\n", p->data);
	}
}

element get_entry(Nlist* list, int pos) {
	Nlist* p;
	p = list;
	int result = 0;

	while (p->link != NULL) {
		result++;
		if (result == pos) break;
		p = p->link;
	}

	if (p->link == NULL) result++;

	if (result == pos) return p->data;

	else return -1;
}

#endif 
