/*
===============================================================================
 Projeto : LYNKIE - Sistema Recommend-a-Game (Teoria dos Grafos)

 Autores :
 - Andre Doerner Duarte - 10427938
 - Matheus Leonardo Cardoso Kroeff - 10426434
 - Naoto Ushizaki - 10437445

 Síntese do conteúdo:
   Programa principal da aplicação. Apresenta um menu em loop que permite
   manipular o grafo de jogos (classe graph_utils), representado por matriz
   de adjacência, orientado e com peso nas arestas (tipo 6). Cada vértice é
   um jogo e cada aresta u -> v indica a similaridade (%) entre os jogos.
   Opções do menu:
     a) ler o grafo do arquivo grafos.txt
     b) gravar o grafo no arquivo grafos.txt
     c) inserir vértice (novo jogo)
     d) inserir aresta (nova similaridade)
     e) remover vértice
     e2) remover último vértice
     f) remover aresta
     g) mostrar o conteúdo do grafo (jogos e conexões)
     h) mostrar a matriz de adjacência
     i) apresentar a conexidade (C0 a C3) e o grafo reduzido
     10) recomendador de jogos (funcionalidade principal)
     j) encerrar a aplicação
   Contém também a função auxiliar conexidadeParaTexto, que converte a
   categoria de conexidade (enum Connexity) em texto.

 Histórico de alterações:
 -----------------------------------------------------------------------------
  Data        | Autor           | Commit   | Descrição
 -----------------------------------------------------------------------------
  12/09/2026  | mackcoder       | 6ee807c  | Project e Relatorio criados
  14/09/2026  | Matheus-Kroeff  | 6a7abbb  | Update graph_utils.cpp
  23/09/2026  | Matheus-Kroeff  | 95d655f  | Update graph_utils.cpp
  23/09/2026  | Matheus-Kroeff  | ac65e1e  | Refactor graph_utils class and
              |                 |          | update header guards
  23/09/2026  | Matheus-Kroeff  | 19bedd6  | Implement main function for graph
              |                 |          | recommendation system
  23/09/2026  | Matheus-Kroeff  | 070b3fa  | Update graph_utils.cpp
  23/09/2026  | Matheus-Kroeff  | 3c34408  | Update graph_utils.cpp
  23/09/2026  | Matheus-Kroeff  | f434e7a  | Add grafos.txt with game and edge
              |                 |          | data
  23/09/2026  | Matheus-Kroeff  | 3b21226  | Create gerar_grafo.py
  24/09/2026  | Matheus-Kroeff  | 8dbc72d  | Update gerar_grafo.py
  24/09/2026  | Matheus-Kroeff  | 82a728a  | testando
  24/09/2026  | Matheus-Kroeff  | 08386aa  | ta funcionando, to tentando fazer a
              |                 |          | criação do arquivo, passei tudo do
              |                 |          | meu vscode para aqui agora
  24/09/2026  | Matheus-Kroeff  | b4a75cf  | Create games.json
  24/09/2026  | Matheus-Kroeff  | ce78a7e  | Update games.json
  24/09/2026  | Matheus-Kroeff  | e9a4f04  | Update games.json
  24/09/2026  | Matheus-Kroeff  | 725435d  | Update games.json
  24/09/2026  | Matheus-Kroeff  | dee10c5  | teste com mais vertices
  24/09/2026  | Matheus-Kroeff  | 8f9e082  | Identificação do grupo em todos os
              |                 |          | arquivos
  24/09/2026  | Matheus-Kroeff  | f025ad5  | Update games.json
  24/09/2026  | mackcoder       | 13c358d  | Refactor showConnectivity to return
              |                 |          | connexity
  24/09/2026  | mackcoder       | bcb3f92  | Implement connectivity text
              |                 |          | conversion and update case
  24/09/2026  | mackcoder       | 76ed26e  | Modify showConnectivity to return
              |                 |          | Connexity type
  24/09/2026  | Matheus-Kroeff  | dde31b9  | Enhance documentation and comments
              |                 |          | in gerar_grafo.py
  25/09/2026  | Matheus-Kroeff  | d7043a0  | conexidade
  25/09/2026  | Matheus-Kroeff  | afdf147  | grafos.txt atualizado
  27/09/2026  | dedeDuarte      | c861f27  | Domentários expplicando código
  27/09/2026  | dedeDuarte      | 8c039e5  | Tratamento caso entrada de caractere inválidos,
              |                 |          | como 'a' -> 'Z'
  27/09/2026  | dedeDuarte      | cece91e  | Códigos compilados removidos do repositório
  27/09/2026  | dedeDuarte      | 44879b7  | Makefile e .gitignore adicionados
  27/09/2026  | dedeDuarte      | 76339d2  | README adicionados e completo com:
              |                 |          | 1. Como rodar com make
              |                 |          | 2. Como rodar sem make
              |                 |          | 3. Como usar
              |                 |          | 4. O que cada arquivo faz
  27/09/2026  | dedeDuarte      | c54a8eb  | Agora programa consegue achar arquivo dentro e fora de src/

 -----------------------------------------------------------------------------
===============================================================================
*/

#include <fstream>
#include <iostream>
#include <string>
#include "graph_utils.h"

std::string conexidadeParaTexto(graph_utils::Connexity c){
    switch(c){
        case graph_utils::C0: return "Desconexo";
        case graph_utils::C1: return "Fracamente conexo";
        case graph_utils::C2: return "Unilateralmente conexo";
        case graph_utils::C3: return "Fortemente conexo";
        default: return "Desconhecido";
    }
}

