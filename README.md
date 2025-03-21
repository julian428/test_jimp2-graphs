# Tester do [jimp2-graphs](https://github.com/yallxe/jimp2-graphs/tree/fe763fa63365c670291d98d80ecb7351f9a6defc)

Konfigurowalny program do testowania projektu ( [yallxe](https://github.com/yallxe) **&&** [Marcello732](https://github.com/Marcello732) ), [jimp2-graphs](https://github.com/yallxe/jimp2-graphs/tree/fe763fa63365c670291d98d80ecb7351f9a6defc).

## Instalacja

Do kompilacji oraz uruchomienia programu potrzebny będzie [nix-shell](https://nixos.org/download/#nix-install-macos) oraz **make**

W folderze z programem:

```bash
make
```

## Uruchamianie

W folderze z programem:

1. Wchodzimy do izolowangeo środowiska:

```bash
nix-shell
```

2. Uruchamiamy program:

```bash
./graph_test
```

## Przykład

```bash
$ > ./graph_test
Test 1. Sprawdzanie działania algorytmu.
    FAILED. Zgodność pliku z założeniami.
        - liczba krawędzi jest niezgodna z założeniami.
        - liczba wierzchołków jest niezgodna z założeniami.
    PASSED. Wszystkie połączenia pomiędzy wierzchołków są możliwe.
    PASSED. Wygenerowane zdjęcie grafu jest zgodne z założeniami.
Test 2. Sprawdzanie funkcjonalności LLM
    FAILED. Nie udało się połączyć z LLM.
    FAILED. Nie udało się otworzyć pliku z grafem.
    FAILED. Nie udało się otworzyć zdjęcia grafu.

Wyniki testów zapisano do pliku:
    logs.txt
```

#### Przykładowy plik _logs.txt_

```txt
19.03.2025 18:30
---
Test 1. Sprawdzanie działania algorytmu.
    FAILED. Zgodność pliku z założeniami.
        - liczba krawędzi jest niezgodna z założeniami.
        - liczba wierzchołków jest niezgodna z założeniami.
    PASSED. Wszystkie połączenia pomiędzy wierzchołków są możliwe.
    PASSED. Wygenerowane zdjęcie grafu jest zgodne z założeniami.
Test 2. Sprawdzanie funkcjonalności LLM
    FAILED. Nie udało się połączyć z LLM.
    FAILED. Nie udało się otworzyć pliku z grafem.
    FAILED. Nie udało się otworzyć zdjęcia grafu.
---

19.03.2025 19:30
---
Test 1. Sprawdzanie działania algorytmu.
    FAILED. Zgodność pliku z założeniami.
        - liczba krawędzi jest niezgodna z założeniami.
        - liczba wierzchołków jest niezgodna z założeniami.
    PASSED. Wszystkie połączenia pomiędzy wierzchołków są możliwe.
    PASSED. Wygenerowane zdjęcie grafu jest zgodne z założeniami.
Test 2. Sprawdzanie funkcjonalności LLM
    PASSED. Udane połączenie z LLM.
    PASSED. Plik z grafem z zgodny z założeniami.
    FAILED. Zdjęcie grafu nie jest zgodne z założeniami.
---
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
      "nodes": 3
    },
    {
      "name": "Sprawdzanne funkcjonalności LLM",
      "eges": 5,
      "nodes": 10,
      "ai": true
    }
  ]
}
```

#### Parametry

- **name** - nazwa testu
- **edges** - ilość wierzchołków
- **nodes** - ilość krawędzi
- **ai** - czy użyć ai do generacji grafu
- **tests** - lista testów
- **model** - nazwa modelu llm
- **api** - adres api modelu llm
