#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

int convert(string timp) {
    int ore = stoi(timp.substr(0, 2));
    int minute = stoi(timp.substr(3, 2));
    return ore * 60 + minute;
}

void createVeh() {
    ofstream veh("vehicule.txt");
    veh << "Masina B123XYZ 08:15 12:05" << endl;
    veh << "Motocicleta CJ45ABC 09:30 11:21" << endl;
    veh << "Camion IS78DEF 07:02 10:30" << endl;
    veh << "Bicicleta CT11JKL 06:00 08:30" << endl;
    veh.close();
}

class IVehicul {
public:
    virtual int calculeazaTimp() const = 0;
    virtual double calculeazaTarif() const = 0;
    virtual ~IVehicul() {}
};

class Vehicul : public IVehicul {
protected:
    string NrIn, OrInStr, OrOutStr;
    int OrIn, OrOut;

public:
    Vehicul(string nr, string inStr, string outStr, int in, int out) {
        NrIn = nr;
        OrInStr = inStr;
        OrOutStr = outStr;
        OrIn = in;
        OrOut = out;
    }

    int calculeazaTimp() const override {
        return OrOut - OrIn;
    }

    double calculeazaTarif() const override {
        return 0;
    }

    void afiseaza(string tip) const {
        int diferenta = calculeazaTimp();
        int ore = diferenta / 60;
        int minute = diferenta % 60;
        int oreIncepute = ceil(diferenta / 60.0);
        cout << "------------------------------------" << endl;
        cout << "Tip vehicul:   " << tip << endl;
        cout << "Numar:         " << NrIn << endl;
        cout << "Ora intrare:   " << OrInStr << endl;
        cout << "Ora iesire:    " << OrOutStr << endl;
        cout << "Timp parcat:   " << ore << " ore si " << minute << " minute" << endl;
        cout << "Ore facturate: " << oreIncepute << " ore incepute" << endl;
        cout << "Tarif total:   " << calculeazaTarif() << " lei" << endl;
    }

    virtual ~Vehicul() {}
};

class Masina : public Vehicul {
private:
    double TarifOra = 5.0;
public:
    Masina(string nr, string inStr, string outStr, int in, int out)
        : Vehicul(nr, inStr, outStr, in, out) {}

    double calculeazaTarif() const override {
        int oreIncepute = ceil(calculeazaTimp() / 60.0);
        return oreIncepute * TarifOra;
    }
};

class Motocicleta : public Vehicul {
private:
    double TarifOra = 3.0;
public:
    Motocicleta(string nr, string inStr, string outStr, int in, int out)
        : Vehicul(nr, inStr, outStr, in, out) {}

    double calculeazaTarif() const override {
        int oreIncepute = ceil(calculeazaTimp() / 60.0);
        return oreIncepute * TarifOra;
    }
};

class Camion : public Vehicul {
private:
    double TarifOra = 10.0;
public:
    Camion(string nr, string inStr, string outStr, int in, int out)
        : Vehicul(nr, inStr, outStr, in, out) {}

    double calculeazaTarif() const override {
        int oreIncepute = ceil(calculeazaTimp() / 60.0);
        return oreIncepute * TarifOra;
    }
};

class Bicicleta : public Vehicul {
private:
    double TarifOra = 2;
public:
    Bicicleta(string nr, string inStr, string outStr, int in, int out)
        : Vehicul(nr, inStr, outStr, in, out) {}

    double calculeazaTarif() const override {
        int oreIncepute = ceil(calculeazaTimp() / 60.0);
        return oreIncepute * TarifOra;
    }
};

int main() {
    vector<Vehicul*> vehicule;
    createVeh();

    ifstream veh("vehicule.txt");
    if (!veh.is_open()) {
        cout << "Eroare la deschiderea fisierului!" << endl;
        return 1;
    }

    string tip, numar, oraIn, oraOut;
    double total = 0;

    while (veh >> tip >> numar >> oraIn >> oraOut) {
        int in  = convert(oraIn);
        int out = convert(oraOut);

        if (tip == "Masina")
            vehicule.push_back(new Masina(numar, oraIn, oraOut, in, out));
        else if (tip == "Motocicleta")
            vehicule.push_back(new Motocicleta(numar, oraIn, oraOut, in, out));
        else if (tip == "Camion")
            vehicule.push_back(new Camion(numar, oraIn, oraOut, in, out));
        else if (tip == "Bicicleta")
            vehicule.push_back(new Bicicleta(numar, oraIn, oraOut, in, out));

        vehicule.back()->afiseaza(tip);
        total += vehicule.back()->calculeazaTarif();
    }
    veh.close();

    cout << "==============================" << endl;
    cout << "Total incasat: " << total << " lei" << endl;

    for (int i = 0; i < (int)vehicule.size(); i++) {
        delete vehicule[i];
    }

    return 0;
}