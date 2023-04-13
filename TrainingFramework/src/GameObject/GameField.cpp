#include"Entity.h"
#include"Player.h"
#include "Level.h"
#include"GameBoard.h"
#include"GameField.h"
#include"Entity.h"	
#include"StatusBar.h"
#include<queue>
#include "ResourceManagers.h"

#define  PLAYER_TURN  true
#define  ENEMY_TURN false
//GameField::GameField() {};
GameField::~GameField() {};
GameField::GameField(std::shared_ptr<Player> player, std::shared_ptr<Entity> enemy) {
	Init(player, enemy);
};
inline void GameField::Init(std::shared_ptr<Player> player, std::shared_ptr<Entity> enemy) {
	m_gameBoard = std::make_shared<GameBoard>();
	m_phase = Phase::BASE_PHASE;
	m_standbyTime = 0;
	m_player = player;
	m_enemy = enemy;
	m_player->SetOpponent(enemy);
	m_enemy->SetOpponent(player);
	m_currentTurn = PLAYER_TURN;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("turnPoint.tga");
	m_turnPoint = std::make_shared<Sprite2D>(model, shader, texture);
	m_turnPoint->Set2DPosition(m_player->Get2DPosition().x, m_player->Get2DPosition().y-130);
	m_turnPoint->SetSize(75, 75);

	//Skill

	texture= ResourceManagers::GetInstance()->GetTexture("board_menu.tga");
	m_boardMenu = std::make_shared<Sprite2D>(model, shader, texture);
	m_boardMenu->Set2DPosition(-80, 300);
	m_boardMenu->SetSize(300, 250);

	texture = ResourceManagers::GetInstance()->GetTexture("bg_info.tga");
	m_info= std::make_shared<Sprite2D>(model, shader, texture);

	//m_skillButtonList.push_back(boardMenu);
	//skill1
	texture = ResourceManagers::GetInstance()->GetTexture("skill11.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->SetName("skill1");
	button->Set2DPosition(20, 240);
	button->SetSize(50, 50);
	button->SetOnClick([player]() {
		if (player->GetCurrentMana() >= 5) {

		player->LostMana(5);
		player->Heal(player->GetCurrentHp() / 2);
		std::cout << "USE 1" << std::endl;
		}
		});
	m_skillButtonList.push_back(button);
	//skill2
	texture = ResourceManagers::GetInstance()->GetTexture("skill12.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->SetName("skill2");
	button->Set2DPosition(20, 300);
	button->SetSize(50, 50);
	button->SetOnClick([player,enemy]() {
		if (player->GetCurrentMana()>= 10) {
			player->LostMana(10);
			int hp = enemy->GetCurrentHp();
			enemy->SetHp(hp / 2);
			player->Heal(hp / 2);
			std::cout << "USE 2" << std::endl;
		}
		std::cout << player->GetCurrentMana();
		});
	m_skillButtonList.push_back(button);
	//skill3
	texture = ResourceManagers::GetInstance()->GetTexture("skill13.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->SetName("skill3");
	button->Set2DPosition(20, 360);
	button->SetSize(50, 50);
	std::shared_ptr gb = m_gameBoard;
	button->SetOnClick([player,gb,this]() {
		if (player->GetCurrentMana() >= 15) {
			player->LostMana(15);
			std::set < std::pair<int, int>> destroyList;
			destroyList = gb->GetPieceIndexType(5);//SWORD
			gb->SetDestroyList(destroyList);
			this->SetPhase(Phase::DESTROY_PHASE);
			std::cout << "USE 3" << std::endl;
		}
		});
	m_skillButtonList.push_back(button);

	//m_infoText = std::make_shared<Text>(shader, font, "", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);

	m_PStatusBar = std::make_shared<StatusBar>(player->GetMaxHp(), player->GetMaxMana(), true);
	m_EStatusBar = std::make_shared<StatusBar>(enemy->GetMaxHp(), enemy->GetMaxMana(), false);
	while (!m_turn.empty()) m_turn.pop();
	m_turn.push(PLAYER_TURN);	
};

inline void GameField::BotMove() {
	auto moveList = m_gameBoard->GetAvailableMoveList();
	auto move = moveList[0];
	m_gameBoard->SwapTwoSelectedPiece(move[0], move[1], move[2], move[3]);
	std::pair<int, int> firstClick = { move[0],move[1] };
	m_click.push_back(firstClick);
	m_gameBoard->m_selected_piece->Set2DPosition(GB_posX +Pi_size/2+ Pi_size * move[1], GB_posY + Pi_size / 2 + Pi_size * move[0]);
	std::pair<int, int> secondClick = { move[2],move[3] };
	m_gameBoard->m_selected_piece2->Set2DPosition(GB_posX + Pi_size / 2 + Pi_size * move[3], GB_posY + Pi_size / 2 + Pi_size * move[2]);

	m_click.push_back(secondClick);
}
void GameField::Update(float deltaTime) {
	switch (m_phase) {
	case Phase::BEGIN_PHASE:
	{
		if (m_currentTurn == PLAYER_TURN)
			m_player->TakeDamageOfPoison();
		else
			m_enemy->TakeDamageOfPoison();
		SetPhase(Phase::BASE_PHASE);
	}
	case Phase::BASE_PHASE:
	{

		if (m_currentTurn == ENEMY_TURN) {
			m_standbyTime += deltaTime;
			if (m_standbyTime > 1.7f) {
				if(m_enemy->IsAlive())
				BotMove();
				SetPhase(Phase::SWAP_PHASE);
				m_standbyTime = 0;
			}
		}
		break;
	}
	case Phase::SWAP_PHASE:
	{

		int lastRow = m_click[0].first;
		int lastCol = m_click[0].second;
		int curRow = m_click[1].first;
		int curCol = m_click[1].second;
		if (m_gameBoard->IsSwapping()) {
			m_gameBoard->ChangePositionOfTwoPiece(lastRow, lastCol, curRow, curCol, deltaTime);
		}
		else {
			auto matchList = m_gameBoard->GetPieceIndexMatchedList();
			m_gameBoard->SetDestroyList(matchList);
			SetPhase(Phase::DESTROY_PHASE);
		}
		break;
	}
	case Phase::DESTROY_PHASE:
	{
		m_click.clear();
		auto destroyList = m_gameBoard->GetDestroyList();
		m_gameBoard->m_selected_piece->Set2DPosition(-200, -200);
		m_gameBoard->m_selected_piece2->Set2DPosition(-200, -200);
		m_pieceList = m_gameBoard->GetPieceTypeMatchedList(destroyList);
		Calculate(m_pieceList, m_currentTurn);
		m_gameBoard->DestroyPieces(destroyList);
		m_gameBoard->RefillGameBoard();
		if (m_pieceList[static_cast<int>(PieceType::Sword)] > 0) {
			if (m_currentTurn == PLAYER_TURN) {
				 m_player->SetAttackNum(m_pieceList[static_cast<int>(PieceType::Sword)]);
				 m_player->SetIsAttack(true);
			}
			else {
				m_enemy->SetAttackNum(m_pieceList[static_cast<int>(PieceType::Sword)]);
				m_enemy->SetIsAttack(true);
			}
		}
		SetPhase(Phase::REFILL_PHASE);
		break;
	}
	case Phase::REFILL_PHASE:
	{
		if (m_gameBoard->IsRefilling()) {
			m_gameBoard->RefillPositionGameBoard(deltaTime);
		}else{
			if ( true) {
				auto matchList = m_gameBoard->GetPieceIndexMatchedList();
				if (!matchList.empty()) {
					auto matchList = m_gameBoard->GetPieceIndexMatchedList();
					m_gameBoard->SetDestroyList(matchList);
					SetPhase(Phase::DESTROY_PHASE);
				}
				else {
					if (m_player->GetAttackNum() == 0 && m_enemy->GetAttackNum() == 0) {

					SetPhase(Phase::BEGIN_PHASE);
					if (!m_gameBoard->HasAnAvailableMove()) {
						m_gameBoard->Init();
					}
					m_currentTurn = !m_currentTurn;
					}
				}
				m_standbyTime = 0;
			}
				}
		break;
	}
	case Phase::END_PHASE:
	{
		if (!m_enemy->IsAlive())
		{
			Level::GetInstance()->SetNumPassedLevel(Level::GetInstance()->GetNumPassedLevel() + 1);
			Level::GetInstance()->SetIsPlayerWin(true);
		}
		else
			Level::GetInstance()->SetIsPlayerWin(false);
		Level::GetInstance()->SetIsEndGame(true);
		break;
	}
}


	if (m_currentTurn == PLAYER_TURN) {
		m_turnPoint->Set2DPosition(m_player->Get2DPosition().x, m_player->Get2DPosition().y - 100);
	}
	else {
		m_turnPoint->Set2DPosition(m_enemy->Get2DPosition().x, m_enemy->Get2DPosition().y - 100);

	}
	if (!m_player->IsAlive() || !m_enemy->IsAlive()) {
		m_standbyTime += deltaTime;
		if(m_standbyTime>=1.5)
			SetPhase(Phase::END_PHASE);
	}
	m_player->Update(deltaTime);
	m_enemy->Update(deltaTime);
	m_PStatusBar->Update(deltaTime,m_player);

	m_EStatusBar->Update(deltaTime, m_enemy);
}
void GameField::Draw() {
	m_gameBoard->Draw();
	m_enemy->Draw();
	m_player->Draw();

	m_PStatusBar->Draw();
	m_EStatusBar->Draw();
	m_turnPoint->Draw();
	m_boardMenu->Draw();
	for (auto it : m_skillButtonList) {
		it->Draw();
	}
	m_info->Draw();
	for(auto it:m_infoText)
		it->Draw();
}

void GameField::SetPhase(Phase phase) {
	m_phase = phase;
	std::cout << "Phase: " << static_cast<int>(phase)<<std::endl;
}
GameField::Phase GameField::getPhase() {
	return m_phase;
}
void GameField::HandleClick(float _x, float _y,bool isPressed) {
	if(m_currentTurn==PLAYER_TURN){

		//std::cout << _x << " va " << _y<<std::endl;
		if (m_phase == Phase::BASE_PHASE && m_player->IsAlive())
			for (auto btnSkill : m_skillButtonList) {
				if (btnSkill->HandleTouchEvents(_x, _y, isPressed)) {

				std::cout << btnSkill->GetName();
				break;
				}
			}
			if (GB_posX <= _x && _x <= GB_posX + GB_width
				&& GB_posY <= _y && _y <= GB_posY + GB_height && !isPressed) {
				int curRow = (int)(_y - GB_posY) / Pi_size;
				int curCol = (int)(_x - GB_posX) / Pi_size;
				if (m_click.size() == 1) {
					int lastRow = m_click[0].first;
					int lastCol = m_click[0].second;
					if (abs(lastRow - curRow) + abs(curCol - lastCol) == 1) {
						m_click.push_back({ curRow, curCol });

						if (m_gameBoard->CanSwapTwoPiece(lastRow, lastCol, curRow, curCol)) {
							m_gameBoard->m_selected_piece2->Set2DPosition(curCol * Pi_size + Pi_size / 2 + GB_posX, curRow * Pi_size + Pi_size / 2 + GB_posY);
							m_gameBoard->SwapTwoSelectedPiece(lastRow, lastCol, curRow, curCol);
							SetPhase(Phase::SWAP_PHASE);
						}
						else {
							m_gameBoard->m_selected_piece->Set2DPosition(-999, -999);
							m_click.clear();
						}
					}
					else {
						m_gameBoard->m_selected_piece->Set2DPosition(-999, -999);
						m_click.clear();
					}
				}
				else if (m_click.empty()) {
					m_click.push_back({ curRow,curCol });
					m_gameBoard->m_selected_piece->Set2DPosition(curCol * Pi_size+Pi_size/2 + GB_posX, curRow * Pi_size+Pi_size/2 + GB_posY);
				}
			}
	}
}
void GameField::HandleMouseMoveEvents(float x, float y) {
	m_info->SetSize(0, 0);
	m_infoText.clear();
	for (auto it : m_skillButtonList) {
		if ((it->Get2DPosition().x - it->GetScale().x / 2.0f <= x) && (x <= it->Get2DPosition().x + it->GetScale().x / 2.0f)
			&& (it->Get2DPosition().y - it->GetScale().y / 2.0f <= y) && (y <= it->Get2DPosition().y + it->GetScale().y / 2.0f))
		{
			// The button is being pressed down
			m_info->SetSize(200, 100);
			m_info->Set2DPosition(it->Get2DPosition().x + 100, it->Get2DPosition().y - 50);
			int x = it->Get2DPosition().x + 10;
			int y = it->Get2DPosition().y - 80;
			if (it->GetName() == "skill1") {
				auto font = ResourceManagers::GetInstance()->GetFont("Alkatra-VariableFont_wght.ttf");
				auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
				auto text = std::make_shared<Text>(shader, font, "Mana Cost: 50", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
				text->Set2DPosition(x, y);
				m_infoText.push_back(text);
				auto text2 = std::make_shared<Text>(shader, font, "Take Damage 50 for enemy", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
				text2->Set2DPosition(x, y+10);
				m_infoText.push_back(text2);


			}
			else if (it->GetName() == "skill2") {
				auto font = ResourceManagers::GetInstance()->GetFont("Alkatra-VariableFont_wght.ttf");
				auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
				auto text = std::make_shared<Text>(shader, font, "Mana Cost: 100", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
				text->Set2DPosition(x, y);
				m_infoText.push_back(text);
				auto text2 = std::make_shared<Text>(shader, font, "Convert 50% current hp of enemy to yours", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
				text2->Set2DPosition(x, y + 10);
				m_infoText.push_back(text2);
			}
			else if (it->GetName() == "skill3") {
				auto font = ResourceManagers::GetInstance()->GetFont("Alkatra-VariableFont_wght.ttf");
				auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
				auto text = std::make_shared<Text>(shader, font, "Mana Cost: 200", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
				text->Set2DPosition(x, y);
				m_infoText.push_back(text);
				auto text2 = std::make_shared<Text>(shader, font, "Destroy all sword piece on the board", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
				text2->Set2DPosition(x, y + 10);
				m_infoText.push_back(text2);
			}
		}
	}
};

void GameField::Calculate(std::vector<int> pieceList,bool isPlayer) {
		/*HP 0,
		Mana 1,
		Poison 2,
		Shield 3 ,
		Spell 4,
		Sword 5 ,*/
		int hp = 10*pieceList[static_cast<int>(PieceType::HP)];
		int mana= 10*pieceList[static_cast<int>(PieceType::Mana)];
		int poison= 5*pieceList[static_cast<int>(PieceType::Poison)];
		int shield= 10*pieceList[static_cast<int>(PieceType::Shield)];
		int spell= 10*pieceList[static_cast<int>(PieceType::Spell)];
	if (isPlayer) {
		m_player->Heal(hp);
		m_player->GainMana(mana);
		m_enemy->Poisoned(poison);
		m_player->SetDefense(shield+m_player->GetDefense());
		spell = (m_enemy->GetCurrentMana() < spell ? m_enemy->GetCurrentMana() : spell);
		m_player->GainMana(spell);
		m_enemy->LostMana(spell);

	}
	else {
		m_enemy->Heal(hp);
		m_enemy->GainMana(mana);
		m_player->Poisoned(poison);
		m_enemy->SetDefense(shield + m_enemy->GetDefense());
		spell = (m_player->GetCurrentMana() < spell ? m_player->GetCurrentMana() : spell);
		m_enemy->GainMana(spell);
		m_player->LostMana(spell);
	}
}