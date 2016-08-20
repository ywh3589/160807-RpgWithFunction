
#include "Core.h"

/*
160814 숙제
인벤토리에 있는 아이템을 플레이어가 장착하고 아이템의 능력치를 전투시 적용하는 코드를 만들어보자.
*/

int main()
{
	// 전체 게임을 초기화한다.
	if (!Init())
		return 0;

	Run();

	Release();

	return 0;
}
