#include"GameBoard.h"
#include"Piece.h"
#include"ResourceManagers.h"
#include"Sprite2D.h"
#include<random>
#include <queue>
#include <set>

GameBoard::GameBoard():m_standbyTime(0),m_moveSpeed(350) {
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
		m_frame->SetSize(GB_frameWidth, GB_frameHeight);
		m_frame->Set2DPosition(GB_posX+GB_width/2, GB_posY+GB_height/2);

		texture= ResourceManagers::GetInstance()->GetTexture("board2.tga");
		m_background= std::make_shared<Sprite2D>(model, shader, texture);
		m_background->SetSize(GB_frameWidth, GB_frameHeight);
		m_background->Set2DPosition(GB_posX + GB_width / 2, GB_posY + GB_height / 2);

		texture = ResourceManagers::GetInstance()->GetTexture("selected_piece.tga");
		m_selected_piece = std::make_shared<Sprite2D>(model, shader, texture);
		m_selected_piece2 = std::make_shared<Sprite2D>(model, shader, texture);
		m_selected_piece->SetSize(Pi_size, Pi_size);
		m_selected_piece2->SetSize(Pi_size, Pi_size);

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
				int rowCheck = -1;
				if (j > 1) {
					int pre1 = static_cast<int>(line[j - 1]->GetType());
					int pre2 = static_cast<int>(line[j - 2]->GetType());
					rowCheck = (pre1 == pre2?pre1:-1);




				}
					while (ran == rowCheck || ran == colCheck) ran = rand() % 6;
				PieceType type = static_cast<PieceType>(ran);
				std::shared_ptr<Piece> p = std::make_shared<Piece>(i, j, type);
				p->Set2DPosition(GB_posX + j * Pi_size + Pi_size/2,GB_posY + i * Pi_size + Pi_size/2);
				line.push_back(p);
			}
			m_board.push_back(line);
		}
	} while (!HasAnAvailableMove());

}

bool GameBoard::IsSwapping() {
	return m_isSwapping;
}
bool GameBoard::IsRefilling() {
	return m_isRefilling;
}

void GameBoard::ChangePositionOfTwoPiece(int lastRow, int lastCol, int curRow, int curCol,float deltaTime) {
	int last_trueX = GB_posX + Pi_size / 2 + lastCol * Pi_size;
	int last_trueY = GB_posY + Pi_size / 2 + lastRow * Pi_size;
	int cur_trueX = GB_posX + Pi_size / 2 + curCol * Pi_size;
	int cur_trueY = GB_posY + Pi_size / 2 + curRow * Pi_size;
	auto lastPiece = m_board[lastRow][lastCol];
	auto curPiece = m_board[curRow][curCol];

	if (lastPiece->Get2DPosition().x == last_trueX && lastPiece->Get2DPosition().y == last_trueY) {
		m_isSwapping = false;
	}
	else {
		int dx = (lastCol - curCol > 0 ? 1 : (lastCol - curCol == 0 ? 0 : -1)) * (int)(m_moveSpeed * deltaTime);
		int dy = (lastRow - curRow > 0 ? 1 : (lastRow - curRow == 0 ? 0 : -1)) * (int)(m_moveSpeed * deltaTime);
		lastPiece->Set2DPosition(lastPiece->Get2DPosition().x + dx , lastPiece->Get2DPosition().y + dy );
		curPiece->Set2DPosition(curPiece->Get2DPosition().x - dx, curPiece->Get2DPosition().y - dy);

		if (abs(lastPiece->Get2DPosition().x -last_trueX + lastPiece->Get2DPosition().y -last_trueY) <= abs(dx+dy))
			lastPiece->Set2DPosition(last_trueX,last_trueY);
		if (abs(curPiece->Get2DPosition().x - cur_trueX + curPiece->Get2DPosition().y - cur_trueY) <= abs(dx+dy))
			curPiece->Set2DPosition(cur_trueX,cur_trueY);
	}
	//if (m_board[lastRow][lastCol]->Get2DPosition().x == last_trueX && m_board[lastRow][lastCol]->Get2DPosition().y == last_trueY) {
	//	m_isSwapping = false;
	//}
	//else {
	//	int dx = (lastCol - curCol > 0 ? 1 : (lastCol - curCol == 0 ? 0 : -1)) * (int)(m_moveSpeed * deltaTime);
	//	int dy = (lastRow - curRow > 0 ? 1 : (lastRow - curRow == 0 ? 0 : -1)) * (int)(m_moveSpeed * deltaTime);
	//	std::cout << "dy: " << dy << std::endl;
	//	std::cout << "delta:" << abs(m_board[lastRow][lastCol]->Get2DPosition().x - last_trueX + m_board[lastRow][lastCol]->Get2DPosition().y - last_trueY) << std::endl;
	//	m_board[lastRow][lastCol]->Set2DPosition(m_board[lastRow][lastCol]->Get2DPosition().x + dx, m_board[lastRow][lastCol]->Get2DPosition().y + dy);
	//	m_board[curRow][curCol]->Set2DPosition(m_board[curRow][curCol]->Get2DPosition().x - dx, m_board[curRow][curCol]->Get2DPosition().y - dy);

	//	if (abs(m_board[lastRow][lastCol]->Get2DPosition().x - last_trueX + m_board[lastRow][lastCol]->Get2DPosition().y - last_trueY) <= abs(dx + dy))
	//		m_board[lastRow][lastCol]->Set2DPosition(last_trueX, last_trueY);
	//	if (abs(m_board[curRow][curCol]->Get2DPosition().x - cur_trueX + m_board[curRow][curCol]->Get2DPosition().y - cur_trueY) <= abs(dx + dy))
	//		m_board[curRow][curCol]->Set2DPosition(cur_trueX, cur_trueY);
	//	//SetPhase(Phase::DESTROY_PHASE);
	//}
};

