/**
 * \file ViewEdit.cpp
 *
 * \author Charles B. Owen
 */


#include "pch.h"
#include "CanadianExperience.h"
#include "ViewEdit.h"

#include "DoubleBufferDC.h"
#include "MainFrm.h"
#include "Picture.h"
#include "Actor.h"
#include "MachineDlg.h"

/// A scaling factor, converts mouse motion to rotation in radians
const double RotationScaling = 0.02;

using namespace std;
using namespace Gdiplus;

/** Implements ViewEdit and ScrollView
* \return N/A
*/
IMPLEMENT_DYNCREATE(CViewEdit, CScrollView)


BEGIN_MESSAGE_MAP(CViewEdit, CScrollView)
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_MACHINELEFT_DIALOGUEBOX, &CViewEdit::OnMachineleftDialoguebox)
    ON_COMMAND(ID_MACHINERIGHT_DIALOGUEBOX, &CViewEdit::OnMachinerightDialoguebox)
    ON_COMMAND(ID_STARTTIME_SET32809, &CViewEdit::OnStarttimeSetLeft)
    ON_COMMAND(ID_STARTTIME_REMOVE32810, &CViewEdit::OnStarttimeRemoveLeft)
    ON_COMMAND(ID_STARTTIME_SET32813, &CViewEdit::OnStarttimeSetRight)
    ON_COMMAND(ID_STARTTIME_REMOVE32814, &CViewEdit::OnStarttimeRemoveRight)
END_MESSAGE_MAP()

/** Constructor */
CViewEdit::CViewEdit()
{
}

/** Destructor */
CViewEdit::~CViewEdit()
{
}

/** Handle initial update of the window */
void CViewEdit::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal(800, 600);
	SetScrollSizes(MM_TEXT, sizeTotal);
}


/** Drawing of the window 
 * \param pDC the device context to draw on */
void CViewEdit::OnDraw(CDC* pDC)
{
    CDoubleBufferDC dbDC(pDC);

    Graphics graphics(dbDC.m_hDC);    // Create GDI+ graphics context

    Gdiplus::Size size = GetPicture()->GetSize();
    SetScrollSizes(MM_TEXT, CSize(size.Width, size.Height));

    GetPicture()->Draw(&graphics);
}

/** 
 * Force an update of this window when the picture changes.
 */
void CViewEdit::UpdateObserver()
{
    Invalidate();
    UpdateWindow();
}

/** 
 * Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context
 * \returns FALSE 
 */
BOOL CViewEdit::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}



/**
 * Handle a left button click
 * \param nFlags Flags that indicate status of the mouse buttons 
 * \param point The x,y location for the mouse click
 */
void CViewEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
    // Convert mouse coordinates to logical coordinates
    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.DPtoLP(&point);

    mLastMouse = Gdiplus::Point(point.x, point.y);

    //
    // Did we hit anything?
    //

    std::shared_ptr<CActor> hitActor;
    std::shared_ptr<CDrawable> hitDrawable;
    auto picture = GetPicture();
    for (auto actor : *picture)
    {
        // Note: We do not exit when we get the first hit, since
        // we are looking at these in drawing order. Instead, we
        // keep the last hit.
        std::shared_ptr<CDrawable> drawable = actor->HitTest(Point(point.x, point.y));
        if (drawable != nullptr)
        {
            hitActor = actor;
            hitDrawable = drawable;
        }
    }

    // If we hit something determine what we do with it based on the
    // current mode.
    if (hitActor != NULL)
    {
        mSelectedActor = hitActor;
        mSelectedDrawable = hitDrawable;
    }

    __super::OnLButtonDown(nFlags, point);
}


/**
* Handle mouse movement
* \param nFlags Flags that indicate status of the mouse buttons
* \param point The x,y location for the mouse
*/
void CViewEdit::OnMouseMove(UINT nFlags, CPoint point)
{
    // Convert mouse coordinates to logical coordinates
    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.DPtoLP(&point);
    Gdiplus::Point newMouse(point.x, point.y);
    Gdiplus::Point delta = newMouse - mLastMouse;
    mLastMouse = newMouse;

    if (nFlags & MK_LBUTTON)
    {
        switch (mMainFrame->GetMode())
        {
        case CMainFrame::Move:
            if (mSelectedDrawable != nullptr)
            {
                if (mSelectedDrawable->IsMovable())
                {
                    mSelectedDrawable->Move(delta);
                }
                else
                {
                    mSelectedActor->SetPosition(mSelectedActor->GetPosition() + delta);
                }
                GetPicture()->UpdateObservers();
            }
            break;

        case CMainFrame::Rotate:
            if (mSelectedDrawable != nullptr)
            {
                mSelectedDrawable->SetRotation(mSelectedDrawable->GetRotation() + delta.Y * RotationScaling);
                GetPicture()->UpdateObservers();
            }
            break;

        default:
            break;
        }

    }
    else
    {
        mSelectedDrawable = nullptr;
        mSelectedActor = nullptr;
    }

    __super::OnMouseMove(nFlags, point);
 }

/** Open the dialogue box for left machine */
void CViewEdit::OnMachineleftDialoguebox()
{
    auto machine = GetPicture()->GetMachines()[0]->GetMachine();
    CMachineDlg dlg(machine);
    if (dlg.DoModal() == IDOK)
    {
        Invalidate();
    }
}

/** Open the dialogue box for right machine */
void CViewEdit::OnMachinerightDialoguebox()
{
    auto machine = GetPicture()->GetMachines()[1]->GetMachine();
    CMachineDlg dlg(machine);
    if (dlg.DoModal() == IDOK)
    {
        Invalidate();
    }
}

/** Set the start time for left machine */
void CViewEdit::OnStarttimeSetLeft()
{
    auto picture = GetPicture();
    auto machine = picture->GetMachines()[0];
    auto currentFrame = picture->GetTimeline()->GetCurrentFrame();
    machine->SetStartTime(currentFrame);
}

/** Remove the start time for left machine */
void CViewEdit::OnStarttimeRemoveLeft()
{
    auto machine = GetPicture()->GetMachines()[0];
    machine->SetStartTime(-1);
}

/** Set the start time for right machine */
void CViewEdit::OnStarttimeSetRight()
{
    auto picture = GetPicture();
    auto machine = picture->GetMachines()[1];
    auto currentFrame = picture->GetTimeline()->GetCurrentFrame();
    machine->SetStartTime(currentFrame);
}

/** Remove the start time for right machine */
void CViewEdit::OnStarttimeRemoveRight()
{
    auto machine = GetPicture()->GetMachines()[1];
    machine->SetStartTime(-1);
}
