#ifndef ReadDataFromFile_H
#define ReadDataFromFile_H

#include <string>
#include <iostream> 
#include <fstream> 
#include <vector> 
#include <sstream>     
#include <conio.h>
#include <thread>
#include <algorithm>
#include <mutex>
#include <regex>

using namespace std;

class ReadDataFromFile
{
private:
	string inp_fileName;
	ifstream infile;
	void CloseFile();
	vector<string> split(const string& s, char delimiter);
	void split(const string& s, char delimiter, vector<string>& tokens);
	vector<string> tokensBag;
	string trim(const std::string &s);
public:
	bool eof;
	string ReadLine();
	vector<string>  GetSplitItems(char delimiter);
	string  GetSplitItem(char delimiter);
	ReadDataFromFile(string fileName);
	~ReadDataFromFile();

};

#endif 