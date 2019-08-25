#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#define BUFFER_SIZE 10000

#pragma region Enums

enum TokenType {
    AND,
    AT,
    ARRAY,
    BEGIN,
    CASE,
    CHR,
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
    IMPLEMENTATION,
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
    STR,
    THEN,
    TO,
    TYPE,
    UNTIL,
    USES,
    VAR,
    WHILE,
    WITH,
    DEFINE,
    EXTRN,
    EXTERNAL,
    MODULE,
    OTHERWISE,
    PRIVATE,
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
    POINTER,
    UNIT,
    CHARACTER,
    CHAR,
    BOOLEAN,
    WHITESPACE,
    NUMBER,
    IDENTIFIER,
    STRING
};

enum SyntaxNodeType {
    STRING_TYPE_NODE,
    SUBRANGE_TYPE_NODE,
    IDENTIFIER_NODE,
    NUMBER_NODE,
    STRING_NODE,
    PROGRAM_NODE,
    UNIT_NODE,
    PROGRAM_HEADING_NODE,
    IDENTIFIER_LIST_NODE,
    BLOCK_NODE,
    LABEL_DECLARATION_LIST_NODE,
    CONSTANT_DEFINITION_LIST_NODE,
    CONSTANT_DEFINITION_NODE,
    CHAR_CONSTANT_NODE,
    NEGATIVE_SIGN_NODE,
    POSITIVE_SIGN_NODE,
    SIGNED_NUMBER_NODE,
    SIGNED_IDENTIFIER_NODE,
    TYPE_DEFINITION_LIST_NODE,
    TYPE_DEFINITION_NODE,
    TYPE_IDENTIFIER_NODE,
    SCALAR_NODE,
    STRUCTURED_TYPE_NODE,
    PACKED_STRUCTURE_NODE,
    ARRAY_TYPE_NODE,
    TYPE_LIST_NODE,
    SET_TYPE_NODE,
    RECORD_TYPE_NODE,
    FIELD_LIST_NODE,
    RECORD_SECTION_LIST_NODE,
    RECORD_SECTION_NODE,
    VARIANT_LIST_NODE,
    VARIANT_NODE,
    TAG_NODE,
    CONSTANT_LIST_NODE,
    FILE_TYPE_NODE,
    POINTER_TYPE_NODE,
    VARIABLE_DECLARATION_LIST_NODE,
    VARIABLE_DECLARATION_NODE,
    PROCEDURE_DECLARATION_NODE,
    FORMAL_PARAMETER_LIST_NODE,
    FORMAL_PARAMETER_SECTION_NODE,
    PARAMETER_GROUP_NODE,
    VAR_PARAMETER_GROUP_NODE,
    FUNCTION_PARAMETER_GROUP_NODE,
    PROCEDURE_PARAMETER_GROUP_NODE,
    FUNCTION_DECLARATION_NODE,
    USES_UNITS_NODE,
    COMPOUND_STATEMENT_NODE,
    STATEMENTS_NODE,
    STATEMENT_NODE,
    UNLABELLED_STATEMENT_NODE,
    SIMPLE_STATEMENT_NODE,
    ASSIGNMENT_STATEMENT_NODE,
    VARIABLE_NODE,
    EXPRESSION_NODE,
    RELATIONAL_OPERATOR_NODE,
    SIMPLE_EXPRESSION_NODE,
    ADDITIVE_OPERATOR_NODE,
    TERM_NODE,
    MULTIPLICATIVE_OPERATOR_NODE,
    SIGNED_FACTOR_NODE,
    FACTOR_NODE,
    UNSIGNED_CONSTANT_NODE,
    FUNCTION_DESIGNATOR_NODE,
    PARAMETER_LIST_NODE,
    SET_NODE,
    ELEMENT_LIST_NODE,
    ELEMENT_NODE,
    PROCEDURE_STATEMENT_NODE,
    ACTUAL_PARAMETER_NODE,
    PARAMETER_WIDTH_NODE,
    GOTO_STATEMENT_NODE,
    EMPTY_STATEMENT_NODE,
    EMPTY_NODE,
    STRUCTURED_STATEMENT_NODE,
    CONDITIONAL_STATEMENT_NODE,
    IF_STATEMENT_NODE,
    CASE_STATEMENT_NODE,
    CASE_LIST_ELEMENT_NODE,
    REPETATIVE_STATEMENT_NODE,
    WHILE_STATEMENT_NODE,
    REPEAT_STATEMENT_NODE,
    FOR_STATEMENT_NODE,
    FOR_LIST_NODE,
    INITIAL_VALUE_NODE,
    FINAL_VALUE_NODE,
    WITH_STATEMENT_NODE,
    RECORD_VARIABLE_LIST_NODE
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
    char* data;
    enum SyntaxNodeType type;
    struct NodeListStruct* nodes;
} SyntaxNode;



#pragma endregion
#pragma region FunctionDefs

void lex(FILE* file);
Token* createToken(char* data, enum TokenType type);
void printToken(Token* token);
char* readIdentifier(FILE* file, char startingChar);
char* readNumber(FILE* file, char startingChar);
char* readString(FILE* file, char openingQuote);
void readComment(FILE* file);
void printTokenBuffer();

