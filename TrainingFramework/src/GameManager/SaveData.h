#pragma once
#include "GameManager/Singleton.h"
#include <string>
#include <filesystem>

class SaveData : public CSingleton<SaveData>
{
public:
	SaveData();
	~SaveData();

	bool IsNewGame();
	void ClearDataFolder();

	void SaveLevel(int numPassedlevel);
	int LoadLevel();
	
private:
	std::string m_DataPath;
};
