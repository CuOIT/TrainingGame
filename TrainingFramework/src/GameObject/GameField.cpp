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
	this->m_player = player;
	this->m_enermy = enermy;
	while (!m_turn.empty()) m_turn.pop();
	m_turn.push(PLAYER_TURN);	
};

void GameField::Update(float deltaTime) {
	m_gameBoard->Update(deltaTime);
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
void GameField::handleClick(float _x, float _y) {
	if(m_currentTurn=PLAYER_TURN){
		float posX = m_gameBoard->Get2DPosition().x;
		float posY = m_gameBoard->Get2DPosition().y;
		//std::cout << _x << " va " << _y<<std::endl;
		if (m_phase == Phase::BASE_PHASE)
			if (posX <= _x && _x <= posX + 400
				&& posY <= _y && _y <= posY + 400) {
				int curRow = (int)(_y - posY) / 50;
				int curCol = (int)(_x - posX) / 50;
				//std::cout << curRow << " va " << curCol <<" co " <<static_cast<int>(m_board[curRow][curCol]->GetType()) << std::endl;
				if (m_click.size() == 1) {
					int lastRow = m_click[0].first;
					int lastCol = m_click[0].second;
					if (abs(lastRow - curRow) + abs(curCol - lastCol) == 1) {
						m_click.push_back({ curRow, curCol });
						if (m_gameBoard->CanSwapTwoPiece(lastRow, lastCol, curRow, curCol)) {
							m_gameBoard->SwapTwoSelectedPiece(lastRow, lastCol, curRow, curCol);
							SetPhase(Phase::SWAP_PHASE);
						}
					}
					else {
						m_click.clear();
					}
				}
				else if (m_click.empty()) {
					m_click.push_back({ curRow,curCol });
					m_gameBoard->m_selected_piece->Set2DPosition(curCol * 50 + 226, curRow * 50 + 226);
				}
			}
	}
}
