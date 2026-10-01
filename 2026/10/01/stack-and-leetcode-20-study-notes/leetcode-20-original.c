typedef int SLDataType;
typedef struct Stack{
    SLDataType* a;
    int top;
    int capacity;
}ST;

void SLInit(ST* pst){
    assert(pst);
    pst->a=NULL;
    pst->top=0;
    pst->capacity=0;
}

void SLDestroy(ST* pst){
    assert(pst);
    free(pst->a);
    pst->top=pst->capacity=0;
}

void SLPush(ST* pst,SLDataType x){
    assert(pst);
    //扩容
    if(pst->top==pst->capacity){
        int newcapacity=pst->capacity==0?4:pst->capacity*2;
        SLDataType* tmp=(SLDataType*)realloc(pst->a,sizeof(SLDataType)*newcapacity);
        if(tmp==NULL){
            perror("realloc fail");
            return;
        }
        pst->a=tmp;
        pst->capacity=newcapacity;
    }
    pst->a[pst->top]=x;
    pst->top++;
}

void STPop(ST* pst){
    assert(pst);
    assert(pst->top>0);
    pst->top--;
}

SLDataType STTop(ST* pst){
    assert(pst);
    assert(pst->top>0);
    return pst->a[pst->top-1];
}

bool STEmpty(ST* pst){
    assert(pst);
    return pst->top==0;
}

int STsize(ST* pst){
    assert(pst);
    return pst->top;
}

bool isValid(char* s) {
    ST st;
    SLInit(&st);
    while(*s){
        if(*s=='('||*s=='['||*s=='{'){
            SLPush(&st,*s);
        }
        else{
            if(STEmpty(&st)){
                SLDestroy(&st);
                return false;
            }
            char top=STTop(&st);
            STPop(&st);
            if((top=='(' && *s!=')') ||
               (top=='[' && *s!=']') ||
               (top=='{' && *s!='}')){
                SLDestroy(&st);
                return false;
            }
        }
        ++s;
    }
    bool ret = STEmpty(&st);
    SLDestroy(&st);
    return ret;
}
