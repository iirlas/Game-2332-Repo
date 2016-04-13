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
//private
bool Application::registerClass ()
{
    WNDCLASSEX wcex;
    wcex.cbSize             = sizeof(WNDCLASSEX);
    wcex.style			    = resourceStyle();
    wcex.lpfnWndProc	    = WndProc;
    wcex.cbClsExtra	        = resourceCLSExtra();
    wcex.cbWndExtra	        = resourceWndExtra();
    wcex.hInstance		    = instance();
    wcex.hIcon			    = resourceIcon();//LoadIcon( instance(), MAKEINTRESOURCE(  ) );
    wcex.hCursor		    = resourceCursor();//LoadCursor( NULL, MAKEINTRESOURCE(  ) );
    wcex.hbrBackground	    = resourceBackground();
    wcex.lpszMenuName	    = resourceMenu();//MAKEINTRESOURCE(  );
    wcex.lpszClassName      = resourceClassName();
    wcex.hIconSm		    = resourceIconSmall();//LoadIcon( instance(), MAKEINTRESOURCE(  ) );
    return (RegisterClassEx(&wcex) != NULL);
}

//=======================================================================
//private
bool Application::setupWindow ( DWORD style )
{
    if ( myHWnd )
    {
        log( _T("A window was already created.") );
        return false;
    }
    myHWnd = CreateWindowEx ( 0, resourceClassName(), startTitle(), style, 
                              startTransX(), startTransY(), 
                              startTransWidth(), startTransHeight(),
                              NULL, NULL, instance(), NULL );
    if ( !myHWnd )
    {
        log( _T("Unable to create window.") );
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
    //destroy();
}

//=======================================================================
int Application::winMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                           LPTSTR    lpCmdLine, int       nCmdShow )
{
    if ( !init( hInstance, WS_LOCKEDWINDOW ) )
    {
        log( _T("Unable to initialize the application\n") );
        return E_FAIL;
    }
    return start( nCmdShow );
}

//=======================================================================
//protected
bool Application::init ( HINSTANCE hInstance, DWORD style )
{
    myInstanceMonitor.create( resourceClassName() );
    if ( !myInstanceMonitor.isThisTheOnlyInstance()  )
    {
        log( _T("More then one type of this application is running.") );
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

        if ( myAppIsRunning )
        {
            update();
        }
    }
    end();
    return (int) msg.wParam;
}

//=======================================================================
//protected
void Application::end ()
{
    if ( myHWnd != NULL )
    {
        preEnd();
        SetWindowLongPtr( myHWnd, GWLP_USERDATA, NULL );
        DestroyWindow( myHWnd );
        myHWnd = NULL;
        UnregisterClass( resourceClassName(), instance() );
        postEnd();
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
void Application::preEnd ()
{
}

//=======================================================================
//protected
void Application::postEnd ()        
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
void Application::quit ()
{
    myAppIsRunning = false;
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