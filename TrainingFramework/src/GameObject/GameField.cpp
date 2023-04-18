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
GameField::GameField(std::shared_ptr<Entity> player, std::shared_ptr<Entity> enemy) {
	Init(player, enemy);
};
inline void GameField::Init(std::shared_ptr<Entity> player, std::shared_ptr<Entity> enemy) {
	m_gameBoard = std::make_shared<GameBoard>();
	m_phase = Phase::BASE_PHASE;
	m_standbyTime = 0;
	//std::shared_ptr<Entity> p = std::make_shared<Entity>(*player);
	m_player = player;
	m_player->SetIsAlive(true);
	m_player->SetAttackNum(0);
	m_player->SetBurned(false);
	m_player->SetPoisoned(0);
	m_player->SetFreezed(0);
	m_player->SetDefense(0);
	m_player->SetHp(m_player->GetMaxHp());
	m_player->SetMana(0);

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture(enemy->GetName()+"_idle.tga");
	m_enemy = std::make_shared<Entity>(model, shader, texture, 6, 1, 0, 0.1f,enemy->GetName(), enemy->GetMaxHp(), enemy->GetMaxMana(), enemy->GetAttack(), enemy->GetDefense());
	m_player->SetOpponent(m_enemy);
	m_enemy->SetOpponent(m_player);
	//m_enemy->SetElement(enemy->GetElement());
	//std::cout << "Ele: " << m_enemy->GetElement();
	m_player->Set2DPosition(GF_posXOfPlayer, GF_posYOfPlayer);
	m_player->SetSize(GF_playerWidth, GF_playerHeight);

	m_enemy->Set2DPosition(Globals::screenWidth - GF_posXOfPlayer, GF_posYOfPlayer);
	m_enemy->SetSize(-GF_playerWidth, GF_playerHeight);
	 shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	 texture = ResourceManagers::GetInstance()->GetTexture("turnPoint.tga");
	m_currentTurn = PLAYER_TURN;
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
	auto skillList = m_player->GetSkillList();
	skillList[0]->Set2DPosition(20, 240);
	skillList[0]->SetOnClick([player]() {
		if (player->GetCurrentMana() >= 50) {
			player->LostMana(50);
			player->UseSkill1();
		//std::cout << "USE 1" << std::endl;
		}
		});
	m_skillButtonList.push_back(skillList[0]);
	//skill2
	skillList[1]->Set2DPosition(20, 300);
	skillList[1]->SetOnClick([player,enemy]() {
		if (player->GetCurrentMana()>= 100) {
			player->LostMana(100);
			player->UseSkill2();
			//std::cout << "USE 2" << std::endl;
		}
		});
	m_skillButtonList.push_back(skillList[1]);
	//skill3
	skillList[2]->Set2DPosition(20, 360);
	std::shared_ptr gb = m_gameBoard;
	skillList[2]->SetOnClick([player,gb,this]() {
		if (player->GetCurrentMana() >= 150) {
			player->LostMana(150);
			player->UseSkill3(gb);
			this->SetPhase(Phase::DESTROY_PHASE);
			//std::cout << "USE 3" << std::endl;
		}
		});
	m_skillButtonList.push_back(skillList[2]);

	//m_infoText = std::make_shared<Text>(shader, font, "", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	m_PStatusBar = std::make_shared<StatusBar>(m_player, true);
	m_EStatusBar = std::make_shared<StatusBar>(m_enemy, false);
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

GameField::Phase GameField::GetPhase() {
	return m_phase;
}
void GameField::Update(float deltaTime) {
	switch (m_phase) {
	case Phase::BEGIN_PHASE:
	{
		if (m_currentTurn == PLAYER_TURN) {
			m_player->TakeDamageOfEffect();
			if (m_player->IsFreezed()) {
				m_currentTurn == ENEMY_TURN;
				SetPhase(Phase::BEGIN_PHASE);
				break;
			}
		}
		else {
			m_enemy->TakeDamageOfEffect();
			if (m_enemy->IsFreezed()) {
				m_currentTurn = PLAYER_TURN;
				SetPhase(Phase::BEGIN_PHASE);
				break;
			}
		}
		SetPhase(Phase::BASE_PHASE);
		break;
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
			if (m_currentTurn == PLAYER_TURN && !m_player->IsMuted()) {
				 m_player->SetAttackNum(m_pieceList[static_cast<int>(PieceType::Sword)]);
				 m_player->SetIsAttack(true);
			}
			else if(m_currentTurn == ENEMY_TURN && !m_enemy->IsMuted()) {
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
		if (m_player->IsAlive())
		{
		
		}
		else
			
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
	m_player->GetEffect()->Update(deltaTime);
	m_player->GetContinousEffect()->Update(deltaTime);

	m_enemy->Update(deltaTime);
	m_enemy->GetEffect()->Update(deltaTime);
	m_enemy->GetContinousEffect()->Update(deltaTime);
	m_PStatusBar->Update(deltaTime);

	m_EStatusBar->Update(deltaTime);
}
void GameField::Draw() {
	m_gameBoard->Draw();
	if (m_currentTurn == PLAYER_TURN)
	{
	m_enemy->Draw();
	m_player->Draw();
	}
	else {
		m_player->Draw();
		m_enemy->Draw();	
	}
	if (m_enemy->IsFreezed()) {
		m_enemy->GetContinousEffect()->Draw();	
	}
	if (m_player->IsFreezed()) {
		m_player->GetContinousEffect()->Draw();
	}
	if (m_enemy->GetEffect() != nullptr) {
		m_enemy->GetEffect()->Draw();
	}
	if (m_player->GetEffect() != nullptr) {
		m_player->GetEffect()->Draw();
	}
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
}

void GameField::HandleClick(float _x, float _y,bool isPressed) {
	if(m_currentTurn==PLAYER_TURN){

		if (m_phase == Phase::BASE_PHASE && m_player->IsAlive())
			for (auto btnSkill : m_skillButtonList) {
				if (btnSkill->HandleTouchEvents(_x, _y, isPressed)) {

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
	for (int i = 0; i < 3;i++) {
		auto it = m_skillButtonList[i];
		if ((it->Get2DPosition().x - it->GetScale().x / 2.0f <= x) && (x <= it->Get2DPosition().x + it->GetScale().x / 2.0f)
			&& (it->Get2DPosition().y - it->GetScale().y / 2.0f <= y) && (y <= it->Get2DPosition().y + it->GetScale().y / 2.0f))
		{
			// The button is being pressed down
			m_info->SetSize(200, 100);
			m_info->Set2DPosition(it->Get2DPosition().x + 100, it->Get2DPosition().y - 50);
			int x = it->Get2DPosition().x + 10;
			int y = it->Get2DPosition().y - 80;
			auto detail = m_player->GetDetailOfSkill(i);
			for (int j = 0; j < detail.size();j++) {
					detail[j]->Set2DPosition(x, y+10*j);
					m_infoText.push_back(detail[j]);

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