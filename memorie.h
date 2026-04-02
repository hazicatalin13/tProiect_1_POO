#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <algorithm>
#include <random>
#include <ctime>


//exceptii

class JocException : public std::exception {
protected: std::string mesaj;
public: 
    JocException(std::string m) : mesaj(m) {}
    const char* what() const noexcept override { return mesaj.c_str(); }
};

class SanityDepletedException : public JocException { 
public: SanityDepletedException() : JocException("GAME OVER: Sanity 0!") {} 
};

class ResurseInsuficienteException : public JocException { 
public: ResurseInsuficienteException(std::string r) : JocException("Eroare: Nu mai ai destul(a) " + r + " pentru aceasta reparatie!") {} 
};

class IDInvalidException : public JocException { 
public: IDInvalidException() : JocException("Eroare: ID invalid!") {} 
};



class Amintire {
protected:
    int id; 
    std::string descriere; 
    float procentDistrugere; 
    static int generatorID;
public:
    Amintire(std::string desc, float dist);
    virtual ~Amintire() {} 
    virtual void afiseaza() const = 0; 
    virtual void afiseazaSimplu() const; 
    virtual Amintire* clone() const = 0; 
    virtual std::string getTip() const = 0;
    
    int getID() const { return id; }
    void setDescriere(std::string d) { descriere = d; }
    void setDistrugere(float d) { procentDistrugere = d; }
    float getProcentDistrugere() const { return procentDistrugere; }
};


class AmintireRestaurabila : virtual public Amintire {
public:
    AmintireRestaurabila(std::string d, float dist) : Amintire(d, dist) {}
    virtual std::string getMaterialNecesar() const = 0;
};


class ObiectFragil : virtual public AmintireRestaurabila {
protected: float factorPedeapsa; 
public:
    ObiectFragil(std::string d, float dist, float risc);
    void afiseaza() const override;
    Amintire* clone() const override;
    std::string getTip() const override { return "FRAGIL"; }
    std::string getMaterialNecesar() const override { return "lipici"; }
    float getPedeapsa() const { return factorPedeapsa; }
};


class ObiectPretios : virtual public AmintireRestaurabila {
protected: int bonusSanity;
public:
    ObiectPretios(std::string d, float dist, int bonus);
    void afiseaza() const override;
    Amintire* clone() const override;
    std::string getTip() const override { return "PRETIOS"; }
    std::string getMaterialNecesar() const override { return "ac"; }
    int getBonus() const { return bonusSanity; }
};

//diamant

class ArtefactLegendar : public ObiectFragil, public ObiectPretios {
public:
    ArtefactLegendar(std::string d, float dist, float risc, int bonus);
    void afiseaza() const override;
    Amintire* clone() const override;
    std::string getTip() const override { return "LEGENDAR"; }
    std::string getMaterialNecesar() const override { return "lipici"; }
};

class ObiectTextil : public AmintireRestaurabila {
public:
    ObiectTextil(std::string d, float dist) : Amintire(d, dist), AmintireRestaurabila(d, dist) {}
    void afiseaza() const override;
    Amintire* clone() const override { return new ObiectTextil(*this); }
    std::string getTip() const override { return "TEXTIL"; }
    std::string getMaterialNecesar() const override { return "ac"; }
};

class ObiectHartie : public AmintireRestaurabila {
public:
    ObiectHartie(std::string d, float dist) : Amintire(d, dist), AmintireRestaurabila(d, dist) {}
    void afiseaza() const override;
    Amintire* clone() const override { return new ObiectHartie(*this); }
    std::string getTip() const override { return "HARTIE"; }
    std::string getMaterialNecesar() const override { return "scoci"; }
};

class ObiectSolid : public AmintireRestaurabila {
public:
    ObiectSolid(std::string d, float dist) : Amintire(d, dist), AmintireRestaurabila(d, dist) {}
    void afiseaza() const override;
    Amintire* clone() const override { return new ObiectSolid(*this); }
    std::string getTip() const override { return "SOLID"; }
    std::string getMaterialNecesar() const override { return "lipici"; }
};

class TrusaMesterului {
    float rAc, rScoci, rLipici;
public:
    TrusaMesterului();
    void reset();
    void foloseste(std::string tip, float cantitateProcent);
    void afisareResurse() const;
};



class ArhivaManager {
    std::vector<Amintire*> colectie;
    int sanity, ziua;
    TrusaMesterului trusa;
public:
    ArhivaManager();
    ~ArhivaManager();
    void adauga(Amintire* a);
    void afisareBazaDate();
    void creareObiect();
    void modificareObiect();
    void stergereObiect();
    void joacaZiua();
    int getSanity() const { return sanity; }
};


class MeniuInteractiv {
    ArhivaManager manager;
public:
    void ruleaza();
};
