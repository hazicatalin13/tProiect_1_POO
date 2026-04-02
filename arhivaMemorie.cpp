#include "memorie.h"

int Amintire::generatorID = 100;

Amintire::Amintire(std::string desc, float dist) : id(generatorID++), descriere(desc), procentDistrugere(dist) {}

void Amintire::afiseazaSimplu() const {
    std::cout << descriere << " (" << (int)(procentDistrugere * 100) << "% distrugere)\n";
}

ObiectFragil::ObiectFragil(std::string d, float dist, float risc) 
    : Amintire(d, dist), AmintireRestaurabila(d, dist), factorPedeapsa(risc) {}

ObiectPretios::ObiectPretios(std::string d, float dist, int bonus) 
    : Amintire(d, dist), AmintireRestaurabila(d, dist), bonusSanity(bonus) {}

ArtefactLegendar::ArtefactLegendar(std::string d, float dist, float risc, int bonus) 
    : Amintire(d, dist), AmintireRestaurabila(d, dist), ObiectFragil(d, dist, risc), ObiectPretios(d, dist, bonus) {}

void ObiectFragil::afiseaza() const { std::cout << "Fragil "; afiseazaSimplu(); }
void ObiectPretios::afiseaza() const { std::cout << "Pretios "; afiseazaSimplu(); }
void ArtefactLegendar::afiseaza() const { std::cout << "Legendar "; afiseazaSimplu(); }
void ObiectTextil::afiseaza() const { std::cout << "Textil "; afiseazaSimplu(); }
void ObiectHartie::afiseaza() const { std::cout << "Hartie "; afiseazaSimplu(); }
void ObiectSolid::afiseaza() const { std::cout << "Solid "; afiseazaSimplu(); }

Amintire* ObiectFragil::clone() const { return new ObiectFragil(*this); }
Amintire* ObiectPretios::clone() const { return new ObiectPretios(*this); }
Amintire* ArtefactLegendar::clone() const { return new ArtefactLegendar(*this); }

TrusaMesterului::TrusaMesterului() : rAc(100.0f), rScoci(100.0f), rLipici(100.0f) {}
void TrusaMesterului::reset() { rAc = 100.0f; rScoci = 100.0f; rLipici = 100.0f; }

void TrusaMesterului::afisareResurse() const {
    std::cout << "Resurse: Ac: " << (int)rAc << "% Scoci: " << (int)rScoci << "% Lipici: " << (int)rLipici << "%\n";
}

void TrusaMesterului::foloseste(std::string tip, float cantitateProcent) {
    if (tip == "ac") {
        if (rAc < cantitateProcent) throw ResurseInsuficienteException("Ac");
        rAc -= cantitateProcent;
    } else if (tip == "scoci") {
        if (rScoci < cantitateProcent) throw ResurseInsuficienteException("Scoci");
        rScoci -= cantitateProcent;
    } else if (tip == "lipici") {
        if (rLipici < cantitateProcent) throw ResurseInsuficienteException("Lipici");
        rLipici -= cantitateProcent;
    }
}

ArhivaManager::ArhivaManager() : sanity(250), ziua(1) {
    std::srand(std::time(0));
    adauga(new ObiectTextil("Ursulet de plus", 0.6f));
    adauga(new ObiectTextil("Paturica veche", 0.8f));
    adauga(new ObiectTextil("Manusa de lana", 0.4f));
    adauga(new ObiectTextil("Fata de masa", 0.5f));
    adauga(new ObiectHartie("Scrisoare veche", 0.5f));
    adauga(new ObiectHartie("Harta orasului", 0.7f));
    adauga(new ObiectHartie("Poza Polaroid", 0.2f));
    adauga(new ObiectHartie("Diploma scoala", 0.4f));
    adauga(new ObiectSolid("Rama foto", 0.4f));
    adauga(new ObiectSolid("Cana ciobita", 0.6f));
    adauga(new ObiectSolid("Figurina lemn", 0.5f));
    adauga(new ObiectSolid("Cutie metalica", 0.3f));
    adauga(new ObiectFragil("Vaza cristal", 0.5f, 2.0f));
    adauga(new ObiectFragil("Glob sticla", 0.7f, 2.5f));
    adauga(new ObiectFragil("Oglinda retro", 0.4f, 1.5f));
    adauga(new ObiectPretios("Ceas de aur", 0.2f, 40));
    adauga(new ObiectPretios("Inel argint", 0.1f, 50));
    adauga(new ObiectPretios("Brosa veche", 0.3f, 30));
    adauga(new ArtefactLegendar("Jurnal bunic", 0.5f, 2.0f, 70));
    adauga(new ArtefactLegendar("Cufar amintiri", 0.6f, 3.0f, 100));
}

