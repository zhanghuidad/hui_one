#include<stdio.h>
#include<iostream>
#include<stdint.h>
using namespace std;
 
 uint32_t data2hex(float data)  
{
	uint32_t temp;  
	uint8_t i=0;  
  
	temp = data;//转存需要计算的数值  
	while(temp)  
	{      
		temp >>= 1;  
		i++;//计算当前值的尾数占有的位数  
	}  
	i--;//计算下来，i会多加一次，这儿减掉  
	temp = data;  //再次赋值，准备合并
	temp = temp<<(23-i);//补足23位尾数  
	temp = (i+127)<<23 | temp;//计算指数，并与尾数合并起来   
	temp = temp & ~(1<<23);//确定正负  我这儿都是正数，就没管负数了  
	
	return temp;//这里就已经是以浮点数的存储方式表示的传进来的参数了
}

// union{ 
//    float f; 
//    char  buf[4]; 
//  }data; 

// void write_Df(float df) 
// { 
// uint16_t d0,d1; 
// data.f = df; 

// d0 = (data.buf [1] << 8) + data.buf [0] ; 
// d1 = (data.buf [3] << 8) + data.buf [2] ; 
// // cout << d0 <<endl;
// // cout << d1 <<endl;
// }
int main()
{  
   uint32_t a;
   a = data2hex(1.0);
   cout << hex << a << endl;
   // float a = 1.0;
   // write_Df(a);
   // for(int i=0;i<=3;i++)
   // {
   // cout << data.buf[i] << endl;
   // }
  
   
   return 0;
}
