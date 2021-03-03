#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio_ext.h>

struct array
{
	int value;
	struct array* next;
};
typedef struct _NODE
{
	char *tu;
	int soLan;
	struct array* e;
	struct _NODE *left;
	struct _NODE* right;
}NODE;


void push(struct array** root, int new_value)
{
	if(*root == NULL)
	{
		*root = (struct array*)calloc(1, sizeof(struct array));
		(*root) -> next = NULL;
		(*root) -> value = new_value;
	}else{
		if((*root) -> value != new_value)
		{
			struct array* new = (struct array*)calloc(1, sizeof(struct array));
			new -> value = new_value;
			new -> next = *root;
			*root = new;
		}
	}
}

void InsertNode(NODE** root, char * _tu1, int _dongXH)
{
	if ((*root) == NULL)
	{
		(*root) = (NODE*)calloc(1, sizeof(NODE));
		(*root) -> tu = (char*)malloc(sizeof(_tu1));
		strcpy((*root)->tu,_tu1);
		(*root)->soLan = 1;
		(*root)->e = NULL;
		push(&((*root) -> e), _dongXH);
	}
	else
	{
		if (strcmp((*root)->tu,_tu1 )< 0)
		{	
			InsertNode(&(*root)->right,_tu1,_dongXH);
		}else if (strcmp((*root)->tu, _tu1) >0)
		{
			InsertNode(&(*root)->left, _tu1,_dongXH);
		}
		else if(strcmp((*root)->tu, _tu1) == 0)
		{	
			push(&((*root) -> e), _dongXH);	
			(*root)->soLan +=1;
		}
	}
}

void PrintBST(NODE* root)
{
	if (root != NULL)
	{
		PrintBST(root->left);
		//printf(" %-20s: %d \n",(root->tu),(root->soLan));
		printf("%s",root->tu);
		PrintBST(root->right);
	}
}




int count =0;
void find(NODE* root,char *s)
{	
	if(root != NULL && count != 1)
	{	
		//printf("%-20s\n", (root->Word).tu);
		if(strcmp((root->tu ), s) == 0)
		{
			count =1;
		}
		if(strcmp((root->tu),s) < 0)
			find(root->right,s);
		if(strcmp((root->tu),s) > 0)
			find(root->left,s);
	}
}

NODE* search(NODE* root,char* s)
{
	if(root == NULL)
	{
		return NULL;
	}
	else
	{
		if(strcmp(s,root->tu) == 0)
			return root;
		else if(strcmp(s , root->tu) < 0)
			return search(root->left,s);
		else if(strcmp(s,root->tu) > 0)
			return search(root->right,s);
	}
}

void Print2(struct array* a)
{
	while(a != NULL)
	{
		printf("%-5d", a -> value);
		a = a -> next;
	}
	printf("\n");
}

void PrintBST1(NODE* root)
{	
	if (root != NULL)
	{	
		//printf("12321\n");
		PrintBST1(root->left);
		printf("%-15s: %-3d : ",root->tu,root->soLan);
		Print2(root->e);
		printf("\n");
		PrintBST1(root->right);
	}
}

int CountNode(NODE* root) {
   if( root == NULL)
      return 0;
   else
      return 1 + CountNode(root->left) + CountNode(root->right);
}

NODE* root = NULL;
NODE* stopRoot = NULL;


int main()
{
	FILE *f = fopen("alice30.txt","r");
	FILE *f1 = fopen("stopw.txt","r");
	char c;
	char c_prev;
	int row;
	int space;
	int stop;
	int breakLine ;
	int i;
	char* s = calloc(100, sizeof(char));
	char* s1 = calloc(100, sizeof(char));
	i =0;
	while(!feof(f1))
	{
		fscanf(f1,"%s",s);
		InsertNode(&stopRoot,s,i);
	}

	fclose(f1);
	//PrintBST(stopRoot);
	//PrintBST1(stopRoot);
	printf("xong\n");

	i = 0;
	row = 1;
	space = 0;
	stop = 0;
	breakLine = 0;
	c = fgetc(f);
	//s1[0] = '\0';
	int check = 0;
	while(c != EOF)
	{	
		//printf("alo \n");
		if (c >= 'A' && c <= 'Z')
		{
			if(c_prev == ' '||c_prev == '.'||c_prev == '-')
			{
				check = 1;
			}
		}
		c = tolower(c);
		if(c < 'a' || c > 'z')
		{
			++stop;
			if(c == ' ' || c == '\n')
				++space;
			if(c == '\n')
			{
				++breakLine;
				++row;
			}
		}else{
			if(stop >= 2)
			{
				s1[i - stop] = '\0';
				if(search(stopRoot,s1) == NULL)
				{
					if(breakLine != 0)
					{	
						if (check == 0)
						{
							InsertNode(&root, s1, row - breakLine);
						}
						breakLine = 0;
						// printf("%s\n", s1);
					}else{
						if (check == 0)
						{
							InsertNode(&root, s1, row);
						}
					}
				i = 0;//
				check = 0;
				}
			}else{
				if(space == 1)
				{
					s1[i - 1] = '\0';
					i = 0;
					if(search(stopRoot,s1) == NULL)
					{
						if(breakLine != 0)
						{
							if (check == 0)
							{
								InsertNode(&root, s1, row - breakLine);
							}							
							breakLine = 0;
						}
						else
						{
							if (check == 0)
							{
								InsertNode(&root, s1, row);
							}
						}
					check = 0;
					}
				}			
			}
			stop = 0;
			space = 0;
		}
		s1[i++] = tolower(c);
		c_prev = c;
		c = fgetc(f);
		if(c == EOF)
		{
			s1[i - stop] = '\0';
			if(search(stopRoot,s1) == NULL){
				// printf("%s\n", s1);
				InsertNode(&root, s1, row);
			}
		}
	}
	fclose(f);
	PrintBST1(root);
	//printf("%d\n",CountNode(root));
}
