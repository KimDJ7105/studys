#include <stdio.h>
#include "linkedlist.h"

int main(int argc, char* argv[]) //명령어 인자로 테스트 파일 이름을 main 함수에 전송
{
	// 필요한 변수 선언
	FILE *fp;
	int id;
	char name[10];
	node* result;
	node* head = NULL;
	int cmd;

	 // 파일 열기
	fp = fopen(argv[1], "rt"); //인자로 넘어온 파일이름을 이용하여 파일 열기

	if (fp == NULL) {

		printf("데이터 파일 열기 오류 \n");
		exit(-1);
	}

	// 명령어를 읽어 필요한 함수 호출
	while (1) {

		fscanf(fp, "%d", &cmd);

		printf("명령 : %d \n", cmd);

		switch (cmd) {

		case 1:
			fscanf(fp, "%d %s", &id, name);
			addNode(&head, id, name);

			break;
		case 2: 
			fscanf(fp, "%d", &id);
			result = searchNode(head, id);
			printf("검색 결과 : %s \n", result->name);
			break;

		case 3: 

			fscanf(fp, "%d", &id);
			result = deleteNode(head, id);
			free(result);
			break;
		case 4: 
			printf("전체 노드 출력 \n");

			printNode(head);

			break;
		case 5:
			freeAllNode(head);
			break;
		case 6: // 프로그램 종료
		default: break;
		}
		if (cmd == 6)break;
	}
	// 파일 닫기
	fclose(fp);
	return 0;
}




