
// Created by manuel boscolo matricola:882852 on 07/05/2023.

#include "json.hpp"

json_exception ex;

// implementazione della struct impl

struct json::impl {
    //implementazione della struct json_list con annessa definizione dei metodi aggiungi_testa e aggiungi_coda
    struct json_list {
        struct cella {
            json info;
            cella *next;
        };
        typedef json_list::cella *Plist;

        Plist head = nullptr;
        Plist tail = nullptr;

        void aggiungi_testa(Plist x);

        void aggiungi_coda(Plist x);
    };

    //implementazione della struct json_dict con annessa definizione dei metodi aggiungi_testa e aggiungi_coda
    struct json_dict {
        struct cella_dict {
            std::string key;
            json val;
            cella_dict *next;
        };
        typedef json_dict::cella_dict *Pdict;

        Pdict head = nullptr;
        Pdict tail = nullptr;

        void aggiungi_testa(Pdict x);

        void aggiungi_coda(Pdict x);
    };

    //dichiarazione dei campi utili per l'implementazione della struct impl
    double numero = 0;
    bool booleano = false;
    std::string stringa ;
    json_list lista;
    json_dict dizionario;
    size_t identificatore = 0;            //variabile aggiuntiva utile per indicare in tempo costante il "tipo" di json
    // 0 null
    // 1 numero
    // 2 bool
    // 3 stringa
    // 4 lista
    // 5 dizionario

};

//______________________________________________________________________________________________________________________________________________________________________-----
//_____________________________________________________IMPLEMENTAZIONE FUNZIONI AUSILIARI PER LISTE E DIZIONARI___________________________________________________________

void json::impl::json_dict::aggiungi_testa(json::impl::json_dict::Pdict x) {
    auto nuova=new cella_dict;
    nuova->key=x->key;
    nuova->val=x->val;
    nuova->next=this->head;
    this->head=nuova;
    if(head->next== nullptr)
    {
        tail=head;
    }}

void json::impl::json_dict::aggiungi_coda(json::impl::json_dict::Pdict x) {
    auto nuova = new cella_dict;
    nuova->key = x->key;
    nuova->val = x->val;
    nuova->next = nullptr;
    if (head == nullptr) {
        head = nuova;
        tail=nuova;
    }
    else {
        tail->next=nuova;
        tail=nuova;
    }
}

void json::impl::json_list::aggiungi_testa(json::impl::json_list::Plist x) {
    auto nuovo = new json_list::cella;
    nuovo->info = x->info;
    nuovo->next = head;
    head = nuovo;
    if (head->next == nullptr) {
        tail = head;
    }
}

void json::impl::json_list::aggiungi_coda(json::impl::json_list::Plist x) {
    auto nuovo=new json_list::cella;
    nuovo->info=x->info;
    nuovo->next= nullptr;

    if(head== nullptr){
        head=nuovo;
        tail=nuovo;
    }else{
        tail->next=nuovo;
        tail=nuovo;
    }
}


//__________________________________________IMPLEMENTAZIONE DEGLI ITERATORI____________________________________________________________________________________________
struct json::list_iterator{

    list_iterator(json::impl::json_list::Plist p) : ptr(p) {}
    json& operator*()const { return ptr->info; }
    list_iterator& operator++() { ptr = ptr->next; return *this; }
    bool operator!=(const list_iterator& z) const { return ptr != z.ptr; }

    json::impl::json_list::Plist ptr;
};
json::list_iterator json::begin_list() {
    return json::list_iterator(this->pimpl->lista.head);
}
json::list_iterator json::end_list() {
    return json::list_iterator(nullptr);
}

struct json::const_list_iterator {
    const_list_iterator(json::impl::json_list::Plist p) : ptr(p) {}
    const json& operator*() const { return ptr->info; }
    const_list_iterator& operator++() { ptr = ptr->next; return *this; }
    bool operator!=(const const_list_iterator& z) const { return ptr != z.ptr;}

    json::impl::json_list::Plist ptr;
};
json::const_list_iterator json::begin_list() const {
    return json::const_list_iterator(this->pimpl->lista.head);
}
json::const_list_iterator json::end_list() const {
    return json::const_list_iterator(nullptr);
}

