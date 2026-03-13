#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int convert(string timp) {
    int ore = stoi(timp.substr(0, 2));
    int minute = stoi(timp.substr(3, 2));
    return ore * 60 + minute;
}

void createVeh(){
    ofstream veh("vehicule.txt");
    veh << "Masina B123XYZ 08:15 12:05" << endl;
    veh << "Motocicleta CJ45ABC 09:30 11:21" << endl;
    veh << "Camion IS78DEF 07:02 10:30" << endl;
    veh << "Masina TM22GHI 10:32 13:43" << endl;
    veh.close();
}

class vehicul{
    protected:
    
    string NrIn, OrInStr, OrOutStr;
    int OrIn;
    int OrOut;
    
    public:
    
    vehicul(string nr, string inStr, string outStr, int in, int out){
        NrIn=nr;
        OrInStr=inStr;
        OrOutStr=outStr;
        OrIn=in;
        OrOut=out;
    }
    
   int TimpTotal(){
    return OrOut-OrIn;
}
    virtual float tarif(){
        return 0;
    }
    
     void afiseaza(string tip){
         int diferenta = TimpTotal();
         int ore = diferenta/60;
         int minute = diferenta%60;
         cout<<"------------------------------------"<<endl;
         cout<<"Tip vehicul: "<<tip<<endl;
         cout<<"Numar: "<<NrIn<<endl;
         cout<<"Ora de intrare: "<<OrInStr<<endl;
         cout<<"Ora de iesire: "<<OrOutStr<<endl;
         cout<<"Timp parcat: "<<ore<<" ore si "<<minute<<" minute"<<endl;
         cout<<"Tarif total: "<<tarif()<<" lei"<<endl;
     }
     
     virtual ~vehicul(){}
};

class masina : public vehicul{
    private:
    
    float TarifOra = 5.0;
    
    public:
    masina(string nr, string inStr, string outStr, int in, int out) : 
    vehicul(nr, inStr, outStr, in, out){}
    
    float tarif() override{
        return (TimpTotal() / 60.0) *TarifOra;
    }
    
};

class motocicleta : public vehicul{
    private:
    
    float TarifOra = 3.0;
    
    public:
    motocicleta(string nr, string inStr, string outStr, int in, int out) : 
    vehicul(nr, inStr, outStr, in, out){}
    
    float tarif() override{
        return (TimpTotal() / 60.0) *TarifOra;
    }
    
};

class camion : public vehicul{
    private:
    
    float TarifOra = 10.0;
    
    public:
    camion(string nr, string inStr, string outStr, int in, int out) : 
    vehicul(nr, inStr, outStr, in, out){}
    
    float tarif() override{
        return (TimpTotal() / 60.0) *TarifOra;
    }
    
};

int main(){
    vector<vehicul*> v;
    createVeh();
    ifstream veh("vehicule.txt");
    if(!veh.is_open()) {
        cout<<"Eroare la deschiderea fisierului"<<endl;
        return 1;
    }
    string tip, numar, oraIn, oraOut;
    float total= 0;
    while(veh>>tip>>numar>>oraIn>>oraOut) {
        int in  = convert(oraIn);
        int out = convert(oraOut);
        if(tip== "Masina")
            v.push_back(new masina(numar, oraIn, oraOut, in, out));
        else if(tip== "Motocicleta")
            v.push_back(new motocicleta(numar, oraIn, oraOut, in, out));
        else if(tip== "Camion")
            v.push_back(new camion(numar, oraIn, oraOut, in, out));
            
        v.back()->afiseaza(tip);
        total += v.back()->tarif();
    }
    veh.close();
    cout<<"=============================="<<endl;
    cout<<"Total: "<<total<<" lei"<<endl;
    for (int i=0; i< v.size();i++) {
        delete v[i];
    }
    
    return 0;
}