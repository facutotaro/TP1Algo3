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
    vector<Actor> Q;
    vector<Actor> V = _actores;
    int influenciaDeQ = 0;
    vector<Actor> sinPopulares;
    filtrarPopulares(Q, V, sinPopulares, influenciaDeQ);
    cliqueMasInfluyente(Q, sinPopulares, 0);
    cout << "[";
    for (auto & re : res) {
        cout << re.id << ", ";
    }
    cout << "]" << endl;
    cout << influenciaDeGrupo(res) << endl;
}

// Arreglar orden K.
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
            vector<Actor> sinPopularesK;
            filtrarPopulares(Q, K, sinPopularesK, influenciaDeQConV); // INV 2: Busco todos los que no tienen no amigos y los agrego a Q.
            cliqueMasInfluyente(Q,sinPopularesK, influenciaDeQConV);

            // Caso NO meto a v.
            Kd.pop_back();
            vector<Actor> sinPopularesKd;
            // Mantengo el Invariante de K:
            filtrarPopulares(Qd, Kd, sinPopularesKd, influenciaDeQConV);
            cliqueMasInfluyente(Qd, sinPopularesKd, influenciaDeQ);
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

void RedSocial::filtrarPopulares(vector<Actor> &Q, vector<Actor> &K, vector<Actor>& sinPopulares, int& influenciaDeQ) const{
    for (Actor v : K) {
        int amigos = 0;

        for (Actor u : K) {
            if (_matrizDeAmistades[v.id][u.id]) {
                amigos++;
            }
        }

        if (amigos == K.size() - 1) {
            Q.push_back(v);
            influenciaDeQ += v.influencia;
        }
        else {
            sinPopulares.push_back(v);
        }
    }
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
            if (!(k1 == k2) && !_matrizDeAmistades[k1.id][k2.id]) {
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







