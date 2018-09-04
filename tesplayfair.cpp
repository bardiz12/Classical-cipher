#include <iostream>
#include <vector>
#include <string>
#include <regex>
using namespace std;

// Kriptografi tugas 1
// Name       : Moch. bardizba Z.
// Student id : 4611416038
// Web        :http://bardizba.com
// Created on : 17th August 2018
// require : g++ with c++11 std, run with : g++ tugas.cpp -o tugas -std=c++11. run ./tugas on unix or tugas.exe on windows
namespace Bardiz{
class playFair{
    vector< vector<char> > tableKey;
    string key;

    public:
        string enc(string plaintext){
            regex abcOnly("[^a-zA-Z]+");
            vector<string> tmp;
            vector<string> plaintextVector;
            vector<string> result;
            string str;
            plaintext = regex_replace(plaintext,abcOnly,"");
            //cout<<plaintext;
            for(unsigned i=0; i<plaintext.size();i+=2){
                /*if(str.size() < 2 ){
                    str+= plaintext[i];
                    
                }else{
                    tmp.push_back(str);
                    str = plaintext[i];
                }*/

                if(plaintext[i] != plaintext[i+1]){
                    str = tolower(plaintext[i]);
                    if(i+1 >= plaintext.size()){
                        str+="z";
                    }else{
                        str+=tolower(plaintext[i+1]);
                    }
                }else{
                    str = tolower(plaintext[i]);
                    str+="z";
                    i--;
                }
               
                if(str.size() == 1){
                    str+="z";
                }
                //cout<<str<<" size = "<<str.size()<<endl;
                tmp.push_back(str);
                //str = plaintext[i] + plaintext[i+1];

                 
            }

            //for

            /*string tmpS;
            for(unsigned i=0;i<tmp.size();i++){
                if(tmp[i][0] == tmp[i][1]){
                    tmpS = "";
                    tmpS.push_back(tmp[i][0]);
                    tmpS.push_back('z');
                    plaintextVector.push_back(tmpS);
                    plaintextVector.push_back(tmpS);
                    //plaintextVector.push_back((tmp[i][1]+'z'));
                }else{
                    plaintextVector.push_back(tmp[i]);
                }
                //cout<<tmp[i]<<" = "<<this->_enc(tmp[i])<<endl;
                //cout<<tmp[i]<<endl;
                //this->_enc(tmp[i]);
            }*/

            for(string &st : tmp){
                result.push_back(this->_enc(st));
            }
            return this->vec2string(result);
        }

        string dec(string plaintext){
            regex abcOnly("[^a-zA-Z]+");
            vector<string> tmp;
            vector<string> plaintextVector;
            string result;
            string str;
            string gb;
            plaintext = regex_replace(plaintext,abcOnly,"");
            for(unsigned i=0; i<plaintext.size();i+=2){
                /*if(str.size() < 2 ){
                    str+= plaintext[i];
                    
                }else{
                    tmp.push_back(str);
                    str = plaintext[i];
                }*/

                //if(plaintext[i] != plaintext[i+1]){
                    str = tolower(plaintext[i]);
                    str+=tolower(plaintext[i+1]);
                //}else{
                //    str = tolower(plaintext[i]);
                //    str+="z";
                //    i--;
                //}


            
               
                //cout<<str<<" size = "<<str.size()<<endl;
                /*if(str[0] != 'z' && str[1] == 'z'){
                    gb = str;
                    str = str[0];
                    str+=gb[0];
                }
                
                */
                //str = plaintext[i] + plaintext[i+1];

                 tmp.push_back(str);
            }

            for(string &st : tmp){
                //cout<<st<<endl;
                result +=this->_dec(st);
            }

            string newResult;
            bool pass = true;
            for(unsigned i = 0; i < result.size(); i++)
            {
                
                if(i>0){
                    if(result[i] == 'z'){
                        if(result[i-1] == result[i+1]){
                            pass = false;
                        }
                    }
                }
                if(pass){
                    newResult+=result[i];
                }
                pass = true;
            }
            

            return newResult;
        }

        string vec2string(vector<string> vec){
            string result = "";
            for(string &st : vec){
                result+=st;
            }
            return result;
        }