struct json::dictionary_iterator{


    dictionary_iterator(json::impl::json_dict::Pdict p) : ptr(p) {}
    std::pair<const std::string&, json&> operator*()const { return {ptr->key, ptr->val}; }
    dictionary_iterator& operator++() { ptr = ptr->next; return *this; }
    bool operator!=(const dictionary_iterator& z) const { return ptr != z.ptr; }

    json::impl:: json_dict::Pdict ptr;

};
json::dictionary_iterator json::begin_dictionary() {
    return json::dictionary_iterator(this->pimpl->dizionario.head);
}
json::dictionary_iterator json::end_dictionary() {
    return json::dictionary_iterator(nullptr);
}

struct json::const_dictionary_iterator{


    const_dictionary_iterator(json::impl::json_dict::Pdict p) : ptr(p) {}
    std::pair<const std::string&, const json&> operator*() const { return {ptr->key, ptr->val}; }
    const_dictionary_iterator& operator++() { ptr = ptr->next; return *this; }
    bool operator!=(const const_dictionary_iterator& z) const { return ptr != z.ptr; }

    json::impl:: json_dict::Pdict ptr;
};
json::const_dictionary_iterator json::begin_dictionary() const {
    return json::const_dictionary_iterator(this->pimpl->dizionario.head);
}
json::const_dictionary_iterator json::end_dictionary() const {
    return json::const_dictionary_iterator(nullptr);
}

//__________________________________________________________________________________________________________________________________________

//___________________________________________DEFINIZIONE DEI COSTRUTTORI/DISTRUTTORI DI CLASSE________________________________________________

json::json() {                             //COSTRUTTORE DI DEFAULT  CREO UN OGGETTO JSON E LO INIZIALIZZO COME JSON NULLO
    pimpl= new impl;
    pimpl->numero = 0;
    pimpl->booleano = false;
    pimpl->stringa.clear();
    pimpl->lista.head= nullptr;
    pimpl->lista.tail= nullptr;
    pimpl->dizionario.head= nullptr;
    pimpl->dizionario.tail= nullptr;
    pimpl->identificatore=0;
}

json::json(const json & x) {    // COPY CONSTRUCTOR
    pimpl = new impl;
    pimpl->identificatore = x.pimpl->identificatore;
    pimpl->numero = x.pimpl->numero;
    pimpl->booleano = x.pimpl->booleano;
    pimpl->stringa = x.pimpl->stringa;
    json::impl::json_list::Plist supp = x.pimpl->lista.head;
    while (supp) {
        this->pimpl->lista.aggiungi_coda(supp);
        supp = supp->next;
    }
    json::impl::json_dict::Pdict supp2 = x.pimpl->dizionario.head;
    while (supp2) {
        this->pimpl->dizionario.aggiungi_coda(supp2);
        supp2 = supp2->next;
    }
}

json::json(json && x) {                                        //MOVE CONSTRUCTOR
    pimpl = x.pimpl;
    x.pimpl = nullptr;
    }

json::~json() {                                             //DISTRUTTORE
    json::impl::json_dict::Pdict tmp=this->pimpl->dizionario.head;
    while(this->pimpl->dizionario.head){
        tmp=this->pimpl->dizionario.head;
        this->pimpl->dizionario.head=  this->pimpl->dizionario.head->next;
        delete tmp;
    }
    json::impl::json_list::Plist tmp2=pimpl->lista.head;
    while(this->pimpl->lista.head){
        tmp2=this->pimpl->lista.head;
        this->pimpl->lista.head=this->pimpl->lista.head->next;
        delete tmp2;
    }
    delete this->pimpl;
}

//______________________________________________________________________________________________________________________________________________________

//--------------------------------------------DEFINIZIONE DELLE FUNZIONI BOOL()__________________________________________________________________________

bool json::is_dictionary() const {                  //IL JSON E DI TIPO DIZIONARIO SE E SOLO SE L IDENTIFICATORE E ==5 (COME DECISO NELL IMPLEMENTAZIONE DI IMP)
    if (pimpl->identificatore==5){return true;}
    else{return false;}
}

