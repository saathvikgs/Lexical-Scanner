///////////////////////////////////////////////////////////////////////////////
// Tokenizer.h - read words from a std::stream                               //
// ver 3.5                                                                   //
// Language:    C++, Visual Studio 2015                                      //
// Application: Lexical Scanner, CSE687 - Object Oriented Design, SP16       //
//              Alienware R15, Core i5, Windows 10                           //
// Author:      Saathvik Shashidhar Gowrapura, SUID: 450734672               //
//              sgowrapu@syr.edu, (315)-751-1059                             //
// Original author: Jim Fawcett, CST 4-187, Syracuse University              // 
//              jfawcett@twcny.rr.com, (315)-443-3948                        //
//////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
*
* This package provides a public Toker class and private ConsumeState class.
* Toker reads words from a std::stream, throws away whitespace
* and returns comments and words from the stream in the order encountered.  Quoted
* strings and certain punctuators and newlines are returned as single tokens.
* Special single characters and special double character pairs are returned as single tokens
* This is a new version, based on the State Design Pattern.  Older versions
* exist, based on an informal state machine design.
*
* Public Interface:
* -----------------
* void consumeChars() - To consume characters depending on token state
*
* std::string getTok() - returns one token as a string(eg. alphanum or special character etc.)
*
* bool setSpecialSingleChars(std::string ssc) - to set special single characters
*
* bool setSpecialCharPairs(std::string scp) - to set double character pairs
*
* void attach(std::istream* pIn) - attaches the filestream  pointer to ConsumeState variable.
*
* Build Process:
* --------------
* Required Files: Tokenizer.h, Tokenizer.cpp
* Build Command: devenv Tokenizer.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 3.5 : 09 Feb 2016
* - added functionalty to collect tokens using getTok() method until the end of file
* - added functionality to set special single character and special character pairs
*   is reached
* ver 3.4 : 03 Feb 2016
* - fixed bug that prevented reading of last character in source by
*   clearing stream errors at beginning of ConsumeState::nextState()
* ver 3.3 : 02 Feb 2016
* - declared ConsumeState copy constructor and assignment operator = delete
* ver 3.2 : 28 Jan 2016
* - fixed bug in ConsumeState::nextState() by returning a valid state
*   pointer if all tests fail due to reaching end of file instead of
*   throwing logic_error exception.
* ver 3.1 : 27 Jan 2016
* - fixed bug in EatCComment::eatChars()
* - removed redundant statements assigning _pState in derived eatChars()
*   functions
* - removed calls to nextState() in each derived eatChars() and fixed
*   call to nextState() in ConsumeState::consumeChars()
* ver 3.0 : 11 Jun 2014
* - first release of new design
*
* Planned Additions and Changes:
* ------------------------------
* - Return quoted strings as single token.  This must handle \" and \'
*   correctly.
* - Consider converting eatNewLine() to eatSpecialTokens() - see below
* - Return [, ], {, }, (, ), <, >, :, ; as single character tokens
* - Return <<, >>, +=, -=, *=, /=, :: as two character tokens
*/
#include "Tokenizer.h"
#include <iostream>
#include <cctype>
#include <string>

