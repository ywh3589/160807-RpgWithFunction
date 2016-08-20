
#include "Battle.h"
#include "Map.h"

void DisplayPlayerInfo()
{
	cout << "�̸� : " << g_pPlayer->strName << "\t���� : " << g_pPlayer->strJobName << endl;
	cout << "���� : " << g_pPlayer->iLevel << "\t����ġ : " << g_pPlayer->iExp << endl;
	cout << "���ݷ� : " << g_pPlayer->iAttack << "\t���� : " << g_pPlayer->iArmor << endl;
	cout << "ü�� : " << g_pPlayer->iHP << " / " << g_pPlayer->iHPMax << "\t���� : " <<
		g_pPlayer->iMP << " / " << g_pPlayer->iMPMax << endl;
	cout << "�����ݾ� : " << g_pPlayer->iGold << " Gold" << endl;
}

void DisplayMonsterInfo(PMONSTER pMonster)
{
	cout << "�̸� : " << pMonster->strName << endl;
	cout << "���� : " << pMonster->iLevel << "\tȹ�����ġ : " << pMonster->iExp << endl;
	cout << "���ݷ� : " << pMonster->iAttack << "\t���� : " << pMonster->iArmor << endl;
	cout << "ü�� : " << pMonster->iHP << " / " << pMonster->iHPMax << "\t���� : " <<
		pMonster->iMP << " / " << pMonster->iMPMax << endl;
	cout << "ȹ��ݾ� : " << pMonster->iGold << " Gold" << endl;
}

void Battle(PMONSTER pMonster, MAP_TYPE eMapType)
{
	// �÷��̾ ���͸� �����Ѵ�.
	int	iDamage = g_pPlayer->iAttack - pMonster->iArmor;
	iDamage = iDamage < 1 ? 1 : iDamage;

	pMonster->iHP -= iDamage;

	cout << g_pPlayer->strName << " ��(��) " << pMonster->strName << " ���� " <<
		iDamage << " ���ظ� �������ϴ�." << endl;

	// ���Ͱ� �׾��� ���
	if (pMonster->iHP <= 0)
	{
		g_pPlayer->iExp += pMonster->iExp;
		g_pPlayer->iGold += pMonster->iGold;

		cout << pMonster->strName << " ���Ͱ� ����Ͽ����ϴ�." << endl;
		cout << pMonster->iExp << " ����ġ�� ȹ���Ͽ����ϴ�." << endl;
		cout << pMonster->iGold << " Gold�� ȹ���Ͽ����ϴ�." << endl;

		SAFE_DELETE(pMonster);
		pMonster = new MONSTER;
		*pMonster = *g_pMonsterPrototype[eMapType];

		Sleep(1000);
		return;
	}

	// ���Ͱ� �÷��̾ �����Ѵ�.
	iDamage = pMonster->iAttack - g_pPlayer->iArmor;
	iDamage = iDamage < 1 ? 1 : iDamage;

	g_pPlayer->iHP -= iDamage;

	cout << pMonster->strName << " ��(��) " << g_pPlayer->strName << " ���� " <<
		iDamage << " ���ظ� �������ϴ�." << endl;

	// �÷��̾ �׾��� ���
	if (g_pPlayer->iHP <= 0)
	{
		g_pPlayer->iHP = g_pPlayer->iHPMax;
		g_pPlayer->iMP = g_pPlayer->iMPMax;
		g_pPlayer->iExp /= 2;
		g_pPlayer->iGold -= (g_pPlayer->iGold * 0.1f);
		cout << g_pPlayer->strName << " ��(��) ����Ͽ����ϴ�." << endl;
	}

	Sleep(1000);
}

void RunBattle(MAP_TYPE eMapType)
{
	// ���� ����� ���͸� �����Ѵ�.
	PMONSTER	pMonster = new MONSTER;
	*pMonster = *g_pMonsterPrototype[eMapType]; //������ ������� ���� ������ Ÿ��(�����Ͱ�)�� RunBattle�ȿ��� ���� MONSTER�� ����

	while (true)
	{
		system("cls");

		switch (eMapType)
		{
		case MT_EASY:
			cout << "================== EASY ==================" << endl;
			break;
		case MT_NORMAL:
			cout << "================== NORMAL ==================" << endl;
			break;
		case MT_HARD:
			cout << "================== HARD ==================" << endl;
			break;
		}
		// �÷��̾� ���
		DisplayPlayerInfo();
		cout << endl;

		// ���� ���
		DisplayMonsterInfo(pMonster);
		cout << endl;

		cout << "1. ����" << endl;
		cout << "2. ��������" << endl;
		cout << "�޴��� �����ϼ��� : ";
		int	iInput = InputInt();

		if (iInput == UINT_MAX || iInput <= BM_NONE || iInput > BM_BACK)
			continue;

		else if (iInput == BM_BACK)
			break;

		switch (iInput)
		{
		case BM_ATTACK:
			Battle(pMonster, eMapType);
			break;
		}
	}

	SAFE_DELETE(pMonster);
}
