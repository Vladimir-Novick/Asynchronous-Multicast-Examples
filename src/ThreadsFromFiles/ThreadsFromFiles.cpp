// ThreadsFromFiles.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "ReadDataFromFile.h"

void FileReader(string fileName)
{
	ReadDataFromFile dataStream(fileName);
	string splitItem = dataStream.GetSplitItem(' ');
	while (splitItem.length() > 0) {
		cout << splitItem << endl;
		splitItem = dataStream.GetSplitItem(' ');
	}

	/*
	int size = static_cast<int>(splitItems.size());
	for (int i = 0; i < size; i++) {
		cout << splitItems[i] << endl;
	}
	*/
}

void do_join(std::thread& t)
{
	t.join();
}

void join_all(std::vector<std::thread>& v)
{
	std::for_each(v.begin(), v.end(), do_join);
}

int main()
{
	vector<string> fileNames;
	vector< thread> threadsItems;

	std::mutex myMutex;


	fileNames.push_back("d:/t/test_1.txt");
	fileNames.push_back("d:/t/test_2.txt");
	fileNames.push_back("d:/t/test_3.txt");

	int sizeNames = static_cast<int>(fileNames.size());
	for (int i = 0; i < sizeNames; i++) {
		string fileName = fileNames[i];
		threadsItems.push_back(std::thread(FileReader, fileName));
	}

	join_all(threadsItems);

/*
	int size = static_cast<int>(splitItems.size());
	for (int i = 0; i < size; i++) {
		cout << splitItems[i] << endl;
	}
*/

	cout << "\n\n Press any key";
	char c;
	
	cin >> c;

}

