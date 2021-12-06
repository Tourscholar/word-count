#ifndef Dataset_h
#define Dataset_h

#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <map>
#include <string>
#include <fstream>
using namespace std;

class Dataset {

private:
	int               _command;           		//命令
	int               _currentLine;       		// 目前所在行
	int               _wordCount;         		// 单词计数
	int               _nonWordCount;      		// 非单词计数
	string            _currentWords;      		// 目前的单词串
	map<string, int>  _wordMap;          			// 单词地图

public:
	Dataset(): _command(0){ }									// 构造函数			
	void createFile();												// 创建文本文件
	void printMenu();													// 打印菜单
	void textCount();													// 统计单词与非单词个数
	void wordLocate();												// 统计单词出现的次数与位置
	void executeCommand();										// 执行各项命令
	void wordPosition(string fileName);				// 返回单词的位置
	void wordCount(string fileName);					// 单吃数量统计
};
#endif /* Dataset_h */