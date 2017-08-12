#include "tsp.hpp"

int main()  {
    cin >> NumberOfNode >> NumberOfEdge;

    for(int i = 1; i <= NumberOfEdge; ++i)  {
        cin >> From >> To >> Value;
        Graph[From][To] = {Value, 10};
        Graph[From][From].Distance = 0;
        Graph[To][From] = {Value, 10};
    }

    for(int Time = 1; Time <= 5; ++Time)   {
        for(int i = 1; i <= ANTS; ++i)   {
            Ant[i].Index.clear();
            Ant[i].Length = 0;
        }

        for(int i = 1; i <= ANTS; ++i)   {
            Tour(i);
            if(Ant[i].Length == -1)
                continue;
            
            if(MinLength > Ant[i].Length)   {
                BestPath.clear();
                for(auto j : Ant[i].Index)  {
                    BestPath.push_back(j);
                }

                MinLength = Ant[i].Length;
            }
        }

        Evaporate();

        for (int i = 1; i <= ANTS; ++i) {
			if (Ant[i].Length == -1)
				continue;

			for (int j = 0; j < Ant[i].Index.size() - 1; j++) {
				From = Ant[i].Index[j];
                To = Ant[i].Index[j + 1];
				Graph[From][To].Pheromone += 1.0 / Ant[i].Length;
                Graph[To][From].Pheromone += 1.0 / Ant[i].Length;
			}
		}
    }

    for(auto i : BestPath)  {
        cout << i << " ";
    }
    cout << "\n" << MinLength;
}

void Tour(int i) {
    memset(Visited, 0, sizeof(Visited));
    Old_From = GetRandomInt();
    From = Old_From;
    Visited[From] = true;

    for(int j = 1; j < NumberOfNode; ++j)    {
        Ant[i].Index.push_back(From);
        To = SelectNext(From);
        if(To == -1)    {
            Ant[i].Index.clear();
            Ant[i].Length = -1;
            return ;
        }
        Visited[To] = true;
        Ant[i].Length += Graph[From][To].Distance;
        From = To;
    }

    Ant[i].Length += Graph[To][Old_From].Distance;
    Ant[i].Index.push_back(From);

    return ;
}

int SelectNext(int i)   {
    int Low, High, Middle;
    double sum = 0, r = 0;
    vector<pair<int, double>> Probability;
    for(int j = 1; j <= NumberOfNode; ++j)   {
        if(Visited[j] || i == j)
            continue;

        sum += (double)pow(Graph[i][j].Pheromone, Alpha) * (double)pow(1.0 / Graph[i][j].Distance, Beta);
    }
    for(int j = 1; j <= NumberOfNode; ++j)  {
        if(Visited[j] || i == j)
            continue;
        
        Probability.push_back(make_pair(j, (double)pow(Graph[i][j].Pheromone, Alpha) * (double)pow(1.0 / Graph[i][j].Distance, Beta) / sum));
    }

    if(Probability.empty()) {
        return -1;
    }

    Low = 0, High = Probability.size() - 1;

    r = GetRandomReal();

    while(Low < High)   {
        Middle = (Low + High) / 2;
        if(Probability[Middle].second <= r)
            High = Middle;
        else
            Low = Middle + 1;
    }

    return Probability[Low].first;
}

void Evaporate()    {
    for(int i = 1; i <= NumberOfNode; ++i)   {
        for(int j = 1; j <= NumberOfNode; ++j) {
            Graph[i][j].Pheromone *= Rho;
        }
    }
}

double GetRandomReal()    {
    random_device rn;
    mt19937_64 rnd(rn());
 
    uniform_real_distribution<double> range(0, 1);

    return range(rnd);
}

int GetRandomInt()    {
    random_device rn;
    mt19937_64 rnd(rn());
 
    uniform_int_distribution<int> range(1, NumberOfNode);

    return range(rnd);
}