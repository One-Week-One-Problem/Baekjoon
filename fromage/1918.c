#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

// string data
char input[101] = { 0, };
char output[101] = { 0, };
int outputIndex = 0;

void out(char token) {
    if (token) output[outputIndex++] = token;
}

// stack operation
char stack[101] = { 0, };
int stackIndex = -1;

void push(char token) {
    stack[++stackIndex] = token;
}

char peek() {
    if (stackIndex < 0) {
        return 0;
    }
    return stack[stackIndex];
}

char pop() {
    char token = peek();
    if (token) stackIndex--;
    return token;
}

// comparator
int getPriority(char token) {
    if (token == '*' || token == '/') return 2;
    if (token == '+' || token == '-') return 1;
    return 0;
}

// flag
int level = 0;
int stackLimits[101] = { -1, };

int main() {
    scanf("%s", input);
    int len = strlen(input);
    // process
    for (int i = 0; i < len; i++) {
        char token = input[i];
        int stackLimit = stackLimits[level];
        switch (token)
        {
        case '+':
        case '-':
        case '*':
        case '/': {
            char prevToken = peek();
            while (prevToken && stackLimit < stackIndex) {
                if (getPriority(prevToken) < getPriority(token)) {
                    break;
                } // if prev priority == current priority, prev is higher
                out(pop());
                prevToken = peek();
            }
            push(token);
            break;
        }
        case '(': {
            stackLimits[++level] = stackIndex;
            break;
        }
        case ')': {
            // local flush
            while (stackLimit < stackIndex) {
                out(pop());
            }
            level--;
            break;
        }
        default:
            // just copy token
            out(token);
            break;
        }
    }
    // global flush
    char token;
    while (token = pop()) {
        out(token); 
    }
    printf("%s", output);
}