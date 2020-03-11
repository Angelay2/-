#include "contact.h"

void InitContact(contact_p *cp)// 注意，我传入的是一个二级指针
{
	FILE *fp = fopen(SAVE_FILE, "rb");
	if(fp == NULL){
		*cp = (contact_p)malloc(sizeof(contact_t)+sizeof(person_t)*DEFAULT);
		if (NULL == *cp){
			perror("malloc");
			exit(1);
		}
		(*cp)->cap = DEFAULT;
		(*cp)->size = 0;
		printf("初始化完成，使用默认方案！\n");
		return;
	}
	contact_t ct;
	fread(&ct, sizeof(contact_t), 1, fp);

	*cp = (contact_p)malloc(sizeof(contact_t)+sizeof(person_t)*(ct.cap));
	if (NULL == *cp){
		perror("malloc");
		exit(1);
	}
	memcpy(*cp, &ct, sizeof(ct));
	//(*cp)->cap = ct.cap;
	//(*cp)->size = ct.size;
	fread((*cp)->person, sizeof(person_t), ct.size, fp);
	printf("初始化完成，使用文件方案！\n");
	fclose(fp);
}

static int IsFull(contact_p cp)
{
	return cp->size < cp->cap ? 0 : 1;
}
static int IsEmpty(contact_p cp)
{
	return cp->size == 0;
}
static int Inc(contact_p *cp)
{
	printf("准备重新开辟空间！%d\n", (*cp)->cap);

	int new_size = (*cp)->cap*2;
	contact_p new_contact = realloc(*cp, sizeof(contact_t)+sizeof(person_t)*new_size);
	if (NULL == new_contact){
		printf("重新开辟空间失败!\n");
		return 0;
	}
	new_contact->cap = new_size;
	//cp = &contact, *cp:contact
	*cp = new_contact;

	printf("重新开辟空间成功！%d\n", (*cp)->cap);
	return 1;//成功
}
//cp = &contact, *cp:contact
int AddPersonToContact(contact_p *cp)
{
	//如果满了，我们要进行主动扩容，扩容失败，我们才出错返回！
	if (IsFull(*cp) && !Inc(cp)){
		printf("add error!\n");//空间满了，且重新申请失败
		return -1;
	}
	//1. 空间没满 2.空间满了，但是重新申请成功
	person_p p = &((*cp)->person[(*cp)->size]);
	printf("请输入你的姓名# ");
	scanf("%s", p->name); //int a = 0;scanf("%d", &a); char b[10];scanf("%s", b);
	printf("请输入你的性别# "); 
	scanf("%s", p->sex);
	printf("请输入你的年纪# ");
	scanf("%d", &(p->age)); //scanf("%s%s%d%d", a,b,c,d,e);
	printf("请输入你的电话# ");
	scanf("%s", p->telphone);
	printf("请输入你的住址# ");
	scanf("%s", p->address);
	(*cp)->size += 1;
	return 0;
}
int SearchPersonFromContact(contact_p cp)//用姓名查找
{
	char _name[NAME_SIZE];
	printf("请输入你要查询的人的姓名# ");
	scanf("%s", _name);
	int i = 0;
	printf("----------------------------------------------\n");
	for (; i < cp->size; i++){
		person_p p = &(cp->person[i]);
		if (strcmp(p->name, _name) == 0){
			printf("| %s | %s | %d | %s | %s |\n", \
				p->name, p->sex, p->age, p->telphone, p->address);
			printf("----------------------------------------------\n");
		}
	}
	return 0;
}

void ShowContact(contact_p cp)
{
	int i = 0;
	printf("----------------------------------------------\n");
	for (; i < cp->size;i++ ){
		person_p p = &(cp->person[i]);
		printf("| %s | %s | %d | %s | %s |\n", \
			p->name, p->sex, p->age, p->telphone, p->address);
		printf("----------------------------------------------\n");
	}
}

int DelPersonFromContact(contact_p cp)//用姓名删除
{
	if (IsEmpty(cp)){
		printf("通讯录是空的，不能删除!\n");
		return 1;
	}
	char _name[NAME_SIZE];
	printf("请输入你要删除的人的姓名# ");
	scanf("%s", _name);
	int i = 0;
	for (; i < cp->size; i++){
		person_p p = &(cp->person[i]);
		if (strcmp(p->name, _name) == 0){
			memcpy(p, &(cp->person[cp->size - 1]), sizeof(person_t));
			break;
		}
	}
	cp->size--;
	return 0;
}

void ClearContact(contact_p cp)
{
	cp->size = 0;
}

//1, 0, -1
static int CompName(const void *x, const void *y)
{
	person_p xp = (person_p)x;
	person_p yp = (person_p)y;

	return strcmp(xp->name, yp->name);
}

void SortContact(contact_p cp)//人名进行排序
{
	if (IsEmpty(cp)){
		printf("通讯录是空的，不能sort!\n");
		return;
	}
	qsort(cp->person, cp->size, sizeof(person_t), CompName);
	printf("sort done!\n");
}

void SaveContact(contact_p cp)
{
	FILE *fp = fopen(SAVE_FILE, "wb");
	if (NULL == fp){
		printf("保存失败!请注意！\n");
		return;
	}
	fwrite(cp, sizeof(contact_t), 1, fp);
	fwrite(cp->person, sizeof(person_t), cp->size, fp);
	fclose(fp);
	printf("save done!\n");
}