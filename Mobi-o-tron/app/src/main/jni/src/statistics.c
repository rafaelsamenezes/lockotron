/**
 * Calcula a moda
 */

 void quick(int vet[], int esq, int dir){
     int pivo = esq,i,ch,j;
     for(i=esq+1;i<=dir;i++){
         j = i;
         if(vet[j] < vet[pivo]){
          ch = vet[j];
          while(j > pivo){
             vet[j] = vet[j-1];
             j--;
          }
          vet[j] = ch;
          pivo++;
         }
     }
     if(pivo-1 > esq){
         quick(vet,esq,pivo-1);
     }
     if(pivo+1 < dir){
         quick(vet,pivo+1,dir);
     }
  }

int getMode(int* values, int size) {
  //  quick(values, 0, size-1);

    int maior = 0;
    int valorAtual = values[0];
    int quantidadeMax = 0;
    int quantidadeAtual = 0;
    int i = 0;
    for(; i<size; i++){
      if (values[i] == valorAtual) {
        quantidadeAtual++;
        }
      }
      else {
         valorAtual = values[i];
         quantidadeAtual = 1;
      }

      if(quantidadeAtual > quantidadeMax){
        quantidadeMax = quantidadeAtual;
        maior = values[i];
      }
    }
    return maior;
}