int main() {
    graph_utils grafo(0);
    int opcao = 0;
    std::string arquivo = "grafos.txt";
    if (!std::ifstream(arquivo) && std::ifstream("src/grafos.txt")) {
        arquivo = "src/grafos.txt";
    }

    std::cout << "==========================================================="  << std::endl;
    std::cout << "   SYSTEM RECOMMEND-A-GAME (TEORIA DOS GRAFOS)             "  << std::endl;
    std::cout << "===========================================================\n" << std::endl;

    do {
        std::cout << "MENU DE OPCOES:" << std::endl;
        std::cout << "====================================================="    << std::endl;
        std::cout << "1.  a)  Ler dados do arquivo grafos.txt"                  << std::endl;
        std::cout << "2.  b)  Gravar dados no arquivo grafos.txt"               << std::endl;
        std::cout << "3.  c)  Inserir vertice (Novo Jogo)"                      << std::endl;
        std::cout << "4.  d)  Inserir aresta (Nova Similaridade)"               << std::endl;
        std::cout << "5.  e)  Remover vertice"                                  << std::endl;
        std::cout << "6.  e2) Remover ultimo vertice"                           << std::endl;
        std::cout << "7.  f)  Remover aresta"                                   << std::endl;
        std::cout << "8.  g)  Mostrar conteudo do arquivo"                      << std::endl;
        std::cout << "9.  h)  Mostrar grafo (Matriz de Adjacencia)"             << std::endl;
        std::cout << "10. i)  Apresentar a conexidade do grafo e o reduzido"    << std::endl;
        std::cout << "11. FUNCIONALIDADE: Recomendador de Jogos"                << std::endl;
        std::cout                                                               << std::endl;
        std::cout << "12. Recomendação personalizada (PageRank)"                << std::endl;
        std::cout << "13. Analisar grau dos vértices"                           << std::endl;
        std::cout << "14. Encontrar cliques"                                    << std::endl;
        std::cout << "15. Caminhos mínimos (Floyd)"                             << std::endl;
        std::cout << "16. Árvore geradora mínima (Kruskal)"                     << std::endl;
        std::cout                                                               << std::endl;
        std::cout << "0.  j)  Encerrar a aplicacao"                             << std::endl;
        std::cout << "====================================================="    << std::endl;
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1: // a) Ler dados do arquivo
                grafo.readfile(arquivo.c_str());
                break;

            case 2: // b) Gravar dados no arquivo
                grafo.writefile(arquivo.c_str());
                break;

            case 3: { // c) Inserir vértice
                std::string nome;
                std::cout << "Digite o nome do novo jogo: ";
                std::cin.ignore();
                std::getline(std::cin, nome);
                grafo.insertV(0, nome);
                std::cout << "Jogo '" << nome << "' inserido no grafo!\n";
                break;
            }

            case 4: { // d) Inserir aresta
                int u, v, pA;
                std::cout << "ID Origem: "; std::cin >> u;
                std::cout << "ID Destino: "; std::cin >> v;
                std::cout << "Peso da Similaridade (1 a 100): "; std::cin >> pA;
                grafo.insertA(u, v, pA);
                std::cout << "Conexao de similaridade inserida entre " << u << " e " << v << "!\n";
                break;
            }

            case 5: { // e) Remover vértice
                int id;
                std::cout << "Digite o ID do vertice/jogo a remover: ";
                std::cin >> id;
                grafo.removeV(id);
                std::cout << "Vertice " << id << " removido do grafo.\n";
                break;
            }

            case 6: { // e2) Remover último vértice
                grafo.removeLastV();
                break;

            }

            case 7: { // f) Remover aresta
                int u, v;
                std::cout << "ID Origem: "; std::cin >> u;
                std::cout << "ID Destino: "; std::cin >> v;
                grafo.removeA(u, v);
                std::cout << "Aresta entre " << u << " e " << v << " removida.\n";
                break;
            }

            case 8: // g) Mostrar conteúdo do arquivo
                grafo.showFileContent();
                break;

            case 9: // h) Mostrar grafo
                grafo.printGraph();
                break;

            case 10: {// i) Conexidade
                int** reduzida;
                int quant_areas;
                graph_utils::Connexity resultado = grafo.showConnectivity(reduzida, quant_areas);
                
                std::cout << "Categoria: C" << resultado << " (" << conexidadeParaTexto(resultado) << ")" << std::endl;
                std::cout << "\nGrafo Reduzido: " << quant_areas << "areas:" << std::endl;
                
                for(int i = 0; i < quant_areas; i++){
                    for(int j = 0; j < quant_areas; j++){
                        std::cout << reduzida[i][j] << " ";
                    }
                    std::cout << std::endl;
                }

                // libera a memoria da matriz reduzida
                for(int i = 0; i < quant_areas; i++)
                    delete[] reduzida[i];
                delete[] reduzida;

                break;
            }
            case 11: { // Funcionalidade Principal
                int id;
                std::cout << "Digite o ID do jogo escolhido (0 a " << grafo.getNumV() - 1 << "): ";
                std::cin >> id;
                grafo.recomendar(id);
                break;
            }

            case 12:
                grafo.pageRank();
                break;

            case 13:
                grafo.grauVertices();
                break;

            case 14:
                grafo.cliques();
                break;

            case 15:
                grafo.floyd();
                break;

            case 16:
                grafo.Kruskal();
                break;

            case 0: // j) Encerrar a aplicação
                std::cout << "Encerrando a aplicacao...\n";
                break;

            default: {
                if (std::cin.eof()) {
                    return 0;
                }
                std::cin.clear();
                std::string entradaInvalida;
                std::getline(std::cin, entradaInvalida);
                std::cout << "Opcao invalida! Tente novamente.\n";
                break;
            }
        }
    } while (opcao != 0);

    return 0;
}
