
#include "Inventory.h"

PINVENTORY	g_pInventory = NULL;

bool InitInventory()
{
	g_pInventory = new INVENTORY;
	memset(g_pInventory, 0, sizeof(INVENTORY));

	return true;
}

int SelectInventoryItem()
{
	system("cls");

	cout << "=================== �κ��丮 ===================" << endl;

	for (int i = 0; i < g_pInventory->iItemCount; ++i)
	{
		cout << i + 1 << ". " << endl;
		DisplayItemInfo(g_pInventory->pItem[i]);
		cout << endl;
	}

	cout << "0. �ڷΰ���" << endl;
	cout << "������ �������� �����ϼ��� : ";
	int	iInput = InputInt();

	if (iInput == UINT_MAX || iInput < 0 || iInput > g_pInventory->iItemCount)
		return UINT_MAX;

	return iInput;
}

void RunInventory()
{
	while (true)
	{
		int	iInput = SelectInventoryItem();

		if (iInput == 0)
			break;

		else if (iInput == UINT_MAX)
			continue;
	}
}

void ReleaseInventory()
{
	for (int i = 0; i < g_pInventory->iItemCount; ++i)
	{
		SAFE_DELETE(g_pInventory->pItem[i]);
	}

	SAFE_DELETE(g_pInventory);
}
