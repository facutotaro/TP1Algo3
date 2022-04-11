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


        sort(_actores.begin(),_actores.end(), [](Actor v, Actor u){
            return v.influencia > u.influencia;
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
int i = 0;

void RedSocial::solver() {
    vector<Actor> vacio;
    // Falta ver caso donde hay populares.
    cliqueMasInfluyente(vacio, actores());
    cout << "[";
    for (auto & re : res) {
        cout << re.id << ", ";
    }
    cout << "]" << endl;
    cout << influenciaDeGrupo(res) << endl;
}

void RedSocial::cliqueMasInfluyente(vector<Actor> Q, vector<Actor> K){ // Me hace ruido la variable global i.
    if(K.empty()){
        if(influenciaDeGrupo(Q) > influenciaMaximaVista){
            influenciaMaximaVista = influenciaDeGrupo(Q);
            res = Q;
        }
    }
    if (i < actores().size()){
        if (influenciaDeGrupo(Q)+influenciaDeGrupo(K) <= influenciaMaximaVista){
            return;
        } else {
            vector<Actor> viejoQ = Q;
            vector<Actor> viejoK = K;
            Q.push_back(K[i]);
            soloAmigosDeQEnK(Q, K);
            agregarCliqueMasGrandeDeKAQ(Q, K); 
            cliqueMasInfluyente(Q, K);

            Q = viejoQ;
            K = viejoK;
            i++;
            cliqueMasInfluyente(Q, K);
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
    int j = K.size()-1;
    int contador = 0;
    while (j >= contador) {
        bool esAmigoDeTodos = true;
        for (Actor v : Q) {
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

    /*for(Actor u : K){
        bool esAmigoDeTodos = true;
        for(Actor v : Q){
            esAmigoDeTodos = esAmigoDeTodos && sonAmigos(v, u);
        }
        if (!esAmigoDeTodos){ // Sera eficiente?
            auto posicion = find(K.begin(), K.end(), u);
            K.erase(posicion);
        }
    }*/
}


void RedSocial::agregarCliqueMasGrandeDeKAQ(vector<Actor>& Q, vector<Actor>& K) const{ // No faltaria sacar los valores de K que metimos en Q?
    vector<Actor> clique = cliqueMasGrande(K);
    for(Actor v : clique){
        Q.push_back(v);
       // K.erase(remove(begin(K), end(K), v), end(K));
    }
}

vector<Actor> RedSocial::cliqueMasGrande(vector<Actor> grupo) const {
    vector<Actor> cliqueActual;
    while (!grupo.empty()) {
        cliqueActual.push_back(masPopular(grupo)); // Me parece que el cliqueMasGrande no necesariamente contiene al masPopular.
        soloAmigosDeQEnK(cliqueActual, grupo);
    }
    return cliqueActual;
}

    /*vector<Actor> cliqueMasGrande;
    vector<Actor> cliqueActual;
    int cliqueActualSize = 0;
    for(int r = 0; r < grupo.size(); r++){
        cliqueActual.push_back(grupo[r]);
        cliqueActualSize++;
        for(int j = 0; j < cliqueActualSize; j++){
            for(int k = 0; k < grupo.size(); k++){
                if(sonAmigos(cliqueActual[j], grupo[k])){
                    cliqueActual.push_back(grupo[k]);
                    cliqueActualSize++;
                }
            }
        }
        if (cliqueActual.size() > cliqueMasGrande.size()){
            cliqueMasGrande = cliqueActual;
        }
        while (0 < cliqueActual.size()){
            cliqueActual.pop_back();
        }
    }
    return cliqueMasGrande;*/

Actor RedSocial::masPopular(vector<Actor> grupo) const { // No nos interesa el mas popular de ESE grupo?
    // No deberiamos preguntar si el elemento ademas de ser amigo del popular actual tambien esta en el grupo?
    int cantAmigosMax = 0;
    Actor popular(0, 0);

    for (int j = 0; j < grupo.size(); ++j) {
        int cantAmigos = 0;

        for(int k = 1; k < _matrizDeAmistades[j].size(); k++) {
            if( _matrizDeAmistades[j][k] && estaEnGrupo(k, grupo))
                cantAmigos++;
       }
        /*
        for (bool k: _matrizDeAmistades[j]) {
            cantAmigos += k;
        }
        */
        if (cantAmigos > cantAmigosMax) {
            cantAmigosMax = cantAmigos;
            popular = grupo[j];
        }
    }
    return popular;
}

bool RedSocial::sonAmigos(Actor v, Actor u) const{
    return _matrizDeAmistades[v.id][u.id];
}

bool RedSocial::estaEnGrupo(int id, const vector<Actor>& grupo) const {
    Actor temp(id, 0);
    return grupo.end() != find(grupo.begin(), grupo.end(), temp);
}