void GameBoard::RefillPositionGameBoard(float deltaTime) {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			auto piece = m_board[i][j];
			int trueX = GB_posX + Pi_size / 2 + Pi_size * j;
			int trueY = GB_posY + Pi_size / 2 + Pi_size * i;
			if (abs(piece->Get2DPosition().y - trueY) >= m_moveSpeed * deltaTime) {
				piece->Set2DPosition(trueX, piece->Get2DPosition().y + int(m_moveSpeed * deltaTime));
			}
			else {
				piece->Set2DPosition(trueX, trueY);
			}
		}
	m_standbyTime += deltaTime;
	if (m_standbyTime > 400 / m_moveSpeed) {
		m_isRefilling = false;
		m_standbyTime = 0;
	}
}
void GameBoard::Draw() {
	m_background->Draw();
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			if(m_board[i][j]!=nullptr &&m_board[i][j]->Get2DPosition().y>=GB_posY)
				m_board[i][j]->Draw();

		}
	m_frame->Draw();
	m_selected_piece->Draw();

	m_selected_piece2->Draw();
}

std::set<std::pair<int,int>> GameBoard::GetPieceIndexMatchedList() {
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
	}
	return matchListIndex;
}

void	GameBoard::SetDestroyList(std::set<std::pair<int, int>> list) {
	m_destroyList = list;
};

std::set<std::pair<int, int>> GameBoard::GetDestroyList() {
	return m_destroyList;
}
std::set<std::pair<int, int>>	GameBoard::GetPieceIndexType(int type) {
	std::set<std::pair<int, int>> list;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (static_cast<int>(m_board[i][j]->GetType()) == type) {
				list.insert({ i,j });
			}
		}
	}
	return list;
};

std::vector<int> GameBoard::GetPieceTypeMatchedList(std::set<std::pair<int, int>> matchList) {
	int n = static_cast<int>(PieceType::COUNT);
	std::vector<int> res(n);
	for (auto x : matchList) {
		int i = x.first;
		int j = x.second;
		int type = static_cast<int>(m_board[i][j]->GetType());
		res[type]++;
	}
	return res;
};

