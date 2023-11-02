#include "FileManager.h"
#include "LoopHero.h"
#include <fstream>

bool FileManager::LoadFile()
{


	fileName = "Text/Data.ini";
	if(mDatas.find(fileName) != mDatas.end()) return false;
										//置段 持失					持失切 ()
	mDatas.insert(make_pair(fileName, map<string, map<string, string>>()));

	ifstream ifs;
	ifs.open("Text/Data.ini");

	string group, key, data;
	char c;
	while (!ifs.eof())
	{
		c = ifs.peek();
		switch (c)
		{
		case '[':
			getline(ifs, group);
			group = group.substr(1, group.length() - 2);
			if (mDatas[fileName].find(group) == mDatas[fileName].end())
			{
				mDatas[fileName].insert(make_pair(group, map<string, string>()));
			}
			break;
		case '#':
		case '\n':
			getline(ifs, data);
			break;
		default:
			getline(ifs, key, '=');
			getline(ifs, data);

			if (!data.empty())
			{
				data = data.substr(1, data.length() - 2);
			}
			if (mDatas[fileName][group].find(key) == mDatas[fileName][group].end())
			{
				mDatas[fileName][group].insert(make_pair(key, data));
			}
			break;
		}
	}

	
	return true;

}

void FileManager::SaveFile()
{
}

void FileManager::LoadIniFile(string filePath, string tag)
{
	if (mDatas.find(tag) != mDatas.end()) return;
	mDatas.insert(make_pair(tag, map<string, map<string, string>>()));

	ifstream ifs;
	ifs.open(filePath.c_str(), ios_base::in);
	if (ifs.is_open())
	{
		string group, key, data;
		while (!ifs.eof())
		{
			char c = ifs.peek();
			switch (c)
			{
			case '[':
				getline(ifs, group);
				group = group.substr(1, group.length() - 2);
				if (mDatas[tag].find(group) == mDatas[tag].end()) mDatas[tag].insert(make_pair(group, map<string, string>()));
				break;
			case '#':
			case '\n':
				getline(ifs, data);
				break;
			default:
				getline(ifs, key, '=');
				getline(ifs, data);
				if (!data.empty()) data = data.substr(1, data.length() - 2);
				if (mDatas[tag][group].find(key) == mDatas[tag][group].end()) mDatas[tag][group].insert(make_pair(key, data));
				break;
			}
		}

		ifs.close();
	}
}