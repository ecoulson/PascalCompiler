#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#define BUFFER_SIZE 1000

#pragma region Enums

enum TokenType {
    AND,
    ARRAY,
    BEGIN,
    CASE,
    CONST,
    DIV,
    DO,
    DOWNTO,
    END,
    ELSE,
    PASCAL_FILE,
    FOR,
    FORWARD,
    FUNCTION,
    GOTO,
    IF,
    IN,
    INTERFACE,
    LABEL,
    MAIN,
    MOD,
    NIL,
    NOT,
    OF,
    OR,
    PACKED,
    PROCEDURE,
    PROGRAM,
    RECORD,
    REPEAT,
    SET,
    THEN,
    TO,
    TYPE,
    UNTIL,
    VAR,
    WHILE,
    WITH,
    DEFINE,
    EXTRN,
    EXTERNAL,
    MODULE,
    OTHERWISE,
    PRIVE,
    PUBLIC,
    STATIC,
    UNIV,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    EQUAL,
    NOT_EQUAL,
    LESS_THAN,
    GREATER_THAN,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    DOT,
    COMMA,
    ASSIGNMENT,
    COLON,
    SEMICOLON,
    LEFT_PARENTHESES,
    RIGHT_PARENTHESES,
    LESS_THAN_OR_EQUAL,
    GREATER_THAN_OR_EQUAL,
    INTEGER,
    REAL,
    UNIT,
    CHARACTER,
    BOOLEAN,
    WHITESPACE,
    NUMBER,
    IDENTIFIER,
    STRING
};

enum SyntaxNodeType {
    IDENTIFIER_NODE,
    PROGRAM_NODE,
    UNIT_NODE,
    PROGRAM_HEADING_NODE,
    IDENTIFIER_LIST_NODE,
};

#pragma endregion
#pragma region TypeDef

typedef struct TokenStruct {
    char* value;
    enum TokenType type;
} Token;

typedef struct NodeListStruct {
    int size;
    int capacity;
    struct SyntaxNodeStruct** array;
} NodeList;

typedef struct SyntaxNodeStruct {
    int value;
    char* data;
    enum SyntaxNodeType type;
    struct NodeListStruct* nodes;
} SyntaxNode;



#pragma endregion
#pragma region FunctionDefs

// Lex
void lex(FILE* file);
Token* createToken(char* data, enum TokenType type);
void printToken(Token* token);
char* readIdentifier(FILE* file, char startingChar);
char* readNumber(FILE* file, char startingChar);
char* readString(FILE* file, char openingQuote);
void readComment(FILE* file);

// Parse
SyntaxNode* parse();
SyntaxNode* parseProgram();
SyntaxNode* parseProgramHeading();
SyntaxNode* parseBlock();
SyntaxNode* readIdentifierList();
Token* readNext(enum TokenType type);
int isNext(enum TokenType type);

// NodeList
void resize(NodeList* list);
NodeList* createNodeList();
void addNode(NodeList* list, SyntaxNode* node);
SyntaxNode* getNode(NodeList* list, int i);

#pragma endregion
#pragma region Code

#pragma region Globals
Token* tokenBuffer[BUFFER_SIZE];
int bufferIndex = 0;
#pragma endregion

int main(int argc, char *argv[]) {
    int i;
    if( argc != 2 )
    {
        printf("Must pass a file to be compiled\n");
        exit(EXIT_FAILURE);
    }
    FILE* input = fopen(argv[1], "r");
    lex(input);
    SyntaxNode* root = parse();
    return 0;
}

