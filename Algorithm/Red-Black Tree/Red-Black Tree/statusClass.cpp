#include"define.h"


statusClass::statusClass(LPCWSTR ClassName, LPCWSTR Title)
{
	IsWCInit = false;
	IsCreate = false;
	hWnd = pWnd = nullptr;
	g_hInst = nullptr;
	winSize = { 0, 0 };
	lstrcpy(szClassName, ClassName);	//������ Ŭ���� �̸�
	lstrcpy(szTitle, Title);			//Ÿ��Ʋ �ٿ� ��µ� ���ڿ�
}

statusClass::statusClass(LPCWSTR ClassName, LPCWSTR Title,
	int x, int y, WNDPROC WndProc)
{
	IsWCInit = false;
	IsCreate = false;
	hWnd = pWnd = nullptr;
	g_hInst = nullptr;
	lstrcpy(szClassName, ClassName);	//������ Ŭ���� �̸�
	lstrcpy(szTitle, Title);			//Ÿ��Ʋ �ٿ� ��µ� ���ڿ�
	winSize = { x, y };

}

void statusClass::SetWindowClass(
	WNDPROC WndProc,
	HINSTANCE hInst,
	UINT style,
	LPCWSTR Icon){
	
	if (IsWCInit)
		return;
	g_hInst = hInst;
	IsWCInit = ON;

	wc.cbSize = sizeof(WNDCLASSEX);

	wc.lpfnWndProc = WndProc;
	Proc = WndProc;
	wc.style = style;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_hInst;
	wc.hIcon = LoadIcon(g_hInst, Icon);
	wc.hCursor = LoadCursor(g_hInst, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(g_hInst, Icon);

	//------------------------------------------------------ :: ������ Ŭ������ ����Ѵ�.
	RegisterClassEx(&wc);							//   :: ������ Ŭ���� ���

}
void statusClass::CreateWnd(DWORD SetType, POINT wndPos, POINT wndSize,
	bool IsCaption, HWND pwnd)
{
	POINT
		ws,
		wp;
	RECT
		getWinSize;
	

	if (IsPOINT(winSize, { 0, 0 }) && IsPOINT(wndSize, winSize))
		ws = winSize = wndSize = wndPos;
	else if (IsPOINT(winSize, { 0, 0 }) && !IsPOINT(wndSize, winSize))
		ws = winSize = wndSize;

	if (!IsPOINT(wndPos, P_default))
		wp = wndPos;
	else if (!pwnd)
	{
		GetWindowRect(GetDesktopWindow(), &getWinSize);
		wp = { (getWinSize.right - wndSize.x) / 2, (getWinSize.bottom - wndSize.y) / 2 };
	}
	else
		wp = { 0, 0 };

	if (IsCaption)
		ws = { GetSystemMetrics(SM_CXFRAME),
		GetSystemMetrics(SM_CYFRAME)
		+ GetSystemMetrics(SM_CYCAPTION) };
	else
		ws = { 0, 0 };

	if (IsCaption)
		ws = P_plus(ws, wndSize);
	else if (IsPOINT(wndSize, P_default))
		if (IsCaption)
			ws = P_plus(ws, winSize);
		else
			ws = winSize;
	else
		ws = wndSize;

	if (SetType == I_default)
		SetType = WS_CAPTION | WS_SYSMENU |
		WS_MINIMIZEBOX;// | WS_THICKFRAME;

	pWnd = pwnd;
	hWnd = CreateWindow(
		szClassName,									//������ Ŭ���� �̸�
		szTitle,												//Ÿ��Ʋ �ٿ� ��µ� ���ڿ�, �տ��� ������
		SetType,											//������ ��Ÿ��, �տ��� ����
		wp.x,													//������ ���� ����� X ��ǥ
		wp.y,													//������ ���� ����� Y ��ǥ
		ws.x,													//�������� ��
		ws.y,													//�������� ����
		pWnd,												//�θ� �ڵ��� ����
		NULL,												//�޴�, Ȥ�� �ڽ� �������� �ĺ���
		g_hInst,												//�����츦 ������ �ν��Ͻ� �ڵ�,  WinMain�� ù��° ����
		NULL												//CREATESTRUCT ����ü�� ���� ���޵Ǵ� ��
		);
}