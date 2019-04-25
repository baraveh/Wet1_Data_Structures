#ifndef WET_1_AVL_H
#define WET_1_AVL_H
#include <iostream>


template <typename T>
class AvlTree {
    T data;
    T key;
    AvlTree* dad;
    AvlTree* right_son;
    AvlTree* left_son;
    int left_high;
    int right_high;
    int stability;

    void AvlTree_bin_add(AvlTree& source){
        AvlTree* source_p =&source;
        AvlTree* temp = this->get(source.get_key());
        //if ( source.get_key() == temp->key)
        //   throw itemAlredyExcist();
        if(source.get_key() < temp->key) {
            temp->left_son = source_p;
            temp->left_son->dad = temp;
            temp->left_high++;
        }
        else {
            temp->right_son =source_p;
            temp->right_son->dad = temp;
            temp->right_high++;
        }
        temp->stability = temp->right_high - temp->left_high;
        stabilty_adj(temp);

    }

    void Avltree_bin_remove(T& key) {
        AvlTree* temp = this->get(key);
        if( bin_tree_tail(temp) == 0){
            stabilty_adj(temp);
            return;
        }
        AvlTree* next;
        next = this->right_son;
        while (next->left_son != NULL)
            next = next->left_son;
        bin_tree_remove_swap(next,temp);
        bin_tree_tail (temp);
        stabilty_adj(temp);
    }
    AvlTree* get(const T& key) {
        AvlTree* temp = this;
        while (temp->get_key() != key) {
            if (key > (temp->get_key())) {
                if (temp->right_son == NULL)
                    return temp;
                temp = temp->right_son;
            }
            if (key < (temp->get_key())) {
                if (temp->left_son == NULL)
                    return temp;
                temp = temp->left_son;
            }
        }
        return temp;
    }

    void stabilty_adj(AvlTree<T> *temp) {
        while (temp->dad != NULL) {
            temp = temp->dad;
            if(temp->right_son != NULL)
                temp->right_high = max(temp->right_son->right_high, temp->right_son->left_high);
            if (temp->left_son != NULL)
                temp->left_high = max(temp->left_son->right_high, temp->left_son->left_high);
            temp->stability = temp->right_high - temp->left_high;
        }
    }

    void LL_roll(AvlTree<T> *temp) {
        if (temp->dad->left_son == temp)
            temp->dad->left_son = temp->left_son;
        else
            temp->dad->right_son = temp->left_son;
        temp->left_son->dad = temp->dad;
        temp->left_son = temp->left_son->right_son;
        temp->left_son->dad->left_son = temp;
        temp->dad = temp->left_son->dad;
        temp->left_son->dad = temp;
        stabilty_adj(temp);
    }

    void LR_roll(AvlTree<T> *temp) {
        if (temp->dad->left_son == temp)
            temp->dad->left_son = temp->left_son->right_son;
        else
            temp->dad->right_son = temp->left_son->right_son;
        temp->left_son->dad = temp->left_son->right_son;
        temp->left_son->right_son->dad = temp->dad;
        temp->dad = temp->left_son->right_son;
        temp->left_son->dad = temp->left_son->right_son;
        temp->left_son->right_son = temp->left_son->right_son->left_son;
        temp->left_son->right_son->dad = temp->left_son;
        temp->dad->left_son = temp->left_son;
        temp->left_son = temp->dad->right_son;
        temp->left_son->dad = temp;
        temp->dad->right_son = temp;
        stabilty_adj(temp->dad->left_son);
        stabilty_adj(temp);


    }

    void RR_roll(AvlTree<T> *temp) {
        if (temp->dad->left_son == temp)
            temp->dad->left_son = temp -> right_son;
        else
            temp->dad->right_son = temp->right_son;
        temp->right_son->dad = temp->dad;
        temp->right_son = temp->right_son->left_son;
        temp->right_son->dad->right_son = temp;
        temp->dad = temp->right_son->dad;
        temp->right_son->dad = temp;
        stabilty_adj(temp);
    }

    void RL_roll(AvlTree<T> *temp) {
        if (temp->dad->left_son == temp)
            temp->dad->left_son = temp->right_son->left_son;
        else
            temp->dad->right_son = temp->right_son->left_son;
        temp->right_son->dad = temp->right_son->left_son;
        temp->right_son->left_son->dad = temp->dad;
        temp->dad = temp->right_son->left_son;
        temp->right_son->dad = temp->right_son->left_son;
        temp->right_son->left_son = temp->right_son->left_son->right_son;
        temp->right_son->left_son->dad = temp->right_son;
        temp->dad->right_son = temp->right_son;
        temp->right_son = temp->dad->left_son;
        temp->right_son->dad = temp;
        temp->dad->left_son = temp;
        stabilty_adj(temp->dad->right_son);
        stabilty_adj(temp);

    }