ArhivaManager::~ArhivaManager() { 
    for(auto a : colectie) delete a; 
    colectie.clear();
}

void ArhivaManager::adauga(Amintire* a) { colectie.push_back(a); }

void ArhivaManager::afisareBazaDate() {
    std::cout << "\n Lista obiecte \n";
    for(auto a : colectie) { std::cout << "[" << a->getID() << "] "; a->afiseaza(); }
}

void ArhivaManager::creareObiect() {
    std::cout << "Tip (1.Tex 2.Har 3.Sol 4.Frag 5.Pret 6.Leg): "; int t; std::cin >> t;

    std::string d; std::cout << "Descriere: "; std::cin.ignore(); std::getline(std::cin, d);

    float dist; std::cout << "Distrugere (0.1-1.0): "; std::cin >> dist;
    if(t==1) adauga(new ObiectTextil(d, dist));
    else if(t==2) adauga(new ObiectHartie(d, dist));
    else if(t==3) adauga(new ObiectSolid(d, dist));
    else if(t==4) { float r; std::cout<<"Risc: "; std::cin>>r; adauga(new ObiectFragil(d, dist, r)); }
    else if(t==5) { int b; std::cout<<"Bonus: "; std::cin>>b; adauga(new ObiectPretios(d, dist, b)); }
    else if(t==6) { float r; int b; std::cout<<"Risc & Bonus: "; std::cin>>r>>b; adauga(new ArtefactLegendar(d, dist, r, b)); }
}

void ArhivaManager::modificareObiect() {
    int id; std::cout << "ID obiect: "; std::cin >> id;
    for(auto a : colectie) if(a->getID() == id) { 
        std::string d; std::cout << "Descriere noua: "; std::cin.ignore(); std::getline(std::cin, d);
        a->setDescriere(d); return; 
    }
    throw IDInvalidException();
}

void ArhivaManager::stergereObiect() {
    int id; std::cout << "ID obiect: "; std::cin >> id;
    auto it = std::find_if(colectie.begin(), colectie.end(), [id](Amintire* a){ return a->getID() == id; });
    if(it != colectie.end()) { delete *it; colectie.erase(it); }
    else throw IDInvalidException();
}

void ArhivaManager::joacaZiua() {
    int reparateSuccesAzi = 0;
    
    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };
    std::shuffle(colectie.begin(), colectie.end(), rng);

    while(reparateSuccesAzi < 5) {
        Amintire* curent = nullptr;
        for(auto a : colectie) if(a->getProcentDistrugere() > 0) { curent = a; break; }

        if(!curent) break;

        std::cout << "\n Sanity: " << sanity << "/250 Reparate: " << reparateSuccesAzi << "/5\n";
        trusa.afisareResurse();
        curent->afiseazaSimplu();
        std::cout << "Unealta: 1.Ac 2.Scoci 3.Lipici 4.Skip 0.Meniu: ";
        int opt; std::cin >> opt;

        if(opt == 0) return;
        if(opt == 4) { sanity -= 20; continue; }

        AmintireRestaurabila* res = dynamic_cast<AmintireRestaurabila*>(curent);
        std::string unelte[] = {"", "ac", "scoci", "lipici"};

        if(res && opt <= 3 && res->getMaterialNecesar() == unelte[opt]) {
            try {
                trusa.foloseste(unelte[opt], res->getProcentDistrugere() * 100.0f);
                res->setDistrugere(0);
                reparateSuccesAzi++;
            } catch (const JocException& e) {
                std::cout << e.what() << "\n";
                sanity -= 30;
            }
        } else {
            sanity -= 40;
        }
        if(sanity <= 0) throw SanityDepletedException();
    }
    ziua++; trusa.reset();
}

void MeniuInteractiv::ruleaza() {
    int opt;
    while(true) {
        std::cout << "\n 1.Joaca 2.Lista 3.Aaduga 4.Modifica 5.Sterge 0.Exit \n> ";
        if(!(std::cin >> opt)) break;
        try {
            switch(opt) {
                case 1: manager.joacaZiua(); break;
                case 2: manager.afisareBazaDate(); break;
                case 3: manager.creareObiect(); break;
                case 4: manager.modificareObiect(); break;
                case 5: manager.stergereObiect(); break;
                case 0: return;
            }
        } catch (const std::exception& e) {
            std::cout << "\n!!! " << e.what() << " !!!\n";
            if(manager.getSanity() <= 0) break;
        }
    }
}