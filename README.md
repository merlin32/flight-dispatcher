# Flight Dispatcher
### Description

Flight Dispatcher is a flight planning application inspired by SimBrief, 
the most popular online platform for creating flight plans for simulators. 
It is designed for aviation enthusiasts and flight simulator players,
offering the ability to select a departure and an arrival airport. 
The app supports automatic waypoint selection, taking weather conditions into 
account, as well as manual waypoint selection for custom routes.

Flight Dispatcher is compatible with specific aircraft types, 
including the Airbus A320Neo, Boeing 747-8F, Beechcraft King Air 350, 
and the F-16C Fighting Falcon. It can automatically calculate required fuel 
and onboard weight, while also allowing manual input for flexibility.

About SimBrief: [Official SimBrief Website](https://www.simbrief.com/home/?page=about)

### Navigating through the app

The app contains two menus: one to create a flight plan and one to 
show each created flight plan.

**Creating a new flight plan**

When creating a new flight plan, the user is asked to enter the 
following base parameters:

| Parameter | Description                                                                                                       |
|:---|:------------------------------------------------------------------------------------------------------------------|
| Callsign | Airline ICAO (or any combination of three letters) and a number                                                   |
| Departure | The ICAO code for the departing airport (e.g., LROP)                                                              |
| Arrival | The ICAO code for the arrival airport (e.g., LRCL)                                                                |
| Departing runway | The runway code (e.g., RW08L) of the departing runway                                                             |
| Arrival runway | The runway code (e.g., RW07) of the arrival runway                                                                |
| Waypoint selection (manual) | The waypoint code (e.g., BUKEL) for each selected waypoint. Mark the end of selection by typing **"end"**         |
| Aircraft type | The name of the aircraft (e.g., Airbus A320Neo)                                                                   |
| Cruise altitude | The altitude achieved after climbing (in FT)                                                                      |
| Contingency | The percentage of the block fuel (e.g., 0.2)                                                                      |
| Reserve Time | Required holding time for unexpected delays (in minutes)                                                          |
| Taxi Fuel | Quantity of fuel needed to taxi (in KG)                                                                           |
| Block Fuel | The total fuel on board (in KG)                                                                                   | 

The values for **cruise altitude**, **contingency**, **reserve time**, **taxi fuel**, and **block fuel** can be determined automatically. To select which parameter should be calculated by the app, the user must type **"auto"** instead of a value.

For each category of aircraft, the user must enter the following parameters:

- **Passenger Aircraft**

| Parameter | Description |
|-----------|---------------------------------------|
| Freight | The amount of baggage loaded (in KG) |
| Passenger | The total number of passengers |

- **Cargo Aircraft**

| Parameter | Description |
|-----------|---------------------------------------|
| Number of containers | The total number of containers to be loaded |
| Container's weight | The total weight of a container (in KG). Input needed for each container |

- **General Aviation Aircraft** (this category includes prop and 
turboprop aircraft only)

| Parameter | Description |
|-----------|---------------------------------------|
| Number of pilots | The total number of pilots (input required only for planes which permit more than one pilot) |
| Passengers | The total number of passengers |
| Baggage quantity | The total quantity of baggage (in KG) |

- **Fighter Jet**

| Parameter | Description |
|-----------------|----------------------------------------------------------------------------------------------|
| Number of pilots | The total number of pilots (input required only for planes which permit more than one pilot) |
| Number of missiles | The total number of missiles loaded on the wings |
| Missile weight | The weight of each missile loaded (in KG) |
| Cannon ammo weight | The quantity of cannon ammo loaded (in KG) |

**Available aircraft types:**
- Airbus A320Neo (passenger aircraft)
- Boeing 747-8F (cargo aircraft)
- Beechcraft King Air 350 (general aviation aircraft)
- F-16C Fighting Falcon (fighter jet aircraft)

**Available waypoints:**
- BUKEL
- MOBRA
- EDETA
- SOKRU
- AKUPO
- ULMIN
- DEGET
- BALUX
- TORNO
- NATEX
- PESAT
- POLUN
- BULEN
- RIXEN
- NALOX
- BABIT
- ETIDA

**Available airports:**
- LROP (Aeroportul International Henri Coanda)
  - Runways:
    - RW08R
    - RW08L
    - RW26L
    - RW26R
- LRCL (Aeroportul International Avram Iancu)
  - Runways:
    - RW07
    - RW25
- LOWW (Vienna International Airport)
  - Runways:
    - RW11
    - RW29
    - RW16
    - RW34
- LTFM (Istanbul Airport)
  - Runways;
    - RW16L
    - RW34R
    - RW16R
    - RW34L
    - RW17L
    - RW35R
    - RW17R
    - RW35L
    - RW18
    - RW36
### Important!

Aveți voie cu cod generat de modele de limbaj la care nu ați contribuit semnificativ doar dacă documentați riguros acest proces.
Codul generat pus "ca să fie"/pe care nu îl înțelegeți se punctează doar pentru puncte bonus, doar în contextul
în care oferă funcționalități ajutătoare și doar dacă are sens.

Codul din proiect trebuie să poată fi ușor de înțeles și de modificat de către altcineva. Pentru detalii, veniți la ore.

O cerință nu se consideră îndeplinită dacă este realizată doar prin cod generat.

- **Fără cod de umplutură/fără sens!**
- **Fără copy-paste!**
- **Fără variabile globale!**
- **Fără atribute publice!**
- **Pentru T2 și T3, fără date în cod!** Datele vor fi citite din fișier, aveți exemple destule.
- **Obligatoriu** fișiere cu date mai multe din care să citiți, obligatoriu cu biblioteci externe: fișiere (local sau server) sau baze de date
- obligatoriu (TBD) să integrați cel puțin două biblioteci externe pe lângă cele pentru stocare

### Tema 0

- [x] Nume proiect (poate fi schimbat ulterior)
- [x] Scurtă descriere a temei alese, ce v-ați propus să implementați

## Tema 1

#### Cerințe
- [x] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi; moștenirile nu se iau în considerare aici
- [x] constructori de inițializare cu parametri pentru fiecare clasă
- [x] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor
<!-- - [x] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [x] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [x] `operator<<` pentru **toate** clasele pentru afișare (`std::ostream`) folosind compunere de apeluri cu `operator<<`
- [x] cât mai multe `const` (unde este cazul) și funcții `private`
- [x] implementarea a minim 3 funcții membru publice pentru funcționalități netriviale specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe
  - nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector
- [x] scenariu de utilizare **cu sens** a claselor definite:
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` DOAR exemple de date de intrare de la tastatură (dacă există); dacă aveți nevoie de date din fișiere, creați alte fișiere separat
- [x] minim 50-55% din codul propriu să fie C++, `.gitattributes` configurat corect
- [x] tag de `git`: de exemplu `v0.1`
- [x] serviciu de integrare continuă (CI) cu **toate bifele**; exemplu: GitHub Actions
- [x] code review #1 2 proiecte

## Tema 2

#### Cerințe
- [x] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [x] moșteniri:
  - minim o clasă de bază și **3 clase derivate** din aceeași ierarhie
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [x] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (i.e. nu simple citiri/afișări sau preluate din biblioteci i.e. draw/update/render)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
    - afișare virtuală, interfață non-virtuală
  - [x] apelarea constructorului din clasa de bază din constructori din derivate
  - [x] clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer de bază, eventual prin interfața non-virtuală din bază
    - [x] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
    - [x] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
    - [x] smart pointers (recomandat, opțional)
- [x] excepții
  - [x] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice distincte
    - clasele de excepții trebuie să trateze categorii de erori distincte (exemplu de erori echivalente: citire fișiere cu diverse extensii)
  - [x] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
  - această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
- [x] funcții și atribute `static`
- [x] STL
- [x] cât mai multe `const`
- [x] funcții *de nivel înalt*, de eliminat cât mai mulți getters/setters/funcții low-level
- [x] minim 75-80% din codul propriu să fie C++
- [x] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, **pe lângă cele 3 derivate deja adăugate** din aceeași ierarhie
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou
  - noua derivată va fi integrată în codul existent (adică va fi folosită, nu adăugată doar ca să fie)
- [x] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.2`
- [ ] code review #2 2 proiecte

## Tema 3

#### Cerințe
- [x] 2 șabloane de proiectare (design patterns)
- [x] o clasă șablon cu sens; minim **2 instanțieri**
  - [x] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
- [x] minim 85% din codul propriu să fie C++
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [x] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.3` sau `v1.0`
- [ ] code review #3 2 proiecte

## Instrucțiuni de compilare

Proiectul este configurat cu CMake.

Instrucțiuni pentru terminal:

1. Pasul de configurare
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# sau ./scripts/cmake.sh configure
```

Sau pe Windows cu GCC folosind Git Bash:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
# sau ./scripts/cmake.sh configure -g Ninja
```

Pentru a configura cu ASan, avem opțiunea `-DUSE_ASAN=ON` (nu merge pe Windows cu GCC):
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DUSE_ASAN=ON
# sau ./scripts/cmake.sh configure -e "-DUSE_ASAN=ON"
```


La acest pas putem cere să generăm fișiere de proiect pentru diverse medii de lucru.


2. Pasul de compilare
```sh
cmake --build build --config Debug --parallel 6
# sau ./scripts/cmake.sh build
```

Cu opțiunea `parallel` specificăm numărul de fișiere compilate în paralel.


3. Pasul de instalare (opțional)
```sh
cmake --install build --config Debug --prefix install_dir
# sau ./scripts/cmake.sh install
```

Vezi și [`scripts/cmake.sh`](scripts/cmake.sh).

Observație: folderele `build/` și `install_dir/` sunt adăugate în fișierul `.gitignore` deoarece
conțin fișiere generate și nu ne ajută să le versionăm.


## Instrucțiuni pentru a rula executabilul

Există mai multe variante:

1. Din directorul de build (implicit `build`). Executabilul se află la locația `./build/oop` după ce a fost rulat pasul de compilare al proiectului (`./scripts/cmake.sh build` - pasul 2 de mai sus).

```sh
./build/oop
```

2. Din directorul `install_dir`. Executabilul se află la locația `./install_dir/bin/oop` după ce a fost rulat pasul de instalare (`./scripts/cmake.sh install` - pasul 3 de mai sus).

```sh
./install_dir/bin/oop
```

3. Rularea programului folosind Valgrind se poate face executând script-ul `./scripts/run_valgrind.sh` din rădăcina proiectului. Pe Windows acest script se poate rula folosind WSL (Windows Subsystem for Linux). Valgrind se poate rula în modul interactiv folosind: `RUN_INTERACTIVE=true ./scripts/run_valgrind.sh`

Implicit, nu se rulează interactiv, iar datele pentru `std::cin` sunt preluate din fișierul `tastatura.txt`.

```sh
RUN_INTERACTIVE=true ./scripts/run_valgrind.sh
# sau
./scripts/run_valgrind.sh
```

4. Pentru a rula executabilul folosind ASan, este nevoie ca la pasul de configurare (vezi mai sus) să fie activat acest sanitizer. Ar trebui să meargă pe macOS și Linux. Pentru Windows, ar merge doar cu MSVC (nerecomandat).

Comanda este aceeași ca la pasul 1 sau 2. Nu merge combinat cu Valgrind.

```sh
./build/oop
# sau
./install_dir/bin/oop
```

## External Libraries

- [nlohmann/json](https://github.com/nlohmann/json): used for parsing and managing static JSON data.