bool json::is_list() const {                            //IL JSON E DI TIPO LISTA SE E SOLO SE L IDENTIFICATORE E ==4 (COME DECISO NELL IMPLEMENTAZIONE DI IMP)
    if (pimpl->identificatore==4){return true;}
    else{return false;}
}

bool json::is_string() const {                      //IL JSON E DI TIPO STRINGA SE E SOLO SE L IDENTIFICATORE E ==3 (COME DECISO NELL IMPLEMENTAZIONE DI IMP)
    if (pimpl->identificatore==3){return true;}
    else{return false;}
}

bool json::is_bool() const {                        //IL JSON E DI TIPO BOOL SE E SOLO SE L IDENTIFICATORE E ==2 (COME DECISO NELL IMPLEMENTAZIONE DI IMP)
    if  (pimpl->identificatore==2){return true;}
    else{return false;}
}

bool json::is_number() const {                      //IL JSON E DI TIPO NUMERICO SE E SOLO SE L IDENTIFICATORE E ==1 (COME DECISO NELL IMPLEMENTAZIONE DI IMP)
    if (pimpl->identificatore==1){return true;}
    else{return false;}
}

bool json::is_null() const {                        //IL JSON E DI TIPO NULL SE E SOLO SE L IDENTIFICATORE E ==0 (COME DECISO NELL IMPLEMENTAZIONE DI IMP)
    if (pimpl->identificatore==0){return true;}
    else{return false;}
}


//____________________________________________________________________________________________________________________________________________________________

//_________________________________________________DEFINIZIONI DELLE FUNZIONI "GET"_____________________________________________________________________________

double &json::get_number() {
    if(!is_number()){
        ex.msg="il json non e di tipo numerico impossibile eseguire get_number()\n";
        throw json_exception();
    }
    double &x = pimpl->numero;
    return x;
}

double const &json::get_number() const {
    if (!is_number()) {
        ex.msg="il json non e di tipo numerico impossibile eseguire get_number()\n";
        throw json_exception();
    }
    double const&x = pimpl->numero;
    return x;
}

bool &json::get_bool() {
    if(!is_bool()){
        ex.msg="il json non e di tipo bool impossibile eseguire get_bool() \n";
       throw json_exception();
    }
    bool& x=pimpl->booleano;
    return x;
}

bool const &json::get_bool() const {
    if(!is_bool()){
        ex.msg="il json non e di tipo bool impossibile eseguire get_bool() \n";
        throw json_exception();
    }
    bool const& x=pimpl->booleano;
    return x;
}

std::string &json::get_string() {
    if (!is_string()) {
        ex.msg="il json non e di tipo string impossibile eseguire get_string() \n";
        throw json_exception();
    }
    std::string &x = pimpl->stringa;
    return x;
}

std::string const &json::get_string() const {
    if (!is_string()) {
        ex.msg="il json non e di tipo string impossibile eseguire get_string() \n";
        throw json_exception();
    }
    std::string const&x = pimpl->stringa;
    return x;
}

//______________________________________________________________________________________________________________________________________________________________

//____________________________________________________DEFINIZIONI DELLE FUNZIONI "SET"__________________________________________________________________________

void json::set_null() {                   //RIPORTA  UN JSON ALLO STATO NULLO
    delete this->pimpl;
    this->pimpl=new impl;
    pimpl->numero = 0;
    pimpl->booleano = false;
    pimpl->stringa.clear();
    pimpl->lista.head= nullptr;
    pimpl->lista.tail= nullptr;
    pimpl->dizionario.head= nullptr;
    pimpl->dizionario.tail= nullptr;
    pimpl->identificatore=0;
}

void json::set_string(const std::string & x) {
    set_null();
    pimpl->stringa=x;
    pimpl->identificatore=3;
}

void json::set_bool(bool x) {
    set_null();
    pimpl->booleano = x;
    pimpl->identificatore=2;
}

void json::set_number(double x) {
    set_null();
    pimpl->numero = x;
    pimpl->identificatore=1;
}

void json::set_dictionary() {
    set_null();
    pimpl->dizionario.head= nullptr;
    pimpl->dizionario.tail= nullptr;
    pimpl->identificatore=5;
}