bool GameBoard::HasAnMatch() {

	if (this->GetPieceIndexMatchedList().empty()) {
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
	m_isSwapping = true;

}
void GameBoard::SwapTwoPiece(int lastRow, int lastCol, int curRow, int curCol) {

	if (m_board[lastRow][lastCol]==nullptr && m_board[curRow][curCol] == nullptr) return;
	std::swap(m_board[lastRow][lastCol], m_board[curRow][curCol]);
	if (m_board[lastRow][lastCol] != nullptr) {
		//m_board[lastRow][lastCol]->Set2DPosition(GB_posX + lastCol * 50 + 26, GB_posY + lastRow * 50 + 26);
		m_board[lastRow][lastCol]->SetRow(lastRow);
		m_board[lastRow][lastCol]->SetCol(lastCol);	
	}
	if (m_board[curRow][curCol] != nullptr) {
		//m_board[curRow ][curCol ]->Set2DPosition(GB_posX + curCol * 50 + 26, GB_posY + curRow * 50 + 26);
		m_board[curRow][curCol]->SetRow(curRow);
		m_board[curRow][curCol]->SetCol(curCol);
	}
}

void GameBoard::DestroyPieces(std::set<std::pair<int,int>> pieceIndexMatchedList) {
	for (auto a : pieceIndexMatchedList) {
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
			PieceType type = static_cast<PieceType>(rand()%static_cast<int>(PieceType::COUNT));
			std::shared_ptr<Piece> p = std::make_shared<Piece>(nullCount, j, type);
			p->Set2DPosition(GB_posX + Pi_size/2 + Pi_size*j , GB_posY + (nullCount-temp) * Pi_size + Pi_size/2);
			m_board[nullCount][j] = p;
		}
	}
	m_isRefilling = true;
}
bool GameBoard::SameType(std::vector<std::pair<int,int>> listPiece) {
	if (listPiece.size() == 0) return false;
	auto type = m_board[listPiece[0].first][listPiece[0].second]->GetType();
	for (auto x : listPiece) {
		if (m_board[x.first][x.second]->GetType() != type) return false;
	}
	return true;
}
bool GameBoard::HasAnAvailableMove() {
//Horizontal Check
	int i = 0;
	//for (int j = 1; j < 7; j++) {
	//	auto type = m_board[i][j]->GetType();
	//	if (m_board[i][j - 1]->GetType() == type && m_board[i + 1][j + 1]->GetType() == type) return true;
	//	if (m_board[i + 1][j - 1]->GetType() == type && m_board[i + 1][j + 1]->GetType() == type) return true;
	//	if (m_board[i + 1][j - 1]->GetType() == type && m_board[i][j + 1]->GetType() == type) return true;
	//}
	for (int j = 1; j < 7; j++) {
		if (SameType({ {i,j}, {i,j - 1}, {i + 1,j + 1} })) return true;
		if (SameType({ {i,j}, {i+1,j - 1}, {i + 1,j + 1} })) return true;
		if (SameType({ {i+1,j}, {i,j - 1}, {i ,j + 1} })) return true;
	}
	//for(i=1;i<7;i++)
	//	for (int j = 1; j < 7; j++) {
	//		auto type = m_board[i][j]->GetType();
	//		if (m_board[i][j - 1]->GetType() == type && m_board[i + 1][j + 1]->GetType() == type) return true;
	//		if (m_board[i+1][j - 1]->GetType() == type && m_board[i + 1][j + 1]->GetType() == type) return true;
	//		if (m_board[i+1][j - 1]->GetType() == type && m_board[i ][j + 1]->GetType() == type) return true;
	//		if (m_board[i-1][j - 1]->GetType() == type && m_board[i][j + 1]->GetType() == type) return true;
	//		if (m_board[i][j-1]->GetType() == type && m_board[i - 1][j + 1]->GetType() == type) return true;
	//		if (m_board[i-1][j - 1]->GetType() == type && m_board[i - 1][j + 1]->GetType() == type) return true;

	//	}
	for (i = 1; i < 7; i++)
		for (int j = 1; j < 7; j++) {
			if (SameType({ {i,j}, {i,j - 1}, {i + 1,j + 1} })) return true;
			if (SameType({ {i,j}, {i + 1,j - 1}, {i + 1,j + 1} })) return true;
			if (SameType({ {i,j}, {i+1,j - 1}, {i ,j + 1} })) return true;

			if (SameType({ {i,j}, {i,j - 1}, {i - 1,j + 1} })) return true;
			if (SameType({ {i,j}, {i - 1,j - 1}, {i - 1,j + 1} })) return true;
			if (SameType({ {i,j}, {i-1,j - 1}, {i ,j + 1} })) return true;
		}
	//for (int j = 1; j < 7; j++) {
	//	auto type = m_board[i][j]->GetType();
	//	if (m_board[i - 1][j - 1]->GetType() == type && m_board[i][j + 1]->GetType() == type) return true;
	//	if (m_board[i][j - 1]->GetType() == type && m_board[i - 1][j + 1]->GetType() == type) return true;
	//	if (m_board[i - 1][j - 1]->GetType() == type && m_board[i - 1][j + 1]->GetType() == type) return true;
	//}
	for (int j = 1; j < 7; j++) {
		if (SameType({ {i,j}, {i,j - 1}, {i - 1,j + 1} })) return true;
		if (SameType({ {i,j}, {i - 1,j - 1}, {i - 1,j + 1} })) return true;
		if (SameType({ {i,j}, {i - 1,j - 1}, {i ,j + 1} })) return true;
	}

//Vertical Check
	int j = 0;
	for (int i = 1; i < 7; i++) {
		if (SameType({ {i,j}, {i - 1,j }, {i + 1,j + 1} })) return true;
		if (SameType({ {i,j}, {i - 1,j + 1}, {i + 1,j + 1} })) return true;
		if (SameType({ {i,j}, {i - 1,j + 1}, {i +1 ,j} })) return true;
	}
	for (j = 1; j < 7; j++) 
		for (int i = 1; i < 7; i++) {
			if (SameType({ {i,j}, {i - 1,j }, {i + 1,j + 1} })) return true;
			if (SameType({ {i,j}, {i - 1,j + 1}, {i + 1,j + 1} })) return true;
			if (SameType({ {i,j}, {i - 1,j + 1}, {i + 1 ,j} })) return true;

			if (SameType({ {i,j}, {i - 1,j }, {i + 1,j - 1} })) return true;
			if (SameType({ {i,j}, {i - 1,j - 1}, {i + 1,j} })) return true;
			if (SameType({ {i,j}, {i - 1,j - 1}, {i + 1,j - 1} })) return true;
		}
	for (int i = 1; i < 7; i++) {
		if (SameType({ {i,j}, {i - 1,j }, {i + 1,j - 1} })) return true;
		if (SameType({ {i,j}, {i - 1,j - 1}, {i + 1,j} })) return true;
		if (SameType({ {i,j}, {i - 1,j - 1}, {i + 1,j - 1} })) return true;
	}

	return false;
}