    int bin_tree_tail(AvlTree<T> *temp) {
        int L = 0;
        int R = 0;
        if (temp->dad->left_son == temp)
            L = 1;
        else
            R = 1;
        if (temp->right_son == NULL && temp->left_son == NULL) {
            if (L == 1) {
                temp->dad->left_son = NULL;
                (temp->dad->left_high)--;
            } else {
                temp->dad->right_son = NULL;
                (temp->dad->right_high)--;
            }
            temp->dad = NULL;
            return 0;
        }
        if ((temp->right_son == NULL && temp->left_son != NULL) || (temp->left_son == NULL && temp->right_son != NULL)) {
            if (temp->left_son != NULL) {
                if (L == 1) {
                    temp->dad->left_son = temp->left_son;
                    (temp->dad->left_high)--;
                } else {
                    temp->dad->right_son = temp->left_son;
                    (temp->dad->right_high)--;
                }
                temp->left_son->dad = temp->dad;
            }
            if (temp->right_son != NULL) {
                if (L == 1) {
                    temp->dad->left_son = temp->right_son;
                    (temp->dad->left_high)--;
                } else {
                    temp->dad->right_son = temp->right_son;
                    (temp->dad->right_high)--;
                }
                temp->right_son->dad = temp->dad;
            }
            return 0;
        }
        return 1;
    }

    void bin_tree_remove_swap(AvlTree<T> *next, AvlTree<T> *temp) {
        AvlTree<T> *temp2;
        temp2->left_high = next->left_high;
        next->left_high = temp->left_high;
        temp->left_high = temp2->left_high;
        temp2->right_high = next->right_high;
        next->right_high = temp->right_high;
        temp->right_high = temp2->right_high;
        temp->stability = temp->right_high - temp->left_high;
        next->stability = next->right_high - next->right_high;
        if (temp->left_son != NULL)
            temp->left_son->dad = next;
        if (temp->right_son != NULL)
            temp->right_son->dad = next;
        if (next->left_son != NULL)
            next->left_son->dad = temp;
        if (next->right_son != NULL)
            next->right_son->dad = temp;
        temp2->dad = next->dad;
        next->dad = temp->dad;
        temp->dad = temp2->dad;
        temp->dad->left_son = temp;
        temp2->left_son = next->left_son;
        next->left_son = temp->left_son;
        temp->left_son = temp2->left_son;
        temp2->right_son = next->right_son;
        next->right_son = temp->right_son;
        temp->right_son = temp2->right_son;
        temp->dad->left_son = temp;
        if (next->dad->left_son == temp)
            next->dad->left_son = next;
        else
            next->dad->right_son = next;

    }

    void chose_and_roll(AvlTree<T> *temp) {
        if (temp->stability == 2 && temp->left_son->stability > 0)
            temp->LL_roll(temp);
        if (temp->stability == 2 && temp->left_son->stability == -1)
            temp->LR_roll(temp);
        if (temp->stability == 2 && temp->right_son->stability < 0)
            temp->RR_roll(temp);
        if (temp->stability == 2 && temp->right_son->stability == 1)
            temp->RL_roll(temp);
    }
    int max(int num1, int num2) {
        if (num1 >= num2)
            return num1;
        return num2;
    }
public:
    AvlTree(T num,T Data):
            key(num),data(Data),dad(NULL), right_son (NULL), left_son (NULL),
            left_high(0),right_high(0),stability(0){};
    AvlTree(const AvlTree& source){};
    ~AvlTree()= default;
    AvlTree& get_r(const T& key){
        return *(get(key));
    }

    void Avltree_add (AvlTree& source){
        AvlTree_bin_add(source);
        AvlTree* temp = this->get(source.get_key());
        while (temp->dad != NULL && temp->stability < 2 && temp->stability > -2  ){
            temp = temp->dad;
        }
        if(temp->stability == 2 || stability == -2 )
            chose_and_roll(temp);
    }
    void Avltree_remove (T key){
        AvlTree* temp = (get(key))->dad;
        Avltree_bin_remove(key);
        while (temp->dad != NULL ){
            chose_and_roll(temp);
            temp = temp->dad;
        }
    }
    T& get_key(){
        return key;
    }
    T& get_data(){
        return data;
    }
    int get_stability(){
        return stability;
    }
    void inorder(AvlTree* temp) {
        if (temp == NULL) return;
        inorder(temp->left_son);
        std::cout << temp->get_key() << std::endl;
        inorder(temp->right_son);
    }


    // class itemDosentExcist : public std::exception {
    //   public:
    //     const char *what() const {
    //       return "Item Dosent Excist";
    // }
    //};
    //class itemAlredyExcist : public std::exception {
    //public:
    //  const char *what() const {
    //    return "Item Alredy Excist";
    // }
    //};
};







#endif //WET_1_AVL_H





