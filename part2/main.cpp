#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

const char WHITESPACE(32);
int product_count, m, q, height, width, current_max;
vector<int> matrix;

void load_matrix(string fileName){
    //load file and store variables
    ifstream file;
    file.open(fileName.c_str());
    file >> m;
    file >> q;
    product_count = m%q;

    //load all integers
    while(!file.eof()){
        int i;
        file >> i;
        matrix.push_back(i);
    }

    //calculate matrix width and height
    file.close();
    file.open(fileName.c_str());
    height = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n') - 1;
    width = matrix.size()/height;

    file.close();
}

int get_value(int x, int y){
    //return int at x/y in matrix
    int index = x + width*y;
    return matrix.at(index);
}

void calculate_horizontal(){
    //determine depth based on m, depth is how many x elements over we can go before our m pushes things out of bounds
    int depth = width-product_count;
    
    //calculate max
    for(int y = 0; y < height; y++){
        for(int x = 0; x <= depth; x++){
            //set amount to first value in selection
            int amnt = get_value(x, y);
            //calculate each value in selection
            for(int i = 1; i < product_count; i++){
                amnt *= get_value(x+i, y);
                amnt %= q;
            }
            //check if this is our max
            if(amnt > current_max)
                current_max = amnt;
        }
    }
}

void calculate_vertical(){
    //determine depth based on m, depth is how many y elements over we can go before our m pushes things out of bounds
    int depth = height-product_count;
    
    //calculate max
    for(int x = 0; x < width; x++){
        for(int y = 0; y <= depth; y++){
            //set amount to first value in selection
            int amnt = get_value(x, y);
            //calculate each value in selection
            for(int i = 1; i < product_count; i++){
                amnt *= get_value(x, y+i);
                amnt %= q;
            }
            //check if this is our max
            if(amnt > current_max)
                current_max = amnt;
        }
    }
}

void calculate_diagonal(){
    //determine depth of both x and y
    int depth_x = width-product_count,
        depth_y = height-product_count;

    //calculate max left->right diagonal
    for(int x = 0; x <= depth_x; x++){
        for(int y = 0; y <= depth_y; y++){
            //set amount to first value in selection
            int amnt = get_value(x, y);
            //calculate each value in selection
            for(int i = 1; i < product_count; i++){
                amnt *= get_value(x+i, y+i);
                amnt %= q;
            }
            //check if this is our max
            if(amnt > current_max)
                current_max = amnt;
        }
    }

    depth_y = height - depth_y;
    //calculate max right->left diagonal
    for(int x = 0; x <= depth_x; x++){
        for(int y = height-1; y >= depth_y; y--){
            //set amount to first value in selection
            int amnt = get_value(x, y);
            //calculate each value in selection
            for(int i = 1; i < product_count; i++){
                amnt *= get_value(x+i, y-i);
                amnt %= q;
            }
            //check if this is our max
            if(amnt > current_max)
                current_max = amnt;
        }
    }
}

void print_matrix(){
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            cout << get_value(x, y) << " ";
        }
        cout << endl;
    }
}

int main(){
    //load matrix from file
    load_matrix("big_mat");
    current_max = 0;

    //calculate values
    calculate_horizontal();
    calculate_vertical();
    calculate_diagonal();

    //print values
    cout << "Maximum Value: " << current_max << endl;

    return 0;
}