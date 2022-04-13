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
            return v.id < u.id;
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
    cliqueMasInfluyente(vacio, V, 0);
    cout << "[";
    for (auto & re : res) {
        cout << re.id << ", ";
    }
    cout << "]" << endl;
    cout << influenciaDeGrupo(res) << endl;
}

void RedSocial::cliqueMasInfluyente(vector<Actor>& Q, vector<Actor>& K, int i) const{ // Me hace ruido la variable global i.
    if(K.empty()){
        if(influenciaDeGrupo(Q) > influenciaMaximaVista){
            influenciaMaximaVista = influenciaDeGrupo(Q);
            res = Q;
        }
    }
    if(i < actores().size()) {
        if (influenciaDeGrupo(Q) + influenciaDeGrupo(K) <= influenciaMaximaVista) {
            return;
        } else {
            vector<Actor> viejoQ = Q;
            vector<Actor> viejoK = K;

            Q.push_back(K[0]);
            soloAmigosDeQEnK(Q, K); // Me quedo solo con todos los amigos de Q en K.
            agregarCliqueMasGrandeDeKAQ(Q, K); // Busco todos los que no tienen no amigos y los agrego a Q.
            i++;
            cliqueMasInfluyente(Q, K, i);

            // Q.erase(remove(Q.begin(), Q.end(), actores()[i-1]), Q.end());
            cliqueMasInfluyente(viejoQ, viejoK, i);
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

void RedSocial::agregarCliqueMasGrandeDeKAQ(vector<Actor>& Q, vector<Actor>& K) const{ // No faltaria sacar los valores de K que metimos en Q?
    for(Actor v : K) {
        if (esAmigoDeTodos(v, K)) {
            Q.push_back(v);
            K.erase(remove(K.begin(), K.end(), v), K.end());
        }
    }
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



