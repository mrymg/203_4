#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

int lineCount(const char *filename)
{
    int ch = 0;
    int count = 1;
    FILE *fileHandle;

    if ((fileHandle = fopen(filename, "r")) == NULL) {
        return -1;
    }

    do {
        ch = fgetc(fileHandle);
        if ( ch == '\n')
            count++;
    } while (ch != EOF);

    fclose(fileHandle);

    return count;
}



void BNF_TREE();

int main() {
    char *condition[2] = {"(<cond><set-op><cond>)", "(<expr><rel-op><expr>)"};
    char *expressionRule[3] = {"(<expr><op><expr>)", "<pre-op>(<expr>)", "<var>"};

    FILE *f_OP;
    FILE *f_PRE_OP;
    FILE *f_REL_OP;
    FILE *f_SET_OP;
    FILE *f_VAR;
    int row = 0;
    int j =0;
    char *line = NULL;
    size_t len = 0;

    f_OP = fopen("op", "r");
    row = lineCount("op")-1;
    char ** opArr = (char**)malloc(sizeof(char*)*row);
    j = 0;
    line = NULL;
    len = 0;
    while ((getline(&line, &len, f_OP)) != -1) {
        opArr[j++] = strdup(strtok(line, "\r\n"));
    }
    printf("%s", opArr[0]);
    printf("\n");
    /* ------ */
    /* ------ */
    /* ------ */
    f_PRE_OP = fopen("pre_op", "r");
    row = lineCount("pre_op")-1;
    char ** pre_opArr = (char**)malloc(sizeof(char*)*row);
    j = 0;
    line = NULL;
    len = 0;
    while ((getline(&line, &len, f_PRE_OP)) != -1) {
        pre_opArr[j++] = strdup(strtok(line, "\r\n"));
    }
    printf("%s", pre_opArr[0]);
    printf("\n");
    /* ------ */
    /* ------ */
    /* ------ */
    f_REL_OP = fopen("rel_op", "r");
    row = lineCount("rel_op")-1;
    char **rel_opArr = (char**)malloc(sizeof(char*)*row);
    j = 0;
    line = NULL;
    len = 0;
    while ((getline(&line, &len, f_REL_OP)) != -1) {
        rel_opArr[j++] = strdup(strtok(line, "\r\n"));
    }
    printf("%s", rel_opArr[0]);
    printf("\n");
    /* ------ */
    /* ------ */
    /* ------ */
    f_SET_OP = fopen("set_op", "r");
    row = lineCount("set_op")-1;
    char ** set_opArr = (char**)malloc(sizeof(char*)*row);
    j = 0;
    line = NULL;
    len = 0;
    while ((getline(&line, &len, f_SET_OP)) != -1) {
        set_opArr[j++] = strdup(strtok(line, "\r\n"));
    }
    printf("%s", set_opArr[0]);
    printf("\n");
    /* ------ */
    /* ------ */
    /* ------ */
    f_VAR = fopen("var", "r");
    row = lineCount("var")-1;
    char ** varArr = (char**)malloc(sizeof(char*)*row);
    j = 0;
    line = NULL;
    len = 0;
    while ((getline(&line, &len, f_VAR)) != -1) {
        varArr[j++] = strdup(strtok(line, "\r\n"));
    }
    printf("%s", varArr[0]);
    printf("\n");
    /* ------ */
    /* ------ */
    /* ------ */



    fclose(f_OP);
    fclose(f_PRE_OP);
    fclose(f_REL_OP);
    fclose(f_SET_OP);
    fclose(f_VAR);
    free(opArr);
    free(pre_opArr);
    free(rel_opArr);
    free(set_opArr);
    free(varArr);
    return 0;
}