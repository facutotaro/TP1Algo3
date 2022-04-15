#include "ej1-2.h"

RedSocial::RedSocial(std::string s) {
    _nombreDelArchivo = std::move(s);

    ifstream my_file;
    my_file.open("../ej1-2/instancias-ej1-2/" + _nombreDelArchivo + ".clq", ios::in);
    if (!my_file) {
    } else {
        string o, p;
        my_file >> o;
        my_file >> p;

        int N = 0;
        int M = 0;

        my_file >> N;
        my_file >> M;

        _actores = vector<Actor>(N, Actor(0, 0));
        _amistades = vector<pair<int, int>>(M, make_pair(0, 0));
        _matrizDeAmistades = vector<vector<bool>>(N+1, vector<bool>(N+1, false));  //O(n*m)

        int i = 0;

        while (i < N) {
            Actor actor = Actor(0, 0);
            string n;
            my_file >> n;
            my_file >> actor.id;
            my_file >> actor.influencia;
            _actores[i] = actor;
            i++;
        }

        while (i < M+N) {
            string e;
            int id1, id2;
            my_file >> e;
            my_file >> id1;
            my_file >> id2;
            _amistades[i-N].first = id1;
            _amistades[i-N].second = id2;
            _matrizDeAmistades[id1][id2] = true;
            _matrizDeAmistades[id2][id1] = true;
            i++;
        }

        // Ordenarlo para agarrar el de mas influencia primero. La influencia max vista sera alta al principio, lo que facilita podas.

        sort(_actores.begin(),_actores.end(), [](Actor v, Actor u){
            return v.influencia < u.influencia;
        });

       solver();

    }

}

RedSocial::~RedSocial() {

}

string RedSocial::nombre() const {
    return _nombreDelArchivo;
}

vector<Actor> RedSocial::actores() const{
    return _actores;
}

vector<pair<int, int>> RedSocial::amistades() const{
    return _amistades;
}

vector<vector<bool>> RedSocial::matrizDeAmistades() {
    return _matrizDeAmistades;
}

Actor::Actor(const int ID, const int inf) {
    id = ID;
    influencia = inf;
}

bool Actor::operator==(Actor v) const {
    return this->id == v.id;
}

// Variables Globales:
int influenciaMaximaVista = -1;
vector<Actor> res;

void RedSocial::solver() {
    vector<Actor> vacio;
    // Falta ver caso donde hay populares.
    vector<Actor> V = _actores;
    cliqueMasInfluyente(vacio, V, 0);
    cout << "[";
    for (auto & re : res) {
        cout << re.id << ", ";
    }
    cout << "]" << endl;
    cout << influenciaDeGrupo(res) << endl;
}

void RedSocial::cliqueMasInfluyente(vector<Actor>& Q, vector<Actor>& K, int influenciaDeQ) const{ // Pasarle paramentro influencia DeQ.
    invariante(Q, K); // Funcion para el debug
    if(K.empty()){ // Caso Base
        if(influenciaDeQ > influenciaMaximaVista){
            influenciaMaximaVista = influenciaDeQ;
            res = Q;
        }
    } else {
        if (influenciaDeQ + influenciaDeGrupo(K) <= influenciaMaximaVista) { // Poda
            return;
        } else {
            vector<Actor> Qd = Q; // Quizas no copiar estos???
            vector<Actor> Kd = K;

            Actor v = K[K.size()-1];
            int influenciaDeQConV = influenciaDeQ + v.influencia;

            // Caso meto a v.
            Q.push_back(K[K.size()-1]);
            K.pop_back();
            // Mantengo el Invariante de K:
            soloAmigosDeQEnK(Q, K); // INV 1: Me quedo solo con todos los amigos de Q en K.
            agregarCliqueMasGrandeDeKAQ(Q, K, influenciaDeQConV); // INV 2: Busco todos los que no tienen no amigos y los agrego a Q.
            cliqueMasInfluyente(Q,K, influenciaDeQConV);

            // Caso NO meto a v.
            Kd.pop_back();
            agregarCliqueMasGrandeDeKAQ(Qd, Kd, influenciaDeQ);// Chequiar si hay actores populares <-Facu: esto creo que no hace falta porque sino los restantes ya estarian en la clique
            cliqueMasInfluyente(Qd, Kd, influenciaDeQ);
        }
    }
}

