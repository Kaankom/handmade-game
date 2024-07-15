#include <windows.h>

LRESULT CALLBACK MainWindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;

    switch (uMsg) {
		case WM_SIZE:
		{
			OutputDebugStringA("WM_SIZE\n");
		} break;
		case WM_DESTROY:
		{
			OutputDebugStringA("WM_DESTROY\n");
		} break;
		case WM_CLOSE:
		{
			OutputDebugStringA("WM_CLOSE\n");
		} break;
		case WM_PAINT:
		{
			PAINTSTRUCT Paint;
			HDC DeviceContext = BeginPaint(hwnd, &Paint);
			int X = Paint.rcPaint.left;
			int Y = Paint.rcPaint.top;
			int Width = Paint.rcPaint.right - Paint.rcPaint.left;
			int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
			PatBlt(DeviceContext, X, Y, Width, Height, WHITENESS);
			EndPaint(hwnd, &Paint);
		} break;
		case WM_ACTIVATEAPP:
		{
			OutputDebugStringA("WM_ACTIVEAPP\n");
		} break;
		default:
		{
			//OutputDebugStringA("DEFAULT\n");
			Result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		} break;
    }
	return(Result);
}

int CALLBACK WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,
                     int nShowCmd)
{
	WNDCLASS WindowClass = {};
	WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	WindowClass.lpfnWndProc = MainWindowCallback;
	WindowClass.hInstance = hInstance;
	//WindowClass.hIcon = ;
	WindowClass.lpszClassName = "HandmadeGameWindowClass";

	if (RegisterClass(&WindowClass))
	{
		HWND WindowHandle = CreateWindowExA(0, WindowClass.lpszClassName, "HandmadeHero", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);
		if (WindowHandle)
		{
			MSG Message;
			for (;;)
			{
				BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
				if(MessageResult > 0)
				{
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}
				else
				{
					break;
				}
			}

		}
	}
	else
	{}


	return(0);
}
