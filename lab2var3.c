#include <stdio.h>
#include <string.h>

#define N 10


int check(char s[], int i, char stack[], int top) {

    if (s[i] == '\0') {
        return top == -1;
    }
    

    if (s[i] == '(' , s[i] == '[' , s[i] == '{') {
        top++;
        stack[top] = s[i];
    }

    else if (s[i] == ')' , s[i] == ']' , s[i] == '}') {
        if (top == -1) return 0;
        
        char last = stack[top];
        if ((s[i] == ')' && last == '(') ||
            (s[i] == ']' && last == '[') ||
            (s[i] == '}' && last == '{')) {
            top--;
        } else {
            return 0;
        }
    }
    

    return check(s, i + 1, stack, top);
}

int main() {
    char s[N + 1];
    char stack[N];
    int top = -1;
    
    printf("Введите скобки: ");
    scanf("%s", s);
    

    if (strlen(s) > N) {
        printf("false\n");
        return 0;
    }
    

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != '(' && s[i] != ')' && 
            s[i] != '[' && s[i] != ']' && 
            s[i] != '{' && s[i] != '}') {
            printf("false\n");
            return 0;
        }
    }
    

    int result = check(s, 0, stack, top);
    printf("%s\n", result ? "true" : "false");
    
    return 0;
}