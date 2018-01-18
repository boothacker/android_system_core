extern "C" {
    void _ZN7android6Tracer4initEv(){}
    void _ZN7android10VectorImpl19reservedVectorImpl1Ev() { };
    void _ZN7android10VectorImpl19reservedVectorImpl2Ev() { };
    void _ZN7android10VectorImpl19reservedVectorImpl3Ev() { };
    void _ZN7android10VectorImpl19reservedVectorImpl4Ev() { };
    void _ZN7android10VectorImpl19reservedVectorImpl5Ev() { };
    void _ZN7android10VectorImpl19reservedVectorImpl6Ev() { };
    void _ZN7android10VectorImpl19reservedVectorImpl7Ev() { };
    void _ZN7android10VectorImpl19reservedVectorImpl8Ev() { };
    void _ZN7android16SortedVectorImpl25reservedSortedVectorImpl1Ev() { };
    void _ZN7android16SortedVectorImpl25reservedSortedVectorImpl2Ev() { };
    void _ZN7android16SortedVectorImpl25reservedSortedVectorImpl3Ev() { };
    void _ZN7android16SortedVectorImpl25reservedSortedVectorImpl4Ev() { };
    void _ZN7android16SortedVectorImpl25reservedSortedVectorImpl5Ev() { };
    void _ZN7android16SortedVectorImpl25reservedSortedVectorImpl6Ev() { };
    void _ZN7android16SortedVectorImpl25reservedSortedVectorImpl7Ev() { };
    void _ZN7android16SortedVectorImpl25reservedSortedVectorImpl8Ev() { };
    volatile int _ZN7android6Tracer8sIsReadyE = 1;
    unsigned long long _ZN7android6Tracer12sEnabledTagsE = 0;
    int _ZN7android6Tracer8sTraceFDE = -1;
void _ZN7android9CallStackC1EPKci(char const*, int);
 void _ZN7android9CallStack6updateEii(int, int);

 void _ZN7android9CallStackC1EPKcii(char const* logtag, int ignoreDepth, int maxDepth){
  maxDepth = maxDepth-1;
  maxDepth = maxDepth+1;
  _ZN7android9CallStackC1EPKci(logtag, ignoreDepth);
  
 }

 void _ZN7android9CallStack6updateEiii(int ignoreDepth, int maxDepth, int tid){
  maxDepth = maxDepth-1;
  maxDepth = maxDepth+1; 
  _ZN7android9CallStack6updateEii(ignoreDepth, tid);
 }
}
