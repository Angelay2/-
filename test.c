#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <windows.h>

#pragma warning(disable:4996)
//1.一个数组中只有两（1）个数字是出现一次，
//其他所有数字都出现了两次。
//找出这两个只出现一次的数字，编程实现。

//return value: 0:success, other:failed
//args: a:输入数组，num: 元素的个数， xp(yp):输出型参数， 通过该指针，获得对应的输出值
int FindTowData(int a[], int num, int *xp, int *yp)
{
	assert(a);
	assert(num >= 2);
	assert(xp);
	assert(yp);
	*xp = 0;
	*yp = 0;

	//A
	int result = a[0];
	int i = 1;
	for (; i < num; i++){
		result ^= a[i];
	}
	if (result == 0){
		return 1;
	}

	//B
	i = 0;
	int flag = 1;//0000 0001
	while (i < 8 * sizeof(int)){
		//不建议：flag<<=i;
		if (result & (flag<<i)){ // flag<<i 会不会影响flag的值呢？不会！！ x+=10
			break;
		}
		i++;
	}
	//C
	flag <<= i; //一个坑！！
	//flag 就标识了不相同的那个比特位！
	for (i = 0; i < num; i++){
		if (a[i] & flag){ //A
			*xp ^= a[i];
		}
		else{ //B
			*yp ^= a[i];
		}
	}
	return 0;
}

//2.喝汽水，1瓶汽水1元，2个空瓶可以换一瓶汽水，
//给20元，可以喝多少汽水。
//编程实现。
//return : total drink
//money : 钱数
int DrinkWater(int money)
{
	int total = money;
	int empty = money;

	while (empty > 1){	
		total += empty / 2;
		empty = empty / 2 + empty % 2;
	}
	printf("empty: %d\n", empty);//0?
	return total;
	//return total + 1; //可以向老板借一个空瓶子，最后喝完，再还给他。
}

void Reverse(char *start, char *end)
{
	assert(start);
	assert(end);
	while (start < end){
		*start ^= *end;
		*end ^= *start;
		*start ^= *end;
		start++, end--;
	}
}
//1.实现一个函数，可以左旋字符串中的k个字符。
//ABCD左旋一个字符得到BCDA
//ABCD左旋两个字符得到CDAB
void LeftMove(char *str, int len, int n)
{
	assert(str);
	assert(len > 0);
	assert(n > 0);

	int step = n % len;
	if (step == 0){
		return;
	}

	//1
	//int i = 0;
	//for (; i < step; i++){
	//	char c = str[0];
	//	int j = 1;
	//	for (; j < len; j++){
	//		str[j - 1] = str[j];
	//	}
	//	str[j - 1] = c;
	//}
	//2:推荐
	//Reverse(str, str + step - 1);
	//Reverse(str + step, str + len - 1);
	//Reverse(str, str + len - 1);
	//3
	char *mem = (char*)malloc(2 * len + 1);
	if (!mem){
		return;
	}
	strcpy(mem, str);
	strcat(mem, str);
	strncpy(str, mem+step, len);

	free(mem);
}

int main()
{
	char str[] = "1234abcd";
	LeftMove(str, strlen(str), 4000);
	printf("%s\n", str);


	//int money = 20;
	//int total = DrinkWater(money);
	//printf("total: %d\n", total);
	//int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1, 13, 45 };
	////int a[] = { 1, 2, 2, 1, 13, 45 };
	//int num = sizeof(a) / sizeof(a[0]);
	//int x, y;
	//if (FindTowData(a, num, &x,&y) == 0){ //success
	//	printf("find success : %d, %d\n", x, y);
	//}
	system("pause");
	return 0;
}