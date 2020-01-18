#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef  enum  {false, true} bool;
typedef enum {threeLeaf, twoLeaf, oneLeaf, zeroLeaf} dataType;
int random(int range){
    srand(time(NULL));
    return rand()%range;
}
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
/****defined specifications****/


typedef struct leaf3Tree{
    void* left;
    void* mid;
    void* right;
} leaf3Tree;

typedef struct leaf2Tree{
    void* left;
    void* right;
} leaf2Tree;

typedef struct leaf1Tree{
    void* child;
} leaf1Tree;

typedef struct leaf{
    char *data;
} leaf;

typedef struct Node{
    void* node;
    dataType type;
}Node;







leaf3Tree *whichCondition(Node *root, int rnd){
    root = malloc(sizeof(leaf3Tree));
    Node tmpnode;
    leaf3Tree * l3root = (leaf3Tree*)malloc(sizeof(leaf3Tree));





    int thisRnd;
    if(rnd == 0){
        /* if random is 0 then create (<cond><set-op><cond>)*/
        root->type = threeLeaf;
        thisRnd = random(2);


    }
    else if(rnd ==1){
        /* if random is 1 then create (<expr><rel-op><expr>) */

    }
};
leaf3Tree *whichExpression(void);
void showTree(Node *root);

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
//    printf("%s", opArr[0]);
//    printf("\n");
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
//    printf("%s", pre_opArr[0]);
//    printf("\n");
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
//    printf("%s", rel_opArr[0]);
//    printf("\n");
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
//    printf("%s", set_opArr[0]);
//    printf("\n");
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
//    printf("%s", varArr[0]);
//    printf("\n");
    /* ------ */
    /* ------ */
    /* ------ */

    int rCnd = random(2);
    Node *root = NULL;


    printf("if(");
    printf(") {}\n");

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