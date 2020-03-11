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
	int cap; //总共容纳的人数
	int size;//当前人数
	person_t person[0]; //柔性数组
}contact_t, *contact_p;

//1. 我们在读取文件的时候，有没有可能，文件存在，但是为空？
//2. 通讯录编写的时候，没有考虑输入内容重复的问题，如果让你考虑，你会做那哪方面的修改呢？
//int ModPersonFromContact();

void InitContact(contact_p *cp);// 注意，我传入的是一个二级指针
int AddPersonToContact(contact_p *cp);
int DelPersonFromContact(contact_p cp);//用姓名
int SearchPersonFromContact(contact_p cp);//用姓名查找
void ShowContact(contact_p cp);
void ClearContact(contact_p cp);
void SortContact(contact_p cp); //人名进行排序
void SaveContact(contact_p cp);

#endif