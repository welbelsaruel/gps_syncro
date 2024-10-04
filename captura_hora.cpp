#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>
#include <sstream>

using namespace std;

string exec(const char* cmd){
    
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

    if(!pipe)
        throw runtime_error("Comando não executado");

    ostringstream result;  
    char c;     

    while (fread(&c, 1, 1, pipe.get()) == 1) {
        result.put(c);  
    }
    
    return result.str();

}

int main(){
    
    string comando="adb shell dumpsys location | grep 'mTime='";

    string hora;

    try{
        hora=exec(comando.c_str());
    }
    catch(const runtime_error& e){
        cerr<<"O comando ADB: "<<e.what()" não foi executado"<<endl;
        return -1;
    }

    if(!hora.empty())
        cout<<"Hora capturada: "<<hora<<endl;
    else
        cerr<<"Erro ao obter a hora"<<endl;

}
