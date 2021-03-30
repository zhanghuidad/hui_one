#include<iostream>
#include<stdio.h>
#include<stdint.h>
using namespace std;

long FloatTohex(float HEX)//浮点数到十六进制转换1
{    
    cout <<HEX<< endl;
    cout <<&HEX<< endl;
    cout <<(long *)&HEX<< endl;
    cout <<*(long *)&HEX<< endl;
    cout <<hex<<*(long *)&HEX<< endl;
    printf("%X\n",*(long *)&HEX);
    return *( long *)&HEX;
}

int main()
{   
    // int b;
    // uint32_t a = 6;
    // for(int i = 0;i<=31;i++)
    // {
    // // // a = (a>>i)&1;
    // // // a = a>>1;
    // // // a = (a>>1)&1;
    // b = (a>>i)&1;
    // cout << b <<endl;
    // }
    // a = (a>>2)&1;
    
/*//int ** 
    // int b=1; 
    // int *p=&b; 
    // int **a=&p;;
    // cout << **a <<endl;

    // int a = 1;
    // cout << hex << a <<endl;

*/
float Hdecimal=0.1;
cout << &Hdecimal <<endl;

long hX=FloatTohex(Hdecimal);

printf("\n正序十六进制值：\n %f=%X\n",Hdecimal,hX);
return 0;

}
