#include"Entity.h"
#include"Player.h"
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
GameField::GameField(std::shared_ptr<Player> player, std::shared_ptr<Entity> enermy) {
	Init(player, enermy);
};
inline void GameField::Init(std::shared_ptr<Player> player, std::shared_ptr<Entity> enemy) {
	this->m_gameBoard = std::make_shared<GameBoard>();
	this->m_phase = Phase::BASE_PHASE;
	this->m_standbyTime = 0;
	this->m_player = player;
	this->m_enemy = enemy;
	this->m_currentTurn = PLAYER_TURN;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("currentTurn.tga");
	m_currentTurnPoint = std::make_shared<Sprite2D>(model,shader, texture);
	m_currentTurnPoint->Set2DPosition(player->Get2DPosition().x, player->Get2DPosition().y-100);
	m_currentTurnPoint->SetSize(100, 100);
	this->m_PStatusBar = std::make_shared<StatusBar>(player->GetMaxHp(), player->GetMaxMana(), true);
	this->m_EStatusBar = std::make_shared<StatusBar>(enemy->GetMaxHp(), enemy->GetMaxMana(), false);
	while (!m_turn.empty()) m_turn.pop();
	m_turn.push(PLAYER_TURN);	
};

inline void GameField::BotMove() {
	auto moveList = m_gameBoard->GetAvailableMoveList();
	auto move = moveList[moveList.size()-1];
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
		m_standbyTime += deltaTime;
	if (m_standbyTime > 1) {
			if (m_currentTurn == PLAYER_TURN)
				m_player->TakeDamageOfPoison();
			else
				m_enemy->TakeDamageOfPoison();
			m_standbyTime = 0;
			SetPhase(Phase::BASE_PHASE);
	}
	//else if (m_standbyTime > 2) {
	//	m_standbyTime = 0;
	//	  }
	break;
	}
	case Phase::BASE_PHASE:
	{

		if (m_currentTurn == ENEMY_TURN) {
			m_standbyTime += deltaTime;
			if (m_standbyTime > 1.7f) {
				BotMove();
				//m_enemy->SetAttackNum(250);
				//m_enemy->SetIsAttack(true);
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
			SetPhase(Phase::DESTROY_PHASE);
		}
		break;
	}
	case Phase::DESTROY_PHASE:
	{
		m_click.clear();
		auto matchList = m_gameBoard->GetPieceIndexMatchedList();
		m_gameBoard->m_selected_piece->Set2DPosition(-200, -200);
		m_gameBoard->m_selected_piece2->Set2DPosition(-200, -200);
		//Calculate Damage;
		m_pieceList = m_gameBoard->GetPieceTypeMatchedList(matchList);
		Calculate(m_pieceList, m_currentTurn);
		//for (auto x : pieceList) {
		//	std::cout << x << " ";
		//}
		//std::cout << std::endl;
		//std::cout << "PLayer: " << m_player->GetCurrentHp() << " / "<<m_player->GetMaxHp()<<std::endl;
		//std::cout << "PLayer: " << m_player->GetCurrentMana() << " / " << m_player->GetMaxMana()<<std::endl;

		//std::cout << "Enemy: " << m_enemy->GetCurrentHp() << " / " << m_enemy->GetMaxHp() << std::endl;
		//std::cout << "Enemy: " << m_enemy->GetCurrentMana() << " / " << m_enemy->GetMaxMana() << std::endl;
		m_gameBoard->DestroyPieces(matchList);
		m_gameBoard->RefillGameBoard();//this function will set refilling=true;
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
		m_standbyTime += deltaTime;
		if (m_gameBoard->IsRefilling() ) {
			m_gameBoard->RefillPositionGameBoard(deltaTime);
		}else{
			if ( true) {
				auto matchList = m_gameBoard->GetPieceIndexMatchedList();
				if (matchList.empty()) {
					SetPhase(Phase::BEGIN_PHASE);
					if (!m_gameBoard->HasAnAvailableMove()) {
						m_gameBoard->Init();
					}
					m_currentTurn = !m_currentTurn;
				}
				else {
					SetPhase(Phase::DESTROY_PHASE);
				}
				m_standbyTime = 0;
			}
				}

		
		break;
	}
}

	if (m_currentTurn) m_currentTurnPoint->Set2DPosition(m_player->Get2DPosition().x, m_player->Get2DPosition().y-100);
	else m_currentTurnPoint->Set2DPosition(m_enemy->Get2DPosition().x,m_enemy->Get2DPosition().y-100);

	//m_gameBoard->Update(deltaTime);
	m_PStatusBar->Update(deltaTime,m_player);
	m_EStatusBar->Update(deltaTime, m_enemy);
	m_player->Attack(m_enemy, deltaTime);
	m_enemy->Attack(m_player, deltaTime);
	m_player->Update(deltaTime);
	m_enemy->Update(deltaTime);

}
void GameField::Draw() {
	m_gameBoard->Draw();
	m_enemy->Draw();
	m_player->Draw();
	m_PStatusBar->Draw();
	m_EStatusBar->Draw();
	m_currentTurnPoint->Draw();
}

void GameField::SetPhase(Phase phase) {
	m_phase = phase;
	std::cout << "Phase: " << static_cast<int>(phase)<<std::endl;
}
GameField::Phase GameField::getPhase() {
	return m_phase;
}
void GameField::HandleClick(float _x, float _y) {
	if(m_currentTurn==PLAYER_TURN){

		//std::cout << _x << " va " << _y<<std::endl;
		if (m_phase == Phase::BASE_PHASE)
			if (GB_posX <= _x && _x <= GB_posX + GB_width
				&& GB_posY <= _y && _y <= GB_posY + GB_height) {
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

void GameField::Calculate(std::vector<int> pieceList,bool isPlayer) {
		/*HP 0,
		Mana 1,
		Poison 2,
		Shield 3 ,
		Spell 4,
		Sword 5 ,*/
	if (isPlayer) {
		int hp = pieceList[static_cast<int>(PieceType::HP)];
		m_player->Heal(hp);
		int mana= pieceList[static_cast<int>(PieceType::Mana)];
		m_player->GainMana(mana);
		int poison= pieceList[static_cast<int>(PieceType::Poison)];
		m_enemy->Poisoned(poison);
		int shield= 10*pieceList[static_cast<int>(PieceType::Shield)];
		m_player->SetDefense(shield+m_player->GetDefense());
		int spell= pieceList[static_cast<int>(PieceType::Spell)];
		spell = (m_enemy->GetCurrentMana() < spell ? m_enemy->GetCurrentMana() : spell);
		m_player->GainMana(spell);
		m_enemy->LostMana(spell);

	}
	else {
		int hp = pieceList[static_cast<int>(PieceType::HP)];
		m_enemy->Heal(hp);
		int mana = pieceList[static_cast<int>(PieceType::Mana)];
		m_enemy->GainMana(mana);
		int poison = pieceList[static_cast<int>(PieceType::Poison)];
		m_player->Poisoned(poison);
		int shield = 10*pieceList[static_cast<int>(PieceType::Shield)];
		m_enemy->SetDefense(shield + m_enemy->GetDefense());
		int spell = pieceList[static_cast<int>(PieceType::Spell)];
		m_enemy->GainMana(spell);
		m_player->LostMana(spell);
	}
}