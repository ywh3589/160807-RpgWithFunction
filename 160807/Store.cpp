
#include "Store.h"

PSTORE	g_pStore = NULL;

PITEMNODE CreateItemNode(PITEM pItem)
{
	PITEMNODE	pNode = new ITEMNODE;
	memset(pNode, 0, sizeof(ITEMNODE));

	pNode->pItem = pItem;

	return pNode;
}

bool InitStore()	//making two lists for items using linked list functions in value.h 
{
	g_pStore = new STORE;
	memset(g_pStore, 0, sizeof(STORE));

	InitItemList(&g_pStore->tWeaponList);
	InitItemList(&g_pStore->tArmorList);

	//  ���� ���Ϸκ��� �������� �о�´�.
	FILE*	pFile = NULL;

	fopen_s(&pFile, "WeaponStore.wst", "rb");

	if (!pFile)
		return false;
	//-----------?--------------
	int		iCount = 0;
	fread(&iCount, 4, 1, pFile);
	//--------------------------
	for (int i = 0; i < iCount; ++i)
	{
		PITEM	pItem = new ITEM;
		memset(pItem, 0, sizeof(ITEM));

		fread(pItem, sizeof(ITEM), 1, pFile);
		PITEMNODE	pNode = CreateItemNode(pItem);
		AddItemList(&g_pStore->tWeaponList, pNode);
	}

	fclose(pFile);

	fopen_s(&pFile, "ArmorStore.wst", "rb");

	if (!pFile)
		return false;

	fread(&iCount, 4, 1, pFile);

	for (int i = 0; i < iCount; ++i)
	{
		PITEM	pItem = new ITEM;
		memset(pItem, 0, sizeof(ITEM));

		fread(pItem, sizeof(ITEM), 1, pFile);
		PITEMNODE	pNode = CreateItemNode(pItem);
		AddItemList(&g_pStore->tArmorList, pNode);
	}

	fclose(pFile);

	return true;
}

int DisplayItemList(PITEMLIST pList)
{
	system("cls");

	PITEMNODE	pNode = pList->pBegin->pNext;

	for (int i = 0; i < pList->iCount; ++i, pNode = pNode->pNext)
	{
		cout << i + 1 << ". " << endl;
		DisplayItemInfo(pNode->pItem);
		cout << endl;
	}

	cout << "0. �ڷΰ���" << endl;
	cout << "�÷��̾� ������ : " << g_pPlayer->iGold << " Gold" << endl;

	cout << "������ �������� �����ϼ��� : ";
	int	iInput = InputInt();

	if (iInput == UINT_MAX || iInput < 0 || iInput > pList->iCount)
		return UINT_MAX;

	return iInput;
}

PITEM FindItem(PITEMLIST pList, int iNumber)
{
	PITEMNODE	pNode = pList->pBegin->pNext;

	for (int i = 0; i < iNumber; ++i, pNode = pNode->pNext)
	{
	}

	return pNode->pItem;
}

void RunStoreBuy(STORE_TYPE eType)
{
	while (true)
	{
		int	iInput = 0;

		PITEMLIST	pList = NULL;

		// ������ ����� �����ش�.
		switch (eType)
		{
		case ST_WEAPON:
			pList = &g_pStore->tWeaponList;
			break;
		case ST_ARMOR:
			pList = &g_pStore->tArmorList;
			break;
		}

		iInput = DisplayItemList(pList);

		if (iInput == UINT_MAX)
			continue;

		else if (iInput == 0)
			break;

		PITEM	pItem = FindItem(pList, iInput - 1);

		// ���� �������� üũ�Ѵ�.
		if (pItem->iPrice > g_pPlayer->iGold)
		{
			cout << "�������� �����մϴ�." << endl;
			continue;
		}

		// �κ��丮 ������ �������� üũ�Ѵ�.
		else if (g_pInventory->iItemCount == INVENTORY_MAX)
		{
			cout << "�κ��丮�� ������ �����մϴ�." << endl;
			continue;
		}

		// ���� ������ �ƴ϶�� �������� �����Ѵ�.
		PITEM	pNewItem = new ITEM;
		memset(pNewItem, 0, sizeof(ITEM));
		*pNewItem = *pItem;
		//pNewItem = pItem;

		// �÷��̾� ���� �����Ѵ�.
		g_pPlayer->iGold -= pItem->iPrice;

		// �κ��丮�� �������� �־��ش�.
		g_pInventory->pItem[g_pInventory->iItemCount] = pNewItem;
		++g_pInventory->iItemCount;
		cout << pNewItem->strName << " �������� �����Ͽ����ϴ�." << endl;
		Sleep(1000);
	}
}

int SelectStoreMenu()
{
	system("cls");
	cout << "1. �������" << endl;
	cout << "2. ������" << endl;
	cout << "3. �ڷΰ���" << endl;
	cout << "������ �����ϼ��� : ";
	int	iInput = InputInt();

	if (iInput == UINT_MAX || iInput <= ST_NONE || iInput > ST_BACK)
		return ST_NONE;

	return iInput;
}

#if 1
void RunStore()
{
	while (true)
	{
		int iInput = SelectStoreMenu();

		if (iInput == ST_NONE)
			continue;

		else if (iInput == ST_BACK)
			return;

		RunStoreBuy((STORE_TYPE)iInput);
	}
}
#endif

#if 0
void RunStore()
{

	while (true)
	{

	}
}
#endif
void ReleaseStore()
{
	SAFE_DELETE(g_pStore);
}
