/******************************************************************************************
* Data Structures in C++
* ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
* Junhui DENG, deng@tsinghua.edu.cn
* Computer Science & Technology, Tsinghua University
* Copyright (c) 2006-2013. All rights reserved.
******************************************************************************************/

#pragma once

#pragma warning(disable : 4996 4800)
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "../_share/release.h"

class MyBitmap //λͼMyBitmap��
{ 
public: // Ϊ�˴�ӡ��Ϊpublic 0425
	char* M; int N; //����ͼ����ŵĿռ�M[]������ΪN*sizeof(char)*8����
protected:
	void init(int n) 
	{ 
		M = new char[N = (n + 7) / 8]; 
		memset(M, 0, N); 
	}
public:
	MyBitmap(int n = 8) { init(n); } //��ָ����Ĭ�Ϲ�ģ��������ͼ��Ϊ������ʱѡ�ý�С��Ĭ��ֵ��
	MyBitmap(char* file, int n = 8) //��ָ����Ĭ�Ϲ�ģ����ָ���ļ��ж�ȡ����ͼ
	{
		init(n); 
		FILE* fp = fopen(file, "r"); 
		fread(M, sizeof (char), N, fp); 
		fclose(fp);
	}
	~MyBitmap() { delete[] M; M = NULL; } //����ʱ�ͷű���ͼ�ռ�

	void set(int k)
	{
		expand(k);
		M[k >> 3] |= (0x80 >> (k & 0x07)); //  λͼ 0000 0100  ���� 6
		// int d = x/8;  
		// int num = k % 8; // ע k % 8 == (k & 0x07));
		// M[k >> 3] |= (1 << num);  λͼ 0000 0100  ���� 4
	}
	void clear(int k)
	{
		expand(k);
		M[k >> 3] &= ~(0x80 >> (k & 0x07));
	}
	bool test(int k)
	{
		expand(k);
		return M[k >> 3] & (0x80 >> (k & 0x07));
	}

	void dump(char* file) //��λͼ���嵼����ָ�����ļ����Ա�Դ˺����λͼ������ʼ��
	{
		FILE* fp = fopen(file, "w"); 
		fwrite(M, sizeof (char), N, fp); 
		fclose(fp);
	}
	char* bits2string(int n) //��ǰnλת��Ϊ�ַ�������
	{ 
		expand(n - 1); //��ʱ���ܱ����ʵ����λΪMyBitmap[n - 1]
		char* s = new char[n + 1]; 
		s[n] = '\0'; //�ַ�����ռ�ռ䣬���ϲ�����߸����ͷ�
		for (int i = 0; i < n; i++)
			s[i] = test(i) ? '1' : '0';
		return s; //�����ַ���λ��
	}
	void expand(int k) //�������ʵ�MyBitmap[k]�ѳ��磬��������
	{ 
		if (k < 8 * N) return; //���ڽ��ڣ���������
		int oldN = N; 
		char* oldM = M;
		init(2 * k); //���������ƣ��ӱ�����
		memcpy_s(M, N, oldM, oldN); 
		delete[] oldM; //ԭ����ת�����¿ռ�
	}	

	void print(int n) //��λ��ӡ�Լ���λͼ���ݣ��Ǳ���ӿ�
	{
		expand(n);
		for (int i = 0; i < n; i++)
			printf(test(i) ? "1" : "0");
	}
};