// Parse
void printNode(SyntaxNode* node, int depth);
SyntaxNode* parse();
SyntaxNode* parseProgram();
SyntaxNode* parseProgramHeading();
SyntaxNode* parseIdentifierList();
SyntaxNode* parseIdentifier();
SyntaxNode* parseBlock();
int blockIsNext();
SyntaxNode* parseLabelDeclarationList();
SyntaxNode* parseConstantDefinitionList();
SyntaxNode* readConstantDefinition();
SyntaxNode* parseConstant();
SyntaxNode* parseNumber();
SyntaxNode* parseString();
SyntaxNode* parseSign();
SyntaxNode* parseCharConstant();
SyntaxNode* parseTypeDefinitionList();
SyntaxNode* parseTypeDefinition();
SyntaxNode* parseType();
int isNextSimpleType();
SyntaxNode* parseSimpleType();
int isTypeIdentifier();
SyntaxNode* parseTypeIdentifier();
int isStringType();
SyntaxNode* parseStringType();
SyntaxNode* parseScalar();
int isSubRangeType();
SyntaxNode* parseSubrangeType();
int isNextStructuredType();
SyntaxNode* parseStructuredType();
SyntaxNode* parseArrayType();
SyntaxNode* parseTypeList();
SyntaxNode* parseSetType();
SyntaxNode* parseFileType();
SyntaxNode* parseRecordType();
SyntaxNode* parseFieldList();
SyntaxNode* parseFixedPart();
SyntaxNode* parseRecordSection();
SyntaxNode* parseVariantPart();
SyntaxNode* parseTag();
SyntaxNode* parseVariant();
SyntaxNode* parseConstantList();
SyntaxNode* parsePointerType();
SyntaxNode* parseVariableDeclarationList();
SyntaxNode* parseVariableDeclaration();
SyntaxNode* parseProcedureDeclaration();
SyntaxNode* parseFormalParameterList();
SyntaxNode* parseFormalParameterSection();
SyntaxNode* parseParameterGroup();
SyntaxNode* parseFunctionDeclarationList();
SyntaxNode* parseUsesUnits();
SyntaxNode* parseCompoundStatement();
SyntaxNode* parseStatements();
SyntaxNode* parseStatement();
SyntaxNode* parseUnlabelledStatement();
int isAssignmentNext();
SyntaxNode* parseAssignmentStatement();
SyntaxNode* parseExpression();
SyntaxNode* parseExpression();
int isProcedureNext();
SyntaxNode* parseProcedureStatement();
SyntaxNode* parseParameterList();
SyntaxNode* parseActualParameter();
SyntaxNode* parseParameterWidth();
SyntaxNode* parseGotoStatement();
SyntaxNode* parseEmptyStatement();
Token* readNext(enum TokenType type);
int isNext(enum TokenType type);
int isNthTypeNext(enum TokenType type, int n);

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
    for (int i = 0; i < BUFFER_SIZE; i++) {
        tokenBuffer[i] = NULL;
    }
    FILE* input = fopen(argv[1], "r");
    lex(input);
    printTokenBuffer();
    SyntaxNode* root = parse();
    printNode(root, 0);
    return 0;
}

#pragma region Lex
char* getTokenType(enum TokenType type) {
    switch (type)
    {
    case AND:
        return "And Token";
    case ARRAY:
        return "Array Token";
    case BEGIN:
        return "Begin Token";
    case CASE:
        return "Case Token";
    case CHR:
        return "CHR Token";
    case CONST:
        return "Const Token";
    case DIV:
        return "Div Token";
    case DO:
        return "Do Token";
    case DOWNTO:
        return "Downto Token";
    case END:
        return "End Token";
    case ELSE:
        return "Else Token";
    case PASCAL_FILE:
        return "File Token";
    case FOR:
        return "For Token";
    case FORWARD:
        return "Forward Token";
    case FUNCTION:
        return "Function Token";
    case GOTO:
        return "Goto Token";
    case IF:
        return "If Token";
    case IN:
        return "In Token";
    case INTERFACE:
        return "Interface Token";
    case IMPLEMENTATION:
        return "Implementation Token";
    case LABEL:
        return "Label Token";
    case MAIN:
        return "Main Token";
    case MOD:
        return "Mod Token";
    case NIL:
        return "Nil Token";
    case NOT:
        return "Not Token";
    case OF:
        return "Of Token";
    case OR:
        return "Or Token";
    case PACKED:
        return "Packed Token";
    case PROCEDURE:
        return "Procedure Token";
    case PROGRAM:
        return "Program Token";
    case RECORD:
        return "Record Token";
    case REPEAT:
        return "Repeat Token";
    case SET:
        return "Set Token";
    case STR:
        return "String Keyword Token";
    case THEN:
        return "Then Token";
    case TO:
        return "To Token";
    case TYPE:
        return "Type Token";
    case UNTIL:
        return "Until Token";
    case USES:
        return "Uses Token";
    case VAR:
        return "Var Token";
    case WHILE:
        return "While Token";
    case WITH:
        return "With Token";
    case DEFINE:
        return "Define Token";
    case EXTRN:
        return "Extrn Token";
    case EXTERNAL:
        return "External Token";
    case MODULE:
        return "Module Token";
    case OTHERWISE:
        return "Otherwise Token";
    case PRIVATE:
        return "Private Token";
    case PUBLIC:
        return "Public Token";
    case STATIC:
        return "Static Token";
    case UNIV:
        return "Univ Token";
    case ADDITION:
        return "Addition Token";
    case SUBTRACTION:
        return "Subtraction Token";
    case MULTIPLICATION:
        return "Multiplication Token";
    case DIVISION:
        return "Division Token";
    case EQUAL:
        return "Equal Token";
    case NOT_EQUAL:
        return "Not Equal Token";
    case LESS_THAN:
        return "Less Than Token";
    case GREATER_THAN:
        return "Greater Than Token";
    case LEFT_BRACKET:
        return "Left Bracket Token";
    case RIGHT_BRACKET:
        return "Right Bracket Token";
    case DOT:
        return "Dot Token";
    case COMMA:
        return "Comma Token";
    case ASSIGNMENT:
        return "Assignment Token";
    case COLON:
        return "Colon Token";
    case SEMICOLON:
        return "Semicolon Token";
    case LEFT_PARENTHESES:
        return "Left Parentheses Token";
    case RIGHT_PARENTHESES:
        return "Right Parentheses Token";
    case LESS_THAN_OR_EQUAL:
        return "Less Than Or Equal Token";
    case GREATER_THAN_OR_EQUAL:
        return "Greater Than Or Equal Token";
    case INTEGER:
        return "Integer Token";
    case REAL:
        return "Real Token";
    case UNIT:
        return "Unit Token";
    case CHARACTER:
        return "Character Token";
    case CHAR:
        return "Char Token";
    case BOOLEAN:
        return "Boolean Token";
    case WHITESPACE:
        return "Whitespace Token";
    case NUMBER:
        return "Number Token";
    case IDENTIFIER:
        return "Identifier Token";
    case STRING:
        return "String Token";
    case POINTER:
        return "Pointer Token";
    case AT:
        return "At Token";
    default:
        return "Undefined Token";
    }
}

