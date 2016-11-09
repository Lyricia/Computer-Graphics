#include"define.h"


int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR IpCmdLine,
	int nCmdShow)
{

	MSG msg;			//�޼��� ����ü

	wm.SetWindowClass(WndProc, hInstance, SWC_default_style, MAKEINTRESOURCE(IDRB_ICON));
	pc.SetWindowClass(TreeProc, hInstance, SWC_default_style, MAKEINTRESOURCE(IDRB_ICON));

	wm.CreateWnd(I_default, P_default, { default_winMain.x, default_winMain.y }, true);
	
	if (! wm.hwnd() )						//������ ������ ���� ��
		return(FALSE);			//���α׷� ����
	
	//------------------------------------------------------ :: ������ �����츦 ȭ�鿡 ���
	ShowWindow(wm.hwnd(), nCmdShow);				//�����츦 ȭ�鿡 ��Ÿ����.
	UpdateWindow(wm.hwnd());								//�������� Ŭ���̾�Ʈ ������ ĥ�Ѵ�.
	//------------------------------------------------------ :: �޽��� ���� : ������ ���� �޼��� ť�κ��� �޼����� ���� ó���Ѵ�.

	pc.CreateWnd(WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, { 0, 0 },
		wm.size(), false, wm.hwnd());

	while (1)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{

			if (msg.message == WM_QUIT)
				break;


			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)	// �� ȸ �ʱ�ȭ
{

	switch (uMsg)
	{

	case WM_CREATE:
		// Global Value Setting
		break;

	case WM_LBUTTONDOWN:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MBUTTONDOWN:
		break;
	case WM_CHAR:
		SendMessage(pc.hwnd(), WM_CHAR, wParam, lParam);
		break;
	case WM_DESTROY:

		DestroyWindow(hWnd);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);	//���� �޼����� DefWindowProc()�� ó��
	}

	return 0;
}

