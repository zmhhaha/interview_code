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
quit
*/

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <exception>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <map>

std::map<int, std::string> hash={{0,"零"},{1,"一"},{2,"二"},{3,"三"},{4,"四"},{5,"五"},{6,"六"},{7,"七"},{8,"八"},{9,"九"},
                       {10,"十"},{100,"百"},{1000,"千"},{11,"元"},{12,"万"},{13,"亿"},{14,"角"},{15,"分"}};

class parameterexception: public std::exception { 
public:
    virtual const char* what() const throw() 
    {   
        std::stringstream errMessage;
        errMessage
        << "Have some mistake in parameter\n"
        << "The struct of input\n"
        << "Mode\n"
        << "  -i The interactive mode.\n"
        << "  -f The input file mode.\n"
        << "Example: -i\n"
        << "Example: -f filename\n";
        return errMessage.str().c_str(); 
    }
};

class numberinputexception: public std::exception { 
public:
    virtual const char* what() const throw() 
    {   
        return "This is not an effective input.\nExample: xxxxx.xx"; 
    }
};

void parameterInput(int argc, char* argv[]){
    if(2 == argc && 0 == strcmp(argv[1],"-i")) { }
    else if(3 == argc && 0 == strcmp(argv[1],"-f")){ }
    else {
        throw parameterexception();
    }
}

int effectivechar(char onechar){
    if(onechar <= '9' && onechar >= '0') return 1;
    if('.' == onechar) return 2;
    return 0;
}

std::string effectivity(char* originNumber){
    //std::cout << strlen(originNumber) << std::endl;
    //std::cout << originNumber << std::endl;
    std::string effans = "";
    int nstring = strlen(originNumber);
    if(nstring > 15) {
        throw(numberinputexception());
        return "-1";
    }
    int point = 0;
    int pointlocation = -1;
    int stringbegin = -1;
    int stringend = nstring;
    for(int i = 0; i < nstring; i++){
        if(pointlocation != -1 && i - pointlocation > 2){
            throw(numberinputexception());
            return "-1";
        }
        if(0 == effectivechar(originNumber[i])){
            throw(numberinputexception());
            return "-1";
        }else if(2 == effectivechar(originNumber[i])){
            point++;
            if(nstring - i - 1 == 1 && nstring > 14){
                throw(numberinputexception());
                return "-1";
            } 
            pointlocation = i;
            if(2 == point || 0 == i || nstring - 1 == i){
                throw(numberinputexception());
                return "-1";
            }
            if(-1 == stringbegin) stringbegin = i - 1;
        }else{
            if(originNumber[i] != '0') {
                stringend = i;
                if(-1 == stringbegin) stringbegin = i;
            }
        }
    }
    if(0 == point) {
        stringend = nstring - 1;
        if(nstring > 12) {
            throw(numberinputexception());
            return "-1";
        }
    }
    //std::cout << stringend - stringbegin + 1 << std::endl;
    if(-1 == stringbegin || nstring == stringend) return "0";
    for(int i = stringbegin; i <= stringend; i++){
        effans += originNumber[i];
    }
    return effans;
}

class transverter{
public:
    transverter(std::string& input): _originstring(input){}
    std::vector<int> transfer(){
        int nstring = _originstring.size();
        std::vector<int> ans;
        if(_originstring.size() == 1 && _originstring[0] == '0') return std::vector<int>(1,0);
        int pointlocation = _originstring.find(".");
        if(pointlocation == std::string::npos) return integer(0,_originstring.size()-1);
        if(pointlocation == 1 && _originstring[0] == '0') {
            ans = decimals(2,nstring - 1);
            ans.pop_back();
            return ans;
        }
        ans = decimals(pointlocation+1, nstring - 1);
        std::vector<int> integerans(integer(0,pointlocation-1));
        ans.insert(ans.end(),integerans.begin(),integerans.end());
        return ans;
    }
    std::vector<int> decimals(int begin, int end){
        std::vector<int> key;
        if(end - begin == 1){
            if(_originstring[begin] == '0'){
                key.push_back(15);
                key.push_back(_originstring[end]-'0');
                key.push_back(0);
            }
            else{
                key.push_back(15);
                key.push_back(_originstring[end]-'0');
                key.push_back(14);
                key.push_back(_originstring[begin]-'0');
            }
        }
        else{
            key.push_back(14);
            key.push_back(_originstring[begin]-'0');
        }
        if(_originstring[begin - 2] == '0' && *(key.rbegin()) != 0) key.push_back(0);
        return key;
    }
    std::vector<int> integer(int begin, int end){
        std::vector<int> key;
        int partend = end;
        int partbegin;
        bool prezero = false;
        if(end - begin < 3) partbegin = begin;
        else partbegin = end - 3;
        std::vector<int> part(fourchar(partbegin,partend));
        if(part.size() != 0) {
            key.push_back(11);
            key.insert(key.end(), part.begin(), part.end());
        }
        else prezero = true;
        int numberbit = 12;
        for(partend = partbegin - 1; partend >= begin; partend = partbegin - 1, numberbit++){
            part.clear();
            partbegin = partbegin -4;
            if(partbegin < 0) part = fourchar(begin, partend);
            else part = fourchar(partbegin, partend);
            if(part.size() != 0) {
                key.push_back(numberbit);
                key.insert(key.end(), part.begin(), part.end());
                prezero = false;
            }
            else if(!prezero) key.push_back(0);
        }
        return key;
    }
    std::vector<int> fourchar(int begin, int end){
        std::vector<int> key;
        if(_originstring[end] != '0') key.push_back(_originstring[end]-'0');
        int numberbit = 10;
        for(int i = end - 1; i >= begin; i--, numberbit *= 10){
            if(_originstring[i] != '0') {
                key.push_back(numberbit);
                key.push_back(_originstring[i]-'0');
            }
            else if(_originstring[i+1] != '0') key.push_back(0);
        }
        return key;
    }
private:
    std::string _originstring;
};

