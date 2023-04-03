#include"Entity.h"
#include"Player.h"
#include"GameBoard.h"
#include"GameField.h"
#include"Entity.h"
#include<queue>

#define  PLAYER_TURN  true
#define  ENEMY_TURN false
GameField::GameField() {};
GameField::~GameField() {};
GameField::GameField(std::shared_ptr<Player> player, std::shared_ptr<Entity> enermy) {
	Init(player, enermy);
};
void GameField::Init(std::shared_ptr<Player> player, std::shared_ptr<Entity> enermy) {
	this->m_gameBoard = std::make_shared<GameBoard>();
	this->m_phase = Phase::BASE_PHASE;
	this->m_standbyTime = 0;
	this->m_player = player;
	this->m_enermy = enermy;
	this->m_currentTurn = PLAYER_TURN;
	while (!m_turn.empty()) m_turn.pop();
	m_turn.push(PLAYER_TURN);	
};

void GameField::Update(float deltaTime) {
	switch (m_phase) {
	case Phase::BASE_PHASE:
	{
		if (m_currentTurn == ENEMY_TURN) {
			auto moveList = m_gameBoard->GetAvailableMoveList();
			auto move = moveList[0];
			m_gameBoard->SwapTwoSelectedPiece(move[0],move[1],move[2],move[3]);
			std::pair<int, int> firstClick = { move[0],move[1] };
			m_click.push_back(firstClick);
			m_gameBoard->m_selected_piece->Set2DPosition(225 + 50 * move[1], 225 + 50 *move[0]);
			std::pair<int, int> secondClick = { move[2],move[3] };
			m_gameBoard->m_selected_piece2->Set2DPosition(225 + 50 * move[3], 225 + 50 * move[2]);

			m_click.push_back(secondClick);
			SetPhase(Phase::SWAP_PHASE);
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
		auto matchList = m_gameBoard->GetMatchList();
		std::cout << "M: " << matchList.size();
		m_gameBoard->m_selected_piece->Set2DPosition(-200,-200);
		m_gameBoard->m_selected_piece2->Set2DPosition(-200,-200);
		//Calculate Damage;
		m_gameBoard->DestroyPieces(matchList);
		m_gameBoard->RefillGameBoard();//this function will set refilling=true;
		SetPhase(Phase::REFILL_PHASE);
		break;
	}
	case Phase::REFILL_PHASE:
	{
		if (m_gameBoard->IsRefilling()) {
			m_gameBoard->RefillPositionGameBoard(deltaTime);
		}
		m_standbyTime += deltaTime;
		if (m_standbyTime > 2 && !m_gameBoard->IsRefilling()) {
			auto matchList = m_gameBoard->GetMatchList();
			if (matchList.empty()) {
				SetPhase(Phase::BASE_PHASE);
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
		break;
	}
	}

	//m_gameBoard->Update(deltaTime);
	m_player->Update(deltaTime);
	m_enermy->Update(deltaTime);
}
void GameField::Draw() {
	m_gameBoard->Draw();
	m_player->Draw();
	m_enermy->Draw();
}

void GameField::SetPhase(Phase phase) {
	m_phase = phase;
}
GameField::Phase GameField::getPhase() {
	return m_phase;
}
void GameField::HandleClick(float _x, float _y) {
	if(m_currentTurn=PLAYER_TURN){
		float posX = m_gameBoard->Get2DPosition().x;
		float posY = m_gameBoard->Get2DPosition().y;
		//std::cout << _x << " va " << _y<<std::endl;
		if (m_phase == Phase::BASE_PHASE)
			if (posX <= _x && _x <= posX + 400
				&& posY <= _y && _y <= posY + 400) {
				int curRow = (int)(_y - posY) / 50;
				int curCol = (int)(_x - posX) / 50;
				if (m_click.size() == 1) {
					int lastRow = m_click[0].first;
					int lastCol = m_click[0].second;
					if (abs(lastRow - curRow) + abs(curCol - lastCol) == 1) {
						m_click.push_back({ curRow, curCol });
						m_gameBoard->m_selected_piece->Set2DPosition(-200,-226);

						if (m_gameBoard->CanSwapTwoPiece(lastRow, lastCol, curRow, curCol)) {
							m_gameBoard->SwapTwoSelectedPiece(lastRow, lastCol, curRow, curCol);
							SetPhase(Phase::SWAP_PHASE);
						}
						else {
							m_gameBoard->m_selected_piece->Set2DPosition(-200, -226);
							m_click.clear();
						}
					}
					else {
						m_gameBoard->m_selected_piece->Set2DPosition(-200, -226);
						m_click.clear();
					}
				}
				else if (m_click.empty()) {
					m_click.push_back({ curRow,curCol });
					m_gameBoard->m_selected_piece->Set2DPosition(curCol * 50 + 226, curRow * 50 + 226);
				//std::cout << m_gameBoard->m_selected_piece->Get2DPosition().x << " va " << m_gameBoard->m_selected_piece->Get2DPosition().y << std::endl;
				}
			}
	}
}
