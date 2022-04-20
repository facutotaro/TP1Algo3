#include "ej2.h"

RedSocialEj2::RedSocialEj2(std::string s) {
    _nombreDelArchivo = std::move(s);

    ifstream my_file;
    my_file.open(_nombreDelArchivo, ios::in);
    if (!my_file) {
    } else {
        string o, p;
        my_file >> o;
        my_file >> p;

        int N = 0;
        int M = 0;

        my_file >> N;
        my_file >> M;

        _actores = vector<Actor2>(N, Actor2(0, 0));
        _amistades = vector<pair<int, int>>(M, make_pair(0, 0));
        _matrizDeAmistades = vector<vector<bool>>(N + 1, vector<bool>(N + 1, false));  //O(n*m)

        int i = 0;

        while (i < N) {
            Actor2 actor = Actor2(0, 0);
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

        sort(_actores.begin(), _actores.end(), [](Actor2 v, Actor2 u) {
            return v.influencia < u.influencia;
        });
        int influenciaMaximaVista2 = -1;
        vector<Actor2> _res;
    }
}

RedSocialEj2::~RedSocialEj2() {

}

string RedSocialEj2::nombre() const {
    return _nombreDelArchivo;
}

RedSocialEj2::Actor2::Actor2(const int ID, const int inf) {
    id = ID;
    influencia = inf;
}
    
bool RedSocialEj2::Actor2::operator==(Actor2 v) const {
    return this->id == v.id;
}




void RedSocialEj2::solverEj2() {
    vector<Actor2> Q;
    vector<Actor2> V = _actores;
    vector<Actor2> sinPopulares;
    filtrarPopulares(Q, V, sinPopulares);
    cliqueMasInfluyente(Q, sinPopulares);
    
    int i = 0;
    while (i < _res.size() - 1) {
        cout << _res[i].id << " ";
        i++;
    }
    cout << _res[i].id << endl;
    cout << influenciaMaximaVista2 << endl;
}

void RedSocialEj2::cliqueMasInfluyente(vector<Actor2> &Q, vector<Actor2> &K) const {
    if (K.empty()) { // Caso Base
        if (influenciaDeGrupo(Q) > influenciaMaximaVista2) {
            influenciaMaximaVista2 = influenciaDeGrupo(Q);
            _res = Q;
        }
    } else {
        vector<vector<Actor2>> I;
        if (influenciaDeGrupo(Q) + influenciaGruposIndependientes(I, K) <= influenciaMaximaVista2) { return; }
        else {
            if (influenciaDeGrupo(Q) + influenciaDeGrupo(K) <= influenciaMaximaVista2) { return; }
            else {
                vector<Actor2> Qd = Q;
                vector<Actor2> Kd = K;

                // Caso meto a v.
                Q.push_back(K.back());
                K.pop_back();
                // Mantengo el Invariante de K:
                soloAmigosDeQEnK(Q, K); // INV 1: Me quedo solo con todos los amigos de Q en K.
                vector<Actor2> sinPopularesK;
                filtrarPopulares(Q, K,sinPopularesK); // INV 2: Busco todos los que no tienen no amigos y los agrego a Q.
                cliqueMasInfluyente(Q, sinPopularesK);

                // Caso NO meto a v.
                Kd.pop_back();
                vector<Actor2> sinPopularesKd;
                // Mantengo el Invariante de K:
                filtrarPopulares(Qd, Kd, sinPopularesKd);
                cliqueMasInfluyente(Qd, sinPopularesKd);
                // }
            }
        }
    }
}

int RedSocialEj2::influenciaDeGrupo(const vector<Actor2> &grupo) { // O(|grupo|)
    int influenciaDeGrupo = 0;
    for (auto & v : grupo) {
        influenciaDeGrupo += v.influencia;
    }
    return influenciaDeGrupo;
}

int RedSocialEj2::influenciaGruposIndependientes(vector<vector<Actor2>> &I, vector<Actor2> &K) const {
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

bool RedSocialEj2::noTieneAmigos(const vector<Actor2>& grupo, Actor2 a) const {
    bool noTieneAmigos = true;
    for (auto &u : grupo) {
        if (sonAmigos(a, u)) {
            noTieneAmigos = false;
            break;
        }
    }
    return noTieneAmigos;
}

// Idea de Invariante de Q: Fijarse solo el ultimo elemento de Q.
void RedSocialEj2::soloAmigosDeQEnK(vector<Actor2> &Q, vector<Actor2> &K) const { // O(k^2)
    vector<Actor2> soloAmigosDeQEnK;
    for (auto & i : K) {
        if (sonAmigos(Q.back(), i)) soloAmigosDeQEnK.push_back(i);
    }
    K = soloAmigosDeQEnK;
}

void RedSocialEj2::filtrarPopulares(vector<Actor2> &Q, vector<Actor2> &K, vector<Actor2> &sinPopulares) const { // O(k^2)
    for (auto & v : K) { // Recorro todos los vertices en k.
        int amigos = 0;
        for (auto & u : K)
            if (sonAmigos(v, u)) amigos++;
        if (amigos == K.size() - 1) Q.push_back(v); // La variable amigos es igual que el tamanio de K - 1 (sin contar a sigo mismo). Por lo tanto es amigo de todos y lo quiero en Q.
        else sinPopulares.push_back(v); // Caso contrario se queda en K.
    }
}

bool RedSocialEj2::sonAmigos(Actor2 v, Actor2 u) const { //O(1)
    return _matrizDeAmistades[v.id][u.id];
}











