#include <iostream>
#include <cstring>
using namespace std;

#include "./includes/lexer.h"

int main (int argc, char *argv[]) {
    char *src = "+- */ >>= = !=";
    Lexer *lexer = new Lexer(src);

    Token *token = lexer->GetToken();
    if(token == NULL){
        return 0;
    }
    while(token->Kind != END_OF_FILE) {
        cout << token->Kind << ' ';
        token = lexer->GetToken();
    }
    cout << "\ntest\n" << strlen(src);
    return 0;
}