
#include "Core.h"
#include "Map.h"
#include "Store.h"
#include "Inventory.h"

enum MAIN_MENU
{
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT
};

PPLAYER	g_pPlayer = NULL;

PPLAYER CreatePlayer()
{
	PPLAYER	pPlayer = new PLAYER;

	memset(pPlayer, 0, sizeof(PLAYER));

	cout << "플레이어 이름을 입력하세요 : ";
	cin.getline(pPlayer->strName, NAME_SIZE - 1);

	while (true)
	{
		system("cls");
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요 : ";
		int	iJob = InputInt();

		if (iJob > JOB_NONE && iJob < JOB_MAX)
		{
			pPlayer->eJob = (JOB)iJob;
			break;
		}
	}

	switch (pPlayer->eJob)
	{
	case JOB_KNIGHT:
		strcpy_s(pPlayer->strJobName, "기사");
		pPlayer->iAttack = 20;
		pPlayer->iArmor = 20;
		pPlayer->iHP = 500;
		pPlayer->iHPMax = 500;
		pPlayer->iMP = 200;
		pPlayer->iMPMax = 200;
		break;
	case JOB_ARCHER:
		strcpy_s(pPlayer->strJobName, "궁수");
		pPlayer->iAttack = 30;
		pPlayer->iArmor = 15;
		pPlayer->iHP = 400;
		pPlayer->iHPMax = 400;
		pPlayer->iMP = 300;
		pPlayer->iMPMax = 300;
		break;
	case JOB_WIZARD:
		strcpy_s(pPlayer->strJobName, "마법사");
		pPlayer->iAttack = 40;
		pPlayer->iArmor = 10;
		pPlayer->iHP = 300;
		pPlayer->iHPMax = 300;
		pPlayer->iMP = 500;
		pPlayer->iMPMax = 500;
		break;
	}

	pPlayer->iLevel = 1;
	pPlayer->iExp = 0;
	pPlayer->iGold = 10000;

	return pPlayer;
}


bool Init()
{
	// 플레이어 및 몬스터를 생성하고 초기화한다.
	g_pPlayer = CreatePlayer();

	// 맵을 초기화한다.
	if (!InitMap())
		return false;

	// 상점을 초기화한다.
	if (!InitStore())
		return false;

	// 인벤토리 초기화 
	if (!InitInventory())
		return false;

	return true;
}

int SelectMenu()
{
	system("cls");
	cout << "=================== 로비 ===================" << endl;
	cout << "1. 맵" << endl;
	cout << "2. 상점" << endl;
	cout << "3. 인벤토리" << endl;
	cout << "4. 종료" << endl;

	cout << "메뉴를 선택하세요 : ";
	int	iInput = InputInt();

	if (iInput <= MM_NONE || iInput > MM_EXIT)
		return MM_NONE;

	return iInput;
}

void Run()
{
	while (true)
	{
		switch (SelectMenu())
		{
		case MM_MAP:
			RunMap();
			break;
		case MM_STORE:
			RunStore();
			break;
		case MM_INVENTORY:
			RunInventory();
			break;
		case MM_EXIT:
			return;
		}
	}
}

void Release()
{
	if (g_pPlayer)
	{
		delete	g_pPlayer;
		g_pPlayer = NULL;
	}

	ReleaseMap();
	ReleaseStore();
	ReleaseInventory();
}
