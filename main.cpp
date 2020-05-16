#include <bits/stdc++.h>

using namespace std;

class PizzaInexistenta: public exception {
public:
    PizzaInexistenta () noexcept {}
    PizzaInexistenta (const PizzaInexistenta&) noexcept = default;
    PizzaInexistenta& operator= (const PizzaInexistenta&) noexcept = default;
    virtual ~PizzaInexistenta() noexcept = default;
    virtual const char* what() const noexcept {
        return "Pizza introdusa nu exista in meniu\n";
    }
};

class PizzaExistenta: public exception {
public:
    PizzaExistenta () noexcept {}
    PizzaExistenta (const PizzaExistenta&) noexcept = default;
    PizzaExistenta& operator= (const PizzaExistenta&) noexcept = default;
    virtual ~PizzaExistenta() noexcept = default;
    virtual const char* what() const noexcept {
        return "Pizza introdusa exista deja in meniu\n";
    }
};

class Ingredient {
    string nume;
    int cantitate;
    int pret;
public:
    ///constructorii
    Ingredient();
    Ingredient(string, int, int);

    ///copy-constructorul
    Ingredient(const Ingredient&);

    ///destructorul
    virtual ~Ingredient();

    ///operatirul =
    Ingredient& operator =(const Ingredient&);

    ///citire/scriere
    friend istream& operator >>(istream&, Ingredient&);
    friend ostream& operator <<(ostream&, Ingredient&);

    ///get si set
    int getPret() const;
    void setPret(int);
    int getCant() const;
    void setCant(int);
    string getNume() const;
    void setNume(string);
};

Ingredient::Ingredient(): nume(""), cantitate(0), pret(0){
}

Ingredient::Ingredient(string nume, int cantitate, int pret): nume(nume), cantitate(cantitate), pret(pret) {
}

Ingredient::Ingredient(const Ingredient &other) {
    nume = other.nume;
    cantitate = other.cantitate;
    pret = other.pret;
}

Ingredient& Ingredient::operator =(const Ingredient &other) {
    nume = other.nume;
    cantitate = other.cantitate;
    pret = other.pret;
    return *this;
}

Ingredient::~Ingredient() {
    nume = "";
    cantitate = 0;
    pret = 0;
}

int Ingredient::getPret() const { return pret; }
void Ingredient::setPret(int pret) { this -> pret = pret; }
int Ingredient::getCant() const { return cantitate; }
void Ingredient::setCant(int cant) { this -> cantitate = cant; }
string Ingredient::getNume() const { return nume; }
void Ingredient::setNume(string nume) { this -> nume = nume; }

istream& operator >>(istream &f, Ingredient &ing) {
    string nume;
    int pret, cantitate;

    cout << "Introduceti numele, cantitatea si pretul:\n";
    f >> nume >> cantitate >> pret;

    ing.nume = nume;
    ing.cantitate = cantitate;
    ing.pret = pret;

    return f;
}
ostream& operator <<(ostream &g, Ingredient &ing) {
    g << ing.nume << " ";
    return g;
}

class Produs {
protected:
    string nume;
    vector <Ingredient> ing;
public:
    ///constructorii
    Produs();
    Produs(string, vector <Ingredient>);

    ///destructorul
    virtual ~Produs();

    ///copy-constructorul
    Produs(const Produs&);

    ///operatorul =
    Produs& operator =(const Produs&);

    ///medoda virtuala pura care calculeaza pretul
    virtual int calculeazaPret() const = 0;
    virtual void afisare(ostream&);

    ///get si set
    string getNume() const;
    void setNume(string);
    vector <Ingredient> getIng() const;
    void setIng(vector <Ingredient>);
};

Produs::Produs() {
}

Produs::Produs(string nume, vector <Ingredient> ing): nume(nume), ing(ing) {
}

Produs::~Produs() {
    ing.clear();
    ing.shrink_to_fit();
}

Produs::Produs(const Produs &other) {
    nume = other.nume;
    ing = other.ing;
}

Produs& Produs::operator =(const Produs &other) {
    nume = other.nume;
    ing = other.ing;
    return *this;
}

string Produs::getNume() const { return nume; }
void Produs::setNume(string nume) { this -> nume = nume; }
vector <Ingredient> Produs::getIng() const { return ing; }
void Produs::setIng(vector <Ingredient> ing) { this -> ing = ing; }

void Produs::afisare(ostream &g) {
    g << "Numele produsului este: " << nume << '\n';
    g << "Ingredientele sunt: ";
    for (auto it: ing) {
        g << it << " ";
    }

    g << '\n';
}

ostream& operator <<(ostream &g, Produs &p) {
    Produs *pp = &p;
    pp -> afisare(g);
    return g;
}

