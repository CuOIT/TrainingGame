#include "SaveData.h"
#include <iostream>

SaveData::SaveData()
{
	m_DataPath = "..\\Data\\SaveGame\\";

}

SaveData::~SaveData()
{

}

void SaveData::ClearDataFolder()
{
	for (auto& entry : std::filesystem::directory_iterator(m_DataPath))
		std::filesystem::remove_all(entry.path());
	
	std::cout << "Clear Data!" << std::endl;
}

bool SaveData::IsNewGame()
{
	if(std::filesystem::is_empty(m_DataPath))
	{
		return true;
	}
	else
	{
	return false;
	}
}

void SaveData::Init(std::string& fileName)
{
	FILE* fp = NULL;
	std::string filePath = m_DataPath + fileName;
	fp = fopen(filePath.c_str(), "w+");

	if (fileName == "Level.txt")
	{
		fprintf(fp, "%s %d", "LevelPassed:", 0);
		std::printf("%s\n", "Init level!");
	}
	else if (fileName == "Player.txt")
	{
		fprintf(fp, "%s\n", "warrior1/200/200/5/0");
		fprintf(fp, "%s\n", "warrior2/200/200/5/0");
		fprintf(fp, "%s\n", "warrior3/200/200/5/0");
		std::printf("%s\n", "Init Player!");
	}
	fclose(fp);
}

void SaveData::SaveLevel(int numPassedlevel)
{
	FILE* fp = NULL;
	std::string filePath = m_DataPath + "Level.txt";
	fp = fopen(filePath.c_str(), "w+");

	if (fp != NULL)
	{
		if (this->LoadLevel() < numPassedlevel + 1)
		{
			fprintf(fp, "%s %d", "LevelPassed:", numPassedlevel);
		}
		fclose(fp);
		std::printf("%s\n", "Save Level!");
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
		this->Init(std::string("Level.txt"));
	else
	{
		int success = fscanf(fp, "%s %d", sTmp, &numPassedLevel);
		fclose(fp);
		std::printf("%s %d\n", "LevelPassed:", numPassedLevel);
	}
	return numPassedLevel;
}

void SaveData::SavePlayer(std::shared_ptr<Player> player)
{
	FILE* fp = NULL;
	std::string filePath = m_DataPath + "Player.txt";
	fp = fopen(filePath.c_str(), "w");

	if (fp != NULL)
	{
		fprintf(fp, "%s %s\n", "Name:", player->GetName().c_str());
		fprintf(fp, "%s %d\n", "MaxHP:", player->GetMaxHp());
		fprintf(fp, "%s %d\n", "MaxMP:", player->GetMaxMana());
		fprintf(fp, "%s %d\n", "Attack:", player->GetAttack());
		fprintf(fp, "%s %d\n", "Defense:", player->GetDefense());

		fclose(fp);
		std::printf("%s\n", "Save Player!");
	}
}

std::vector<std::shared_ptr<Player>> SaveData::LoadPlayer()
{
	FILE* fp = NULL;
	std::string filePath = m_DataPath + "Player.txt";
	fp = fopen(filePath.c_str(), "r");

	char name[20] = { 0 };
	int maxHP = 0;
	int maxMP = 0;
	int attack = 0;
	int defense = 0;
	int success = 0;

	std::vector<std::shared_ptr<Player>> listPlayer;

	if (fp == NULL)
		this->Init(std::string("Player.txt"));
	else
	{
		for (int i = 0; i < 3; i++)
		{
			success = fscanf(fp, "%[^/]/%d/%d/%d/%d\n", name, &maxHP, &maxMP, &attack, &defense);
			std::shared_ptr<Player> player = std::make_shared<Player>(name, maxHP, maxMP, attack, defense);
			listPlayer.push_back(player);
		} 
		
		fclose(fp);
	}
	
	return listPlayer;
}

std::shared_ptr<Entity> SaveData::LoadEnemy()
{
	FILE* fp = NULL;
	std::string filePath = "..\\Data\\Enemy.txt";
	fp = fopen(filePath.c_str(), "r");

	char name[20] = { 0 };
	int maxHP = 0;
	int maxMP = 0;
	int attack = 0;
	int defense = 0;
	int index = 0;

	if (fp != NULL)
	{
		int level = this->LoadLevel();
		do
		{
			int success = fscanf(fp, "%*d/%[^/]/%d/%d/%d/%d", name, &maxHP, &maxMP, &attack, &defense);
			index++;
		} while (index == level);
		fclose(fp);
	}
	std::shared_ptr<Entity> enemy = std::make_shared<Entity>();
	enemy->SetName(name);
	enemy->SetMaxHp(maxHP);
	enemy->SetMaxMana(maxMP);
	enemy->SetAttack(attack);
	enemy->SetDefense(defense);

	return enemy;
}

	