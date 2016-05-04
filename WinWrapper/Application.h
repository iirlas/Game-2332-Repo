//-------------------------------------------------------------------------
// Author: Issac Irlas
//-------------------------------------------------------------------------

#pragma once

#if !defined(_APPLICATION_H_)
#define _APPLICATION_H_
#define WS_LOCKEDWINDOW     (WS_OVERLAPPEDWINDOW&~WS_THICKFRAME)
#include "Utilities\InstanceMonitor.h"
#include "Utilities\Rect.h"
#include "Utilities\TTypes.h"
#include "Utilities\Logger.h"

// Window framework class
class Application
{
   //======================================================================
   // Removal of default Copy Constructor and Assignment operator
   Application ( const Application& other );
   Application& operator= ( const Application& other );
private:

   //=======================================================================
   // The Window Processor for windows specific message.
   // If a message is not defined by the class then the 
   // defaultWinProc is called.
   friend LRESULT CALLBACK	WndProc ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

   //=======================================================================
   // Registers the windows class with this class's resources. 
   // Note: Methods with the prefix of "resource" are used in registation;
   //       exception for resourceAccelTable() which is call in start().
   bool registerClass ();

   //=======================================================================
   // Creates the window and setup the window size, client size, and assigns 
   // this class's pointer to the UserData section of the HWnd.
   bool setupWindow ( DWORD style );

public:

   //=======================================================================
   //
   static void enableCRTHeapDebugging ( bool maxImpact );

   //=======================================================================
   //
   static void breakOnCRTAlloc ( int n );

   //=======================================================================
   // Default Constructor.
   Application ();

   //=======================================================================
   // Default Destructor the is propery inheritable.
   virtual ~Application ();

   //=======================================================================
   // The entry point for the application.
   // Pass the _tWinMain's arguments to this function to start the program.
   // Note: This will setup the application by calling init, then calling 
   //       start.
   int winMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
      LPTSTR    lpCmdLine, int       nCmdShow );

