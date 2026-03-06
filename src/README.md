## Programos paleidimas

Paleidus programą vartotojas turi pasirinkti duomenų įvedimo būdą.

Programa pateiks klausimą:

```
Ivedimas ranka, atsitiktinis ar is failo? (r/a/f):
```

Galimi pasirinkimai:

* **r** – vartotojas pats įveda studentų duomenis
* **a** – programa sugeneruoja atsitiktinius studentų duomenis
* **f** – duomenys nuskaitomi iš failo (`data/studentaiXXXX.txt`)

### 1. Įvedimas ranka (r)

Vartotojas įveda:

* studento pavardę
* studento vardą
* namų darbų pažymius (1–10)
* egzamino pažymį

Įvedus pavardę **0** studentų įvedimas baigiamas.

### 2. Atsitiktinis generavimas (a)

Programa paprašo:

```
Kiek studentu generuoti?
Kiek ND pazymiu generuoti kiekvienam studentui?
```

Tuomet sugeneruojami:

* atsitiktiniai vardai ir pavardės
* atsitiktiniai pažymiai nuo 1 iki 10

### 3. Skaitymas iš failo (f)

Programa nuskaito studentų duomenis iš failo, esančio kataloge:

```
data/studentaiXXXX.txt
```

Failo formatas:

```
Vardas Pavarde ND1 ND2 ND3 ... Egz
```

### Rikiavimas

Po duomenų įvedimo programa paprašo pasirinkti rikiavimo būdą:

```
Rikiuoti pagal:
1 - vardą
2 - pavardę
3 - galutinį balą (vidurkis)
4 - galutinį balą (mediana)
```

### Rezultatų išvedimas

Galiausiai vartotojas pasirenka kur išvesti rezultatus:

```
Isvedimas i ekrana ar i faila? (e/f)
```

* **e** – rezultatai išvedami ekrane
* **f** – rezultatai įrašomi į failą `rezultatai.txt`

Taip pat parodomas programos vykdymo laikas.
