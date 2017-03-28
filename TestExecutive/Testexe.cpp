///////////////////////////////////////////////////////////////////////////////
// Tokenizer.h - read words from a std::stream                               //
// ver 1.1                                                                  //
// Language:    C++, Visual Studio 2015                                      //
// Application: Lexical Scanner, CSE687 - Object Oriented Design, SP16       //
//              Alienware R15, Core i5, Windows 10                           //
// Author:      Saathvik Shashidhar Gowrapura, SUID: 450734672               //
//              sgowrapu@syr.edu, (315)-751-1059                             //
//////////////////////////////////////////////////////////////////////////////
/*Package Operations :
*------------------ -
*This package demonstrates all the requirements for Project - 1 of CSE - 687
* It is an automated test suite that tests both the semiexpression and tokenizer packages.
*
*  Public Interface :
*-------------------------------- -
*	testRequirement3(), testRequirement4(), testRequirement5(), testRequirement6_7_8(), testRequirement9(), testRequirement10() demonstrate the corresponding requirements
*   of the Project - 1 Statement
*
*  DisplayInputStream(), DisplayInputStream2() is used to display the input file provided
*
* Build Process :
*--------------
* Required Files :
*SemiExpression.h, SemiExpression.cpp, Tokenizer.h, Tokenizer.cpp
*
* Build Command : devenv Project1.sln / rebuild debug
*
*
* Maintenance History :
*--------------------
* ver 1.0 : 10 Feb 2016
* -first release
*/
#include "../SemiExp/SemiExp.h"
#include <iostream>
#include<fstream>

class TestExecutive 
{
public:
	void testRequirement3();											//to demonstrate requirement 3
	void DisplayInputStream();											//to display the contents of the input file
	void testRequirement4();											//to demonstrate requirement 4
	void testRequirement5();											//to demonstrate requirement 5
	void DisplayInputStream2();											//to display the contents of the input file
	void testRequirement6_7_8();										//to demonstrate requirement 6,7 and 8
	void testRequirement9();											//to demonstrate requirement 9
	void testRequirement10();											////to demonstrate requirement 10
};

void TestExecutive::testRequirement3()									////to demonstrate requirement 3
{
	std::cout << "\n\n--------------------------------------------------------------------------------\n";
	std::cout << " Demonstrating requirement 3\n";
	std::cout << " I have provided Tokenizer package to collect tokens.\n These tokens are combined to make meaningful semi expression. This is done by SemiExpression package. \n Also I have provided a scanner interface and ITokCollection\n\n\n";
}

void TestExecutive::DisplayInputStream()							//to display the contents of the input file
{
	std::string line;
	std::cout << "----------Input data -------" << "\n\n";
	std::ifstream inputfile("../Tokenizer/Test.txt");
	if (inputfile.is_open()) {
		while (getline(inputfile, line)) {
			std::cout << line << "\n";
		}
		inputfile.close();
	}
	else
		std::cout << "Unable to open file";
	std::cout << "\n----------Input data -------" << "\n\n";
}

void TestExecutive::testRequirement4()												//to demonstrate requirement 4
{
	std::string getcontent;
	std::cout << "\n\n--------------------------------------------------------------------------------\n";
	std::cout << " Demonstrating requirement 4\n";
	Scanner::Toker testToker;
	std::string fileSpec = "../Tokenizer/test.txt";
	std::ifstream in(fileSpec);
	if (!in.good())
	{
		std::cout << "\n  can't open " << fileSpec << "\n\n";
		//return 1;
	}
    testToker.attach(&in);
	testToker.addSpecialSingleChars("$");
	testToker.addSpecialCharPairs("$$");
	do
	{
		std::string tok = testToker.getTok();
		if (tok == "\n")
			tok = "newline";
		std::cout << "\n -- " << tok;
	} while (in.good());
	std::cout << "\n\n";
	testToker.reset();
}

void TestExecutive::testRequirement5()													//to demonstrate requirement 5
{
	std::cout << "\n\n--------------------------------------------------------------------------------\n";
	std::cout << " Demonstrating requirement 5\n";
	std::cout << "The Toker class contained in the Tokenizer class has a member function getTok() that produces token for each call to getTok()\n";
	std::cout << "This is done until the end of file is reached\n\n";
}

