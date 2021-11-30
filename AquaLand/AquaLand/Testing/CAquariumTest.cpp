/**
* \file CAquariumTest.cpp
*
* \author Charles B. Owen
* 
* Test to determine if the aquarium class is working correctly.
*/

#include "pch.h"
#include "CppUnitTest.h"

#include <regex>
#include <string>
#include <fstream>
#include <streambuf>

#include "Aquarium.h"
#include "FishBeta.h"
#include "FishAngler.h"
#include "FishMagikarp.h"
#include "DecorCastle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	/**
	* Create a path to a place to put temporary files
	*/
	wstring TempPath()
	{
		// Create a path to temporary files
		wchar_t path_nts[MAX_PATH];
		GetTempPath(MAX_PATH, path_nts);

		// Convert null terminated string to wstring
		return wstring(path_nts);
	}

	/**
	* Read a file into a wstring and return it.
	* \param filename Name of the file to read
	* \return File contents
	*/
	wstring ReadFile(const wstring& filename)
	{
		ifstream t(filename);
		wstring str((istreambuf_iterator<char>(t)),
			istreambuf_iterator<char>());

		return str;
	}

	/**
	* Test to ensure an aquarium .aqua file is empty
	*/
	void TestEmpty(wstring filename)
	{
		Logger::WriteMessage(filename.c_str());

		wstring xml = ReadFile(filename);
		Logger::WriteMessage(xml.c_str());

		Assert::IsTrue(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
		Assert::IsTrue(regex_search(xml, wregex(L"<aqua/>")));
	}

	/**
	 *  Populate an aquarium with three Beta fish
	 */
	void PopulateThreeBetas(CAquarium* aquarium)
	{
		shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(aquarium);
		fish1->SetLocation(100, 200);
		aquarium->Add(fish1);

		shared_ptr<CFishBeta> fish2 = make_shared<CFishBeta>(aquarium);
		fish2->SetLocation(400, 400);
		aquarium->Add(fish2);

		shared_ptr<CFishBeta> fish3 = make_shared<CFishBeta>(aquarium);
		fish3->SetLocation(600, 100);
		aquarium->Add(fish3);
	}

	void TestThreeBetas(wstring filename)
	{
		Logger::WriteMessage(filename.c_str());

		wstring xml = ReadFile(filename);
		Logger::WriteMessage(xml.c_str());

		// Ensure three items
		Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

		// Ensure the positions are correct
		Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
		Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
		Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));

		// Ensure the types are correct
		Assert::IsTrue(regex_search(xml,
			wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"beta\"/><item.* type=\"beta\"/></aqua>")));
	}

	/**
	 *  Populate an aquarium with every type
	 */
	void PopulateAllTypes(CAquarium* aquarium)
	{
		// Adds a beta fish to the aquarium
		shared_ptr<CFishBeta> fishBeta = make_shared<CFishBeta>(aquarium);
		fishBeta->SetLocation(100, 200);
		fishBeta->SetSpeedX(1);
		fishBeta->SetSpeedY(2);
		aquarium->Add(fishBeta);

		// Adds an angler fish to the aquarium
		shared_ptr<CFishAngler> fishAngler = make_shared<CFishAngler>(aquarium);
		fishAngler->SetLocation(300, 400);
		fishAngler->SetSpeedX(3);
		fishAngler->SetSpeedY(4);
		aquarium->Add(fishAngler);

		// Adds a magikarp fish to the aquarium
		shared_ptr<CFishMagikarp> fishMagikarp = make_shared<CFishMagikarp>(aquarium);
		fishMagikarp->SetLocation(500, 600);
		fishMagikarp->SetSpeedX(5);
		fishMagikarp->SetSpeedY(6);
		aquarium->Add(fishMagikarp);

		// Adds a decor castle to the aquarium
		shared_ptr<CDecorCastle> decorCastle = make_shared<CDecorCastle>(aquarium);
		decorCastle->SetLocation(700, 800);
		aquarium->Add(decorCastle);
	}

	void TestAllTypes(wstring filename)
	{
		Logger::WriteMessage(filename.c_str());

		wstring xml = ReadFile(filename);
		Logger::WriteMessage(xml.c_str());

		// Ensure four items
		Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*<item.*</aqua>")));

		// Ensure the positions are correct
		Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\" xSpeed=\"1\" ySpeed=\"2\"")));
		Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"300\" y=\"400\" xSpeed=\"3\" ySpeed=\"4\"")));
		Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"500\" y=\"600\" xSpeed=\"5\" ySpeed=\"6\"")));
		Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"700\" y=\"800\"")));

		// Ensure the types are correct
		Assert::IsTrue(regex_search(xml,
			wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"angler\"/><item.* type=\"magikarp\"/><item.* type=\"castle\"/></aqua>")));
	}

	TEST_CLASS(CAquariumTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCAquariumConstruct)
		{
			CAquarium aquarium;
		}

		TEST_METHOD(TestCAquariumHitTest)
		{
			CAquarium aquarium;

			Assert::IsTrue(aquarium.HitTest(100, 200) == nullptr,
				L"Testing empty aquarium");

			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(&aquarium);
			fish1->SetLocation(100, 200);
			aquarium.Add(fish1);

			Assert::IsTrue(aquarium.HitTest(100, 200) == fish1,
				L"Testing fish at 100, 200");

			Assert::IsTrue(aquarium.HitTest(300, 400) == nullptr,
				L"Testing 300, 400 while fish is at 100, 200");

			shared_ptr<CFishBeta> fish2 = make_shared<CFishBeta>(&aquarium);
			fish2->SetLocation(100, 200);
			aquarium.Add(fish2);

			Assert::IsFalse(aquarium.HitTest(100, 200) == fish1,
				L"Validating that fish1 (on bottom) is NOT hit");

			Assert::IsTrue(aquarium.HitTest(100, 200) == fish2,
				L"Validating that fish2 (on top) is hit");
		}

		TEST_METHOD(TestCAquariumSave)
		{
			// Create a path to temporary files
			wstring path = TempPath();

			// Create an aquarium
			CAquarium aquarium;

			//
			// First test, saving an empty aquarium
			//
			wstring file1 = path + L"test1.aqua";
			aquarium.Save(file1);

			TestEmpty(file1);

			//
			// Now populate the aquarium
			//

			PopulateThreeBetas(&aquarium);

			wstring file2 = path + L"test2.aqua";
			aquarium.Save(file2);

			TestThreeBetas(file2);

			//
			// Test all types
			//
			CAquarium aquarium3;
			PopulateAllTypes(&aquarium3);

			wstring file3 = path + L"test3.aqua";
			aquarium3.Save(file3);

			TestAllTypes(file3);
		}

		TEST_METHOD(TestCAquariumClear)
		{
			// Create a path to temporary files
			wstring path = TempPath();

			// Create an aquarium
			CAquarium aquarium;

			//
			// Populate the aquarium
			//
			PopulateAllTypes(&aquarium);

			wstring file1 = path + L"test1.aqua";
			aquarium.Save(file1);

			TestAllTypes(file1);

			//
			// Now test aquarium is empty
			//
			aquarium.Clear();

			wstring file2 = path + L"test2.aqua";
			aquarium.Save(file2);

			TestEmpty(file2);
		}

		TEST_METHOD(TestCAquariumLoad)
		{
			// Create a path to temporary files
			wstring path = TempPath();

			// Create two aquariums
			CAquarium aquarium, aquarium2;

			//
			// First test, saving an empty aquarium
			//
			wstring file1 = path + L"test1.aqua";

			aquarium.Save(file1);
			TestEmpty(file1);

			aquarium2.Load(file1);
			aquarium2.Save(file1);
			TestEmpty(file1);

			//
			// Now populate the aquarium
			//

			PopulateThreeBetas(&aquarium);

			wstring file2 = path + L"test2.aqua";
			aquarium.Save(file2);
			TestThreeBetas(file2);

			aquarium2.Load(file2);
			aquarium2.Save(file2);
			TestThreeBetas(file2);

			//
			// Test all types
			//
			CAquarium aquarium3;
			PopulateAllTypes(&aquarium3);

			wstring file3 = path + L"test3.aqua";
			aquarium3.Save(file3);
			TestAllTypes(file3);

			aquarium2.Load(file3);
			aquarium2.Save(file3);
			TestAllTypes(file3);
		}

	};

}