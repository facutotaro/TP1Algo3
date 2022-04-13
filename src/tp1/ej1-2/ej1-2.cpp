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
            my_file >> e;
            my_file >> _amistades[i-N].first;
            my_file >> _amistades[i-N].second;
            i++;
        }

        // Ordenarlo para agarrar el de mas influencia primero. La influencia max vista probablemente esta al principio lo que facilita podas.

        sort(_actores.begin(),_actores.end(), [](Actor v, Actor u){
            return v.influencia < u.influencia;
        });

        _matrizDeAmistades = vector<vector<bool>>(N+1, vector<bool>(N+1, 0));
        // Creo que deberiamos tener una listaDeAdyacencia para saber rapido el grado de un nodo.


        for(auto & a : _amistades){
            _matrizDeAmistades[a.first][a.second] = true;
            _matrizDeAmistades[a.second][a.first] = true;
        }

       solver();

    }
    my_file.close();
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
    cliqueMasInfluyente(vacio, V);
    cout << "[";
    for (auto & re : res) {
        cout << re.id << ", ";
    }
    cout << "]" << endl;
    cout << influenciaDeGrupo(res) << endl;
}

void RedSocial::cliqueMasInfluyente(vector<Actor> Q, vector<Actor> K) const{
    //invariante(Q, K); // Funcion para el debug
    if(K.empty()){ // Caso Base
        if(influenciaDeGrupo(Q) > influenciaMaximaVista){
            influenciaMaximaVista = influenciaDeGrupo(Q);
            res = Q;
        }
    } else {
        if (influenciaDeGrupo(Q) + influenciaDeGrupo(K) <= influenciaMaximaVista) { // Poda
            return;
        } else {
            vector<Actor> Qd = Q;
            vector<Actor> Kd = K;

            // Caso meto a v.
            Q.push_back(K[K.size()-1]);
            K.pop_back();
            // Mantengo el Invariante de K:
            soloAmigosDeQEnK(Q, K); // INV 1: Me quedo solo con todos los amigos de Q en K.
            agregarCliqueMasGrandeDeKAQ(Q, K); // INV 2: Busco todos los que no tienen no amigos y los agrego a Q.
            cliqueMasInfluyente(Q,K);

            // Caso NO meto a v.
            Kd.pop_back();
            agregarCliqueMasGrandeDeKAQ(Qd, Kd);// Chequiar si hay actores populares
            cliqueMasInfluyente(Qd, Kd);
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

void RedSocial::soloAmigosDeQEnK(vector<Actor>& Q, vector<Actor>& K) const{ //Cambiar ordenamiento de Actores y en vez de hacer erase usar pop back iterando sobre el ultimo.
    int j = K.size()-1;                                                     // O(K*Q) = O(n2)
    int contador = 0;
    while (j >= contador) {
        bool esAmigoDeTodos = true;
        for (Actor v : Q) { // O(|Q|)
            esAmigoDeTodos = esAmigoDeTodos && sonAmigos(v, K[j]);
        }
        if (esAmigoDeTodos) {
            Actor temp = K[contador];
            K[contador] = K[j];
            K[j] = temp;
            contador++;
        } else {
            K.pop_back();
            j--;
        }
    }
}

void RedSocial::agregarCliqueMasGrandeDeKAQ(vector<Actor>& Q, vector<Actor>& K) const{ //
    vector<Actor> noSonAmigosDeTodos;
    for(Actor v : K) { // O(|K|)
        if (esAmigoDeTodos(v, K)) { // O(|K|)
            Q.push_back(v);
        }  else {
            noSonAmigosDeTodos.push_back(v);
        }
    }
    K = noSonAmigosDeTodos;
}

bool RedSocial::esAmigoDeTodos(Actor a, const vector<Actor>& grupo) const {
    bool esAmigoDeTodos = true;
    for(int j = 0; esAmigoDeTodos && j < grupo.size(); j++){
        if (!(grupo[j] == a))
            esAmigoDeTodos = sonAmigos(a, grupo[j]) && esAmigoDeTodos;
    }
    return esAmigoDeTodos;
}

bool RedSocial::sonAmigos(Actor v, Actor u) const{
    return _matrizDeAmistades[v.id][u.id];
}

void RedSocial::invariante(vector<Actor>& Q, vector<Actor>& K) const{
    int type1 = 0; // LOS DEL CLIQUE NO SON AMIGOS
    int type2 = 0; // LOS DEL CLIQUE NO SON AMIGOS CON LOS DE K
    int type3 = 0; // HAY POPULARES EN K
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