namespace Scanner
{
  class ConsumeState
  {
  public:
    ConsumeState();													//Constructor
    ConsumeState(const ConsumeState&) = delete;						//Constructor
    ConsumeState& operator=(const ConsumeState&) = delete;
    virtual ~ConsumeState();										//Destructor
    void attach(std::istream* pIn) { _pIn = pIn; }					//Method to create a reference to the file
    virtual void eatChars() = 0;									//Virtual method that should be implemented
    void consumeChars() {											//Method to consume chars depending on the token state 
      _pState->eatChars();
      _pState = nextState();
    }
	void resetConsumeState() {										//Method to reset the pointers of type ConsumeState
		resetFirst = true;
		resetSecond = true;
	}
	bool setSpecialSingleChars(std::string ssc)											// Function to add and display special single character
	{
		std::cout << "\n Before setting the special single char $, the vector is: \n";
		for (unsigned int i = 0; i < specialSingleChars.size(); i++)					//iterating through the specialSingleChars vector
			std::cout << specialSingleChars[i] << " ";
		specialSingleChars.push_back(ssc);
		std::cout << "\n After setting the special single char $, the vector is: \n";
		for (unsigned int i = 0; i < specialSingleChars.size(); i++)
			std::cout << specialSingleChars[i] << " ";
		return true;
	}	
	bool setSpecialCharPairs(std::string scp)											// Function to add and display special character pair
	{
		std::cout << "\n Before setting the special char pair $$, the vector is: \n";
		for (unsigned int i = 0; i < specialDoubleChars.size(); i++)					//iterating through the specialCharPairs vector
			std::cout << specialDoubleChars[i]<<" ";
		specialDoubleChars.push_back(scp);
		std::cout << "\n After setting the special char pair $$, the vector is: \n";
		for (unsigned int i = 0; i < specialDoubleChars.size(); i++)
			std::cout << specialDoubleChars[i]<<" ";
		return true;
	}
    bool canRead() { return _pIn->good(); }												//The getTok() method in Toker class calls this method to check whether it can read from the file or not
    std::string getTok() { return token; }												//Method to return tokens
    bool hasTok() { return token.size() > 0; }											//Method to check the length of the token and return the boolean value accordingly
    ConsumeState* nextState();															//Method to check the next type of tokens in the input stream and set the pointer accordingly
	ConsumeState* nextother_state();													//Method to check the next type of tokens in the input stream and set the pointer accordingly											
	ConsumeState* next_other_state();													//Method to check the next type of tokens in the input stream and set the pointer accordingly
  protected:
    static std::string token;															//static variables
    static std::istream* _pIn;
	static bool resetFirst;
	static bool resetSecond;
    static int prevChar;																//prevChar holds the ASCII value of previous character in the token
    static int currChar;															   //currChar holds the ASCII value of the current character in the token
    static ConsumeState* _pState;
    static ConsumeState* _pEatCppComment;
    static ConsumeState* _pEatCComment;
    static ConsumeState* _pEatWhitespace;
    static ConsumeState* _pEatPunctuator;
    static ConsumeState* _pEatAlphanum;
    static ConsumeState* _pEatNewline;
	static ConsumeState* _pEatDoubleQuotedString;    
	static ConsumeState* _pEatSingleQuotedString;
	static ConsumeState* _pEatSpecialSingleChar;
	static ConsumeState* _pEatSpeicalDoubleChar;
	static std::vector<std::string> specialSingleChars;									// defining vector
	static std::vector<std::string> specialDoubleChars;									 // defining vector
  };
}

using namespace Scanner;

std::string ConsumeState::token;
std::istream* ConsumeState::_pIn = nullptr;
int ConsumeState::prevChar;
int ConsumeState::currChar;											
ConsumeState* ConsumeState::_pState = nullptr;								//Initializing pointers
ConsumeState* ConsumeState::_pEatCppComment = nullptr;
ConsumeState* ConsumeState::_pEatCComment = nullptr;
ConsumeState* ConsumeState::_pEatWhitespace = nullptr;
ConsumeState* ConsumeState::_pEatPunctuator = nullptr;
ConsumeState* ConsumeState::_pEatAlphanum = nullptr;
ConsumeState* ConsumeState::_pEatDoubleQuotedString = nullptr;
ConsumeState* ConsumeState::_pEatSingleQuotedString = nullptr;
ConsumeState* ConsumeState::_pEatNewline;
ConsumeState* ConsumeState::_pEatSpecialSingleChar = nullptr;
ConsumeState* ConsumeState::_pEatSpeicalDoubleChar = nullptr;
std::vector<std::string> ConsumeState::specialSingleChars = { "<", ">", "[", "]", "(", ")", "{", "}", ":", "=", "+", "-", "*", "\n" };   //initializing vector
std::vector<std::string> ConsumeState::specialDoubleChars = { "<<", ">>", "::", "++", "--", "==", "+=", "-=", "*=", "/=" };              //initializing vector
bool ConsumeState::resetFirst = true;
bool ConsumeState::resetSecond = true;
void testLog(const std::string& msg);

