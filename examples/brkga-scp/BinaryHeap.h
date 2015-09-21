/**
 * \class BinaryHeap
 * \brief A binary heap data structure.
 *
 * This class builds a binary heap data structure, which provides O(lg n)
 * extractMin() and decreaseKey() operations.
 *
 * \author Rodrigo Franco Toso
 * \version 8.0.0
 * \date 08/12/2005
 *
 * Contact: rtoso@ic.uff.br
 * Created on: 01/09/2005
 *
 * License:
 *   Copyleft (C) 2005 by Rodrigo Franco Toso
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software Foundation,
 *   Inc. 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Changelog:
 *      [07/12/2005] Unfortunately, the author did not write this kind of
 *                   documentation.
 *      [08/12/2005] Fully documented.
 */

#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <vector>
#include <string>
#include <limits>
#include <iostream>

template< class T >
class BinaryHeap {
public:
    /**
     * \brief Default constructor.
     * \param n Heap's size.
     */
    explicit BinaryHeap(const unsigned n);

    /**
     * \brief Destructor.
     */
    ~BinaryHeap();

    /**
     * \brief Insert an item into the heap.
     * \param v Item to be inserted.
     * \param w Key.
     * \returns A <code>bool</code> indicating success or failure.
     */
    bool add(const unsigned v, const T& w);

    /**
     * \brief Insert an item into the heap.
     * \param v Item to be inserted.
     * \param w Key.
     * \returns A <code>bool</code> indicating success or failure.
     */
    bool insert(const unsigned v, const T& w);

    /**
     * \brief Extract the item with smallest key among the others.
     * \returns The item.
     */
    unsigned extractMin();

    /**
     * \brief Decrease the key of an item.
     * \param v Item.
     * \param w New key.
     * \returns A <code>bool</code> indicating success or failure.
     */
    bool decreaseKey(const unsigned v, const T& w);
    bool increaseKey(const unsigned v, const T& w);

    /**
     * \brief Get the key of an item.
     * \param v Item.
     * \returns Item's key.
     */
    T getKey(const unsigned v) const;

    /**
     * \brief Get the number of items into the heap.
     * \returns Heap's size.
     */
    unsigned sizeV() const;

    /**
     * \brief Query about the heap's status.
     * \returns A <code>bool</code> indicating if the heap is empty.
     */
    bool isEmpty() const;

    void print(const std::string& before) const;

private:
    /**
     * \brief Adjust an item to conform with heap's protocol.
     * \param v Item possibly in wrong position.
     */
    void adjustHeapUp(unsigned v);

    /**
     * \brief Adjust an item to conform with heap's protocol.
     * \param v Item possibly in wrong position.
     */
    void adjustHeapDown(unsigned v);

    /**
     * \brief Return the index of i's left child.
     * \param i Item.
     * \returns i's left child index.
     */
    unsigned left(const unsigned i) const;

    /**
     * \brief Return the index of i's right child.
     * \param i Item.
     * \returns i's right child index.
     */
    unsigned right(const unsigned i) const;

    /**
     * \brief Return the index of i's parent.
     * \param i Item.
     * \returns i's parent index.
     */
    unsigned parent(const unsigned i) const;

    unsigned maxSize;               ///< Heap's size.
    unsigned itemCounter;           ///< Number of items currently on heap.
    std::vector< unsigned > heap;        ///< Binary heap priority queue data structure.
    std::vector< T > keys;        		///< Keys.
    std::vector< unsigned > position;    ///! Pointer to i's position on heap.
};

/******************************************************************************
 *                        Constructors and Destructors                        *
 *****************************************************************************/
template< class T >
BinaryHeap< T >::BinaryHeap(const unsigned n) : maxSize(n), itemCounter(0), heap(0), keys(n), position(n) {
    for(unsigned i = 0; i < maxSize; i++) { position[i] = std::numeric_limits< unsigned >::max(); }
}

template< class T >
BinaryHeap< T >::~BinaryHeap() {}

/******************************************************************************
 *                                 Algorithms                                 *
 *****************************************************************************/
template< class T >
inline bool BinaryHeap< T >::add(const unsigned v, const T& w) {
    // Adjust item's key:
    keys[v] = w;

    // Insert v into the heap:
    heap.push_back(v);
    position[v] = itemCounter;

    // Adjust the heap:
    ++itemCounter;
    adjustHeapUp(position[v]);
    return true;
}

