#include <iostream>
#include "math.h"
#include <vector>
#include <set>
#include <string>
#include <iomanip>

std::pair<double, double> hrom (){

    return std::make_pair((rand()%30000)/10000.0-1, (rand()%30000)/10000.0-1);
}

double FIT (const std::pair<double, double>&p) {
    return cos(p.first)*cos(p.second)*exp(p.second/2);
}

void mutation (std::vector<std::pair<double, double>>&v){
    for (auto p : v) {
        if (rand() % 100 < 25) {
            p = hrom();

        }

    }
}

void crossover (std::vector<std::pair<double, double>>&v){
    std::vector<std::pair<double, double>>new_v;

    new_v.push_back(std::make_pair(v[0].first, v[5].second));
    new_v.push_back(std::make_pair(v[1].first, v[4].second));
    new_v.push_back(std::make_pair(v[2].first, v[3].second));
    new_v.push_back(std::make_pair(v[3].first, v[4].second));
    new_v.push_back(std::make_pair(v[4].first, v[5].second));
    new_v.push_back(std::make_pair(v[5].first, v[0].second));

    v=new_v;
}

double Average(std::set<double>& s){
    double sum=0;
    for (const auto& i : s){
        sum+=i;
    }
    return sum/6.;
}

void print (int g, const std::vector<std::pair<double, double>>& p, std::set<double>&f){
    std::cout<<std::setw(10)<<"N"<<std::setw(10)<<"X"<<std::setw(10)<<"Y"<<std::setw(10)<<"F"<<std::endl;
    std::cout<<std::setw(10)<<g;
    std::set<double>::iterator it=f.begin();
    for (int i=0; i<p.size(); i++){

        std::cout<<std::setw(10)<<p[i].first<<std::setw(10)<<p[i].second<<std::setw(10)<<*it<<std::endl;
        std::cout<<"          ";
        it++;
    }
    std::cout<<std::endl;

    std::cout<<"Average F "<<Average(f)<<"\n"<<
                "Max F    "<<*f.rbegin()<<"\n";
}


int main() {
    srand(time(NULL));

    int n=6;

    std::vector<std::pair<double, double>>population(n);
    std::set<double> function;

    for (auto& i : population){
        i=hrom();
        function.insert(FIT(i));
    }
    print(0, population, function);

    for (int i=1; i<=10; i++){
        function.clear();
        crossover(population);
        mutation(population);
        for (auto& i : population){
            function.insert(FIT(i));
        }
        print(i, population, function);
    }


    return 0;
}