std::vector<std::vector<int>> GameBoard::GetAvailableMoveList() {
	std::vector<std::vector<int>> list;
//Horizontal Check
	int i = 0;
	for (int j = 1; j < 7; j++) {
		if (SameType({ {i,j}, {i,j - 1}, {i + 1,j + 1} })) {
			std::vector<int> res={i,j+1,i+1,j+1};
			list.push_back(res);
		}
		if (SameType({ {i,j}, {i + 1,j - 1}, {i + 1,j + 1} })) {
			std::vector<int> res = { i,j ,i + 1,j };
			list.push_back(res);
		};
		if (SameType({ {i,j}, {i + 1,j - 1}, {i,j + 1} })) {
			std::vector<int> res = { i,j - 1,i+1,j - 1 };
			list.push_back(res);
		};
	}
	for (i = 1; i < 7; i++)
		for (int j = 1; j < 7; j++) {
			if (SameType({ {i,j}, {i,j - 1}, {i + 1,j + 1} })) {
				std::vector<int> res = { i,j + 1,i + 1,j + 1 };
				list.push_back(res);
			}
			if (SameType({ {i,j}, {i + 1,j - 1}, {i + 1,j + 1} })) {
				std::vector<int> res = { i,j ,i + 1,j };
				list.push_back(res);
			};
			if (SameType({ {i,j}, {i + 1,j - 1}, {i,j + 1} })) {
				std::vector<int> res = { i,j - 1,i + 1,j - 1 };
				list.push_back(res);
			};
			if (SameType({ {i,j}, {i,j - 1}, {i - 1,j + 1} })) {
				std::vector<int> res = { i,j + 1,i - 1,j + 1 };
				list.push_back(res);
			}
			if (SameType({ {i,j}, {i - 1,j - 1}, {i - 1,j + 1} })) {
				std::vector<int> res = { i,j ,i - 1,j };
				list.push_back(res);
			};
			if (SameType({ {i,j}, {i - 1,j - 1}, {i ,j + 1} })) {
				std::vector<int> res = { i,j - 1,i - 1,j - 1 };
				list.push_back(res);
			};
		}

	for (int j = 1; j < 7; j++) {
		if (SameType({ {i,j}, {i,j - 1}, {i - 1,j + 1} })) {
			std::vector<int> res = { i,j + 1,i - 1,j + 1 };
			list.push_back(res);
		}
		if (SameType({ {i,j}, {i - 1,j - 1}, {i - 1,j + 1} })) {
			std::vector<int> res = { i,j ,i - 1,j };
			list.push_back(res);
		};
		if (SameType({ {i,j}, {i - 1,j - 1}, {i ,j + 1} })) {
			std::vector<int> res = { i,j - 1,i - 1,j - 1 };
			list.push_back(res);
		};
	}
//Vertical Check
	int j = 0;
	for (int i = 1; i < 7; i++) {
		if (SameType({ {i,j}, {i - 1,j }, {i + 1,j + 1} })) {
			std::vector<int> res = { i + 1,j ,i + 1 ,j + 1 };
			list.push_back(res);
		};
		if (SameType({ {i,j}, {i - 1,j + 1}, {i + 1,j + 1} })) {
			std::vector<int> res = { i,j ,i + 1,j + 1 };
			list.push_back(res);
		};
		if (SameType({ {i,j}, {i - 1,j + 1}, {i + 1 ,j} })) {
			std::vector<int> res = { i - 1,j,i - 1,j + 1 };
			list.push_back(res);
		};
	}
	for (j = 1; j < 7; j++)
		for (int i = 1; i < 7; i++) {
			if (SameType({ {i,j}, {i - 1,j }, {i + 1,j + 1} })) {
				std::vector<int> res = { i + 1,j ,i + 1 ,j + 1 };
				list.push_back(res);
			};
			if (SameType({ {i,j}, {i - 1,j + 1}, {i + 1,j + 1} })) {
				std::vector<int> res = { i,j ,i + 1,j + 1 };
				list.push_back(res);
			};
			if (SameType({ {i,j}, {i - 1,j + 1}, {i + 1 ,j} })) {
				std::vector<int> res = { i - 1,j,i - 1,j + 1 };
				list.push_back(res);
			};

			if (SameType({ {i,j}, {i - 1,j }, {i + 1,j - 1} })) {
				std::vector<int> res = { i + 1,j,i + 1,j - 1 };
				list.push_back(res);
			};
			if (SameType({ {i,j}, {i - 1,j - 1}, {i + 1,j} })) {
				std::vector<int> res = { i - 1,j,i - 1,j - 1 };
				list.push_back(res);
			};
			if (SameType({ {i,j}, {i - 1,j - 1}, {i + 1,j - 1} })) {
				std::vector<int> res = { i,j,i ,j - 1 };
				list.push_back(res);
			};
		}
	for (int i = 1; i < 7; i++) {
		if (SameType({ {i,j}, {i - 1,j }, {i + 1,j - 1} })) {
			std::vector<int> res = { i + 1,j,i + 1,j - 1 };
			list.push_back(res);
		};
		if (SameType({ {i,j}, {i - 1,j - 1}, {i + 1,j} })) {
			std::vector<int> res = { i - 1,j,i - 1,j - 1 };
			list.push_back(res);
		};
		if (SameType({ {i,j}, {i - 1,j - 1}, {i + 1,j - 1} })) {
			std::vector<int> res = { i,j,i ,j - 1 };
			list.push_back(res);
		};
	}


	return list;
};

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

