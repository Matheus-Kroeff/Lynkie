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
  27/09/2026  | dedeDuarte      | cd94721  | Docs: Relatório de commits e alterações
  27/09/2026  | dedeDuarte      | 8c039e5  | Tratamento caso entrada de caractere inválidos,
              |                 |          | como 'a' -> 'Z'
  27/09/2026  | dedeDuarte      | cece91e  | Códigos compilados removidos do repositório
  27/09/2026  | dedeDuarte      | 44879b7  | Makefile e .gitignore adicionados
  27/09/2026  | dedeDuarte      | 76339d2  | README adicionados e completo com:
              |                 |          | 1. Como rodar com make
              |                 |          | 2. Como rodar sem make
              |                 |          | 3. Como usar
              |                 |          | 4. O que cada arquivo faz
  27/09/2026  | dedeDuarte      | 3f54e50  | docs(Relatório de commits): Relatório de commits
              |                 |          | atualizado
  27/09/2026  | dedeDuarte      | c54a8eb  | Agora programa consegue achar arquivo dentro e fora de src/
  27/09/2026  | dedeDuarte      | bcd19b0  | doc: Relatório de commits atualizado
  27/09/2026  | dedeDuarte      | 481a703  | Docs: Nome do projeto alterado (Lykie)
  27/09/2026  | dedeDuarte      | 0c3da29  | Docs: Nome do projeto alterado (LYNKIE)
  16/10/2026  | Matheus-Kroeff  | a2695e0  | Correção do Readfile, tratamento de nomes compostos e
              |                 |          | valida peso de arestas (1-100)
  16/10/2026  | Matheus-Kroeff  | 287e4b7  | Pequenas correções
  15/10/2026  | mackcoder       | a365cdd  | Delete Relatorio_Ativdades/src directory
  15/10/2026  | mackcoder       | 7ce2adf  | Revise README with project details and updates
  15/10/2026  | mackcoder       | db4810e  | Create README for Graph Theory Project Lynkie
  16/10/2026  | Matheus-Kroeff  | 89fc3b5  | Filtro de Indie no python gerador do grafo.txt
  16/10/2026  | Matheus-Kroeff  | 8a61a8b  | Função para remover o ultimo vertice
  20/10/2026  | Matheus-Kroeff  | fc2d873  | Update games.json
  21/10/2026  | Matheus-Kroeff  | 390dd3a  | Aumentando o json
  20/10/2026  | dedeDuarte      | 8ea63ef  | Chore: Preparando espaço para novas funções
  20/10/2026  | dedeDuarte      | 019677e  | Feat(graph): Calculador de grau de vértices adicionado
  20/10/2026  | dedeDuarte      | a03cc0e  | Feat(grauVertices): Agora mostra o nome do jogo
  21/10/2026  | dedeDuarte      | 9102079  | Feat(floyd): Algoritmo de caminhos mínimos adicionado
  21/10/2026  | dedeDuarte      | aaba27c  | Feat(floyd): Melhoria na impressão do caminho mínimo
  21/10/2026  | dedeDuarte      | ee57187  | Feat(pageRank): Recomendação personalizada de jogos
              |                 |          | adicionada
  21/10/2026  | dedeDuarte      | c0ebd7a  | Refactor(graph): Padronização da escrita e
              |                 |          | simplificação dos comentários
  22/10/2026  | dedeDuarte      | 7624c46  | Feat(cliques): Função que identifica cliques Maximais
              |                 |          | implementadas
  22/10/2026  | dedeDuarte      | d1578b6  | Feat(cliques): Simplifica busca e melhora comentarios
              |                 |          | e prints
  23/10/2026  | dedeDuarte      | 78a4eba  | Feat(coloracao): Coloração de grafos implementada
  23/10/2026  | dedeDuarte      | 9ed96fa  | Feat(coloracao): Adiciona opção de listar jogos de
              |                 |          | cada classe

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
        std::cout << "16. Coloração de grafos"                                  << std::endl;
        std::cout                                                               << std::endl;
        std::cout << "0.  j)  Encerrar a aplicacao"                             << std::endl;
        std::cout << "====================================================="    << std::endl;
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
