#include "pch.h"
#include "ReadDataFromFile.h"


ReadDataFromFile::ReadDataFromFile(string fileName)
{
	
	inp_fileName = fileName;
	eof = true;
	// Opening file in input mode 
	infile.open(inp_fileName, ios_base::in);
	if (infile) eof = false;
}


string ReadDataFromFile::ReadLine() {
	string line;
	while (infile) {
		// Read a Line from File 
		getline(infile, line);
		return line;
	}

	CloseFile();

	return "";
}

vector<string>  ReadDataFromFile::GetSplitItems(char delimiter) {
	vector<string> tokens;
	string line;
	while (infile) {
		// Read a Line from File 
		getline(infile, line);
		split(line, delimiter, tokens);
		
	}

	CloseFile();
	return tokens;
}

string  ReadDataFromFile::GetSplitItem(char delimiter) {
	string line;
	int size = static_cast<int>(tokensBag.size());
	if (size > 0) {
		string back = tokensBag.back();
		tokensBag.pop_back();
		return back;
	}
	if (infile) {
		// Read a Line from File 
		getline(infile, line);
		split(line, delimiter, tokensBag);
		int size2 = static_cast<int>(tokensBag.size());
		if (size2 > 0) {
			string back = tokensBag.back();
			tokensBag.pop_back();
			return back;
		}
	}

	CloseFile();
	return "";
}

vector<string> ReadDataFromFile::split(const string& s, char delimiter)
{
	vector<string> tokens;
	string token;
	istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

void ReadDataFromFile::split(const string& s, char delimiter, vector<string>& tokens)
{

	string token;
	istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter))
	{
		auto tokenTrim = trim(token);
		if (tokenTrim.length() > 0) {
			tokens.push_back(token);
		}
	}
	
}

std::string ReadDataFromFile::trim(const std::string &s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isspace(*it))
		it++;

	std::string::const_reverse_iterator rit = s.rbegin();
	while (rit.base() != it && isspace(*rit))
		rit++;

	return std::string(it, rit.base());
}

void ReadDataFromFile::CloseFile() {
	// Close the file 
	if (infile.is_open()) {
		infile.close();
	}
	eof = true;
}


ReadDataFromFile::~ReadDataFromFile()
{
	CloseFile();
}
