# Port para PlayStation 3 (HEN)

## Importante
O `main.c` atual usa SDL2 e serve para validar a lógica no desktop. Ele não compila
automaticamente para PS3. O console precisa de um executável PowerPC/PSL1GHT e
bibliotecas compiladas para PS3.

## Caminho recomendado
1. Preparar PS3DEV/PSL1GHT e escolher uma camada gráfica compatível.
2. Adaptar janela, desenho, temporização e entrada do SDL2 para RSX/libpad,
   ou compilar uma SDL2 efetivamente portada para PS3.
3. Criar os metadados `PARAM.SFO`, gerar `EBOOT.BIN` e empacotar o `.pkg`.
4. Testar primeiro no RPCS3; depois testar em console HEN.
5. Corrigir travamentos, colisões, controles e desempenho com logs de teste.

Referências:
- PSL1GHT: https://github.com/ps3dev/PSL1GHT
- PS3 toolchain: https://github.com/ps3dev/ps3dev
- Exemplo de projeto PS3 com build em Docker: https://github.com/utkuhalis/ps3-homebrew

## Próximos sistemas do jogo
- Máquina de estados do jogador (parado, correr, pular, cair, atacar, dash, dano).
- Colisão por caixas e plataformas.
- Câmera lateral com limites de sala.
- Inimigos com estados e hitboxes.
- Sistema de vida, energia e checkpoints.
- Animações e efeitos sonoros originais.
