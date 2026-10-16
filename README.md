# Projeto de Grafos — Lynkie 🎮

> **Disciplina:** Teoria dos Grafos
> **Docente:** Ivan Oliveira
> **Metodologia:** Scrum / Agile

---

## 👥 Integrantes do Grupo

Nome | RA
-----|---
**André Doerner Duarte** | 10427938
**Matheus Leonardo Cardoso Kroeff** | 10426434
**Naoto Ushizaki** | 10437445

---

## 1. 🎯 Introdução

O **Lynkie** é um **sistema de recomendação de jogos indies baseado em grafos**. Ele sugere títulos pela **similaridade de conteúdo** (tags e gêneros), e não pela popularidade ou pelo número de avaliações. Assim, jogos pouco conhecidos podem chegar a jogadores com interesses parecidos.

---

## 2. 💡 O Projeto

### 2.1 Motivação

Jogos indies têm um sério **problema de visibilidade**. Em 2025, mais de **19 mil jogos** foram lançados na Steam, e **quase metade (≈49%) recebeu menos de 10 avaliações** (PLAZA, 2025; TAHA, 2025). Como o algoritmo da Steam favorece jogos com tráfego e engajamento logo após o lançamento, títulos sem orçamento de marketing acabam ignorados.

Recomendadores tradicionais dependem de avaliações, então sofrem do **problema de *cold start***: não conseguem recomendar itens novos ou com pouca interação (JI; SHEN, 2015; GLISOVIC; KRAGIC; TEGNER, 2025). Uma abordagem **baseada em conteúdo** contorna isso.

### 2.2 Objetivo

Desenvolver um sistema que reúna jogos independentes e os **recomende pela similaridade entre seus conteúdos**, facilitando a descoberta de títulos menos conhecidos e ampliando sua visibilidade.

**ODS relacionados:**
- **ODS 8** – Trabalho Decente e Crescimento Econômico: apoia pequenos estúdios e desenvolvedores.
- **ODS 9** – Indústria, Inovação e Infraestrutura: propõe uma modelagem em grafos para sistemas de recomendação.

### 2.3 Como funciona

O sistema tem duas etapas:

