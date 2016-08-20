
#include "Battle.h"
#include "Map.h"

void DisplayPlayerInfo()
{
	cout << "이름 : " << g_pPlayer->strName << "\t직업 : " << g_pPlayer->strJobName << endl;
	cout << "레벨 : " << g_pPlayer->iLevel << "\t경험치 : " << g_pPlayer->iExp << endl;
	cout << "공격력 : " << g_pPlayer->iAttack << "\t방어력 : " << g_pPlayer->iArmor << endl;
	cout << "체력 : " << g_pPlayer->iHP << " / " << g_pPlayer->iHPMax << "\t마나 : " <<
		g_pPlayer->iMP << " / " << g_pPlayer->iMPMax << endl;
	cout << "보유금액 : " << g_pPlayer->iGold << " Gold" << endl;
}

void DisplayMonsterInfo(PMONSTER pMonster)
{
	cout << "이름 : " << pMonster->strName << endl;
	cout << "레벨 : " << pMonster->iLevel << "\t획득경험치 : " << pMonster->iExp << endl;
	cout << "공격력 : " << pMonster->iAttack << "\t방어력 : " << pMonster->iArmor << endl;
	cout << "체력 : " << pMonster->iHP << " / " << pMonster->iHPMax << "\t마나 : " <<
		pMonster->iMP << " / " << pMonster->iMPMax << endl;
	cout << "획득금액 : " << pMonster->iGold << " Gold" << endl;
}

void Battle(PMONSTER pMonster, MAP_TYPE eMapType)
{
	// 플레이어가 몬스터를 공격한다.
	int	iDamage = g_pPlayer->iAttack - pMonster->iArmor;
	iDamage = iDamage < 1 ? 1 : iDamage;

	pMonster->iHP -= iDamage;

	cout << g_pPlayer->strName << " 이(가) " << pMonster->strName << " 에게 " <<
		iDamage << " 피해를 입혔습니다." << endl;

	// 몬스터가 죽었을 경우
	if (pMonster->iHP <= 0)
	{
		g_pPlayer->iExp += pMonster->iExp;
		g_pPlayer->iGold += pMonster->iGold;

		cout << pMonster->strName << " 몬스터가 사망하였습니다." << endl;
		cout << pMonster->iExp << " 경험치를 획득하였습니다." << endl;
		cout << pMonster->iGold << " Gold를 획득하였습니다." << endl;

		SAFE_DELETE(pMonster);
		pMonster = new MONSTER;
		*pMonster = *g_pMonsterPrototype[eMapType];

		Sleep(1000);
		return;
	}

	// 몬스터가 플레이어를 공격한다.
	iDamage = pMonster->iAttack - g_pPlayer->iArmor;
	iDamage = iDamage < 1 ? 1 : iDamage;

	g_pPlayer->iHP -= iDamage;

	cout << pMonster->strName << " 이(가) " << g_pPlayer->strName << " 에게 " <<
		iDamage << " 피해를 입혔습니다." << endl;

	// 플레이어가 죽었을 경우
	if (g_pPlayer->iHP <= 0)
	{
		g_pPlayer->iHP = g_pPlayer->iHPMax;
		g_pPlayer->iMP = g_pPlayer->iMPMax;
		g_pPlayer->iExp /= 2;
		g_pPlayer->iGold -= (g_pPlayer->iGold * 0.1f);
		cout << g_pPlayer->strName << " 이(가) 사망하였습니다." << endl;
	}

	Sleep(1000);
}

void RunBattle(MAP_TYPE eMapType)
{
	// 실제 사용할 몬스터를 생성한다.
	PMONSTER	pMonster = new MONSTER;
	*pMonster = *g_pMonsterPrototype[eMapType]; //기존에 만들었던 몬스터 프로토 타입(데이터값)을 RunBattle안에서 만든 MONSTER로 복사

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
		// 플레이어 출력
		DisplayPlayerInfo();
		cout << endl;

		// 몬스터 출력
		DisplayMonsterInfo(pMonster);
		cout << endl;

		cout << "1. 공격" << endl;
		cout << "2. 도망가기" << endl;
		cout << "메뉴를 선택하세요 : ";
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
