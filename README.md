
# Tester do [jimp2-graphs](https://github.com/yallxe/jimp2-graphs/tree/fe763fa63365c670291d98d80ecb7351f9a6defc)

Konfigurowalny program do testowania projektu ( [yallxe](https://github.com/yallxe) __&&__ [Marcello732](https://github.com/Marcello732) ), [jimp2-graphs](https://github.com/yallxe/jimp2-graphs/tree/fe763fa63365c670291d98d80ecb7351f9a6defc).


## Instalacja

Do kompilacji oraz uruchomienia programu potrzebny będzie [nix-shell](https://nixos.org/download/#nix-install-macos) oraz __make__

W folderze z programem:
```bash
make
```

Należy również na własną rękę pobrać wybrany model w [lmstudio](https://lmstudio.ai/) i włączyć api.
## Uruchamianie

W folderze z programem:

1. Wchodzimy do izolowangeo środowiska:
```bash
nix-shell
```
2. Kompilujemy program do testowania:
```bash
cd jimp2-graphs
make
```

3. Wracamy do folderu z programem testującym:
```bash
cd ..
```

4. Włączamy lmstudio:
```bash
lmstudio
```

5. Uruchamiamy program:
```bash
./bin/graph_test
```
## Przykład

```bash
$> ./bin/graph_test
Testowanie programu jimp2-graphs.


Test 1. Sprawdzanie działalności algorytmu.
        PASSED. Zgodność pliku z założeniami.
        PASSED. Zdjęcie grafu zostało wygenerowane.
        PASSED. Zgodność grafu z założeniami.
        PASSED. Graf jest skierowany.

Test 2. Sprawdzanie reakcji na niepoprawne dane.
        PASSED. Zgodność pliku z założeniami.
        PASSED. Zdjęcie grafu zostało wygenerowane.
        PASSED. Zgodność grafu z założeniami.
        PASSED. Graf jest skierowany.

Test 3. Sprawdzanie reakcji na za dużo krawędzi
        FAILED. Zgodność pliku z założeniami.
                - Niezgodna ilość krawędzi.
        PASSED. Zdjęcie grafu zostało wygenerowane.
        FAILED. Zgodność grafu z założeniami.
                - Niezgodna ilość krawędzi.
        FAILED. Graf jest skierowany.

Test 4. Sprawdzanie funkcjonalności LLM.
Enter prompt for AI: Sending request to http://127.0.0.1:1234/v1/chat/completions
Saving to graph.txt
Saving to graph.png
Graph image saved as graph.png
        FAILED. Zgodność pliku z założeniami.
                - Niezgodna ilość krawędzi.
                - Niezgodna ilość wierzchołków.
        PASSED. Zdjęcie grafu zostało wygenerowane.
        FAILED. Zgodność grafu z założeniami.
                - Nieprawidłowy format wierchołków.
                - Niezgodna ilość krawędzi.
                - Niezgodna ilość wierzchołków.
        FAILED. Graf jest skierowany.


Bardziej szczegółowe informacje zostały zapisane do pliku: logs/log_21.03.2025@17:32.txt

```

#### Przykładowy plik _logs\_[data@czas].txt_

```txt
nazwa pliku: logs/log_21.03.2025@17:32.txt

Test 1. Sprawdzanie działalności algorytmu.
        PASSED. Zgodność pliku z założeniami.
        PASSED. Zdjęcie grafu zostało wygenerowane.
        PASSED. Zgodność grafu z założeniami.
        PASSED. Graf jest skierowany.


--- Szczegóły Testu: Sprawdzanie działalności algorytmu. ---

podane wierzchołki: 4 | oczekiwane wierzchołki: 4
podane krawędzie: 3 | oczekiwane krawędzie: 3
generowane przez ai: false

Macierz Sąsiedztwa:

0 1 1 0
0 0 0 1
0 0 0 0
0 0 0 0

Wygenerowany graf:

4 3
A
B
C
D
A B
A C
B D


##########
##########


Test 2. Sprawdzanie reakcji na niepoprawne dane.
        PASSED. Zgodność pliku z założeniami.
        PASSED. Zdjęcie grafu zostało wygenerowane.
        PASSED. Zgodność grafu z założeniami.
        PASSED. Graf jest skierowany.


--- Szczegóły Testu: Sprawdzanie reakcji na niepoprawne dane. ---

podane wierzchołki: -1 | oczekiwane wierzchołki: 2
podane krawędzie: -1 | oczekiwane krawędzie: 1
generowane przez ai: false

Macierz Sąsiedztwa:

0 1
0 0

Wygenerowany graf:

2 1
A
B
A B


##########
##########


Test 3. Sprawdzanie reakcji na za dużo krawędzi
        FAILED. Zgodność pliku z założeniami.
                - Niezgodna ilość krawędzi.
        PASSED. Zdjęcie grafu zostało wygenerowane.
        FAILED. Zgodność grafu z założeniami.
                - Niezgodna ilość krawędzi.
        FAILED. Graf jest skierowany.


--- Szczegóły Testu: Sprawdzanie reakcji na za dużo krawędzi ---

podane wierzchołki: 2 | oczekiwane wierzchołki: 2
podane krawędzie: 10 | oczekiwane krawędzie: 1
generowane przez ai: false

Macierz Sąsiedztwa:

0 1
0 0

Wygenerowany graf:

2 2
A
B
A B
B A


##########
##########


Test 4. Sprawdzanie funkcjonalności LLM.
        FAILED. Zgodność pliku z założeniami.
                - Niezgodna ilość krawędzi.
                - Niezgodna ilość wierzchołków.
        PASSED. Zdjęcie grafu zostało wygenerowane.
        FAILED. Zgodność grafu z założeniami.
                - Nieprawidłowy format wierchołków.
                - Niezgodna ilość krawędzi.
                - Niezgodna ilość wierzchołków.
        FAILED. Graf jest skierowany.


--- Szczegóły Testu: Sprawdzanie funkcjonalności LLM. ---

podane wierzchołki: 3 | oczekiwane wierzchołki: 3
podane krawędzie: 6 | oczekiwane krawędzie: 6
generowane przez ai: true

Macierz Sąsiedztwa:

1 0 0
0 0 0
0 0 0

Wygenerowany graf:

1 7
,
, ,
, ,
, ,
, ,
, ,
, ,
, ,


##########
##########
```
## Konfiguracja testów

W pliku `config.json`

```json
{
  "api": "http://127.0.0.1:1234",
  "model": "llama-3.2-1b-instruct",
  "tests": [
    {
      "name": "Sprawdzanie działalności algorytmu.",
      "edges": 3,
      "nodes": 4
    },
    {
      "name": "Sprawdzanie reakcji na niepoprawne dane.",
      "nodes": -1,
      "edges": -1,
      "expected_nodes": 2,
      "expected_edges": 1
    },
    {
      "name": "Sprawdzanie reakcji na za dużo krawędzi",
      "nodes": 2,
      "edges": 10,
      "expected_edges": 2
    },
    {
      "name": "Sprawdzanie funkcjonalności LLM.",
      "edges": 6,
      "nodes": 3,
      "ai": true
    }
  ]
}

```

#### Parametry
- __api__ - adres api lmstudio
- __model__ - model do generowania grafu
- __tests__ - lista testów
- __name__ - nazwa testu
- __nodes__ - ilość wierzchołków podawanych do programu
- __edges__ - ilość krawędzi podawanych do programu
- __expected_nodes__ - oczekiwana ilość wierzchołków (opcjonalna wartość)
- __expected_edges__ - oczekiwana ilość krawędzi (opcjonalna wartość)
- __ai__ - true/false czy używać ai do generowania (opcjonalna wartość)