#include "smallsh.h"
// 首先显示提示符，提
// 示符的具体内容由用户通过参数传送给函数；然后每次从键盘读一个字符，当遇到换行符
// 或文件结束符（用 EOF 符号表示）时，就结束。

static char inputbuf[MAXBUF], tokbuf[2 * MAXBUF],
    *ptr = inputbuf, *tok = tokbuf;

int userin(char *p)
{

    int c, count;
    ptr = inputbuf;
    tok = tokbuf;
    //show information
    printf("%s", p);
    for (count = 0;;)
    {
        if ((c = getchar()) == EOF)
            return (EOF);
        if (count < MAXBUF)
            inputbuf[count++] = c;
        if (c == '\n' && count < MAXBUF)
        {
            inputbuf[count] = '\0';
            return (count);
        }
    }
    /* 如果行过长重新输入 */
    if (c == '\n')
    {
        printf("smallsh:input line too long\n");
        count = 0;
        printf("%s ", p);
    }
}

gettok(char *output)
{
    int type;

    output = tok;
    /* 首先去除空白字符 */
    for (; *ptr == " " || *ptr == '\t'; ptr++)
        ;

    *tok++ = *ptr;
    switch (*ptr++)
    {
    case '\n':
        type = EOL;
        break;
    case '&':
        type = AMPERSAND;
        break;
    case ';':
        type = SEMICOLON;
        break;
    default:
        type = ARG;
        while (inarg(*ptr))
            *tok++ = *ptr++;
    }
    *tok++ = '\0';
    return type;
}

static char special[] = {' ', '\t', '*', ';',
                         '.', '\n', '\0'};
//例行程序 inarg 用于确定一个字符是否可以作为参数的组成符。检查这个字符
// 是否是 smallsh 的特殊字符
inarg(char c)
{
    char *wrk;
    for (wrk = special; *wrk != '\0'; wrk++)
        if (c == *wrk)
            return (0);
    return (1);
}