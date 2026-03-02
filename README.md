/**Made by Igor Puścion and Patryk Krajewski**/

1. Opis problemu i celów projektu
  a) Problem:
    Matematyka, zwłaszcza całki oznaczone i wizualizacja funkcji, często sprawia trudności wielu uczniom i studentom. Główne problemy to:
      - Brak możliwości szybkiego wizualizowania funkcji – ręczne rysowanie wykresów jest czasochłonne i podatne na błędy.
      - Trudności ze zrozumieniem całki oznaczonej – uczniowie nie widzą związku między wzorem funkcji a polem pod wykresem.
      - Konieczność ręcznego obliczania całek – żmudne obliczenia mogą zniechęcać do nauki.
      - Brak interaktywności – tradycyjne metody nie pozwalają na szybkie sprawdzanie różnych zakresów całkowania.
  b) Cele projektu:
      - Przystępna prezentacja funkcji: Stworzenie narzędzia, które w prosty sposób przedstawia funkcje matematyczne z automatyczną wizualizacją wykresu.
      - Wsparcie w nauce całek: Oferowanie praktycznej pomocy w rozumieniu całki oznaczonej poprzez wizualizację pola pod wykresem.
      - Szybkie obliczanie wyników: Automatyczne obliczanie całki oznaczonej dla dowolnych granic a i b.
      - Intuicyjny interfejs: Czytelny i przyjazny interfejs z kolorowym rozróżnieniem funkcji i łatwą obsługą.
      - Wielofunkcyjność: Możliwość dodawania wielu funkcji jednocześnie z indywidualnymi ustawieniami.

2. Zastosowane technologie i materiały
  a) Technologie:
      - Język C++: Główny język programowania – wybrany ze względu na wydajność, kontrolę nad pamięcią oraz nasze osobiste doświadczenie.
      - Qt: Framework do tworzenia graficznego interfejsu użytkownika – zapewnia międzyplatformowość i nowoczesny wygląd.
      - Qt Charts: Moduł Qt do rysowania wykresów – użyty do wizualizacji funkcji i obszarów całkowania.
      - tinyexpr: Lekka biblioteka do parsowania i ewaluacji wyrażeń matematycznych – umożliwia wprowadzanie funkcji w formie tekstowej.
      - CMake: System budowania projektu – ułatwia kompilację na różnych platformach.
  b) Materiały:
      - Qt Creator: Środowisko IDE do programowania i debugowania aplikacji.
      - Git Bash: Terminal do zarządzania wersjonowaniem kodu, budowania projektu i wykonywania poleceń systemowych.
      - Dokumentacja techniczna: Oficjalna dokumentacja Qt i Qt Charts – główne źródło wiedzy.

3. Opis procesu realizacji
  a) Planowanie
    Na początku określiliśmy główne cele projektu, takie jak wizualizacja funkcji, obliczanie całek oznaczonych dla zadanych zakresów oraz ich czytelne przedstawienie.
  b) Projektowanie
    Stworzyliśmy wizualizację ogólnego wyglądu aplikacji w programie MS Paint, a następnie zaimplementowaliśmy szablon przy użyciu QLayout.
  c) Dodawanie funkcjonalności
    Krok po kroku dodawaliśmy nowe funkcjonalności, które zaplanowaliśmy na liście w repozytorium GitHub.
  d) Testowanie
    Przetestowaliśmy aplikację w różnych scenariuszach, w tym przy wprowadzaniu danych nieprawidłowych i ekstremalnych.
  e) Dokumentacja
    Na koniec przygotowaliśmy dokumentację projektu, która obejmuje opis problemu, zastosowane technologie, proces realizacji oraz wyniki. Jest to ważne, aby inni użytkownicy mogli zrozumieć, jak działa aplikacja, i ewentualnie ją rozwijać.

4. Wyniki i wnioski
  a) Wyniki:
      - Aplikacja umożliwia użytkownikom dodawanie, usuwanie i wizualizację do 20 funkcji jednocześnie oraz liczenie ich całek oznaczonych dla dowolnego zakresu.
      - Wykresy są wyświetlane w czytelnym, skalowalnym układzie współrzędnych.
      - Interfejs użytkownika jest intuicyjny i responsywny.
  b) Wnioski:
    Projekt pokazuje, że można stworzyć zaawansowaną aplikację edukacyjną przy użyciu dostępnych technologii, która skutecznie wspiera naukę matematyki poprzez intuicyjną wizualizację.