#pragma region Lex
void lex(FILE* file) {
    char ch = fgetc(file);
    while (ch != EOF) {
        if (ch == '<') {
            ch = fgetc(file);
            if (ch == '>') {
                tokenBuffer[bufferIndex++] = createToken("<>", NOT_EQUAL);
                ch = fgetc(file);
            } else if (ch == '=') {
                tokenBuffer[bufferIndex++] = createToken("<=", LESS_THAN_OR_EQUAL);
                ch = fgetc(file);
            } else {
                tokenBuffer[bufferIndex++] = createToken("<", LESS_THAN);
                ch = fgetc(file);
            }
        }
        if (ch == ':') {
            ch = fgetc(file);
            if (fgetc(file) == '=') {
                tokenBuffer[bufferIndex++] = createToken(":=", ASSIGNMENT);
                ch = fgetc(file);
            } else {
                fseek(file, -1, SEEK_CUR);
                tokenBuffer[bufferIndex++] = createToken(":", COLON);
            }
        }
        if (ch == '/') {
            if (fgetc(file) == '/') {
                readComment(file);
                ch = fgetc(file);
            } else {
                fseek(file, -1, SEEK_CUR);
                tokenBuffer[bufferIndex++] = createToken("/", DIVISION);
            }
        }
        if (ch >= '0' && ch <= '9') {
            tokenBuffer[bufferIndex++] = createToken(readNumber(file, ch), NUMBER);
        }
        if (ch == '"' || ch == '\'') {
            tokenBuffer[bufferIndex++] = createToken(readString(file, ch), STRING);
        }
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            char* identifier = readIdentifier(file, ch);
            if (strcasecmp(identifier, "and") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, AND);
            } else if (strcasecmp(identifier, "array") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, ARRAY);
            } else if (strcasecmp(identifier, "begin") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, BEGIN);
            } else if (strcasecmp(identifier, "boolean") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, BOOLEAN);
            } else if (strcasecmp(identifier, "character") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, CHARACTER);
            } else if (strcasecmp(identifier, "case") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, CASE);
            } else if (strcasecmp(identifier, "const") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, CONST);
            } else if (strcasecmp(identifier, "div") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, DIV);
            } else if (strcasecmp(identifier, "do") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, DO);
            } else if (strcasecmp(identifier, "downto") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, DOWNTO);
            } else if (strcasecmp(identifier, "end") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, END);
            } else if (strcasecmp(identifier, "else") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, ELSE);
            } else if (strcasecmp(identifier, "file") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, PASCAL_FILE);
            } else if (strcasecmp(identifier, "for") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, FOR);
            } else if (strcasecmp(identifier, "forward") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, FORWARD);
            } else if (strcasecmp(identifier, "function") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, FUNCTION);
            } else if (strcasecmp(identifier, "goto") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, GOTO);
            } else if (strcasecmp(identifier, "if") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, IF);
            } else if (strcasecmp(identifier, "in") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, IN);
            } else if (strcasecmp(identifier, "integer") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, INTEGER);
            } else if (strcasecmp(identifier, "interface") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, INTERFACE);
            } else if (strcasecmp(identifier, "label") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, LABEL);
            } else if (strcasecmp(identifier, "main") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, MAIN);
            } else if (strcasecmp(identifier, "mod") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, MOD);
            } else if (strcasecmp(identifier, "nil") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, NIL);
            } else if (strcasecmp(identifier, "not") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, NOT);
            } else if (strcasecmp(identifier, "of") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, OF);
            } else if (strcasecmp(identifier, "or") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, OR);
            } else if (strcasecmp(identifier, "packed") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, PACKED);
            } else if (strcasecmp(identifier, "procedure") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, PROCEDURE);
            } else if (strcasecmp(identifier, "program") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, PROGRAM);
            } else if (strcasecmp(identifier, "real") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, REAL);
            } else if (strcasecmp(identifier, "record") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, RECORD);
            } else if (strcasecmp(identifier, "repeat") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, REPEAT);
            } else if (strcasecmp(identifier, "set") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, SET);
            } else if (strcasecmp(identifier, "then") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, THEN);
            } else if (strcasecmp(identifier, "to") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, TO);
            } else if (strcasecmp(identifier, "type") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, TYPE);
            } else if (strcasecmp(identifier, "unit") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, UNIT);
            } else if (strcasecmp(identifier, "until") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, UNTIL);
            } else if (strcasecmp(identifier, "var") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, VAR);
            } else if (strcasecmp(identifier, "while") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, WHILE);
            } else if (strcasecmp(identifier, "with") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, WITH);
            } else if (strcmp(identifier, "") != 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, IDENTIFIER);
            }
        }
        switch (ch)
        {
            case '+':
                tokenBuffer[bufferIndex++] = createToken("+", ADDITION);
                break;
            case '-':
                tokenBuffer[bufferIndex++] = createToken("-", SUBTRACTION);
                break;
            case '*':
                tokenBuffer[bufferIndex++] = createToken("*", MULTIPLICATION);
                break;
            case '>':
                tokenBuffer[bufferIndex++] = createToken(">", GREATER_THAN);
                break;
            case '[':
                tokenBuffer[bufferIndex++] = createToken("[", LEFT_BRACKET);
                break;
            case ']':
                tokenBuffer[bufferIndex++] = createToken("]", RIGHT_BRACKET);
                break;
            case '(':
                tokenBuffer[bufferIndex++] = createToken("(", LEFT_PARENTHESES);
                break;
            case ')':
                tokenBuffer[bufferIndex++] = createToken(")", RIGHT_PARENTHESES);
                break;
            case '.':
                tokenBuffer[bufferIndex++] = createToken(".", DOT);
                break;
            case ',':
                tokenBuffer[bufferIndex++] = createToken(",", COMMA);
                break;
            case ';':
                tokenBuffer[bufferIndex++] = createToken(";", SEMICOLON);
                break;
            case ' ':
            case '\t':
            case '\n':
            case '\r':
                break;
            default: 
                break;
        }
        ch = fgetc(file);
    }
}

