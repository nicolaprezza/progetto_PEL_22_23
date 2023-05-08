
# Progetto Programmazione e laboratorio A.A. 2022/2023



Lo scopo del progetto è scrivere un parser (tramite grammatiche context-free) di file in formato json. Il contenuto del file deve essere salvato in un container C++ che permetta l’accesso (tramite iteratori e overloading di operatori) del contenuto letto dal file json.

Nelle due sezioni seguenti vengono introdotti il formato json e la descrizione del container da realizzare. 


**Nota**: se trovate imprecisioni/errori o volete un chiarimento su parti di questo documento o di json.hpp, aprite una GitHub issue (pulsante "issues" in alto) citando la linea del file in questione (se il commento riguarda una linea particolare del codice o di questo README). Per citare una particolare linea di README.md, aprite il file (cliccando su README.md in alto), rendete visibili le linee (pulsante `<>` "display the source blob"), selezionate i numeri di linea interessati -> cliccate i tre puntini -> "copy permalink". A questo punto, potete incollare il link copiato nella issue. Analogo per json.hpp (in questo caso i numeri di linea sono immediatamente visibili).

## 1. Formato json

Si vuole scrivere un parser per una variante _semplificata_ di json – un formato testuale per lo scambio di informazione sul Web. **Importante**: usate la descrizione json fornita di seguito e non quella trovata in rete.

Un file json contiene dati in una struttura ad albero (ricorsiva), simile al formato XML. A differenza di XML, il formato json ammette sia **liste** di valori che **dizionari** (definiti nel dettaglio qui sotto). Globalmente, un file json è una lista, un dizionario, un numero (double), un booleano, una stringa, oppure null.

### Liste

Una lista è una sequenza di valori eterogenei separati da virgola e racchiusa tra due parentesi quadre. I valori contenuti nella lista possono essere di **sei** tipi: una lista (ricorsione), un dizionario (definito sotto), una stringa racchiusa tra doppi apici, un valore di tipo double, bool (true/false), oppure null (che sta ad indicare l’assenza di un valore).

Il seguente è un esempio di un semplice file json di tipo lista (ossia, l’intero file è una lista), contenente due stringhe, un valore di tipo double (34.5), seguito da un valore di tipo bool (true), seguito da null, seguito da una lista.


    [
        "prima stringa",
        "seconda stringa",
        34.5,
        true,
        null, 
        [1,2,false,43]
    ]


**Nota.** I separatori (newline, tab, spazi) vanno ignorati. L’unica eccezione sono i separatori racchiusi tra doppi apici  (per esempio, lo spazio in "prima stringa"): in questo caso, i separatori devono fare parte della stringa estratta dal file. 


### Una nota importante sulle stringhe 

Tutti i caratteri tra le doppie virgolette vanno estratti tali e quali. Tenete presente che le stringhe possono contenere il carattere `"` preceduto da un carattere di `\`, i.e., la stringa potrebbe contenere la sotto stringa `\"`. In questo caso, quindi, la stringa **non** termina con quella occorrenza di `"`. Le stringhe terminano solo quando il carattere `"` **non** è preceduto da `\`.

**Nota bene**: Fate attenzione a seguire questa regola!

Sotto riportiamo alcuni esempi.

Per esempio, considerate il seguente file json: 

    [
        "una stringa con \n virgolette \"escaped\"",
        "seconda stringa senza escape",
        "terza stringa con altri\" escape",
        "doppio \\" escape",
    ]

Nell’esempio sopra, le quattro stringhe da estrarre dal file (ossia, i caratteri da inserire nelle `std::string` che andrete a costruire) sono, rispettivamente: 

	una stringa con \n virgolette \"escaped\"
	seconda stringa senza escape
	terza stringa con altri\" escape
	doppio \\" escape

