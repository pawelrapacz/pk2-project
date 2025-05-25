# 6. Mapa miasta
Celem projektu jest wyznaczanie najkrótszej trasy pomiędzy dwoma punktami w mieście. Ulice w mieście leżą tylko na linii północ-południe oraz wschód-zachód, jednak w mieście istnieją również ścieżki, po których poruszają się piesi.
<br>
W celu wyznaczenia trasy należy wykorzystać algorytm ***Dijkstry*** wyszukujący najkrótszej ścieżki w grafie. Na wejście wymagane są trzy pliki. Pierwszy zawiera id, nazwę punktu i jego współrzędne, drugi plik zawiera binarną tablicę kwadratową z informacją, czy pomiędzy dwoma punktami znajduje się połączenie (tablica nie jest symetryczna), a trzeci plik zawiera listę tras do wyznaczenia. Każda linijka zawiera jedną trasę w postaci `<punkt początkowy>` `<punkt docelowy>`. Przykładowe pliki:

```
1 Dom 0 10
2 Apteka 10 12
3 Policja 6 7
4 Sklep 11 5
5 Szkoła 1 1
6 Szpital 14 0
```

```
0 1 0 0 0 0
1 0 1 1 0 0
1 1 0 1 1 0
0 1 1 0 1 1
0 0 1 1 0 1
0 0 0 1 1 0
```

```
Dom Szpital
Szpital Dom
```

Odległość pomiędzy punktami wyznaczana jest za pomocą metryki ***euklidesowej*** dla pieszych, a za pomocą metryki ***Manhattan*** dla samochodów.

Wynikiem działania programu jest plik wyjściowy zawierający przebieg wyznaczonej trasy, z podaniem całkowitej odległości oraz poszczególnych punktów trasy, np. trasa dla pieszych:

```
trasa: Dom → Szpital: 23.1001
Dom → Apteka → Sklep → Szpital

trasa: Szpital → Dom: 17.9243
Szpital → Sklep → Policja → Dom
```
Należy wziąć pod uwagę, że może nie istnieć możliwość wyznaczenia zadanej trasy.

Program powinien być uruchamiany z linii poleceń, gdzie są podawane parametry programu (powinna być możliwość podawania dowolnej kolejności parametrów):

 - `-coor` plik wejściowy z współrzędnymi
 - `-tab` plik wejściowy z tablicą połączeń
 - `-q` plik wejściowy z trasami do wyznaczenia
 - `-out` plik wynikowy z wyznaczonymi trasami