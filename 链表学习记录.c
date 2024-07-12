#include<stdio.h> /*提供malloc()原型*/
#include<stdlib.h> /*提供strcpy()原型*/
#include<string.h> /*储存片名的数组大小*/
#define TSIZE 45

struct film {
	char title[TSIZE];
	int rating;
	struct film * next; /*指向链表中的下一个结构*/
};
char * s_gets(char * st, int n);

int main(void)
{
	struct film * head = NULL;
	struct film * prev, * current;
	char input[TSIZE];

	/*收集并储存信息*/
	puts("enter first movie title:");
	while (s_gets(input, TSIZE) != NULL && input[0] != '\0')
	{
		current = (struct film *)malloc(sizeof(struct film));
		if (head == NULL)
			head = current;
		else
			prev->next = current;
		current->next = NULL;
		strcpy(current->title, input);
		puts("enter your rating <0-10>:");
		scanf("%d", &current -> rating);
		while (getchar() != '\n')
			continue;
		puts("enter next movie title (empty line to stop):");
		prev = current;
	}

	/*显示电影列表*/
	if (head == NULL)
		printf("no data entered.");
	else
		printf("here is the movie list:\n");
	current = head;
	while (current != NULL)
	{
		printf("movie: %s Rating: %d\n", current->title, current->rating);
		current = current -> next;
	}

	/*完成任务，释放已分配的内存*/
	current = head;
	while (head != NULL)
	{
		current = head;
		head = current->next;
		free(current);
	}
	printf("bye!\n");

	return 0;
}

char * s_gets(char * st, int n)
{
	char * ret_val;
	char * find;

	ret_val = fgets(st, n, stdin);//从标准输入（通常是键盘输入）读取一行字符，并将其存储在字符数组st中。
	if (ret_val)
	{
		find = strchr(st, '\n'); //查找换行符
		if (find)
			*find = '\0';
		else
			while (getchar() != '\n')
				continue;//处理剩余输入行
	}
	return ret_val;
}
