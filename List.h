#ifndef LIST_H
#define LIST_H
#include <iostream>

//defines a template class for List
template <typename T>
class List{
    private:
        struct listNode{ //Each node in the list contains data of type T, a pointer to the next node, and a pointer to the previous node
            T data;
            listNode * next;
            listNode * prev;
        };

        //declares pointers to the front and back of the list 
        listNode * head;
        listNode * tail;

        //iterates through each node in the list from the starting node until null, printing each node's data.
        void print(listNode * start){
            listNode * curr = start;
            while (curr){
                std::cout << *(curr->data) << std::endl;
                curr = curr->next;
            }
        }

        //For use in merge sort. Finds the node in the middle of the given two nodes, then half-severs the list by setting the next pointer of the left partition to null.
        //Leaves the previous pointer of the right partition alone, b/c it's useful when recursively calling mergeSort.
        typename List<T>::listNode * split(listNode * firstNode, listNode * lastNode){
            listNode * left = firstNode;
            listNode * right = lastNode;
            while (left->next != right && left != right && left){
                left = left->next;
                right = right->prev;
            }
            right = left->next;
            left->next = NULL;
            return right;
        }

        //For use in merge sort. Merges the list together in descending order 
        typename List<T>::listNode * merge(listNode * nodeOne, listNode * nodeTwo){
            if (!nodeOne){ //if either one of the nodes is null it returns the other node
                return nodeTwo;
            } else if (!nodeTwo){
                return nodeOne;
            }

            if (*(nodeOne->data) > *(nodeTwo->data)){ //sorts in DESCENDING order
                nodeOne->next = merge(nodeOne->next, nodeTwo); //recursively merges the two nodes until sorted
                nodeOne->next->prev = nodeOne; //makes sure the node after nodeOne is linked to nodeOne via prev ptr
                nodeOne->prev = NULL; //Since nodeOne was larger in this case, it must be the start of this partition, ergo its prev ptr must be null
                return nodeOne; //returns the start of the partition 
            } else {
                nodeTwo->next = merge(nodeOne, nodeTwo->next); //Duality from above
                nodeTwo->next->prev = nodeTwo;
                nodeTwo->prev = NULL;
                return nodeTwo;
            }
        }

        //Sorts the list via splitting the list into various sub-lists, then merging the sub-lists in descending order
        //O(NlogN)
        typename List<T>::listNode * mergeSort(listNode * head, listNode * tail){

            if (!head || !head->next){ //If the list passed through is empty or has only one item, returns the one item / null.
                return head;
            }

            listNode * middle = split(head, tail); //sets the middle ptr to what was given by the split function
            head = mergeSort(head, middle->prev); //recursively splits the list down on the left side until one/zero items in each
            middle = mergeSort(middle, tail); //same as above but for right side
            return merge(head, middle); //merges together all of the lists in descending order, returning the head of the new sorted list
        }

        //swaps the position of two nodes
        void swap(listNode * nodeOne, listNode * nodeTwo){

            //case for if the two nodes are next to each other
            if (nodeOne->next == nodeTwo || nodeTwo->next == nodeOne){
                nodeOne->next = nodeTwo->next; 
                nodeTwo->prev = nodeOne->prev; 
                nodeOne->prev = nodeTwo; 
                nodeTwo->next = nodeOne; 
                if (nodeOne->prev) //These if statements just make sure that it doesn't try to access anything that's null
                    nodeOne->prev->next = nodeOne;
                if (nodeOne->next)
                    nodeOne->next->prev = nodeOne;
                if (nodeTwo->prev)
                    nodeTwo->prev->next = nodeTwo;
                if (nodeTwo->next)
                    nodeTwo->next->prev = nodeTwo;

            //if the two nodes are not right next to each other
            } else {
            listNode temp = *nodeOne; //need a temporary node that isn't just a ptr to store the next and prev info for a node 

            nodeOne->next = nodeTwo->next;
            nodeOne->prev = nodeTwo->prev;
            if (nodeOne->prev) //makes sure it isn't accessing something from null
                nodeOne->prev->next = nodeOne;
            if (nodeOne->next)
                nodeOne->next->prev = nodeOne;

            nodeTwo->next = temp.next; //since we already set nodeOne's prev and next, we need to use the temp node to update nodeTwo
            nodeTwo->prev = temp.prev;
            if (nodeTwo->prev)
                nodeTwo->prev->next = nodeTwo;
            if (nodeTwo->next)
                nodeTwo->next->prev = nodeTwo;
            } 
        }

        //Sorts a list via finding the largest item in the non-sorted partition, bringing it to the front, and iterating until complete
        //O(N^2)
        typename List<T>::listNode * selectionSort(listNode * head){
            listNode * currOuter = head;
            listNode * currInner = head;
            listNode * newHead = head;
            bool headAlreadySet = false;
            while (currOuter){ //While it hasn't reached the end of the list:

                listNode * largest = currInner = currOuter; //sets the largest and the current inner ptr (start of unsorted partition) to where the current outer ptr is.
                while (currInner){ //while it hasn't reached the end of the list:
                    if (*(largest->data) < *(currInner->data)){
                        largest = currInner; //if it encounters an item larger than the beginning of the unsorted partition, it updates the ptr to the largest item.
                    }
                    currInner = currInner->next; //moves forward through list
                }

                /*If it's currently on its first iteration this will detect that and set the new head to the largest in the list.
                I had to use a bool because there were cases where it was encountering the old head a second time after having swapped it, and set the new head to the later one.
                This was causing the new head to actually be set to a ways into the list, making the ones before it only accessible by prev ptrs.*/
                if (currOuter == head && !headAlreadySet){
                    newHead = largest;
                    headAlreadySet = true;
                }

                if (largest != currOuter) //only bothers swapping the two nodes if the largest isn't already where it should be 
                    swap(currOuter, largest);

                currOuter = largest->next; //iterates based off of the largest node, bc if it was the outer node it might be a ways into the list after being swapped.
            }

            return newHead; 
        }

    public:
        List() : head(NULL), tail(NULL){} //constructs an empty list with null pointers to head and tail
        ~List(){ //iterates through the list, freeing memory for each node.
            listNode * curr = head;
            while (curr){
                listNode * nodeToDelete = curr;
                curr = curr->next;
                delete nodeToDelete;
            }
        }

        void print(){print(head);} //passes the head of the list for the user to the real print function

        void append(T data){ //dynamically allocates memory for a new node, setting the data and then setting the node to the end of the list. 
            listNode * newNode = new listNode;
            newNode->next = NULL;
            newNode->data = data;

            if (!head){
                newNode->prev = NULL;
                head = newNode;
                tail = newNode;
            } else {
                newNode->prev = tail;
                tail->next = newNode;
                tail = newNode;
            }
        }

        void mergeSort(){ //calls the private merge sort function, updates the new head, then finds the new tail and updates that as well.
            head = mergeSort(head, tail);
            listNode * curr = head;
            while (curr->next){
                curr = curr->next;
            }
            tail = curr;
        }

        void selectionSort(){ //same as above but for selection sort
            head = selectionSort(head);
            listNode * curr = head;
            while (curr->next){
                curr = curr->next;
            }
            tail = curr;
        }
};

#endif