// Base32Dll.cpp: 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Base32Dll.h"


//// 这是导出变量的一个示例
//BASE32DLL_API int nBase32Dll=0;
//
//// 这是导出函数的一个示例。
//BASE32DLL_API int fnBase32Dll(void)
//{
//    return 42;
//}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 Base32Dll.h
//CBase32Dll::CBase32Dll()
//{
//    return;
//}
//#include "windows.h"
//typedef char* (*pEnc)(char*);
//文件头


//HMODULE hModule = LoadLibrary(L"Base32Dll.dll");
//if (!hModule) {
//	cout << "ERROR" << endl;
//}
//char pse[] = "CHAR";
//char* psd;
//psd = pEnc(GetProcAddress(hModule, "Base32Enc"))(pse);//不能写成(pEnc)GetProcAddress(hModule, "Base32Enc")(pse),函数的优先级较高,GetProcADdress会收到三个参数,所以需要先执行GetProcAddress,转换成pEnc类型再使用函数指针.
//printf("%s", psd);
//FreeLibrary(hModule);
//主函数


#include "Base32Dll.h"
#include "stdafx.h"
using namespace std;

#define allocERR 0
#define PutIn 10 //10的倍数

char Base32List[33] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

char* Base32Enc(char* argv)
{
	setlocale(LC_ALL, "chs");
	unsigned int StrCharSize, convStrBits = 0;//转换UNICODE编码后的char字符个数

	StrCharSize = mbstowcs(NULL, argv, 0);//调用函数获得需要的内存空间

	wchar_t* sp = new(nothrow) wchar_t[StrCharSize + 1]();//分配内存空间,存储UNICODE元数据
	unsigned char* od = new(nothrow) unsigned char[8 * (StrCharSize * sizeof(wchar_t) / sizeof(char) / 5 + 1) + 1]();//分配内存空间,存储编码后数据
	unsigned char* pProc, *dProc;//以8bit为单位的处理用指针
	void* pSrc, *pOverflow;//存储元数据首地址和溢出地址
	void* dSrc, *dOverflow;//存储译文首地址和溢出地址
	if ((sp == NULL) || (od == NULL)) return allocERR;//检测空指针

	mbstowcs((wchar_t*)sp, argv, 2 * StrCharSize);//在申请的内存空间存入转换后的UNICODE字符

	pProc = (unsigned char*)(sp);
	pSrc = sp;
	pOverflow = sp + StrCharSize;
	pOverflow = (char*)pOverflow + 1;
	dProc = (unsigned char*)(od);
	dSrc = od;
	dOverflow = od + 8 * (StrCharSize * sizeof(wchar_t) / sizeof(char) / 5 + 1);
	//各类指针初始化

	//for (unsigned int i = 0; i < StrCharSize + 1; i++) {
	//	for (int j = 15; j >= 0; j--) {
	//		if ((*sp & (1 << j)) != 0) {
	//			putchar('1');
	//		}
	//		else
	//		{
	//			putchar('0');
	//		}
	//	}//显示二进制
	//	*sp = *sp << 8 | *sp >> 8;
	//	sp++;
	//}
	//sp = (wchar_t*)srcp;
	//printf("\n");
	//由于wchar_t内存数据如此存放:第一个字符低位,第一个字符高位,第二个字符低位,第二个字符高位...
	//读取时wchar_t指针指向16bit数据,逆向读取(变成正常的高位->低位)
	//所以用char指针的时候就会出现(低位->高位)的错误
	//进行高低位交换后即可避免.

	for (unsigned int i = 0; i <= (StrCharSize / PutIn + 1); i++) {//以8 * #PutIn# bit数据为单位处理
		for (unsigned int i = 0; i < PutIn / 2; i++) {
			//for (int i = 15; i >= 0; i--) {
			//	if ((*sp & (1 << i)) != 0) {
			//		putchar('1');
			//	}
			//	else
			//	{
			//		putchar('0');
			//	}
			//}
			//显示二进制
			*sp = *sp << 8 | *sp >> 8;
			sp++;
			if (sp > pOverflow) { break; }//溢出检测
		}//对读入数据高低位交换
		 //sp = (wchar_t*)srcp;
		 //printf("\n");
		unsigned char pCode[8 * PutIn / 5] = { 0 };//创建译码后译文存储空间(8 * #PutIn# / 5位)
		int count = 0;
		for (int j = 0; j < PutIn; j++) {
			//for (int i = 7; i >= 0; i--) {
			//	if ((*pProc & (1 << i)) != 0) {
			//		putchar('1');
			//	}
			//	else
			//	{
			//		putchar('0');
			//	}
			//}
			//显示二进制
			for (int k = 0; k < 8; k++) {
				if ((*pProc & (1 << (7 - k))) != 0) { pCode[count / 5] |= (1 << (4 - (count % 5))); }//判断该位是否是1(用1移位再取与可知此位是0还是有值)并按5位二进制的实际值大小相加
				count++;
			}//对每一个char的8bit做操作
			pProc++;
			if (pProc > pOverflow) { break; }//溢出检测
		}//对一次性输入的#PutIN#个char字符操作
		 //printf("\n");
		for (int j = 0; j < 8 * PutIn / 5; j++) {
			*dProc = Base32List[pCode[j]];
			dProc++;
			if (dProc == dOverflow) { *dProc = 0; break; }
		}//译文译码
	}
	delete[] pSrc;

	return (char*)od;
}

