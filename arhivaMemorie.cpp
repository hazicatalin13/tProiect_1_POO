#include "memorie.h"
#include<iostream>
#include<algorithm>

int Amintire::generatorID = 100;
Amintire::Amintire(std::string desc, int dist) : id(generatorID++), descriere(desc), distrugere(dist) {}

ArhivaManager::~ArhivaManager() { 
    for(auto a : colectie) {
        delete a; 
    }
    colectie.clear(); 
}
void ArhivaManager::afisareBazaDate() {
    std::cout << "\n--- LISTA COMPLETA (ADMIN) ---";
    for(auto a : colectie) { std::cout << "\n[" << a->getID() << "] "; a->afiseaza(); }
    std::cout << std::endl;
}

void ArhivaManager::adaugareAdmin() {
    std::cout << "Tip (1.Tex 2.Har 3.Frag 4.Pret 5.Leg): "; int t; std::cin >> t;
    std::cout << "Desc: "; std::string d; std::cin.ignore(); std::getline(std::cin, d);
    std::cout << "Dist: "; int dist; std::cin >> dist;
    if(t==1) adauga(new ObiectTextil(d, dist));
    else if(t==2) adauga(new ObiectHartie(d, dist));
    else if(t==3) adauga(new ObiectFragil(d, dist));
    else if(t==4) adauga(new ObiectPretios(d, dist));
    else if(t==5) adauga(new ArtefactLegendar(d, dist));
}

void ArhivaManager::modificareAdmin() {
    int id; std::cout << "ID: "; std::cin >> id;
    for(auto a : colectie) if(a->getID() == id) {
        std::cout << "Desc noua: "; std::string d; std::cin.ignore(); std::getline(std::cin, d);
        a->setDesc(d); return;
    }
    throw IDInvalidException();
}

void ArhivaManager::stergereAdmin() {
    int id; std::cout << "ID: "; std::cin >> id;
    auto it = std::find_if(colectie.begin(), colectie.end(), [id](Amintire* a){ return a->getID() == id; });
    if(it != colectie.end()) { delete *it; colectie.erase(it); }
    else throw IDInvalidException();
}

void ArhivaManager::joacaZiua() {
    int succesAzi = 0;
    for(auto a : colectie) a->setProcesat(false);

    while(succesAzi < 3) {
        Amintire* tinta = nullptr;
        for(auto a : colectie) if(a->getDist() > 0 && !a->esteProcesat()) { tinta = a; break; }

        if(!tinta) { 
            std::cout << "\nToate obiectele disponibile au fost incercate! Resetam...\n";
            for(auto a : colectie) a->setProcesat(false);
            continue;
        }

        std::cout << "\nZIUA " << ziua << " | " << succesAzi << "/3 REPARATE | Sanity: " << sanity << "\n";
        std::cout << "Resurse: Ac:" << rAc << "% Scoci:" << rScoci << "% Lipici:" << rLipici << "%\n";
        tinta->afiseaza();
        std::cout << "\nUnealta (1.Ac 2.Scoci 3.Lipici 4.Skip 0.Meniu): ";
        int opt; std::cin >> opt;

        if(opt == 0) return;
        if(opt == 4) { sanity -= 20; tinta->setProcesat(true); continue; }

        AmintireRestaurabila* res = dynamic_cast<AmintireRestaurabila*>(tinta);
        std::string unelte[] = {"", "ac", "scoci", "lipici"};

        try {
            if(res && opt >= 1 && opt <= 3 && unelte[opt] == res->getMaterial()) {
                int cost = res->getDist();
                if(opt == 1) { if(rAc < cost) throw ResurseInsuficienteException("Ac"); rAc -= cost; }
                else if(opt == 2) { if(rScoci < cost) throw ResurseInsuficienteException("Scoci"); rScoci -= cost; }
                else if(opt == 3) { if(rLipici < cost) throw ResurseInsuficienteException("Lipici"); rLipici -= cost; }
                
                std::cout << "Succes!\n";
                res->setDist(0); succesAzi++;
            } else {
                std::cout << "Gresit! Sanity -40.\n";
                sanity -= 40; tinta->setProcesat(true);
            }
        } catch (const ResurseInsuficienteException& e) {
            std::cout << e.what() << " | Sanity -30.\n";
            sanity -= 30; tinta->setProcesat(true);
        }
        if(sanity <= 0) throw SanityDepletedException();
    }
    std::cout << "\n--- ZI INCHEIATA ---";
    ziua++; rAc = 100; rScoci = 100; rLipici = 100;
}

void MeniuInteractiv::login() {
    std::cout << "1. Player | 2. Admin\n>: "; int t; std::cin >> t;
    std::cout << "User: "; std::string u; std::cin >> u;
    if(t == 2) {
        std::cout << "Parola: "; std::string p; std::cin >> p;
        if(p == "restaurator2024") utilizatorCurent = new Admin(u);
        else utilizatorCurent = new Player(u);
    } else utilizatorCurent = new Player(u);
}

void MeniuInteractiv::ruleaza() {
    login();
    int opt;
    while(true) {
        std::cout << "\n[" << utilizatorCurent->getUsername() << "]";
        std::cout << "\n1.Joaca";
        if(utilizatorCurent->poateModifica()) std::cout << " 2.Lista 3.Adauga 4.Modifica 5.Sterge";
        std::cout << " 0.Exit\n> "; std::cin >> opt;
        try {
            if(opt == 1) manager.joacaZiua();
            else if(opt == 2 && utilizatorCurent->poateModifica()) manager.afisareBazaDate();
            else if(opt == 3 && utilizatorCurent->poateModifica()) manager.adaugareAdmin();
            else if(opt == 4 && utilizatorCurent->poateModifica()) manager.modificareAdmin();
            else if(opt == 5 && utilizatorCurent->poateModifica()) manager.stergereAdmin();
            else if(opt == 0) break;
        } catch (const JocException& e) {
            std::cout << "\n!!! " << e.what() << " !!!\n";
            if(std::string(e.what()).find("GAME OVER") != std::string::npos) break;
        }
    }
}
