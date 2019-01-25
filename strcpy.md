

```cpp

//将源字符串加const，表明其为输入参数
//对源地址和目的地址加非0断言
//为了实现链式操作，将目的地址返回
char* StrCpy(char* strDest, const char* strSrc){
    
    assert((strDest!=NULL)&&(strSrc!=NULL));
    
    char *address=strDest;
    while((*strDest++ = *strSrc++) != '\0');
    return address;
}

```

为了实现链式操作，将目的地址返回Strcpy函数可以作为另外一个函数的实参。考虑：

int length = strlen( strcpy(str, “Hello World”) );
