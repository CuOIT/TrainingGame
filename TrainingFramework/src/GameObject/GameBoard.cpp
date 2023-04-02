#include"GameBoard.h"
#include"Piece.h"
#include"ResourceManagers.h"
#include"Sprite2D.h"
#include<random>
#include <queue>
#include <set>

GameBoard::GameBoard() :Sprite2D(),m_phase(Phase::BASE_PHASE),m_standbyTime(0),m_moveSpeed(300) {
	this->Set2DPosition(200, 200);
	Init();
};

GameBoard::~GameBoard() {}

void GameBoard::Init() {
	do {
		m_board.clear();

		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("frame.tga");
		m_frame = std::make_shared<Sprite2D>(model, shader, texture);
		m_frame->SetSize(450, 450);
		m_frame->Set2DPosition(400, 400);
		texture= ResourceManagers::GetInstance()->GetTexture("board.tga");
		m_background= std::make_shared<Sprite2D>(model, shader, texture);
		m_background->SetSize(420, 420);
		m_background->Set2DPosition(400, 400);
		texture = ResourceManagers::GetInstance()->GetTexture("selected_piece.tga");
		m_selected_piece = std::make_shared<Sprite2D>(model, shader, texture);
		m_selected_piece->SetSize(50, 50);
		srand(time(NULL));
		std::vector<std::shared_ptr<Piece>> line;
		for (int i = 0; i < 8; i++) {
			line.clear();
			for (int j = 0; j < 8; j++) {
				int colCheck;
				if (i <= 1) {
					colCheck = -1;
				}
				else {
					int pre3 = static_cast<int>(m_board[i-1][j]->GetType());
					int pre4 = static_cast<int>(m_board[i-2][j]->GetType());
					colCheck = (pre3 == pre4 ? pre3 : -1);
				}
				int ran = rand() % 6;
				if (j > 1) {
					int pre1 = static_cast<int>(line[j - 1]->GetType());
					int pre2 = static_cast<int>(line[j - 2]->GetType());
					int rowCheck = (pre1 == pre2?pre1:-1);


					while (ran == rowCheck || ran == colCheck) ran = rand() % 6;


				}
				PieceType type = static_cast<PieceType>(ran);
				texture = ResourceManagers::GetInstance()->GetTexture("piece_hp.tga");
				switch (type) {
				case PieceType::HP:
					texture = ResourceManagers::GetInstance()->GetTexture("piece_hp.tga");
					break;
				case PieceType::Mana:
					texture = ResourceManagers::GetInstance()->GetTexture("piece_mana.tga");
					break;
				case PieceType::Poison:
					texture = ResourceManagers::GetInstance()->GetTexture("piece_poison.tga");
					break;
				case PieceType::Shield:
					texture = ResourceManagers::GetInstance()->GetTexture("piece_shield.tga");
					break;
				case PieceType::Spell:
					texture = ResourceManagers::GetInstance()->GetTexture("piece_spell.tga");
					break;
				case PieceType::Sword:
					texture = ResourceManagers::GetInstance()->GetTexture("piece_sword.tga");
					break;
				}
				std::shared_ptr<Piece> p = std::make_shared<Piece>(model, shader, texture, i, j, type);
				p->Set2DPosition(this->Get2DPosition().x + j * 50 + 26,this->Get2DPosition().y + i * 50 + 26);
				p->SetSize(48, 48);
				line.push_back(p);
			}
			m_board.push_back(line);
		}
	} while (!HasAnAvailableMove());

}

