
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

	//  상점 파일로부터 아이템을 읽어온다.
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

	cout << "0. 뒤로가기" << endl;
	cout << "플레이어 소지금 : " << g_pPlayer->iGold << " Gold" << endl;

	cout << "구매할 아이템을 선택하세요 : ";
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

		// 아이템 목록을 보여준다.
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

		// 돈이 부족한지 체크한다.
		if (pItem->iPrice > g_pPlayer->iGold)
		{
			cout << "소지금이 부족합니다." << endl;
			continue;
		}

		// 인벤토리 공간이 부족한지 체크한다.
		else if (g_pInventory->iItemCount == INVENTORY_MAX)
		{
			cout << "인벤토리에 공간이 부족합니다." << endl;
			continue;
		}

		// 위의 경우들이 아니라면 아이템을 구매한다.
		PITEM	pNewItem = new ITEM;
		memset(pNewItem, 0, sizeof(ITEM));
		*pNewItem = *pItem;
		//pNewItem = pItem;

		// 플레이어 돈을 차감한다.
		g_pPlayer->iGold -= pItem->iPrice;

		// 인벤토리에 아이템을 넣어준다.
		g_pInventory->pItem[g_pInventory->iItemCount] = pNewItem;
		++g_pInventory->iItemCount;
		cout << pNewItem->strName << " 아이템을 구매하였습니다." << endl;
		Sleep(1000);
	}
}

int SelectStoreMenu()
{
	system("cls");
	cout << "1. 무기상점" << endl;
	cout << "2. 방어구상점" << endl;
	cout << "3. 뒤로가기" << endl;
	cout << "상점을 선택하세요 : ";
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
