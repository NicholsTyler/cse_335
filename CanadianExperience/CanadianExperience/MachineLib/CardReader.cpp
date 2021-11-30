/**
 * \file CardReader.cpp
 *
 * \author Tyler Nichols
 */

#include "pch.h"
#include "CardReader.h"

using namespace Gdiplus;
using namespace std;

/// There should be 10 air sources for the card reader
const int NumSources = 10;

/// Image for the back of the card reader
const std::wstring CardReaderBackImage = L"images/card-reader-back.png";

/// Image for the front of the card reader
const std::wstring CardReaderFrontImage = L"images/card-reader-front.png";


// The card actual dimensions are 847 by 379 pixels,
// a size choosen to make the column spacing exactly
// 10 pixels. We draw it much smaller than that on the screen

/// Width to draw the card on the screen in pixels
const int CardWidth = 132;

/// Height to draw the card on the screen in pixels
const int CardLength = 297;

/// Amount of offset the center of the card so it will
/// appear at the right place relative to the card reader.
const int CardOffsetX = 126;

/// Y dimension of the offset
const int CardOffsetY = 65;

// These values are all for the underlying image. They
// can be used for find the punches.

/// Width of a card column in pixels
const int CardColumnWidth = 10;

/// Height of a card row in pixels
const int CardRowHeight = 29;

/// X offset for the first column (left side)
const int CardColumn0X = 24;

/// Y offset to the first row (0's)
/// There are actually two rows above this that can be used
const int CardRow0Y = 78;

/// Width of a punched hole
const int CardPunchWidth = 8;

/// Height of a punched hole
const int CardPunchHit = 20;

/// Any average luminance below this level is considered a punched hole
const double CardPunchLuminance = 0.1;

//
// These values are for the outputs of the card reader,
// where the tubing attaches.
//

/// Y offset to the first card reader output in pixels
const int OutputOffsetY = -92;

/// X offset to the first card reader output in pixels
const int OutputOffsetX = -35;

/// X spacing for the outputs
const double OutputSpacingX = 10.7;

CCardReader::CCardReader()
{
    mBackground.SetImage(CardReaderBackImage);
    mBackground.Rectangle(-mBackground.GetImageWidth() / 2, 0);

    mForeground.SetImage(CardReaderFrontImage);
    mForeground.Rectangle(-mForeground.GetImageWidth() / 2, 0);

    mCard.Rectangle(CardOffsetX, CardOffsetY, CardLength, CardWidth);
    mCard.SetRotation(-0.25);

    // Set up the sources
    for (int i = 0; i < NumSources; i++)
    {
        auto source = make_shared<CAirSource>();
        mSources.push_back(source);
    }
}

/**
* Draws the card reader
* \param graphics The graphics to draw with
* \param pos The position to draw at
*/
void CCardReader::Draw(Gdiplus::Graphics* graphics, Gdiplus::Point pos)
{
    Point cPos = GetPosition();
    int posX = cPos.X + pos.X;
    int posY = cPos.Y + pos.Y;

    mBackground.DrawPolygon(graphics, posX, posY);

    auto cardScale = (double)CardLength / mCard.GetImageWidth();

    mCard.DrawPolygon(graphics, posX, posY + ( (double)mColumn - 1) * cardScale * CardColumnWidth);
    mForeground.DrawPolygon(graphics, posX, posY);
}

/**
 * Determine if a hole is punched in the card.
 * @param column Column on the card, from 0 (left of first column) to 80 (last column)
 * @param row Row on the card, -2 to 9.
 * @return True if hole is punched at column, row
*/
bool CCardReader::IsPunched(int column, int row)
{
    auto luminance = mCard.AverageLuminance(CardColumn0X + (column - 1) * CardColumnWidth,
        CardRow0Y + CardRowHeight * row, CardPunchWidth, CardPunchHit);
    return luminance < CardPunchLuminance;
}

/**
* Set the time of the card reader
* \param time The time to set the card reader to
*/
void CCardReader::SetTime(double time)
{
    double beat = time * mBeatsPerMinute / 60.0;
    double remainder = fmod(beat, 1);
    mColumn = (int)beat;
    SetPressure(int(remainder * 2));
}

/**
* Implements the SetPressure function from IAirSinkDestination
* \param pressure The pressure to set component to
*/
void CCardReader::SetPressure(double pressure)
{
    // Determine what is punched in this row
    for (int row = 0; row < NumSources; row++)
    {
        bool punched = IsPunched(mColumn, row);
        if (punched)
            mSources[row]->SetPressure(pressure);
        else
            mSources[row]->SetPressure(0);
    }
}

/**
 * Set the position of the card reader in the machine. This
 * must, in turn, set the positions for the sources.
 * @param x X location of the card reader in the machine
 * @param y Y location of the card reader in the machine
*/
void CCardReader::SetPosition(int x, int y)
{
    CComponent::SetPosition(x, y);

    for (int row = 0; row < NumSources; row++)
    {
        mSources[row]->SetPosition(
            (int)(x + OutputOffsetX + OutputSpacingX * row),
            y + OutputOffsetY
        );
    }
}

