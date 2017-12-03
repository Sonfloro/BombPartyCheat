// Bomb Party Cheat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <direct.h>
#include <Windows.h>
#include <ctime>

using namespace std;
class CompareStrings
{
private:
	string m_string;

public:

	CompareStrings(string str = " ")
		:m_string(str)
	{
	}
	int length()
	{
		return m_string.length();
	}
	string get_string()
	{
		return m_string;
	}
	bool contains(string str)
	{
		unsigned int count = 0;
		vector<char> c_array(m_string.begin(), m_string.end());
		vector<char> str_array(str.begin(), str.end());
		if (str_array.size() > c_array.size())
		{
			return false;
		}
		for (unsigned int i = 0; i < c_array.size(); i++)
		{
			if (c_array[i] == str_array[count])
			{
				if ((i + str_array.size()) > c_array.size())
				{
					return false;
				}
				for (; count < str_array.size(); count++, i++)
				{
					if (c_array[i] != str_array[count])
					{
						count = 0;
						break;
					}
				}
				if (count == str_array.size())
				{
					return true;
				}
			}
		}
		return false;
	}
	bool startsWith(string str)
	{
		vector<char> c_array(m_string.begin(), m_string.end());
		vector<char> str_array(str.begin(), str.end());

		if (str_array.size() > c_array.size())
		{
			return false;
		}

		for (unsigned int i = 0; i < str_array.size(); i++)
		{
			if (c_array[i] == str_array[i])
			{
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	void setString(string str)
	{
		m_string = str;
	}
};




int getKeyCode(char letter)
{
	switch (letter)
	{
	case	'a':	return 0x41;
	case	'b':	return 0x42;
	case	'c':	return 0x43;
	case	'd':	return 0x44;
	case	'e':	return 0x45;
	case	'f':    return 0x46;
	case	'g':	return 0x47;
	case	'h':	return 0x48;
	case	'i':	return 0x49;
	case	'j':	return 0x4A;
	case	'k':	return 0x4B;
	case	'l':	return 0x4C;
	case	'm':	return 0x4D;
	case	'n':	return 0x4E;
	case	'o':	return 0x4F;
	case	'p':	return 0x50;
	case	'q':	return 0x51;
	case	'r':	return 0x52;
	case	's':	return 0x53;
	case	't':	return 0x54;
	case	'u':	return 0x55;
	case	'v':	return 0x56;
	case	'w':	return 0x57;
	case	'x':	return 0x58;
	case	'y':	return 0x59;
	case	'z':	return 0x5A;
	}
}


void toClipboard(const std::string &s) {
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hg) {
		CloseClipboard();
		return;
	} 
	memcpy(GlobalLock(hg), s.c_str(), s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

void typeKey(WORD key, int delay)
{
	INPUT input;
	WORD vkey = key; // see link below
	input.type = INPUT_KEYBOARD;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = vkey;
	input.ki.dwFlags = 0; // there is no KEYEVENTF_KEYDOWN
	SendInput(1, &input, sizeof(INPUT));

	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
	Sleep(delay);
}


bool alreadyUsed(string *str, string str2)
{
	for (unsigned int i = 0; i < 2048; i++)
	{
		if (str[i] == str2)
		{

			return true;
		}
	}
	return false;
}


void sortWords(string *words, int maxLength)
{
	for (int startIndex = 0; startIndex < maxLength; startIndex++)
	{
		int smallestIndex = startIndex;
		for (int currentIndex = startIndex + 1; currentIndex < maxLength; currentIndex++)
		{
			if (words[currentIndex].length() > words[smallestIndex].length())
			{
				smallestIndex = currentIndex;
			}
		}
		std::swap(words[startIndex], words[smallestIndex]);
	}
}
void clearUsedWords(string *wordsUsed)
{
	for (int i = 0; i < 2048; i++)
	{
		wordsUsed[i] = "";
	}
}

int main()
{
	string wordsUsed[15000];
	string specialWords[3] = { "con", "nul", "prn" };
	//string dictionary = "C:\\Users\\Sonfloro\\Documents\\Visual Studio 2015\\Projects\\Bomb Party Cheat\\textFiles\\dictionary.txt";
	string dictionary = "dictionary.txt";
	_mkdir("BPC");
	int offset = 0;
	bool b_recentlyUsed = false;
	string lastUsedWord;
	while (true)
	{
		string prompt;
		string replace_word;
		bool loop = true;
		bool isSavedPrompt = false;
		bool replace = false;
		b_recentlyUsed = false;
		do
		{
			cin.clear();
			cout << "Enter the word prompt" << endl;
			getline(cin, prompt);
		} while (prompt == "" || prompt == " ");

		if (prompt == "6")
		{
			clearUsedWords(wordsUsed);
			cout << "Words used list has been cleared!" << endl;
		}
		if (prompt == lastUsedWord)
		{
			b_recentlyUsed = true;
			
		}
		for (unsigned int i = 0; i < 2; i++)
		{
			if (prompt == specialWords[i])
			{
				replace = true;
				if (prompt == "con")
				{
					replace_word = "con_";
				}
				if (prompt == "nul")
				{
					replace_word = "nul_";
				}
				if (prompt == "prn")
				{
					replace_word = "prn_";
				}
			}
		}

		//ifstream savedPrompt("C:\\Users\\Sonfloro\\Documents\\Visual Studio 2015\\Projects\\Bomb Party Cheat\\textFiles\\savedPrompts.txt");
		ifstream savedPrompt("savedPrompts.txt");
		if (savedPrompt.is_open())
		{
			string line;
			while (getline(savedPrompt, line))
			{
				if (prompt == line)
				{
					isSavedPrompt = true;
					break;
				}
			}
			savedPrompt.close();
		}


		if (isSavedPrompt)
		{
			isSavedPrompt = false;
			int usableWordsIndex = 0;
			string usableWords[15000];
			ifstream readSavedPrompt;
			if (replace)
			{
				readSavedPrompt.open("BPC\\" + replace_word + ".txt");
			}
			else
			{
				readSavedPrompt.open("BPC\\" + prompt + ".txt");
			}
			string biggestWord;
			if (readSavedPrompt.is_open())
			{
				string line;
				while (getline(readSavedPrompt, line))
				{
					CompareStrings c_line(line);
					if (c_line.contains(prompt))
					{
						if (usableWordsIndex < 15000)
						{
							usableWords[usableWordsIndex] = c_line.get_string();
							usableWordsIndex++;
						}
					}
				}
				readSavedPrompt.close();
				sortWords(usableWords, 15000);
				sortWords(wordsUsed, 15000);
				bool used = false;
				for (unsigned int i = 0; i < 15000; i++)
				{

					if (alreadyUsed(wordsUsed, usableWords[i]))
					{
						used = true;
						biggestWord = usableWords[i + 1];
					}
					else
					{
						if (!used)
						{
							biggestWord = usableWords[0];
						}
					}
				}
				toClipboard(biggestWord);
				wordsUsed[offset] = biggestWord;
				offset++;
				for (unsigned int i = 0; i < 5; i++)
				{
					cout << usableWords[i] << endl;
				}
				Sleep(1000);
				char *keyboardInputArray = new char[biggestWord.size() + 1];
				strcpy_s(keyboardInputArray, biggestWord.size() + 1, biggestWord.c_str());
				srand(static_cast<unsigned int>(time(0)));
				rand();
				int random;
				for (int i = 0; i < biggestWord.size() + 1; i++)
				{
					random = rand() % 51 + 50;
					WORD code = getKeyCode(keyboardInputArray[i]);
					typeKey(code, random);
					srand(static_cast<unsigned int>(time(0)) + i);
				}
				typeKey(0x0D, 50);
				delete[] keyboardInputArray;
				lastUsedWord = biggestWord;
			}
			else
			{
				cout << "Error opening readSavedPrompt text file: " << prompt << ".txt " << endl;
			}
		}
		else
		{
			ofstream savedPrompt;
			//savedPrompt.open("C:\\Users\\Sonfloro\\Documents\\Visual Studio 2015\\Projects\\Bomb Party Cheat\\textFiles\\savedPrompts.txt", ios::app);
			savedPrompt.open("savedPrompts.txt", ios::app);
			savedPrompt << prompt << endl;
			savedPrompt.close();
			ofstream createSavedPrompt;
			if (replace)
			{
				createSavedPrompt.open("BPC\\" + replace_word + ".txt");
			}
			else
			{
				createSavedPrompt.open("BPC\\" + prompt + ".txt");
			}
			ifstream file(dictionary);
			int usableWordsIndex = 0;
			string usableWords[15000];
			string biggestWord;
			if (file.is_open())
			{
				string line;
				while (getline(file, line))
				{
					CompareStrings c_line(line);
					if (c_line.contains(prompt))
					{
						if (usableWordsIndex < 15000)
						{
							usableWords[usableWordsIndex] = c_line.get_string();
							usableWordsIndex++;
						}
						createSavedPrompt << line << endl;
					}
				}
				sortWords(usableWords, 15000);
				if (alreadyUsed(wordsUsed, usableWords[0]))
				{
					biggestWord = usableWords[offset];
				}
				else
				{
					biggestWord = usableWords[0];
				}
				toClipboard(biggestWord);
				wordsUsed[offset] = biggestWord;
				offset++;
				for (unsigned int i = 0; i < 5; i++)
				{
					cout << usableWords[i] << endl;
				}
				file.close();
				createSavedPrompt.close();
				Sleep(1000);
				char *keyboardInputArray = new char[biggestWord.size() + 1];
				strcpy_s(keyboardInputArray, biggestWord.size() + 1, biggestWord.c_str());
				srand(static_cast<unsigned int>(time(0)));
				rand();
				int random;
				for (int i = 0; i < biggestWord.size() + 1; i++)
				{
					random = rand() % 30;
					WORD code = getKeyCode(keyboardInputArray[i]);
					typeKey(code, random);
					srand(static_cast<unsigned int>(time(0)) + i);
				}
				typeKey(0x0D, 50);
				delete[] keyboardInputArray;
				lastUsedWord = biggestWord;
			}
			else
			{
				cout << "Error opening file..." << endl;
			}
		}
	}
}


