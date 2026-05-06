#pragma once 
#include <vector>
#include <stdexcept>
#include <iostream>

struct HeapOrder {
    double price;
    int timestamp;
    bool operator<(const HeapOrder& other) const { return price < other.price; } // Max-heap
};

class HeapQueue{ 
    private: 
        std::vector<HeapOrder> heap;
        void up(int idx){
            while (idx > 0){
                int parent = (idx - 1) /2;
                if(heap[parent] < heap[idx]){
                    std::swap(heap[parent], heap[idx]);
                    idx = parent; 
                } else { 
                    break; 
                }
            }
        }
        void down(int idx) { 
            int n = heap.size(); 
            while (true) { 
                int left = 2 * idx + 1; 
                int right = 2 * idx + 2; 
                int largest = idx; 
                if (left < n && heap[largest] < heap[left]){
                    largest = left; 
                }   
                if (right < n && heap[largest] < heap[right]){
                    largest = right; 
                }   
                if (largest != idx) {
                    std::swap(heap[idx], heap[largest]);
                    idx = largest; 
                } else { 
                    break; 
                }
            }
        }
    public: 
        HeapQueue() = default;
        void push(const HeapOrder& order) { 
            heap.push_back(order);
            up(heap.size() - 1);
        }
        void pop() { 
            if (heap.empty()){
                return;
            }
            heap[0] = heap.back(); 
            heap.pop_back(); 
            if (!heap.empty()){
                down(0);
            
            }
        }
        const HeapOrder& top() const { 
            if (!heap.empty()) {
                return heap[0];
            }
            throw std::out_of_range("Heap is empty");
        }
        bool empty() const {
            return heap.empty();
        }
        size_t size() const {
            return heap.size();
        
        }

};