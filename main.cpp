#include <iostream>
#include <vector>
#include <fstream>
struct  dec_s{
int index = -1;
int size = -1;
int min = 9999999999;
std::vector<int> indexes; // Связи с точками
std::vector<int> len_index; // Растояние до точек
}dec_s;
int getIdIndexDecstra(std::vector<struct dec_s>* graph,int index){
    for(int a = 0;a<graph->size();a++){
        if(graph->at(a).index==index){
            return a;
        }
    }
    return -1;
}
bool is_get_in(std::vector<int>* back_index,int index){
    for(int i = 0;i<back_index->size();i++){
        if(back_index->at(i)==index){
            return false;
        }
    }
    return true;
}
void recursive(std::vector<int>* back_index,int new_id,std::vector<struct dec_s>* graph){
 //   bool a = false;
    for(int i = 0;i<graph->at(new_id).indexes.size();i++){
       // std::cout << i <<"d\n";
      //  std::cout << graph->at(new_id).indexes.at(i) <<"\n";
     if(is_get_in(back_index,graph->at(new_id).indexes.at(i))){
   //      a = true;
        int b = getIdIndexDecstra(graph,graph->at(new_id).indexes.at(i));
        if(graph->at(b).min>graph->at(new_id).len_index.at(i)+graph->at(new_id).min){
            graph->at(b).min = graph->at(new_id).len_index.at(i)+graph->at(new_id).min;
        }
        if(is_get_in(back_index,new_id)){
        back_index->push_back(graph->at(new_id).index);
        }
       // std::cout << graph->at(new_id).index <<"ds5\n";
       // std::cout << graph->at(b).index <<"d5\n";
        recursive(back_index,b,graph);
      }
    }
   // if(!a){
  //      back_index.push_back();
 //   }
    //for(int a =0;a<back_index.size();a++){
   //    std::cout << back_index.at(a) << "\n";
   // }
  //  std::cout << graph->at(new_id).index <<" ds\n";
 //   std::cout << "s\n";
}
std::vector<struct dec_s> algorithmDecstra(std::vector<struct dec_s> graph,int start_index){ // Находит минимальное растояние от start_index до index_path
    int s= -1;
    s = getIdIndexDecstra(&graph,start_index);
    graph.at(s).min = 0;
    if(s!=-1){
    for(int i = 0;i<graph.at(s).size;i++){
        int b = getIdIndexDecstra(&graph,graph.at(i).indexes.at(i));
        if(graph.at(b).min>graph.at(s).len_index.at(i)+graph.at(s).min){
            graph.at(b).min = graph.at(s).len_index.at(i)+graph.at(s).min;
        }
        std::vector<int> a;
        a.push_back(graph.at(s).index);
        recursive(&a,b,&graph);
    }
    }
    return graph;
}
std::vector<struct dec_s> createGraph(const char* path_input){
    int sizeGraph;
    std::vector<struct dec_s> graph;
    std::ifstream fl(path_input);
    //std::cout << "Введите количество точек в графе:\n";
    //std::cin >> sizeGraph;
    fl >> sizeGraph;
  //  std::cout << sizeGraph << "\n";
    for(int i = 0;i<sizeGraph;i++){
        struct dec_s buffer;
        int index;
        int size;
        std::vector<int> indexes; // Связи с точками
        std::vector<int> len_index; // Растояние до точек
      //  std::cout << "Введите индекс точки:\n";
      //  std::cin >> index;
      fl >> index;
    //  std::cout << index << "\n";
        //std::cout << "Введите количество связей:\n";
       // std::cin >> size;
       fl >> size;
       // std::cout << size << "\n";
        int buff;
    for(int a = 0;a<size;a++){
          //  std::cout << "Введите индекс точки с которой связь:\n";
         //   std::cin >> buff;
            fl >> buff;
          //  std::cout << buff << "\n";
            indexes.push_back(buff);
           // std::cout << "Расстояние до этой точки:\n";
            fl >> buff;
          //  std::cout << buff << "\n";
         //   std::cin >> buff;
            len_index.push_back(buff);
    }
    buffer.index = index;
    buffer.size = size;
    buffer.indexes = indexes;
    buffer.len_index = len_index;
    graph.push_back(buffer);
    }
    return graph;
}
int main(){
std::cout << "Started:\n";
std::vector<struct dec_s> gr = createGraph("input");
std::vector<struct dec_s> new_gr = algorithmDecstra(gr,1);
std::cout <<"stop\n";
for(int i = 0;i<new_gr.size();i++){
    std::cout << "index-" << new_gr.at(i).index << "\n";
    std::cout << "min_length" << new_gr.at(i).min << "\n\n";
}
}