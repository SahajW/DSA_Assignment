#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

#define STACK_CAPACITY 100

typedef struct 
{
    char items[STACK_CAPACITY];
    int topIndex;
} CharStack;

typedef struct
{
    int items[STACK_CAPACITY];
    int topIndex;
} IntStack;

void initCharStack(CharStack *s) 
{
    s->topIndex = -1;
}

bool isCharStackEmpty(CharStack *s) 
{
    return s->topIndex == -1;
}

void pushChar(CharStack *s, char ch) 
{
    if (s->topIndex < STACK_CAPACITY - 1)
        s->items[++(s->topIndex)] = ch;
}

char popChar(CharStack *s) 
{
    if (!isCharStackEmpty(s))
        return s->items[(s->topIndex)--];
    return '\0';
}

char peekChar(CharStack *s) 
{
    if (!isCharStackEmpty(s))
        return s->items[s->topIndex];
    return '\0';
}

void initIntStack(IntStack *s) 
{
    s->topIndex = -1;
}

bool isIntStackEmpty(IntStack *s) 
{
    return s->topIndex == -1;
}

void pushInt(IntStack *s, int value) 
{
    if (s->topIndex < STACK_CAPACITY - 1)
        s->items[++(s->topIndex)] = value;
}

int popInt(IntStack *s) 
{
    if (!isIntStackEmpty(s))
        return s->items[(s->topIndex)--];
    return 0;
}

bool isOperator(char ch) 
{
    return (ch == '+' || ch == '-' || ch == '*' || 
            ch == '/' || ch == '^' || ch == '%');
}

int getPrecedence(char operator) 
{
    switch (operator) {
        case '+':
        case '-': return 1;
        case '*':
        case '/':
        case '%': return 2;
        case '^': return 3;
        default:  return 0;
    }
}

bool isRightAssociative(char operator) 
{
    return (operator == '^');
}

void infixToPostfix(const char *infixExpr, char *postfixExpr) 
{
    CharStack operatorStack;
    initCharStack(&operatorStack);
    int outputIndex = 0;

    for (int i = 0; infixExpr[i] != '\0'; i++) 
    {
        char currentChar = infixExpr[i];
        
            continue;

        if (isalnum(currentChar)) {
            postfixExpr[outputIndex++] = currentChar;
        }
        else if (currentChar == '(') {
            pushChar(&operatorStack, currentChar);
        }
        else if (currentChar == ')') {
            while (!isCharStackEmpty(&operatorStack) && peekChar(&operatorStack) != '(')
                postfixExpr[outputIndex++] = popChar(&operatorStack);
            popChar(&operatorStack); // Remove the '('
        }
        else if (isOperator(currentChar)) {
            while (!isCharStackEmpty(&operatorStack) && peekChar(&operatorStack) != '(' &&
                  (getPrecedence(peekChar(&operatorStack)) > getPrecedence(currentChar) ||
                  (getPrecedence(peekChar(&operatorStack)) == getPrecedence(currentChar) &&
                   !isRightAssociative(currentChar)))) {
                postfixExpr[outputIndex++] = popChar(&operatorStack);
            }
            pushChar(&operatorStack, currentChar);
        }
    }

    while (!isCharStackEmpty(&operatorStack))
        postfixExpr[outputIndex++] = popChar(&operatorStack);

    postfixExpr[outputIndex] = '\0';
}

int performOperation(int operand1, int operand2, char operator) 
{
    switch (operator) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return (operand2 != 0) ? operand1 / operand2 : 0;
        case '%': return operand1 % operand2;
        case '^': return (int)pow(operand1, operand2);
        default:  return 0;
    }
}

int evaluatePostfix(const char *postfixExpr) 
{
    IntStack valueStack;
    initIntStack(&valueStack);

    for (int i = 0; postfixExpr[i] != '\0'; i++) 
    {
        char currentChar = postfixExpr[i];

        if (isdigit(currentChar)) {
            pushInt(&valueStack, currentChar - '0');
        }
        else if (isOperator(currentChar)) {
            int operand2 = popInt(&valueStack);
            int operand1 = popInt(&valueStack);
            pushInt(&valueStack, performOperation(operand1, operand2, currentChar));
        }
    }
    return popInt(&valueStack);
}

int main() {
    const char *expressions[] = 
    {
        "7+3*5",
        "(7+3)*5",
        "3^2^2",
        "8+((2+3)*6)-4",
        "x+y*z-w"
    };

    int totalTests = 5;

    printf("\n========== Infix to Postfix Conversion and Evaluation ==========\n");

    for (int i = 0; i < totalTests; i++) 
    {
        char postfixResult[STACK_CAPACITY];

        printf("\n--- Test Case %d ---\n", i + 1);
        printf("Infix Expression   : %s\n", expressions[i]);
        
        infixToPostfix(expressions[i], postfixResult);
        printf("Postfix Expression : %s\n", postfixResult);

        bool hasVariables = false;
        for (int j = 0; expressions[i][j] != '\0'; j++) {
            if (isalpha(expressions[i][j])) {
                hasVariables = true;
                break;
            }
        }
        
        if (hasVariables)
            printf("Evaluation Result  : Cannot compute (contains variables)\n");
        else
            printf("Evaluation Result  : %d\n", evaluatePostfix(postfixResult));
    }
    
    printf("\n================================================================\n");
    return 0;
}