class Pizza: public Produs {
protected:
    static const int manopera = 10;
    bool vegetariana;
public:
    ///constructorii
    Pizza();
    Pizza(string, vector <Ingredient> ing, bool);

    ///copy-constructorul
    Pizza(const Pizza&);

    ///destructorul
    virtual ~Pizza();

    ///operatrul >, =
    bool operator <(const Pizza&) const;
    Pizza& operator =(const Pizza&);

    ///metoda care calculeaza pretul
    virtual int calculeazaPret() const;
    virtual void afisare(ostream&);

    ///get si set
    void setVeg(bool);
    bool getVeg() const;

    ///citire / scriere
    friend istream& operator >>(istream&, Pizza&);
};

Pizza::Pizza() {
}

Pizza::Pizza(string nume, vector <Ingredient> v, bool veg): Produs(nume, v), vegetariana(veg) {
}

Pizza::Pizza(const Pizza &other): Produs(other), vegetariana(other.vegetariana){
}

Pizza& Pizza::operator =(const Pizza &other) {
    this -> Produs::operator=(other);
    this -> vegetariana = other.vegetariana;
    return *this;
}

Pizza::~Pizza() {
    vegetariana = false;
}

bool Pizza::operator <(const Pizza &other) const {
    if (this -> calculeazaPret() < other.calculeazaPret()) return true;
    return false;
}

int Pizza::calculeazaPret() const {
    int ans = 0;
    for (auto it: ing) {
        ans += it.getPret() * it.getCant();
    }

    ans = ans + Pizza::manopera;
    return ans;
}

void Pizza::afisare(ostream &g) {
    this -> Produs::afisare(g);
    if (vegetariana == true) g << "Pizza este vegetariana!\n";
    else g << "Pizza nu este vegetariana!\n";
}

void Pizza::setVeg(bool veg) { vegetariana = veg; }
bool Pizza::getVeg() const { return vegetariana; }

istream& operator >>(istream &f, Pizza &p) {
    cout << "Intruduceti numele produsului:\n";
    string nume; f >> nume;
    p.setNume(nume);

    cout << "Introduceti daca e sau nu vegetariana(0 - nu e, 1 - e):\n";
    bool veg; f >> veg;
    p.setVeg(veg);

    cout << "Introduceti numarul de ingrediente:\n";
    int n; f >> n;
    vector <Ingredient> v;
    for (int i = 1; i <= n; ++ i) {
        Ingredient aux;
        f >> aux;
        v.push_back(aux);
    }

    p.setIng(v);
    return f;
}

class PizzaOnline: public Pizza {
    int distantaLivrare;
public:
    ///constructorii
    PizzaOnline();
    PizzaOnline(string, vector <Ingredient>, bool, int);

    ///copy-constructorul
    PizzaOnline(const PizzaOnline&);

    ///destructorul
    ~PizzaOnline();

    ///operatorul =
    PizzaOnline& operator =(const PizzaOnline&);

    ///metoda de calcul al pretului
    virtual int calculeazaPret() const;
    void afisare(ostream&);

    ///citire
    friend istream& operator >>(istream&, PizzaOnline&);

    ///get si set
    int getDist();
    void setDist(int);
};

PizzaOnline::PizzaOnline() {
}

PizzaOnline::PizzaOnline(string nume, vector <Ingredient> ing, bool veg, int dist): Pizza(nume, ing, veg), distantaLivrare(dist) {
}

PizzaOnline::PizzaOnline(const PizzaOnline &other): Pizza(other), distantaLivrare(other.distantaLivrare) {
}

PizzaOnline& PizzaOnline::operator =(const PizzaOnline &other) {
    this -> Pizza::operator=(other);
    this -> distantaLivrare = other.distantaLivrare;
    return *this;
}

PizzaOnline::~PizzaOnline() {
}

int PizzaOnline::calculeazaPret() const {
    int ans = this -> Pizza::calculeazaPret();
    ans = ans + ans * (distantaLivrare / 10) / 20;
    return ans;
}

void PizzaOnline::afisare(ostream &g) {
    this -> Pizza::afisare(g);
    g << "Distanta de livrare este de: " << distantaLivrare << "km!\n";
}

int PizzaOnline::getDist() { return distantaLivrare; }
void PizzaOnline::setDist(int dist) { distantaLivrare = dist; }

istream& operator >>(istream& f, PizzaOnline &p) {
    Pizza pizza; f >> pizza;
    cout << "Introduceti distanta pana la destinatie:\n";
    int dist; f >> dist;

    p.nume = pizza.getNume();
    p.ing = pizza.getIng();
    p.vegetariana = pizza.getVeg();
    p.distantaLivrare = dist;

    return f;
}