        string humanize(string raw, string temp){
            int i = 0;
            string res = "";
            for(char &c : temp){
                if(c != ' ' && c!= '\n' && c!='.' && c!= ','){
                    res+=raw[i++];
                }else{
                    res+=c;
                }
            }
            return res;
        }
        string _enc(string str){
            string tmp = "";
            string result="";
            int ax,ay,bx,by;
            
            for(unsigned i=0;i<5;i++){
                for(unsigned j=0;j<5;j++){
                    if(this->tableKey[i][j] == str[0]){
                        ay = i;
                        ax = j;
                    }
                    if(this->tableKey[i][j] == str[1]){
                        by = i;
                        bx = j;
                    }
                }
            }
            
            //cout<<str[0]<<" = "<<ax<<","<<ay<<endl;
            //cout<<str[1]<<" = "<<bx<<","<<by<<endl;
            //cout<<"enc :"<<endl;
            //cout<<str<<"=";
            if(ay == by){
                result+= this->tableKey[ay][(((ax+1) % 5))];
                result+= this->tableKey[ay][(((bx + 1) % 5))];
            }else if(ax == bx){
                result+= this->tableKey[ay][(((ay+1) % 5))];
                result+= this->tableKey[ay][(((by + 1) % 5))];
            }else{
                result+= this->tableKey[ay][bx];
                result+= this->tableKey[by][ax];
            }
            //cout<<" ";
            return result;
        }

        string _dec(string str){
            string tmp = "";
            string result="";
            int ax,ay,bx,by,satu,dua,tiga,empat;
            
            for(unsigned i=0;i<5;i++){
                for(unsigned j=0;j<5;j++){
                    if(this->tableKey[i][j] == str[0]){
                        ay = i;
                        ax = j;
                    }
                    if(this->tableKey[i][j] == str[1]){
                        by = i;
                        bx = j;
                    }
                }
            }
            
            
            //cout<<str<<"=";
            if(ay == by){
                satu = ((ax - 1));
                satu = (satu < 0 ? (satu + 5) : satu);
                dua = ((bx - 1));
                dua = (dua < 0 ? (dua + 5) : dua);
                //cout<<str[0]<<" = "<<<<","<<(ay)<<endl;
                result+= this->tableKey[ay][satu];
                result+= this->tableKey[by][dua];
            }else if(ax == bx){
                cout<<str[0]<<" = "<<ax<<","<<ay<<endl;
                cout<<str[1]<<" = "<<bx<<","<<by<<endl;
                cout<<"enc :"<<endl;
                satu = ((ay - 1));
                satu = (satu < 0 ? (satu + 5) : satu);
                dua = ((by - 1));
                dua = (dua < 0 ? (dua + 5) : dua);
                //cout<<str[0]<<" = "<<<<","<<(ay)<<endl;
                result+= this->tableKey[satu][ax];
                result+= this->tableKey[dua][bx];
            }else{
                result+= this->tableKey[ay][bx];
                result+= this->tableKey[by][ax];
            }
            //cout<<" "<<endl;
            return result;
        }

        string generateKey(string key,char exlude){
                this->key = "";
                
                bool found;
                for(char& k : key+"abcdefghijklmnopqrstuvwxyz" )
                {
                    found = false;
                    for(char& j : this->key){
                        if(k == j){
                            found = true;
                        }
                    }
                    if(!found && exlude != k){
                        this->key+=k;
                    }

                }

                return this->key;
                
        }

        vector< vector<char> > getMatrix(){
            return this->tableKey;
        }

        vector< vector<char> > generateTable(){
            
            int index = 0;
            for(unsigned i = 0; i < 5; i++)
            {
                vector<char> row;
                for(unsigned j = 0; j < 5; j++)
                {
                   row.push_back(this->key[index++]);
                }
                tableKey.push_back(row);
                
            }            

            return tableKey;

            
        }

};
};

/*int main(){

    playFair pf = playFair();
    
    string key = pf.generateKey("standerchbkfgil",'j');
    string pt = "good brooms sweep clean";
    vector< vector<char> > ab = pf.generateTable();

    cout<<"Matrix Table : \n";
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cout<<ab[i][j]<<" ";
        }
        cout<<"\n";
    }

    string encr = pf.vec2string(pf.enc(pt));
    //cout<<encr<<endl;

    string decr = pf.dec(encr);
    string human = pf.humanize(decr,pt);
    cout<<human;
}*/

