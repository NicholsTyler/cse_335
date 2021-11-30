/**
 * \file PictureFactory.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include "PictureFactory.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "ImageDrawable.h"
#include "MachineDrawable.h"

using namespace std;
using namespace Gdiplus;

/**
 * Constructor
*/
CPictureFactory::CPictureFactory()
{
}

/**
 * Destructor
*/
CPictureFactory::~CPictureFactory()
{
}


/** Factory method to create a new picture.
* \returns The created picture
*/
std::shared_ptr<CPicture> CPictureFactory::Create()
{
    shared_ptr<CPicture> picture = make_shared<CPicture>();

    // Create the background and add it
    auto background = make_shared<CActor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(Point(-100, 0));
    auto backgroundI = make_shared<CImageDrawable>(L"Background", L"images/Background.png");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    // Create and add Machine One
    auto machineOne = make_shared<CActor>(L"MachineOne");
    machineOne->SetPosition(Point(200, 350));
    auto machineOneI = make_shared<CMachineDrawable>(L"MachineOne", 1);
    machineOneI->SetName(machineOne->GetName());
    picture->AddMachine(machineOneI);
    machineOne->AddDrawable(machineOneI);
    machineOne->SetRoot(machineOneI);
    picture->AddActor(machineOne);

    // Create and add Machine Two
    auto machineTwo = make_shared<CActor>(L"MachineTwo");
    machineTwo->SetPosition(Point(750, 350));
    auto machineTwoI = make_shared<CMachineDrawable>(L"MachineTwo", 2);
    machineTwoI->SetName(machineTwo->GetName());
    picture->AddMachine(machineTwoI);
    machineTwo->AddDrawable(machineTwoI);
    machineTwo->SetRoot(machineTwoI);
    picture->AddActor(machineTwo);

    // Create and add Harold
    CHaroldFactory factory;
    auto harold = factory.Create();

    // This is where Harold will start out.
    harold->SetPosition(Point(750, 500));

    picture->AddActor(harold);

    // Create and add Sparty
    CSpartyFactory sfactory;
    auto sparty = sfactory.Create();

    sparty->SetPosition(Point(520, 500));
    picture->AddActor(sparty);

    return picture;
}
