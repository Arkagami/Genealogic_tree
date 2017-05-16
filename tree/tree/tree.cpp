#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

int printneed = 0;
int que = 0;
int pokolenie = 0;
int consta = 10;
int hms = 0;
typedef struct tree TREE;
//TREE *human;
TREE **id;

TREE *ADD(char *per);
TREE *ADD_PARENTS(tree *ch, char *per);
TREE *ADD_CHILD(tree *parent);


struct tree {
	int id;
	char *name;
	bool gender;
	int   age;
	tree *mother;
	tree *father;
	tree *child[5];
};

struct list{
	char *el;
	list *next;
};

struct queue {
	list *beg, *end;
};

void Print_person() {
	printf("\n");
	for (int i = 0; i < hms; i++) {
		printf("%i %s\n", i, id[i]->name);
	}
}

void pushToQueue(queue *q, char *iEl)   //добавить в очередь
{
	list *tmp;
	tmp = (list*)malloc(sizeof(list));
	tmp->next = NULL;
	tmp->el = iEl;
	if (q->end != NULL)
		q->end->next = tmp;
	else
		q->beg = tmp;
	q->end = tmp;
}

int popFromQueue(queue *q, char **iEl) // вз€ть из очереди
{
	if (q->beg == NULL) return 0;
	list *tmp;
	tmp = q->beg;
	*iEl = tmp->el;
	q->beg = tmp->next;
	delete tmp;
	if (q->beg == NULL) q->end = NULL;
	return 1;
}

queue *CreateQueue()            //создать очередь
{
	queue *q;
	q = (queue *)malloc(sizeof(queue));
	q->beg = NULL;
	q->end = NULL;
	return q;
}

int isQueueEmpty(queue *q)      //проверка очереди на пустоту
{
	if (q->beg == NULL) return 1;
	return 0;
}

int ClearQueue(queue *q)        //очистка очереди
{
	if (q->beg == NULL) return 0;
	list *tmp, *t;
	tmp = q->beg;
	while (tmp->next != NULL)
	{
		t = tmp;
		tmp = t->next;
		delete t;
	}
	q->beg = NULL;
	q->end = NULL;
	return 1;
}

void PrintQueue(queue *q)       //вывестии очередь на экран
{
	//printf("\n");
	queue *tmp = CreateQueue();
	char *iEl = NULL;
	while (!isQueueEmpty(q))
	{
		popFromQueue(q, &iEl);
		printf("%s\t ", iEl);
		pushToQueue(tmp, iEl);
	}
	while (!isQueueEmpty(tmp))
	{
		popFromQueue(tmp, &iEl);
		pushToQueue(q, iEl);
	}
}

void chek_array(){
	if (consta == hms) {
		consta *= 2;
		realloc(id, consta * sizeof(TREE));
	}
}

TREE *add_mother(tree *ch){
	int flag;
	char noname[100];
	printf("\nChoose from existing people(1) or add a new person(2)?\n");
	scanf_s("%i", &flag);

	if (flag == 2) {
		//realloc(id, sizeof(id) + sizeof(int));
		chek_array();
		printf("Enter her name: ");
		memset(noname, 0, sizeof(noname));
		scanf_s("%s", noname, 100);
		//gets_s(noname);

		id[hms] = ADD_PARENTS(ch, noname);
		ch->mother = id[hms];
		id[hms]->gender = 0;
		hms += 1;
		return id[hms];
	}
	if (flag == 1) {
		int number, i=0;
		Print_person();
		printf("\nSelect a person from the list and enter his number: ");
		scanf_s("%i", &number);
		ch->mother = id[number];
		while (id[number]->child[i] != NULL) i++;
		id[number]->child[i] = ch;
		//while (i < 5) id[number]->child[i] = NULL;
		printf("\nReady\n");
		return id[number];
	}
	if ((flag!=1)&&(flag!=2)) {
		ch->mother = NULL;
		return NULL;
	}
	return NULL;
}

TREE *add_father(tree *ch) {
	int flag;
	char noname[100];
	printf("Choose from existing people(1) or add a new person(2)?\n");
	scanf_s("%i", &flag);

	if (flag == 2) {
		//realloc(id, sizeof(id) + sizeof(int));
		chek_array();
		printf("Enter his name: ");
		memset(noname, 0, sizeof(noname));
		scanf_s("%s", noname, 100);
		//gets_s(noname, 100);

		id[hms] = ADD_PARENTS(ch, noname);
		ch->father = id[hms];
		id[hms]->gender = 1;
		hms += 1;
		return id[hms];
	}

	if (flag == 1) {
		int number, i = 0;
		Print_person();
		printf("Select a person from the list and enter his number: ");
		scanf_s("%i", &number);
		ch->father = id[number];
		while (id[number]->child[i] != NULL) i++;
		id[number]->child[i] = ch;
		//while (i < 5) id[number]->child[i] = NULL;

		printf("Ready");
		return id[number];
	}

	if ((flag != 1) && (flag != 2)) {
		ch->father = NULL;
		return NULL;
	}
	return NULL;
}