void GameBoard::Update(float deltaTime) {

	switch (m_phase) {
		case Phase::BASE_PHASE:
		{
			
			break;
		}
		case Phase::SWAP_PHASE:
		{

			int lastRow = m_click[0].first;
			int lastCol = m_click[0].second;
			int curRow = m_click[1].first;
			int curCol = m_click[1].second;
			if (m_board[lastRow][lastCol]->Get2DPosition().x == 226 +lastCol * 50 && m_board[lastRow][lastCol]->Get2DPosition().y == 226 + lastRow * 50) {
				m_standbyTime += deltaTime;
				if (m_standbyTime >= 0.5f) {
					m_standbyTime = 0;
					SetPhase(Phase::DESTROY_PHASE);
				}
			}
			else {
				int vx = (lastCol - curCol > 0 ? 1 : (lastCol - curCol == 0 ? 0 : -1));
				int vy = (lastRow - curRow > 0 ? 1 : (lastRow - curRow == 0 ? 0 : -1));
				std::cout << "Move speed:" << m_moveSpeed << std::endl;
				m_board[lastRow][lastCol]->Set2DPosition(m_board[lastRow][lastCol]->Get2DPosition().x + vx * (int)(m_moveSpeed * deltaTime), m_board[lastRow][lastCol]->Get2DPosition().y + vy * (int)(m_moveSpeed * deltaTime));
				m_board[curRow][curCol]->Set2DPosition(m_board[curRow][curCol]->Get2DPosition().x - vx * (int)(m_moveSpeed * deltaTime), m_board[curRow][curCol]->Get2DPosition().y - vy * (int)(m_moveSpeed * deltaTime));
				if (abs(m_board[lastRow][lastCol]->Get2DPosition().x - 226 - 50 * lastCol + m_board[lastRow][lastCol]->Get2DPosition().y - 226 - 50 * lastRow) < abs((int)(m_moveSpeed * deltaTime)))
					m_board[lastRow][lastCol]->Set2DPosition(226+50*lastCol,226+50*lastRow);
				if (abs(m_board[curRow][curCol]->Get2DPosition().x - 226 - 50 * curCol + m_board[curRow][curCol]->Get2DPosition().y - 226 - 50 * curRow) < abs((int)(m_moveSpeed * deltaTime)))
					m_board[curRow][curCol]->Set2DPosition(226+50*curCol,226+50*curRow);
				//SetPhase(Phase::DESTROY_PHASE);
			}
			
			
			break;
		}
		case Phase::DESTROY_PHASE: 
		{
			m_click.clear();
			DestroyPieces(this->GetMatchList());
			RefillGameBoard();
			SetPhase(Phase::REFILL_PHASE);
			break;
		}
		case Phase::REFILL_PHASE:
		{
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++) {
					m_board[i][j]->Dropping(m_moveSpeed*deltaTime);
				}
			m_standbyTime +=deltaTime;
			if (m_standbyTime >= 400/m_moveSpeed) {
			auto matchList = this->GetMatchList();
			if (matchList.empty()) {
				SetPhase(Phase::BASE_PHASE);
				if (!HasAnAvailableMove()) {
					Init();
				}
			}
			else {
				SetPhase(Phase::DESTROY_PHASE);
			}
			m_standbyTime = 0;
			}
			break;
		}
	}


}
void GameBoard::Draw() {
	m_background->Draw();
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			if(m_board[i][j]!=nullptr &&m_board[i][j]->Get2DPosition().y>=200)
				m_board[i][j]->Draw();

		}
	m_frame->Draw();
	if (m_click.size() == 1) {
		m_selected_piece->Draw();
	}
}

std::set<std::pair<int,int>> GameBoard::GetMatchList() {
	std::set<std::shared_ptr<Piece>> matchingListOfBoard;
	std::queue<std::shared_ptr<Piece>> matchingListNeighbor;


	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 7; j++) {

			if (matchingListNeighbor.size() == 0 ) {
				matchingListNeighbor.push(m_board[i][j]);
			}
			else if (matchingListNeighbor.front()->GetType() == m_board[i][j]->GetType()) {
				matchingListNeighbor.push(m_board[i][j]);
			}
			else {
				if (matchingListNeighbor.size() >= 3) {

					while (!matchingListNeighbor.empty()) {
						matchingListOfBoard.insert(matchingListNeighbor.front());

						matchingListNeighbor.pop();

					}
				}
				else {
					while (!matchingListNeighbor.empty()) {
						matchingListNeighbor.pop();
					}
				}
				matchingListNeighbor.push(m_board[i][j]);
			}
		}
		if (!matchingListNeighbor.empty())
			if (matchingListNeighbor.front()->GetType() == m_board[i][7]->GetType()) {
				matchingListNeighbor.push(m_board[i][7]);
			}
		if (matchingListNeighbor.size() >= 3) {

			while (!matchingListNeighbor.empty()) {
				matchingListOfBoard.insert(matchingListNeighbor.front());


				matchingListNeighbor.pop();

			}
		}
		else {
			while (!matchingListNeighbor.empty()) {
				matchingListNeighbor.pop();
			}
		}

	}

	for (int j = 0; j < 8; j++) {

		for (int i = 0; i < 7; i++) {

			if (matchingListNeighbor.size() == 0) {
				matchingListNeighbor.push(m_board[i][j]);
			}
			else if (matchingListNeighbor.front()->GetType() == m_board[i][j]->GetType()) {
				matchingListNeighbor.push(m_board[i][j]);
			}
			else {
				if (matchingListNeighbor.size() >= 3) {

					while (!matchingListNeighbor.empty()) {
						matchingListOfBoard.insert(matchingListNeighbor.front());

						matchingListNeighbor.pop();

					}
				}
				else {
					while (!matchingListNeighbor.empty()) {
						matchingListNeighbor.pop();
					}
				}
				matchingListNeighbor.push(m_board[i][j]);
			}
		}
		if (!matchingListNeighbor.empty())
			if (matchingListNeighbor.front()->GetType() == m_board[7][j]->GetType()) {
				matchingListNeighbor.push(m_board[7][j]);
			}
		if (matchingListNeighbor.size() >= 3) {

			while (!matchingListNeighbor.empty()) {
				matchingListOfBoard.insert(matchingListNeighbor.front());



				matchingListNeighbor.pop();

			}
		}
		else {
			while (!matchingListNeighbor.empty()) {
				matchingListNeighbor.pop();
			}
		}
	}
	std::set<std::pair<int, int>> matchListIndex;
	for (auto iter : matchingListOfBoard) {
		matchListIndex.insert({ iter->GetRow(),iter->GetCol() });
		std::cout << iter->GetRow() << " va " << iter->GetCol() << std::endl;
	}
	return matchListIndex;
}
bool GameBoard::HasAnMatch() {

	if (this->GetMatchList().empty()) {
		return false;
	}
	else return true;
}

