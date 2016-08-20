
#pragma once

#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

#define	NAME_SIZE	32
#define ITEM_SIZE	5
#define	SAFE_DELETE(p)	if(p){delete p; p = NULL;}

enum JOB
{
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_MAX
};

enum MAP
{
	MAP_NONE,
	MAP_EASY,
	MAP_NORMAL,
	MAP_HARD,
	MAP_BACK
};

enum MAP_TYPE
{
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_MAX
};

enum BATTLE_MENU
{
	BM_NONE,
	BM_ATTACK,
	BM_BACK
};


enum ITEM_TYPE
{
	IT_WEAPON,
	IT_ARMOR
};

enum STORE_TYPE
{
	ST_NONE,
	ST_WEAPON,
	ST_ARMOR,
	ST_BACK
};

typedef struct _tagItem
{
	char		strName[NAME_SIZE];
	ITEM_TYPE	eType;
	int			iOption;
	int			iPrice;
	int			iSell;
}ITEM, *PITEM;

typedef struct _tagItemNode
{
	_tagItemNode*	pNext;
	_tagItemNode*	pPrev;
	PITEM			pItem;
}ITEMNODE, *PITEMNODE;

typedef struct _tagItemList
{
	PITEMNODE	pBegin;
	PITEMNODE	pEnd;
	int			iCount;
}ITEMLIST, *PITEMLIST;

typedef struct _tagStore
{
	ITEMLIST	tWeaponList;
	ITEMLIST	tArmorList;
}STORE, *PSTORE;

#define	INVENTORY_MAX	10

typedef struct _tagInventory
{
	PITEM	pItem[INVENTORY_MAX];
	int		iItemCount;
}INVENTORY, *PINVENTORY;

typedef struct _tagPlayer
{
	char	strName[NAME_SIZE];
	char	strJobName[NAME_SIZE];
	JOB		eJob;
	int		iAttack;
	int		iArmor;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iLevel;
	int		iExp;
	int		iGold;
	PITEM	strItem[ITEM_SIZE];		//아이템을 장착할 수 있는 공간 추가 
}PLAYER, *PPLAYER;

typedef struct _tagMonster
{
	char	strName[NAME_SIZE];
	int		iAttack;
	int		iArmor;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iLevel;
	int		iExp;
	int		iGold;
}MONSTER, *PMONSTER;

static int InputInt()
{
	int	iInput;
	cin >> iInput;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return UINT_MAX;
	}

	return iInput;
}

static void InitItemList(PITEMLIST pList)
{
	memset(pList, 0, sizeof(ITEMLIST));
	pList->pBegin = new ITEMNODE;
	pList->pEnd = new ITEMNODE;

	memset(pList->pBegin, 0, sizeof(ITEMNODE));
	memset(pList->pEnd, 0, sizeof(ITEMNODE));

	//linking two nodes(begin, end)
	pList->pBegin->pNext = pList->pEnd;
	pList->pEnd->pPrev = pList->pBegin;
}

static void AddItemList(PITEMLIST pList, PITEMNODE pNode)
{
	PITEMNODE	pLast = pList->pEnd->pPrev; // looking for the last one among valuable nodes(except the end node)

	pLast->pNext = pNode;
	pNode->pPrev = pLast;

	pList->pEnd->pPrev = pNode;	//pNode becomes newly the last node
	pNode->pNext = pList->pEnd;

	++pList->iCount; //iCOunt = iCount+1
}

static void ReleaseItemList(PITEMLIST pList)
{
	PITEMNODE	pNode = pList->pBegin;

	while (pNode)
	{
		PITEMNODE	pNext = pNode->pNext;
		SAFE_DELETE(pNode);
		pNode = pNext;
	}
}

static void DisplayItemInfo(PITEM pItem)
{
	cout << "이름 : " << pItem->strName << "\t종류 : ";
	switch (pItem->eType)
	{
	case IT_WEAPON:
		cout << "무기" << endl;
		cout << "공격력 : ";
		break;
	case IT_ARMOR:
		cout << "방어구" << endl;
		cout << "방어력 : ";
		break;
	}

	cout << pItem->iOption << endl;
	cout << "구매가격 : " << pItem->iPrice << "\t판매가격 : " << pItem->iSell << endl;
}


extern PPLAYER	g_pPlayer;
extern PINVENTORY	g_pInventory;