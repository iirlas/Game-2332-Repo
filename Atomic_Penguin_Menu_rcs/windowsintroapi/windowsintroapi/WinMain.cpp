#include <windows.h>
#include "resource.h"

//---------------------------------------------------------------------------
HWND hWnd;
LRESULT CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_GUIDE),
	          hWnd, reinterpret_cast<DLGPROC>(DlgProc));

	return FALSE;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch(Msg)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch(wParam)
		{
		case ID_OK:
			EndDialog(hWndDlg, 0);
			return TRUE;
		}
		break;
	}

	return FALSE;
}





//#include <Windows.h> // standard window.h include
//#include "resource.h"
//
///**  **/
//
//// name of our class and the title
//const char *className = "MyFirstWindow";
//char *title = "Windows API"; 
//const char *className2 = "MySecondWindow";
//char *title2 = "Windows Help Menu"; 
//
//
////global flag for our message loop
//bool running = true;
//
//// handle to the window
//HWND hWnd = NULL; 
//
//bool windowsClosed1 = false; 
//bool windowsClosed2 = false;
//HINSTANCE hInstance;
//
//LRESULT CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
//
//// A windows callback procedure
//LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//   switch(uMsg)
//   {
//      case WM_CLOSE:
//         DestroyWindow(hWnd);
//         return 0;
//
//      case WM_DESTROY:
//         PostQuitMessage(0);
//         running = false; 
//         return 0; 
//
//      case WM_COMMAND:
//      {
//         switch(LOWORD(wParam))
//         {
//            case IDM_EXIT_APP:
//               PostQuitMessage(0);
//               running = false;
//               break;
//
//            case IDM_USER_GUIDE:
//               //DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_ONE), hWnd, NULL);
//               break;
//
//            case ID_OK:
//               EndDialog(hWnd, 0);
//               PostQuitMessage(0);
//               running = false;
//               return TRUE;
//         }
//      }break;
//
//   default:
//      return DefWindowProc(hWnd, uMsg, wParam, lParam);
//
//      return FALSE;
//   }
//}
//
///**
//   This structure contains information about the windows class. 
//   It is used with the RegisterClassEx and describes various aspects of the window.
//**/
////HINSTANCE hInstance - A handle to the current instance of application
////HINSTANCE hPrevInstance - A handle to the previous instance of the applicaiton
////LPSTR lpCmdLine - The command line for the application, exluding the program name...
////int nCmdShow - Controls how the window will be shown
//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//   WNDCLASSEX WndEx;
//   MSG        msg;
//
//   WndEx.cbSize = sizeof(WNDCLASSEX); //Size, in bytes, of this structure
//   WndEx.style  = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // the class style
//
//   WndEx.lpfnWndProc = (WNDPROC)WndProc; // A pointer to the window proccedure
//
//   WndEx.cbClsExtra  = 0; //number of extra bytes to allocate following the window-class structure
//
//   WndEx.cbWndExtra  = 0; // The number of extra bytes to allocate following the window instance
//
//   WndEx.hIcon       = LoadIcon(NULL, IDI_APPLICATION); // A handle to the class icon
//
//   WndEx.hCursor     = LoadCursor(NULL, IDC_ARROW); // A handle to the class cursor
//
//   WndEx.hbrBackground = NULL; // A handle to the class background brush
//
//   WndEx.lpszMenuName = MAKEINTRESOURCE(IDR_MAIN_MENU); // Not using menu now // Now we are using it, creating menu from resource file made using resedit
//   
//   WndEx.lpszClassName = className; // A pointer to a String that contains the class name
//
//   WndEx.hInstance     = hInstance; // A handle to the instance that contains the window procedure for the class
//
//   WndEx.hIconSm       = LoadIcon(NULL, IDI_APPLICATION); // A handle to a small icon that is associated with the window class
//
//   DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_ONE), hWnd, NULL);//reinterpret_cast<DLGPROC>(DlgProc));
//
///**
//Registers the previously set up WNDCLASSEX structure with the class. 
//**/
//   // register the windows class?
//   if(!RegisterClassEx(&WndEx))
//   {
//      MessageBox(NULL, "Failed to register class", "ERROR", MB_OK );//| MB_IConerror);
//      return 0; 
//   }
//
//   // Create the window!!
///** 
//This creates the window and sets up some details about it, such as its position, size, style and it's parent (if any).
//**/
//   // WS_EXAPPWINDOW | WS_EX_WINDOWEDGE - The extended window style
//   // className - A pointer to a string that contains the class name
//   // title - A pointer to a string that contains the title of the window
//   // WS_OVERLAPPEDWINDOW - The style of th ewindow being created? 
//   // CW_USEDEFAULT - initial x, y position of the window
//   // x, y size of the window
//   // NULL - A handle to the parent or owner window
//   // NULL - A handle to a menu
//   // hInstance - A handle to the instance of the window
//   // NULL - iParam
//   if(!(hWnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, 
//                              className, 
//                              title, 
//                              WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
//                              CW_USEDEFAULT, 
//                              CW_USEDEFAULT, 
//                              460, 
//                              340, 
//                              NULL, 
//                              NULL, 
//                              hInstance, 
//                              NULL)))
//   {
//      MessageBox(NULL, "Failed to create the window", "ERROR", MB_OK); //| MB_IConerror); 
//      return 0; 
//   }
//   
//   // The window is initially hidden, we need to show it
//   ShowWindow(hWnd, SW_SHOW);
//
///** 
//Whenever anything happens to your window, a message is sent. 
//This might be a resize, a create message, a close message etc etc. 
//This message needs to be caught and translated in order to be of any use, 
//this is the job of our message loop, along with our callback procedure. 
//The message loop catches the message and our callback procedure defines how we should act. 
//Here is our callback procedure again. 
//**/
//
//   // The main message loop of program
//   while(running)
//   {
///** 
//The "PeekMessage" function checks whether there are any messages that need to be processed, 
//if there are, then the message is translated and dispatched. 
//In this process, the callback procedure is called so that any messages sent can be caught arbitrarily as described above.
//**/
//      // Are their any message in the message queue
//      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//      {
//         // translate and dispatch the message
//         TranslateMessage(&msg);
//         DispatchMessage(&msg);
//      }
//   }
//   return msg.wParam;
//}
//
//LRESULT CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
//{
//   switch(Msg)
//   {
//   case WM_INITDIALOG:
//      return true;
//
//   case WM_COMMAND:
//      switch(wParam)
//      {
//      case IDOK:
//            EndDialog(hWnd, 0);
//            return true;
//      }
//      break;
//   }
//   return false;
//}
//