int main(int argc, char* argv[]){
    try{
        parameterInput(argc, argv);
    }
    catch(parameterexception& e){
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    catch(std::exception& e){
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    if(2 == argc) {
        char originNumber[20];
        while(true){
            memset(originNumber,0,sizeof(originNumber));
            std::cout << "Please input a number:";
            scanf("%s",originNumber);
            std::string effstring = "";
            if(4 == strlen(originNumber)
                && originNumber[0] == 'q'
                && originNumber[1] == 'u'
                && originNumber[2] == 'i'
                && originNumber[3] == 't') return 0;
            try{
                effstring += effectivity(originNumber);
            }
            catch(numberinputexception& e){
                std::cout << e.what() << std::endl;
                continue;
            }
            std::cout << effstring.c_str() << std::endl;
            transverter trans(effstring);
            std::vector<int> ans(trans.transfer());
            for(int i = ans.size() - 1; i >= 0; i--)
            printf("%s", hash[ans[i]].c_str());
            printf("\n");
        }
    }

    if(3 == argc) {
        std::string filein = argv[2];
        std::string fileout = "result.dat";
        std::ifstream infile;
        std::ofstream outfile;
        try{
            infile.open(filein);
            outfile.open(fileout, std::ios::ate);
        }
        catch(std::exception& e){
            std::cout << e.what() << std::endl;
            std::cout << "file open fail\n";
        }
        char originNumber[20];
        memset(originNumber,0,sizeof(originNumber));
        while(infile >> originNumber){
            std::string effstring = "";
            try{
                effstring += effectivity(originNumber);
            }
            catch(numberinputexception& e){
                std::cout << e.what() << std::endl;
                continue;
            }
            outfile << effstring.c_str() << "\t";
            transverter trans(effstring);
            std::vector<int> ans(trans.transfer());
            for(int i = ans.size() - 1; i >= 0; i--)
            outfile << hash[ans[i]].c_str();
            outfile << "\n";
            memset(originNumber,0,sizeof(originNumber));
        }
    }

    /*std::string input="1110.01";

    transverter trans(input);

    std::vector<int> ans(trans.transfer());

    for(int i=0; i<ans.size();i++){
        printf("%d\t", ans[i]);
    }*/

    return 0;
}

/*结果
Please input a number:1
一元
Please input a number:12
一十二元
Please input a number:113
一百一十三元
Please input a number:1234
一千二百三十四元
Please input a number:12345
一万二千三百四十五元
Please input a number:123456
一十二万三千四百五十六元
Please input a number:1234567
一百二十三万四千五百六十七元
Please input a number:12345678
一千二百三十四万五千六百七十八元
Please input a number:123456789
一亿二千三百四十五万六千七百八十九元
Please input a number:1234567890
一十二亿三千四百五十六万七千八百九十元
Please input a number:13456789001
一百三十四亿五千六百七十八万九千零一元
Please input a number:123456789012
一千二百三十四亿五千六百七十八万九千零一十二元
Please input a number:123456789012.1
一千二百三十四亿五千六百七十八万九千零一十二元一角
Please input a number:123456789012.01
一千二百三十四亿五千六百七十八万九千零一十二元零一分
Please input a number:101010101010.01
一千零一十亿一千零一十万一千零一十元零一分
Please input a number:0
零
Please input a number:0
零
Please input a number:0
零
Please input a number:0
零
Please input a number:0.01
一分
Please input a number:1
一元

*/
