/*
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <cmath>
#include <climits>
#include "graph_utils.h"
#include <iomanip>

// Construtor
// Cria um grafo com n vértices e nenhuma aresta. A representação usada é a
// matriz de adjacência n x n: adj[u][v] guarda o peso da aresta u -> v
// (0 significa "não existe aresta").
graph_utils::graph_utils(int n) {
    this->n = n;
    this->m = 0;

    if (n > 0) {
        // Aloca a matriz como um vetor de ponteiros (linhas), e cada linha
        // como um vetor de n inteiros, todos iniciados em 0 (sem arestas).
        adj = new int*[n];
        for (int u = 0; u < n; u++) {
            adj[u] = new int[n];
            for (int v = 0; v < n; v++) {
                adj[u][v] = 0;
            }
        }

        // Vetores paralelos aos vértices: o índice i de peso/rotulos
        // corresponde ao vértice i. Nome padrão "Jogo i" até ler o arquivo.
        peso = new int[n];
        rotulos = new std::string[n];

        for (int t = 0; t < n; t++) {
            peso[t] = 0;
            rotulos[t] = "Jogo " + std::to_string(t);
        }
    } else {
        // Grafo vazio: ponteiros nulos para que o destrutor e as outras
        // funções saibam que não há memória alocada.
        adj = nullptr;
        peso = nullptr;
        rotulos = nullptr;
    }
}

// Destrutor
// Libera toda a memória dinâmica. A matriz precisa ser liberada em duas
// etapas: primeiro cada linha (adj[v]) e depois o vetor de ponteiros (adj).
graph_utils::~graph_utils() {
    if (adj != nullptr) {
        for (int v = 0; v < n; v++) {
            delete [] adj[v];
        }
        delete [] adj;
    }

    if (peso != nullptr) delete [] peso;
    if (rotulos != nullptr) delete [] rotulos;

    n = 0;
    m = 0;

    std::cout << "Memoria do grafo liberada com sucesso.\n";
}

// Opção a: Ler dados do arquivo grafo.txt
// Formato esperado do arquivo:
//   <tipo do grafo>
//   <n = número de vértices>
//   n linhas: <id> "<nome do jogo>" <peso do vértice>
//   <m = número de arestas>
//   m linhas: <origem> <destino> <peso da aresta>
void graph_utils::readfile(const char *arquivo) {
    std::ifstream file(arquivo);

    if (!file.is_open()) {
        std::cout << "ERRO: Nao foi possivel abrir o arquivo " << arquivo << "!\n";
        return;
    }

    // Limpa a memória anterior se já houver um grafo carregado
    if (n > 0 && adj != nullptr) {
        for (int v = 0; v < n; v++) {
            delete [] adj[v];
        }
        delete [] adj;
        delete [] peso;
        delete [] rotulos;
        adj = nullptr;
        peso = nullptr;
        rotulos = nullptr;
        n = 0;
        m = 0;
    }

    int graphType, numV;
    if (!(file >> graphType >> numV) || numV < 0) {
        std::cout << "ERRO: Estrutura de arquivo invalida (Cabecalho).\n";
        file.close();
        return;
    }

    this->n = numV;
    this->m = 0;

    if (n > 0) {
        adj = new int*[n];
        for (int u = 0; u < n; u++) {
            adj[u] = new int[n]();
        }

        peso = new int[n];
        rotulos = new std::string[n];

        for (int i = 0; i < n; i++) {
            int id, pV;
            file >> id;

            std::string aux, rotulo_final;
            file >> aux;
            
            // Tratamento robusto para nomes entre aspas e com espaços
            if (aux.front() == '"') {
                rotulo_final = aux;
                while (rotulo_final.back() != '"' && file >> aux) {
                    rotulo_final += " " + aux;
                }
                if (rotulo_final.size() >= 2) {
                    rotulo_final = rotulo_final.substr(1, rotulo_final.size() - 2);
                }
            } else {
                rotulo_final = aux;
            }

            file >> pV;
            if (id >= 0 && id < n) {
                rotulos[id] = rotulo_final;
                peso[id] = pV;
            }
        }

        int numA;
        if (file >> numA) {
            int u, v, pA;
            for (int a = 0; a < numA; a++) {
                if (file >> u >> v >> pA) {
                    // Valida limites e insere na matriz
                    if (u >= 0 && u < n && v >= 0 && v < n && pA >= 1 && pA <= 100) {
                        if (adj[u][v] == 0) this->m++;
                        adj[u][v] = pA;
                    }
                }
            }
        }
    }

    file.close();
    std::cout << "Arquivo lido com sucesso! Vertices: " << n << " | Arestas validas: " << m << "\n";
}

// Opção b: Gravar dados no arquivo grafo.txt
// Escreve no mesmo formato que o readfile lê, então o arquivo gerado pode
// ser carregado de novo sem perda de informação.
void graph_utils::writefile(const char *arquivo) {
    if (n == 0 || adj == nullptr) {
        std::cout << "Grafo vazio na memoria. Nada para salvar.\n";
        return;
    }
    std::ofstream file(arquivo);
    if (!file.is_open()) {
        std::cout << "ERRO: Nao foi possivel abrir o arquivo para gravacao.\n";
        return;
    }
    // Tipo 6 = grafo orientado com peso nas arestas.
    file << "6\n";
    file << n << "\n";

    // O nome é gravado entre aspas para que nomes com espaço sejam lidos
    // corretamente pelo readfile.
    for (int i = 0; i < n; i++) {
        file << i << " \"" << rotulos[i] << "\" " << peso[i] << "\n";
    }

    // Percorre a matriz inteira e grava só as posições com peso > 0,
    // ou seja, as arestas que realmente existem.
    file << m << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] > 0) {
                file << i << " " << j << " " << adj[i][j] << "\n";
            }
        }
    }

    file.close();
    std::cout << "Dados salvos com sucesso no arquivo " << arquivo << "!\n";
}

// Opção c: Inserir vértice
// Como a matriz tem tamanho fixo, não dá para "aumentar" ela. A solução é
// criar uma matriz nova (n+1) x (n+1), copiar os valores antigos e liberar
// a antiga -> O novo vértice recebe o índice n (última linha/coluna).
void graph_utils::insertV(int pesoV, std::string nomeJogo) {
    int new_n = n + 1;

    // Nova matriz zerada: a última linha e coluna ficam em 0, pois o
    // vértice novo ainda não tem arestas.
    int **new_adj = new int*[new_n];
    for(int r = 0; r < new_n; r++) {
        new_adj[r] = new int[new_n];
        for(int c = 0; c < new_n; c++) {
            new_adj[r][c] = 0;
        }
    }

    // Copia a parte n x n antiga para o canto superior esquerdo da nova
    // matriz e já libera cada linha antiga depois de copiada.
    for(int r = 0; r < n; r++) {
        for(int t = 0; t < n; t++) {
            new_adj[r][t] = adj[r][t];
        }
        delete [] adj[r];
    }
    delete [] adj;
    adj = new_adj;

    // Mesma ideia para os vetores de peso e rótulo: copia e adiciona o
    // novo vértice na última posição.
    int *new_peso = new int[new_n];
    std::string *new_rotulos = new std::string[new_n];

    for(int k = 0; k < n; k++) {
        new_peso[k] = peso[k];
        new_rotulos[k] = rotulos[k];
    }
    new_peso[n] = pesoV;
    new_rotulos[n] = nomeJogo.empty() ? ("Jogo " + std::to_string(n)) : nomeJogo;

    delete [] peso;
    delete [] rotulos;

    peso = new_peso;
    rotulos = new_rotulos;

    n = new_n;
}

// Opção d: Inserir aresta
// Grafo orientado: grava só adj[v][w] (v -> w), não adj[w][v].
void graph_utils::insertA(int v, int w, int pAresta) {
    if (v < 0 || v >= n || w < 0 || w >= n) {
        std::cout << "ERRO: IDs de vertices invalidos!\n";
        return;
    }
    
    // Validação solicitada pelo professor: Similaridade deve estar entre 1 e 100
    if (pAresta < 1 || pAresta > 100) {
        std::cout << "ERRO: Peso/Similaridade invalido! Informe um valor entre 1 e 100.\n";
        return;
    }

    if (adj[v][w] == 0) {
        m++; // Incrementa o contador apenas se for uma nova aresta
    }
    adj[v][w] = pAresta;
    std::cout << "Aresta (" << v << " -> " << w << ") inserida/atualizada com peso " << pAresta << "%.\n";
}

// Opção e: Remover vértice
// Cria uma matriz (n-1) x (n-1) copiando tudo menos a linha v e a coluna v.
// Remover a linha/coluna apaga junto todas as arestas que saíam ou
// chegavam em v. Os vértices depois de v "descem" um índice.
void graph_utils::removeV(int v) {
    if (v < 0 || v >= n) {
        std::cout << "ERRO: ID de vertice invalido!\n";
        return;
    }

    // 1. Desconta do contador 'm' todas as arestas ligadas a este vértice (entrantes e saindo)
    for (int i = 0; i < n; i++) {
        if (adj[v][i] > 0) m--; // Aresta saindo de v
        if (i != v && adj[i][v] > 0) m--; // Aresta entrando em v
    }

    int new_n = n - 1;

    // Caso de borda: Remover o último vértice do grafo (Permitir n = 0)
    if (new_n == 0) {
        for (int i = 0; i < n; i++) delete [] adj[i];
        delete [] adj;
        delete [] peso;
        delete [] rotulos;

        adj = nullptr;
        peso = nullptr;
        rotulos = nullptr;
        n = 0;
        m = 0;
        std::cout << "Ultimo vertice removido. O grafo agora esta vazio (n = 0, m = 0).\n";
        return;
    }

    // Criar novas estruturas redimensionadas
    int **new_adj = new int*[new_n];
    for (int i = 0; i < new_n; i++) {
        new_adj[i] = new int[new_n]();
    }

    int *new_p = new int[new_n];
    std::string *new_r = new std::string[new_n];

    int new_i = 0;
    for (int i = 0; i < n; i++) {
        if (i == v) continue;

        int new_j = 0;
        for (int j = 0; j < n; j++) {
            if (j == v) continue;
            new_adj[new_i][new_j] = adj[i][j];
            new_j++;
        }
        new_p[new_i] = peso[i];
        new_r[new_i] = rotulos[i];
        new_i++;
    }

    // Desalocar estrutura antiga
    for (int i = 0; i < n; i++) delete [] adj[i];
    delete [] adj;
    delete [] peso;
    delete [] rotulos;

    // Atualizar ponteiros e tamanho
    adj = new_adj;
    peso = new_p;
    rotulos = new_r;
    n = new_n;

    std::cout << "Vertice " << v << " removido com sucesso! Novo total: " << n << " vertices e " << m << " arestas.\n";
}

void graph_utils::removeLastV() {
    if(n == 0){
        std::cout << "ERRO: Grafo vazio.\n";
        return;
    }
    std::cout << "Removendo o ultimo vertice (ID " << (n - 1) << " - " << rotulos[n - 1] << ")...\n";

    // Remove a última posição do Grafo
    removeV(n - 1);
}

// Opção f: Remover aresta
// Remover a aresta v -> w é só zerar a posição na matriz. Só decrementa m
// se a aresta existia, para o contador não ficar errado.
void graph_utils::removeA(int v, int w) {
    if(v >= 0 && v < n && w >= 0 && w < n) {
        if(adj[v][w] != 0) {
            adj[v][w] = 0;
            m--;
        }
    }
}

// Opção g: Mostrar conteúdo do arquivo
void graph_utils::showFileContent() {
    std::ifstream file("src/grafos.txt");

    if (!file.is_open()) {
        std::cout << "ERRO: Nao foi possivel abrir o arquivo 'grafos.txt' no disco.\n";
        std::cout << "Certifique-se de que o arquivo existe na pasta do projeto.\n";
        return;
    }

    std::cout << "\n=======================================================\n";
    std::cout << "         CONTEUDO BRUTO DO ARQUIVO (grafos.txt)        \n";
    std::cout << "=======================================================\n";

    std::string linha;
    while (std::getline(file, linha)) {
        std::cout << linha << "\n";
    }

    file.close();
    std::cout << "=======================================================\n";
}

// Opção h: Mostrar grafo (Matriz de Adjacência)
void graph_utils::printGraph() {
    if (n == 0 || adj == nullptr) {
        std::cout << "O grafo esta vazio! Leia o arquivo primeiro (Opcao 1).\n";
        return;
    }

    std::cout << "\n=======================================================\n";
    std::cout << "            MATRIZ DE ADJACENCIA DO GRAFO              \n";
    std::cout << "=======================================================\n\n";

    // Cabeçalho com os índices das colunas; depois cada linha i mostra
    // os pesos das arestas que saem do vértice i.
    std::cout << "      ";
    for (int j = 0; j < n; j++) {
        std::cout << "[" << j << "]\t";
    }
    std::cout << "\n";

    for (int i = 0; i < n; i++) {
        std::cout << "[" << i << "]\t";
        for (int j = 0; j < n; j++) {
            std::cout << adj[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n=======================================================\n";
}

// Opção i: Apresentar a conexidade do grafo e o reduzido
// Classificação:
//   C3 - fortemente conexo
//   C2 - unilateralmente conexo
//   C1 - fracamente conexo
//   C0 - desconexo
// Também monta o grafo reduzido (condensação): cada componente fortemente
// conexa vira um único vértice. Os parâmetros são por referência, então
// quem chama recebe a matriz reduzida e o número de componentes.
graph_utils::Connexity graph_utils::showConnectivity(int** &reduzida, int &quant_areas) {
    if (n == 0) {
        quant_areas = 0;
        reduzida = nullptr;
        return C0;
    }

    // Alocação da matriz de alcance (reach)
    // reach[u][v] == true significa que existe um caminho de u até v.
    // O "()" no new inicializa todas as posições com false.
    bool** reach = new bool*[n];
    for (int i = 0; i < n; i++) {
        reach[i] = new bool[n]();
    }

    // Preenchimento via Busca em Largura (BFS)
    // Roda uma BFS a partir de cada vértice u; todo vértice visitado nessa
    // busca é alcançável a partir de u. A fila é um vetor simples:
    // "start" aponta para o próximo a ser processado e "end" para a
    // próxima posição livre (fila vazia quando start == end). Como cada
    // vértice entra no máximo uma vez, n posições são suficientes.
    for (int u = 0; u < n; u++) {
        int* line = new int[n];
        int start = 0, end = 0;

        line[end++] = u;
        reach[u][u] = true; // todo vértice alcança a si mesmo

        while (start < end) {
            int pointer = line[start++]; // retira o primeiro da fila
            for (int next = 0; next < n; next++) {
                // Segue só a direção da aresta (pointer -> next). A própria
                // linha reach[u] funciona como vetor de "visitados".
                if (adj[pointer][next] != 0 && !reach[u][next]) {
                    reach[u][next] = true;
                    line[end++] = next;
                }
            }
        }
        delete[] line;
    }

    // Montagem do Grafo Reduzido
    // areas[v] guarda o número da componente fortemente conexa de v
    // (-1 = ainda sem componente).
    int* areas = new int[n];
    for (int idx = 0; idx < n; idx++) areas[idx] = -1;

    // Cada vértice ainda sem componente abre uma componente nova ("atual").
    // Todos os vértices c que alcançam var e são alcançados por ele
    // (ida e volta) pertencem à mesma componente fortemente conexa.
    int atual = 0;
    for (int var = 0; var < n; var++) {
        if (areas[var] == -1) {
            areas[var] = atual;
            for (int c = var + 1; c < n; c++) {
                if (reach[var][c] && reach[c][var]) {
                    areas[c] = atual;
                }
            }
            atual++;
        }
    }
    quant_areas = atual;    

    // Matriz do grafo reduzido (quant_areas x quant_areas). Para cada aresta
    // a -> b do grafo original que liga componentes diferentes, marca 1 na
    // aresta componente(a) -> componente(b). Arestas dentro da mesma
    // componente são ignoradas (não geram laço). O resultado é sempre um
    // grafo sem ciclos (DAG). Quem chama é responsável por liberar "reduzida".
    reduzida = new int*[quant_areas];
    for (int p = 0; p < quant_areas; p++) {
        reduzida[p] = new int[quant_areas]();
    }
    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            if (adj[a][b] != 0 && areas[a] != areas[b]) {
                reduzida[areas[a]][areas[b]] = 1; 
            }
        }
    }
    delete[] areas;

    // Verificação de C3 (Fortemente Conexo)
    // Basta um par (x, y) sem caminho em algum dos dois sentidos para não
    // ser C3. A condição "&& C3true" no for externo encerra a busca cedo.
    bool C3true = true;
    for (int x = 0; x < this->n && C3true; x++) {
        for (int y = 0; y < this->n; y++) {
            if (x != y && (!reach[x][y] || !reach[y][x])) {
                C3true = false;
                break;
            }
        }
    }

    // Verificação de C2 (Unilateralmente Conexo)
    // Só é testado se não for C3. Aqui basta um dos sentidos: falha se
    // existir um par onde nem x alcança y nem y alcança x.
    bool C2true = true;
    if (!C3true) {
        for (int x = 0; x < this->n && C2true; x++) {
            for (int y = 0; y < this->n; y++) {
                if (x != y && !(reach[x][y] || reach[y][x])) {
                    C2true = false;
                    break;
                }
            }
        }
    }

    // Desalocação garantida da matriz reach
    for (int d = 0; d < n; d++) {
        delete[] reach[d];
    }
    delete[] reach;

    // Retornos diretos se for C3 ou C2
    if (C3true) return C3;
    if (C2true) return C2;

    // Checagem de C1 (Fracamente Conexo)
    // Uma única BFS a partir do vértice 0, mas tratando o grafo como não
    // orientado: pode andar por uma aresta em qualquer direção
    // (adj[pointer][next] OU adj[next][pointer]). Se a busca visitar todos
    // os vértices, o grafo é fracamente conexo; senão, é desconexo (C0).
    bool* list_vertices_passados = new bool[n]();
    int* line = new int[n];
    int start = 0, end = 0;

    list_vertices_passados[0] = true;
    line[end++] = 0;

    while (start < end) {
        int pointer = line[start++];
        for (int next = 0; next < n; next++) {
            if ((adj[pointer][next] != 0 || adj[next][pointer] != 0) && !list_vertices_passados[next]) {
                list_vertices_passados[next] = true; 
                line[end++] = next;
            }
        }
    }   

    bool C1true = true;
    for (int idx = 0; idx < n; idx++) {
        if (!list_vertices_passados[idx]) {
            C1true = false;
            break;
        }
    }
    delete[] list_vertices_passados;
    delete[] line;

    return C1true ? C1 : C0;  
}

// Funcionalidade Principal: Recomendador de Jogos
// As recomendações de um jogo v são os seus vizinhos diretos, ou seja, as
// arestas que saem de v (linha v da matriz). O peso da aresta é mostrado
// como a porcentagem de similaridade entre os jogos.
void graph_utils::recomendar(int v) {
    if (v < 0 || v >= n) {
        std::cout << "ID de jogo invalido!\n";
        return;
    }

    std::cout << "\n=======================================================\n";
    std::cout << " RECOMENDACOES PARA: " << rotulos[v] << "\n";
    std::cout << "=======================================================\n";

    bool encontrou = false;
    for (int i = 0; i < n; i++) {
        if (adj[v][i] > 0) {
            std::cout << " -> " << rotulos[i] << " | Similaridade: " << adj[v][i] << "%\n";
            encontrou = true;
        }
    }

    if (!encontrou) {
        std::cout << " Nenhuma conexao de similaridade encontrada para este jogo.\n";
    }
}

void graph_utils::pageRank() {
    return;
}

void graph_utils::grauVertices() {
    // Para cada vertice
    for (int i = 0; i < this->n; i++) {
        int saida = 0;
        int entrada = 0;

        // Percorrer toda a lista vertical e horizontal
        for (int j = 0; j < this->n; j++) {
            if (this->adj[i][j]) saida++;
            if (this->adj[j][i]) entrada++;
        }

        std::cout << std::left;
        std::cout << "    Vertice " << i << " (" << this->rotulos[i] << "):" << std::endl;
        std::cout << "    Grau de saida: " << std::setw(5) << saida;
        std::cout << "    Grau de entrada: " << std::setw(5) << entrada;
        std::cout << "    Grau total: " << std::setw(5) << saida + entrada << std::endl;
        std::cout << std::endl;
    }
}

void graph_utils::cliques() {
    return;
}

bool _lerInteiro(int &valor) {
    if (std::cin >> valor) return true;

    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
    std::cout << "Entrada invalida. Informe um numero inteiro.\n";
    return false;
}

void graph_utils::floyd() {
    if (this->n == 0) {
        std::cout << "Grafo vazio. Carregue ou insira vertices antes de executar Floyd.\n";
        return;
    }

    // Custo = 101 - similaridade (entre 1 e 100 por aresta)
    const int INF = INT_MAX;
    std::vector<std::vector<int>> dist(this->n, std::vector<int>(this->n, INF));
    std::vector<std::vector<int>> proximo(this->n, std::vector<int>(this->n, -1));

    for (int i = 0; i < this->n; i++) {
        dist[i][i] = 0;
        proximo[i][i] = i;
        for (int j = 0; j < this->n; j++) {
            // adj = 0   -> Sem aresta
            // adj = 100 -> Custo 1
            if (i != j && this->adj[i][j] != 0) {
                dist[i][j] = 101 - this->adj[i][j];
                proximo[i][j] = j;
            }
        }
    }

    // Algoritimo de Floyd
    for (int k = 0; k < this->n; k++) {
        for (int i = 0; i < this->n; i++) {
            if (dist[i][k] == INF) continue;

            for (int j = 0; j < this->n; j++) {
                if (dist[k][j] == INF) continue;

                if (dist[i][k] > INT_MAX - dist[k][j]) continue;
                int custo = dist[i][k] + dist[k][j];

                // Atualiza o custo e o caminho apenas se houver melhora
                if (custo < dist[i][j]) {
                    dist[i][j] = custo;
                    proximo[i][j] = proximo[i][k];
                }
            }
        }
    }

    std::cout << "\nFloyd: custo de cada aresta = 101 - similaridade.\n";
    while (true) {
        std::cout << "\n1. Consultar caminho minimo\n"
                  << "2. Mostrar matriz de custos minimos\n"
                  << "0. Voltar ao menu principal\n"
                  << "Escolha uma opcao: ";
        int opcao;
        if (!_lerInteiro(opcao)) return;

        switch (opcao) {
            case 1: {
                int origem;
                int destino;

                // Le origem
                std::cout << "ID da origem (0 a " << this->n - 1 << "): ";
                if (!_lerInteiro(origem)) return;

                // Le destino
                std::cout << "ID do destino (0 a " << this->n - 1 << "): ";
                if (!_lerInteiro(destino)) return;

                // Vertices invalidos
                if (origem < 0 || origem >= this->n || destino < 0 || destino >= this->n) {
                    std::cout << "IDs de vertices invalidos.\n";
                    continue;
                }

                // Caminho inexistente
                if (proximo[origem][destino] == -1) {
                    std::cout << "Nao existe caminho de " << origem << " para " << destino << ".\n";
                    continue;
                }

                // Caso tenha caminho possivel
                std::cout << "Caminho minimo: ";

                int atual = origem;
                std::cout << atual << " (" << this->rotulos[atual] << ")";

                while (atual != destino) {
                    atual = proximo[atual][destino];
                    std::cout << " -> " << atual << " (" << this->rotulos[atual] << ")";
                }

                std::cout << "\nCusto total: " << dist[origem][destino] << "\n";
                break;
            }

            case 2: {
                // Calcula largura para os indices
                int largura = static_cast<int>(std::to_string(this->n - 1).size()) + 2;

                // Ajusta largura para os custos
                for (const auto &linha : dist) {
                    for (int custo : linha) {
                        if (custo != INF) {
                            int tamanho = static_cast<int>(std::to_string(custo).size()) + 2;
                            if (tamanho > largura) largura = tamanho;
                        }
                    }
                }

                // Garante largura minima
                if (largura < 5) largura = 5;
                std::cout << "\nCustos minimos (linha = origem, coluna = destino; INF = sem caminho):\n";

                // Mostra IDs dos destinos
                std::cout << std::setw(largura) << "ID";
                for (int j = 0; j < this->n; j++) std::cout << std::setw(largura) << j;
                std::cout << '\n';

                // Mostra custos por origem
                for (int i = 0; i < this->n; i++) {
                    std::cout << std::setw(largura) << i;

                    for (int j = 0; j < this->n; j++) {
                        if (dist[i][j] == INF) std::cout << std::setw(largura) << "INF";
                        else std::cout << std::setw(largura) << dist[i][j];
                    }

                    std::cout << '\n';
                }
                break;
            }

            case 0:
                return;

            default:
                std::cout << "Opcao invalida.\n";
                break;
        }
    }
}

void graph_utils::Kruskal() {
    return;
}