void printTokenBuffer() {
    printf("Tokens:\n");
    for (int i = 0; i < bufferIndex; i++) {
        printf("Token:\n\t type: %s\n\t data: %s\n", getTokenType(tokenBuffer[i] -> type), tokenBuffer[i] -> value);
    }
    printf("End Tokens\n");
}

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
            if (ch == '=') {
                tokenBuffer[bufferIndex++] = createToken(":=", ASSIGNMENT);
                ch = fgetc(file);
            } else {
                fseek(file, -1, SEEK_CUR);
                tokenBuffer[bufferIndex++] = createToken(":", COLON);
                ch = fgetc(file);
            }
        }
        if (ch == '/') {
            if (fgetc(file) == '/') {
                readComment(file);
            } else {
                fseek(file, -1, SEEK_CUR);
                tokenBuffer[bufferIndex++] = createToken("/", DIVISION);
                ch = fgetc(file);
            }
        }
        if (ch >= '0' && ch <= '9') {
            tokenBuffer[bufferIndex++] = createToken(readNumber(file, ch), NUMBER);
            ch = fgetc(file);
        }
        if (ch == '"' || ch == '\'') {
            tokenBuffer[bufferIndex++] = createToken(readString(file, ch), STRING);
            ch = fgetc(file);
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
            }  else if (strcasecmp(identifier, "char") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, CHAR);
            } else if (strcasecmp(identifier, "chr") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, CHR);
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
            } else if (strcasecmp(identifier, "implementation") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, IMPLEMENTATION);
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
            } else if (strcasecmp(identifier, "pointer") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, POINTER);
            } else if (strcasecmp(identifier, "real") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, REAL);
            } else if (strcasecmp(identifier, "record") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, RECORD);
            } else if (strcasecmp(identifier, "repeat") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, REPEAT);
            } else if (strcasecmp(identifier, "set") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, SET);
            } else if (strcasecmp(identifier, "string") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, STR);
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
            } else if (strcasecmp(identifier, "uses") == 0) {
                tokenBuffer[bufferIndex++] = createToken(identifier, USES);
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
            case '=':
                tokenBuffer[bufferIndex++] = createToken("=", EQUAL);
                break;
            case '@':
                tokenBuffer[bufferIndex++] = createToken("@", AT);
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
    memset(token, 0, sizeof(Token));
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
    int dots = 0;
    int wasDot = 0;
    while (ch != EOF && (((ch >= '0' && ch <= '9') || (ch == '.' && dots < 2)))) {
        if (ch == '.') {
            dots++;
            if (wasDot) {
                size--;
                break;
            }
            wasDot = 1;
        } else {
            wasDot = 0;
        }
        size++;
        ch = fgetc(file);
    }
    fseek(file, -size, SEEK_CUR);
    if (wasDot) {
        fseek(file, -1, SEEK_CUR);
    }

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

char* getNodeType(SyntaxNode* node) {
    switch (node -> type)
    {
        case IDENTIFIER_NODE:
            return "Identifier Node";
        case NUMBER_NODE:
            return "Number Node";
        case STRING_NODE:
            return "String Node";
        case STRING_TYPE_NODE:
            return "String Type Node";
        case SIGNED_IDENTIFIER_NODE:
            return "Signed Identifier Node";
        case SIGNED_NUMBER_NODE:
            return "Signed Number Node";
        case CHAR_CONSTANT_NODE:
            return "Char Constant Node";
        case CONSTANT_DEFINITION_NODE:
            return "Constant Definition Node";
        case NEGATIVE_SIGN_NODE:
            return "Negative Sign Node";
        case POSITIVE_SIGN_NODE:
            return "Positive Sign Node";
        case PROGRAM_NODE:
            return "Program Node";
        case UNIT_NODE:
            return "Unit Node";
        case PROGRAM_HEADING_NODE:
            return "Program Heading Node";
        case IDENTIFIER_LIST_NODE:
            return "Identifier List Node";
        case TYPE_IDENTIFIER_NODE:
            return "Type Identifier Node";
        case BLOCK_NODE:
            return "Block Node";
        case SUBRANGE_TYPE_NODE:
            return "Subrange Type Node";
        case LABEL_DECLARATION_LIST_NODE:
            return "Label Declaration List Node";
        case CONSTANT_DEFINITION_LIST_NODE:
            return "Constant Definition List Node";
        case TYPE_DEFINITION_LIST_NODE:
            return "Type Definition List Node";
        case TYPE_DEFINITION_NODE:
            return "Type Definition Node";
        case SCALAR_NODE:
            return "Scalar Node";
        case VARIABLE_DECLARATION_LIST_NODE:
            return "Variable Declaration List Node";
        case PROCEDURE_DECLARATION_NODE:
            return "Procedure Declaration Node";
        case FUNCTION_DECLARATION_NODE:
            return "Function Declaration Node";
        case USES_UNITS_NODE:
            return "Uses Units Node";
        case COMPOUND_STATEMENT_NODE:
            return "Compound Statement Node";
        case TYPE_LIST_NODE:
            return "Type List Node";
        case PACKED_STRUCTURE_NODE:
            return "Packed Structure Node";
        case ARRAY_TYPE_NODE:
            return "Array Type Node";
        case SET_TYPE_NODE:
            return "Set Type Node";
        case FILE_TYPE_NODE:
            return "File Type Node";
        case POINTER_TYPE_NODE:
            return "Pointer Type Node";
        case RECORD_TYPE_NODE:
            return "Record Type Node";
        case RECORD_SECTION_LIST_NODE:
            return "Record Section List Node";
        case RECORD_SECTION_NODE:
            return "Record Section Node";
        case VARIANT_LIST_NODE:
            return "Variant List Node";
        case VARIANT_NODE:
            return "Variant Node";
        case TAG_NODE:
            return "Tag Node";
        case CONSTANT_LIST_NODE:
            return "Constant List Node";
        case FIELD_LIST_NODE:
            return "Field List Node";
        case VARIABLE_DECLARATION_NODE:
            return "Variable Declaration Node";
        case FORMAL_PARAMETER_LIST_NODE:
            return "Formal Parameter List Node";
        case FORMAL_PARAMETER_SECTION_NODE:
            return "Formal Parameter Section Node";
        case PARAMETER_GROUP_NODE:
            return "Parameter Group Node";
        case VAR_PARAMETER_GROUP_NODE:
            return "Var Parameter Group Node";
        case FUNCTION_PARAMETER_GROUP_NODE:
            return "Function Parameter Group Node";
        case PROCEDURE_PARAMETER_GROUP_NODE:
            return "Procedure Parameter Group Node";
        case STATEMENTS_NODE:
            return "Statements Node";
        case STATEMENT_NODE:
            return "Statement Node";
        case UNLABELLED_STATEMENT_NODE:
            return "Unlabelled Statement Node";
        case SIMPLE_STATEMENT_NODE:
            return "Simple Statement Node";
        case ASSIGNMENT_STATEMENT_NODE:
            return "Assignement Statement Node";
        case VARIABLE_NODE:
            return "Variable Node";
        case EXPRESSION_NODE:
            return "Expression Node";
        case RELATIONAL_OPERATOR_NODE:
            return "Relational Operator Node";
        case SIMPLE_EXPRESSION_NODE:
            return "Simple Expression Node";
        case ADDITIVE_OPERATOR_NODE:
            return "Additive Operator Node";
        case TERM_NODE:
            return "Term Node";
        case MULTIPLICATIVE_OPERATOR_NODE:
            return "Multiplicative Operator Node";
        case SIGNED_FACTOR_NODE:
            return "Signed Factor Node";
        case FACTOR_NODE:
            return "Factor Node";
        case UNSIGNED_CONSTANT_NODE:
            return "Unsigned Constant Node";
        case FUNCTION_DESIGNATOR_NODE:
            return "Function Designator Node";
        case PARAMETER_LIST_NODE:
            return "Parameter List Node";
        case SET_NODE:
            return "Set Node";
        case ELEMENT_LIST_NODE:
            return "Element List Node";
        case ELEMENT_NODE:
            return "Element Node";
        case PROCEDURE_STATEMENT_NODE:
            return "Procedure Statement Node";
        case ACTUAL_PARAMETER_NODE:
            return "Actual Parameter Node";
        case PARAMETER_WIDTH_NODE:
            return "Parameter Width Node";
        case GOTO_STATEMENT_NODE:
            return "Goto Statement Node";
        case EMPTY_STATEMENT_NODE:
            return "Empty Statement Node";
        case EMPTY_NODE:
            return "Empty node";
        case STRUCTURED_STATEMENT_NODE:
            return "Structured Statement Node";
        case CONDITIONAL_STATEMENT_NODE:
            return "Conditional Statement Node";
        case IF_STATEMENT_NODE:
            return "If Statement Node";
        case CASE_STATEMENT_NODE:
            return "Case Statement Node";
        case CASE_LIST_ELEMENT_NODE:
            return "Case List Element Node";
        case REPETATIVE_STATEMENT_NODE:
            return "Repatative Statement Node";
        case WHILE_STATEMENT_NODE:
            return "While Statement Node";
        case REPEAT_STATEMENT_NODE:
            return "Repeat Statement Node";
        case FOR_STATEMENT_NODE:
            return "For Statement Node";
        case FOR_LIST_NODE:
            return "For List Node";
        case INITIAL_VALUE_NODE:
            return "Initial Value Node";
        case FINAL_VALUE_NODE:
            return "Final Value Node";
        case WITH_STATEMENT_NODE:
            return "With Statement Node";
        case RECORD_VARIABLE_LIST_NODE:
            return "Record Variable List Node";
        default:
            return "UNDEFINED NODE TYPE";
    }
}

void printNode(SyntaxNode* node, int depth) {
    if (node != NULL) {
        printf("data: %s type: %s\n", node -> data, getNodeType(node));
        if (node -> nodes != NULL && node -> nodes -> size > 0) {
            printf("---%d---\nchildren of: %s. Number of children: %d\n", depth, getNodeType(node), node -> nodes -> size);
            for (int i = 0; i < node -> nodes -> size; i++) {
                printf("child %d: ", i + 1);
                printNode(getNode(node -> nodes, i), depth + 1);
            }
            printf("end of children of: %s\n---%d---\n", getNodeType(node), depth);
        }
    }
}

SyntaxNode* createNode() {
    SyntaxNode* node = (SyntaxNode*)malloc(sizeof(SyntaxNode));
    memset(node, 0, sizeof(SyntaxNode));
    return node;
}

SyntaxNode* parse() {
    bufferIndex = 0;
    return parseProgram();
}

SyntaxNode* parseProgram() {
    SyntaxNode* root = createNode();
    root -> data = NULL;
    root -> type = PROGRAM_NODE;
    NodeList* nodes = createNodeList();

    addNode(nodes, parseProgramHeading());

    if (tokenBuffer[bufferIndex] -> type == INTERFACE) {
        bufferIndex++;
    }
    while (tokenBuffer[bufferIndex] -> type != DOT) {
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
        if (isNext(LEFT_PARENTHESES) ) {
            readNext(LEFT_PARENTHESES);
            SyntaxNode* idList = parseIdentifierList();
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

SyntaxNode* parseIdentifierList() {
    SyntaxNode* node = createNode();
    NodeList* list = createNodeList();
    node -> type = IDENTIFIER_LIST_NODE;
    list -> size = 0;

    addNode(list, parseIdentifier());
    while (isNext(COMMA) ) {
        readNext(COMMA);
        addNode(list, parseIdentifier());
    }
    node -> nodes = list;
    return node;
}

SyntaxNode* parseIdentifier() {
    SyntaxNode* node = createNode();
    Token* identifier = readNext(IDENTIFIER);
    node -> type = IDENTIFIER_NODE;
    node -> data = identifier -> value;
    return node;
}

#pragma region BLOCK

SyntaxNode* parseBlock() {
    SyntaxNode* blockNode = createNode();
    NodeList* list = createNodeList();
    blockNode -> type = BLOCK_NODE;
    blockNode -> nodes = list;
    while (blockIsNext()) {
        if (isNext(LABEL)) {
            addNode(list, parseLabelDeclarationList());
        } else if (isNext(CONST)) {
            addNode(list, parseConstantDefinitionList());
        } else if (isNext(TYPE)) {
            addNode(list, parseTypeDefinitionList());
        } else if (isNext(VAR)) {
            addNode(list, parseVariableDeclarationList());
        } else if (isNext(PROCEDURE)) {
            addNode(list, parseProcedureDeclaration());
        }  else if (isNext(FUNCTION)) {
            addNode(list, parseFunctionDeclarationList());
        } else if (isNext(USES)) {
            addNode(list, parseUsesUnits());
        } else if (isNext(IMPLEMENTATION)) {
            readNext(IMPLEMENTATION);
        }
    }
    addNode(list, parseCompoundStatement());
    return blockNode;
}

int blockIsNext() {
    return isNext(LABEL) ||
            isNext(CONST) ||
            isNext(LABEL) ||
            isNext(TYPE) ||
            isNext(VAR) ||
            isNext(PROCEDURE) ||
            isNext(FUNCTION) ||
            isNext(USES) ||
            isNext(IMPLEMENTATION);
}

SyntaxNode* parseLabelDeclarationList() {
    readNext(LABEL);
    SyntaxNode* node = createNode();
    node -> type = LABEL_DECLARATION_LIST_NODE;
    node -> nodes = createNodeList();
    addNode(node -> nodes, parseNumber());
    while (isNext(COMMA)) {
        readNext(COMMA);
        addNode(node -> nodes, parseNumber());
    }
    readNext(SEMICOLON);
    return node;
}

SyntaxNode* parseConstantDefinitionList() {
    readNext(CONST);
    SyntaxNode* node = createNode();
    NodeList* list = createNodeList();
    node -> type = CONSTANT_DEFINITION_LIST_NODE;
    node -> nodes = list;

    SyntaxNode* constantDefinition = readConstantDefinition();
    addNode(list, constantDefinition);
    readNext(SEMICOLON);
    while (isNext(IDENTIFIER)) {
        constantDefinition = readConstantDefinition();
        addNode(list, constantDefinition);
        readNext(SEMICOLON);
    }
    return node;
}

SyntaxNode* readConstantDefinition() {
    SyntaxNode* node = createNode();
    NodeList* list = createNodeList();
    node -> type = CONSTANT_DEFINITION_NODE;
    node -> nodes = list;
    addNode(list, parseIdentifier());
    readNext(EQUAL);
    addNode(list, parseConstant());
    return node;
}

SyntaxNode* parseConstant() {
    if (isNext(NUMBER)) {
        return parseNumber();
    } else if (isNext(IDENTIFIER)) {
        return parseIdentifier();   
    } else if (isNext(STRING)) {
        return parseString();
    } else if (isNext(SUBTRACTION) || isNext(ADDITION)) {
        SyntaxNode* node = createNode();
        NodeList* list = createNodeList();
        node -> nodes = list;
        addNode(list, parseSign());
        if (isNext(IDENTIFIER)) {
            node -> type = SIGNED_IDENTIFIER_NODE;
            addNode(list, parseIdentifier());
        } else if (isNext(NUMBER)) {
            node -> type = SIGNED_NUMBER_NODE;
            addNode(list, parseNumber());
        }
        return node;
    } else if (isNext(CHR)) {
        return parseCharConstant();
    }
    printf("Failed to parse constant");
    exit(1);
}

SyntaxNode* parseNumber() {
    SyntaxNode* node = createNode();
    node -> type = NUMBER_NODE;
    node -> data = readNext(NUMBER) -> value;
    return node;
}

SyntaxNode* parseString() {
    SyntaxNode* node = createNode();
    node -> type = STRING_NODE;
    node -> data = readNext(STRING) -> value;
    return node;
}

SyntaxNode* parseSign() {
    SyntaxNode* node = createNode();
    if (isNext(SUBTRACTION)) {
        readNext(SUBTRACTION);
        node -> type = NEGATIVE_SIGN_NODE;
        node -> data = "-";
        return node;
    }
    if (isNext(ADDITION)) {
        readNext(ADDITION);
        node -> type = POSITIVE_SIGN_NODE;
        node -> data = "+";
        return node;
    }
    printf("Failed to parse sign");
    exit(1);
}

SyntaxNode* parseCharConstant() {
    SyntaxNode* node = createNode();
    NodeList* list = createNodeList();
    node -> type = CHAR_CONSTANT_NODE;
    node -> nodes = list;
    readNext(CHR);
    readNext(LEFT_PARENTHESES);
    node -> data = parseNumber() -> data;
    readNext(RIGHT_PARENTHESES);
    return node;
}

SyntaxNode* parseTypeDefinitionList() {
    readNext(TYPE);
    SyntaxNode* node = createNode();
    NodeList* list = createNodeList();
    node -> nodes = list;
    node -> type = TYPE_DEFINITION_LIST_NODE;

    addNode(list, parseTypeDefinition());
    readNext(SEMICOLON);
    while (isNext(IDENTIFIER)) {
        addNode(list, parseTypeDefinition());
        readNext(SEMICOLON);
    }
    return node;
}

SyntaxNode* parseTypeDefinition() {
    SyntaxNode* node = createNode();
    NodeList* list = createNodeList();
    node -> nodes = list;
    node -> type = TYPE_DEFINITION_NODE;
    addNode(list, parseIdentifier());
    readNext(EQUAL);
    addNode(list, parseType());
    return node;
}

SyntaxNode* parseType() {
    if (isNextSimpleType()) {
        return parseSimpleType();
    }
    if (isNextStructuredType()) {
        return parseStructuredType();
    }
    if (isNext(POINTER)) {
        return parsePointerType();
    }
    printf("Failed to parse type.\n");
    exit(1);
}

int isNextSimpleType() {
    return isNext(LEFT_PARENTHESES) ||
            isStringType() ||
            isSubRangeType() ||
            isTypeIdentifier();
}

SyntaxNode* parseSimpleType() {
    if (isNext(LEFT_PARENTHESES)) {
        return parseScalar();
    }
    if (isStringType()) {
        return parseStringType();
    }
    if (isSubRangeType()) {
        return parseSubrangeType();
    }
    if (isTypeIdentifier()) {
        return parseTypeIdentifier();
    }
    printf("Failed to parse simple type");
    exit(1);
}

int isStringType() {
    return isNext(STR) && tokenBuffer[bufferIndex + 1] -> type == LEFT_BRACKET;
}

SyntaxNode* parseStringType() {
    SyntaxNode* node = createNode();
    node -> type = STRING_TYPE_NODE;
    readNext(STR);
    readNext(LEFT_BRACKET);
    if (isNext(IDENTIFIER)) {
        node -> data = parseIdentifier() -> data;
    } else if (isNext(NUMBER)) {
        node -> data = parseNumber() -> data;
    }
    readNext(RIGHT_BRACKET);
    return node;
}

int isSubRangeType() {
    return isNext(NUMBER) ||
            isNext(ADDITION) ||
            isNext(SUBTRACTION) ||
            isNext(STRING) ||
            isNext(CHR) ||
            (isNext(IDENTIFIER) && tokenBuffer[bufferIndex + 1] -> type == DOT);
}

SyntaxNode* parseSubrangeType() {
    SyntaxNode* node = createNode();
    NodeList* list = createNodeList();
    node -> nodes = list;
    node -> type = SUBRANGE_TYPE_NODE;
    addNode(list, parseConstant());
    readNext(DOT);
    readNext(DOT);
    addNode(list, parseConstant());
    return node;
}

int isTypeIdentifier() {
    return isNext(CHAR) ||
            isNext(BOOLEAN) ||
            isNext(INTEGER) ||
            isNext(REAL) ||
            isNext(STR) || 
            isNext(IDENTIFIER);
}

SyntaxNode* parseTypeIdentifier() {
    if (isNext(IDENTIFIER)) {
        SyntaxNode* node = parseIdentifier();
        node -> type = TYPE_IDENTIFIER_NODE;
        return node;
    }
    Token* token = tokenBuffer[bufferIndex++];
    SyntaxNode* node = createNode();
    node -> type = TYPE_IDENTIFIER_NODE;
    node -> data = token -> value;
    return node;
}

SyntaxNode* parseScalar() {
    readNext(LEFT_PARENTHESES);
    SyntaxNode* scalarNode = parseIdentifierList();
    scalarNode -> type = SCALAR_NODE;
    readNext(RIGHT_PARENTHESES);
    return scalarNode;
}

int isNextStructuredType() {
    return isNext(PACKED) ||
            isNext(ARRAY) ||
            isNext(RECORD) ||
            isNext(SET) ||
            isNext(PASCAL_FILE);
}

SyntaxNode* parseStructuredType() {
    if (isNext(PACKED)) {
        readNext(PACKED);
        SyntaxNode* node = createNode();
        node -> type = PACKED_STRUCTURE_NODE;
        node -> nodes = createNodeList();
        addNode(node -> nodes, parseStructuredType());
        return node;
    }
    if (isNext(ARRAY)) {
        return parseArrayType();
    }
    if (isNext(SET)) {
        return parseSetType();
    }
    if (isNext(PASCAL_FILE)) {
        return parseFileType();
    }
    if (isNext(RECORD)) {
        return parseRecordType();
    }
    printf("Failed to parse Structured Type");
    exit(1);
}

SyntaxNode* parseArrayType() {
    SyntaxNode* node = createNode();
    node -> type = ARRAY_TYPE_NODE;
    node -> nodes = createNodeList();
    readNext(ARRAY);
    readNext(LEFT_BRACKET);
    addNode(node -> nodes, parseTypeList());
    readNext(RIGHT_BRACKET);
    readNext(OF);
    addNode(node -> nodes, parseType());
    return node;
}

SyntaxNode* parseTypeList() {
    SyntaxNode* node = createNode();
    node -> type = TYPE_LIST_NODE;
    node -> nodes = createNodeList();
    addNode(node -> nodes, parseSimpleType());
    while (isNext(COMMA)) {
        readNext(COMMA);
        addNode(node -> nodes, parseSimpleType());
    }
    return node;
}

SyntaxNode* parseSetType() {
    SyntaxNode* node = createNode();
    node -> type = SET_TYPE_NODE;
    node -> nodes = createNodeList();
    readNext(SET);
    readNext(OF);
    addNode(node -> nodes, parseSimpleType());
    return node;
}

SyntaxNode* parseFileType() {
    SyntaxNode* node = createNode();
    node -> type = FILE_TYPE_NODE;
    readNext(PASCAL_FILE);
    if (isNext(OF)) {
        readNext(OF);
        node -> nodes = createNodeList();
        addNode(node -> nodes, parseType());
        return node;
    } else {
        return node;
    }
    printf("Failed to parse File Type");
    exit(1);
}

SyntaxNode* parseRecordType() {
    SyntaxNode* node = createNode();
    node -> type = RECORD_TYPE_NODE;
    readNext(RECORD);
    if (isNext(IDENTIFIER) || isNext(CASE)) {
        node -> nodes = createNodeList();
        addNode(node -> nodes, parseFieldList());
    }
    readNext(END);
    return node;
}

SyntaxNode* parseFieldList() {
    SyntaxNode* node = createNode();
    node -> type = FIELD_LIST_NODE;
    node -> nodes = createNodeList();
    if (isNext(IDENTIFIER)) {
        addNode(node -> nodes, parseFixedPart());
        if (isNext(SEMICOLON)) {
            readNext(SEMICOLON);
        }
    }
    if (isNext(CASE)) {
        addNode(node -> nodes, parseVariantPart());
    }
    return node;
}

SyntaxNode* parseFixedPart() {
    SyntaxNode* node = createNode();
    node -> type = RECORD_SECTION_LIST_NODE;
    node -> nodes = createNodeList();
    addNode(node -> nodes, parseRecordSection());
    while (isNext(SEMICOLON) && tokenBuffer[bufferIndex + 1] -> type != CASE) {
        readNext(SEMICOLON);
        addNode(node -> nodes, parseRecordSection());
    }
    return node;
}

SyntaxNode* parseRecordSection() {
    SyntaxNode* node = createNode();
    node -> type = RECORD_SECTION_NODE;
    node -> nodes = createNodeList();
    addNode(node -> nodes, parseIdentifierList());
    readNext(COLON);
    addNode(node -> nodes, parseType());
    return node;
}

SyntaxNode* parseVariantPart() {
    SyntaxNode* node = createNode();
    node -> type = VARIANT_LIST_NODE;
    node -> nodes = createNodeList();
    readNext(CASE);
    addNode(node -> nodes, parseTag());
    readNext(OF);
    addNode(node -> nodes, parseVariant());
    while (isNext(SEMICOLON)) {
        readNext(SEMICOLON);
        addNode(node -> nodes, parseVariant());
    }
    return node;
}

SyntaxNode* parseVariant() {
    SyntaxNode* node = createNode();
    node -> type = VARIANT_NODE;
    node -> nodes = createNodeList();
    addNode(node -> nodes, parseConstantList());
    readNext(COLON);
    readNext(LEFT_PARENTHESES);
    addNode(node -> nodes, parseFieldList());
    readNext(RIGHT_PARENTHESES);
    return node;
}

SyntaxNode* parseTag() {
    SyntaxNode* node = createNode();
    node -> type = TAG_NODE;
    node -> nodes = createNodeList();
    if (isNext(IDENTIFIER)) {
        addNode(node -> nodes, parseIdentifier());
        readNext(COLON);
        addNode(node -> nodes, parseTypeIdentifier());
    } else {
        addNode(node -> nodes, parseTypeIdentifier());
    }
    return node;
}

SyntaxNode* parseConstantList() {
    SyntaxNode* node = createNode();
    node -> nodes = createNodeList();
    node -> type = CONSTANT_LIST_NODE;
    addNode(node -> nodes, parseConstant());
    while (isNext(COMMA)) {
        readNext(COMMA);
        addNode(node -> nodes, parseConstant());
    }
    return node;
}

SyntaxNode* parsePointerType() {
    readNext(POINTER);
    SyntaxNode* node = parseTypeIdentifier();
    node -> type = POINTER_TYPE_NODE;
    return node;
}

SyntaxNode* parseVariableDeclarationList() {
    readNext(VAR);
    SyntaxNode* node = createNode();
    node -> type = VARIABLE_DECLARATION_LIST_NODE;
    node -> nodes = createNodeList();
    addNode(node -> nodes, parseVariableDeclaration());
    while (isNext(SEMICOLON)) {
        readNext(SEMICOLON);
        if (isNext(IDENTIFIER)) {
            addNode(node -> nodes, parseVariableDeclaration());
        }
    }
    return node;
}

SyntaxNode* parseVariableDeclaration() {
    SyntaxNode* node = createNode();
    node -> type = VARIABLE_DECLARATION_NODE;
    node -> nodes = createNodeList();
    addNode(node -> nodes, parseIdentifierList());
    readNext(COLON);
    addNode(node -> nodes, parseType());
    return node;
}

SyntaxNode* parseProcedureDeclaration() {
    readNext(PROCEDURE);
    SyntaxNode* node = createNode();
    node -> type = PROCEDURE_DECLARATION_NODE;
    node -> nodes = createNodeList();
    addNode(node -> nodes, parseIdentifier());
    if (isNext(LEFT_PARENTHESES)) {
        addNode(node -> nodes, parseFormalParameterList());
    }
    readNext(SEMICOLON);
    addNode(node -> nodes, parseBlock());
    return node;
}

SyntaxNode* parseFormalParameterList() {
    readNext(LEFT_PARENTHESES);
    SyntaxNode* node = createNode();
    node -> type = FORMAL_PARAMETER_LIST_NODE;
    node -> nodes = createNodeList();
    addNode(node -> nodes, parseFormalParameterSection());
    while (isNext(SEMICOLON)) {
        readNext(SEMICOLON);
        addNode(node -> nodes, parseFormalParameterSection());
    }
    readNext(RIGHT_PARENTHESES);
    return node;
}

SyntaxNode* parseFormalParameterSection() {
    if (isNext(IDENTIFIER)) {
        return parseParameterGroup();
    } else if (isNext(VAR)) {
        SyntaxNode* node = createNode();
        node -> type = VAR_PARAMETER_GROUP_NODE;
        node -> nodes = createNodeList();
        addNode(node -> nodes, parseParameterGroup());
        return node;
    } else if (isNext(FUNCTION)) {
        SyntaxNode* node = createNode();
        node -> type = FUNCTION_PARAMETER_GROUP_NODE;
        node -> nodes = createNodeList();
        addNode(node -> nodes, parseParameterGroup());
        return node;
    } else if (isNext(PROCEDURE)) {
        SyntaxNode* node = createNode();
        node -> type = PROCEDURE_PARAMETER_GROUP_NODE;
        node -> nodes = createNodeList();
        addNode(node -> nodes, parseParameterGroup());
        return node;
    }
    printf("Failed to parse formal parameter section");
    exit(1);
}

SyntaxNode* parseParameterGroup() {
    SyntaxNode* node = createNode();
    node -> nodes = createNodeList();
    node -> type = PARAMETER_GROUP_NODE;
    addNode(node -> nodes, parseIdentifier());
    readNext(COLON);
    addNode(node -> nodes, parseTypeIdentifier());
    return node;
}

SyntaxNode* parseFunctionDeclarationList() {
    readNext(FUNCTION);
    SyntaxNode* node = createNode();
    node -> type = FUNCTION_DECLARATION_NODE;
    node -> nodes = createNodeList();
    addNode(node -> nodes, parseIdentifier());
    if (isNext(LEFT_PARENTHESES)) {
        addNode(node -> nodes, parseFormalParameterList());
    }
    readNext(COLON);
    addNode(node -> nodes, parseTypeIdentifier());
    readNext(SEMICOLON);
    addNode(node -> nodes, parseBlock());
    return node;
}

SyntaxNode* parseUsesUnits() {
    readNext(USES);
    SyntaxNode* node = createNode();
    NodeList* list = createNodeList();
    node -> type = USES_UNITS_NODE;
    node -> nodes = list;
    SyntaxNode* usedIdentifierList = parseIdentifierList();
    for (int i = 0; i < usedIdentifierList -> nodes -> size; i++) {
        addNode(list, getNode(usedIdentifierList -> nodes, i));
    }
    free(usedIdentifierList -> nodes);
    free(usedIdentifierList);
    readNext(SEMICOLON);
    return node;
}

#pragma endregion

SyntaxNode* parseCompoundStatement() {
    readNext(BEGIN);
    SyntaxNode* node = createNode();
    node -> type = COMPOUND_STATEMENT_NODE;
    node -> nodes = createNodeList();
    addNode(node -> nodes, parseStatements());
    readNext(END);
    if (isNext(SEMICOLON)) {
        readNext(SEMICOLON);
    }
    return node;
}

SyntaxNode* parseStatements() {
    SyntaxNode* node = createNode();
    node -> type = STATEMENTS_NODE;
    node -> nodes = createNodeList();
    addNode(node -> nodes, parseStatement());
    while (isNext(SEMICOLON)) {
        readNext(SEMICOLON);
        SyntaxNode* statement = parseStatement();
        if (statement -> type != EMPTY_STATEMENT_NODE) {
            addNode(node -> nodes, statement);
        }
    }
    return node;
}

SyntaxNode* parseStatement() {
    SyntaxNode* node = createNode();
    node -> type = STATEMENT_NODE;
    node -> nodes = createNodeList();
    if (isNext(NUMBER)) {
        addNode(node -> nodes, parseNumber());
        readNext(COLON);
    }
    SyntaxNode* statement = parseUnlabelledStatement();
    if (statement -> type == EMPTY_STATEMENT_NODE) {
        return statement;
    }
    addNode(node -> nodes, statement);
    return node;
}

SyntaxNode* parseUnlabelledStatement() {
    if (isAssignmentNext()) {
        return NULL;
    }
    if (isProcedureNext()) {
        return parseProcedureStatement();
    }
    if (isNext(GOTO)) {
        return parseGotoStatement();
    }
    return parseEmptyStatement();
}

int isAssignmentNext() {
    return isNext(AT) || 
    (
        (isNext(IDENTIFIER) && isNthTypeNext(LEFT_BRACKET, 1)) ||
        (isNext(IDENTIFIER) && isNthTypeNext(DOT, 1)) ||
        (isNext(IDENTIFIER) && isNthTypeNext(ASSIGNMENT, 1)) ||
        (isNext(IDENTIFIER) && isNthTypeNext(POINTER, 1))
    );
}

SyntaxNode* parseAssignmentStatement() {
    return NULL;
}

SyntaxNode* parseExpression() {
    SyntaxNode* node = createNode();
    node -> type = EXPRESSION_NODE;
    node -> nodes = createNodeList();
    addNode(node -> nodes, parseSimpleExpression());
    return node;
}

int isProcedureNext() {
    return (isNext(IDENTIFIER) && isNthTypeNext(LEFT_PARENTHESES, 1)) || 
            isNext(IDENTIFIER);
}

SyntaxNode* parseProcedureStatement() {
    SyntaxNode* node = createNode();
    node -> type = PROCEDURE_STATEMENT_NODE;
    node -> nodes = createNodeList();
    addNode(node -> nodes, parseIdentifier());
    if (isNext(LEFT_PARENTHESES)) {
        readNext(LEFT_PARENTHESES);
        addNode(node -> nodes, parseParameterList());
        readNext(RIGHT_PARENTHESES);
    }
    return node;
}

SyntaxNode* parseParameterList() {
    SyntaxNode* node = createNode();
    node -> type = PARAMETER_LIST_NODE;
    node -> nodes  = createNodeList();
    addNode(node -> nodes, parseActualParameter());
    while (isNext(COMMA)) {
        readNext(COMMA);
        addNode(node -> nodes, parseActualParameter());
    }
    return node;
}

SyntaxNode* parseActualParameter() {
    SyntaxNode* node = createNode();
    node -> nodes = createNodeList();
    node -> type = ACTUAL_PARAMETER_NODE;
    addNode(node -> nodes, parseExpression());
    while (isNext(COLON)) {
        addNode(node -> nodes, parseParameterWidth());
    }
    return node;
}

SyntaxNode* parseParameterWidth() {
    readNext(COLON);
    SyntaxNode* node = parseExpression();
    node -> type = PARAMETER_WIDTH_NODE;
    return node; 
}

SyntaxNode* parseGotoStatement() {
    readNext(GOTO);
    SyntaxNode* node = createNode();
    node -> type = GOTO_STATEMENT_NODE;
    node -> data = parseNumber() -> data;
    return node;
}

SyntaxNode* parseEmptyStatement() {
    SyntaxNode* node = createNode();
    node -> type = EMPTY_STATEMENT_NODE;
    return node;
}

Token* readNext(enum TokenType type) {
    if (tokenBuffer[bufferIndex] -> type != type) {
        printf("Expected next token to be type %s", getTokenType(type));
        exit(1);
    }
    return tokenBuffer[bufferIndex++];
}

int isNext(enum TokenType type) {
    return tokenBuffer[bufferIndex] -> type == type;
}

int isNthTypeNext(enum TokenType type, int n) {
    return BUFFER_SIZE > bufferIndex + n && 
        tokenBuffer[bufferIndex + n] != NULL && 
        tokenBuffer[bufferIndex + n] -> type == type;
}

#pragma endregion

#pragma region List

NodeList* createNodeList() {
    NodeList* list = (NodeList*)malloc(sizeof(NodeList));
    memset(list, 0, sizeof(NodeList));
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