Token* createToken(char* data, enum TokenType type) {
    Token* token = (Token*)malloc(sizeof(Token));
    token -> type = type;
    token -> value = data;
    return token;
}

void printToken(Token* token) {
    printf("Token\n data: \"%s\", type \"%d\"\n", token -> value, token -> type);
}

char* readNumber(FILE* file, char startingChar) {
    int size = 0;
    char ch = startingChar;
    int hasDot = 0;
    while (ch != EOF && (((ch >= '0' && ch <= '9') || (ch == '.' && hasDot == 0)))) {
        if (ch == '.') {
            hasDot = 1;
        }
        size++;
        ch = fgetc(file);
    }
    fseek(file, -size + 1, SEEK_CUR);

    char* number = (char*)malloc(sizeof(char) * size + 1);
    int i = 0;
    number[i++] = startingChar;
    number[size] = '\0';
    ch = startingChar;
    while (ch != EOF && i < size) {
        ch = fgetc(file);
        number[i++] = ch;
    }
    return number;
}

char* readIdentifier(FILE* file, char startingChar) {
    int size = 0;
    char ch = startingChar;
    while (ch != EOF && ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')  || ch == '_')) {
        size++;
        ch = fgetc(file);
    }
    fseek(file, -size, SEEK_CUR);

    char* identifier = (char*)malloc(sizeof(char) * size + 1);
    int i = 0;
    identifier[i++] = startingChar;
    identifier[size] = '\0';
    ch = startingChar;
    while (ch != EOF && i < size) {
        ch = fgetc(file);
        identifier[i++] = ch;
    }
    return identifier;
}

char* readString(FILE* file, char openingQuote) {
    int size = 0;
    char startingChar = fgetc(file);
    char ch = startingChar;
    while (ch != EOF && ch != openingQuote) {
        size++;
        ch = fgetc(file);
    }
    fseek(file, -size, SEEK_CUR);

    char* string = (char*)malloc(sizeof(char) * size + 1);
    int i = 0;
    string[i++] = startingChar;
    string[size] = '\0';
    while (ch != EOF && i < size) {
        ch = fgetc(file);
        string[i++] = ch;
    }
    fgetc(file);
    return string;
}

void readComment(FILE* file) {
    char ch = fgetc(file);
    while (ch != '\n') {
        ch = fgetc(file);
    }
}

#pragma endregion

#pragma region Parser
// https://github.com/antlr/grammars-v4/blob/master/pascal/pascal.g4`

