#include "stdafx.h"
#include "Application.h"
#include "Utilities\Logger.h"
#include <assert.h>

HINSTANCE Application::ourHInstance = NULL;
bool Application::ourClassIsRegistered = false;
unsigned int Application::ourSignature = (
   ((unsigned int)'A' << 24) |
   ((unsigned int)'P' << 16) |
   ((unsigned int)'P' << 8)  |
   ((unsigned int)'L'));

//=======================================================================
//friend
LRESULT CALLBACK WndProc ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
   Application* app = (Application*)GetWindowLongPtr ( hWnd, GWLP_USERDATA );
   if ( app && !IsBadReadPtr( &app->mySignature, sizeof(app->mySignature) ) && 
      app->mySignature == Application::ourSignature )
   {
      // update transform and viewport.
      if ( message == WM_MOVE || message == WM_SIZE )
      {
         GetWindowRect( hWnd, &app->myTransform );
         GetClientRect( hWnd, &app->myViewport );
      }
      // someone called DestroyWindow instead of quit.
      if ( message == WM_DESTROY && app->myAppIsRunning )
      {
         app->myAppIsRunning = false;
      }
      if ( !!app->myMessageProcessors[message] )
      {
         // call user defined message processors.
         return (app->*(app->myMessageProcessors[message]))( wParam, lParam );
      }
   }
   return DefWindowProc(hWnd, message, wParam, lParam);
}

//=======================================================================
void Application::enableCRTHeapDebugging ( bool maxImpact )
{
#ifdef _DEBUG
   int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG ) | _CRTDBG_LEAK_CHECK_DF;

   // _CRTDBG_CHECK_ALWAYS_DF can SERIOUSLY slow execution, but breakpoints immediately on heap corruption
   if ( maxImpact )
      flag |= _CRTDBG_CHECK_ALWAYS_DF;

   _CrtSetDbgFlag(flag);

   // NOTE: This allocation is INTENTIONALLY leaked.  It should show up in the output window at program 
   // termination.  Any allocation #'s LESS than this can be ignored: microsoft bugs in the CRT.
   // It shows up as a "data: <    > DE AD BE EF", i.e., "DEAD BEEF"
   int* iTestDebug = new int( 0xEFBEADDE );

   OutputDebugString( _T("\n\
                         ******************************************************\n\
                         CRT DEBUG MODE ENABLED\n\
                         After program exits, review debug output window\n\
                         for leaks and other heap corruption information\n\
                         EXPECT ONE INTENTIONAL LEAK:\n\
                         {nnn} normal block at 0xXXXXXXXX, 4 bytes long\n\
                         Data: <    > DE AD BE EF\n\
                         Any allocation number < {nnn} can be ignored\n") );

   if ( maxImpact )
      OutputDebugString( _T(">>> MAX HEAP CHECKING ENABLED: EXPECT SLOW EXECUTION <<<\n") );

   OutputDebugString( _T("\
                         ******************************************************\n\n"));

#endif

   // For Reference: These could be used to expand upon the debugging
   // Store current heap state
   //_CrtMemState  memState;
   //_CrtMemCheckpoint( &memState );

   // Dump allocations since given checkpoint
   // _CrtMemDumpAllObjectsSince( &memState );

   // _CrtDumpMemoryLeaks(); immediate memory dump report to output window

}

//=======================================================================
void Application::breakOnCRTAlloc ( int n )
{
#ifdef _DEBUG
   _CrtSetBreakAlloc( n ); 
#endif
}

//=======================================================================
//private
bool Application::registerClass ()
{
   WNDCLASSEX wcex;
   wcex.cbSize          = sizeof(WNDCLASSEX);
   wcex.style			   = resourceStyle();
   wcex.lpfnWndProc	   = WndProc;
   wcex.cbClsExtra	   = resourceCLSExtra();
   wcex.cbWndExtra	   = resourceWndExtra();
   wcex.hInstance		   = instance();
   wcex.hIcon			   = (resourceIconID() == -1 ? resourceIcon() : LoadIcon( instance(), MAKEINTRESOURCE( resourceIconID() )));
   wcex.hCursor		   = (resourceCursorID() == -1 ? resourceCursor() : LoadCursor( NULL, MAKEINTRESOURCE( resourceCursorID() )));
   wcex.hbrBackground	= resourceBackground();
   wcex.lpszMenuName	   = (resourceMenuID() == -1 ? resourceMenu() : MAKEINTRESOURCE( resourceMenuID() ));
   wcex.lpszClassName   = resourceClassName();
   wcex.hIconSm		   = (resourceIconSmallID() == -1 ? resourceIconSmall() : LoadIcon( instance(), MAKEINTRESOURCE( resourceIconSmallID() ) ));
   return (RegisterClassEx(&wcex) != NULL);
}

//=======================================================================
//private
bool Application::setupWindow ( DWORD style )
{
   if ( myHWnd )
   {
      Logger::message( _T("A window was already created.") );
      return false;
   }
   myHWnd = CreateWindowEx ( 0, resourceClassName(), startTitle(), style, 
      startTransX(), startTransY(), 
      startTransWidth(), startTransHeight(),
      NULL, NULL, instance(), NULL );
   if ( !myHWnd )
   {
      Logger::message( _T("Unable to create window.") );
      return false;
   }
   SetWindowLongPtr( myHWnd, GWLP_USERDATA, (LONG)this );
   GetWindowRect( window(), &myTransform );
   GetClientRect( window(), &myViewport );
   resizeViewportToTransform();
   return true;
}