/*TREE *child_child(tree *ch) {
	int number;
	char noname[100];
	printf(" Enter children number(<5)\n");
	scanf_s("%i", &number);
	for (int i = 1; i <= number; i++) {
		//realloc(id, sizeof(id) + sizeof(int));
		chek_array();
		printf("Enter child's name");
		memset(noname, 0, sizeof(noname));
		scanf_s("%s", noname, 100);

		id[hms++] = ADD_CHILD(ch, noname);
		ch->child[i - 1] = id[hms - 1];
	}
	for (int i = number; i < 5; i++)
		ch->child[i] = NULL;


}*/

TREE *ADD(char *per)
{
	//id = (TREE **)malloc(44 * sizeof(TREE *));
	TREE *human;
	int age, gen;
	chek_array();

	human = (TREE*) malloc(sizeof(TREE));
	human->name = (char *)malloc(strlen(per) + 1);
	strcpy_s((human->name), strlen(per)+1, per);
	//strcpy_s()
	id[hms++] = human;

	printf("Enter age:");
	scanf_s("%i", &age);
	human -> age = age;

	printf("Enter gender. \n1-men\n2-women\n");
	scanf_s("%i", &gen);
	if (gen == 1) human->gender = 1;
	if (gen == 2) human->gender = 0;

	human->mother = NULL;
	human->father = NULL;
	int i = 0;
	while (i < 5) {
		human->child[i] = NULL;
		i++;
	}

	return human;
}

TREE *ADD_PARENTS(tree *ch, char *per) {
	TREE *human;
	int age;
	chek_array();
	human = (TREE *)malloc(sizeof(TREE));
	human->name = (char *)malloc(strlen(per) + 1);
	strcpy_s((human->name), strlen(per)+1, per);
	printf("Enter age: ");
	scanf_s("%i", &age);
	human->age = age;
	human->child[0] = ch;
	human->mother = NULL;
	human->father = NULL;
	for (int i = 1; i < 5; i++)
		human->child[i] = NULL;
	return human;
}

TREE *ADD_CHILD(tree *parent) {
	TREE *human;
	int age;
	int flag;
	printf("\nChoose from existing people(1) or add a new person(2)? Enter number: \n");
	scanf_s("%i", &flag);

	if (flag == 1) {
		int number, i = 0;
		Print_person();
		printf("Select a person from the list and enter his number: ");
		scanf_s("%i", &number);
		if ((parent->gender) == 1)  id[number]->father = parent;
		if ((parent->gender) == 0)  id[number]->mother = parent;  
		return id[number];

	}

	if (flag == 2) {
		chek_array();
		printf("Enter his or her name:");
		char noname[101];
		scanf_s("%s", &noname, 100);
		//gets_s(noname);
		human = (TREE *)malloc(sizeof(TREE));
		human->name = (char *)malloc(strlen(noname) + 1);
		strcpy_s((human->name), strlen(noname) + 1, noname);
		printf("Enter your age");
		scanf_s("%i", &age);
		human->age = age;
		id[hms] = human;
		hms++;
		if ((parent->gender) == 1) { human->father = parent; human->mother = NULL; }
		if ((parent->gender) == 0) { human->mother = parent; human->father = NULL; }
		for (int i = 0; i < 5; i++)
			human->child[i] = NULL;
		return human;
	}
	return NULL;
}