**Nota**: I caratteri speciali `\n` (e simili, tipo `\t`, `\r`, etc.) non fanno eccezione! Se il file json contiene una stringa in cui compare `\n`, ad esempio, vanno estratti **due** caratteri: backslash (`\`) seguito dal carattere `n`, **non** va estratto il singolo carattere `\n` (che significa newline). Questa è una modifica rispetto al formato originale che abbiamo introdotto per semplificare la scrittura del parser.

### Dizionari 

Un dizionario è un insieme (una lista) di coppie

**chiave : valore**

separate da virgola e racchiuse da due parentesi graffe. Notare che chiave e valore sono separate da un carattere ‘:’ (due punti). Le chiavi possono essere solo stringhe racchiuse tra doppi apici (di nuovo, queste stringhe possono contenere caratteri escape ‘\\’). I valori possono essere, come sopra, una lista, un dizionario, una stringa racchiusa tra doppi apici (possibilmente con caratteri escape ‘\\’), un valore double o bool, oppure null.

Per esempio, il seguente file json è di tipo dizionario.

    {
        "prima chiave" : 5,
        "seconda chiave" : [4.12,2,true],
        "terza chiave" : "una stringa",
        "quarta chiave" : {"a" : 4, "b" : [4,5]}
    }

Nell’esempio qui sopra, il dizionario contiene quattro coppie **chiave : valore**   :

1. Nella prima, la chiave è la stringa **prima chiave** e il valore è l’intero **5**
2. Nella seconda, la chiave è la stringa **seconda chiave** e il valore è la lista  **\[4.12,2,true]**
3. Nella terza, la chiave è la stringa **terza chiave** e il valore è la stringa **una stringa**
4. Nella quarta, la chiave è la stringa **quarta chiave** e il valore è di nuovo (ricorsivamente) un dizionario: **{"a" : 4, "b" : \[4,5]}**

Notate bene la struttura ricorsiva del formato json: la vostra grammatica deve ammettere annidamenti arbitrari di dizionari e liste. 

### Esempi e dataset su cui testare il parser

Potete usare il seguente database di file json per testare il vostro codice: 

<https://github.com/jdorfman/awesome-json-datasets>.

Può tornarvi utile visualizzare un file json in formato ad albero. Per questo, potete usare uno dei tanti visualizzatori json online, ad esempio il seguente:

<https://jsonviewer.stack.hu/>.

**Nota.** Il visualizzatore sopra racchiude le stringhe tra doppi apici. Il vostro parser invece non deve estrarre i doppi apici che racchiudono le stringhe (vedi esempi sopra). 

  


## 2. Container

Lo scopo del progetto è scrivere un container

    class json;

che permetta di immagazzinare tutte le informazioni contenute in un file json. Il parser json realizzato verrà usato per estrarre dati da un file json e costruire un oggetto di tipo `json`. Qui sotto trovate una descrizione della dichiarazione della classe json.hpp che trovate in questo repository GitHub.

La classe json deve essere definita in modo ricorsivo, come segue. Un oggetto di tipo `json` contiene un’unica variabile privata

    impl* pimpl;

Dove `json::impl` è una struct (privata) che siete liberi di definire (come visto a lezione del modulo 1: pattern Pimpl). Nel decidere che variabili e metodi definire dentro `json::impl`, tenete conto che ogni istanza di `json` può essere una di queste sei cose:

1. null,
2. un numero,
3. un booleano, 
4. una stringa, 
5. una lista (di json), oppure
6. un dizionario (insieme di coppie &lt;stringa, json>).

Una buona idea potrebbe quindi essere quella di definire, dentro `json::impl`, una variabile double, una variabile `bool`, una variabile `std::string`, una lista di `json`, e una lista di `std::pair<std::string,json>` per il dizionario (in aggiunta a metodi e altre variabili che ritenete necessarie). Ogni oggetto `json` userà solo una di queste cinque variabili (in modo analogo a come abbiamo fatto con la classe token a lezione) e potreste modellare il valore null controllando che ognuna di queste cinque variabili non sia “in uso”.

  
  
  
### Eccezioni

Nel file json.hpp è definita la struct

    struct json_exception {
        std::string msg;
    };

che dovete usare per le eccezioni. Usate la stringa `msg` per fornire un messaggio di errore informativo (vi tornerà utile in fase di debugging: nei nostri report che vi forniremo, stamperemo questi messaggi).

### Tipi membri di json


    json::impl;

Questa è la struct (privata in json) che potete utilizzare per definire le variabili e metodi che volete usare nell’implementazione di json (come detto sopra, un oggetto `json` contiene un puntatore `impl*`). 

Ricordate che `json::impl` ha accesso ai membri privati di `json`, quindi se lo desiderate dentro `json::impl` potete anche definire metodi che prendono in input oggetti `json` e modificano il loro contenuto (accedendo a membri privati di `json`). 



---
    json::list_iterator;
    json::dictionary_iterator;
    json::const_list_iterator;
    json::const_dictionary_iterator;

Questi sono dei forward iterator che permettono di navigare le liste e i dizionari contenuti in un oggetto `json` (maggiori dettagli sono descritti sotto, nei metodi `begin_list()`, `end_list()`, `begin_dictionary()`, `end_dictionary()`). Su ognuno di questi iteratori, definire (come visto a lezione) i metodi per modificare gli iteratori ed accedere al loro contenuto (in particolare: `operator++` prefix e postfix, `operator*`, `operator->`, `operator==`, `operator!=`).

  
### Metodi pubblici di json


#### Costruttori, distruttore e assegnamenti:

Costruttore di default, copy constructor, move constructor, distruttore, copy assignment e move assignment, implementati con la semantica standard come visto a lezione. Il costruttore di default deve costruire un oggetto `json` di tipo null (ossia, la funzione `is_null()` descritta sotto deve restituire `true`).

    json::json();
    json::json(json const&);
    json::json(json&&);
    json::~json();
    json& json::operator=(json const&);
    json& json::operator=(json&&);



#### Metodi bool

I seguenti metodi possono essere utilizzati per capire di che tipo è l’oggetto `json` (lista, dizionario, stringa, numero, booleano, oppure null). Nota bene: esattamente **uno** di questi metodi deve restituire true (l’oggetto `json` è esattamente uno di questi sei tipi).

---
    bool json::is_list() const;
Questo metodo restituisce true se e solo se l’oggetto è una lista.

---
    bool json::is_dictionary() const;
Questo metodo restituisce true se e solo se l’oggetto è un dizionario.

---  
    bool json::is_string() const;
Questo metodo restituisce true se e solo se l’oggetto è una stringa.

---
    bool json::is_number() const;

Questo metodo restituisce true se e solo se l’oggetto è un numero (double).

---
    bool json::is_bool() const;
Questo metodo restituisce true se e solo se l’oggetto è un booleano.

---
    bool json::is_null() const;
Questo metodo restituisce true se e solo se l’oggetto è null.


#### Metodi per accedere (dall’esterno) al contenuto del container

    json const& json::operator[](std::string const& key) const;
    json& json::operator[](std::string const& key);

Se l’oggetto è un dizionario (`is_dictionary()` restituisce `true`), questo metodo restituisce una reference all’elemento `json` associato alla chiave `key` (ricordate che un dizionario è un insieme di coppie chiave-valore in cui le chiavi sono di tipo `std::string` e i valori sono di tipo `json`).

**Nota.** Non è un problema se questo metodo scorre tutto il contenuto del dizionario (per esempio, se avete implementato il dizionario tramite una lista). Non ci aspettiamo che questo metodo sia particolarmente efficiente (a differenza del metodo `json::insert`, vedi sotto).

Se il dizionario non contiene nessuna coppia chiave-valore la cui chiave è uguale a `key`, allora:

- il metodo `operator[]` deve inserire nel dizionario una nuova coppia chiave-valore la cui chiave è `key` e il cui valore è un `json` costruito con il costruttore di default (i.e., un `json` il cui contenuto è `null`), ed infine restituire una reference a questo nuovo `json` appena costruito;
- il metodo `operator[] const` deve lanciare invece un'eccezione non potendo effettuare nessun inserimento.

In ogni caso, se l’oggetto non è un dizionario, lanciamo un’eccezione `json_exception` (con messaggio `msg` a piacere)
se il metodo `operator[]` viene invocato.

---
 
Se l’oggetto è una lista (`is_list()` restituisce `true`), usiamo gli iteratori `list_iterator` e `const_list_iterator` per accedere ai membri della lista (a loro volta, degli oggetti `json`).

I seguenti metodi permettono di ottenere iteratori all’inizio e alla fine della lista. Se `is_list()` restituisce `false`, questi metodi devono lanciare un’eccezione `json_exception` (con messaggio `msg` a piacere). 

**Attenzione.** L’ordine degli elementi nella lista deve essere lo stesso del file letto in input. In particolare, gli iteratori devono restituire gli elementi in questo ordine.

    json::list_iterator json::begin_list();
    json::const_list_iterator json::begin_list() const;
    json::list_iterator json::end_list();
    json::const_list_iterator json::end_list() const;

---

In modo analogo, se l’oggetto è un dizionario (`is_dictionary()` restituisce `true`), usiamo gli iteratori `dictionary_iterator` e `const_dictionary_iterator` per accedere alle coppie contenute nel dizionario (le coppie sono di tipo `std::pair<std::string,json>`). I seguenti metodi permettono di ottenere iteratori all’inizio e alla fine del dizionario. Se  `is_dictionary()` restituisce `false`, questi metodi devono lanciare un’eccezione `json_exception` (con messaggio `msg` a piacere).

**Attenzione.** A differenza degli iteratori su lista, in questo caso non è importante l’ordine in cui vengono immagazzinati e visitati gli elementi del dizionario.

    json::dictionary_iterator json::begin_dictionary();
    json::const_dictionary_iterator json::begin_dictionary() const;
    json::dictionary_iterator json::end_dictionary();
    json::const_dictionary_iterator json::end_dictionary() const;

  
---

Se `is_number()` è `true` (l’oggetto è un numero), i metodi qui sotto restituiscono una reference / const reference alla variabile `double` contenuta nel `json` (e che potete salvare in `json::impl`). Se `is_number()` è `false`, questo metodo deve lanciare un’eccezione `json_exception` (con messaggio `msg` a piacere). 

    double& json::get_number();
    double const& json::get_number() const;

  
---

Se `is_bool()` è `true` (l’oggetto è un boolean), questi metodi restituiscono una reference / const reference alla variabile booleana contenuta nel `json` (e che potete salvare in `json::impl`). Altrimenti, viene lanciata un’eccezione `json_exception` (con messaggio `msg` a piacere). 

    bool& json::get_bool();
    bool const& json::get_bool() const;

---

Se `is_string()` è `true` (l’oggetto è una stringa), questi metodi restituiscono una reference / const reference alla variabile di tipo stringa stringa contenuta nel `json` (e che potete salvare in `json::impl`). Altrimenti, viene lanciata un’eccezione `json_exception` (con messaggio `msg` a piacere). 

    std::string& json::get_string();
    std::string const& json::get_string() const;

 
 
#### Metodi per settare il contenuto del json

Questo metodo rende il json di tipo stringa, rendendo la sua stringa memorizzata internamente uguale a `x` e cancellando gli eventuali dati precedentemente memorizzati nel json (per esempio, se il json era di tipo lista, questa funzione deve svuotare la lista e poi memorizzare la stringa `x`). Dopo la chiamata di questa funzione, `is_string()` deve restituire `true` (nessun altro metodo booleano deve restituire `true`).

    void json::set_string(std::string const& x);

--- 

Questo metodo rende il json di tipo bool, rendendo il bool memorizzato internamente uguale a `x` e cancellando gli eventuali dati precedentemente memorizzati nel json (per esempio, se il json era di tipo lista, questa funzione deve svuotare la lista e poi memorizzare il booleano `x`). Dopo la chiamata di questa funzione, `is_bool()` deve restituire `true` (nessun altro metodo booleano deve restituire `true`).

    void json::set_bool(bool x);

---

Questo metodo rende il json di tipo numero, rendendo il double memorizzato internamente uguale a `x` e cancellando gli eventuali dati precedentemente memorizzati nel json (per esempio, se il json era di tipo lista, questa funzione deve svuotare la lista e poi memorizzare il double `x`). Dopo la chiamata di questa funzione, `is_number()` deve restituire true (nessun altro metodo booleano deve restituire `true`).

    void json::set_number(double x);

---

Questo metodo rende il json di tipo null, cancellando gli eventuali dati precedentemente memorizzati nel json (per esempio, se il json era di tipo lista, questa funzione deve svuotare la lista e poi memorizzare il fatto che l’oggetto è un json null). Dopo la chiamata di questa funzione, `is_null()` deve restituire `true` (nessun altro metodo booleano deve restituire `true`).

    void json::set_null();

---

Questo metodo rende il json di tipo lista, rendendo la lista interna uguale alla lista vuota  e cancellando gli eventuali dati precedentemente memorizzati nel json, _anche nel caso il json fosse una lista_ (per esempio, se il json era di tipo lista, questa funzione deve rimpiazzare la lista con la lista vuota). Dopo la chiamata di questa funzione, `is_list()` deve restituire `true` (nessun altro metodo booleano deve restituire `true`).

    void json::set_list();

---


Questo metodo rende il json di tipo dizionario, rendendo il dizionario interno uguale al dizionario vuoto  e cancellando gli eventuali dati precedentemente memorizzati nel json, _anche nel caso il json fosse un dizionario_ (per esempio, se il json era di tipo lista, questa funzione deve svuotare la lista e inizializzare il dizionario a quello vuoto). Dopo la chiamata di questa funzione, `is_dictionary()` deve restituire `true` (nessun altro metodo booleano deve restituire `true`).

    void json::set_dictionary();

---

Se il `json` è di tipo lista (`is_list()` restituisce true), questo metodo aggiunge `x` in testa alla lista. 

**Importante:** per motivi di efficienza, il metodo non deve scorrere tutta la lista! implementate il metodo come visto a lezione. 

Se il `json` non è di tipo lista, questa funzione deve lanciare un’eccezione `json_exception` (con messaggio `msg` a piacere). 

    void json::push_front(json const& x);

---

Se il `json` è di tipo lista (`is_list()` restituisce `true`), questo metodo aggiunge `x` in fondo alla lista. 

**Importante:** per motivi di efficienza, il metodo non deve scorrere tutta la lista! implementate il metodo come visto a lezione. 

Se il `json` non è di tipo lista, questa funzione deve lanciare un’eccezione `json_exception` (con messaggio `msg` a piacere). 

    void json::push_back(json const& x);

---

Se il `json` è di tipo dizionario (`is_dictionary()` restituisce `true`), questo metodo aggiunge la coppia chiave-valore `x` nel dizionario. Il metodo non deve verificare se esiste già una coppia nel dizionario la cui chiave è `x.first` (potete assumere che questo non avvenga mai nei test che eseguiremo noi). 

**Importante:** per motivi di efficienza, il metodo non deve scorrere il contenuto di tutto il dizionario! 

Se il `json` non è di tipo dizionario, questa funzione deve lanciare un’eccezione `json_exception` (con messaggio `msg` a piacere). 

    void json::insert(std::pair<std::string,json> const& x);

  

### Metodi esterni (non membri di json)


    std::ostream& operator<<(std::ostream& lhs, json const& rhs);

Questo metodo scrive l’oggetto `rhs` sull’output stream `lhs` in formato json valido (vedi descrizione formato json all’inizio del documento). Nota: i separatori (spazi, tab, newlines) sono opzionali nel formato json (potete scegliere se metterli o no: è equivalente). 

---

    std::istream& operator>>(std::istream& lhs, json& rhs);

Questo metodo legge da `lhs` un oggetto `json` e lo salva in `rhs` (sovrascrivendone il contenuto). Questa è la funzione che lancia il parser json realizzato: l’input stream è uno stream di caratteri che contiene un documento in formato json (come descritto all’inizio). L’operatore `>>` deve estrarre i dati dallo stream (usando il parser) e costruire l’oggetto `json` che contiene quei dati (cancellando il contenuto precedente di `rhs`, se questi sono presenti).

Se la funzione riscontra dei problemi durante il parsing, deve venire lanciata un’eccezione `json_exception` (con messaggio `msg` a piacere). Cercate di rilevare il numero più elevato possibile di errori di parsing (testeremo il vostro codice anche su file json in formato errato, verificando che venga lanciata l’eccezione).

  


### Suggerimenti sul parser

Suggeriamo di scrivere il parser come segue (come visto a lezione):

1. Definite una grammatica context-free in grado di riconoscere il formato json, seguendo la descrizione fornita all’inizio del documento.
2. Create una funzione per ogni simbolo non terminale della grammatica. 
3. Ogni funzione creata al punto 2 dovrebbe ricevere in input una reference a `std::istream` e restituire in output un oggetto di tipo `json`. Per esempio, se avete scritto una funzione `LIST` che parsa un’intera lista dal’istream in input, questa funzione costruirà un `json` costruito a partire da quella lista (di oggetti `json`) e la restituirà. Questo vi permetterà di implementare le funzioni in modo ricorsivo: la funzione `LIST`, a sua volta, chiamerà funzioni per estrarre i componenti della lista, le quali a loro volta restituiranno degli oggetti `json`; questi oggetti andranno inseriti all’interno della lista dell’oggetto json restituito da `LIST`.

  
  


## 3. Obiettivo finale ed esempi di come verrà testato il codice

Il container json creato può essere usato come un editor di file in formato json. Una volta caricato, il file può essere manipolato/navigato usando gli operatori definiti. Per esempio, supponiamo che `std::cin` contenga lo stream:

    [
        1,
        {
            "prima chiave" : 5,
            "seconda chiave" : [4.12,2,true],
            "terza chiave" : "una stringa",
            "quarta chiave" : {"a" : 4, "b" : [4,5]}
        },
        3
    ]

allora, il seguente codice è valido e deve stampare a schermo “4”: 

    json j;
    std::cin >> j;
    json& y = *(++j.begin_list());
    std::cout << y["quarta chiave"]["a"];


Inoltre, la classe ci permette di modificare un oggetto `json`. Per esempio, se la variabile 

    json z;

contiene i dati del file json

    {"c" : 5, "d" : 6}

e `j` è la variabile di tipo `json` definita sopra, allora dopo l’assegnamento

    (*(++j.begin_list()))["prima chiave"] = z

 
La variabile `j` deve contenere i seguenti dati: 

    [
        1,
        {
            "prima chiave" : {"c" : 5, "d" : 6},
            "seconda chiave" : [4.12,2,true],
            "terza chiave" : "una stringa",
            "quarta chiave" : {"a" : 4, "b" : [4,5]}
        },
        3
    ]

## 4. Come testare il vostro codice?
 
Ricordate la regola generale: la scrittura del codice è solo metà del lavoro! La metà rimanente consiste nel progettare dei test approfonditi per rilevare eventuali bug. In fase di valutazione, il nostro compito sarà quello di mettere sotto stress il vostro codice (testandolo sui file più disparati, sia in formato json valido che non, e combinando operatori in tutti i modi possibili), quindi progettate degli ottimi test e ricordatevi di compilare il codice con gli strumenti di debug mostrati a lezione (assert, compiler sanitizers). Ricordatevi anche di usare Valgrind.
 
Detto questo, consigliamo di crearvi un file test.cpp in cui definirete una funzione `main` che testa l'oggetto `json` da voi scritto. Questo file test.cpp **non** deve essere consegnato (dovrete consegnare solo json.cpp, leggi sotto): serve solo a voi per testare il vostro codice. Testate ogni metodo di `json` in maniera isolata, su molti test case. Verificate che non ci siano memory leaks. L'output di Valgrind deve sempre terminare con:

	ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
	
Ogni errore di memoria che troveremo verrà penalizzato. 
 

## 5. Consegna del progetto

Noi vi forniamo un file json.hpp (in questo repository GitHub) che contiene le dichiarazioni della classe e gli unici `#include` ammessi. 

**Nota.** Il file json.hpp **non** deve essere modificato in alcun modo. Noi, infatti, compileremo e testeremo il vostro codice con il file json.hpp fornito da noi (e non con quello che voi potreste aver modificato).

Il vostro compito sarà quello di implementare il file json.cpp, contenente la definizione di tutti i metodi/tipi descritti sopra. Note importanti: 

1. json.cpp può solo includere json.hpp. Non può contenere nessun altro #include e nessuna macro (in generale, nessun codice preceduto da #, eccetto `#include json.hpp`). Tutti gli include e macro verranno automaticamente rimossi prima di compilare il vostro codice. Gli unici `#include` ammessi sono quelli presenti nel file json.hpp fornito da noi.
2. json.cpp **non** deve definire la funzione `main`: saremo noi a scriverla per testare il vostro codice. Se definite la funzione `main`, il codice non compilerà.

### Formato e link per la consegna

Ogni studente deve consegnare il proprio file json.cpp (con esattamente questo nome), contenuto dentro ad una cartella il cui nome deve essere la matricola dello studente, archiviata e compressa in un file tar.gz creato come descritto qui sotto. Questo archivio è l'unico file che va consegnato tramite il modulo moodle che troverete nella pagina moodle del modulo 1 (<https://moodle.unive.it/course/view.php?id=13453>). 

Esempio: se la mia matricola è 012345 e mi trovo dentro ad una cartella contenente la mia implementazione json.cpp, per creare l'archivio devo seguire i seguenti passi (da terminale Ubuntu):

    mkdir 012345
    mv json.cpp 012345
    tar -zcvf 012345.tar.gz 012345

Questi passi creano il file `012345.tar.gz`, che deve essere consegnato tramite moodle. Se volete verificare che la creazione dell'archivio sia andata a buon fine, il seguente comando estrae l'archivio:

    tar -xvzf 012345.tar.gz

**Importante**: seguite **esattamente** queste istruzioni. Lanceremo uno script che estrae e compila automaticamente tutti i vostri progetti, quindi ogni minimo errore (esempio: archivio non in formato tar.gz, nome cartella sbagliato, nome file diverso da json.cpp) porterà all'esclusione automatica del progetto. 

Le scadenze di giugno sono:

- **14 giugno ore 23:59**
- **27 giugno ore 23:59**

I prossimi appelli saranno a settembre e gennaio. 

Il modulo moodle per la consegna verrà aperto a breve e potrete cominciare a consegnare da subito. Potete ri-consegnare un numero illimitato di volte. Ad intervalli regolari (solitamente, ogni 2 settimane) noi scarichiamo tutti i progetti consegnati e li testiamo, segnalando eventuali problemi (per esempio, memory leaks, segmentation faults, ecc) via mail direttamente agli interessati. Dopo la scadenza il modulo per la consegna verrà disattivato e l’ultima consegna che avete fatto verrà valutata.

**Importante**: consigliamo di consegnare con largo anticipo rispetto alla scadenza, in modo da ricevere utili feedback! Come detto sopra, testiamo i vostri codici ogni circa 2 settimane. Evitate di consegnare all’ultimo: dopo la consegna non potrete più apportare modifiche quindi se il vostro programma contiene bug verrete valutati negativamente.

  

## 6. Valutazione del progetto

Ogni metodo da voi scritto verrà testato da noi in modo accurato, su molti input diversi (file json sia in formato valido che non). 

Compileremo il vostro codice con lo standard C++14 (--std=c++14).

Un metodo che porta all’interruzione inaspettata del codice (esempio, segmentation fault) viene valutato 0 punti. Un metodo non implementato viene valutato 0 punti. Alcuni metodi, come quelli su iteratori, sono molto importanti perché ci permettono di testare il vostro codice (accedendo al contenuto del container): fate attenzione ad implementarli correttamente, altrimenti non avremo modo di testare il vostro codice. 

### Timeout

Attenzione: il vostro codice deve essere ragionevolmente veloce. Imposteremo un timeout di qualche minuto (in realtà dovrebbero bastare pochi secondi) per la lettura di file json e costruzione dell’oggetto json corrispondente (vedi link con dataset json fornito sopra). Se il vostro codice impiega troppo tempo ad eseguire il parsing di un file json grosso, probabilmente avete implementato male l’inserimento di dati in liste/dizionari: ricordate che gli inserimenti non devono scorrere tutti gli elementi della lista/dizionario (ma, per esempio, devono solo allocare una nuova cella in memoria e sistemare qualche puntatore - se usate le liste per entrambe queste due strutture).

### Plagi

I vostri codici verranno confrontati utilizzando un rilevatore di plagi. Questo strumento è in grado di rilevare tentativi di mascherare copiature di codice come rinomina di variabili, conversione di cicli for in cicli while, etc. Tutti i progetti coinvolti in copiature saranno considerati falliti automaticamente. Tenete bene a mente queste semplici regole: 

1. **Mai** passare il codice ad uno compagno che deve ancora sostenere l’esame. Costui infatti potrebbe copiare (anche solo in parte), con la conseguenza che entrambi non passerete l’esame. Discutere idee generali sulla soluzione va bene, ma il codice non deve mai essere condiviso. 
2. Non postate porzioni del vostro codice online (per esempio, su forum). Altri studenti potrebbero copiare il codice ed entrambi non passerete l’esame (in passato è successo anche questo).