1. **Pré-processamento (Python):** o script `gerar_grafo.py` lê um subconjunto do [Steam Games Dataset](https://www.kaggle.com/datasets/fronkongames/steam-games-dataset) (`games.json`), extrai tags e gêneros, calcula a similaridade entre todos os pares de jogos e exporta o grafo para `grafos.txt`.
2. **Análise e recomendação (C++):** a classe `graph_utils` carrega o grafo como **matriz de adjacência** e oferece um menu para editar o grafo, analisar a conexidade e gerar recomendações.

**Modelagem do grafo (tipo 6 – orientado com peso nas arestas):**

| Elemento | Significado |
|----------|-------------|
| **Vértice** | Um jogo (rotulado com o nome) |
| **Aresta u → v** | O jogo *v* é recomendado para quem gostou de *u* |
| **Peso da aresta** | Similaridade entre os jogos (0–100%) |

- **Similaridade:** **coeficiente de Jaccard** sobre o conjunto de tags e gêneros: `J(A,B) = |A ∩ B| / |A ∪ B|`.
- **Limiar:** só entram arestas com **similaridade ≥ 15%**, o que deixa o grafo mais esparso e as recomendações mais relevantes.
- **Grafo atual:** **86 vértices** e **1408 arestas**.

**Funcionalidades principais:**
- 📂 Leitura e gravação do grafo em arquivo (`grafos.txt`)
- ✏️ Inserção e remoção de vértices e arestas
- 🔗 **Conexidade** (C0 a C3) via matriz de alcance (BFS a partir de cada vértice)
- 🧩 **Componentes fortemente conexas** e **grafo reduzido**: cada componente funciona como um *cluster* de jogos parecidos (nichos/subgêneros)
- ⭐ **Recomendação:** lista os vizinhos diretos do jogo escolhido com o grau de similaridade, em O(n)

**Ferramentas:** C++ (g++/GCC), Python 3, VS Code, GDB, Git e GitHub.

---

## 3. 🛠️ Metodologia
O desenvolvimento do projeto será realizado utilizando o **Scrum** como **framework *ágil***, **organizando o trabalho em *Sprints*** e priorizando as funcionalidades por meio do *Product Backlog*. A equipe acompanhará a evolução do projeto por meio dos eventos e responsabilidades definidos pelo Scrum, buscando realizar entregas incrementais e melhorar o processo ao longo do desenvolvimento.

- **Scrum:** Organização do projeto em Sprints, com Product Backlog, Sprint Backlog, acompanhamento e avaliação das entregas.
- **Product Owner:** Responsável por definir e priorizar os requisitos, organizar o Product Backlog e validar se as entregas atendem aos objetivos do projeto.
- **Scrum Master:** Responsável por acompanhar as Sprints, auxiliar na aplicação do Scrum, identificar impedimentos e contribuir para a organização e melhoria do processo.
- **Equipe de Desenvolvimento:** Responsável pela implementação, testes e integração das funcionalidades do sistema.

**Validação:** testes funcionais pelo menu da aplicação. Foram conferidos a contagem de vértices e arestas, a edição do grafo, a gravação e releitura sem perda de dados, a conexidade, o grafo reduzido e a coerência das recomendações com as similaridades calculadas.

---

## 4. 🚀 Conclusão e Expectativas

O Lynkie mostra que a **Teoria dos Grafos** é uma base eficaz para recomendação: ao ligar jogos por **similaridade de conteúdo**, um título indie sem avaliações pode ser recomendado tanto quanto um jogo popular. A análise de **componentes fortemente conexas** também revela agrupamentos naturais de jogos parecidos.

Como próximos passos, esperamos:
- **ampliar a base de jogos** e otimizar a estrutura para grafos maiores;
- explorar **medidas de similaridade assimétricas**, aproveitando o modelo orientado (por exemplo, ponderar pela popularidade do jogo de destino);
- incorporar as **preferências do usuário** às recomendações.

---

## ✉️ Contatos

Fique à vontade para entrar em contato com os membros da equipe para dúvidas, sugestões ou colaborações no projeto:

* **André Doerner Duarte**
  * 📧 E-mail: andredoernerd@gmail.com
  * 💼 [LinkedIn](https://www.linkedin.com/in/andredoernerduarte/)
  * 🐙 [GitHub](https://github.com/DedeDuarte)

* **Matheus Leonardo Cardoso Kroeff**
  * 📧 E-mail: 10426434@mackenzista.com.br
  * 💼 [LinkedIn](https://www.linkedin.com/in/matheus-leonardo-cardoso-kroeff-23838535b/)
  * 🐙 [GitHub](https://github.com/Matheus-Kroeff)

* **Naoto Ushizaki**
  * 📧 E-mail: 10437445@mackenzista.com.br
  * 💼 [LinkedIn](https://www.linkedin.com/in/naoto-ushizaki-30b94a172/)
  * 🐙 [GitHub](https://github.com/mackcoder)

---

## 5. 📚 Referências

* FRONKONGAMES. **Steam Games Dataset**. [S. l.]: Kaggle, 2022. Disponível em: https://www.kaggle.com/datasets/fronkongames/steam-games-dataset. Acesso em: 11 set. 2026.

* GLISOVIC, Natalija; KRAGIC, Danica; TEGNER, Martin. Item cold start in e-commerce recommender systems: a survey. **IEEE Access**, [s. l.], v. 13, p. 164702–164722, 2025. DOI: 10.1109/ACCESS.2025.3611026. Disponível em: https://doaj.org/article/32dd1ad8b4804791aef91d719bb7dc7a. Acesso em: 27 set. 2026.

* JI, Ke; SHEN, Hong. Addressing cold-start: scalable recommendation with tags and keywords. **Knowledge-Based Systems**, [s. l.], v. 83, p. 42–50, jul. 2015. DOI: 10.1016/j.knosys.2015.03.008. Disponível em: https://www.sciencedirect.com/science/article/abs/pii/S0950705115001008. Acesso em: 27 set. 2026.

* PLAZA, William R. Mais de 19 mil jogos foram lançados na Steam em 2025, mas quase metade não tem nem 10 avaliações. **Hardware.com.br**, [s. l.], 23 dez. 2025. Disponível em: https://www.hardware.com.br/noticias/steam-19-mil-jogos-2025-sem-avaliacoes/. Acesso em: 11 set. 2026.

* TAHA. 18K games released on Steam in 2025, half have less than 10 reviews. **MP1st**, 28 nov. 2025. Disponível em: https://mp1st.com/news/18k-games-released-steam-2025-half-have-10-reviews. Acesso em: 12 set. 2026.
