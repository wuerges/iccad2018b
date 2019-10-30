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
cd iccad2018b && mkdir build && cd build && cmake ..
make
```

## Casos de teste

Os casos de teste usados foram fornecidos pelo contest. 
A tabela a seguir apresenta um resumo dos casos de teste.

| Test case path | Boundary rectangle | Number of layers | Number of tracks | Number of buses | Number of bits in buses | Maximum number of pin shapes | Maximum number of bits per bus | Number of obstacles |
|:----|----:|----:|----:|----:|----:|----:|----:|----:|
| beta_0905/beta_1.input | 874800x26568960 | 3 | 49209 | 34 | 1260 | 2 | 66 | 159 |
| beta_0905/beta_2.input | 874800x26568960 | 3 | 49209 | 26 | 1262 | 2 | 107 | 0 |
| beta_0905/beta_3.input | 4698000x13317120 | 3 | 22732 | 60 | 665 | 2 | 24 | 555108 |
| beta_0905/beta_4.input | 4698000x13317120 | 3 | 22732 | 62 | 698 | 2 | 24 | 0 |
| beta_0905/beta_5.input | 21904440x2843016 | 4 | 54150 | 6 | 1964 | 2 | 449 | 0 |
| beta_0912/beta_1.input | 874800x26568960 | 3 | 49209 | 34 | 1260 | 2 | 66 | 159 |
| beta_0912/beta_2.input | 874800x26568960 | 3 | 49209 | 26 | 1262 | 2 | 107 | 0 |
| beta_0912/beta_3.input | 4698000x13317120 | 3 | 22732 | 60 | 665 | 2 | 24 | 555108 |
| beta_0912/beta_4.input | 4698000x13317120 | 3 | 22732 | 62 | 698 | 2 | 24 | 0 |
| beta_0912/beta_5.input | 21904440x2843016 | 4 | 54150 | 6 | 1964 | 2 | 449 | 0 |
| example_0205/example_1.input | 1000x1000 | 2 | 34 | 1 | 3 | 2 | 3 | 17 |
| example_0205/example_2.input | 149480x139285 | 5 | 7592 | 5 | 96 | 4 | 32 | 370 |
| example_0711/alpha_1.input | 16670x14135 | 3 | 287 | 3 | 64 | 2 | 32 | 10 |
| example_0711/example_1.input | 1000x1000 | 2 | 34 | 1 | 3 | 2 | 3 | 17 |
| example_0711/example_2.input | 149480x139285 | 5 | 7592 | 5 | 96 | 4 | 32 | 1510 |
| final_case/beta_1.input | 874800x26568960 | 3 | 49209 | 34 | 1260 | 2 | 66 | 159 |
| final_case/beta_2.input | 874800x26568960 | 3 | 49209 | 26 | 1262 | 2 | 107 | 0 |
| final_case/beta_3.input | 4698000x13317120 | 3 | 22732 | 60 | 665 | 2 | 24 | 555108 |
| final_case/beta_4.input | 4698000x13317120 | 3 | 22732 | 62 | 698 | 2 | 24 | 0 |
| final_case/beta_5.input | 21904440x2843016 | 4 | 54150 | 6 | 1964 | 2 | 449 | 0 |
| final_case/final_1.input | 27021600x11064960 | 3 | 81226 | 18 | 1032 | 2 | 130 | 0 |
| final_case/final_2.input | 5929200x979200 | 3 | 14209 | 70 | 1285 | 2 | 64 | 0 |
| final_case/final_3.input | 4924800x10575360 | 4 | 21379 | 47 | 852 | 2 | 133 | 0 |