ConsumeState* ConsumeState::nextState()												//This method identifies the next type of character in the input stream and sets the state accordingly
{
	if (!(_pIn->good()))																//If the file pointer is not set or the file is missing then return null pointer
	{
		return nullptr;
	}
	int chNext = _pIn->peek();														//peek method checks the next character in the input stream
	if (chNext == EOF)
	{
		_pIn->clear();
		// if peek() reads end of file character, EOF, then eofbit is set and
		// _pIn->good() will return false.  clear() restores state to good
	}
	
	std::string identifySpecialDoubleChar;											//Variable to identify the speical character pairs in the input stream
	identifySpecialDoubleChar += currChar;
	identifySpecialDoubleChar += _pIn->peek();										//setting its value
	for (unsigned int i = 0; i < specialDoubleChars.size(); i++)
	{
		if (specialDoubleChars[i] == identifySpecialDoubleChar)						//if the specialDoubleChars vector contains the identifySpecialDoubleChar then set the state to eatSpecialCharPair 
		{
			testLog("state: eatSpecialDoubleChar");
			return _pEatSpeicalDoubleChar;
		}
	}
	
	if (currChar == '/' && chNext == '/')											  //set the state to Cppcomment
	{
		testLog("state: eatCppComment");
		return _pEatCppComment;
	}
	if (currChar == '/' && chNext == '*')												//set the state to C comment
	{
		testLog("state: eatCComment");
		return _pEatCComment;
	}
	if (currChar == '_' && isalnum(chNext))											//set the state to alphanum 
	{
		testLog("state: eatAlphanum"); return _pEatAlphanum;
	}
	if (std::isspace(currChar) && currChar != '\n')									//set the state to whitespace if currChar is whitespace
	{
		testLog("state: eatWhitespace");
		return _pEatWhitespace;
	}

	return next_other_state();
}

ConsumeState* ConsumeState::next_other_state()										//This method identifies the next type of character in the input stream and sets the state accordingly
{
	if (currChar == '\'')
	{
		testLog("state: eatSingleQuotedString");
		return _pEatSingleQuotedString;												//set the state to eatSingleQuotedString when currChar = '
	}
	if (currChar == '"')
	{
		testLog("state: eatDoubleQuotedString");
		return _pEatDoubleQuotedString;												//set the state to eat eatDoubleQuotedString when currChar = "
	}
	return nextother_state();
}

ConsumeState* ConsumeState::nextother_state()										//This method identifies the next type of character in the input stream and sets the state accordingly
{
	int chNext = _pIn->peek();
	std::string identifySpecialSingleChar;											//Variable to identify the speical single character in the input stream
	identifySpecialSingleChar += currChar;											//setting its value
	if (currChar == '\\' && _pIn->peek() == 'n')
	{
		identifySpecialSingleChar += _pIn->peek();
		testLog("state: eatSpecialSingleChar");
		return _pEatSpecialSingleChar;
	}
	if (chNext == EOF)
	{
		_pIn->clear();
	}
	for (unsigned int i = 0; i < specialSingleChars.size(); i++)
	{
		if (specialSingleChars[i] == identifySpecialSingleChar)						//if the specialDoubleChars vector contains the identifySpecialSingleChar then set the state to eatSpecialSingleChar
		{
			testLog("state: eatSpecialSingleChar");
			return _pEatSpecialSingleChar;
		}
	}
	if (chNext == EOF)
	{
		_pIn->clear();
	}
 
  if (currChar == '\n')																//set the state to newline
  {
    testLog("state: eatNewLine"); return _pEatNewline;
  }
  
  if (std::isalnum(currChar))														//set the state to alphanum
  {
	  testLog("state: eatAlphanum"); return _pEatAlphanum;
  }
  if (ispunct(currChar))															//set the state to punctuator
  {
    testLog("state: eatPunctuator"); return _pEatPunctuator;
  }
  if (!_pIn->good())
  {
    std::cout << "\n  end of stream with currChar = " << currChar << "\n\n";
    return _pEatWhitespace;
  }
  throw(std::logic_error("invalid type"));
}