template <class T>
class Meniu {
    vector <T> prod;
    static int idx;
    int valoareIncasata;
public:
    ///constructorii
    Meniu(): valoareIncasata(0) {
    }

    Meniu(vector <T> prod, int val): prod(prod), valoareIncasata(val){
    }

    ///copy-constructorul
    Meniu(const Meniu &other) {
        prod = other.prod;
        valoareIncasata = other.valoareIncasata;
    }

    ///destructorul
    virtual ~Meniu() {
        prod.clear();
        prod.shrink_to_fit();
    }

    ///operatorul +=, =
    void operator +=(const T &x) {
        prod.push_back (x);
        idx = idx + 1;
    }

    Meniu& operator =(const Meniu &other) {
        prod = other.prod;
        valoareIncasata = other.valoareIncasata;
        return *this;
    }

    ///verifica daca un produs de tip T exista deja
    bool check(string nume) {
        for (auto it: prod) {
            if (it.getNume() == nume) return true;
        }

        return false;
    }

    ///returneaza pretul produsului de pe pozitia pos
    int getPret(int pos) {
        T p = prod[pos];
        return p.calculeazaPret();
    }

    ///vinde produsul de la pozitia pos
    void vinde(const int pos) {
        T p = prod[pos - 1];
        valoareIncasata = valoareIncasata + p.calculeazaPret();
        cout << "Costul este de: " << p.calculeazaPret() << " lei.\n";
    }

    static int getIdx() {
        return idx;
    }

    int getIncasari() {
        return valoareIncasata;
    }

    ///citire / scriere
    template <class TT> friend istream& operator >>(istream &f, Meniu<TT> &m) {
        int n; cin >> n;
        for (int i = 1; i <= n; ++ i) {
            T aux; cin >> aux;
            m += aux;
        }

        int x; cin >> x;
        m.valoareIncasata = x;
        return f;
    }

    template <class TT> friend ostream& operator <<(ostream &g, Meniu<TT> &m) {
        g << "Numarul de produse este:" << m.idx << '\n';
        int idx =  0;
        for (auto it: m.prod) {
            g << ++idx << "." << it << '\n';
        }

        return g;
    }
};

template <> class Meniu <PizzaOnline> {
    vector <PizzaOnline> prod;
    static int idx;
    int valoareIncasata;
    int valoareVegetariene;
public:
    ///constructorii
    Meniu(): valoareIncasata(0), valoareVegetariene(0) {
    }

    Meniu(vector <PizzaOnline> v, int val, int valVeg): prod(v), valoareIncasata(val), valoareVegetariene(valVeg) {
    }

    ///copy-constructorul
    Meniu(const Meniu &other) {
        prod = other.prod;
        valoareIncasata = other.valoareIncasata;
        valoareVegetariene = other.valoareVegetariene;
    }

    ///destructorul
    ~Meniu() {
        prod.clear();
        prod.shrink_to_fit();
    }

    ///opertatorii =, +=
    Meniu& operator =(const Meniu &other) {
        prod = other.prod;
        valoareIncasata = other.valoareIncasata;
        valoareVegetariene = other.valoareVegetariene;
        return *this;
    }

    void operator +=(const PizzaOnline &x) {
        prod.push_back(x);
        idx = idx + 1;
    }

    ///returneaza pretul prodului p
    int getPret(int idx) {
        PizzaOnline p = prod[idx];
        return p.calculeazaPret();
    }

    ///verifica daca pizza vegetariana p exista deja in meniu
    bool check (string nume) {
        for (auto it: prod) {
            if (it.getNume() == nume) return true;
        }
        return false;
    }

    ///vinde produsul de pe pozitia pos
    void vinde(const int pos) {
        PizzaOnline p = prod[pos - 1];
        valoareIncasata = valoareIncasata + p.calculeazaPret();
        if (p.getVeg() == true) valoareVegetariene = valoareVegetariene + p.calculeazaPret();
        cout << "Costul este de: " << p.calculeazaPret() << " lei.\n";
    }

    static int getIdx() {
        return idx;
    }

    int getIncasari() {
        return valoareIncasata;
    }

    int getIncasariVeg() {
        return valoareVegetariene;
    }

    ///citire/scriere
    friend istream& operator >>(istream &f, Meniu<PizzaOnline> &m) {
        int n; cin >> n;
        for (int i = 1; i <= n; ++ i) {
            PizzaOnline aux; cin >> aux;
            m += aux;
        }

        int x; cin >> x;
        m.valoareIncasata = x;

        cin >> x;
        m.valoareVegetariene = x;
        return f;
    }
    friend ostream& operator <<(ostream &g, Meniu<PizzaOnline> &m) {
        g << "Numarul de produse din meniu este: " << m.idx << '\n';
        int idx = 0;
        for (auto it: m.prod) {
            g << ++idx << "." << it << '\n';
        }

        return g;
    }
};

