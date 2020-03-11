#ifndef _CONTACT_H_
#define _CONTACT_H_

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#pragma warning(disable:4996)

#define NAME_SIZE 32
#define SEX_SIZE 8
#define TELPHONE_SIZE 16
#define ADDRESS_SIZE 128
#define DEFAULT 1

#define SAVE_FILE "save.bin"

typedef struct _person{
	char name[NAME_SIZE];
	char sex[SEX_SIZE];
	int age;
	char telphone[TELPHONE_SIZE];
	char address[ADDRESS_SIZE];
}person_t, *person_p;

typedef struct _contact{
	int cap; //�ܹ����ɵ�����
	int size;//��ǰ����
	person_t person[0]; //��������
}contact_t, *contact_p;

//1. �����ڶ�ȡ�ļ���ʱ����û�п��ܣ��ļ����ڣ�����Ϊ�գ�
//2. ͨѶ¼��д��ʱ��û�п������������ظ������⣬������㿼�ǣ���������ķ�����޸��أ�
//int ModPersonFromContact();

void InitContact(contact_p *cp);// ע�⣬�Ҵ������һ������ָ��
int AddPersonToContact(contact_p *cp);
int DelPersonFromContact(contact_p cp);//������
int SearchPersonFromContact(contact_p cp);//����������
void ShowContact(contact_p cp);
void ClearContact(contact_p cp);
void SortContact(contact_p cp); //������������
void SaveContact(contact_p cp);

#endif