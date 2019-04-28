#ifndef WET_1_AVL_H
#define WET_1_AVL_H
#include <iostream>

template <typename S>
template <typename T>
class AvlTree {
    S data;
    T key;
    AvlTree* dad;
    AvlTree* right_son;
    AvlTree* left_son;
    int left_high;
    int right_high;
    int stability;

    void AvlTree_bin_add(const AvlTree& source){
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
        stabilty_adj(temp);

    }

    void Avltree_bin_remove(T& key) {
        AvlTree* temp = this->get(key);
        //if(temp->key != key)
        //throw itemDosen'tExsict;
        AvlTree* temp_dad;
        temp_dad = temp->dad;
        if( bin_tree_tail(temp) == 0){
            if(temp_dad != NULL)
                stabilty_adj(temp_dad);
            return;
        }
        AvlTree* next;
        next = temp->right_son;
        while (next != NULL && next->left_son != NULL )
            next = next->left_son;
        bin_tree_remove_swap(next,temp);
        temp_dad = temp->dad;
        bin_tree_tail (temp);
        if(temp_dad != NULL)
            stabilty_adj(temp_dad);
        return;
    }
    AvlTree* get(const T& key) {
        AvlTree* temp = this;
        while (temp->dad != NULL)
            temp = temp->dad;
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

    void stabilty_adj(AvlTree<T> *source) {
        while (source->dad != NULL) {
            high_upR(source);
            high_upL(source);
            source->stability = source->left_high - source->right_high;
            chose_and_roll(source);
            source = source->dad;
        }
        high_upR(source);
        high_upL(source);
        source->stability = source->left_high - source->right_high;
        chose_and_roll(source);

    }
    void high_upR(AvlTree<T> *source){
        if(source->right_son != NULL) {
            int high = max(source->right_son->right_high, source->right_son->left_high);
            high = high +1 ;
            source->right_high = high;
            return;
        }
        source->right_high = 0;

    }
    void high_upL(AvlTree<T> *source) {
        if (source->left_son != NULL){
            int high = max(source->left_son->right_high, source->left_son->left_high);
            high= high +1 ;
            source->left_high = high;
            return;
        }
        source->left_high = 0;

    }


    void LL_roll(AvlTree<T> *source) {
        AvlTree* tempAR = source->left_son->right_son;
        AvlTree* new_head = source->left_son;
        if (source->dad != NULL)
            dad_atach(source,new_head);
        new_head->dad = source->dad;
        new_head->right_son = source;
        source->dad = new_head;
        source->left_son = tempAR;
        if (tempAR != NULL)
            source->left_son->dad = source;
        high_upR(new_head->right_son);
        high_upL(new_head->right_son);
        new_head->right_son->stability = source->left_high - source->right_high;
        new_head->right_high++;


    }

    void LR_roll(AvlTree<T> *source) {
        AvlTree* tempBR = source->left_son->right_son->right_son;
        AvlTree* tempBL = source->left_son->right_son->left_son;
        AvlTree* new_head =  source->left_son->right_son;
        if (source->dad != NULL)
            dad_atach(source,new_head);
        new_head->dad = source ->dad;
        source ->left_son->dad = new_head;
        source -> dad = new_head;
        new_head->left_son = source ->left_son;
        new_head->right_son = source;
        if (tempBL != NULL)
            tempBL -> dad = new_head ->left_son;
        if (tempBR != NULL)
            tempBR -> dad = new_head ->right_son;
        new_head->left_son->right_son = tempBL;
        new_head->right_son->left_son = tempBR;
        high_upR(new_head->right_son);
        high_upL(new_head->right_son);
        new_head->right_son->stability = source->left_high - source->right_high;
        high_upR(new_head->left_son);
        high_upL(new_head->left_son);
        new_head->left_son->stability = source->left_high - source->right_high;
        new_head->left_high++;
        new_head->right_high++;

    }

    void RR_roll(AvlTree<T> *source) {
        AvlTree* tempAL = source->right_son->left_son;
        AvlTree* new_head = source->right_son;
        if (source->dad != NULL)
            dad_atach(source,new_head);
        new_head->dad = source->dad;
        new_head->left_son = source;
        source->dad = new_head;
        source->right_son = tempAL;
        if (tempAL != NULL)
            source->right_son->dad = source;
        if(source->right_son != NULL)
            source->right_high = max(source->right_son->right_high, source->right_son->left_high);
        if (source->left_son != NULL)
            source->left_high = max(source->left_son->right_high, source->left_son->left_high);
        high_upR(new_head->left_son);
        high_upL(new_head->left_son);
        new_head->left_son->stability = source->left_high - source->right_high;
        new_head->left_high++;

    }

    void RL_roll(AvlTree<T> *source) {
        AvlTree* tempBL = source->right_son->left_son->left_son;
        AvlTree* tempBR = source->right_son->left_son->right_son;
        AvlTree* new_head =  source->right_son->left_son;
        if (source->dad != NULL)
            dad_atach(source,new_head);
        new_head->dad = source ->dad;
        source->right_son->dad = new_head;
        source-> dad = new_head;
        new_head->left_son = source;
        new_head->right_son = source->right_son;
        if (tempBL != NULL)
            tempBL -> dad = new_head ->left_son;
        if (tempBR != NULL)
            tempBR -> dad = new_head ->right_son;
        new_head->right_son->left_son = tempBR;
        new_head->left_son->right_son = tempBL;
        high_upR(new_head->right_son);
        high_upL(new_head->right_son);
        new_head->right_son->stability = source->left_high - source->right_high;
        high_upR(new_head->left_son);
        high_upL(new_head->left_son);
        new_head->left_son->stability = source->left_high - source->right_high;
        new_head->left_high++;
        new_head->right_high++;

    }

    void dad_atach(AvlTree<T> *source,AvlTree<T> *new_head){
        if (source->dad->left_son != NULL && source->dad->left_son == source)
            source->dad->left_son = new_head;
        else
            source->dad->right_son =  new_head;
    }

    int bin_tree_tail(AvlTree<T> *temp) {
        int L = 0;
        int R = 0;
        if (temp->dad != NULL) {
            if(temp->dad->left_son != NULL) {
                if (temp->dad->left_son->get_key() == temp->get_key())
                    L = 1;
                else
                    R = 1;
            }
            if (temp->right_son == NULL && temp->left_son == NULL) {
                if (L == 1) {
                    temp->dad->left_son = NULL;
                    (temp->dad->left_high)--;
                } else {
                    temp->dad->right_son = NULL;
                    (temp->dad->right_high)--;
                }
                temp->dad = NULL;
                temp->right_son = NULL;
                temp->left_son = NULL;
                delete (temp);
                return 0;
            }

            if ((temp->right_son == NULL && temp->left_son != NULL) ||
                (temp->left_son == NULL && temp->right_son != NULL)) {
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
                temp->dad = NULL;
                temp->right_son = NULL;
                temp->left_son = NULL;
                delete (temp);
                return 0;
            }
        }
        if(temp->right_son == NULL || temp->left_son == NULL ) {
            if (temp->right_son == NULL)
                temp->left_son->dad = NULL;
            else
                temp->right_son->dad = NULL;
            temp->dad = NULL;
            temp->right_son = NULL;
            temp->left_son = NULL;
            delete (temp);
            return 0;
        }

        return 1;
    }

    void bin_tree_remove_swap(AvlTree<T> *next, AvlTree<T> *temp) {
        AvlTree<T> temp2(0);
        temp2.left_high = next->left_high;
        next->left_high = temp->left_high;
        temp->left_high = temp2.left_high;
        temp2.right_high = next->right_high;
        next->right_high = temp->right_high;
        temp->right_high = temp2.right_high;
        temp->stability = temp->right_high - temp->left_high;
        next->stability = next->right_high - next->right_high;
        if (temp->left_son != NULL && temp->left_son != next)
            temp->left_son->dad = next;
        if (temp->right_son != NULL && temp->right_son != next)
            temp->right_son->dad = next;
        if (next->left_son != NULL)
            next->left_son->dad = temp;
        if (next->right_son != NULL)
            next->right_son->dad = temp;
        if (next->dad != temp) {
            temp2.dad = next->dad;
            next->dad = temp->dad;
            temp->dad = temp2.dad;
        }else{
            next->dad = temp->dad;
            temp->dad = next;
        }
        if(temp->left_son != next) {
            temp2.left_son = next->left_son;
            next->left_son = temp->left_son;
            temp->left_son = temp2.left_son;
        }else{
            temp->left_son = next->left_son;
            next->left_son = temp;
        };
        if(temp->right_son != next) {
            temp2.right_son = next->right_son;
            next->right_son = temp->right_son;
            temp->right_son = temp2.right_son;
        }else{
            temp->right_son = next->right_son;
            next->right_son = temp;
        }
        if (next->dad != NULL ) {
            if (next->dad->left_son == temp)
                next->dad->left_son = next;
            else
                next->dad->right_son = next;
        }
        if (temp->dad->left_son == next)
            temp->dad->left_son = temp;
        else
            temp->dad->right_son = temp;

    }

    void chose_and_roll(AvlTree<T> *temp) {
        if (temp->left_son!=NULL)
            if (temp->stability == 2 && temp->left_son->stability > 0)
                temp->LL_roll(temp);
        if (temp->left_son!=NULL)
            if (temp->stability == 2 && temp->left_son->stability == -1)
                temp->LR_roll(temp);
        if (temp->right_son!=NULL)
            if (temp->stability == -2 && temp->right_son->stability < 0)
                temp->RR_roll(temp);
        if (temp->right_son!=NULL)
            if (temp->stability == -2 && temp->right_son->stability == 1)
                temp->RL_roll(temp);
    }
    int max(int num1, int num2) {
        if (num1 >= num2)
            return num1;
        return num2;
    }
public:
    AvlTree (T num):
            key(num),dad(NULL), right_son (NULL), left_son (NULL),
            left_high(0),right_high(0),stability(0){};
    //data TODO

    AvlTree(const AvlTree& source){};
    ~AvlTree()= default;
    AvlTree& get_r(const T& key){
        return *(get(key));
    }

    void Avltree_add (AvlTree& source) {

        AvlTree_bin_add(source);
    }
    void Avltree_remove (T key){
        AvlTree* temp = (get(key))->dad;
        Avltree_bin_remove(key);
    }

    T& get_key(){
        return key;
    }
    // T& get_data(){
    //   return data;
    // }
    int get_stability(){
        return stability;
    }
    /*void inorder(AvlTree* temp) {
        if (temp == NULL) return;
        inorder(temp->left_son);
        std::cout << temp->get_key() << std::endl;
        inorder(temp->right_son);
    }
    void inordercount(AvlTree* temp,int* counter) {
        if (temp == NULL) return;
        inordercount(temp->left_son,counter);
        (*counter)++;
        inordercount(temp->right_son,counter);
    }
    void inorderstabilty(AvlTree* temp,int* counter) {
        if (temp == NULL) return;
        inorderstabilty(temp->left_son,counter);
        if(this->get_stability() <= 2 && this->get_stability() >= -2)
            (*counter)++;
        inorderstabilty(temp->right_son,counter);
    }
    void postorder(AvlTree* temp) {
        if (temp == NULL) return;
        postorder(temp->left_son);
        postorder(temp->right_son);
        std::cout << temp->get_key() << std::endl;
    }
    void preorder(AvlTree* temp) {
        if (temp == NULL) return;
        std::cout << temp->get_key() << std::endl;
        preorder(temp->left_son);
        preorder(temp->right_son);
    }
    bool searchKey(T key){
        AvlTree* temp = this;
        while (temp->dad != NULL)
            temp = temp->dad;
        while (temp->get_key() != key) {
            if (key > (temp->get_key())) {
                if (temp->right_son == NULL)
                    return false;
                temp = temp->right_son;
            }
            if (key < (temp->get_key())) {
                if (temp->left_son == NULL)
                    return false;
                temp = temp->left_son;
            }
        }
        return true;
    }



    void deleteElement(int key){
        Avltree_remove(key);
    } */
    int countNodesInTree(){
        AvlTree* temp = this;
        while (temp->dad != NULL )
            temp = temp->dad;
        int counter;
        counter = 0;
        inordercount(temp,&counter);
        return (counter);

    }
    bool checkIfBalanced(){
        int counter = this->countNodesInTree();
        AvlTree* temp = this;
        while (temp->dad != NULL )
            temp = temp->dad;
        int balnce=0;
        inorderstabilty(temp,&balnce);
        if( balnce == counter)
            return true;
        return false;
    }
    AvlTree* gethed(){
        AvlTree* temp = this;
        while (temp->dad != NULL )
            temp = temp->dad;
        return temp;

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

    AvlTree& merge (const AvlTree& a, const AvlTree& b);
    S& operator[](const T& key);
};







#endif //WET_1_AVL_H