//=======================================================================
Application::Application ()
:mySignature(ourSignature), myHWnd(NULL), myInstanceMonitor(), myViewport(), myTransform()
{
   ZeroMemory( myMessageProcessors, USHRT_MAX * sizeof(*myMessageProcessors) );  
}
//=======================================================================
Application::~Application ()
{
}

//=======================================================================
int Application::winMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                          LPTSTR    lpCmdLine, int       nCmdShow )
{
   if ( !init( hInstance, style() ) )
   {
      Logger::message( _T("Unable to initialize the application\n") );
      return E_FAIL;
   }
   return start( nCmdShow );
}

//=======================================================================
void Application::quit ()
{
   myAppIsRunning = false;
   PostQuitMessage(0);
}

//=======================================================================
//protected
bool Application::init ( HINSTANCE hInstance, DWORD style )
{
   myInstanceMonitor.create( resourceClassName() );
   if ( !myInstanceMonitor.isThisTheOnlyInstance()  )
   {
      Logger::message( _T("More then one type of this application is running.") );
      return false;
   }

   if ( !preInit( hInstance ) )
   {
      return false;
   }

   if ( !ourClassIsRegistered )
   {
      Application::ourHInstance = hInstance;
      ourClassIsRegistered = registerClass();
   }

   if ( !preWindow() || !setupWindow( style ) || !postInit() )
   {
      return false;
   }

   return (GetWindowLongPtr( myHWnd, GWLP_USERDATA ) == (LONG)this);
}



//=======================================================================
//protected
int Application::start ( int nShowCmd )
{
   MSG msg = {0};
   HACCEL hAccelTable = resourceAccelTable();
   ShowWindow( myHWnd, nShowCmd );
   UpdateWindow( myHWnd );
   myAppIsRunning = true;
   while ( myAppIsRunning )
   {
      if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) && 
         !TranslateAccelerator(msg.hwnd, hAccelTable, &msg) )
      {
         preMessage();
         TranslateMessage(&msg);
         DispatchMessage(&msg);
         postMessage();
      }
      update();
   }
   end();
   PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
   return (int) msg.wParam;
}

//=======================================================================
//protected
void Application::end ()
{
   if ( myHWnd != NULL )
   {
      preDestroy();
      SetWindowLongPtr( myHWnd, GWLP_USERDATA, NULL );
      DestroyWindow( myHWnd );
      myHWnd = NULL;
      UnregisterClass( resourceClassName(), instance() );
      postDestroy();
   }
}

//=======================================================================
//protected
HINSTANCE Application::instance ()
{ 
   return ourHInstance;
}

//=======================================================================
//protected
HWND Application::window ()
{ 
   return myHWnd; 
}

//=======================================================================
//protected
const Rect& Application::transform ()
{ 
   return myTransform; 
}

//=======================================================================
//protected
const Rect& Application::viewport ()
{ 
   return myViewport; 
}


//=======================================================================
//protected
bool Application::preInit ( HINSTANCE hInstance )
{
   return bind( &Application::onClose, WM_CLOSE );
}

//=======================================================================
//protected
bool Application::preWindow ()
{
   return true;
}

//=======================================================================
//protected
bool Application::postInit ()
{
   return true; 
}

//=======================================================================
//protected
void Application::preMessage ()
{
}

//=======================================================================
//protected
void Application::postMessage ()
{
}

//=======================================================================
//protected
void Application::update ()
{
}

//=======================================================================
//protected
void Application::preDestroy ()
{
}

//=======================================================================
//protected
void Application::postDestroy ()        
{
}

//=======================================================================
//protected
bool Application::bind ( MsgProc messageProcessor, UINT messageType )
{
   if ( messageType < USHRT_MAX && myMessageProcessors[messageType] == NULL )
   {
      myMessageProcessors[messageType] = messageProcessor;
   }
   return (messageType < USHRT_MAX) && (myMessageProcessors[messageType] == messageProcessor);
}

//=======================================================================
//protected
void Application::resizeViewportToTransform ()
{
   POINT differ;
   differ.x = transform().width() - viewport().width();
   differ.y = transform().height() - viewport().height();
   MoveWindow( window(), transform().x(), transform().y(),
      transform().width() + differ.x, 
      transform().height() + differ.y, TRUE );
}

//=======================================================================
//protected
void Application::resizeViewportTo ( int x, int y, int width, int height )
{
   if ( x == CW_USEDEFAULT )
   {
      x = transform().x();
      y = transform().y();
   }
   MoveWindow( window(), x, y, width, height, TRUE );
   GetWindowRect( window(), &myTransform );
   GetClientRect( window(), &myViewport );
   resizeViewportToTransform();
}

//=======================================================================
//protected
LRESULT Application::onClose ( WPARAM wParam, LPARAM lParam )
{
   quit();
   return wParam;
}


//---------------------------------------------------------------------------------------- 
// Change the main window title to the specified string
//
void Application::winSetTitle ( tstring title )
{
   ::SetWindowText( window(), title.c_str() );
}

//---------------------------------------------------------------------------------------- 