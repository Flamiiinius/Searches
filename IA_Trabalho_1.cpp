// 362.880 configuracoes possiveis!!!

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>

// DFS e DFSI ->OK!
// BFS,gredy, A* -> dar o free

using namespace std;
bool vis[876543210];

struct la {
    int config[3][3];
    la *pai;
    int nivel;
    int custo; //so para as informadas
    char pos; //de onde veio
};

typedef la* pla;
typedef int m3[3][3];
typedef m3* pm3;
int EstadoFinal[3][3];
int Para_o_print[3][3];
long n_nos = 0;

void print(pla fim){ //imprimir no fim do programa
    cout << endl << "Encontramos uma solucao, o caminho e: ";
    char*s;
    s=(char*)malloc(fim->nivel*sizeof(char));
    pla temp=fim->pai;
    int i=0;
    s[0]=fim->pos;
    while(temp->pai!=NULL){
        i++;
        s[i]=temp->pos;
        temp=temp->pai;
    }
    int test = i;
    for(;i>=0;i--) cout << s[i]<< " ";
    cout << endl;
    cout << "No nivel: " << fim->nivel-1 << endl;
    cout << "Numero de nos => " << n_nos << endl;
    if (test < 100) {
        int quer = -1;
        cout << endl << "Quer uma vizualizacao da resolucao?\n Sim            --> 1 \n Nao            --> QQ carater" << endl;
        cin >> quer;
        
        if (quer == 1){
            char char_x;
            int cordX = 0, cordY = 0;
            i = test;
            cout << endl << "Inicio" << endl;
            for (int i = 0; i<3; i++){
                cout << "|||||||||||    ";
                for (int j = 0; j<3; j++){
                    cout << Para_o_print[i][j] << " ";
                }
                cout << "    |||||||||||"<< endl;
            }
            
            for (; i>=0 ; i--) {
                char_x = s[i];
                
                for (int i = 0; i<3; i++)
                    for (int j = 0; j<3; j++)
                        if (Para_o_print[i][j] == 0) {
                            cordY = i;
                            cordX = j;
                        }
                cout << endl;
                
                if ( char_x == 'U' ) {
                    cout << "Move Up" << endl;
                    //cout << cordY << " " << cordX << endl;
                    Para_o_print[cordY][cordX] = Para_o_print[cordY-1][cordX];
                    Para_o_print[cordY-1][cordX] = 0;
                }
                if ( char_x == 'D' ) {
                    cout << "Move Down" << endl;
                    Para_o_print[cordY][cordX] = Para_o_print[cordY+1][cordX];
                    Para_o_print[cordY+1][cordX] = 0;
                }
                if ( char_x == 'L' ) {
                    cout << "Move Left" << endl;
                    Para_o_print[cordY][cordX] = Para_o_print[cordY][cordX-1];
                    Para_o_print[cordY][cordX-1] = 0;
                }
                if ( char_x == 'R' ) {
                    cout << "Move Right" << endl;
                    Para_o_print[cordY][cordX] = Para_o_print[cordY][cordX+1];
                    Para_o_print[cordY][cordX+1] = 0;
                }
                
                for (int i = 0; i<3; i++){
                    cout << "|||||||||||    ";
                    for (int j = 0; j<3; j++){
                        cout << Para_o_print[i][j] << " ";
                    }
                    cout << "    |||||||||||"<< endl;
                }
            }
        }
    }
    cout << endl;
    
    exit(EXIT_SUCCESS);
}

void input(pla root) { //temos que adicionar uma confirmacao a ver se os numeros sao de 0 a 8 - erro recomeçar
    int x;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++){
            cin >> x;
            root->config[i][j] = x;
            Para_o_print[i][j] = x;
        }
    
    cout << endl << "Digite o estado final:" << endl;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            cin >> EstadoFinal[i][j];
    
    return;
}

bool solve(pla root) { //ver se e solucao
    int check[8];
    int inv1 = 0, inv2 = 0, h = 0;
    
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (root->config[i][j] != 0) { check[h] = root->config[i][j]; h++; }
    
    for (int i = 0; i<8; i++)
        for (int j = i + 1; j<8; j++)
            if (check[j]>check[i]) inv1++;
    
    h = 0;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (EstadoFinal[i][j] != 0) { check[h] = EstadoFinal[i][j]; h++; }
    
    for (int i = 0; i<8; i++)
        for (int j = i + 1; j<8; j++)
            if (check[j]>check[i]) inv2++;
    
    return ((inv1 + inv2) % 2);
}

