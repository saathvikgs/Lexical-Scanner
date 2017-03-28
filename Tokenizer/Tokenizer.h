#ifndef TOKENIZER_H
#define TOKENIZER_H
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
 This package provides a public Toker class and private ConsumeState class.
* Toker reads words from a std::stream, throws away whitespace
* and returns comments and words from the stream in the order encountered.  Quoted
* strings and certain punctuators and newlines are returned as single tokens.
* Special single characters and special double character pairs are returned as single tokens
* This is a new version, based on the State Design Pattern.  Older versions
* exist, based on an informal state machine design.
 * This is a new version, based on the State Design Pattern.  Older versions
 * exist, based on an informal state machine design.
 *
 * Public Interface:
 * -----------------
 *  bool attach(std::istream* pIn) - Attach pointer of file stream to ConsumeState pointer.
 *
 *  std::string getTok() - returns one token as a string(eg. alphanum or special character etc.)
 *
 *  bool canRead() - Check whether characters are available to read from file stream.
 *
 *  bool addSpecialSingleChars(std::string addssc) - Add a particular string to the default list of
 *                                                Single Character tokens.
 *
 *  bool addSpecialCharPairs(std::string addscp) - Add a particular string to the default list of
 *                                              Double Character tokens.
 *
 *
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
 * - added methods to set Special Single and Double character tokens
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
#include <iosfwd>
#include <string>
#include<vector>
#include<algorithm>

namespace Scanner
{
  class ConsumeState;

  class Toker
  {
  public:
    Toker();                                           //Constructor
    Toker(const Toker&) = delete;					   //Constructor
    ~Toker();										   //Destructor
    Toker& operator=(const Toker&) = delete;
    bool attach(std::istream* pIn);					  //Method to create a reference to the file
    std::string getTok();							  //Method to get tokens from file
    bool canRead();									 //Method to check 
	bool addSpecialSingleChars(std::string addssc);  //Method to add special single character
	bool addSpecialCharPairs(std::string addscp);    //Method to add special character pair
	void reset();									 //Method to access the resetConsumeState method in ConsumeState class
  private:
    ConsumeState* pConsumer;						// Pointer to ConsumeState class
  };
}
#endif
#define a