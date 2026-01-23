#include <iostream>
#include <string>

using namespace std;

class contBancar {
    private: 
    string nume;
    string iban;
    int sold;
    string valuta;
    bool activ;
    
    public:
     contBancar(){
        nume = "Necunoscut";
        iban = "N/A";
        sold = 0;
        valuta = "N/A";
        activ = false;
     }
     
     contBancar(string n, string i, int s, string v, bool g){
         nume = n;
         iban = i;
         sold = s;
         valuta = v;
         activ = g;
     }
     
     contBancar(const contBancar& c){
        nume = c.nume;
        iban = c.iban;
        sold = c.sold;
        valuta = c.valuta;
        activ = c.activ;
     }
     
     ~contBancar(){
         cout << "Operatie finalizata" << endl;
     }
     
     
    void depunere(int suma) {
         sold += suma;
     }
     
    void retragere(int suma){
        if(suma <= sold)
         sold -= suma;
        else
         cout << "Fonduri insuficiente!";
    }
    
    void gestionare(){
        if(activ == true){
            activ = false;
        } else {
            activ = true;
        }
    }
    
    void creare(){
         cout << "Introdu nume: ";
         cin.ignore();
         getline(cin, nume); 

         cout << "Introdu IBAN: ";
         cin >> iban; 
         
         cout<<"Introdu valuta: ";
         cin>>valuta;

         cout << "Introdu sold initial: ";
         cin >> sold;

         activ = true; 

    }
     
    void afisare() {
        cout << "\nNume: " << nume;
        cout << "\nIBAN: " << iban;
        cout << "\nSold: " << sold;
        cout << "\nValuta: " << valuta;
        cout << "\nStatus: " << (activ ? "Activ" : "Inactiv") << endl;
    }
     
};

    int main(){
        
        int a;
        int suma;
        
        contBancar cont1;
        contBancar cont2("Nikita Caliniuc", "MD12BANK0001", 1000, "MDL", true);
        contBancar cont3=cont2;
        
        
    do {
        cout << "\n--- MENIU ---\n";
        cout << "1. Afisare cont initial\n";
        cout << "2. Depunere bani (cont initial)\n";
        cout << "3. Retragere bani (cont initial)\n";
        cout << "4. Gestionare: Activ/Inactiv\n";
        cout << "5. Creare cont nou\n";
        cout << "0. Iesire\n";
        cout << "Alege optiunea: ";
        cin >> a;

        switch (a) {
            case 1:
                cont2.afisare();
                break;

            case 2:
                cout << "Introdu suma: ";
                cin >> suma;
                cont2.depunere(suma);
                cont2.afisare();
                break;

            case 3:
                cout << "Introdu suma: ";
                cin >> suma;
                cont2.retragere(suma);
                cont2.afisare();
                break;
                
            case 4:
                cont2.gestionare();
                cont2.afisare();
                break;
                
            case 5: 
                cont3.creare(); 
                cont3.afisare();
                break;
                
            case 0:
                cout << "Iesire din program...\n";
                break;

            default:
                cout << "Optiune invalida!\n";
        }

    } while (a != 0);
        
        return 0;
    }










































