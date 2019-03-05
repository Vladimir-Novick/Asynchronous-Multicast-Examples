
#include "pch.h"
#include <iostream>
#include "ReadDataFromFile.h"
#include "Accumulator.h"

void FileReader(string fileName,  Accumulator* ObjectToCallBack)
{
	ReadDataFromFile dataStream(fileName);
	string splitItem = dataStream.GetSplitItem(' ');
	while (splitItem.length() > 0) {
		ObjectToCallBack->CallBackFunction(splitItem);
		splitItem = dataStream.GetSplitItem(' ');
	}
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

	Accumulator accumulator;

	int sizeNames = static_cast<int>(fileNames.size());
	for (int i = 0; i < sizeNames; i++) {
		string fileName = fileNames[i];
		threadsItems.push_back(std::thread(FileReader, fileName, &accumulator));
	}

	join_all(threadsItems);


	cout << "\n\n Press any key";
	char c;
	
	cin >> c;

}

