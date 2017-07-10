#include "utils.hpp"
#include "node.hpp"

#include <iostream>
#include <cstdlib>

using namespace std;


int main(){

    srand(time(NULL));

    Node *root;

    for(int i=0; i<10; i++){
        root = new Node();

        cout << "A eq. gerada do node é (torça para ser pequena): ";
        root->print_node_d();
        cout << endl;

        vector<double> x = {double (random()%10) };

        cout << "Para x = " << x[0] << ", O valor da eq. do node é: " << root->eval(x) << endl << endl;
    }

    Node *copy = root->get_copy();

    cout << "cópia do ultimo:";
    copy->print_node_d();
    cout << endl;

    return 0;
}