bool comp(int m1[3][3],int m2[3][3]){ //comparacao
    for(int i =0;i<3;i++)
        for(int j=0;j<3;j++)
            if(m1[i][j]!=m2[i][j])
                return false;
    return true;
}

pla move(pla root,char B){ // cria o filho (tudo menos o custo)
    
    pla nova = (pla)malloc(sizeof(la));
    
    if (B == 'U') { /* para as 6 posicoes em que pode estar - cada uma tem 6*/
        if (root->config[1][0] == 0) {  memcpy(nova->config, root->config, sizeof(m3));nova->config[1][0] = root->config[0][0]; nova->config[0][0] = 0; }    // nao falta o resto da matriz?  S— estamos a escrever o 0 e o de cima, nao falta copiar o resto da matriz toda?
        else if (root->config[1][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][1] = root->config[0][1]; nova->config[0][1] = 0; }
        else if (root->config[1][2] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][2] = root->config[0][2]; nova->config[0][2] = 0; }
        else if (root->config[2][0] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[2][0] = root->config[1][0]; nova->config[1][0] = 0; }
        else if (root->config[2][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[2][1] = root->config[1][1]; nova->config[1][1] = 0; }
        else if (root->config[2][2] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[2][2] = root->config[1][2]; nova->config[1][2] = 0; }
    }
    else if(B =='D'){
        if (root->config[1][0] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][0] = root->config[2][0]; nova->config[2][0] = 0; }
        else if (root->config[1][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][1] = root->config[2][1]; nova->config[2][1] = 0; }
        else if (root->config[1][2] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][2] = root->config[2][2]; nova->config[2][2] = 0; }
        else if (root->config[0][0] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[0][0] = root->config[1][0]; nova->config[1][0] = 0; }
        else if (root->config[0][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[0][1] = root->config[1][1]; nova->config[1][1] = 0; }
        else if (root->config[0][2] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[0][2] = root->config[1][2]; nova->config[1][2] = 0; }
    }
    else if (B == 'L') {
        if (root->config[2][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[2][1] = root->config[2][0]; nova->config[2][0] = 0; }
        else if (root->config[2][2] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[2][2] = root->config[2][1]; nova->config[2][1] = 0; }
        else if (root->config[1][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][1] = root->config[1][0]; nova->config[1][0] = 0; }
        else if (root->config[1][2] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][2] = root->config[1][1]; nova->config[1][1] = 0; }
        else if (root->config[0][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[0][1] = root->config[0][0]; nova->config[0][0] = 0; }
        else if (root->config[0][2] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[0][2] = root->config[0][1]; nova->config[0][1] = 0; }
    }
    else if (B == 'R') {
        if (root->config[2][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[2][1] = root->config[2][2]; nova->config[2][2] = 0; }
        else if (root->config[2][0] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[2][0] = root->config[2][1]; nova->config[2][1] = 0; }
        else if (root->config[1][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][1] = root->config[1][2]; nova->config[1][2] = 0; }
        else if (root->config[1][0] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][0] = root->config[1][1]; nova->config[1][1] = 0; }
        else if (root->config[0][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[0][1] = root->config[0][2]; nova->config[0][2] = 0; }
        else if (root->config[0][0] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[0][0] = root->config[0][1]; nova->config[0][1] = 0; }
    }
    
    nova->pai = root;
    nova->nivel = root->nivel + 1;
    nova->pos = B;
    
    if(comp(nova->config,EstadoFinal))print(nova); //se encontramos sul.
    
    int vis_index = nova->config[0][0]*100000000+nova->config[0][1]*10000000+nova->config[0][2]*1000000+nova->config[1][0]*100000+nova->config[1][1]*10000+nova->config[1][2]*1000+nova->config[2][0]*100+nova->config[2][1]*10+nova->config[2][2]*1;
    if(vis[vis_index]){free(nova);return root;}
    else{
        vis[vis_index]=true;
        n_nos++;
    }
    return nova;
}

int Heu1(m3 m){ // pessas fora do sitio
    int s=0;
    for(int j=0;j<3;j++)
        for(int k=0;k<3;k++)
            if(EstadoFinal[j][k]!=m[j][k])s++;
    return s;
}

int Heu2(m3 m){ //manhatan distance
    int s=0,x = 0,x1 = 0,x2 = 0,y = 0,y1 = 0,y2 = 0;
    for(int i=1;i<9;i++){
        for(int j=0;j<3;j++)
            for(int k=0;k<3;k++){
                if(m[j][k]==i){x1=j;y1=k;}
                if(EstadoFinal[j][k]==i){x2=j;y2=k;}
                x=x1-x2;y=y1-y2;}
        if(x>0)s+=x;
        else s-=x;
        if(y>0)s+=y;
        else s-=y;
    }
    return s;
}

bool can_i(int m[3][3],char teste){
    if		(teste == 'U'){ if (m[0][0] == 0 || m[0][1] == 0 || m[0][2] == 0){ return false;}}
    else if (teste == 'D'){ if (m[2][0] == 0 || m[2][1] == 0 || m[2][2] == 0){ return false;}}
    else if (teste == 'L'){ if (m[0][0] == 0 || m[1][0] == 0 || m[2][0] == 0){ return false;}}
    else if (teste == 'R'){ if (m[0][2] == 0 || m[1][2] == 0 || m[2][2] == 0){ return false;}}
    return true;
}

void dfs(pla root) {
    if (can_i(root->config, 'U')&&root->pos!='D'){
        pla nova = move(root, 'U');
        if (nova != root){
            dfs(nova);
            free(nova);}
    }
    if (can_i(root->config, 'D')&&root->pos!='U'){
        pla nova = move(root, 'D');
        if (nova != root){
            dfs(nova);
            free(nova);}
    }
    if (can_i(root->config, 'L')&&root->pos!='R'){
        pla nova = move(root, 'L');
        if (nova != root){
            dfs(nova);
            free(nova);}
    }
    if (can_i(root->config, 'R')&&root->pos!='L'){
        pla nova = move(root, 'R');
        if (nova != root){
            dfs(nova);
            free(nova);}
    }
    return;
}

void bfs(pla root){ // ONDE PODEMOS DAR O FREE ????
    queue<pla> Estados;
    Estados.push(root);
    while(!Estados.empty()){
        pla temp=Estados.front();
        if (can_i(temp->config, 'U')&&temp->pos!='D'){
            pla nova = move(temp, 'U');
            if (nova != temp){
                Estados.push(nova);}
        }
        if (can_i(temp->config, 'D')&&temp->pos!='U'){
            pla nova = move(temp, 'D');
            if (nova != temp){
                Estados.push(nova);}
        }
        if (can_i(temp->config, 'L')&&temp->pos!='R'){
            pla nova = move(temp, 'L');
            if (nova != temp){
                Estados.push(nova);}
        }
        if (can_i(temp->config, 'R')&&temp->pos!='L'){
            pla nova = move(temp, 'R');
            if (nova != temp){
                Estados.push(nova);}
        }
        Estados.pop();
    }
}

pla get_new(pla root,char B){ // MOVE S/ VISITADOS
    pla nova=(pla)malloc(sizeof(la));
    
    if (B == 'U') { /* para as 6 posicoes em que pode estar - cada uma tem 6*/
        if (root->config[1][0] == 0) {  memcpy(nova->config, root->config, sizeof(m3));nova->config[1][0] = root->config[0][0]; nova->config[0][0] = 0; }    // nao falta o resto da matriz?  S— estamos a escrever o 0 e o de cima, nao falta copiar o resto da matriz toda?
        else if (root->config[1][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][1] = root->config[0][1]; nova->config[0][1] = 0; }
        else if (root->config[1][2] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][2] = root->config[0][2]; nova->config[0][2] = 0; }
        else if (root->config[2][0] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[2][0] = root->config[1][0]; nova->config[1][0] = 0; }
        else if (root->config[2][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[2][1] = root->config[1][1]; nova->config[1][1] = 0; }
        else if (root->config[2][2] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[2][2] = root->config[1][2]; nova->config[1][2] = 0; }
    }
    else if(B =='D'){
        if (root->config[1][0] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][0] = root->config[2][0]; nova->config[2][0] = 0; }
        else if (root->config[1][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][1] = root->config[2][1]; nova->config[2][1] = 0; }
        else if (root->config[1][2] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][2] = root->config[2][2]; nova->config[2][2] = 0; }
        else if (root->config[0][0] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[0][0] = root->config[1][0]; nova->config[1][0] = 0; }
        else if (root->config[0][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[0][1] = root->config[1][1]; nova->config[1][1] = 0; }
        else if (root->config[0][2] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[0][2] = root->config[1][2]; nova->config[1][2] = 0; }
    }
    else if (B == 'L') {
        if (root->config[2][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[2][1] = root->config[2][0]; nova->config[2][0] = 0; }
        else if (root->config[2][2] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[2][2] = root->config[2][1]; nova->config[2][1] = 0; }
        else if (root->config[1][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][1] = root->config[1][0]; nova->config[1][0] = 0; }
        else if (root->config[1][2] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][2] = root->config[1][1]; nova->config[1][1] = 0; }
        else if (root->config[0][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[0][1] = root->config[0][0]; nova->config[0][0] = 0; }
        else if (root->config[0][2] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[0][2] = root->config[0][1]; nova->config[0][1] = 0; }
    }
    else if (B == 'R') {
        if (root->config[2][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[2][1] = root->config[2][2]; nova->config[2][2] = 0; }
        else if (root->config[2][0] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[2][0] = root->config[2][1]; nova->config[2][1] = 0; }
        else if (root->config[1][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][1] = root->config[1][2]; nova->config[1][2] = 0; }
        else if (root->config[1][0] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[1][0] = root->config[1][1]; nova->config[1][1] = 0; }
        else if (root->config[0][1] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[0][1] = root->config[0][2]; nova->config[0][2] = 0; }
        else if (root->config[0][0] == 0) {memcpy(nova->config, root->config, sizeof(m3)); nova->config[0][0] = root->config[0][1]; nova->config[0][1] = 0; }
    }
    
    nova->pai = root;
    nova->nivel = root->nivel + 1;
    nova->pos = B;
    //n_nos++;
    return nova;
}

void DLS(pla root,int depth){ //2a parte iterativo
    if(depth == 0) return;
    else if (depth >0){
        if(can_i(root->config,'U')&&root->pos!='D'){
            pla nova = move(root,'U');
            if(nova!=root){
                DLS(nova,depth-1);
                free(nova);
            }
            else{
                pla temp =(pla)malloc(sizeof(la));
                temp=get_new(root,'U');
                DLS(temp,depth-1);
                free(temp);
            }
        }
        if(can_i(root->config,'D')&&root->pos!='U'){
            pla nova = move(root,'D');
            if(nova!=root){
                DLS(nova,depth-1);
                free(nova);
            }
            else{
                
                pla temp =(pla)malloc(sizeof(la));
                temp=get_new(root,'D');
                DLS(temp,depth-1);
                free(temp);
            }
        }
        if(can_i(root->config,'L')&&root->pos!='R'){
            pla nova = move(root,'L');
            if(nova!=root){
                DLS(nova,depth-1);
                free(nova);
            }
            else{
                pla temp =(pla)malloc(sizeof(la));
                temp=get_new(root,'L');
                DLS(temp,depth-1);
                free(temp);
            }
        }
        if(can_i(root->config,'R')&&root->pos!='L'){
            pla nova = move(root,'R');
            if(nova!=root){
                DLS(nova,depth-1);
                free(nova);
            }
            else{
                pla temp =(pla)malloc(sizeof(la));
                temp=get_new(root,'R');
                DLS(temp,depth-1);
                free(temp);
            }
        }
    }
    return;
    
}

void IDDFS(pla root){ // 1a parte iterativo
    for(int i=1;;i++){
        DLS(root,i);
        memset (vis,false,sizeof(vis));
        n_nos=0;}
}

struct cmp{ //funcao para comparacao das priority_queue
    bool operator()(const pla a,const pla b){return(b->custo < a->custo);}
};

void bg2(pla root) { // gredy H2
   	priority_queue<pla,vector<pla>,cmp > Estados;
    root->custo=Heu2(root->config);
    Estados.push(root);
    while(!Estados.empty()){
        pla temp=Estados.top(); Estados.pop();
        if (can_i(temp->config, 'U')&&temp->pos!='D'){
            pla nova = move(temp, 'U');
            if (nova != temp){
                nova->custo=Heu2(nova->config);
                Estados.push(nova);}
        }
        if (can_i(temp->config, 'D')&&temp->pos!='U'){
            pla nova = move(temp, 'D');
            if (nova != temp){
                nova->custo=Heu2(nova->config);
                Estados.push(nova);}
        }
        if (can_i(temp->config, 'L')&&temp->pos!='R'){
            pla nova = move(temp, 'L');
            if (nova != temp){
                nova->custo=Heu2(nova->config);
                Estados.push(nova);}
        }
        if (can_i(temp->config, 'R')&&temp->pos!='L'){
            pla nova = move(temp, 'R');
            if (nova != temp){
                nova->custo=Heu2(nova->config);
                Estados.push(nova);}
        }
    }
}

void A_A2(pla root) { //A* Heu2
    priority_queue<pla,vector<pla>,cmp > Estados;
    root->custo=Heu2(root->config);
    Estados.push(root);
    while(!Estados.empty()){
        pla temp=Estados.top(); Estados.pop();
        if (can_i(temp->config, 'U')&&temp->pos!='D'){
            pla nova = move(temp, 'U');
            if (nova != temp){
                nova->custo=Heu2(nova->config) + nova->nivel;
                Estados.push(nova);}
            else if(nova->custo > (Heu2(nova->config) + nova->nivel)){
                nova->custo =Heu2(nova->config) + nova->nivel;
                nova->pai = temp;
                nova->nivel = temp->nivel + 1;
                nova->pos = 'U';
                Estados.push(nova);
            }
        }
        if (can_i(temp->config, 'D')&&temp->pos!='U'){
            pla nova = move(temp, 'D');
            if (nova != temp){
                nova->custo=Heu2(nova->config) + nova->nivel;
                Estados.push(nova);}
            else if(nova->custo > (Heu2(nova->config) + nova->nivel)){
                nova->custo =Heu2(nova->config) + nova->nivel;
                nova->pai = temp;
                nova->nivel = temp->nivel + 1;
                nova->pos = 'D';
                Estados.push(nova);
            }
        }
        if (can_i(temp->config, 'L')&&temp->pos!='R'){
            pla nova = move(temp, 'L');
            if (nova != temp){
                nova->custo=Heu2(nova->config) + nova->nivel;
                Estados.push(nova);}
            else if(nova->custo > (Heu2(nova->config) + nova->nivel)){
                nova->custo =Heu2(nova->config) + nova->nivel;
                nova->pai = temp;
                nova->nivel = temp->nivel + 1;
                nova->pos = 'L';
                Estados.push(nova);
            }
        }
        if (can_i(temp->config, 'R')&&temp->pos!='L'){
            pla nova = move(temp, 'R');
            if (nova != temp){
                nova->custo=Heu2(nova->config) + nova->nivel;
                Estados.push(nova);}
            else if(nova->custo > (Heu2(nova->config) + nova->nivel)){
                nova->custo =Heu2(nova->config) + nova->nivel;
                nova->pai = temp;
                nova->nivel = temp->nivel + 1;
                nova->pos = 'R';
                Estados.push(nova);
            }
        }
    }
}

void bg1(pla root) { //gredy H1
   	priority_queue<pla,vector<pla>,cmp > Estados;
    root->custo=Heu1(root->config);
    Estados.push(root);
    while(!Estados.empty()){
        pla temp=Estados.top(); Estados.pop();
        if (can_i(temp->config, 'U')&&temp->pos!='D'){
            pla nova = move(temp, 'U');
            if (nova != temp){
                nova->custo=Heu1(nova->config);
                Estados.push(nova);}
        }
        if (can_i(temp->config, 'D')&&temp->pos!='U'){
            pla nova = move(temp, 'D');
            if (nova != temp){
                nova->custo=Heu1(nova->config);
                Estados.push(nova);}
        }
        if (can_i(temp->config, 'L')&&temp->pos!='R'){
            pla nova = move(temp, 'L');
            if (nova != temp){
                nova->custo=Heu1(nova->config);
                Estados.push(nova);}
        }
        if (can_i(temp->config, 'R')&&temp->pos!='L'){
            pla nova = move(temp, 'R');
            if (nova != temp){
                nova->custo=Heu1(nova->config);
                Estados.push(nova);}
        }
    }
}

void A_A1(pla root) { //A* Heu2
    priority_queue<pla,vector<pla>,cmp > Estados;
    root->custo=Heu1(root->config);
    Estados.push(root);
    while(!Estados.empty()){
        pla temp=Estados.top(); Estados.pop();
        if (can_i(temp->config, 'U')&&temp->pos!='D'){
            pla nova = move(temp, 'U');
            if (nova != temp){
                nova->custo=Heu1(nova->config) + nova->nivel;
                Estados.push(nova);}
            else if(nova->custo > (Heu1(nova->config) + nova->nivel)){
                nova->custo =Heu1(nova->config) + nova->nivel;
                nova->pai = temp;
                nova->nivel = temp->nivel + 1;
                nova->pos = 'U';
                Estados.push(nova);
            }
        }
        if (can_i(temp->config, 'D')&&temp->pos!='U'){
            pla nova = move(temp, 'D');
            if (nova != temp){
                nova->custo=Heu1(nova->config) + nova->nivel;
                Estados.push(nova);}
            else if(nova->custo > (Heu1(nova->config) + nova->nivel)){
                nova->custo =Heu1(nova->config) + nova->nivel;
                nova->pai = temp;
                nova->nivel = temp->nivel + 1;
                nova->pos = 'D';
                Estados.push(nova);
            }
        }
        if (can_i(temp->config, 'L')&&temp->pos!='R'){
            pla nova = move(temp, 'L');
            if (nova != temp){
                nova->custo=Heu1(nova->config) + nova->nivel;
                Estados.push(nova);}
            else if(nova->custo > (Heu1(nova->config) + nova->nivel)){
                nova->custo =Heu1(nova->config) + nova->nivel;
                nova->pai = temp;
                nova->nivel = temp->nivel + 1;
                nova->pos = 'L';
                Estados.push(nova);
            }
        }
        if (can_i(temp->config, 'R')&&temp->pos!='L'){
            pla nova = move(temp, 'R');
            if (nova != temp){
                nova->custo=Heu1(nova->config) + nova->nivel;
                Estados.push(nova);}
            else if(nova->custo > (Heu1(nova->config) + nova->nivel)){
                nova->custo =Heu1(nova->config) + nova->nivel;
                nova->pai = temp;
                nova->nivel = temp->nivel + 1;
                nova->pos = 'R';
                Estados.push(nova);
            }
        }
    }
}

void A_A(pla root){ // Escolher a Heuristica
    int x;
    cout << endl << "Qual heuristica quer?" << endl;
    cout << "Numero de pecas na posicao errada - 1" << endl;
    cout << "Manhattan distance                - 2" << endl;
    cin >> x;
    if (x == 1) {
        A_A1(root);
    }
    else A_A2(root);
}

void bg(pla root){ //Escolher a Heuristica
    int x;
    cout << endl << "Qual heuristica quer?" << endl;
    cout << "Numero de pecas na posicao errada - 1" << endl;
    cout << "Manhattan distance                - 2" << endl;
    cin >> x;
    if (x == 1) {
        bg1(root);
    }
    else bg2(root);
}

int main() {
    int pesquisa;
    pla root;
    root = (pla)malloc(sizeof(la));
    root->pai = NULL;
    root->pos = 'N';
    root->nivel = 1;
    cout << "Digite o input (Represente o vazio por 0): " << endl;
    input(root);
    
    int vis_index = root->config[0][0]*100000000+root->config[0][1]*10000000+root->config[0][2]*1000000+root->config[1][0]*100000+root->config[1][1]*10000+root->config[1][2]*1000+root->config[2][0]*100+root->config[2][1]*10+root->config[2][2]*1;
    vis[vis_index] =true;
    
    if (solve(root)) { cout << "Nao tem solucao" << endl; return 0; }
    if (comp(root->config,EstadoFinal)){cout << "input e igual ao output!!!" << endl; return 0;}
    
    do {
        cout << endl << "Escolha a pesquisa:\n Dfs            --> 1\n Bfs            --> 2\n Dfsi           --> 3\n Busca Gredy    --> 4\n A*             --> 5\n Sair           --> 0\n";
        
        cin >> pesquisa;
        //pesquisas
        if (!pesquisa) return 0;
        else if (pesquisa == 1) dfs(root);
        else if (pesquisa == 2) bfs(root);
        else if (pesquisa == 3) IDDFS(root);
        else if (pesquisa == 4) bg(root);
        else if (pesquisa == 5) A_A(root);
        else cout << "||| ERRO (Carater nao reconhecido) |||" << endl;
    } while (pesquisa >5 || pesquisa < 0);
    
    return 0;
}

//FIM