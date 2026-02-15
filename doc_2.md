# Infix to Postfix Converter and Evaluator

## Overview
This program converts mathematical expressions from infix notation (normal mathematical notation) to postfix notation (Reverse Polish Notation) and evaluates numeric postfix expressions using stack data structures.

## Data Structures

### Character Stack Structure
typedef struct {
    char items[STACK_CAPACITY];  // Array to store characters (STACK_CAPACITY = 100)
    int topIndex;                // Index of top element (-1 when empty)
} CharStack;
**Purpose**: Used during the infix-to-postfix conversion process to temporarily store operators and parentheses while maintaining proper precedence.

### Integer Stack Structure
typedef struct {
    int items[STACK_CAPACITY];   // Array to store integer values
    int topIndex;                // Index of top element (-1 when empty)
} IntStack;
**Purpose**: Used during postfix expression evaluation to store operands and intermediate calculation results.

## Functions Implemented

### Character Stack Operations

#### 1. `void initCharStack(CharStack *s)`
- **Purpose**: Sets up the character stack by initializing topIndex to -1
- **Parameters**: Pointer to CharStack structure
- **Returns**: Nothing (void)

#### 2. `bool isCharStackEmpty(CharStack *s)`
- **Purpose**: Determines whether the character stack contains any elements
- **Returns**: true if empty (topIndex == -1), false if elements exist

#### 3. `void pushChar(CharStack *s, char ch)`
- **Purpose**: Inserts a character onto the top of the character stack
- **Parameters**: Stack pointer and character to insert
- **Note**: Performs boundary checking to prevent overflow

#### 4. `char popChar(CharStack *s)`
- **Purpose**: Removes and retrieves the top character from the stack
- **Returns**: The removed character, or '\0' if stack is empty
- **Note**: Decrements topIndex after retrieval

#### 5. `char peekChar(CharStack *s)`
- **Purpose**: Views the top character without removing it
- **Returns**: Top character or '\0' if empty
- **Note**: Allows inspection of stack top without modification

### Integer Stack Operations

#### 6. `void initIntStack(IntStack *s)`
- **Purpose**: Prepares the integer stack by setting topIndex to -1
- **Parameters**: Pointer to IntStack structure
- **Returns**: Nothing (void)

#### 7. `bool isIntStackEmpty(IntStack *s)`
- **Purpose**: Checks if the integer stack has any values
- **Returns**: true when empty (topIndex == -1), false otherwise

#### 8. `void pushInt(IntStack *s, int value)`
- **Purpose**: Places an integer value onto the top of the integer stack
- **Parameters**: Stack pointer and integer value to insert
- **Note**: Includes overflow protection by checking capacity

#### 9. `int popInt(IntStack *s)`
- **Purpose**: Extracts and returns the top integer from the stack
- **Returns**: The removed integer, or 0 if stack is empty
- **Note**: Decrements topIndex after extraction

### Utility Functions

#### 10. `bool isOperator(char ch)`
- **Purpose**: Identifies if a character represents a mathematical operator
- **Operators Recognized**: +, -, *, /, ^, %
- **Returns**: true if character is an operator, false otherwise

#### 11. `int getPrecedence(char operator)`
- **Purpose**: Returns the priority level of an operator for proper order of operations
- **Precedence Levels**:
  - Level 1: Addition (+), Subtraction (-)
  - Level 2: Multiplication (*), Division (/), Modulus (%)
  - Level 3: Exponentiation (^)
- **Returns**: Integer representing precedence (higher value = greater priority)

#### 12. `bool isRightAssociative(char operator)`
- **Purpose**: Determines if an operator associates from right to left
- **Right Associative Operators**: Exponentiation (^) only
- **Left Associative Operators**: All others (+, -, *, /, %)
- **Returns**: true for right-associative operators, false for left-associative

### Core Conversion Function

#### 13. `void infixToPostfix(const char *infixExpr, char *postfixExpr)`
- **Purpose**: Transforms an infix expression into postfix notation using the Shunting Yard algorithm
- **Algorithm**:
  1. Initialize an empty character stack (operatorStack)
  2. Process each character in the infix expression:
     - **Whitespace**: Skip and continue
     - **Operand (alphanumeric)**: Append directly to postfix output
     - **Left Parenthesis '('**: Push onto operator stack
     - **Right Parenthesis ')'**: Pop operators to output until matching '(' is found, then discard the '('
     - **Operator**: 
       - Pop operators with higher precedence to output
       - For equal precedence, pop if left-associative
       - Push current operator onto stack
  3. Pop all remaining operators from stack to output
  4. Null-terminate the postfix string
- **Parameters**: Input infix string and output postfix string buffer
- **Returns**: Nothing (result stored in postfixExpr parameter)

### Evaluation Functions

#### 14. `int performOperation(int operand1, int operand2, char operator)`
- **Purpose**: Executes a mathematical operation on two operands
- **Supported Operations**: 
  - Addition (+)
  - Subtraction (-)
  - Multiplication (*)
  - Division (/)
  - Modulus (%)
  - Exponentiation (^)
- **Parameters**: Two integers (operand1, operand2) and operator character
- **Returns**: Result of the operation
- **Note**: Includes division by zero protection (returns 0 if divisor is 0)

#### 15. `int evaluatePostfix(const char *postfixExpr)`
- **Purpose**: Calculates the numerical result of a postfix expression
- **Algorithm**:
  1. Initialize an empty integer stack (valueStack)
  2. Scan postfix expression from left to right:
     - **Digit**: Convert character to integer and push onto stack
     - **Operator**: 
       - Pop two operands (second pop is operand1, first pop is operand2)
       - Perform operation
       - Push result back onto stack
  3. Final value remaining on stack is the result
- **Returns**: Computed result as an integer

## Main Method Organization

The `main()` function is structured as follows:

1. **Test Expression Array**: Defines five sample expressions to demonstrate functionality:
   - `"7+3*5"` → Tests operator precedence (multiplication before addition)
   - `"(7+3)*5"` → Tests parentheses override of precedence
   - `"3^2^2"` → Tests right associativity of exponentiation (3^(2^2) = 3^4 = 81)
   - `"8+((2+3)*6)-4"` → Tests nested parentheses with multiple operators
   - `"x+y*z-w"` → Tests variable handling (conversion works, evaluation cannot)
2. **Header Display**: Prints program title banner
3. **Conversion and Evaluation Loop**: For each test expression:
   - Displays test case number
   - Shows original infix expression
   - Converts to postfix and displays the result
   - Checks if expression contains alphabetic variables
   - If numeric: evaluates and displays result
   - If contains variables: displays message that evaluation is not possible
4. **Footer Display**: Prints closing banner
5. **Clean Exit**: Returns 0 upon successful completion

##Sample Output
![Output_2](output/output_2.png "Program 2 output")