#include <stdio.h>

// float Hex_To_Decimal(unsigned char *Byte,int num)//十六进制到浮点数
// {
// //      char cByte[4];//方法一
// //     for (int i=0;i<num;i++)
// //     {
// //     cByte[i] = Byte[i];
// //     }
// //      
// //     float pfValue=*(float*)&cByte;
// //return  pfValue;
    
//         return *((float*)Byte);//方法二

// }

long FloatTohex(float HEX)//浮点数到十六进制转换1
{   
    return *( long *)&HEX;
}




// void FloatToByte(float floatNum,unsigned char* byteArry)////浮点数到十六进制转换2
// {
//     char* pchar=(char*)&floatNum;
//     for(int i=0;i<sizeof(float);i++)
//     {
//         *byteArry=*pchar;
//         pchar++;
//         byteArry++;
    
//     }
// }


void main()
{

    // unsigned char floatToHex[4];
    // unsigned    char hexbyte[4]={0x3f,0x80,0x00,0x00};//传输数据为3d cc cc cd
    float Hdecimal=0.1;
//     float flh=0.4;
// //     int num=sizeof(hexbyte);
// //     printf("num= %d\n",num);

//     Hdecimal=Hex_To_Decimal(hexbyte,sizeof(hexbyte));//十六进制转换为浮点数
//     printf("\n 浮点数为：\n %f\n",Hdecimal);
    
    long hX=FloatTohex(Hdecimal);//浮点数转换为十六进制一

    printf("\n正序十六进制值：\n %f=%X\n",Hdecimal,hX);//正序显示

    // FloatToByte(Hdecimal,floatToHex);//浮点数转为十六进制二
    
    // printf("\n倒序十六进制：\n%f=%x %x %x %x\n",Hdecimal,floatToHex[0],floatToHex[1],floatToHex[2],floatToHex[3] );//倒序显示
    
    // FloatToByte(flh,floatToHex);//浮点数转为十六进制二

    // printf("\n倒序十六进制：\n%f=%x %x %x %x\n",flh,floatToHex[0],floatToHex[1],floatToHex[2],floatToHex[3] );//低位在前

    // FloatToByte(flh,floatToHex);//浮点数转为十六进制二
    
    // printf("\n正序十六进制：\n%f=%x %x %x %x\n",flh,floatToHex[3],floatToHex[2],floatToHex[1],floatToHex[0] );//高位在前
     
     
}