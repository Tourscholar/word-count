#include "Dataset.h"

Dataset::Dataset() : _command(0) {}

void Dataset::createFile()
{
	string fileName, line;
	cout << "Please enter the file name to be created: " << endl;
	cin >> fileName;
	ofstream file;

	file.open(fileName);

	char command = 'n';
	while (command == 'n')
	{
		cout << "Please enter a line of text: ";
		getline(cin, line);										/* 将cin输入读取到line中 */
		getline(cin, line);
		file << line << endl;
		cout << " End of input？y or n :";
		cin >> command;
	}
	cout << "End of the creation！" << endl;

	file.close();
}

void Dataset::printMenu()
{
	cout << "**********************************" << endl;
	cout << "*******Retrieval and counting of document text words******" << endl;
	cout << "---------------------------------" << endl;
	cout << "|\t\t" << "【1】Create a text document" << "\t\t\t|" << endl;
	cout << "|\t\t" << "【2】Text word summary" << "\t\t\t\t|" << endl;
	cout << "|\t\t" << "【3】Word location" << "\t\t\t\t|" << endl;
	cout << "|\t\t" << "【4】Quit" << "\t\t\t\t\t|" << endl;
	cout << "---------------------------------" << endl;
}

void Dataset::textCount()
{
	_currentLine = 0;
	_wordCount = 0;
	_nonWordCount = 0;
	cout << "Please enter a file name: ";
	string fileName;
	cin >> fileName;

	_wordMap.clear();
	wordCount(fileName);

	cout << ">>>>>>>>>>>>Word<<<>>>>Number<<<<<<" << endl;
	for (auto iter = _wordMap.begin(); iter != _wordMap.end(); iter++)
	{
		cout.fill(' ');
		/* fill成员函数设置填充的内容 */
		cout << setw(15) << iter->first << setw(10) << iter->second << endl;
		/* setw(n)用于在输出操作中设置使用的字段宽度 */

	}
	cout << endl << ">>>>>>>>>>>>>>>>" << "The total number of words for "
		<< fileName << " is " << _wordCount << endl << endl;
	cout << ">>>>>>>>>>>>>>>>" << "The total number of non-words for "
		<< fileName << " is " << _nonWordCount << endl << endl;
}

void Dataset::wordLocate()
{
	cout << "======================================" << endl;
	cout << "||      Positioning statistics and positioning of text file strings    ||" << endl;
	cout << "||==================================||" << endl;
	cout << "||\t\t" << "a.   The number of times a word appears  " << " \t\t||" << endl;
	cout << "||\t\t\t\t\t\t\t\t\t||" << endl;
	cout << "||\t\t\t\t\t\t\t\t\t||" << endl;
	cout << "||\t\t" << "b.   Where the word appears" << " \t\t\t\t||" << endl;
	cout << "||\t\t\t\t\t\t\t\t\t||" << endl;
	cout << "======================================" << endl;

	string command;
	cout << "Please enter a or b: ";
	cin >> command;
	string word;
	if (command == "a")
	{
		string fileName;
		cout << "Please enter a text file name: ";
		cin >> fileName;

		cout << "Please enter the word to be counted: ";
		cin >> word;
		_wordMap.clear();
		wordCount(fileName);
		cout << "Word: " << word << " Text file: " << fileName << " appear in total: " << _wordMap[word] << " times" << endl;
	}
	else if (command == "b")
	{
		string fileName;
		cout << "Please enter a text file name: ";
		cin >> fileName;
		wordPosition(fileName);
	}
	else
		cout << "Typing error, exited！" << endl;
}

void Dataset::executeCommand()
{
	while (_command != 4)
	{
		printMenu();
		cout << "please choose<1 ~ 4>:";
		cin >> _command;
		switch (_command)
		{
		case 1:
			createFile();
			break;
		case 2:
			textCount();
			break;
		case 3:
			wordLocate();
			break;
		default:
			cout << "Good Bye!" << endl;
			break;
		}

	}
}

void Dataset::wordPosition(string fileName)
{
	string word;
	cout << "Word to retrieve: ";
	cin >> word;
	_currentLine = 0;
	int position = 0;
	ifstream file;
	file.open(fileName);

	vector<int> _wordPosition;
	while (getline(file, _currentWords))
	{
		position = 1;
		_wordPosition.clear();
		_currentLine++;
		_wordCount = 0;
		stringstream ss(_currentWords);     //  建立一个stringstream的对象 并将刚才读取的line（字符串）的内容放在ss里面
		string tempWord;					/* (Create a stringstream object and put the content of the line 	
											   																					(string) just read in ss */
		while (ss >> tempWord)
		{
			if (word == tempWord)
			{
				_wordCount++;
				_wordPosition.push_back(position);
			}
			position += tempWord.size() + 1;
		}
		if (_wordCount != 0)
		{
			cout << "Line number: " << _currentLine << ", Occurrences is " << _wordCount << ", starting positions are: ";
			for (auto iter = _wordPosition.begin(); iter != _wordPosition.end(); iter++)
				cout << "  " << *iter;
			cout << " Characters" << endl;
		}
	}
	file.close();
}

void Dataset::wordCount(string fileName)
{
	ifstream file;
	file.open(fileName);
	while (getline(file, _currentWords))
	{
		_currentLine++;
		stringstream ss(_currentWords);          // 建立一个stringstream的对象 并将刚才读取的line（字符串）的内容放在ss里面
		string word;							 /* (Create a stringstream object and put the content of the line 	
																																		(string) just read in ss */										    
		string word;													 
		while (ss >> word) {

			if (word[0] >= 'A' && word[0] <= 'Z' || word[0] >= 'a' && word[0] <= 'z')
				_wordCount++;
			else
				_nonWordCount++;

			if (_wordMap[word] == 0)
				_wordMap[word] = 1;
			else
				_wordMap[word]++;
		}
	}
	file.close();
}