void json::set_list() {
    set_null();
    pimpl->lista.head= nullptr;
    pimpl->lista.tail= nullptr;
    pimpl->identificatore=4;
}



//___________________________________________________________________________________________________________________________________________________--

//__________________________________________________________DEFINIZIONE DEGLI OPERATORI_________________________________________________________________-

json &json::operator=(const json & x) {
    if (this == &x) { return *this; }
    else {
        delete this->pimpl;
        this->pimpl = new impl;

        this->set_null();
        this->pimpl->identificatore = x.pimpl->identificatore;
        this->pimpl->numero = x.pimpl->numero;
        this->pimpl->stringa = x.pimpl->stringa;
        this->pimpl->booleano = x.pimpl->booleano;
        json::impl::json_list::Plist suppl = x.pimpl->lista.head;
        while (suppl) {
            this->pimpl->lista.aggiungi_coda(suppl);
            suppl = suppl->next;
        }
        json::impl::json_dict::Pdict suppd = x.pimpl->dizionario.head;
        while (suppd) {
            this->pimpl->dizionario.aggiungi_coda(suppd);
            suppd = suppd->next;
        }
        return *this;
    }
}

json &json::operator=(json && x) {
    if (this != &x) {
        delete this->pimpl;
        this->pimpl = x.pimpl;
        x.pimpl = nullptr;
    }
    return *this;
}

json const &json::operator[](const std::string & chiave) const {
    if(!is_dictionary()){ex.msg="errore il json non e di tipo dizionario"; throw json_exception();}
    json::impl::json_dict::Pdict supp=pimpl->dizionario.head;
    while(supp!= nullptr) {
        if (supp->key == chiave) { return supp->val; }
        supp = supp->next;
    }
    ex.msg="Errore elemento non trovato nel dizionario";
    throw json_exception();
}

json &json::operator[](const std::string & chiave) {
    if(!is_dictionary()){ex.msg="errore il json non e di tipo dizionario"; throw json_exception();}
    json::impl::json_dict::Pdict supp=pimpl->dizionario.head;
    while(supp!= nullptr){
        if( supp->key==chiave){return supp->val;}
        supp=supp->next;
    }
    auto nuova= new json::impl::json_dict::cella_dict;
    nuova->key=chiave;
    nuova->val.set_null();
    nuova->next= nullptr;
    this->pimpl->dizionario.aggiungi_coda(nuova);

    return pimpl->dizionario.head->val;
}



//___________________________________________________________________________________________________________________________________________________________________________

//_____________________________________________________________DEFINIZIONE FUNZIONI PUSH E INSERT___________________________________________________________________________

void json::push_front(const json & x) {
    if (is_list()) {
        auto nuovo=new json::impl::json_list::cella;
        nuovo->info=x;
        nuovo->next= nullptr;
        this->pimpl->lista.aggiungi_testa(nuovo);
    }else{
        ex.msg="il json non e di tipo lista ";
        throw json_exception();
    }
}

void json::push_back(const json & x) {
    if(is_list()){
        auto nuovo=new json::impl::json_list::cella;
        nuovo->info=x;
        nuovo->next= nullptr;
        pimpl->lista.aggiungi_coda(nuovo);
    }else{
        ex.msg="il json non e di tipo lista";
        throw json_exception();
    }
}

void json::insert(const std::pair<std::string, json> & x) {
    if(!is_dictionary()){ex.msg="Errore il json non e di tipo dizionario, eseguire prima una set_dictionary";throw json_exception();}
    auto nuovo=new json::impl::json_dict::cella_dict;
    nuovo->key=x.first;
    nuovo->val=x.second;
    nuovo->next= nullptr;
    this->pimpl->dizionario.aggiungi_coda(nuovo);
}



//_________________________________________________________________________________________________________________________________________________________________________
//______________________________________________________________DEFINIZIONE OPERATORI STREAM_______________________________________________________________________________