void GameBoard::SwapTwoSelectedPiece(int lastRow, int lastCol, int curRow, int curCol) {
	/*SetPhase(Phase::SWAP_PHASE);*/
	std::swap(m_board[lastRow][lastCol], m_board[curRow][curCol]);

	m_board[lastRow][lastCol]->SetRow(lastRow);
	m_board[lastRow][lastCol]->SetCol(lastCol);

	m_board[curRow][curCol]->SetRow(curRow);
	m_board[curRow][curCol]->SetCol(curCol);
}
void GameBoard::SwapTwoPiece(int lastRow, int lastCol, int curRow, int curCol) {

	if (m_board[lastRow][lastCol]==nullptr && m_board[curRow][curCol] == nullptr) return;
	std::swap(m_board[lastRow][lastCol], m_board[curRow][curCol]);
	if (m_board[lastRow][lastCol] != nullptr) {
		//m_board[lastRow][lastCol]->Set2DPosition(this->Get2DPosition().x + lastCol * 50 + 26, this->Get2DPosition().y + lastRow * 50 + 26);
		m_board[lastRow][lastCol]->SetRow(lastRow);
		m_board[lastRow][lastCol]->SetCol(lastCol);	
	}
	if (m_board[curRow][curCol] != nullptr) {
		//m_board[curRow ][curCol ]->Set2DPosition(this->Get2DPosition().x + curCol * 50 + 26, this->Get2DPosition().y + curRow * 50 + 26);
		m_board[curRow][curCol]->SetRow(curRow);
		m_board[curRow][curCol]->SetCol(curCol);
	}

}

void GameBoard::DestroyPieces(std::set<std::pair<int,int>> matchList) {
	for (auto a : matchList) {
		int i = a.first;
		int j = a.second;
		m_board[i][j] = nullptr;
	}
}