class EatWhitespace : public ConsumeState	
{
public:
  virtual void eatChars()																	//Method to eat whitespace in input stream when eatwhitespace state is set
  {
    token.clear();
    //std::cout << "\n  eating whitespace";
    do {
      if (!_pIn->good())  // end of stream
        return;
      currChar = _pIn->get();
    } while (std::isspace(currChar) && currChar != '\n');
  }
};

class EatCppComment : public ConsumeState
{
public:
  virtual void eatChars()																		//Method to eat C++ comments when eatcppcomment state is set
  {
    token.clear();
   // std::cout << "\n\n Demonstration of eating C++ comment";
    do {
      if (!_pIn->good())  // end of stream
        return;
	  token += currChar;
	  currChar = _pIn->get();
    } while (currChar != '\n');
  }
};

class EatCComment : public ConsumeState
{
public:
  virtual void eatChars()																		//Method to eat C comments when eatccomment state is set
  {
    token.clear();
   // std::cout << "\n\n Demonstrating of eating C comment";
    do {
		token += currChar;
      if (!_pIn->good())  // end of stream
        return;
	  
      currChar = _pIn->get();
	} while (currChar != '/');
	token += currChar;
	//while (currChar != '*' || _pIn->peek() != '/');
   // _pIn->get();
    currChar = _pIn->get();
  }
};

class EatPunctuator : public ConsumeState
{
public:
  virtual void eatChars()																		//Method to eat punctuator when eatPunctuator state is set
  {
    token.clear();
   //std::cout << "\n\n Demonstration of eating punctuator";
    do {
      token += currChar;
      if (!_pIn->good())  // end of stream
        return;
      currChar = _pIn->get();
    } while (ispunct(currChar));
  }
};

class EatAlphanum : public ConsumeState
{
public:
  virtual void eatChars()																		//Method to eat alphabets and numbers when eatAlphanum state is set
  {
    token.clear();
   // std::cout << "\n\n Demonstration of eating alphanum";
    do {
      token += currChar;
      if (!_pIn->good())  // end of stream
        return;
      currChar = _pIn->get();
    } while (isalnum(currChar) || currChar == '_');
  }
};

class EatNewline : public ConsumeState
{
public:
  virtual void eatChars()																		//Method to eat newlines when eatNewline state is set
  {
    token.clear();
    token += currChar;
    if (!_pIn->good())  // end of stream
      return;
    currChar = _pIn->get();
  }
};

class EatDoubleQoutedString : public ConsumeState
{
public:
	virtual void eatChars()																	//Method to eat double quoted string when eatDoubleQuotedString state is set
	{
		token.clear();
		//std::cout<< "\n\n Demostrating eating double quoted string";
		do {
			if (!_pIn->good())
				return;
			if (currChar == '\\' && _pIn->peek() == '"')
			{
				prevChar = currChar;
				currChar = _pIn->get();
				token += currChar;
			}
			if(currChar != '"')
			token += currChar;
			currChar = _pIn->get();
			//token += currChar;
		} while (currChar != '"');
		currChar = _pIn->get();
	}
};

class EatSingleQuotedString : public ConsumeState
{
public:
	virtual void eatChars()																	//Method to eat single quoted string when eatSingleQuotedString state is set
	{
		token.clear();
		//std::cout << "\n\n Demonstrating eating single quoted string";
		do
		{
			if (!_pIn->good())
				return;
			if (currChar == '\\' && _pIn->peek() == '\'')
			{
				prevChar = currChar;
				currChar = _pIn->get();
				token += currChar;
			}
			if (currChar != '\'')
				token += currChar;
			currChar = _pIn->get();
		} while (currChar != '\'');
		currChar = _pIn->get();
	}
};

class EatSpecialSingleChar : public ConsumeState
{
public:
	virtual void eatChars()																		//Method to eat special single character when eatSpecialSingleChar state is set
	{
		token.clear();
		//std::cout << "\n\n Demonstrating eating special single characters";
		if (!_pIn->good())
			return;
		if (currChar == '\\' && _pIn->peek() == 'n')
		{
			prevChar = currChar;
			token += prevChar;
			currChar = _pIn->get();
			token += currChar;
		}
		else 
		{
			token += currChar;
		}
		currChar = _pIn->get();
	}
};