template <> int Meniu <Pizza>::idx = 0;
int Meniu <PizzaOnline>::idx = 0;

void afiseazaMeniu() {
    cout << "MENIU:\n";
    cout << "-2.Adauga in map.\n";
    cout << "-1.Scoate din map.\n";
    cout << "0.Verifica daca un element e in map.\n";
    cout << "1.Afiseaza meniul.\n";
    cout << "2.Adauga o pizza in meniu.\n";
    cout << "3.Comanda o pizza.\n";
    cout << "4.Afiseaza incasari.\n";
    cout << "5.Exit.\n";
}


int main() {
    map <int, vector <Ingredient> > mp;

    Meniu<Pizza> meniuPizza;
    Meniu<PizzaOnline> meniuPizzaOnline;

    while (true) {
        afiseazaMeniu();

        int type; cin >> type;
        if (type == -2) {
            cout << "Introduceti id-ul pizzei:\n";
            int id; cin >> id;
            if (mp.find(id) != mp.end()) {
                cout << "Exista deja o pizza cu aces id!\n";
                continue;
            }

            Pizza p; cin >> p;
            mp[id] = p.getIng();
        } else if (type == -1) {
            cout << "Introduceti id-ul pizzei:\n";
            int id; cin >> id;
            if (mp.find(id) == mp.end()) {
                cout << "Nu exista o pizza cu acest id in map!\n";
                continue;
            }
            mp.erase(id);
        } else if (type == 0) {
            cout << "Introduceti id-ul pizzei:\n";
            int id; cin >> id;
            if (mp.find(id) == mp.end()) cout << "Nu exista o pizza cu acest id!\n";
            else {
                cout << "Ingredientele sunt: ";
                vector <Ingredient> v = mp[id];
                for (auto it: v) {
                    cout << it << " ";
                }
                cout << '\n';
            }
        } else if (type == 1) {
            cout << "Ce fel de meniu doriti sa se afiseze? (1 - meniu pizza, 2 - meniu pizza online)\n";
            int type; cin >> type;
            if (type == 1) cout << meniuPizza << '\n';
            else cout << meniuPizzaOnline << '\n';
        } else if (type == 2) {
            cout << "In ce meniu vreti sa introduceti produsul? (1 - meniu pizza, 2 - meniu pizza online)\n";
            int type; cin >> type;
            if (type == 1) {
                try {
                    Pizza p; cin >> p;
                    if (meniuPizza.check(p.getNume())) throw (PizzaExistenta());
                    meniuPizza += p;
                } catch (exception &e) {
                    cout << e.what() << '\n';
                }
            } else {
                try {
                    PizzaOnline p; cin >> p;
                    if (meniuPizzaOnline.check(p.getNume())) throw (PizzaExistenta());
                    meniuPizzaOnline += p;
                } catch (exception &e) {
                    cout << e.what() << '\n';
                }
            }
        }

        else if (type == 3) {
            cout << "Introdu tipul de comanda(1 - Comanda din meniu online, 2 - Comanda din meniu)\n";
            int type; cin >> type;
            cout << "Introduceti indexul produsului:\n";
            int idx; cin >> idx;

            if (type == 2) {
                try {
                    if (idx < 1 || idx > meniuPizza.getIdx()) throw (PizzaInexistenta());
                    meniuPizza.vinde(idx);
                } catch (exception &e) {
                    cout << e.what() << '\n';
                }
            } else {
                try {
                    if (idx < 1 || idx > meniuPizzaOnline.getIdx()) throw (PizzaInexistenta());
                    meniuPizzaOnline.vinde(idx);
                } catch (exception &e) {
                    cout << e.what() << '\n';
                }
            }
        } else if (type == 4) {
            cout << "Pentru ce meniu sa se afiseze incasarile: (1 - meniu, 2 - meniu online)?\n";
            int type; cin >> type;
            if (type == 1) cout << "Incasarile sunt de: " << meniuPizza.getIncasari() << " lei.\n";
            else {
                cout << "Incasarile sunt de: " << meniuPizzaOnline.getIncasari() << " lei.\n";
                cout << "Incasarile pentru pizzele vegetariene sunt de " << meniuPizzaOnline.getIncasariVeg() << " lei.\n";
            }
        } else if (type == 5) {
            break;
        } else {
            cout << "Comanda introdusa nu este valida!\n";
        }
    }

    return 0;
}
