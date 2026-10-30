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
     11) recomendador de jogos (funcionalidade principal)
     12) recomendação personalizada com PageRank
     13) mostrar graus dos vértices
     14) buscar cliques maximais
     15) consultar caminhos mínimos com Floyd
     16) colorir o grafo sem considerar o sentido das arestas
     17) Euleriano
     
     j) encerrar a aplicação
   Contém também a função auxiliar conexidadeParaTexto, que converte a
   categoria de conexidade (enum Connexity) em texto.
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
        std::cout << "\n  MENU PRINCIPAL\n";
        std::cout << "  -------------------------------------------------------\n";
        std::cout << "   [ Arquivo ]\n";
        std::cout << "     1.  Ler dados do arquivo grafos.txt\n";
        std::cout << "     2.  Gravar dados no arquivo grafos.txt\n";
        std::cout << "     8.  Mostrar conteudo do arquivo\n";
        std::cout << "   [ Edicao do grafo ]\n";
        std::cout << "     3.  Inserir vertice (novo jogo)\n";
        std::cout << "     4.  Inserir aresta (nova similaridade)\n";
        std::cout << "     5.  Remover vertice\n";
        std::cout << "     6.  Remover ultimo vertice\n";
        std::cout << "     7.  Remover aresta\n";
        std::cout << "   [ Visualizacao ]\n";
        std::cout << "     9.  Mostrar grafo (matriz de adjacencia)\n";
        std::cout << "     10. Conexidade do grafo e grafo reduzido\n";

        std::cout << "\n  MANUTENCAO / INFORMACOES ADICIONAIS\n";
        std::cout << "  -------------------------------------------------------\n";
        std::cout << "   [ Recomendacao ]\n";
        std::cout << "     11. Recomendador de jogos\n";
        std::cout << "     12. Recomendacao personalizada (PageRank)\n";
        std::cout << "     15. Caminhos minimos (Floyd)\n";
        std::cout << "   [ Caracteristicas do grafo ]\n";
        std::cout << "     13. Grau dos vertices\n";
        std::cout << "     14. Cliques\n";
        std::cout << "     16. Coloracao\n";
        std::cout << "     17. Percurso euleriano\n";

        std::cout << "\n  -------------------------------------------------------\n";
        std::cout << "     0.  Encerrar a aplicacao\n";
        std::cout << "=========================================================\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;
        if (std::cin.eof()) return 0;

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
                grafo.coloracao();
                break;

            case 17:
                grafo.checkEuleriano();
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
