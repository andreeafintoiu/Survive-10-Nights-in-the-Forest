# Survive 10 Nights in the Forest


## Survive 10 Nights in the Forest este un joc de tip Survival RPG, inspirat din unul din cele mai populare jocuri pe platforma Roblox, "99 Nights in the Forest". 

### Scopul principal al jocului "Survive 10 Nights in the Forest" este de a-ți proteja baza, adică de a menține focul de tabără în viață. Pe parcursul fiecărei zile, numărul de puncte necesar pentru a upgrada focul de tabără se mărește, și rata de scădere crește. În cazul în care focul moare, și nivelul de lumină din bază ajunge la 0 la sfârșitul zilei, jocul se termină imediat, deoarece un cerb mutant va ataca jucătorul, ajungând instant în Game Over.

Pentru a ajunge la ziua 10, jucătorul trebuie:
- să mențină focul de tabără activ cu ajutorul materialelor (lemn, cărbune, canistră de benzină) prin acțiunea de căutare (scavenge: jucătorul primește un număr random de resurse, ce rămân în inventar de pe o zi pe alta);
- în timpul acțiunilor de căutare, jucătorul poate alege între două variante:
  - **tăierea lemnelor** lângă bază: 100% șansă de succes, cantitatea de lemn obținută depinzând de nivelul toporului: 1-2 bucăți la nivel 1, 3-4 bucăți la nivel 2 și 4-5 bucăți la nivel 3;
  - **explorarea în adâncul pădurii**: șanse mai mici de găsire a combustibilului (30% pentru cărbune, 15% pentru canistra de benzină), posibilitatea ca sesiunea să fie irosită fără a găsi nimic (șansă de 15%), dar și șansa de a declanșa un eveniment aleatoriu/random event (șansă de 40%);
- să adune materialele necesare -- lemn, blană de lup -- pentru a-și upgrada uneltele -- topor, pușcă -- pentru a supraviețui unui **event**; în timpul acțiunilor de scavenge din pădure, pot fi întâmpinate evenimente aleatorii, în care jucătorul se luptă cu lupi, iar entitatea poate dropa între 0-3 resurse;
- un **event** care poate duce la game over este atacul cultiștilor din zilele 2,4,6,8 și 10;
- în funcție de nivelul uneltelor putem avea două rezultate:
  - în cazul în care jucătorul câștigă, nivelul focului crește cu 20% (nivel_foc + [20% * nivel_foc]);
  - în cazul în care jucătorul pierde, nivelul focului scade cu 50% (nivel_foc - [50% * nivel_foc] + 1);
- ziua 2 de atac necesită unelte de nivel 1, zilele 4,6 și 8 necesită unelte de cel puțin nivelul 2, iar ziua 10 necesită unelte de nivel 3;
- în zilele 3, 6 și 9, un NPC vizitează baza jucătorului. Comerciantul de piei (Pelt Trader) poate upgrada uneltele jucătorului în funcție de un număr fix de lemn și blană de lup. Fiind în zilele 3, 6 și 9, jucătorul are șanse să învingă grupurile de cultiști care vin în baza lui;
- jucătorul este constrâns în ceea ce privește numărul de acțiuni de scavenge pe care le îndeplinește într-o zi. Aceste poate îndeplini maxim **3 acțiuni de scavenge** pe zi, și de fiecare dată acesta trebuie să decidă dacă dorește să meargă mai departe sau să se întoarcă în bază pentru a alimenta focul și a se adăposti. Cu fiecare acțiune de scavenge îndeplinită se apropie noaptea;
- încă un inamic pe care jucătorul il poate întâlni este cerbul mutant: dacă jucătorul se află în afara zonei sigure (bazei) noaptea, cerbul îl atacă, rezultând în GAME OVER. În schimb, dacă nivelul focului de tabără atinge 0, cerbul poate ataca jucătorul în orice moment al zilei, rezultând în GAME OVER.

Dacă jucătorul reușește să treacă peste ultimul atac al cultiștilor din ziua 10, acesta va primi un premiu, un item pe nume "Medalionul Supraviețuitorului" și un mesaj de victorie.

BASE GAME: [99 Nights in the Forest 🔦](https://www.roblox.com/games/79546208627805/99-Nights-in-the-Forest)

## Tema 0

#### Cerințe

- [X] Nume proiect (poate fi schimbat ulterior)
- [X] Scurtă descriere a temei alese, ce v-ați propus să implementați

## Tema 1

#### Cerințe
- [X] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi; moștenirile nu se iau în considerare aici
- [X] constructori de inițializare cu parametri pentru fiecare clasă
- [X] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor
<!-- - [ ] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [ ] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [X] `operator<<` pentru **toate** clasele pentru afișare (`std::ostream`) folosind compunere de apeluri cu `operator<<`
- [X] cât mai multe `const` (unde este cazul) și funcții `private`
- [X] implementarea a minim 3 funcții membru publice pentru funcționalități netriviale specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe
  - nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector
- [X] scenariu de utilizare **cu sens** a claselor definite:
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` DOAR exemple de date de intrare de la tastatură (dacă există) pentru a acoperi cât mai multe cazuri; dacă aveți nevoie de date din fișiere, creați alte fișiere separat
- [X] minim 52-60% din codul propriu să fie C++, adică să aveți mai mult cod decât ce e inclus în template; testele nu se pun, nu vă luați după procentajul din interfața web; detalii la ore
- [x] `.gitattributes` configurat corect (nu trebuie făcute modificări aici)
- [X] tag de `git`: de exemplu `v0.1`
- [X] serviciu de integrare continuă (CI) cu **toate bifele**; exemplu: GitHub Actions
- [ ] code review #1 2 proiecte

## Tema 2

#### Cerințe
- [ ] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [ ] moșteniri:
  - minim o clasă de bază și **3 clase derivate** din aceeași ierarhie; cele 3 derivate moștenesc aceeași clasă de bază
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [ ] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (i.e. nu simple citiri/afișări sau preluate din biblioteci i.e. draw/update/render)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
    - afișare virtuală, interfață non-virtuală
  - [ ] apelarea constructorului din clasa de bază din constructori din derivate
  - [ ] clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer de bază, eventual prin interfața non-virtuală din bază
    - [ ] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
    - [ ] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
    - [ ] smart pointers (recomandat, opțional)
- [ ] excepții
  - [ ] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice distincte
    - clasele de excepții trebuie să trateze categorii de erori distincte (exemplu de erori echivalente: citire fișiere cu diverse extensii)
  - [ ] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
  - această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
- [ ] funcții și atribute `static`
- [ ] STL
- [ ] cât mai multe `const`
- [ ] funcții *de nivel înalt*, de eliminat cât mai mulți getters/setters/funcții low-level
- [ ] minim 75-78% din codul propriu să fie C++; testele nu se pun, nu vă luați după procentajul din interfața web
- [ ] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, **pe lângă cele 3 derivate deja adăugate** din aceeași ierarhie
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou
  - noua derivată va fi integrată în codul existent (adică va fi folosită, nu adăugată doar ca să fie)
- [ ] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.2`
- [ ] code review #2 2 proiecte

## Tema 3

#### Cerințe
- [ ] 2 șabloane de proiectare (design patterns)
- [ ] o clasă șablon cu sens; minim **2 instanțieri**
  - [ ] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
- [ ] minim 80-90% din codul propriu să fie C++; testele nu se pun, nu vă luați după procentajul din interfața web
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [ ] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.3` sau `v1.0`
- [ ] code review #3 2 proiecte
