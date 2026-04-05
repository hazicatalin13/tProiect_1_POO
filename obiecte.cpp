#include "memorie.h"
#include<iostream>

ArhivaManager::ArhivaManager() {
    adauga(new ObiectTextil("Ursulet de plus ros la cusaturi", 60));
    adauga(new ObiectHartie("Scrisoare de dragoste ingalbenita", 50));
    adauga(new ObiectFragil("Cana de cafea crapata", 30));
    adauga(new ArtefactLegendar("Jurnalul de bord al bunicului", 50));
    adauga(new ObiectPretios("Ceas de buzunar fara limbi", 40));
    adauga(new ObiectTextil("Paturica de bebelus descusuta", 80));
    adauga(new ObiectHartie("Harta unei insule indepartate", 90));
    adauga(new ObiectFragil("Vaza de cristal sparta in doua", 70));
    adauga(new ObiectPretios("Brosa din argint oxidat", 20));
    adauga(new ObiectTextil("Fata de masa cu gauri", 55));
    adauga(new ObiectHartie("Poza veche rupta", 45));
    adauga(new ObiectFragil("Glob de zapada fisurat", 65));
    adauga(new ObiectTextil("Manusa de lana destramata", 25));
    adauga(new ObiectPretios("Inel cu piatra slabita", 15));
    adauga(new ObiectHartie("Diploma de merit patata", 35));
    adauga(new ArtefactLegendar("Cufar vechi de zestre", 85));
    adauga(new ObiectFragil("Oglinda de mana ciobita", 40));
    adauga(new ObiectTextil("Ghiozdan vechi de piele", 75));
    adauga(new ObiectHartie("Bilet de tren de acum 50 de ani", 10));
    adauga(new ObiectPretios("Medalie de onoare zgariata", 5));
}
//textil,pretioase-ac
//hartie-scoci
//fragile,legendare-lipici