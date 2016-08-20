

#include "Map.h"
#include "Battle.h"

PMONSTER	g_pMonsterPrototype[MT_MAX] = {};

PMONSTER CreateMonsterPrototype(char* pName, int iAttack, int iArmor, int iHP, int iMP, int iLevel, int iExp, int iGold)
{
	PMONSTER	pMonster = new MONSTER;
	memset(pMonster, 0, sizeof(MONSTER));

	strcpy_s(pMonster->strName, pName);
	pMonster->iAttack = iAttack;
	pMonster->iArmor = iArmor;
	pMonster->iHP = iHP;
	pMonster->iHPMax = iHP;
	pMonster->iMP = iMP;
	pMonster->iMPMax = iMP;
	pMonster->iLevel = iLevel;
	pMonster->iExp = iExp;
	pMonster->iGold = iGold;

	return pMonster;
}

bool InitMap()
{
	system("cls");
	cout << "읽어올 파일명을 입력하세요 : ";
	fflush(stdin);
	char	strFileName[256] = {};
	cin.getline(strFileName, 255);
	// 각 맵에서 사용할 몬스터 프로토타입 정보를 생성한다.

	FILE  *pFile = NULL;
	fopen_s(&pFile, strFileName, "rb");

	if (!pFile)
		return false;

	for (int i = 0; i < MT_MAX; ++i)
	{
		SAFE_DELETE(g_pMonsterPrototype[i]);
		g_pMonsterPrototype[i] = new MONSTER;
		fread(g_pMonsterPrototype[i], sizeof(MONSTER), 1, pFile);
	}

	fclose(pFile);

	return true;
}

int SelectMapMenu()
{
	system("cls");
	cout << "=================== 맵 선택 ===================" << endl;
	cout << "1. 쉬움" << endl;
	cout << "2. 중간" << endl;
	cout << "3. 어려움" << endl;
	cout << "4. 뒤로가기" << endl;

	cout << "메뉴를 선택하세요 : ";
	int	iInput = InputInt();

	if (iInput <= MAP_NONE || iInput > MAP_BACK)
		return MAP_NONE;

	return iInput;
}

void RunMap()
{
	while (true)
	{
		switch (SelectMapMenu())
		{
		case MAP_EASY:
			RunBattle(MT_EASY);
			break;
		case MAP_NORMAL:
			RunBattle(MT_NORMAL);
			break;
		case MAP_HARD:
			RunBattle(MT_HARD);
			break;
		case MAP_BACK:
			return;
		}
	}
}

void ReleaseMap()
{
	for (int i = 0; i < MT_MAX; ++i)
	{
		SAFE_DELETE(g_pMonsterPrototype[i]);
	}
}
