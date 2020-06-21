#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define M 102
#define N 102

int Map[M][N];
int I, J; // 현재 위치
int stack[M*N*2];
int sp;

int init(){ sp = 0; I = J = 1; return 0;}

int isEmpty(){return sp == 0;}
int Push(int x){
	if(sp>=M*N*2){return -2;}
	stack[sp] = x;
	sp++;
	return 0;
}
int Pop(){
	if(sp == 0) return -1;
	sp--; return stack[sp];
}
void print_map(int x, int y){
	int i, j;
	for(i = 0; i < x+2; i++){
		for(j = 0; j < y+2; j++){
			printf("%d ",Map[i][j]);
		}
		printf("\n");
	}
	printf("\n stack :");
	for(i=0;i<sp;i++) printf("%d ",stack[i]);
	printf("\n\n");
}
int find(int x, int y){
	while(1){
		print_map(x, y);
		int check;
		int s = 0;
		// 목적지 도착
		if( (I == x) && (J == y) ) break;
		// 상 하 좌 우 길 확인
		if(Map[I][J+1] == 0){
			s=Push(I);s=Push(J);
			Map[I][J] = 2;// int 형으로 선언해서 2가 갔던 길을 표시
			J = J+1;
			printf("1\n");
			check = 1;
		}else if(Map[I][J-1] == 0){ 
			s=Push(I);s=Push(J);
			Map[I][J] = 2;
			J = J-1; 
			printf("2\n");
			check = 2;
		}else if(Map[I+1][J] == 0){
			s=Push(I);s=Push(J);
			Map[I][J] = 2;
			I = I+1; 
			printf("3\n");
			check = 3;
		}else if(Map[I-1][J] == 0){
			s=Push(I);s=Push(J);
			Map[I][J] = 2;
			I = I-1; 
			printf("4\n");
			check = 4;
		}else{ // 후진 
			Map[I][J] = 2;
			J = Pop(); I = Pop();
			
			if( I == -1 || J == -1 ) {
				s = -1;
			}
			check = 5;
		}
		printf("here : %d %d %d\n", I, J,check);
		if(s<0){
			return s;
		}
		
	}
	return 0;
}
int main(){
	int ret;
	int x, y; // 미로의 출구 
	int i, j;
	init();
	//// 입력 값으로 가로 세로 크기를 받고 그 값을 미로 출구로 사용 
	//// 맵을 입력받음 
	scanf("%d %d", &x, &y);
	for(i = 1; i < x+1; i++){
		for(j = 1; j < y+1; j++){
			scanf("%d",&Map[i][j]);
		}
	}
	for(i = 0; i<x+2; i++){
		Map[0][i] = 1;
		Map[i][0] = 1;
		Map[x+1][i] = 1;
		Map[i][x+1] = 1;
	}
	ret = find(x, y);
	if(ret == -1){
		printf("미로의 출구가 없습니다\n");
	}else if(ret == -2){
		printf("stack is full\n");
	}else{
		printf("succeed\n");
	}
	printf("a\n");


	return 0;
}