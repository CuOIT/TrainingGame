#pragma once
#include "GameManager/Singleton.h"
#include <string>
#include <filesystem>
#include "Player.h"

class SaveData : public CSingleton<SaveData>
{
public:
	SaveData();
	~SaveData();

	void ClearDataFolder();
	void Init(std::string &fileName);

	void SaveLevel(int numPassedlevel);
	int LoadLevel();

	void SavePlayer(std::shared_ptr<Player> player);
	std::shared_ptr<Player> LoadPlayer();

	bool IsNewGame();
	void SetIsNewGame(bool isNewGame) { m_isNewGame = isNewGame; };
	bool GetIsNewGame() { return m_isNewGame; };
	
private:
	std::string m_DataPath;
	bool m_isNewGame;
};
