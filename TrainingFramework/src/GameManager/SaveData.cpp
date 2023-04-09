#include "SaveData.h"
#include <iostream>

SaveData::SaveData()
{
	m_DataPath = "..\\Data\\SaveGame\\";
}

SaveData::~SaveData()
{

}

bool SaveData::IsNewGame()
{
	if (std::filesystem::is_empty(m_DataPath))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void SaveData::ClearDataFolder()
{
	for (auto& entry : std::filesystem::directory_iterator(m_DataPath))
		std::filesystem::remove_all(entry.path());
	
	std::cout << "Clear Data!" << std::endl;
}

void SaveData::SaveLevel(int numPassedlevel)
{
	FILE* fp = NULL;
	std::string filePath = m_DataPath + "Level.txt";
	fp = fopen(filePath.c_str(), "w");

	if (fp != NULL)
	{
		fprintf(fp, "%s %d", "LevelPassed:", numPassedlevel);
		fclose(fp);
	}
	
	
}

int SaveData::LoadLevel()
{
	FILE* fp = NULL;
	std::string filePath = m_DataPath + "Level.txt";
	fp = fopen(filePath.c_str(), "r");
	int numPassedLevel = 0;
	char sTmp[100];
	if (fp == NULL)
		return -1;
	else
	{
		fscanf(fp, "%s %d", sTmp, &numPassedLevel);
		fclose(fp);
		std::printf("%d\n", numPassedLevel);
	}
	return numPassedLevel;
}