# Hallownest PS3 Homebrew — projeto inicial

Projeto original de plataforma 2D/metroidvania inspirado na atmosfera de aventuras sombrias.
Não contém código, mapas, músicas ou personagens extraídos de Hollow Knight.

## Estado real
- [x] Estrutura inicial do projeto
- [x] Protótipo de movimento, pulo, ataque e dash em C/SDL2
- [x] Controles de teclado para testar no PC
- [ ] Portar a camada gráfica/entrada para PSL1GHT/PS3
- [ ] Integrar sprites, animações, mapas, inimigos e áudio originais
- [ ] Compilar EBOOT.BIN e gerar PKG
- [ ] Testar no RPCS3 e em PS3 HEN real

**Este ZIP é código-fonte inicial, não é um PKG instalável.** A compilação para PS3 ainda não foi feita nem validada.

## Estrutura
- `src/main.c`: protótipo jogável em SDL2 para testar a lógica.
- `CMakeLists.txt`: compilação de teste em computador com SDL2.
- `docs/PS3_PORT.md`: próximos passos técnicos para o port.
- `.github/workflows/`: workflow de verificação do código-fonte.

## Testar no computador
É necessário SDL2 e CMake:
```sh
cmake -S . -B build
cmake --build build
./build/hallownest
```
No Windows, execute `build/hallownest.exe`.

## Próxima etapa para PS3
O PS3 não executa diretamente este binário SDL2 de PC. É preciso usar uma toolchain PS3 (PS3DEV/PSL1GHT) e uma versão de SDL2 compilada para PS3, ou substituir a camada SDL2 por chamadas PSL1GHT. Veja `docs/PS3_PORT.md`.

## Controles do protótipo
- A/D ou setas: mover
- Espaço: pular
- J: golpe
- K: dash
- Esc: sair