/* rbTree view Processure */
LRESULT CALLBACK TreeProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)	// �� ȸ �ʱ�ȭ
{
	HDC										hdc;
	HDC										LayDC;
	HBITMAP								Lay;
	PAINTSTRUCT						ps;

	static rbTree							tree;
	static Node							*pHeight;

	static bool								IsClip = false;
	int											cntHeight;
	TCHAR									msg[100];
	static SIZE							Csize;
	static TCHAR							msg_for_node[20];

	RECT
		tmp = { 0, 0, default_winMain.x, default_winMain.y },
		nodeBox = { -10, -10, 10, 10 },
		rc_for_node = { 50, default_winMain.y - 100, 200, default_winMain.y - 70 },
		rc_for_insert = {	rc_for_node.right + 10, default_winMain.y - 100
								, rc_for_node.right + 75, default_winMain.y - 70 },
		rc_for_delete = {	rc_for_insert.right + 10, default_winMain.y - 100
								, rc_for_insert.right + 75, default_winMain.y - 70 };
	POINT
		rootPos = { default_winMain.x / 2, 50 };

	static POINT
		rembPos = { 0, 0 },
		selPos = { 0, 0 }, 
		Mp;

	static int
		cnt_Insert = 0,
		len_for_node = 0;

		
	switch (uMsg)
	{

	case WM_CREATE:

		//Caret Setting
		CreateCaret(hWnd, NULL, 1, 15);
		// Global Value Setting
		IsClip = false;

		break;

	case WM_MOUSEMOVE:
		Mp.x = LOWORD(lParam);
		Mp.y = HIWORD(lParam);

		if (IsClip)
		{
			rembPos = P_plus(rembPos, P_minus(Mp, selPos));
			selPos = Mp;
			InvalidateRect(hWnd, NULL, false);
		}

		break;

	case WM_LBUTTONDOWN:
		Mp.x = LOWORD(lParam);
		Mp.y = HIWORD(lParam);

		if (PtInRect(&rc_for_node, Mp))
		{
			SetCaretPos(Csize.cx + rc_for_node.left + 5, rc_for_node.top + Csize.cy / 2);
			ShowCaret(hWnd);
			break;
		}
		else
			HideCaret(hWnd);

		if (PtInRect(&rc_for_insert, Mp))
		{
			InsertNode(hWnd, msg_for_node, &tree, &rembPos);
			break;
		}
		if (PtInRect(&rc_for_delete, Mp))
		{
			deleteNode(hWnd, msg_for_node, &tree, &rembPos);
			break;
		}

		selPos = Mp;
		IsClip = true;

		InvalidateRect(hWnd, NULL, false);
		break;

	case WM_MBUTTONDOWN:
		Mp.x = LOWORD(lParam);
		Mp.y = HIWORD(lParam);

		rembPos = { default_winMain.x / 2, 50 };
		InvalidateRect(hWnd, NULL, false);

		break;

	case WM_LBUTTONUP:
		IsClip = false;
		break;

	case WM_RBUTTONDOWN:
	
		int istnode;
		istnode = _wtoi(msg_for_node);
		lstrcpy(msg_for_node, L"");
		istnode = sideStore(3, cnt_Insert + istnode, 999);
		while (cnt_Insert < istnode)
		cnt_Insert = insertSample(cnt_Insert, &tree, &rembPos);

		InvalidateRect(hWnd, NULL, false);
		break;

	case WM_CHAR:
		
		len_for_node = lstrlen(msg_for_node);
		if (len_for_node < input_val_max - 1 && sideCheck(48, wParam, 58))
		{
			msg_for_node[len_for_node] = wParam;//�Է¹�������wParam���ֽ��ϴ�.
			msg_for_node[len_for_node + 1] = 0;

			SendMessage(hWnd, WM_PAINT, wParam, lParam);
			SetCaretPos(Csize.cx + rc_for_node.left + 5, rc_for_node.top + Csize.cy / 2);
			ShowCaret(hWnd);
			InvalidateRect(hWnd, NULL, false);
			break;
		}

		switch (wParam)
		{
			// backspace
		case 8:
			if (len_for_node > 0)
				msg_for_node[len_for_node - 1] = NULL;
			SendMessage(hWnd, WM_PAINT, wParam, lParam);
			SetCaretPos(Csize.cx + rc_for_node.left + 5, rc_for_node.top + Csize.cy / 2);
			ShowCaret(hWnd);
			InvalidateRect(hWnd, NULL, false);
			break;

			// insert
		case 105:
		case 13:
		case 32:
			InsertNode(hWnd, msg_for_node, &tree, &rembPos);
			HideCaret(hWnd);
			break;
			
			// delete
		case 27:
		case 100:
			deleteNode(hWnd, msg_for_node, &tree, &rembPos);
			HideCaret(hWnd);
			break;
		case 113:
			DestroyWindow(hWnd);
			DestroyWindow(wm.hwnd());
			break;
		}
		/*
		wsprintf(msg, L"%d", wParam);
		ErrorMsgBox((char*)msg);
		/**/
		break;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		//	DoubleBuffering
		LayDC = CreateCompatibleDC(hdc);
		Lay = CreateCompatibleBitmap(hdc, default_winMain.x, default_winMain.y);
		SelectObject(LayDC, Lay);
		//	Begin work
		SetBkMode(LayDC, TRANSPARENT);
		SetTextColor(LayDC, RGB(255, 255, 255));

		FillRect(LayDC, &tmp, (HBRUSH)GetStockObject(WHITE_BRUSH));
		//	Drawing Init.
		cntHeight = 0;
		pHeight = tree.root();

		//	Drawing Tree
		if (tree.root() != nullptr)
			DrawTree(LayDC, rootPos, rembPos, cntHeight, pHeight, tree.size(), { 0, 0 });

		//	rembPos View
		SetTextColor(LayDC, RGB(125, 125, 125));
		wsprintf(msg, L"rembPos : %d, %d", rembPos.x, rembPos.y);
		tmp = { default_winMain.x - 350, default_winMain.y - 150, default_winMain.x, default_winMain.y };
//		DrawText(LayDC, msg, -1, &tmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		//		DrawLineBox(LayDC, rc_for_node, RGB(125, 125, 125), RGB(255, 255, 255), 2, DL_FRAME);
		FrameRect(LayDC, &rc_for_node, (HBRUSH)GetStockObject(GRAY_BRUSH));
		SetTextColor(LayDC, RGB(125, 125, 125));
		wsprintf(msg, L"node's key : %s", msg_for_node);
		GetTextExtentPoint32(LayDC, msg, lstrlen(msg), &Csize);
		tmp = R_P_plus(rc_for_node, { 5, 0 });
		DrawText(LayDC, msg, -1, &tmp, DT_VCENTER | DT_SINGLELINE);

		SetTextColor(LayDC, RGB(255, 255, 255));
		DrawLineBox(LayDC, rc_for_insert, RGB(125, 125, 125), RGB(255, 255, 255), 2, DL_FRAME);
		wsprintf(msg, L"insert");
		DrawText(LayDC, msg, -1, &rc_for_insert, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

		DrawLineBox(LayDC, rc_for_delete, RGB(125, 125, 125), RGB(255, 255, 255), 2, DL_FRAME);
		wsprintf(msg, L"delete");
		DrawText(LayDC, msg, -1, &rc_for_delete, DT_VCENTER | DT_CENTER | DT_SINGLELINE);


		SetTextColor(LayDC, RGB(125, 125, 125));
		wsprintf(msg, L"���Է� : Enter, Space, i, [insert] box");
		TextOut(LayDC, rc_for_node.left - 15, rc_for_node.top - 25, msg, lstrlen(msg));
		wsprintf(msg, L"�ݻ��� : Esc, d, [delete] box");
		TextOut(LayDC, rc_for_node.left - 15, rc_for_node.top - 45, msg, lstrlen(msg));
		wsprintf(msg, L"���ؽ�Ʈ�ڽ��� ���ϴ¸�ŭ�� ���� �Է��Ͻ� �� ���콺 ������ ��ư�� ���� ������ ��带 �߰��� �� �ֽ��ϴ�.");
		TextOut(LayDC, rc_for_node.left - 15, rc_for_node.top - 65, msg, lstrlen(msg));
		wsprintf(msg, L"�ݸ��콺 ���� ��ư�� ���� ä �巡���Ͽ� �̵��� �� �ֽ��ϴ�.");
		TextOut(LayDC, rc_for_node.left - 15, rc_for_node.top - 85, msg, lstrlen(msg));
		wsprintf(msg, L"�ݸ��콺 ��� ��ư�� ���� ��Ʈ��带 �� �� �ֽ��ϴ�.");
		TextOut(LayDC, rc_for_node.left - 15, rc_for_node.top - 105, msg, lstrlen(msg));
		wsprintf(msg, L"��Q Ű�� ���α׷��� ������ �� �ֽ��ϴ�.");
		TextOut(LayDC, rc_for_node.left - 15, rc_for_node.top - 125, msg, lstrlen(msg));
		wsprintf(msg, L"�ݱ��� �ؽ�Ʈ���ڿ� Ŀ���� ���� �ʾƵ� Key���� �Է��� �� �ֽ��ϴ�!");
		TextOut(LayDC, rc_for_node.left - 15, rc_for_node.top - 145, msg, lstrlen(msg));


		BitBlt(hdc, 0, 0, default_winMain.x, default_winMain.y, LayDC, 0, 0, SRCCOPY);

		EndPaint(hWnd, &ps);
		DeleteDC(LayDC);
		DeleteObject(Lay);
		break;

	case WM_DESTROY:

		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);	//���� �޼����� DefWindowProc()�� ó��
	}

	return 0;
}