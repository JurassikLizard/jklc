#include "./includes/lexer.h"

#include <cstring>
#include <iostream>
#include <stdlib.h>

using namespace std;

Lexer::Lexer(char *src): CurChar('\0'), CurPos(-1), Source(src) {
    Lexer::NextChar();
}

void Lexer::NextChar() {
    CurPos += 1;
    if(CurPos >= strlen(Source)) {
        CurChar = '\0'; // EOF
    }
    else {
        CurChar = Source[CurPos];
    }
}

char Lexer::Peek() {
    if(CurPos + 1 >= strlen(Source)) {
        return '\0';
    }
    return Source[CurPos + 1];
}

Token *Lexer::GetToken() {
    Token *token = NULL;

    SkipWhitespace();
    SkipComment();

    switch(CurChar) {
        case '+':
            token = new Token(string(1, CurChar).c_str(), PLUS);
            break;
        case '-':
            token = new Token(string(1, CurChar).c_str(), MINUS);
            break;
        case '*':
            token = new Token(string(1, CurChar).c_str(), ASTERISK);
            break;
        case '/':
            token = new Token(string(1, CurChar).c_str(), SLASH);
            break;
        case '\n':
            token = new Token(string(1, CurChar).c_str(), NEWLINE);
            break;
        case '\0':
            token = new Token(string(1, CurChar).c_str(), END_OF_FILE);
            break;
        case '=':
            if(Peek() == '=') { // ==
                char lastChar = CurChar;
                NextChar();
                token = new Token((string(1, lastChar) + CurChar).c_str(), EQEQ);
            }
            else {
                token = new Token(string(1, CurChar).c_str(), EQ);
            }
            break;
        case '>':
            if(Peek() == '=') { // >=
                char lastChar = CurChar;
                NextChar();
                token = new Token((string(1, lastChar) + CurChar).c_str(), GTEQ);
            }
            else {
                token = new Token(string(1, CurChar).c_str(), GT);
            }
            break;
        case '<':
            if(Peek() == '=') { // <=>
                char lastChar = CurChar;
                NextChar();
                token = new Token((string(1, lastChar) + CurChar).c_str(), LTEQ);
            }
            else {
                token = new Token(string(1, CurChar).c_str(), EQ);
            }
            break;
        case '!':
            if(Peek() == '=') { // !=
                char lastChar = CurChar;
                NextChar();
                token = new Token((string(1, lastChar) + CurChar).c_str(), NOTEQ);
            }
            else {
                //token = new Token(string(1, CurChar).c_str(), EQ);
                Abort("Expected !=, got !");
            }
            break;
        default:
            string str = "Unkown Token: ";
            str.append(string(1, CurChar));
            str.append(string(1, '\n'));
            Abort(str.c_str());
            break;
    }

    NextChar();
    return token;
}

void Lexer::Abort(const char *msg) {
    cout << msg;
    exit(-1);
}

void Lexer::SkipWhitespace() {
    while (CurChar == ' ' || CurChar == '\t' || CurChar == '\n' || CurChar == '\n') {
        NextChar();
    }
}

void Lexer::SkipComment() {
    if (CurChar == '/' && Peek() == '/') { // '//'
        while (CurChar != '\n') {
            NextChar();
        }
    }
}

Token::Token(const char *tokText, int tokKind) : Text(tokText), Kind(tokKind) {

}