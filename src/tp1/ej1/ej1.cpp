#include "ej1.h"

RedSocialEj1::RedSocialEj1(std::string s) {
    _nombreDelArchivo = std::move(s);

    ifstream my_file;
    my_file.open(_nombreDelArchivo , ios::in);
    if (!my_file) {
    } else {
        string o, p;
        my_file >> o;
        my_file >> p;

        int N = 0;
        int M = 0;

        my_file >> N;
        my_file >> M;

        _actores = vector<Actor1>(N, Actor1(0, 0));
        _amistades = vector<pair<int, int>>(M, make_pair(0, 0));
        _matrizDeAmistades = vector<vector<bool>>(N + 1, vector<bool>(N + 1, false));  //O(n*m)

        int i = 0;

        while (i < N) {
            Actor1 actor = Actor1(0, 0);
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

        sort(_actores.begin(), _actores.end(), [](Actor1 v, Actor1 u) {
            return v.influencia < u.influencia;
        });
        int influenciaMaximaVista1 = -1;
        vector<Actor1> _res;
    }
}

RedSocialEj1::~RedSocialEj1() {

}

string RedSocialEj1::nombre() const {
    return _nombreDelArchivo;
}

RedSocialEj1::Actor1::Actor1(const int ID, const int inf) {
    id = ID;
    influencia = inf;
}

bool RedSocialEj1::Actor1::operator==(Actor1 v) const {
    return this->id == v.id;
}



void RedSocialEj1::solverEj1() {
    vector<Actor1> Q;
    vector<Actor1> V = _actores;
    vector<Actor1> sinPopulares;
    filtrarPopulares(Q, V, sinPopulares);
    cliqueMasInfluyente(Q, sinPopulares);
    int i = 0;
    while (i < _res.size() - 1) {
        cout << _res[i].id << " ";
        i++;
    }
    cout << _res[i].id << endl;
    cout << influenciaMaximaVista1 << endl;
}

void RedSocialEj1::cliqueMasInfluyente(vector<Actor1> &Q, vector<Actor1> &K) const {
    if (K.empty()) { // Caso Base
        if (influenciaDeGrupo(Q) > influenciaMaximaVista1)
        {influenciaMaximaVista1 = influenciaDeGrupo(Q);
        _res = Q;} 
    } else {
        if (influenciaDeGrupo(Q) + influenciaDeGrupo(K) <= influenciaMaximaVista1) return;
        else {
            vector<Actor1> Qd = Q;
            vector<Actor1> Kd = K;

            // Caso meto a v.
            Q.push_back(K.back());
            K.pop_back();
            // Mantengo el Invariante de K:
            soloAmigosDeQEnK(Q, K); // INV 1: Me quedo solo con todos los amigos de Q en K.
            vector<Actor1> sinPopularesK;
            filtrarPopulares(Q, K,sinPopularesK); // INV 2: Busco todos los que no tienen no amigos y los agrego a Q.
            cliqueMasInfluyente(Q, sinPopularesK);

            // Caso NO meto a v.
            Kd.pop_back();
            vector<Actor1> sinPopularesKd;
            // Mantengo el Invariante de K:
            filtrarPopulares(Qd, Kd, sinPopularesKd);
            cliqueMasInfluyente(Qd, sinPopularesKd);
        }
    }
}

int RedSocialEj1::influenciaDeGrupo(const vector<Actor1> &grupo) { // O(|grupo|)
    int influenciaDeGrupo = 0;
    for (auto & v: grupo) {
        influenciaDeGrupo += v.influencia;
    }
    return influenciaDeGrupo;
}

// Idea de Invariante de Q: Fijarse solo el ultimo elemento de Q.
void RedSocialEj1::soloAmigosDeQEnK(vector<Actor1> &Q, vector<Actor1> &K) const { // O(k^2)
    vector<Actor1> soloAmigosDeQEnK;
    for (auto & i : K) {
        if (sonAmigos(Q.back(), i)) soloAmigosDeQEnK.push_back(i);
    }
    K = soloAmigosDeQEnK;
}

void RedSocialEj1::filtrarPopulares(vector<Actor1> &Q, vector<Actor1> &K, vector<Actor1> &sinPopulares) const { // O(k^2)
    for (auto & v : K) { // Recorro todos los vertices en k.
        int amigos = 0;
        for (auto & u : K)
            if (sonAmigos(v, u)) amigos++;
        if (amigos == K.size() - 1) Q.push_back(v); // La variable amigos es igual que el tamanio de K - 1 (sin contar a sigo mismo). Por lo tanto es amigo de todos y lo quiero en Q.
        else sinPopulares.push_back(v); // Caso contrario se queda en K.
    }
}

bool RedSocialEj1::sonAmigos(Actor1 v, Actor1 u) const { //O(1)
    return _matrizDeAmistades[v.id][u.id];
}













