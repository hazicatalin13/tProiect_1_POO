#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <algorithm>

class JocException : public std::exception {
protected:
    std::string mesaj;
public:
    JocException(std::string m) : mesaj(m) {}
    const char* what() const noexcept override { return mesaj.c_str(); }
};

class SanityDepletedException : public JocException {
public: SanityDepletedException() : JocException("GAME OVER: Sanity s-a epuizat!") {}
};

class ResurseInsuficienteException : public JocException {
public: ResurseInsuficienteException(std::string r) : JocException("Resurse insuficiente: " + r) {}
};

class AccesInterzisException : public JocException {
public: AccesInterzisException() : JocException("Acces interzis: Doar Admin!") {}
};

class IDInvalidException : public JocException {
public: IDInvalidException() : JocException("ID invalid!") {}
};

class User {
protected:
    std::string username;
public:
    User(std::string nume) : username(nume) {}
    virtual ~User() {}
    virtual bool poateModifica() const = 0; 
    std::string getUsername() const { return username; }
};

class Player : public User {
public:
    Player(std::string nume) : User(nume) {}
    bool poateModifica() const override { return false; }
};

class Admin : public User {
public:
    Admin(std::string nume) : User(nume) {}
    bool poateModifica() const override { return true; }
};

class Amintire {
protected:
    int id;
    std::string descriere;
    int distrugere; 
    bool procesatInSesiune = false; 
    static int generatorID;
public:
    Amintire(std::string desc, int dist);
    virtual ~Amintire() {}
    virtual void afiseaza() const = 0;
    int getID() const { return id; }
    int getDist() const { return distrugere; }
    void setDist(int d) { distrugere = d; }
    void setDesc(std::string d) { descriere = d; }
    bool esteProcesat() const { return procesatInSesiune; }
    void setProcesat(bool v) { procesatInSesiune = v; }
};

class AmintireRestaurabila : virtual public Amintire {
public:
    AmintireRestaurabila(std::string d, int dist) : Amintire(d, dist) {}
    virtual std::string getMaterial() const = 0;
};

class ObiectFragil : virtual public AmintireRestaurabila {
public:
    ObiectFragil(std::string d, int dist) : Amintire(d, dist), AmintireRestaurabila(d, dist) {}
    void afiseaza() const override { std::cout << descriere << " (" << distrugere << "% distrugere)"; }
    std::string getMaterial() const override { return "lipici"; }
};

class ObiectPretios : virtual public AmintireRestaurabila {
public:
    ObiectPretios(std::string d, int dist) : Amintire(d, dist), AmintireRestaurabila(d, dist) {}
    void afiseaza() const override { std::cout << descriere << " (" << distrugere << "% distrugere)"; }
    std::string getMaterial() const override { return "ac"; }
};

class ArtefactLegendar : public ObiectFragil, public ObiectPretios {
public:
    ArtefactLegendar(std::string d, int dist) : Amintire(d, dist), AmintireRestaurabila(d, dist), ObiectFragil(d, dist), ObiectPretios(d, dist) {}
    void afiseaza() const override { std::cout << descriere << " (" << distrugere << "% distrugere)"; }
    std::string getMaterial() const override { return "lipici"; }
};

class ObiectTextil : public AmintireRestaurabila {
public:
    ObiectTextil(std::string d, int dist) : Amintire(d, dist), AmintireRestaurabila(d, dist) {}
    void afiseaza() const override { std::cout << descriere << " (" << distrugere << "% distrugere)"; }
    std::string getMaterial() const override { return "ac"; }
};

class ObiectHartie : public AmintireRestaurabila {
public:
    ObiectHartie(std::string d, int dist) : Amintire(d, dist), AmintireRestaurabila(d, dist) {}
    void afiseaza() const override { std::cout << descriere << " (" << distrugere << "% distrugere)"; }
    std::string getMaterial() const override { return "scoci"; }
};

class ArhivaManager {
    std::vector<Amintire*> colectie;
    int sanity = 250, ziua = 1;
    int rAc = 100, rScoci = 100, rLipici = 100;
public:
    ArhivaManager();
    ~ArhivaManager();
    ArhivaManager(const ArhivaManager&) = delete;          //regula celor 3
    ArhivaManager& operator=(const ArhivaManager&) = delete;
    void adauga(Amintire* a) { colectie.push_back(a); }
    void afisareBazaDate();
    void adaugareAdmin();
    void modificareAdmin();
    void stergereAdmin();
    void joacaZiua();
};

class MeniuInteractiv {
    ArhivaManager manager;
    User* utilizatorCurent;
public:
    MeniuInteractiv() : utilizatorCurent(nullptr) {}
    ~MeniuInteractiv() { delete utilizatorCurent; }
    void login();
    void ruleaza();
};