void TestExecutive::DisplayInputStream2()												//to display the contents of the input file
{
	std::string line;
	std::cout << "----------Input data -------" << "\n\n";
	std::ifstream inputfile("../Tokenizer/semitest.txt");
	if (inputfile.is_open()) {
		while (getline(inputfile, line)) {
			std::cout << line << "\n";
		}
		inputfile.close();
	}
	else
		std::cout << "Unable to open file";
	std::cout << "\n----------Input data -------" << "\n\n";
}

void TestExecutive::testRequirement6_7_8()													//to demonstrate requirement 6,7 and 8
{
	std::cout << "\n\n--------------------------------------------------------------------------------\n";
	std::cout << " Demonstrating requirement 6, 7 and 8\n";
	Scanner::Toker testSemiExpToker;
	std::string fileSpec = "../Tokenizer/semitest.txt";
	std::fstream in(fileSpec);
	if (!in.good())
	{
		std::cout << "\n  can't open file " << fileSpec << "\n\n";
	}
	testSemiExpToker.attach(&in);

	Scanner::SemiExp semiTest(&testSemiExpToker);
	semiTest.show(false);
	while (semiTest.get())
	{
		std::cout << "\n  -- semiExpression --";
		semiTest.show();
	}
	/*
	May have collected tokens, but reached end of stream
	before finding SemiExp terminator.
	*/
	if (semiTest.length() > 0)
	{
		std::cout << "\n  -- semiExpression --";
		semiTest.show();
		std::cout << "\n\n";
	}
	testSemiExpToker.reset();
}

void TestExecutive::testRequirement9()																//to demonstrate requirement 9
{
	std::cout << "\n\n--------------------------------------------------------------------------------\n";
	std::cout << " Demonstrating requirement 9\n";
	std::cout << "\n\nThe input is \nstd::string Str = \"THIS IS A STRING\";\n\n";
	Scanner::Toker testToker2;
	std::string fileSpec = "../Tokenizer/semitest2.txt";
	std::fstream in(fileSpec);
	if (!in.good())
	{
		std::cout << "\n  can't open file " << fileSpec << "\n\n";
	}
	testToker2.attach(&in);
	Scanner::SemiExp semiCollection(&testToker2);
	std::cout << "\n Output for get(clear = true) function.\n get function will store tokens in the vector";
	std::cout << "show function is used to display\n";
	semiCollection.get(true);
	semiCollection.show(true);
	std::cout << "\n\nOutput for length() function\n";
	std::cout << semiCollection.length() << "\n\n";
	std::cout << "Output for operator() function\nIndex value of 3 is passed as argument\n";
	std::cout << semiCollection.operator[](3) << "\n\n";
	std::cout << "Output for find(string) function\n:: is passed as a value to the function\n";
	std::cout << semiCollection.find("::") << "\n\n";
	std::cout << "Output for push(string) function\nappendedString is passed as argument\n";
	semiCollection.push_back("appendedString");
	semiCollection.show(false);
	std::cout << "\n\nOutput for remove(string) function\nappendedString is passed as argument\n";
	semiCollection.remove("appendedString");semiCollection.show(false);
	std::cout << "\n\nOutput for remove(size_t i) function\nIndex value 6 is passed as argument\n";
	semiCollection.remove(6);semiCollection.show(true);
	std::cout << "\n\nOutput for toLower() function\n";
	std::cout << "               Before"; semiCollection.show(false);
	semiCollection.toLower();
	std::cout << "               After"; semiCollection.show(false);
	std::cout << "\n\nOutput for trim() function";
	std::cout << "\n               Before"; semiCollection.show(true);
	semiCollection.trimFront();
	std::cout << "               After"; semiCollection.show(true);
	std::cout << "\n\nOutput for clear() function\n";
	semiCollection.clear();
	semiCollection.show(true);
}

void TestExecutive::testRequirement10()									//to demonstrate requirement 10
{
	std::cout << "\n\n--------------------------------------------------------------------------------\n";
	std::cout << " Demonstrating requirement 10\n";
	std::cout << "I have included an automated unit test suite called TestExecutive that exercises all of the special cases\n\n\n";
}

int main()
{
	TestExecutive testExeObj;
	testExeObj.testRequirement3();
	testExeObj.DisplayInputStream();
	testExeObj.testRequirement4();
	testExeObj.testRequirement5();
	testExeObj.DisplayInputStream2();
	testExeObj.testRequirement6_7_8();
	testExeObj.testRequirement9();
	testExeObj.testRequirement10();
	return 0;
}