1. Descrierea Proiectului
Acest proiect este o aplicație de tip joc de gestiune și restaurare.  Utilizatorul preia rolul unui restaurator care trebuie să salveze obiecte vechi (amintiri) folosind un set limitat de resurse și gestionându-și starea mentală (Sanity). Aplicația include un sistem de progresie pe zile și o bază de date interactivă pentru obiecte.

2. Structura Claselor
-Clase Core (Nucleu)
Amintire (Abstractă): Definește obiectul de bază, stochează ID-ul unic (generat static), descrierea și gradul de distrugere.

ArhivaManager: Gestionează colecția de obiecte utilizând std::vector<Amintire*>, controlează logica zilelor de joc și resursele.

TrusaMesterului: Gestionează stocul de materiale (Ac, Scoci, Lipici).

-Ierarhia de Moștenire (3 Niveluri)
AmintireRestaurabila (derivat din Amintire): Interfață pentru obiectele care pot fi reparate.

Categorii de Bază:
ObiectTextil, ObiectHartie, ObiectSolid: Obiecte standard care necesită materiale specifice.
Categorii Speciale:
ObiectFragil: Include un factor de pedeapsă la eșec.
ObiectPretios: Oferă bonus de Sanity la restaurare.
Moștenire în Diamant (Diamond Inheritance)
ArtefactLegendar: Moștenește atât din ObiectFragil, cât și din ObiectPretios. Folosește moștenirea virtuală (virtual public) pentru a rezolva ambiguitatea bazei comune AmintireRestaurabila.

3. Implementare Tehnică
Polimorfism: Utilizarea metodelor virtual și virtual pure (ex: afiseaza(), clone()) permite tratarea uniformă a diferitelor tipuri de obiecte prin pointeri de bază.
Membri Statici: generatorID (în clasa Amintire) asigură identificatori unici pentru fiecare obiect creat.

Gestionarea Resurselor:

Encapsulare: Utilizarea modificatorilor private pentru date sensibile și protected pentru membrii partajați în ierarhie.

Destructor: Implementat în ArhivaManager pentru eliberarea memoriei alocate dinamic în vector.

Tratarea Excepțiilor: Sistem robust bazat pe o clasă de bază JocException (derivată din std::exception), cu specializări pentru resurse insuficiente, ID invalid sau Game Over.

4. Funcționalități Meniu 
Aplicația oferă un meniu interactiv:

Joaca: Pornește logica de amestecare a obiectelor (std::shuffle) și procesul de restaurare.

Listare: Afișează toate amintirile din bază.

Adauga: Permite crearea de noi obiecte (polimorfism la creare).

Modifica: Actualizarea descrierii obiectelor existente.

Sterge: Eliminarea obiectelor din arhivă.

5. Compilare și Rulare
Comandă recomandată :

Bash
g++ main.cpp arhivaMemorie.cpp -o Amintiri 
./Amintiri
