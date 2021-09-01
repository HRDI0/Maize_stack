#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAZE_S 6
#define MAX 100

typedef struct {
	short r;
	short c;
}element;
typedef struct {
	element data[MAX];
	int top;
}Stacktype;

// 스택 초기화 함수
void init_stack(Stacktype* s)
{
	s->top = -1;
}

//공백 상태 검출 함수
int is_empty(Stacktype* s)
{
	return (s->top == -1);
}

//포화 상태 검출 함수
int is_full(Stacktype *s)
{
	return (s->top == (MAX - 1));
}

//삽입함수
void push(Stacktype *s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
//삭제 함수
element pop(Stacktype *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
//피크 함수
element peek(Stacktype *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}

element here = { 1,0 }, entry = { 1,0 };

char maze[MAZE_S][MAZE_S] = {
	{ '1', '1', '1', '1', '1', '1' },
{ 'e', '0', '1', '0', '0', '1' },
{ '1', '0', '0', '0', '1', '1' },
{ '1', '0', '1', '0', '1', '1' },
{ '1', '0', '1', '0', '0', 'x' },
{ '1', '1', '1', '1', '1', '1' },
};

// 위치를 스택에 삽입
void push_loc(Stacktype *s, int r, int c)
{
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}

//미로를 한 화면에 출력한다.
void maze_print(char maze[MAZE_S][MAZE_S])
{
	printf("\n");
	for (int r = 0; r < MAZE_S; r++) {
		for (int c = 0; c < MAZE_S; c++) {
			printf("%c ", maze[r][c]);
		}
		printf("\n");
	}
}

int main(void)
{
	int r, c;
	int i = 0;
	element road[20] = { 0, };
	Stacktype s;

	init_stack(&s);
	here = entry;
	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		c = here.c;
		maze[r][c] = '.';
		maze_print(maze);
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);
		if (is_empty(&s)) {
			printf("실패\n");
			return;
		}
		else {
			here = pop(&s);
			road[i].r = here.r;
			road[i].c = here.c;
			i++;
		}
	}
	printf("\n성공\n");
	printf("\n 경로 좌표 \n");
	for (i = 0; i < 8; i++) {
		printf("%d , %d \n", road[i].r, road[i].c);
	}
	
	return 0;
}