#pragma once
#include <vector>
#include <list>
#include <map>
#include <limits>
#include <functional>
#include <iostream>

namespace wrtool {
    namespace hash {
        template<class D, class N>
        class consistent_hash {
            public:
                consistent_hash();
                consistent_hash(std::vector<N> &actual_nodes);
                consistent_hash(std::map<N, N> &virtual_actual_nodes);
                ~consistent_hash();

                void add_actual_node(const N & node);
                void add_virtual_node(const N & virtual_node, const N &actual_node);

                const N & get_actual_node(const D & data);
                const N & get_virtual_node(const D & data);

                void show_debug_info ();
            private :
                consistent_hash(const consistent_hash& ) = delete;
                const consistent_hash& operator=(const consistent_hash&) = delete;
                void update_node_poses();

            private :
                //D data;
                std::map<N, N> virtual_actual_nodes;
                std::vector<N> virtual_nodes;
                std::map<size_t, N> virtual_node_poses;
                static const size_t hash_ring_length = 512;
        };

        template<class D, class N>
        const size_t consistent_hash<D, N>::hash_ring_length ;


        template<class D, class N>
        consistent_hash<D,N>::consistent_hash() 
        {
        }

        template<class D, class N>
        consistent_hash<D,N>::~consistent_hash() 
        {
        }
        
        template<class D, class N>
        consistent_hash<D,N>::consistent_hash(std::vector<N> &actual_nodes) 
        {
            //this->virtual_nodes = actual_nodes; 
            for (auto node : actual_nodes) {
                this->virtual_nodes.push_back(node);
                this->virtual_actual_nodes.emplace(node, node);
            }

            update_node_poses();
        }

        template<class D, class N>
        consistent_hash<D, N>::consistent_hash(std::map<N, N> &virtual_actual_nodes)
        {
            for (auto i : virtual_actual_nodes) {
                this->virtual_nodes.push_back(i->first);
                this->virtual_actual_nodes.emplace(i->first, i->second);
            }

            update_node_poses();
        }

        template<class D, class N>
        void consistent_hash<D, N>::add_actual_node(const N & node)
        {
            this->virtual_nodes.push_back(node);
            this->virtual_actual_nodes.emplace(node, node);

            update_node_poses();
        }

        template<class D, class N>
        void consistent_hash<D, N>::add_virtual_node(const N & virtual_node, const N &actual_node)
        {
            this->virtual_nodes.push_back(virtual_node);
            this->virtual_actual_nodes.emplace(virtual_node, actual_node);

            update_node_poses();
        }

        template<class D, class N>
        void consistent_hash<D, N>::update_node_poses()
        {
            std::hash<N> hash_fn;
            for(auto &i : this->virtual_nodes) {
                size_t hash_ret = hash_fn(i);
                this->virtual_node_poses.emplace(hash_ret % hash_ring_length, i);
            }
        }

        template<class D, class N>
        const N & consistent_hash<D, N>::get_actual_node(const D & data)
        {
            auto virtual_node = get_virtual_node(data);

            return this->virtual_actual_nodes[virtual_node];
            
        }

        template<class D, class N>
        const N & consistent_hash<D, N>::get_virtual_node(const D & data)
        {
            std::hash<D> hash_fn;

            size_t hash_ret = hash_fn(data);
            
            //std::cout << "[DEBUG] hash_ret = " << hash_ret << std::endl;

            size_t data_pos = hash_ret % hash_ring_length;
            //std::cout << "[DEBUG] data_pos = " << data_pos << std::endl;

            auto rbegin = this->virtual_node_poses.rbegin();
            if (data_pos >= rbegin->first) {
                auto begin = this->virtual_node_poses.begin();
                return begin->second;
            }

            for (auto &i : this->virtual_node_poses) {
                if (i.first >= data_pos)
                    return i.second;
            }
        }

        template<class D, class N>
        void consistent_hash<D, N>::show_debug_info()
        {
            //std::map<N, N> virtual_actual_nodes;
            //std::vector<N> virtual_nodes;
            //std::map<size_t, N> virtual_node_poses;
            
            std::cout << "[DEBUG] hash_ring_length: " << hash_ring_length << std::endl;

            std::cout << "[DEBUG] virtual_nodes: " << std::endl;
            for (auto &i : this->virtual_nodes) {
                std::cout << i << "    " ;
            }
            std::cout << std::endl;

            std::cout << "[DEBUG] virtual_actual_nodes: " << std::endl;
            for (auto &i : this->virtual_actual_nodes) {
                std::cout << i.first << " : " << i.second << std::endl;
            }

            std::cout << "[DEBUG] virtual_node_poses: " << std::endl;
            for (auto &i : this->virtual_node_poses) {
                std::cout << i.first << " : " << i.second << std::endl;
            }
        }
    }
}