SyntaxNode* createNode() {
    return (SyntaxNode*)malloc(sizeof(SyntaxNode));
}

SyntaxNode* parse() {
    bufferIndex = 0;
    return parseProgram();
}

SyntaxNode* parseProgram() {
    SyntaxNode* root = (SyntaxNode*)malloc(sizeof(SyntaxNode*));
    root -> type = PROGRAM_NODE;
    NodeList* nodes = createNodeList();

    addNode(nodes, parseProgramHeading());

    if (tokenBuffer[bufferIndex] -> type == INTERFACE) {
        bufferIndex++;
    }

    while (tokenBuffer[bufferIndex++] -> type != DOT) {
        addNode(nodes, parseBlock());
    }
    root -> nodes = nodes;
    return root;
}

SyntaxNode* parseProgramHeading() {
    SyntaxNode* node = createNode();
    NodeList* list = createNodeList();
    Token* name;
    if (isNext(UNIT)) {
        readNext(UNIT);
        node -> type = UNIT_NODE;
        name = readNext(IDENTIFIER);
        node -> data = name -> value;
    } else {
        readNext(PROGRAM);
        node -> type = PROGRAM_HEADING_NODE;
        name = readNext(IDENTIFIER);
        if (isNext(LEFT_PARENTHESES) == 1) {
            readNext(LEFT_PARENTHESES);
            SyntaxNode* idList = readIdentifierList();
            for (int i = 0; i < idList -> nodes -> size; i++) {
                addNode(list, getNode(idList -> nodes, i));
            }
            free(idList -> nodes);
            free(idList);
            readNext(RIGHT_PARENTHESES);
        }
    }
    node -> nodes = list;
    node -> data = name -> value;
    readNext(SEMICOLON);
    return node;
}

SyntaxNode* readIdentifierList() {
    SyntaxNode* node = createNode();
    NodeList* list = createNodeList();
    node -> type = IDENTIFIER_LIST_NODE;
    list -> size = 0;

    SyntaxNode* identifierNode = createNode();
    Token* identifier = readNext(IDENTIFIER);
    identifierNode -> type = IDENTIFIER_NODE;
    identifierNode -> data = identifier -> value;
    addNode(list, identifierNode);
    while (isNext(COMMA) == 1) {
        readNext(COMMA);
        SyntaxNode* identifierNode = createNode();
        Token* identifier = readNext(IDENTIFIER);
        identifierNode -> type = IDENTIFIER_NODE;
        identifierNode -> data = identifier -> value;
        addNode(list, identifierNode);
    }
    node -> nodes = list;
    return node;
}

SyntaxNode* parseBlock() {
    return NULL;
}

Token* readNext(enum TokenType type) {
    if (tokenBuffer[bufferIndex] -> type != type) {
        printf("Expected next token to be type %d", type);
        exit(1);
    }
    return tokenBuffer[bufferIndex++];
}

int isNext(enum TokenType type) {
    return tokenBuffer[bufferIndex] -> type == type;
}

#pragma endregion

#pragma region List

NodeList* createNodeList() {
    NodeList* list = (NodeList*)malloc(sizeof(NodeList));
    list -> size = 0;
    list -> capacity = 0;
    list -> array = (SyntaxNode**)malloc(0);
    return list;
}

void addNode(NodeList* list, SyntaxNode* node) {
    if (list -> size + 1 >= list -> capacity) {
        resize(list);
    }
    list -> array[list -> size] = node;
    list -> size++;
}

void resize(NodeList* list) {
    if (list -> size == 0) {
        list -> capacity = 4;
    } else {
        list -> capacity *= 2;
    }
    SyntaxNode** resizedList = (SyntaxNode**)malloc(sizeof(SyntaxNode) * list -> capacity);
    for (int i = 0; i < list -> size; i++) {
        resizedList[i] = list -> array[i];
    }
    free(list -> array);
    list -> array = resizedList;
}

SyntaxNode* getNode(NodeList* list, int i) {
    return list -> array[i];
}

#pragma endregion

#pragma endregion