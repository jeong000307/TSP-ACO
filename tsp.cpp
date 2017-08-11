#include "tsp.hpp"

int max_pheromone = 0;
int flag = 0;

int main()  {
    int NodeNumber, EdgeNumber;
    double Temp = 0;
    double Phi = 0;
    int From = 0, To = 0;
    int Old_From = 1;
    double Value = 0;

    cin >> NodeNumber >> EdgeNumber;

    AntMap[1] = 10000;

    for(int i = 1; i <= EdgeNumber; ++i)   {
        cin >> From >> To >> Value;
        Graph[From].push_back({To, Value, 1});
        Graph[To].push_back({From, Value, 1});
    }

    for(int k = 1; k <= NodeNumber; ++k)   {
        Old_From = From;
        for(int i = 1; i <= 100; ++i)    {
            r = GetRandomNumber();
            Max_arg = make_pair(0, 0);
            if(r <= r0) {
                for(auto j : Graph[From]) {
                    if(j.Destination != Old_From)   {
                        Temp = j.Pheromone * pow(1 / j.Distance, Beta);
                        if(Max_arg.second < Temp)
                            Max_arg.first = j.Destination;
                            Max_arg.second = Temp;
                    }
                }
            }
            else    {
                for(auto j : Graph[From]) {
                    Temp += j.Pheromone * pow(1 / j.Distance, Beta);
                }
                for(auto j : Graph[From]) {
                    if(j.Destination != Old_From)   {
                        Phi = j.Pheromone * pow(1 / j.Distance, Beta);
                        Phi /= Temp;
                        if(Max_arg.second < Phi)   {
                            Max_arg.first = j.Destination;
                            Max_arg.second = Phi;
                        }
                    }
                }
            }

            if(!Max_arg.first)
                break;
            Graph[From][Max_arg.first].Pheromone = (1 - Rho2) * Graph[From][Max_arg.first].Pheromone + Rho2 * Tau0;
            Old_From = From;
            From = Max_arg.first;
            cout << From << " ";
        }
        cout << "\n";
    }

    cout << "\n" << "temp : "; 
    search(1);

    cout << "\n" << "search : " << " ";
    for(auto i : searchMap)
        cout << i << " ";
    cout << "\n";
}

double GetRandomNumber()    {
    random_device rn;
    mt19937_64 rnd(rn());
 
    uniform_int_distribution<double> range(0, 1);

    return range(rnd);
}

void search(int start)  {
    ++visited[start];
    Max_arg = make_pair(0, 0);
    if(start == 1)
        ++flag;
    if(flag == 2)
        return ;
    for(auto i : Graph[start])  {
        if(!visited[i.Destination]) {
            if(i.Pheromone > Max_arg.second)    {
                Max_arg.first = i.Destination;
                Max_arg.second = i.Pheromone;
            }
        }
        cout << i.Destination << " ";
    }
    cout << "\n";

    if(!Max_arg.first)
        return ;
    searchMap.push_back(Max_arg.first);
    search(Max_arg.first);
}