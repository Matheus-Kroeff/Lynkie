# Graph Theory Project — Lynkie 🎮

> **Course:** Graph Theory
> **Professor:** Ivan Oliveira
> **Methodology:** Scrum / Agile

---

## 👥 Team Members

Name | Student ID
-----|---
**André Doerner Duarte** | 10427938
**Matheus Leonardo Cardoso Kroeff** | 10426434
**Naoto Ushizaki** | 10437445

---

## 1. 🎯 Introduction

**Lynkie** is a **graph-based recommendation system for indie games**. It suggests titles by **content similarity** (tags and genres) rather than by popularity or number of reviews. This lets lesser-known games reach players with similar interests.

---

## 2. 💡 The Project

### 2.1 Motivation

Indie games face a serious **visibility problem**. In 2025, more than **19,000 games** were released on Steam, and **almost half (≈49%) received fewer than 10 reviews** (PLAZA, 2025; TAHA, 2025). Steam's algorithm favors games with strong traffic and engagement right after launch, so titles without a marketing budget end up overlooked.

Traditional recommenders rely on reviews and suffer from the **cold-start problem**: they cannot recommend new items or items with few interactions (JI; SHEN, 2015; GLISOVIC; KRAGIC; TEGNER, 2025). A **content-based** approach avoids this.

### 2.2 Goal

Build a system that gathers independent games and **recommends them by content similarity**, making lesser-known titles easier to discover and increasing their visibility.

**Related SDGs:**
- **SDG 8** – Decent Work and Economic Growth: supports small studios and developers.
- **SDG 9** – Industry, Innovation and Infrastructure: proposes a graph-based model for recommendation systems.

### 2.3 How It Works

The system has two stages:

1. **Preprocessing (Python):** the `gerar_grafo.py` script reads a subset of the [Steam Games Dataset](https://www.kaggle.com/datasets/fronkongames/steam-games-dataset) (`games.json`), extracts tags and genres, computes the similarity between every pair of games, and exports the graph to `grafos.txt`.
2. **Analysis and recommendation (C++):** the `graph_utils` class loads the graph as an **adjacency matrix** and provides a menu to edit the graph, analyze connectivity, and generate recommendations.

**Graph model (type 6 – directed, edge-weighted):**

| Element | Meaning |
|---------|---------|
| **Vertex** | A game (labeled with its name) |
| **Edge u → v** | Game *v* is recommended to players who liked *u* |
| **Edge weight** | Similarity between the games (0–100%) |

- **Similarity:** **Jaccard coefficient** over the set of tags and genres: `J(A,B) = |A ∩ B| / |A ∪ B|`.
- **Threshold:** only edges with **similarity ≥ 15%** are kept, which makes the graph sparser and the recommendations more relevant.
- **Current graph:** **86 vertices** and **1,408 edges**.

**Main features:**
- 📂 Read and write the graph from/to a file (`grafos.txt`)
- ✏️ Insert and remove vertices and edges
- 🔗 **Connectivity** classification (C0 to C3) using a reachability matrix (BFS from every vertex)
- 🧩 **Strongly connected components** and **condensed graph**: each component acts as a *cluster* of similar games (niches/subgenres)
- ⭐ **Recommendation:** lists the direct neighbors of the selected game with their similarity score, in O(n)

**Tools:** C++ (g++/GCC), Python 3, VS Code, GDB, Git, and GitHub.

---

## 3. 🛠️ Methodology
The project is developed using **Scrum** as an **agile framework**, **organizing the work into Sprints** and prioritizing features through the *Product Backlog*. The team tracks progress through the events and roles defined by Scrum, aiming for incremental deliveries and continuous process improvement.

- **Scrum:** Project organized into Sprints, with a Product Backlog, Sprint Backlog, and tracking and review of deliverables.
- **Product Owner:** Defines and prioritizes requirements, maintains the Product Backlog, and validates that deliverables meet the project's goals.
- **Scrum Master:** Oversees the Sprints, supports the use of Scrum, identifies impediments, and helps organize and improve the process.
- **Development Team:** Implements, tests, and integrates the system's features.

**Validation:** functional tests through the application menu. We checked the vertex and edge counts, graph editing, saving and reloading without data loss, connectivity classification, the condensed graph, and whether recommendations match the similarities computed during preprocessing.

---

## 4. 🚀 Conclusion and Future Work

Lynkie shows that **Graph Theory** is an effective foundation for recommendation: by linking games through **content similarity**, an indie title with no reviews can be recommended just as easily as a popular one. The analysis of **strongly connected components** also reveals natural clusters of similar games.

As next steps, we plan to:
- **expand the game database** and optimize the data structure for larger graphs;
- explore **asymmetric similarity measures**, taking advantage of the directed model (e.g., weighting by the popularity of the target game);
- incorporate **user preferences** into the recommendations.

---

## ✉️ Contact

Feel free to reach out to the team members with questions, suggestions, or collaboration ideas:

* **André Doerner Duarte**
  * 📧 Email: andredoernerd@gmail.com
  * 💼 [LinkedIn](https://www.linkedin.com/in/andredoernerduarte/)
  * 🐙 [GitHub](https://github.com/DedeDuarte)

* **Matheus Leonardo Cardoso Kroeff**
  * 📧 Email: 10426434@mackenzista.com.br
  * 💼 [LinkedIn](https://www.linkedin.com/in/matheus-leonardo-cardoso-kroeff-23838535b/)
  * 🐙 [GitHub](https://github.com/Matheus-Kroeff)

* **Naoto Ushizaki**
  * 📧 Email: 10437445@mackenzista.com.br
  * 💼 [LinkedIn](https://www.linkedin.com/in/naoto-ushizaki-30b94a172/)
  * 🐙 [GitHub](https://github.com/mackcoder)

---

## 5. 📚 References

* FRONKONGAMES. **Steam Games Dataset**. [S. l.]: Kaggle, 2022. Available at: https://www.kaggle.com/datasets/fronkongames/steam-games-dataset. Accessed: Sep. 11, 2026.

* GLISOVIC, Natalija; KRAGIC, Danica; TEGNER, Martin. Item cold start in e-commerce recommender systems: a survey. **IEEE Access**, v. 13, p. 164702–164722, 2025. DOI: 10.1109/ACCESS.2025.3611026. Available at: https://doaj.org/article/32dd1ad8b4804791aef91d719bb7dc7a. Accessed: Sep. 27, 2026.

* JI, Ke; SHEN, Hong. Addressing cold-start: scalable recommendation with tags and keywords. **Knowledge-Based Systems**, v. 83, p. 42–50, Jul. 2015. DOI: 10.1016/j.knosys.2015.03.008. Available at: https://www.sciencedirect.com/science/article/abs/pii/S0950705115001008. Accessed: Sep. 27, 2026.

* PLAZA, William R. Mais de 19 mil jogos foram lançados na Steam em 2025, mas quase metade não tem nem 10 avaliações. **Hardware.com.br**, Dec. 23, 2025. Available at: https://www.hardware.com.br/noticias/steam-19-mil-jogos-2025-sem-avaliacoes/. Accessed: Sep. 11, 2026.

* TAHA. 18K games released on Steam in 2025, half have less than 10 reviews. **MP1st**, Nov. 28, 2025. Available at: https://mp1st.com/news/18k-games-released-steam-2025-half-have-10-reviews. Accessed: Sep. 12, 2026.
