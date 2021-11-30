/**
 * \file TileRocketPad.h
 *
 * \author 
 *
 * Class that implements a rocket pad.
 */

#pragma once

#include "Tile.h"

class CRocket;

/**
 * Class that implements a rocket pad.
 * 
 * This is where rockets take off and land.
*/
class CTileRocketPad : public CTile
{
public:
    CTileRocketPad(CCity* city);

    ///  Default constructor (disabled)
    CTileRocketPad() = delete;

    ///  Copy constructor (disabled)
    CTileRocketPad(const CTileRocketPad&) = delete;

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    virtual void Report(std::shared_ptr<CMemberReport> report) override;

    virtual bool PendingDelete() override;

    virtual void Update(double elapsed) override;

    /** Determines if this pad has the rocket.
    * \returns true if pad has rocket */
    bool HasRocket() { if (mRocket != nullptr) return true; else return false; }

    /** Sets the rocket for this pad
    * \param rocket A shared pointer to the rocket */
    void SetRocket(std::shared_ptr<CRocket> rocket) { mRocket = rocket; }

    /** Gets the rocket from this pad
    * \returns Pointer to the rocket */
    std::shared_ptr<CRocket> GetRocket() { return mRocket; }

    void RocketIsGone();
    void RocketHasLanded();

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CTileVisitor* visitor) override { visitor->VisitRocketPad(this); }

    virtual void Draw(Gdiplus::Graphics* graphics) override;

private:
    /// Pointer to the rocket if this pad has it.
    std::shared_ptr<CRocket> mRocket = nullptr;
};

