#include <iostream>
#include <random>
#include <vector>
#include <utility>
#include <cmath>

// 초기 페로몬 10
// 초기 개미 마릿수 10,000

using namespace std;

struct edge {
	int Destination;
	double Distance;
	double Pheromone;
	edge() {}
	edge(int Destination, double Distance, double Pheromone) : Destination(Destination), Distance(Distance), Pheromone(Pheromone) {}
};

typedef vector<edge> MyVector;


const double Rho1 = 0.7; // 증발율 1
const double Rho2 = 0.7; // 증발율 2
const double Tau0 = 2; // 페로몬 갱신 양
const double Beta = 0.3; // 휴리스틱 함수의 지수
const double r0 = 0.85; // 노드 선택 방법의 확률 결정 상수
double r; // 랜덤 숫자

MyVector Distance[50001];
MyVector Graph[50001];
int AntMap[50001] = {0, };
int visited[50001] = {0, };
vector<int> searchMap;

pair<int, double> Max_arg;

double GetRandomNumber();
void search(int start);