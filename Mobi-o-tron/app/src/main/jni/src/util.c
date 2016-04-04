void quickSort(int vet[], int esq, int dir){
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
        quickSort(vet,esq,pivo-1);
    }
    if(pivo+1 < dir){
        quickSort(vet,pivo+1,dir);
    }
}