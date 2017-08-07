#include <iostream>

#define PHEROMONE 10

using namespace std;

pair<int><int>graph[1001][1001];

int main()  {
    int nodeNumber, edgeNumber;

    cin >> nodeNumber >> edgeNumber;

    for(int i = 1; i <= edgeNumber; ++i)   {
        int from, to, value;
        cin >> from >> to >> value;
        graph[from][to] = make_pair(value, PHEROMONE);
    }


}

void SelectEdge() {

}

void UpdatePheromone()  {
    
}