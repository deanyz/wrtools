#include <wr_hash.hpp>
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv)
{
    int rand_count = 1000;
    std::cout << "begin..." << std::endl;
    wrtool::hash::consistent_hash<std::string, std::string> consis_hash{};

    std::cout << "add nodes..." << std::endl;
    consis_hash.add_virtual_node("08b5027f-5c16-484c-86fd-eacbea673dbb", "192.168.1.101");
    consis_hash.add_virtual_node("c8f26e6e-c1d7-4ca6-8b47-3d0c2ceecd48", "192.168.1.101");
    consis_hash.add_virtual_node("9fcff797-ee1a-4e81-9197-96fd90d0fa2f", "192.168.1.102");
    consis_hash.add_virtual_node("536034d7-829c-47b5-99f9-581a4d850e0a", "192.168.1.102");
    consis_hash.add_virtual_node("af6b6ba2-1286-4b61-9051-0aed955af54c", "192.168.1.103");
    consis_hash.add_virtual_node("df7f6c97-cce0-46c8-a3a3-e1c290dda5d4", "192.168.1.103");

    std::cout << "show debug info" << std::endl;
    consis_hash.show_debug_info();

    //std::cout << "enter a data:" << std::endl;
    //std::string  data;
    //std::cin >> data;

    //std::cout << "get actual node..." << std::endl;
    //std::string node = consis_hash.get_actual_node(data);
    
    //std::cout << "locate [" << data << "] on node [" << node << "] " << std::endl;
    
    std::map<std::string, size_t> node_rate;
    //node_rate.emplace("node1", 0);
    //node_rate.emplace("node2", 0);
    //node_rate.emplace("node3", 0);
    //node_rate.emplace("node4", 0);
    //node_rate.emplace("node5", 0);
    //node_rate.emplace("node6", 0);
    node_rate.emplace("08b5027f-5c16-484c-86fd-eacbea673dbb", 0);
    node_rate.emplace("c8f26e6e-c1d7-4ca6-8b47-3d0c2ceecd48", 0);    
    node_rate.emplace("9fcff797-ee1a-4e81-9197-96fd90d0fa2f", 0);
    node_rate.emplace("536034d7-829c-47b5-99f9-581a4d850e0a", 0);
    node_rate.emplace("af6b6ba2-1286-4b61-9051-0aed955af54c", 0);
    node_rate.emplace("df7f6c97-cce0-46c8-a3a3-e1c290dda5d4", 0);

    
    std::srand(std::time(0)); //use current time as seed for random generator
    for (int i = 0; i < rand_count; i++ ) {
        int rand = std::rand()%100000;
        //std::cout << "Debug: " << i <<"  rand:" << rand<< std::endl;
        auto temp_node = consis_hash.get_virtual_node(std::to_string(rand));
        //std::cout << "Debug: " << temp_node << std::endl;
        node_rate[temp_node]++;
    }

    std::cout << "Debug" << std::endl;
    for (auto i : node_rate) {
        std::cout << i.first << " : " << float(i.second)/rand_count << std::endl;
    }
    return 0;
}
