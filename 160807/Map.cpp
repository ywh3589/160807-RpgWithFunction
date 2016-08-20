

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
	cout << "�о�� ���ϸ��� �Է��ϼ��� : ";
	fflush(stdin);
	char	strFileName[256] = {};
	cin.getline(strFileName, 255);
	// �� �ʿ��� ����� ���� ������Ÿ�� ������ �����Ѵ�.

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
	cout << "=================== �� ���� ===================" << endl;
	cout << "1. ����" << endl;
	cout << "2. �߰�" << endl;
	cout << "3. �����" << endl;
	cout << "4. �ڷΰ���" << endl;

	cout << "�޴��� �����ϼ��� : ";
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
