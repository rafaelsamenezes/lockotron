.global getMode

// int* values -> r0
// int size -> r1

// int i -> r2
// int valorAtual -> r3
// int quantidadeMax -> r4
// int quantidadeAtual -> r5
// int maior -> r6
// int temp -> r7

getMode:
    stmdb sp!, {r2, r3, r4, r5, r6, r7}  // Empilha os valores dos registradores que serão usados

    mov r2, #0   // int i = 0;
    mov r4, #0   // int quantidadeMax = 0;
    mov r5, #1   // int quantidadeAtual = 1;
    ldr r6, [r0] // int maior = values[0];
    ldr r3, [r0] // int valorAtual = values[0];

getMode_loop:
    cmp r1, r2        // if (i < size)
    beq getMode_end   // Termina loop
    add r0, r0, #4    // pega proximo int
    ldr r7, [r0]      // temp = values[i];
    cmp r3, r7        // values[i] == valorAtual
    bne else
        add r5, r5, #1  // quantidadeAtual++;
        B endif
    else:
        mov r3, r7      // valorAtual = values[i];
        mov r5, #1      // quantidadeAtual = 1;
    endif:
    cmp r5, r4        // if (quantidadeAtual > quantidadeMax)
    blt fim
        mov r4, r5      // quantidadeMax = quantidadeAtual;
        mov r6, r7      // maior = values[i];
    fim:
    add r2, r2, #1    // i++;
    B getMode_loop

getMode_end:
    mov r0, r6
    ldmia sp!, {r2, r3, r4, r5, r6, r7}
    bx lr