void CONNECT_PEOPLE() {
	int number, i = 0;
	int flag;
	//char noname[101];
	Print_person();
	printf("\n\nSelect a person from the list and enter his number: ");
	scanf_s("%i", &number);

	if (id[number]->mother == NULL) {
		printf("\n\nIf you want to add a mother, then press 1: ");
		scanf_s("%i", &flag);
		if (flag == 1) add_mother(id[number]);
		//else id[number]->mother = NULL;
	}

	if (id[number]->father == NULL) {
		printf("\n\nIf you want to add a father, then press 1: ");
		scanf_s("%i", &flag);
		if (flag == 1) add_father(id[number]);
		//else id[number]->father = NULL;
	}

	i = 0;
	while (id[number]->child[i] != NULL) i++;
	if (i < 5) {
		printf("\nIf you want to add a child, then press 1: ");
		scanf_s("%i", &flag);
		if (flag == 1) {

			int numb = 10;
			while (numb > 5 - i) {
			printf("\nHow many children do you want to add? Enter the number from 1 to %i!\n", (5 - i));
			scanf_s("%i", &numb);
		}
			int j = 0;
			
			while (j < numb) {
				id[number]->child[i + j] = ADD_CHILD(id[number]);
				j++;
			}
		}
	}
	//printf("Choose from existing people(1) or add a new person(2)?\n");
	//scanf_s("%i", &flag);
	//return human;
}

queue *Ancestors(queue *g, tree *a) {
	tree *mth, *fth;
	char *name;

	if (popFromQueue(g, &name) == 1) {
		printf("%s\t", name);
		printneed -= 1;
	}

	if ((mth = a->mother) != NULL) { pushToQueue(g, mth->name); que += 1; }
	if ((fth = a->father) != NULL) { pushToQueue(g, fth->name); que += 1; }

	if ((printneed == 0)&&(que!=0)) {
		printf("\n%i generation:", pokolenie);
		printneed = que;
		que = 0;
		pokolenie += 1;
		//PrintQueue(g);
	}
	
	if (mth!= NULL) g = Ancestors(g, mth);
	if (fth!= NULL) g = Ancestors(g, fth);

	return g;
}

queue *Descendants(queue *g, tree *a) {
	tree *ch[5];
	char *name;

	if (popFromQueue(g, &name) == 1) {
		printf("%s\t", name);
		printneed -= 1;
	}

	if ((ch[0] = a->child[0]) != NULL){	pushToQueue(g, ch[0]->name); que += 1;}
	if ((ch[1] = a->child[1]) != NULL){	pushToQueue(g, ch[1]->name); que += 1;}
	if ((ch[2] = a->child[2]) != NULL){	pushToQueue(g, ch[2]->name); que += 1;}
	if ((ch[3] = a->child[3]) != NULL){	pushToQueue(g, ch[3]->name); que += 1;}
	if ((ch[4] = a->child[4]) != NULL){	pushToQueue(g, ch[4]->name); que += 1;}

	if (printneed == 0) {
		printf("\n%i generation:", pokolenie);
		printneed = que;
		que = 0;
		pokolenie += 1;
	}

	if (ch[0] != NULL)	Descendants(g, ch[0]);
	if (ch[1] != NULL)	Descendants(g, ch[1]);
	if (ch[2] != NULL)	Descendants(g, ch[2]);
	if (ch[3] != NULL)	Descendants(g, ch[3]);
	if (ch[4] != NULL)	Descendants(g, ch[4]);
	
	return g;
}

void turn_person(){
	int number = 0;
	int answ = 0;
	queue *line;
	line = CreateQueue();
	printf("\nFrom whom you want to recognize relatives? You will choose id of the person");
	Print_person();
	scanf_s("%i", &number);
	printf("\nTo print ancestors(1) or descendants(2) ?");
	scanf_s("%i", &answ);

	printneed = 1;
	que = 0;

	if (answ == 1) { 
		pokolenie = 1;
		pushToQueue(line, id[number]->name);
		line = Ancestors(line, id[number]); 
		PrintQueue(line); 
		_getch(); }//ѕредки
	if (answ == 2) { 
		pokolenie = 1;
		pushToQueue(line, id[number]->name);
		line = Descendants(line, id[number]); 
		PrintQueue(line); 
		_getch(); }//ѕотомки
}

int main()
{	
	//int *id;
	char person;
	int d;
	id = (TREE **)malloc(consta * sizeof(TREE *));

	printf("Hello!It is your family tree.\n\n");
	do {
		
		printf("Menu:\n0\tExit\n1\tAdd new person\n2\tEdit person\n3\tPrint children and grandchildren\n");
		scanf_s("%d", &d);

		if (d == 1) {
			//id = (TREE **)malloc(consta* sizeof(TREE *));
			printf("Enter First Name:");
			scanf_s("%s", &person, 100);
			//gets_s(person);
			ADD(&person);
		};

		if (d == 2) { 
			//printf("Enter Your First Name and Last Name:");
			//scanf_s("%s", &person, 100);
			
			CONNECT_PEOPLE();
			
		};

		if (d == 3) {  
			turn_person();
		};

		system("cls");
	} while (d != 0);
	return 0;
}