class EatSpecialDoubleChar : public ConsumeState
{
public:
	virtual void eatChars()																			//Method to eat special character pair when eatSpecialCharPair state is set
	{
		token.clear();
		//std::cout << "\n\n Demonstrating eating special character pair";
		if (!_pIn->good())
			return;
		prevChar = currChar;
		token += prevChar;
		currChar = _pIn->get();
		token += currChar;
		currChar = _pIn->get();
	}
};

ConsumeState::ConsumeState()																		//Constructor
{
  if (resetFirst)
  {
	  resetFirst = false;
    _pEatAlphanum = new EatAlphanum();
    _pEatCComment = new EatCComment();
    _pEatCppComment = new EatCppComment();
    _pEatPunctuator = new EatPunctuator();
    _pEatWhitespace = new EatWhitespace();
    _pEatNewline = new EatNewline();
	_pEatDoubleQuotedString = new EatDoubleQoutedString();
	_pEatSingleQuotedString = new EatSingleQuotedString();
    _pState = _pEatWhitespace;
	_pEatSpecialSingleChar = new EatSpecialSingleChar();
	_pEatSpeicalDoubleChar = new EatSpecialDoubleChar();
  }
}

ConsumeState::~ConsumeState()																		//Destructor
{
  if (resetSecond)
  {
    resetSecond = false;
    delete _pEatAlphanum;
    delete _pEatCComment;
    delete _pEatCppComment;
    delete _pEatPunctuator;
    delete _pEatWhitespace;
    delete _pEatNewline;
	delete _pEatDoubleQuotedString;
	delete _pEatSingleQuotedString;
	delete _pEatSpecialSingleChar;
	delete _pEatSpeicalDoubleChar;
  }
}

Toker::Toker() : pConsumer(new EatWhitespace()) {}													//Constructor

void Toker::reset() { pConsumer->resetConsumeState(); }												//to access resetConsumeState method

Toker::~Toker() { delete pConsumer; }

bool Toker::attach(std::istream* pIn)																//to create a reference to file
{
  if (pIn != nullptr && pIn->good())
  {
    pConsumer->attach(pIn);
    return true;
  }
  return false;
}

std::string Toker::getTok()																			//to get tokens from the input stream
{
  while(true) 
  {
    if (!pConsumer->canRead())
      return "";
    pConsumer->consumeChars();
    if (pConsumer->hasTok())
      break;
  }
  return pConsumer->getTok();
}

bool Toker::canRead() { return pConsumer->canRead(); }												//to access canRead() method in ConsumeState class

bool Toker::addSpecialSingleChars(std::string addssc)												//to access setSpecialSingleChars() method in ConsumeState class
{
	pConsumer->setSpecialSingleChars(addssc);
	return true;
	
}

bool Toker::addSpecialCharPairs(std::string addscp)												//to access setSpecialCharPairs() method in ConsumeState class
{
	pConsumer->setSpecialCharPairs(addscp);
	return true;
}

void testLog(const std::string& msg)															//to get the message from nextstate() method
{
#ifdef TEST_LOG
  std::cout << "\n  " << msg;
#endif
}

//----< test stub >--------------------------------------------------

#ifdef TEST_TOKENIZER

#include <fstream>

int main()
{
  //std::string fileSpec = "../Tokenizer/Tokenizer.cpp";
  //std::string fileSpec = "../Tokenizer/Tokenizer.h";
  std::string fileSpec = "../Tokenizer/Test.txt";

  std::ifstream in(fileSpec);
  if (!in.good())
  {
    std::cout << "\n  can't open " << fileSpec << "\n\n";
    return 1;
  }
  Toker toker;
  toker.attach(&in);
  do
  {
    std::string tok = toker.getTok();
    if (tok == "\n")
      tok = "newline";
    std::cout << "\n -- " << tok;
  } while (in.good());

  std::cout << "\n\n";
  return 0;
}
#endif
