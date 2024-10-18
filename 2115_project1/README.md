This is the gitlab repo where you submit everything for your final project part 1. Please modify this readme file.

Title:Lexical Scanner for a Custom Programming Language(including Json)

Name: Kenina Wang

Student Number: B00956129

Course Number: CSCI2115


Requirements

Install PyCharm CE


How to run

-Clone the project file to your local computer and open it with PyCharm CE

-Run the code and enter the text to be parsed when you see the prompt "Please input your text (like '(2e+3 + 8) * 23'):"

-Enter a JSON fragment, such as {"name": "Alice", "age": 25}, and the program will parse and output a tokenized Token list.


Input and Output: 

input:{"name": "Alice", "age": 25} 

output: 

<Token(LBRACE,{ )> 

<Token(STRING,name )> 

<Token(COLON ,: )> 

<Token(STRING,Alice )> 

<Token(COMMA,, )> 

<Token(STRING,age )> 

<Token(COLON ,: )> 

<Token(NUMBER,25.0 )> 

<Token(RBRACE,} )>


Assumptions

The input should be a valid JSON fragment, such as an object, array, string, number, boolean, etc.

The program assumes that the string is surrounded by single or double quotes ". Unescaped special characters are not supported.


Code Explanation

Token Class:

Defines different Token types in JSON, such as {, }, [, ], :, ,, strings, numbers, etc.

TokenType Class:

Contains the type of Token and the corresponding value.

LexerError Class:

Used to throw exceptions and locate errors

Scanner Class:

It is the core part of the code:

advance(): advance to the next character position.

skip_space(): skip whitespace characters.

recognize_num(): recognize numbers, including integers, floating point numbers, and scientific notation.

recognize_str(): recognize strings and handle characters surrounded by single and double quotes.

getNextToken(): The main parsing method, parses JSON character by character and generates a Token list.








