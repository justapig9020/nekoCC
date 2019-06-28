char func1 (int a1, char a2){
    int a;
    char b;
s1:
    b = -1;
    a = a+1-b;
    goto s1;
    return a+b*3;
}

int main (int a, char b) {
    int c;
    int d;
    char e;
    char* f;
    func1 (c+d,e);
/*
 * Here is your context
 */
    return 0;
}

