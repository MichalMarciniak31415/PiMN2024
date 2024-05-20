# PiMN2024
Repo z materiałami do przedmiotu "Programowanie i metody numeryczne" na semestr letni 2024


W folderze Z6 i interpolacje znajdują się klasy dostosowane do paczki ImPlota. Żeby z nich skorzystać, należy przygotować ImPlot'a zgodnie z instrukcjami (ImGui_ImPlot_for_students-master.zip), a następnie:
1) Dodać w pliku CMakeLists.txt nowy plik źródłowy .cpp do sekcji "OTHER SOURCES", np:
```
  set(OTHER_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/solver.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/interpolation.cpp
  )
```

Zwróćmy uwagę, że kolejne pliki źródłowe są oddzielane bez przecinków, średników itp.

2) Dodać w main.cpp header do pliku nagłówkowego .h
   
