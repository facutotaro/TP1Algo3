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
        _matrizDeAmistades = vector<vector<bool>>(N + 1, vector<bool>(N + 1, false));  //O(n*m)

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

        while (i < M + N) {
            string e;
            int id1, id2;
            my_file >> e;
            my_file >> id1;
            my_file >> id2;
            _amistades[i - N].first = id1;
            _amistades[i - N].second = id2;
            _matrizDeAmistades[id1][id2] = true;
            _matrizDeAmistades[id2][id1] = true;
            i++;
        }

        // Ordenarlo para agarrar el de mas influencia primero. La influencia max vista sera alta al principio, lo que facilita podas.

        sort(_actores.begin(), _actores.end(), [](Actor v, Actor u) {
            return v.influencia < u.influencia;
        });

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

void RedSocial::solverEj1() {
    vector<Actor> Q;
    vector<Actor> &V = _actores;
    vector<Actor> sinPopulares;
    filtrarPopulares(Q, V, sinPopulares);
    cliqueMasInfluyente(Q, sinPopulares);
    //cout << "[";
    int i = 0;
    while (i < res.size() - 1) {
        cout << res[i].id << ", ";
        i++;
    }
    //cout << res[i].id << "]" << endl;
    res[i].id;
    //cout << influenciaDeGrupo(res) << endl;
}

void RedSocial::cliqueMasInfluyente(vector<Actor> &Q, vector<Actor> &K) const {
    if (K.empty()) { // Caso Base
        if (influenciaDeGrupo(Q) > influenciaMaximaVista) {
            influenciaMaximaVista = influenciaDeGrupo(Q);
            res = Q;
        }
    } else {
        vector<vector<Actor>> I;
        if (influenciaDeGrupo(Q) + influenciaGruposIndependientes(I, K) <= influenciaMaximaVista) { return; }
        else {
            if (influenciaDeGrupo(Q) + influenciaDeGrupo(K) <= influenciaMaximaVista) { return; }
            else {
                vector<Actor> Qd = Q;
                vector<Actor> Kd = K;

                // Caso meto a v.
                Q.push_back(K.back());
                K.pop_back();
                // Mantengo el Invariante de K:
                soloAmigosDeQEnK(Q, K); // INV 1: Me quedo solo con todos los amigos de Q en K.
                vector<Actor> sinPopularesK;
                filtrarPopulares(Q, K,sinPopularesK); // INV 2: Busco todos los que no tienen no amigos y los agrego a Q.
                cliqueMasInfluyente(Q, sinPopularesK);

                // Caso NO meto a v.
                Kd.pop_back();
                vector<Actor> sinPopularesKd;
                // Mantengo el Invariante de K:
                filtrarPopulares(Qd, Kd, sinPopularesKd);
                cliqueMasInfluyente(Qd, sinPopularesKd);
                // }
            }
        }
    }
}

int RedSocial::influenciaGruposIndependientes(vector<vector<Actor>> &I, vector<Actor> &K) const {
    int influencia = 0;
    for (int i = K.size()-1; i >= 0 ; --i) {
        bool metido = false;
        for (auto & j : I) {
            if (noTieneAmigos(j, K[i])){
                j.push_back(K[i]);
                metido = true;
                break;
            }
        }
        if(!metido){
            I.push_back({K[i]});
            influencia += K[i].influencia;
        }
    }
    return influencia;
}


bool RedSocial::noTieneAmigos(const vector<Actor>& grupo, Actor a) const {
    bool noTieneAmigos = true;
    for (auto &u : grupo) {
        if (sonAmigos(a, u)) {
            noTieneAmigos = false;
            break;
        }
    }
    return noTieneAmigos;
}

int RedSocial::influenciaDeGrupo(const vector<Actor> &grupo) { // O(|grupo|)
    int influenciaDeGrupo = 0;
    for (Actor v : grupo) {
        influenciaDeGrupo += v.influencia;
    }
    return influenciaDeGrupo;
}

// Idea de Invariante de Q: Fijarse solo el ultimo elemento de Q.
void RedSocial::soloAmigosDeQEnK(vector<Actor> &Q, vector<Actor> &K) const { // O(k^2)
    vector<Actor> soloAmigosDeQEnK;
    for (auto & i : K) {
        if (sonAmigos(Q.back(), i)) soloAmigosDeQEnK.push_back(i);
    }
    K = soloAmigosDeQEnK;
}

void RedSocial::filtrarPopulares(vector<Actor> &Q, vector<Actor> &K, vector<Actor> &sinPopulares) const { // O(k^2)
    for (Actor v : K) { // Recorro todos los vertices en k.
        int amigos = 0;
        for (Actor u : K)
            if (sonAmigos(v, u)) amigos++;
        if (amigos == K.size() - 1) Q.push_back(v); // La variable amigos es igual que el tamanio de K - 1 (sin contar a sigo mismo). Por lo tanto es amigo de todos y lo quiero en Q.
        else sinPopulares.push_back(v); // Caso contrario se queda en K.
    }
}

bool RedSocial::sonAmigos(Actor v, Actor u) const { //O(1)
    return _matrizDeAmistades[v.id][u.id];
}

void RedSocial::solverEj2() {
    //Armo vector de tuplas
    vector<Actor> K = _actores;
    vector<vector<Actor>> I;
    particionConMenorInfluencia(I, K);
    int influencia = 0;
    cout << "[";
    int i = 0;
    while (i < I.size()) {
        cout << "[";
        int j = 0;
        while (j < I[i].size() - 1) {
            cout << I[i][j].id << ", ";
            j++;
        }
        cout << I[i][j].id << "] , ";

        influencia += I[i][0].influencia;
        i++;
    }
    cout << "]" << endl;
    cout << "Suma de Influencias: " << influencia << endl;

}

void RedSocial::particionConMenorInfluencia(vector<vector<Actor>> &I, vector<Actor> &K) const { //K tiene tuplas: <actor, bool> donde el booleano es true si el actor ya fue agregado a I.
    for (int i = K.size()-1; i >= 0 ; --i) {
        bool metido = false;
        for (auto & j : I) {
            if (noTieneAmigos(j, K[i])){
                j.push_back(K[i]);
                metido = true;
                break;
            }
        }
        if(!metido) I.push_back({K[i]});
    }
}









