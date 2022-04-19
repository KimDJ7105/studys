#define PROB 1

#if PROB == 1

#include "linked_stack.h"

int main() {
	LinkedStack s;
	element item;

	init_LinkedStack(&s);

	print_stack(&s);

	item.x = 1; item.y = 1; item.z = 1;
	printf("Push item\n");
	push(&s, item); print_stack(&s);

	item.x = 2; item.y = 2; item.z = 2;
	printf("Push item\n");
	push(&s, item); print_stack(&s);

	item.x = 3; item.y = 3; item.z = 3;
	printf("Push item\n");
	push(&s, item); print_stack(&s);

	item.x = 4; item.y = 4; item.z = 4;
	printf("Push item\n");
	push(&s, item); print_stack(&s);

	printf("PoP item\n");	//4
	item = pop(&s);
	printf("PoP等 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);

	printf("PoP item\n");	//3
	item = pop(&s);
	printf("PoP等 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);

	printf("PoP item\n");	//2
	item = pop(&s);
	printf("PoP等 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);

	printf("PoP item\n");	//1
	item = pop(&s);
	printf("PoP等 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);

	printf("PoP item\n");	//傍归
	item = pop(&s);
	printf("PoP data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);

	printf("PoP item\n");	//傍归
	item = pop(&s);
	printf("PoP等 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);

	clean_stack(&s);
}

#elif PROB == 2
#include "linked_que.h"

int main() {
	LinkedQue queue;
	element item;

	init_LinkedQue(&queue);		// 钮 檬扁拳

	print_queue(&queue);

	printf("enqueue item \n");
	item.x = 1, item.y = 1, item.z = 1;
	enqueue(&queue, item); print_queue(&queue);

	printf("enqueue item \n");
	item.x = 2, item.y = 2, item.z = 2;
	enqueue(&queue, item); print_queue(&queue);

	printf("enqueue item \n");
	item.x = 3, item.y = 3, item.z = 3;
	enqueue(&queue, item); print_queue(&queue);

	printf("enqueue item \n");
	item.x = 4, item.y = 4, item.z = 4;
	enqueue(&queue, item); print_queue(&queue);

	printf("enqueue item \n");
	item.x = 5, item.y = 5, item.z = 5;
	enqueue(&queue, item); print_queue(&queue);

	printf("dequeue item\n");	//1
	item = dequeue(&queue);
	printf("Dequeue等 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);

	printf("dequeue item\n");	//2
	item = dequeue(&queue);
	printf("Dequeue等 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);

	printf("dequeue item\n");	//3
	item = dequeue(&queue);
	printf("Dequeue等 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);

	printf("dequeue item\n");	//4
	item = dequeue(&queue);
	printf("Dequeue等 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	
	printf("dequeue item\n");	//5
	item = dequeue(&queue);
	printf("Dequeue等 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	
	printf("dequeue item\n");	//傍归 
	item = dequeue(&queue);
	printf("Dequeue等 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);

	clean_Que(&queue);
}

#endif
