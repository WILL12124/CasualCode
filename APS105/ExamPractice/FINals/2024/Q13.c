#include <string.h>

char *removeStrDuplicates(char *str, char *search)
{
    if (str == NULL || search == NULL)
    {
        return NULL;
    }
    char *temp = str; // 要返回指针

    while (1)
    {
        // search
        char *match = strstr(str, search);
        int sublen = strlen(search);
        int len = strlen(str); // size = len+1

        // remove
        if (match != NULL)
        {
            temp = match;
            WRONG !!!!char *tempStr = strcpy(tempStr, temp); // 你tm直接一个指针就指过去了，连变量本身都没有！
            strcpy(temp, tempStr + sublen);                  // strcpy 不能自己复制自己
        }
        else
            return str;
    }

    // kill space

    // advance str and search util \0
}

#include <string.h>

char *removeStrDuplicates(char *str, char *search)
{
    if (str == NULL || search == NULL || *search == '\0')
    {
        return str;
    }

    char *match;
    int sublen = strlen(search);
    char *original_start = str; // 记住最开始的地址

    // 只要还能找到匹配的子串
    while ((match = strstr(str, search)) != NULL)
    {
        // 计算 match 后面还有多少字符需要移动（包括结束符 '\0'）
        int remaining_len = strlen(match + sublen) + 1;

        // memmove 是解决“内存重叠”的神器
        // 把 match + sublen 开始的内容，覆盖到 match 的位置
        memmove(match, match + sublen, remaining_len);

        // 注意：这里不需要移动 str 指针
        // 因为删掉一个词后，后续内容前移了，我们要从原位继续检查
        // 比如 "is is"，删掉第一个 "is" 变成 " is"，
        // 下次 strstr 依然能找到剩下的那个。
    }

    return original_start;
}