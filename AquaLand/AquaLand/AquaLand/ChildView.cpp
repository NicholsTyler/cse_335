
/**
 * \file ChildView.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include "framework.h"
#include "AquaLand.h"
#include "ChildView.h"
#include "FishBeta.h"
#include "FishAngler.h"
#include "FishMagikarp.h"
#include "DecorCastle.h"
#include "DoubleBufferDC.h"
#include "Aquarium.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;
using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/// Initial fish X location
const int InitialX = 200;

/// Initial fish Y location
const int InitialY = 200;

 /**
  * Constructor
  */
CChildView::CChildView()
{
	srand((unsigned int)time(nullptr));
}

/**
 * Destructor
 */
CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_ADDFISH_BETAFISH, &CChildView::OnAddfishBetafish)
	ON_COMMAND(ID_ADDFISH_ANGLERFISH, &CChildView::OnAddfishAnglerfish)
	ON_COMMAND(ID_ADDFISH_MAGIKARPFISH, &CChildView::OnAddfishMagikarpfish)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ADDDECOR_CASTLE, &CChildView::OnAdddecorCastle)
	ON_COMMAND(ID_FILE_SAVEAS, &CChildView::OnFileSaveas)
	ON_COMMAND(ID_FILE_OPEN32777, &CChildView::OnFileOpen)
	ON_WM_TIMER()
END_MESSAGE_MAP()



/**
 * This function is called before the window is created.
 * \param cs A structure with the window creation parameters
 * \returns TRUE
 */
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

/**
 * This function is called to draw in the window.
 *
 * This function is called in response to a drawing message
 * whenever we need to redraw the window on the screen.
 * It is responsible for painting the window.
 */
void CChildView::OnPaint() 
{
	CPaintDC paintDC(this);     // device context for painting
	CDoubleBufferDC dc(&paintDC); // device context for painting
	Graphics graphics(dc.m_hDC);

	mAquarium.OnDraw(&graphics);

	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
		 * Initialize the elapsed time system
		 */
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);
	}

	/*
	 * Compute the elapsed time since the last draw
	 */
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;

	mAquarium.Update(elapsed);
}


/**
 * Function called by the menu option "Add Fish -> Beta Fish"
 */
void CChildView::OnAddfishBetafish()
{
	auto fish = make_shared<CFishBeta>(&mAquarium);
	double initialX = ((double)rand() / RAND_MAX) * fish.get()->GetAquarium()->GetWidth();
	double initialY = ((double)rand() / RAND_MAX) * fish.get()->GetAquarium()->GetHeight();
	fish->SetLocation(initialX, initialY);
	mAquarium.Add(fish);
	Invalidate();
}

/**
 * Function called by the menu option "Add Fish -> Angler Fish"
 */
void CChildView::OnAddfishAnglerfish()
{
	auto fish = make_shared<CFishAngler>(&mAquarium);
	double initialX = ((double)rand() / RAND_MAX) * fish.get()->GetAquarium()->GetWidth();
	double initialY = ((double)rand() / RAND_MAX) * fish.get()->GetAquarium()->GetHeight();
	fish->SetLocation(initialX, initialY);
	mAquarium.Add(fish);
	Invalidate();
}

/**
 * Function called by the menu option "Add Fish -> Magikarp Fish"
 */
void CChildView::OnAddfishMagikarpfish()
{
	auto fish = make_shared<CFishMagikarp>(&mAquarium);
	double initialX = ((double)rand() / RAND_MAX) * fish.get()->GetAquarium()->GetWidth();
	double initialY = ((double)rand() / RAND_MAX) * fish.get()->GetAquarium()->GetHeight();
	fish->SetLocation(initialX, initialY);
	mAquarium.Add(fish);
	Invalidate();
}

/**
 * Function called by the menu option "Add Decor -> Castle"
 */
void CChildView::OnAdddecorCastle()
{
	auto decor = make_shared<CDecorCastle>(&mAquarium);
	decor->SetLocation(InitialX, InitialY);
	mAquarium.Add(decor);
	Invalidate();
}

/**
 * Called when there is a left mouse button press
 * \param nFlags Flags associated with the mouse button press
 * \param point Where the button was pressed
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	mGrabbedItem = mAquarium.HitTest(point.x, point.y);
	// If we clicked on an item
	if (mGrabbedItem != nullptr)
	{
		mAquarium.ToEnd(mGrabbedItem);
	}
}


/**
 * Called when the left mouse button is released
 * \param nFlags Flags associated with the mouse button release
 * \param point Where the button was pressed
 */
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	OnMouseMove(nFlags, point);
}


/**
 * Called when the mouse is moved
 * \param nFlags Flags associated with the mouse movement
 * \param point Where the button was pressed
 */
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{
		// If an item is being moved, we only continue to 
		// move it while the left button is down.
		if (nFlags & MK_LBUTTON)
		{
			mGrabbedItem->SetLocation(point.x, point.y);
		}
		else
		{
			// When the left button is released, we release the
			// item.
			mGrabbedItem = nullptr;
		}

		// Force the screen to redraw
		Invalidate();
	}
}

/**
 * Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context
 * \returns FALSE
 */
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

/**
 * This function is called when a File Save as menu item is selected.
 *
 * It saves the aquarium to a file.
 */
void CChildView::OnFileSaveas()
{
	CFileDialog dlg(false,  // false = Save dialog box
		L".aqua",           // Default file extension
		nullptr,            // Default file name (none)
		OFN_OVERWRITEPROMPT,      // Flags (warn it overwriting file)
		L"Aquarium Files (*.aqua)|*.aqua|All Files (*.*)|*.*||"); // Filter

	if (dlg.DoModal() != IDOK)
		return;

	wstring filename = dlg.GetPathName();

	mAquarium.Save(filename);
}


/**
 * This function is called when an File Open menu item is selected.
 *
 * It loads the aquarium from a file.
 */
void CChildView::OnFileOpen()
{
	CFileDialog dlg(true,  // true = Open dialog box
		L".aqua",           // Default file extension
		nullptr,            // Default file name (none)
		0,    // Flags
		L"Aquarium Files (*.aqua)|*.aqua|All Files (*.*)|*.*||");  // Filter
	if (dlg.DoModal() != IDOK)
		return;

	wstring filename = dlg.GetPathName();

	mAquarium.Load(filename);
	Invalidate();
}


/**
 * Handle timer events
 * \param nIDEvent The timer event ID
 */
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}
