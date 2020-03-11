#include "contact.h"

void InitContact(contact_p *cp)// ע�⣬�Ҵ������һ������ָ��
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
		printf("��ʼ����ɣ�ʹ��Ĭ�Ϸ�����\n");
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
	printf("��ʼ����ɣ�ʹ���ļ�������\n");
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
	printf("׼�����¿��ٿռ䣡%d\n", (*cp)->cap);

	int new_size = (*cp)->cap*2;
	contact_p new_contact = realloc(*cp, sizeof(contact_t)+sizeof(person_t)*new_size);
	if (NULL == new_contact){
		printf("���¿��ٿռ�ʧ��!\n");
		return 0;
	}
	new_contact->cap = new_size;
	//cp = &contact, *cp:contact
	*cp = new_contact;

	printf("���¿��ٿռ�ɹ���%d\n", (*cp)->cap);
	return 1;//�ɹ�
}
//cp = &contact, *cp:contact
int AddPersonToContact(contact_p *cp)
{
	//������ˣ�����Ҫ�����������ݣ�����ʧ�ܣ����ǲų����أ�
	if (IsFull(*cp) && !Inc(cp)){
		printf("add error!\n");//�ռ����ˣ�����������ʧ��
		return -1;
	}
	//1. �ռ�û�� 2.�ռ����ˣ�������������ɹ�
	person_p p = &((*cp)->person[(*cp)->size]);
	printf("�������������# ");
	scanf("%s", p->name); //int a = 0;scanf("%d", &a); char b[10];scanf("%s", b);
	printf("����������Ա�# "); 
	scanf("%s", p->sex);
	printf("������������# ");
	scanf("%d", &(p->age)); //scanf("%s%s%d%d", a,b,c,d,e);
	printf("��������ĵ绰# ");
	scanf("%s", p->telphone);
	printf("���������סַ# ");
	scanf("%s", p->address);
	(*cp)->size += 1;
	return 0;
}
int SearchPersonFromContact(contact_p cp)//����������
{
	char _name[NAME_SIZE];
	printf("��������Ҫ��ѯ���˵�����# ");
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

int DelPersonFromContact(contact_p cp)//������ɾ��
{
	if (IsEmpty(cp)){
		printf("ͨѶ¼�ǿյģ�����ɾ��!\n");
		return 1;
	}
	char _name[NAME_SIZE];
	printf("��������Ҫɾ�����˵�����# ");
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

void SortContact(contact_p cp)//������������
{
	if (IsEmpty(cp)){
		printf("ͨѶ¼�ǿյģ�����sort!\n");
		return;
	}
	qsort(cp->person, cp->size, sizeof(person_t), CompName);
	printf("sort done!\n");
}

void SaveContact(contact_p cp)
{
	FILE *fp = fopen(SAVE_FILE, "wb");
	if (NULL == fp){
		printf("����ʧ��!��ע�⣡\n");
		return;
	}
	fwrite(cp, sizeof(contact_t), 1, fp);
	fwrite(cp->person, sizeof(person_t), cp->size, fp);
	fclose(fp);
	printf("save done!\n");
}