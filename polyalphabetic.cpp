#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>
#include <regex>
using namespace std;

namespace Bardiz{
class bujurSangkarVignere{
    private:
        string plainteks;
        string key;
        regex abcOnly = regex("[^a-zA-Z]");
        char bujursangkar[27][27] = {
            {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'},
            {'b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a'},
            {'c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b'},
            {'d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c'},
            {'e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d'},
            {'f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e'},
            {'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f'},
            {'h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f','g'},
            {'i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h'},
            {'j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i'},
            {'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j'},
            {'l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j','k'},
            {'m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j','k','l'},
            {'n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j','k','l','m'},
            {'o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j','k','l','m','n'},
            {'p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o'},
            {'q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'},
            {'r','s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q'},
            {'s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r'},
            {'t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s'},
            {'u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t'},
            {'v','w','x','y','z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u'},
            {'w','x','y','z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v'},
            {'x','y','z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w'},
            {'y','z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x'},
            {'z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y'},
            {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}};

    public :
        string encrypt(string plainteks, string key){
            //cout <<bujursangkar[0][18];
            string result = "";
            int k,counter=0;
            int s;

            for(char &c : plainteks){
            if(c == ',' || c== '.' || c== '\n' || c == ' '){
                result+=c;
                //cout<<c;
            }else{
                s = ((int) key[counter++]) - 97;
                if(counter == key.size()){
                    counter = 0;
                }
                if(isupper(c)){
                    k = ((int) tolower(c)) - 97;
                    result+=toupper(bujursangkar[k][s]);
                }else{
                    k = ((int) c) - 97;
                    result+=bujursangkar[k][s];
                }
            }
            }
            return result;
        }

        string decrypt(string chiper, string key){
            string theOneWhoCantBeNamed = "";
            int k,counter=0;
            int s;
            int theChosenOne =0;
            //cout<<chiper[0]<<endl;
            for(char &c : chiper){
                if(c == ',' || c== '.' || c== '\n' || c == ' '){
                    theOneWhoCantBeNamed+=c;
                }else{
                    s = ((int) key[counter++]) - 97;
                    if(counter == key.size()){
                        counter = 0;
                    }
                    for(int i=0;i<27;i++){
                        if(bujursangkar[s][i] == tolower(c)){
                            theChosenOne = i;
                            break;
                        }                       
                    }
                    theOneWhoCantBeNamed+= isupper(c) == true ? toupper(bujursangkar[0][theChosenOne]) : bujursangkar[0][theChosenOne];
                }
            }

            return theOneWhoCantBeNamed;
        }
};
};

/*
int main(){
    string plainteks = "this plaintext";
    string key = "sony";
    bujurSangkarVignere v2 = bujurSangkarVignere();
    string enc = v2.enc(plainteks,key);
    cout<<v2.dec(enc,key);
    
    
    
    

    

};*/