std::ostream& operator<<(std::ostream& lhs, json const& rhs) {
        if (rhs.is_null()) {lhs<<"null";}
        else if (rhs.is_bool()) {if(rhs.get_bool()==0) {lhs<<"false";}else{lhs<<"true";}}
        else if (rhs.is_number()) {lhs << rhs.get_number();}
        else if (rhs.is_string()) {lhs << '"' << rhs.get_string() << '"';}
        else if (rhs.is_list()) {
            lhs << '['<<"\n";
            for (auto a = rhs.begin_list(); a != rhs.end_list(); ++a) {
                if (a!= rhs.begin_list()) {lhs << ",\n"; }
                lhs << *a; }
            lhs << ']';
            lhs<<"\n";
        }
        else if (rhs.is_dictionary()) {
            lhs << '{'<<"\n";
            for (auto b = rhs.begin_dictionary(); b != rhs.end_dictionary(); ++b) {
                if (b != rhs.begin_dictionary()){lhs << ",\n";}
                lhs << '"' << b.ptr->key<< '"' << ": " << b.ptr->val;

            }
            lhs << '}';
            lhs<<"\n";
        }
        return lhs;
    }



    std::istream& operator>>(std::istream& lhs, json& rhs){
    char simbolo;
    lhs >> simbolo;
    if (simbolo == '{') {                   //parsing dizionario
        rhs.set_dictionary();
        lhs >> simbolo;
        if (simbolo != '}') {
            lhs.putback(simbolo);
            do {
                std::string chiave;
                lhs >> simbolo;
                if (simbolo != '"') {ex.msg="formato non valido per l acqusizione del json\n";std::cout<<ex.msg; throw json_exception();}
                getline(lhs, chiave, '"');
                lhs >> simbolo;
                if (simbolo != ':') {ex.msg="formato non valido per l acqusizione del json\n";std::cout<<ex.msg;throw json_exception();}
                json convertito;
                lhs >> convertito;
                rhs.insert({chiave,convertito});
                lhs >> simbolo;
            } while (simbolo == ',');
            if (simbolo != '}') {ex.msg="formato non valido per l acqusizione del json\n";std::cout<<ex.msg;throw json_exception();}
        }

    }
    else if (simbolo== '[') {       //parsing lista
        rhs.set_list();
        lhs >> simbolo;
        if (simbolo!= ']') {
            lhs.putback(simbolo);
            do {
                json convertito;
                lhs >> convertito;
                rhs.push_back(convertito);
                lhs >> simbolo;
            } while (simbolo == ',');
            if (simbolo!= ']') {ex.msg="formato non valido per l acqusizione del json\n";std::cout<<ex.msg;throw json_exception();}
        }
    }

    //parsing numero
    else if (std::isdigit(simbolo) || simbolo == '+' || simbolo == '-' || simbolo == '.') {
        std::string num = std::string(1, simbolo);
        while (lhs.peek() != -1 && (std::isdigit(lhs.peek()) || lhs.peek() == '+' || lhs.peek() == '-' || lhs.peek() == '.' || lhs.peek() == 'e' || lhs.peek() == 'E')) {
            num += lhs.get();
        }
        double d = std::stod(num);
        rhs.set_number(d);
    }

    //parsing stringa
    else if (simbolo == '"') {
        std::string str;
        getline(lhs, str, '"');
        rhs.set_string(str);
    }

    //parsing bool
    else if (simbolo == 't' || simbolo == 'f') {
        std::string boolean = std::string(1, simbolo);
        while (lhs.peek() != -1 && std::isalpha(lhs.peek())) {
            boolean += lhs.get();
        }
        bool b = boolean == "true";
        rhs.set_bool(b);
    }

    //parsing null
    else if (simbolo == 'n') {
        std::string n = std::string(1, simbolo);
        while (lhs.peek() != -1 && std::isalpha(lhs.peek())) {
            n += lhs.get();
        }
        if (n != "null") {ex.msg="formato non valido per l acqusizione del json\n";std::cout<<ex.msg;throw json_exception();}
        rhs.set_null();
    } else {ex.msg="formato non valido per l acqusizione del json\n";std::cout<<ex.msg;throw json_exception();}

    return lhs;
}


//___________________________________________________________FINE_PROGETTO__________________________________________________________________---
//_________________________________________________________ ALUNNO_BOSCOLO_MANUEL_ MAT: 882852____________________________________________________