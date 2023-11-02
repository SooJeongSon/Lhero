#pragma once
#include "Singleton.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

class FileManager : public Singleton<FileManager>
{
private:
	string fileName;
	//파일경로 , 그룹, 키, 데이터
	map<string, map<string, map<string, string>>> mDatas; 

public:
	bool LoadFile();
	void SaveFile();

	void LoadIniFile(string filePath, string tag);

	inline string GetData(string tag, string group, string key)
	{
		auto fit = mDatas.find(tag);
		if (fit != mDatas.end())
		{
			auto git = fit->second.find(group);
			if (git != fit->second.end())
			{
				auto kit = git->second.find(key);
				if (kit != git->second.end())
				{
					return kit->second;
				}
			}
		}
		return "";
	}

	inline map<string, map<string, string>> GetData(string tag)
	{
		auto fit = mDatas.find(tag);
		if (fit != mDatas.end())
		{
			return fit->second;
		}
		return map<string, map<string, string>>();
	}
};

