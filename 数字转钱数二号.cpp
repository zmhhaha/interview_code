/*输入
1
12
113
1234 
12345 
123456
1234567
12345678
123456789
1234567890
13456789001
123456789012
123456789012.1
123456789012.01
101010101010.01
0.0
0
0.00
00.00
0.01
1.00
q
*/

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

int CheckAmountString(char *pszData, int *pnMainLen, char **ppszDecimal, int* pnDecimalLen){
    int  nMainLen = 0x00, nDecimalLen = 0x00;
    *ppszDecimal = NULL;
    while(*pszData){
        if('.' == *pszData){
            if(NULL == *ppszDecimal){
                *ppszDecimal = pszData + 0x01;
            }
            else{
                return -1;
            }
        }
        else if(*pszData >= '0' && *pszData <= '9'){
            if(NULL == *ppszDecimal){
                nMainLen++;
            }
            else{
                nDecimalLen++;
            }
        }
        else{
            return -1;
        }
        pszData++;
    }
    if(0 == nMainLen || nMainLen >12){
        return -1;
    }
    if(nDecimalLen > 2 || (NULL != *ppszDecimal && 0 == nDecimalLen)){
        return -1;
    }
    *pnDecimalLen = nDecimalLen;
    *pnMainLen = nMainLen;
}

void PrintNumber(char ch){
    switch(ch){
        case '0': printf("零");
        break;
        case '1': printf("一");
        break;
        case '2': printf("二");
        break;
        case '3': printf("三");
        break;
        case '4': printf("四");
        break;
        case '5': printf("五");
        break;
        case '6': printf("六");
        break;
        case '7': printf("七");
        break;
        case '8': printf("八");
        break;
        case '9': printf("九");
        break;
        default:
        break;
    }
}

void PrintTenPowAndMoneyTag(int tag){
    switch(tag){
        case 0: printf("千");
        break;
        case 2: printf("十");
        break;
        case 3: printf("百");
        break;
        
        case 5: printf("万");
        break;
        case 9: printf("亿");
        break;

        case 6: printf("元");
        break;
        case 7: printf("角");
        break;
        case 8: printf("分");
        break;
        default:
        break;
    }
}

int PrintMoneyNumber(char *pszData, int pnMainLen, char *ppszDecimal, int pnDecimalLen){
    char *nMainBegin = NULL;
    int nMainReal = 0x00;
    int nDecimalReal = 0x00;
    int nFourChar = 0x00;
    while(pnMainLen > 0){
        if(pnMainLen % 4 == 0) nFourChar = 0x00;
        if(*pszData >= '1' && *pszData <= '9'){
            if(nMainBegin && '0' == *(pszData - 1)) PrintNumber('0');
            PrintNumber(*pszData);
            PrintTenPowAndMoneyTag(pnMainLen % 4);
            if(!nMainBegin) nMainBegin = pszData;
            nMainReal++;
            nFourChar++;
        }
        if(nFourChar != 0 && pnMainLen % 4 == 1){
            PrintTenPowAndMoneyTag(pnMainLen);
        }
        pszData++;
        pnMainLen--;
    }
    if(nMainReal != 0) PrintTenPowAndMoneyTag(6);
    while(pnDecimalLen > 0){
        if(*ppszDecimal != '0'){
            if(nMainReal != 0 && '0' == *(ppszDecimal - 1)) PrintNumber('0');
            PrintNumber(*ppszDecimal);
            if('.' == *(ppszDecimal - 1)) PrintTenPowAndMoneyTag(7);
            else PrintTenPowAndMoneyTag(8);
            nDecimalReal++;
        }
        pnDecimalLen--;
        ppszDecimal++;
    }
    if(0 == nDecimalReal && 0 == nMainReal) PrintNumber('0');
    return 0;
}

int main(){
    char input[15];
    memset(input, 0x00, 15*sizeof(char));
    while(scanf("%s", input)){
        int pnMainLen = 0;
        int pnDecimalLen = 0;
        char *ppszDecimal = NULL;
        if('q' == *input) return 0;
        if(-1 == CheckAmountString(input, &pnMainLen, &ppszDecimal, &pnDecimalLen)){
            printf("输入不合规");
            continue;
        }
        printf("%s\n", input);
        PrintMoneyNumber(input, pnMainLen, ppszDecimal, pnDecimalLen);
        memset(input, 0x00, 15*sizeof(char));
        printf("\n");
    }
    return 0;
}

/*输出
1
一元
12
一十二元
113
一百一十三元
1234
一千二百三十四元
12345
一万二千三百四十五元
123456
一十二万三千四百五十六元
1234567
一百二十三万四千五百六十七元
12345678
一千二百三十四万五千六百七十八元
123456789
一亿二千三百四十五万六千七百八十九元
1234567890
一十二亿三千四百五十六万七千八百九十元
13456789001
一百三十四亿五千六百七十八万九千零一元
123456789012
一千二百三十四亿五千六百七十八万九千零一十二元
123456789012.1
一千二百三十四亿五千六百七十八万九千零一十二元一角
123456789012.01
一千二百三十四亿五千六百七十八万九千零一十二元零一分
101010101010.01
一千零一十亿零一千零一十万零一千零一十元零一分
0.0
零
0
零
0.00
零
00.00
零
0.01
一分
1.00
一元
*/
