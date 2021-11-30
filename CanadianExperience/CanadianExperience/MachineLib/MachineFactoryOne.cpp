/**
 * \file MachineFactoryOne.cpp
 *
 * \author Tyler Nichols
 */

#include "pch.h"
#include "MachineFactoryOne.h"
#include "MachineActor.h"
#include "Shape.h"
#include "CardReader.h"
#include "Cylinder.h"
#include "Chime.h"
#include "Tubing.h"


using namespace std;
using namespace Gdiplus;


/**
 * Create a machine type one object
 * \returns Object of type CWorkingMachine
 */
std::shared_ptr<CMachineActor> CMachineFactoryOne::CreateMachine()
{
    // Locations of stuff
    const int BaseWidth = 650;
    const int BaseHeight = 10;

    // All of the centers (X)
    const int FrameworkCenter = 25;
    const int CardReaderCenter = -250;
    const int CylinderCenter = 63;
    const int ChimesCenter = 47;
    const int CymbalAndDrumCenter = 275;
    const int ClampingPostCenter = -150;

    const int CylinderBottom = -95;
    const int ChimeTop = -335;
    const int CylinderAndChimesSpacing = 55;
    const int NumChimes = 5;

    // The machine itself. The value passed to the 
    // constructor is the machine number.
    auto machine = make_shared<CMachineActor>(1);

    // The base, just a flat to sit things on
    auto base = make_shared<CShape>();
    base->Rectangle(-BaseWidth / 2, BaseHeight, BaseWidth, BaseHeight);
    base->SetColor(Color::DarkGray);
    machine->AddComponent(base);

    //
    // The framework that holds the cylinders and chimes
    //
    auto framework = make_shared<CShape>();
    framework->SetImage(L"images/framework.png");
    framework->Rectangle(-framework->GetImageWidth() / 2, 0);
    framework->SetPosition(FrameworkCenter, 0);
    machine->AddComponent(framework);

    //
    // The card reader
    //
    auto reader = make_shared<CCardReader>();
    reader->SetCard(L"images/suzanna.png");
    reader->SetPosition(CardReaderCenter, 0);
    machine->SetCardReader(reader.get());
    machine->AddComponent(reader);

    //
    // Cylinders and chimes
    //
    int ChimeLength[] = { 220, 170, 125, 100, 75 };
    wchar_t* sounds[] = { L"audio/chimeC3.wav",
        L"audio/chimeD3.wav",
        L"audio/chimeE3.wav",
        L"audio/chimeG3.wav",
        L"audio/chimeA3.wav" };

    // Vector to collect the cylinders so we can 
    // run tubing to them later.
    std::vector<std::shared_ptr<CCylinder>> cylinders;

    //
    // The cylinders and chimes
    //
    int cylinderX = -CylinderAndChimesSpacing * NumChimes / 2 + CylinderCenter;
    int chimeX = -CylinderAndChimesSpacing * NumChimes / 2 + ChimesCenter;
    for (int i = 0; i < NumChimes; i++) {
        //
        // The chime
        //
        auto chime = make_shared<CChime>(ChimeLength[i]);
        chime->SetPosition(chimeX, ChimeTop);
        machine->AddComponent(chime);

        //
        // The cylinder that hits the chime
        //
        auto cylinder = make_shared<CCylinder>();
        cylinder->SetPosition(cylinderX, CylinderBottom);
        machine->AddComponent(cylinder);
        cylinders.push_back(cylinder);

        // Connect the motion
        cylinder->SetMotionSink(chime);

        // Add sound to the chime
        auto channel = machine->GetWavPlayer()->CreateChannel(sounds[i]);
        chime->SetAudioChannel(channel);

        // Move to the next x locations
        cylinderX += CylinderAndChimesSpacing;
        chimeX += CylinderAndChimesSpacing;
    }

    //
    // The cymbal
    //
    auto cymbal = make_shared<CShape>();
    cymbal->SetImage(L"images/cymbal-all.png");
    cymbal->Rectangle(-cymbal->GetImageWidth() / 2, 0);
    cymbal->SetPosition(CymbalAndDrumCenter, 0);
    machine->AddComponent(cymbal);

    auto channel = machine->GetWavPlayer()->CreateChannel(L"audio/cymbal.wav");
    cymbal->SetAudioChannel(channel);

    // Cantilever to hold the cylinder
    auto cant = make_shared<CShape>();
    cant->SetImage(L"images/cantilever.png");
    cant->Rectangle(0, 0);   // 0,0 is lower right corner
    cant->SetPosition(framework->GetImageWidth() / 2 - 46, -framework->GetImageHeight() + 3);
    machine->AddComponent(cant);

    auto cymbalCylinder = make_shared<CCylinder>();
    cymbalCylinder->SetPosition(cant->GetX() + 100, cant->GetY() - 2);
    cymbalCylinder->SetRotation(0.5);
    cymbalCylinder->SetMaxExtent(0.55);
    machine->AddComponent(cymbalCylinder);

    cymbalCylinder->SetMotionSink(cymbal);

    //
    // The drum
    //
    auto drum = make_shared<CShape>();
    drum->SetImage(L"images/drum.png");
    drum->Rectangle(-drum->GetImageWidth() / 2, 0);
    drum->SetPosition(CymbalAndDrumCenter, 0);
    machine->AddComponent(drum);

    channel = machine->GetWavPlayer()->CreateChannel(L"audio/kick.wav");
    drum->SetAudioChannel(channel);

    // Block to hold the cylinder
    auto block = make_shared<CShape>();
    block->SetImage(L"images/angle-block.png");
    block->Rectangle(-block->GetImageWidth(), 0);   // 0,0 is lower right corner
    block->SetPosition(91, 0);
    machine->AddComponent(block);

    auto drumCylinder = make_shared<CCylinder>();
    drumCylinder->SetPosition(90, -30);
    drumCylinder->SetRotation(0.25);
    machine->AddComponent(drumCylinder);

    drumCylinder->SetMotionSink(drum);

    //
    // Clamping post for the tubing
    //
    auto post = make_shared<CShape>();
    post->SetImage(L"images/clamping-post.png");
    post->Rectangle(-post->GetImageWidth() / 2, 0);
    post->SetPosition(ClampingPostCenter, 0);
    machine->AddComponent(post);

    ////
    //// Temporary connection from card reader to cylinders
    ////
/*    for (int i = 0; i < 5; i++)
    {
        reader->GetSource(i)->SetSink(cylinders[4 - i]->GetSink());
    }
    reader->GetSource(8)->SetSink(drumCylinder->GetSink());
    reader->GetSource(9)->SetSink(cymbalCylinder->GetSink());
*/

    //
    // We do the tubing last so it is on top
    //
    for (int i = 0; i < 5; i++)
    {
        auto tubing = make_shared<CTubing>();
        reader->GetSource(i)->SetSpeed(50);
        reader->GetSource(i)->SetSink(tubing->GetSink());
        tubing->GetSource()->SetSink(cylinders[4 - i]->GetSink());
        machine->AddComponent(tubing);

        tubing->AddClamp(ClampingPostCenter, -10 - 10 * i, 0.75, 50);

    }

    auto tubing = make_shared<CTubing>();
    reader->GetSource(9)->SetSink(tubing->GetSink());
    reader->GetSource(9)->SetSpeed(25);
    reader->GetSource(9)->SetSpeed(50);
    tubing->GetSource()->SetSink(cymbalCylinder->GetSink());
    machine->AddComponent(tubing);

    tubing->AddClamp(-162, -90, 0.5, 50);
    tubing->AddClamp(-162, -360, 0.5, 100);

    tubing = make_shared<CTubing>();
    reader->GetSource(8)->SetSpeed(10);
    reader->GetSource(8)->SetSink(tubing->GetSink());
    tubing->GetSource()->SetSink(drumCylinder->GetSink());
    machine->AddComponent(tubing);

    tubing->AddClamp(ClampingPostCenter, -10 - 10 * 5, 0.75, 50);

    // Clamping post clamps for the tubing
    auto clamps = make_shared<CShape>();
    clamps->SetImage(L"images/clamping-post-clamps.png");
    clamps->Rectangle(-clamps->GetImageWidth() / 2, 0);
    clamps->SetPosition(ClampingPostCenter, 0);
    machine->AddComponent(clamps);

    return machine;
}

