## Dependências

Para compilar o projeto é necessário:

- Compilador de C++ 17
- CMake >=3.0
- Boost >=1.69.0

O repositório contém o Rapidcheck como submódulo.


## Instruções

Para clonar e compilar o repositório, realize:

```
git clone https://github.com/wuerges/iccad2018b.git --recurse-submodules
mkdir build && cd build && cmake ../iccad2018b
make
```