protected:
   //=======================================================================
   // A type definition for the message processor member function pointer.
   typedef LRESULT (Application::*MsgProc)( WPARAM wParam, LPARAM lParam );

   //=======================================================================
   // Initializes the application and calls preInit, preWindow, and postInit
   // at their respected time for more detailed initialization for derived class.
   bool init ( HINSTANCE hInstance, DWORD style );

   //=======================================================================
   // Assigns the AccelTable, shows the window, and enters the message loop. 
   // NOTE: During the message loop, preMessage, postMessage, and update
   //       will be called at their respected times.
   //       When the loop is exited, end will be called for cleanup.
   int start ( int nShowCmd );

   //=======================================================================
   // Ends the Application by destroying the window and unregistering the
   // window class. When called, preEnd, and postEnd will be called at 
   // thier respected times.
   void end ();

   //=======================================================================
   // The hInstance for this application
   HINSTANCE instance ();

   //=======================================================================
   // The current opened window for this application
   HWND window ();

   //=======================================================================
   // The size and position of the current window.
   const Rect& transform ();

   //=======================================================================
   // The size and position of the current window's client area.
   const Rect& viewport ();

   //=======================================================================
   // An overridable method that is called prior to initialization.
   // Note: This gives the application its default behavior, 
   //       not recommened to override.
   virtual bool preInit ( HINSTANCE hInstance );

   //=======================================================================
   // An overridable method that is called prior to window creation.
   virtual bool preWindow ();

   //=======================================================================
   // An overridable method that is called after initialization and window
   // creation.
   virtual bool postInit ();

   //=======================================================================
   // An overridable method that is called prior to processing a message.
   virtual void preMessage ();

   //=======================================================================
   // An overridable method that is called after processing a message.
   virtual void postMessage ();

   //=======================================================================
   // An overridable method that is called on the idle time of 
   // processing messages.
   // Note: This method is called any idle time, so any functionilty in this
   //       method will be called continiously without delay. 
   //       Use Timer in "Utilities\Timer.h" to handle this.
   virtual void update ();

   //=======================================================================
   // An overridable method that is called prior to the application exiting.
   virtual void preDestroy ();

   //=======================================================================
   // An overridable method that is called after the application exited.
   virtual void postDestroy ();

   //=======================================================================
   // Binds a message processor method to a window's message.
   // Use this to handle a specific message via a method.
   // Note: Method Must follow the protype:
   //       LRESULT onSomeMessage ( WPARAM wParam, LPARAM lParam );
   //       and to bind the function, you must cast it to the typedef MsgProc
   //       as to the following: 
   //       bind( (MsgProc)(&DerivedClass::onSomeMessage), WM_SOMEMESSAGE );
   bool bind ( MsgProc messageProcessor, UINT messageType );

   //=======================================================================
   // Resizes the viewport to the transform.
   // Note: This also resizes the transform to the current window size.
   void resizeViewportToTransform ();

   //=======================================================================
   // Resizes the viewport to the given position and size.
   // Note: This also resizes the transform to the current window size.
   void resizeViewportTo ( int x, int y, int width, int height );

   //=======================================================================
   // Used to exit the message loop and quit the application.
   // Note: Use this instead of DestoryWindow beause the window is destroyed 
   //       before preExit is called.
   void quit ();

   //=======================================================================
   // An overridable method that is call on the WM_CLOSE window's message.
   virtual LRESULT onClose ( WPARAM wParam, LPARAM lParam );

   //=======================================================================
   // The starting style for the window.
   virtual inline DWORD style ()
   {
      return WS_LOCKEDWINDOW;
   }

   //=======================================================================
   // The starting title for the window.
   virtual inline LPCTSTR startTitle ()
   {
      return _T("Default Application Title");
   }

   //=======================================================================
   // The starting x position of the window.
   virtual inline int startTransX ()
   {
      return CW_USEDEFAULT;
   }

   //=======================================================================
   // The starting y position of the window.
   virtual inline int startTransY ()
   {
      return 0;
   }

   //=======================================================================
   // The starting width of the window's client area.
   virtual inline int startTransWidth ()
   {
      return CW_USEDEFAULT;
   }

   //=======================================================================
   // The starting height of the window's client area.
   virtual inline int startTransHeight ()
   {
      return 0;
   }

   //=======================================================================
   // The resource for the class's style.
   // Used during class registration.
   // For more information view Win32 API WNDCLASS structure: style.
   virtual inline UINT resourceStyle ()
   { 
      return CS_HREDRAW | CS_VREDRAW; 
   }

   //=======================================================================
   // The resource for the class's number of extra bytes in the window's class.
   // Used during class registration. 
   // For more information view Win32 API WNDCLASS structure: cbClsExtra.
   virtual inline int resourceCLSExtra ()
   { 
      return 0; 
   }

   //=======================================================================
   // The resource for the class's number of extra bytes in the hWnd.
   // Used during class registration.
   // For more information view Win32 API WNDCLASS structure: cbWndExtra.
   virtual inline int resourceWndExtra ()
   { 
      return 0;
   }

   //=======================================================================
   // The resource for the window's main Icon.
   // Used during class registration.
   // For more information view Win32 API WNDCLASS structure: hIcon.
   virtual inline HICON resourceIcon ()
   { 
      return 0; 
   }
   //=======================================================================
   virtual inline int resourceIconID ()
   { 
      return -1;
   }

   //=======================================================================
   // The resource for the mouse's cursor.
   // Used during class registration.
   // For more information view Win32 API WNDCLASS structure: hCursor.
   virtual inline HCURSOR resourceCursor ()
   { 
      return LoadCursor( NULL, IDC_ARROW );
   }
   //=======================================================================
   virtual inline int resourceCursorID ()
   { 
      return -1;
   }

   //=======================================================================
   // The resource for the window's client area background.
   // Used during class registration.
   // For more information view Win32 API WNDCLASS structure: hbrBackground.
   virtual inline HBRUSH resourceBackground ()  
   { 
      return (HBRUSH)(COLOR_WINDOW+1);
   }

   //=======================================================================
   // The resource for the window's menu.
   // Used during class registration.
   // For more information view Win32 API WNDCLASS structure: lpszMenuName.
   virtual inline LPCTSTR resourceMenu ()
   { 
      return NULL;
   }
   //=======================================================================
   virtual inline int resourceMenuID ()
   { 
      return -1;
   }

   //=======================================================================
   // The resource for the class's registration name.
   // Used during class registration.
   // For more information view Win32 API WNDCLASS structure: lpszClassName.
   // Note: Recommend to override for any derived application.
   virtual inline LPCTSTR resourceClassName ()
   {
      return _T("DEFAULT_WINDOWS_WRAPPER_CLASS");
   }

   //=======================================================================
   // The resource for the window's icon(small).
   // Used during class registration.
   // For more information view Win32 API WNDCLASS structure: hIconSm.
   virtual inline HICON resourceIconSmall ()
   { 
      return 0;
   }
   //=======================================================================
   virtual inline int resourceIconSmallID ()
   { 
      return -1;
   }

   //=======================================================================
   // The resource for the window's Accel Table.
   // For more information view Win32 API TranslateAccelerator.
   virtual inline HACCEL resourceAccelTable () 
   { 
      return 0; 
   }

   //Set the main window title
   void winSetTitle (tstring title);

private:
   //class variables
   static HINSTANCE    ourHInstance;
   static bool         ourClassIsRegistered;
   static unsigned int ourSignature;

   //member variables
   bool            myAppIsRunning;
   unsigned int    mySignature;
   HWND            myHWnd;
   InstanceMonitor myInstanceMonitor;
   MsgProc         myMessageProcessors[USHRT_MAX];
   Rect            myViewport;
   Rect            myTransform;
};
#endif //_APPLICATION_H_


