#include <stdio.h>
#include <stdlib.h>
#define EXPRESSION_SIZE 100
#define INIT_STACK_SIZE 20
#define STACK_APPEND_SIZE 20

typedef enum
{
    lparen, // (
    rparen, // )
    plus,
    minus,
    times,
    divide,
    mod,
    eos, // end of stack
    operand
} Precedence;

typedef struct
{
    int capacity;
    int top;
    Precedence *stack;
} Pstack; // Precedence Stack

int pstackInit(Pstack *ps, const int size)
{
    if ((ps->stack = malloc(sizeof(Precedence) * size)) == NULL)
    {
        puts("Memory allocation Error");
        return 1;
    }
    ps->capacity = size;
    ps->top = 0;
    return 0;
}

int pstackPush(Pstack *ps, const Precedence token)
{
    if (ps->top >= ps->capacity)
    {
        // stack cap over -> append stack
        if ((ps->stack = realloc(ps->stack, (ps->capacity + STACK_APPEND_SIZE) * sizeof(Precedence))) == NULL)
        {
            puts("Memory re-allocation Error");
            return 1;
        }
        ps->capacity += STACK_APPEND_SIZE;
    }
    ps->stack[ps->top++] = token;
    return 0;
}

Precedence pstackPop(Pstack *ps)
{
    if (ps->top <= 0)
    {
        printf("Wrong Expression : Failed to pop");
        return -1;
    }
    ps->top--;
    return ps->stack[ps->top];
}

Precedence pstackPeek(const Pstack *ps)
{
    return ps->stack[ps->top - 1];
}

void pstackClear(Pstack *ps)
{
    ps->top = 0;
}

void pstackTerminate(Pstack *ps)
{
    if (ps->stack != NULL)
        free(ps->stack);
    ps->capacity = ps->top = 0;
}

//---------------- (   )   +   -   *  /   %  eos
const int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};  // in-stack precedence
const int icp[] = {20, 19, 12, 12, 13, 13, 13, 0}; // incoming precedence
// '(' -> low isp = we want to push it on stack, high icp = we want to keep it on stack -> so we want to keep except ')' comes

// returns Precdence(enum), it also set following symbol & idx value from expression
Precedence getToken(char *symbol, int *idx, const char *expression)
{
    *symbol = expression[(*idx)++];
    switch (*symbol)
    {
    case '(':
        return lparen;
    case ')':
        return rparen;
    case '+':
        return plus;
    case '-':
        return minus;
    case '/':
        return divide;
    case '*':
        return times;
    case '%':
        return mod;
    case '\0':
        return eos;
    default:
        return operand;
    }
}

void printToken(Precedence p)
{
    switch (p)
    {
    case lparen:
        printf("(");
        break;
    case rparen:
        printf(")");
        break;
    case plus:
        printf("+");
        break;
    case minus:
        printf("-");
        break;
    case divide:
        printf("/");
        break;
    case times:
        printf("*");
        break;
    case mod:
        printf("%%");
        break;
    case eos:
        printf("Error : EOS printed");
        break;
    default:
        printf("Error : unable to find matching token");
        break;
    }
}

// this function read infix expression, and print its postfix expression
void printPostfix(Pstack *ps, char *infixExpression)
{
    char symbol;
    // idx used for getToken(), which search and return token from infix expression
    int idx = 0;
    // push 'end of stack' at first
    Precedence token = eos;
    pstackPush(ps, token);
    for (token = getToken(&symbol, &idx, infixExpression); token != eos; token = getToken(&symbol, &idx, infixExpression))
    {
        // token => enum value that determine type of symbol. symbol is character
        if (token == operand)
        {
            if (symbol != '\n')
                printf("%c", symbol);
        }
        else if (token == rparen)
        {
            while (pstackPeek(ps) != lparen)
            {
                token = pstackPop(ps); // pop all operator which is in parethesis
                if (token == eos)      // faile to search matching parenthesis
                {
                    puts("\nWrong Expression");
                    return;
                }
                printToken(token);
            }
            pstackPop(ps); // pops '(' = lparen
            // notice : we don't print parenthesis. since postfix expression doesn't have parenthesis
        }
        else // read operator excpet ')'
        {
            // isp = in-stack Precedence / icp = incoming Precedence
            while (isp[pstackPeek(ps)] >= icp[token])
            {
                // if symbol in stack has higer or equal precedence than following token, we print symbol in stack first
                printToken(pstackPop(ps));
            }
            pstackPush(ps, token);
            // push token to stack
            // we will pop that token if we meet lower precedence or if expression ends
        }
    }
    // we read all expression (token == eos), so we will pop all operator in stack
    while ((token = pstackPop(ps)) != eos)
    {
        if (token == lparen)
        {
            // we processed matching parenthesis pairs when we read rparen
            // if lparen remains on stack, it means expression has un-paired parenthesis
            puts("\nWrong Expression");
            break;
        }
        printToken(token);
    }
    puts("");
}

int main(void)
{
    char infixExpression[EXPRESSION_SIZE];
    Pstack pstack;
    pstackInit(&pstack, INIT_STACK_SIZE);

    FILE *fp = fopen("infixExpression.txt", "r");
    fgets(infixExpression, EXPRESSION_SIZE, fp);
    while (!feof(fp))
    {
        pstackClear(&pstack);
        printf("%s==>", infixExpression);
        printPostfix(&pstack, infixExpression);
        puts("");
        fgets(infixExpression, EXPRESSION_SIZE, fp);
    }
    fclose(fp);
    pstackTerminate(&pstack);
}