void GameBoard::RefillGameBoard() {
	for (int j = 0; j < 8; j++) {
		int nullCount = 0;
		for (int i = 6; i >=0; i--) {
			if (m_board[i][j] != nullptr) {
				int k = i;
				while (k <= 6 && m_board[k + 1][j] == nullptr) {
					SwapTwoPiece(k, j, k + 1, j);
					k++;
				}
			}
		}
		while (nullCount<=7 && m_board[nullCount][j] == nullptr) {
			nullCount++;
		}

		int temp = nullCount;//the number of pieces on the top of the board waiting to drop;
		while (nullCount--) {
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
			auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			int ran = rand() % 6;
			PieceType type = static_cast<PieceType>(ran);
			auto texture = ResourceManagers::GetInstance()->GetTexture("piece_hp.tga");
			switch (type) {
			case PieceType::HP:
				texture = ResourceManagers::GetInstance()->GetTexture("piece_hp.tga");
				break;
			case PieceType::Mana:
				texture = ResourceManagers::GetInstance()->GetTexture("piece_mana.tga");
				break;
			case PieceType::Poison:
				texture = ResourceManagers::GetInstance()->GetTexture("piece_poison.tga");
				break;
			case PieceType::Shield:
				texture = ResourceManagers::GetInstance()->GetTexture("piece_shield.tga");
				break;
			case PieceType::Spell:
				texture = ResourceManagers::GetInstance()->GetTexture("piece_spell.tga");
				break;
			case PieceType::Sword:
				texture = ResourceManagers::GetInstance()->GetTexture("piece_sword.tga");
				break;
			}
			std::shared_ptr<Piece> p = std::make_shared<Piece>(model, shader, texture,nullCount, j, type);
			p->Set2DPosition(this->Get2DPosition().x + j * 50 + 26, this->Get2DPosition().y + (nullCount-temp) * 50 + 26);
			p->SetSize(48, 48);
			m_board[nullCount][j] = p;
		}
	}
}
bool GameBoard::HasAnAvailableMove() {
	int i = 0;
	for (int j = 1; j < 7; j++) {
		auto type = m_board[i][j]->GetType();
		if (m_board[i][j - 1]->GetType() == type && m_board[i + 1][j + 1]->GetType() == type) return true;
		if (m_board[i + 1][j - 1]->GetType() == type && m_board[i + 1][j + 1]->GetType() == type) return true;
		if (m_board[i + 1][j - 1]->GetType() == type && m_board[i][j + 1]->GetType() == type) return true;
	}
	for(i=1;i<7;i++)
		for (int j = 1; j < 7; j++) {
			auto type = m_board[i][j]->GetType();
			if (m_board[i][j - 1]->GetType() == type && m_board[i + 1][j + 1]->GetType() == type) return true;
			if (m_board[i+1][j - 1]->GetType() == type && m_board[i + 1][j + 1]->GetType() == type) return true;
			if (m_board[i+1][j - 1]->GetType() == type && m_board[i ][j + 1]->GetType() == type) return true;
			if (m_board[i-1][j - 1]->GetType() == type && m_board[i][j + 1]->GetType() == type) return true;
			if (m_board[i][j-1]->GetType() == type && m_board[i - 1][j + 1]->GetType() == type) return true;
			if (m_board[i-1][j - 1]->GetType() == type && m_board[i - 1][j + 1]->GetType() == type) return true;

		}
	for (int j = 1; j < 7; j++) {
		auto type = m_board[i][j]->GetType();
		if (m_board[i - 1][j - 1]->GetType() == type && m_board[i][j + 1]->GetType() == type) return true;
		if (m_board[i][j - 1]->GetType() == type && m_board[i - 1][j + 1]->GetType() == type) return true;
		if (m_board[i - 1][j - 1]->GetType() == type && m_board[i - 1][j + 1]->GetType() == type) return true;
	}
	return false;
}
bool GameBoard::CanSwapTwoPiece(int lastRow, int lastCol, int curRow, int curCol) {

	SwapTwoPiece(lastRow, lastCol, curRow, curCol);
	if (HasAnMatch()) {
		SwapTwoPiece(lastRow, lastCol, curRow, curCol);
		return true;
	}
	else {
		SwapTwoPiece(lastRow, lastCol, curRow, curCol);
		return false;
	}
}
void GameBoard::HandleClick(float _x, float _y)
{	
	float posX = this->Get2DPosition().x;
	float posY = this->Get2DPosition().y;
	//std::cout << _x << " va " << _y<<std::endl;
	if(m_phase==Phase::BASE_PHASE)
	if (posX <= _x && _x <= posX + 400
		&& posY <= _y && _y <= posY + 400) {
		int curRow = (int)(_y - posY) / 50;
		int curCol = (int)(_x-posX) / 50;
		//std::cout << curRow << " va " << curCol <<" co " <<static_cast<int>(m_board[curRow][curCol]->GetType()) << std::endl;
		if (m_click.size() == 1) {
			int lastRow = m_click[0].first;
			int lastCol = m_click[0].second;
			if (abs(lastRow - curRow) + abs(curCol - lastCol) == 1)  {
					m_click.push_back({curRow, curCol});
					if (CanSwapTwoPiece(lastRow, lastCol, curRow, curCol)) {
						SwapTwoSelectedPiece(lastRow, lastCol, curRow, curCol);
						SetPhase(Phase::SWAP_PHASE);
					}
				}else {
						m_click.clear();
					}
		}
		else if (m_click.empty()) {
			m_click.push_back({ curRow,curCol });
			m_selected_piece->Set2DPosition(curCol * 50 + 226, curRow * 50 + 226);
		}
	}


}
