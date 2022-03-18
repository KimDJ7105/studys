#ifndef __linkedlist_h__
#define __linkedlist_h__

typedef struct NODE {
	int num;

	struct NODE* link;

} node;

void creatnum(int c, int seed);
void creatnode(int c, int seed);

#endif