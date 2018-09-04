#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>
#include "tesplayfair.cpp"
#include "polyalphabetic.cpp"
using namespace std;
#ifdef WINDOWS
bool isWIndows = true;
#else
bool isWindows = false;
#endif
// Kriptografi tugas 1
// Name       : Moch. bardizba Z.
// Student id : 4611416038
// Site       : http://bardizba.com
// Created on : 17th August 2018
// require    : g++ with c++11 std, run with : g++ tugas.cpp -o tugas -std=c++11. run ./tugas on unix or tugas.exe on windows

string filename = "";
string plaintext;
string resultFilename;
string result;
string ans;
int menu=0;
int menu2=0;
Bardiz::playFair pf = Bardiz::playFair();

char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";

string serviceList[2] = {
    "Encryption",
    "Decryption"
};

string menuList[4] = {
    "Caesar Shift",
    "Vignere Chiper (Polyalphabetic Chiper using Table)",
    "Vignere Chiper",
    "Playfair Chiper"
};


void pagar(){
    cout<<"==================================\n";
}

void clearScreen(){
    system(isWindows ? "cls" : "clear");
}

void header(){
    system("clear");    
    pagar();
    cout<<"Cryptography Assignment\n";
    cout<<"Moch. Bardizba Z. (4611416038)\n";
    cout<<"Created on 17th August 2018\n";
            pagar();
    if(filename != ""){
        cout<<"[Input file : "<<filename<<"]"<<endl;
    }

}

void saveToFile(string filename,string input){
    ofstream out(filename);
    out << input;
    out.close();
}


string monoAlphabeticCaesar(bool enc){
    header();
    cout<<"Key (Integer) : ";
    int key = 0;
    scanf("%u",&key);
    clearScreen();
    pagar();
    cout<<"Monoalphabetic Caesar Shift Encryption"<<endl;
    cout<<"Key = "<<key<<endl;
    //cout<<(enc ? "Plaintext" : "Chipertext")<<endl;
    //                    pagar();
    //cout<<plaintext<<endl<<endl;
    cout<<(enc ? "Chipertext" : "Plaintext")<<endl;
                        pagar();
    int realKey = key > 26 ? key % 26 : key;
    
    string result = "";
    char n;
    int k;
    int margin=0;
    for(char& c : plaintext)
    {
        if(c != ' ' &&  c!= '\n' && c != '.' && c != ','){
            margin = ( ((int) c) <= 90 && ((int) c) >= 65) ? 65 : 97;
            k = ((((int) c - margin) + (realKey * (enc ? 1 : -1))) % 26);
            n = ((k < 0 ? k + 26 : k)+margin);
            result+=n;
        }else{
            result+=c;
        }
    }

    cout<<result<<endl<<endl;
    
    cout<<"Save to file ? (y/n): ";
    cin>>ans;
    if(ans == "y" || ans == "Y"){
        cout<<"Filename : ";
        cin>>resultFilename;
        saveToFile(resultFilename,result);
        cout<<"Saved as "<<resultFilename<<endl;
    }
    return result;
}

string polyAlphabetic(bool enc){
    
    return "ass";
}

string VignereChiper(bool enc){
    header();
    string key;
    cout<<"Key (string) : ";
    cin>>key;
    clearScreen();
                pagar();
    cout<<menuList[menu2 + 1]<<" "<<(enc ? "Encryption" : "Decryption");
    cout<<"\nKey = "<<key<<endl;
                pagar();
    int indexKey = 0;
    char n;
    int k;
    for(char &c : plaintext){
        if(c != ' ' &&  c!= '\n' && c!= ',' && c!='.'){
            
            if(isupper(c)){
                k = ((((int) c - 65) + ((((int) toupper(key[indexKey])) - 65) * (enc ? 1 : -1))) % 26);
                n = (char) ((k < 0 ? k + 26 : k)+65);
            }else{
                k = ((((int) c - 97) + ((((int) key[indexKey]) - 97) * (enc ? 1 : -1))) % 26);
                n = (char) ((k < 0 ? k + 26 : k)+97);
            }
            

            if(indexKey < key.size() -1 ){
                indexKey++;
            }else{
                indexKey = 0;
            }
            result+=n;
        }else{
            result+=c;
        }
    }

    cout<<result<<endl;
    return result;
}

string menuPlayFair(bool enc){
    header();
    string key,result;
    char omit;
    cout<<"Key & Omit char : ";
    cin>>key>>omit;
    pf.generateKey(key,omit);
    pf.generateTable();
    result = enc ? pf.enc(plaintext) : pf.dec(plaintext);
    clearScreen();
            pagar();
    cout <<menuList[menu]<<" ";
    cout<< (enc ? "Encryption " : "Decryption ")<<"Result"<<endl;
            pagar();
    cout<<result<<endl;
    return result;
}

string vignerePakeTabel(bool enc){
    header();
    string key;
    cout<<"Input key (string) : ";
    cin>>key;
                    pagar();
    cout<<"Polyalphabetic Chiper (Vignere chiper using table)\n";
    cout<<(enc ? "Encryption" : "Decryption")<<" Result"<<endl;
                    pagar();
    cout<<"Key : "<<key<<endl;
    
    Bardiz::bujurSangkarVignere bsv = Bardiz::bujurSangkarVignere();
    string result = enc == true ? bsv.encrypt(plaintext,key) : bsv.decrypt(plaintext,key);
    cout<<result<<endl;
    return result;
}

void apaYa(){
    bool enc = menu == 1 ? true : false;
    if(menu2 == 1){
        result = monoAlphabeticCaesar(enc);
    }else if(menu2 == 2){
        result = VignereChiper(enc);
    }else if(menu2 == 3){
        result = vignerePakeTabel(enc);
    }else if(menu2 == 4){
        result = menuPlayFair(enc);
    }else{
        
    }

    cout<<"Save to file ? (y/n): ";
    cin>>ans;
    if(ans == "y" || ans == "Y"){
        cout<<"Filename : ";
        cin>>resultFilename;
        saveToFile(resultFilename,result);
        cout<<"Saved as "<<resultFilename<<endl;
    }
}

void menus2(){
    header();
    cout<<"What type of "<<serviceList[menu-1]<<" do you want? \n";
    for(int i=0;i<4;i++){
        cout<<(i+1)<<". "<<menuList[i]<<endl;
    }
    cout<<"Answer : ";
    scanf("%u",&menu2);
    if(menu2 <= 0 && menu2 > 2){
        system("clear");
        cout<<"ERROR: invalid input\n";
        menus2();        
    }
    apaYa();
}

void menus(){
    header();
    for(int i = 0; i < 2; i++)
    {
        cout<<(i+1)<<". "<<serviceList[i]<<endl;
    }
    
    cout<<"Select menu : ";
    scanf("%u",&menu);
    if(menu <= 0 && menu > 2){
        system("clear");
        cout<<"ERROR: invalid input\n";
        menus();        
    }
    menus2();
}


int main(int argc, char* argv[]){
    ////check if argv[1] is set
    if(argc == 2){
        filename = argv[1];
        cout<<"File : "<<filename<<endl;
    }else{
        header();
        cout<<"File input: ";
        cin>>filename;
    }

    fstream f(filename, fstream::in );
    if(!f.good()){
        cout<<"File "<<filename<<" doesn't exist! abort..";
        return 0;
    }
    getline( f, plaintext, '\0');
    f.close();

    menus();
}