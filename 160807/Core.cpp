
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

	cout << "�÷��̾� �̸��� �Է��ϼ��� : ";
	cin.getline(pPlayer->strName, NAME_SIZE - 1);

	while (true)
	{
		system("cls");
		cout << "1. ���" << endl;
		cout << "2. �ü�" << endl;
		cout << "3. ������" << endl;
		cout << "������ �����ϼ��� : ";
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
		strcpy_s(pPlayer->strJobName, "���");
		pPlayer->iAttack = 20;
		pPlayer->iArmor = 20;
		pPlayer->iHP = 500;
		pPlayer->iHPMax = 500;
		pPlayer->iMP = 200;
		pPlayer->iMPMax = 200;
		break;
	case JOB_ARCHER:
		strcpy_s(pPlayer->strJobName, "�ü�");
		pPlayer->iAttack = 30;
		pPlayer->iArmor = 15;
		pPlayer->iHP = 400;
		pPlayer->iHPMax = 400;
		pPlayer->iMP = 300;
		pPlayer->iMPMax = 300;
		break;
	case JOB_WIZARD:
		strcpy_s(pPlayer->strJobName, "������");
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
	// �÷��̾� �� ���͸� �����ϰ� �ʱ�ȭ�Ѵ�.
	g_pPlayer = CreatePlayer();

	// ���� �ʱ�ȭ�Ѵ�.
	if (!InitMap())
		return false;

	// ������ �ʱ�ȭ�Ѵ�.
	if (!InitStore())
		return false;

	// �κ��丮 �ʱ�ȭ 
	if (!InitInventory())
		return false;

	return true;
}

int SelectMenu()
{
	system("cls");
	cout << "=================== �κ� ===================" << endl;
	cout << "1. ��" << endl;
	cout << "2. ����" << endl;
	cout << "3. �κ��丮" << endl;
	cout << "4. ����" << endl;

	cout << "�޴��� �����ϼ��� : ";
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
