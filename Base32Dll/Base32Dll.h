// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 BASE32DLL_EXPORT
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// BASE32DLL_API 函数视为自 DLL 导入，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef BASE32DLL_EXPORTS
#define BASE32DLL_API __declspec(dllexport)
#else
#define BASE32DLL_API __declspec(dllimport)
#endif

// 此类导出自 Base32Dll.dll
//class BASE32DLL_API CBase32Dll {
//public:
//	CBase32Dll(void);
//	// TODO:  在此添加您的方法。
//};

//extern BASE32DLL_API int nBase32Dll;
//
//BASE32DLL_API int fnBase32Dll(void);

extern "C" _declspec(dllexport) char* Base32Enc(char* argv);
