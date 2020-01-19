#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
char *condition[] = {"(<cond><set-op><cond>)", "(<expr><rel-op><expr>)"};
char *expressionRule[] = {"(<expr><op><expr>)", "<pre-op>(<expr>)", "<var>"};
typedef  enum  {false, true} bool;
typedef enum {threeLeaf, twoLeaf, oneLeaf, zeroLeaf} dataType;
int rando(int range){
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
char* randomTerminal(char** op,int opsize, char** preop, int preopsize, char** relop, int relopsize, char** setop, int setopsize,  char** var, int varsize, char* type){
    char* terminal;
    int rnd;
    if(strcmp(type, "op") == 0){
        rnd = rando(opsize);
        terminal = op[rnd];
        return terminal;
    }else if(strcmp(type, "pre_op")==0){
        rnd = rando(preopsize);
        terminal = preop[rnd];
        return terminal;
    }else if(strcmp(type, "rel_op") == 0){
        rnd = rando(relopsize);
        terminal = relop[rnd];
        return terminal;
    }else if(strcmp(type, "set_op") == 0){
        rnd = rando(setopsize);
        terminal = setop[rnd];
        return terminal;
    }else if(strcmp(type, "var") == 0){
        rnd = rando(varsize);
        terminal = var[rnd];
        return terminal;
    }else{
        terminal = "error";
        return terminal;
    }
}

typedef struct leaf3Tree{
    void* left;
    void* mid;
    void* right;
    dataType type;
} leaf3Tree;

typedef struct leaf2Tree{
    void* left;
    void* right;
    dataType type;
} leaf2Tree;

typedef struct leaf1Tree{
    void* child;
    dataType type;
} leaf1Tree;

typedef struct leaf{
    char *data;
    dataType type;
} leaf;

typedef struct Node{
    void* node;
    dataType type;
}Node;

leaf * nodeWithleaf (char** op,int opsize, char** preop, int preopsize, char** relop, int relopsize, char** setop, int setopsize,  char** var, int varsize, char* type){
    leaf *newNode = (leaf*)malloc(sizeof(leaf));
    char* term = randomTerminal(op, opsize, preop, preopsize, relop, relopsize, setop, setopsize, var, varsize, type);
    newNode->data = term;
    newNode->type = zeroLeaf;
    return newNode;
}
leaf1Tree *nodeWith1leaf(char** op,int opsize, char** preop, int preopsize, char** relop, int relopsize, char** setop, int setopsize,  char** var, int varsize, char* type){
    leaf1Tree *newNode = (leaf1Tree*)malloc(sizeof(leaf1Tree));
    newNode->child = ((leaf*)&newNode->child);
    newNode->type = oneLeaf;
    newNode->child = nodeWithleaf(op, opsize, preop, preopsize, relop, relopsize, setop, setopsize, var, varsize, type);
    return newNode;

}
Node *whichExpression(int num, Node* root, char** op,int opsize, char** preop, int preopsize, char** relop, int relopsize, char** setop, int setopsize,  char** var, int varsize){


    int rnd;

    switch(num){

        case 0:
            printf("%s\n", expressionRule[0]);
            root->type = threeLeaf;
            rnd = rando(3);
            root->node = (leaf3Tree*)root->node;
            ((leaf3Tree*)root->node)->left = whichExpression(rnd, ((leaf3Tree*)root->node)->left , op, opsize, preop, preopsize, relop, relopsize, setop, setopsize, var, varsize);

            ((leaf3Tree*)root->node)->mid = nodeWith1leaf(op, opsize, preop, preopsize, relop, relopsize, setop, setopsize, var, varsize, "op");

            rnd = rando(3);
            ((leaf3Tree*)root->node)->right = whichExpression(rnd, ((leaf3Tree*)root->node)->right, op, opsize, preop, preopsize, relop, relopsize, setop, setopsize, var, varsize);
            break;
        case 1:
            printf("%s\n", expressionRule[1]);
            root->type = twoLeaf;
            root->node = (leaf2Tree*)root->node;
            ((leaf2Tree*)root->node)->left = nodeWith1leaf(op, opsize, preop, preopsize, relop, relopsize, setop, setopsize, var, varsize, "pre_op");
            rnd = rando(3);
            (((leaf2Tree*)root->node))->right = whichExpression(rnd, ((leaf2Tree*)root->node)->right, op, opsize, preop, preopsize, relop, relopsize, setop, setopsize, var, varsize);
            break;
        case 2:
            printf("%s\n", expressionRule[2]);
            root->type = oneLeaf;
            root->node = (leaf1Tree*)root->node;
            ((leaf1Tree*)root->node)->child = nodeWith1leaf(op, opsize, preop, preopsize, relop, relopsize, setop, setopsize, var, varsize, "var");
            break;
    }
    return root;

};

Node *whichCondition(int num, Node *root, char** op,int opsize, char** preop, int preopsize, char** relop, int relopsize, char** setop, int setopsize,  char** var, int varsize){


    int rnd;

    switch (num){
        case 0:
            printf("%s\n", condition[0]);

            root->type = threeLeaf;
            rnd = rando(2);
            ((leaf3Tree*)root->node)->left = whichCondition(rnd,root, op, opsize, preop, preopsize, relop, relopsize, setop, setopsize, var, varsize);
            ((leaf3Tree*)root->node)->mid = nodeWith1leaf(op, opsize, preop, preopsize, relop, relopsize, setop, setopsize, var, varsize, "set_op");
            rnd = rando(2);
            ((leaf3Tree*)root->node)->right = whichCondition(rnd,root, op, opsize, preop, preopsize, relop, relopsize, setop, setopsize, var, varsize);

            break;
        case 1:

            printf("%s\n", condition[1]);
            root->type = threeLeaf;
            rnd = rando(3);

            root->node = (leaf3Tree*)root->node;
            ((leaf3Tree*)root->node)->left = whichExpression(rnd,((leaf3Tree*)root->node)->left,  op, opsize, preop, preopsize, relop, relopsize, setop, setopsize, var, varsize );
            ((leaf3Tree*)root->node)->mid = nodeWith1leaf(op, opsize, preop, preopsize, relop, relopsize, setop, setopsize, var, varsize, "rel_op");
            rnd = rando(3);
            ((leaf3Tree*)root->node)->right = whichExpression(rnd,((leaf3Tree*)root->node)->right,  op, opsize, preop, preopsize, relop, relopsize, setop, setopsize, var, varsize );
            break;
    }
    return root;
};

void showTree(Node *root){

};

int main() {


    FILE *f_OP;
    FILE *f_PRE_OP;
    FILE *f_REL_OP;
    FILE *f_SET_OP;
    FILE *f_VAR;
    int row = 0;
    int j =0;
    char *line = NULL;
    size_t len = 0;
    int opSize, preopSize, relopSize,setopSize,varSize;
    f_OP = fopen("op", "r");
    row = lineCount("op")-1;
    opSize=row;
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
    preopSize = row;
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
    relopSize = row;
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
    setopSize = row;
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
    varSize = row;
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
    Node *root = malloc(sizeof(Node));
    int rnd= rando(2);

    root = whichCondition(rnd, root, opArr,opSize, pre_opArr,preopSize,rel_opArr,relopSize, set_opArr,setopSize,varArr,varSize);
    printf("if(");
    showTree(root);
    printf(") {}\n");

/*printf("-------------- \n");
char*term = randomTerminal(opArr,opSize, pre_opArr,preopSize,rel_opArr,relopSize, set_opArr,setopSize,varArr,varSize, "pre_op");
printf(" ||| %s |||", term);
printf("\n--------------");*/
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