template< class T >
inline bool BinaryHeap< T >::insert(const unsigned v, const T& w) {
    return add(v, w);
}

template< class T >
inline unsigned BinaryHeap< T >::extractMin() {
    // Save the minimum:
    const unsigned min = heap[0];

    // Place the last item into heap's first position:
    heap[0] = heap[--itemCounter];

    // Adjust the positions:
    position[heap[0]] = 0;
    position[min] = std::numeric_limits< unsigned >::max();

    // Adjust the heap:
    adjustHeapDown(0);
    return min;
}

template< class T >
inline bool BinaryHeap< T >::decreaseKey(const unsigned v, const T& w) {
	if(position[v] == std::numeric_limits< unsigned >::max() || keys[v] <= w) { return false; }

    // Update the key:
    keys[v] = w;
    // Adjust the heap:
    adjustHeapUp(position[v]);
    return true;
}

template< class T >
inline bool BinaryHeap< T >::increaseKey(const unsigned v, const T& w) {
	if(position[v] == std::numeric_limits< unsigned >::max() || keys[v] >= w) { return false; }

    // Update the key:
    keys[v] = w;
    // Adjust the heap:
    adjustHeapDown(position[v]);
    return true;
}

/******************************************************************************
 *                            Getterrs and Setters                            *
 *****************************************************************************/
template< class T >
inline T BinaryHeap< T >::getKey(const unsigned v) const {
    return keys[v];
}

template< class T >
inline unsigned BinaryHeap< T >::sizeV() const {
    return itemCounter;
}

template< class T >
inline bool BinaryHeap< T >::isEmpty() const {
    return (itemCounter == 0);
}

/******************************************************************************
 *                              Private Functions                             *
 *****************************************************************************/
template< class T >
inline void BinaryHeap< T >::adjustHeapUp(unsigned v) {
    while(parent(v) != std::numeric_limits< unsigned >::max() && keys[heap[parent(v)]] > keys[heap[v]]) {
        // Swap 'v' with 'parent(v)':
        unsigned pv = position[heap[v]];
        unsigned ppv = position[heap[parent(v)]];
        unsigned parentV = parent(v);

        unsigned temp = heap[v];
        heap[v] = heap[parentV];
        heap[parentV] = temp;

        // Adjust positions:
        position[heap[v]] = pv;
        position[heap[parentV]] = ppv;

        v = parentV;
    }
}

template< class T >
inline void BinaryHeap< T >::adjustHeapDown(unsigned v) {
    while(left(v) < itemCounter) {
        unsigned son = left(v);		// Assume that child with smallest key is the left one.
        if(right(v) < itemCounter && keys[heap[right(v)]] < keys[heap[left(v)]]) { son = right(v); }

        if(keys[heap[v]] > keys[heap[son]]) {
            // Swap 'son' with 'v':
            unsigned pv = position[heap[v]];
            unsigned ppv = position[heap[son]];

            // Swapping:
            unsigned temp = heap[son];
            heap[son] = heap[v];
            heap[v] = temp;

            // Adjust positions:
            position[heap[pv]] = pv;
            position[heap[ppv]] = ppv;

            v = son;
        }
        else { return ; }
    }
}


template< class T >
inline unsigned BinaryHeap< T >::left(const unsigned i) const {
    return ((2*i) + 1);
}

template< class T >
inline unsigned BinaryHeap< T >::right(const unsigned i) const {
    return ((2*i) + 2);
}

template< class T >
inline unsigned BinaryHeap< T >::parent(const unsigned i) const {
    if(i == 0) { return std::numeric_limits< unsigned >::max(); }
    if((i % 2) == 0) { return ((i/2) - 1); }
    else { return (i/2); }
}

template< class T >
void BinaryHeap< T >::print(const std::string& before) const {
    std::cout << before;
    if(itemCounter == 0) { return; }
    unsigned bound = itemCounter-1;
    for(unsigned i = 0; i < bound; i++) {
        std::cout << heap[i] << "(" << keys[heap[i]] << ")" << ", ";
        std::cout.flush();
    }

    std::cout << heap[bound] << "(" << keys[heap[bound]] << ")]" << std::endl;
}

#endif
