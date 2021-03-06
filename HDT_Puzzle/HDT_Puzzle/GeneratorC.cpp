#include "GeneratorC.h"


Generator::Generator() {
	//First Step : maxMap 초기화 -1

	maxMap = new int*[MAX_SIZE_MAP];
	maxMap_Solution = new int*[MAX_SIZE_MAP];
	for (int row = 0; row < MAX_SIZE_MAP; row++) {
		maxMap[row] = new int[MAX_SIZE_MAP];
		maxMap_Solution[row] = new int[MAX_SIZE_MAP];
		for (int col = 0; col < MAX_SIZE_MAP; col++) {
			maxMap[row][col] = -1;
			maxMap_Solution[row][col] = -1;
		}
	}

	this->stRow = MAX_SIZE_MAP / 2;
	this->stCol = MAX_SIZE_MAP / 2;
}

Generator::~Generator() {
	for (int row = 0; row < MAX_SIZE_MAP; row++) {
		delete maxMap[row];
		delete maxMap_Solution[row];
	}

	delete maxMap;
	delete maxMap_Solution;
}

int Generator::getStartRow() {
	return this->stRow;
}
int Generator::getStartCol() {
	return this->stCol;
}

//시작x, 시작y, 바꿀 숫자
void Generator::GeneratorPuzzle(int x, int y, int value, bool pass) {
	maxMap_Solution[x][y] = value;

	if (rand() % 10 < HINT_RATE || value % LUCKYNUM == 0 || value == 1 || value == MAX_VALUE) {
		maxMap[x][y] = value;
		hintVecRow.push_back(x);
		hintVecCol.push_back(y);
		hintNum.push_back(value);
	}
	else {
		maxMap[x][y] = 0;
	}

	int zeroCount = 0;
	for (int i = 0; i < 8; i++) {
		if (x + dRow[i] < 0 || x + dRow[i] >= MAX_SIZE_MAP || y + dCol[i] < 0 || y + dCol[i] >= MAX_SIZE_MAP) {
			continue;
		}
		if (maxMap[x + dRow[i]][y + dCol[i]] == 0) {
			zeroCount++;
		}

	}

	if (zeroCount >= 4) {
		maxMap[x][y] = value;
		hintVecRow.push_back(x);
		hintVecCol.push_back(y);
		hintNum.push_back(value);
		zeroCount = 0;
	}

	curValue = value;

	//최대치 도달
	if (value == MAX_VALUE) {
		return;
	}

	value++;
	//break point는 다음과 같이 설정한다.
	//움직이려는 방향이 maxMap에서 벗어나려 한다면
	//dir배열 index를 1 올리고 움직일 수 있는지 확인한다.
	//이 때 움직이지 않는 횟수에 대한 변수를 선언 후
	//한 지점에서 움직이지 못할 때 마다 ++한다.
	//만약 움직일수 있다면 0으로 초기화
	//만약 모든 방향에서 움직이지 못한다면 ==8이므로 break
	int stopCount = 0;

	int ran;
	ran = rand() % 8;
	//cout<<ran;
		

	for (int i = 0; i < 8; i++) {
		int idx = (ran + i) % 8;
		int lookX = x + dRow[idx], lookY = y + dCol[idx];
		//만약 maxMap을 벗어난다면
		
		if (lookX < 0 || lookX > MAX_SIZE_MAP - 1
			|| lookY < 0 || lookY > MAX_SIZE_MAP - 1
			|| maxMap[lookX][lookY] != -1) {
			stopCount++;
			
		}
		//막힌 곳이 없다면
		else {
			if ((value - maxMap_Solution[lookX][lookY]) > DIF && maxMap_Solution[lookX][lookY] != -1) {
				stopCount = 8;
				break;
			}
			GeneratorPuzzle(lookX, lookY, value, pass);
			break;
		}
	}

	//모든 방향 이동 불가능
	if (stopCount >= 8) {
		maxMap[x][y] = value - 1;
	}
}

//풀어야할 퍼즐 출력
void Generator::ShowPuzzle() {

	//맵 확인 변수(제거 후)
	cout << "----------------------------------------------------" << endl;

	for (int row = 0; row < MAX_SIZE_MAP; row++) {
		for (int col = 0; col < MAX_SIZE_MAP; col++) {
			//if(maxMap[row][col] == -1){
			//    cout<<"   ";
			//}
			//else{
			if (maxMap[row][col] >= 0 && maxMap[row][col] < 10)
				cout << " ";
			cout << maxMap[row][col] << " ";
			//}

		}
		cout << endl;
	}
	cout << "----------------------------------------------------" << endl;
}

//정답 퍼즐 출력
void Generator::ShowCompletePuzzle() {
	cout << endl << "----------------------------------------------------" << endl;
	//맵 확인 변수(제거 전)
	for (int row = 0; row < MAX_SIZE_MAP; row++) {
		for (int col = 0; col < MAX_SIZE_MAP; col++) {

			if (maxMap_Solution[row][col] >= 0 && maxMap_Solution[row][col] < 10)
				cout << " ";
			cout << maxMap_Solution[row][col] << " ";
		}
		cout << endl;
	}
	cout << "----------------------------------------------------" << endl;
}


//최종 숫자 출력
int Generator::getEndNumber() {
	cout << "----------------------------------------------------" << endl;
	cout << "END NUMBER : " << curValue << endl;
	cout << "----------------------------------------------------" << endl;
	return curValue;
}

//힌트 출력
void Generator::ShowHint() {
	cout << "----------------------------------------------------" << endl;
	cout << "HINT (count: " << hintVecRow.size() << ") : ";
	for (int i = 0; i < hintVecRow.size(); i++) {
		cout << hintNum[i] << "(" << hintVecRow[i] << "," << hintVecCol[i] << ") ";
	}
	cout << "----------------------------------------------------" << endl;
}

void Generator::ReduceZero() {

	for (int i = 0; i < MAX_SIZE_MAP; i++) {
		for (int j = 0; j < MAX_SIZE_MAP; j++) {
			int zeroCount = 0;
			for (int t = 0; t < 8; t++) {
				if (i + dRow[t] < 0 || i + dRow[t] >= MAX_SIZE_MAP || j + dCol[t] < 0 || j + dCol[t] >= MAX_SIZE_MAP) {
					continue;
				}
				if (maxMap[i + dRow[t]][j + dCol[t]] == 0) {
					zeroCount++;
				}
			}

			if (zeroCount >= ZERO) {
				maxMap[i][j] = maxMap_Solution[i][j];
				hintVecRow.push_back(i);
				hintVecCol.push_back(j);
				hintNum.push_back(maxMap_Solution[i][j]);
			}

		}
	}


}

int ** Generator::getPuzzle()
{
	return maxMap;
}

int** Generator::getCompletePuzzle()
{
	return maxMap_Solution;
}

vector<vector<int> > Generator::getHint() {
	vector<vector<int> > temp;

	temp.push_back(this->hintVecRow);
	temp.push_back(this->hintVecCol);
	temp.push_back(this->hintNum);
	return vector<vector<int> >(temp);
}