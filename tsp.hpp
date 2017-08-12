#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <random>

#define ANTS 10000
#define NODE 100

using namespace std;

struct Edge {
    int Distance = 0;
    double Pheromone = 0;
	Edge() {}
	Edge(int Distance, double Pheromone) : Distance(Distance), Pheromone(Pheromone) {}
};

struct AntStruct {
    bool Visited[ANTS + 1] = {false, };
    vector<int> Index;
    int Length = 0;
};

Edge Graph[NODE + 1][NODE + 1];
vector<int> BestPath;
AntStruct Ant[ANTS + 1];
bool Visited[NODE + 1] = {0, };

int NumberOfNode, NumberOfEdge;
int From, To, Old_From, Value;

double MinLength = INT32_MAX;

double Alpha = 1.5;
double Beta = 1.5;
double Rho = 0.75;

int GetRandomInt();
double GetRandomReal();
int SelectNext(int i);
void Tour(int i);
void Evaporate();