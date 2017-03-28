#ifndef SEMIEXPRESSION_H
#define SEMIEXPRESSION_H
///////////////////////////////////////////////////////////////////////////////
// Tokenizer.h - read words from a std::stream                               //
// ver 3.4                                                                   //
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
* -------------------
* This package provides a public SemiExp class that collects and makes
* available sequences of tokens.  SemiExp uses the services of a Toker
* class to acquire tokens.  Each call to SemiExp::get() returns a
* sequence of tokens that ends in {.  This will be extended to use the
* full set of terminators: {, }, ;, and '\n' if the line begins with #.
*
* This is a new version for students in CSE687 - OOD, Spring 2016 to use
* for Project #1.
*
*  Public Interface:
*  ---------------------------------
*  size_t length() - to obtain the length of the vector containg tokens
*
*  void push_back(const std::string& tok) - to push the string into the vector containing tokens
*
*  bool remove(const std::string& tok) - to remove token from the vector upon matching of the string passed as argument
*
* remove(size_t n) - function to remove the token at index n
*
*  toLower() - Convert all the upper case leeters in the semi expression to lower case
*
* trimFront() - Remove all leading newline characters in the semi expression
*
* clear() - Remove all the existing tokens in the semi expression
*
* bool get_for(std::string& tok) - to get semiexpression when for loop is encountered
*
* Maintenance History:
* --------------------
* ver 3.4 : 10 Feb 2016
* - Implemented the interface ITokCollection
* - added public :, protected :, private : as terminators
* - provided a rule to termination of collection of tokens on certian cases
* ver 3.3 : 08 Feb 2016
* - New comments and functions are added
* ver 3.2 : 02 Feb 2016
* - declared SemiExp copy structor and assignment operator = delete
* - added default argument for Toker pointer to nullptr so SemiExp
*   can be used like a container of tokens.
* - if pToker is nullptr then get() will throw logic_error exception
* ver 3.1 : 30 Jan 2016
* - changed namespace to Scanner
* - fixed bug in termination due to continually trying to read
*   past end of stream if last tokens didn't have a semiExp termination
*   character
* ver 3.0 : 29 Jan 2016
* - built in help session, Friday afternoon
*
* Build Process:
* --------------
* Required Files:
*   SemiExpression.h, SemiExpression.cpp, Tokenizer.h, Tokenizer.cpp,ITokCollection.h
*
* Build Command: devenv Project1.sln /rebuild debug
*
*/

#include <vector>
#include "../Tokenizer/Tokenizer.h"
#include "./ITokCollection.h"
namespace Scanner
{
  using Token = std::string;

  class SemiExp : ITokCollection
  {
  public:
    SemiExp(Toker* pToker = nullptr);
    SemiExp(const SemiExp&) = delete;
    SemiExp& operator=(const SemiExp&) = delete;
    //Token operator[](size_t n);
    size_t length();														//returns the length of the vector containing the tokens
	bool get(bool clear = true);											//to get tokens and make turn them into semi expressions
	std::string& operator[](int n);											//to get the tokens at position n from the vector
	size_t find(const std::string& tok);									//to find the position of the string token in vector. Returns the position when the string passed as argument is found in the vector 
	void push_back(const std::string& tok);									//push the string passed as argument into the vector
	bool remove(const std::string& tok);									//remove the string token passed as argument from the vector
	bool remove(size_t i);													//remove the token from the vector at position which is passed as argument
	void toLower();															//convert the token in the vector into lower case
	void trimFront();														//to trim the leading whitespaces
	void clear();															//to clear the vector containing tokens
	std::string show(bool showNewLines = false);							//to display the tokens in the vector and to display new lines based on a boolean value passed as argument						
	bool get_for(std::string& tok);											//to get semi expressions when token for is encountered
  private:
    std::vector<Token> _tokens;												//vector to hold tokens
    Toker* _pToker;															//pointer to toker class
  };
}
#endif