int RedSocial::influenciaDeGrupo(const vector<Actor>& grupo) { // O(|grupo|)
    int influenciaDeGrupo = 0;
    for(Actor v : grupo){
        influenciaDeGrupo = influenciaDeGrupo + v.influencia;
    }
    return influenciaDeGrupo;
}

// Idea de Invariante de Q: Fijarse solo el ultimo elemento de Q.
void RedSocial::soloAmigosDeQEnK(vector<Actor>& Q, vector<Actor>& K) const{ //Cambiar ordenamiento de Actores y en vez de hacer erase usar pop back iterando sobre el ultimo, O(K)
    int j = 0;
    while (j < K.size()){
        bool esAmigoDeTodos = sonAmigos(Q[Q.size()-1], K[j]);
        if (!esAmigoDeTodos) {
            K[j] = K[K.size()-1];
            K.pop_back();
        } else {
            j++;
        }
    }
}

void RedSocial::agregarCliqueMasGrandeDeKAQ(vector<Actor>& Q, vector<Actor>& K, int& influenciaDeQ) const{ // O(k²)
    vector<Actor> ref = K; //O(k)
    for (int i = 0; i < K.size(); ++i) { //K * O(K) <- O(k²)
        if (esAmigoDeTodos(K[i], ref)){
            Q.push_back(K[i]);
            influenciaDeQ += K[i].influencia;
            K[i] = K[K.size()-1];
            K.pop_back();
        }
    }
}

bool RedSocial::esAmigoDeTodos(Actor a, const vector<Actor>& grupo) const { //O(grupo)
    bool esAmigoDeTodos = true;
    for(int j = 0; esAmigoDeTodos && j < grupo.size(); j++){
        if (!(grupo[j] == a))
            esAmigoDeTodos = sonAmigos(a, grupo[j]) && esAmigoDeTodos; //O(1)
    }
    return esAmigoDeTodos;
}

bool RedSocial::sonAmigos(Actor v, Actor u) const{ //O(1)
    return _matrizDeAmistades[v.id][u.id];
}

void RedSocial::invariante(vector<Actor>& Q, vector<Actor>& K) const{
    int type1 = 0; // LOS DEL CLIQUE NO SON AMIGOS: No se cumple Q.
    int type2 = 0; // LOS DEL CLIQUE NO SON AMIGOS CON LOS DE K: No se cumple Inv 1.
    int type3 = 0; // HAY POPULARES EN K: No se cumple Inv 2.
    for (auto & q : Q)
    {
        for (auto & k : K) // Hay no amigos en Q.
        {
            if (!(q == k) && !_matrizDeAmistades[q.id][k.id]) {
                type1++;

            }
        }
        for (auto & k : K) // Hay no amigos de los de Q en K.
        {
            if (!_matrizDeAmistades[q.id][k.id]) {
                type2++;
            }
        }
    }
    for (auto & k1 : K)
    {
        bool esPopular = true;
        for (auto & k2 : K) // Hay populares en K.
        {
            if (!(k1 == k2) && _matrizDeAmistades[k1.id][k2.id]) {
                esPopular = false;
                break;
            }
        }
        if (esPopular) {
            type3++;

        }
    }
    type1 = type1 / 2;
    type2 = type2 / 2;
    type3 = type3 / 2;
    if (type1)cout << "LOS DEL CLIQUE NO SON AMIGOS(" << type1 << ")" << endl;
    if (type2)cout << "LOS DEL CLIQUE NO SON AMIGOS CON LOS DE K(" << type2 << ")" << endl;
    if (type3)cout << "HAY POPULARES EN K(" << type3 << ")" << endl;
}





