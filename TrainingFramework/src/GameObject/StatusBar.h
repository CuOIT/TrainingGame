#pragma once
#include"Sprite2D.h"
#include"Entity.h"
#include"Font.h"
#include"Text.h"
#include"SpriteAnimation.h"
class StatusBar {
	//#define w
public:
	StatusBar(int maxHp, int maxMana, bool isPlayer);
	~StatusBar();

	void SetHp(int hp);
	void SetMana(int mana);
	void SetShiled(int shield);
	void SetPoison(int poison);

	void Update(float deltaTime, std::shared_ptr<Entity> entity);
	void Draw();
private:
	std::shared_ptr<Sprite2D> m_avatar;
	std::shared_ptr<Sprite2D> m_statusBarBG;
	std::shared_ptr<Sprite2D> m_hpBar;
	std::shared_ptr<Sprite2D> m_manaBar;

	std::shared_ptr<Sprite2D> m_poisonStt;
	std::shared_ptr<Sprite2D> m_shieldStt;
	std::shared_ptr<Text> m_shieldText;
	std::shared_ptr<Text> m_poisonText;

	std::shared_ptr<Sprite2D> m_freezedStt;
	std::shared_ptr<Sprite2D> m_burnedStt;
	std::shared_ptr<Text> m_freezedText;
	std::shared_ptr<Text> m_burnedText;

	std::shared_ptr<Sprite2D> m_mutedStt;
	std::shared_ptr<Text> m_mutedText;
	bool m_isPlayer;
	int m_maxHp;
	int m_maxMana;
	int m_hp;
	int m_mana;
	int m_poison;
	int m_shield;

};