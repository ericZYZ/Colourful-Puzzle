#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include <iostream>
#include <iterator>

std::vector<int> sort_indexes(std::vector<int> v) {

  // initialize original index locations
  std::vector<int> idx(v.size());
  iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  sort(idx.begin(), idx.end(),
       [&v](int i1, int i2) {return v[i1] < v[i2];});

  return idx;
}

using namespace std;
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    // get the first line of input
    string first;
    getline(cin, first);
    
    // split line into tokens
    istringstream buf(first);
    istream_iterator<std::string> beg(buf), end;
    vector<std::string> tokens(beg, end);
    int num_bricks = stoi(tokens[2]);
    int height = stoi(tokens[0]);
    int width = stoi(tokens[1]);
        
    vector<vector<int>> color2d;
    vector<vector<int>> value2d;
    vector<int> value_sum1d;
    for (int i=0;i<num_bricks;i++)
    {
        string tmp;
        getline(cin, tmp);
        istringstream buf(tmp);
        istream_iterator<std::string> beg(buf), end;
        vector<std::string> tokens(beg, end);
        int tok_len = tokens.size();
        
        vector<int> color1d; 
        vector<int> value1d;
        for(int j=0;j<(tok_len/2);j++)
        {
            color1d.push_back(stoi(tokens[j*2]));
            value1d.push_back(stoi(tokens[j*2+1]));   
        }
        color2d.push_back(color1d);
        value2d.push_back(value1d);
        
        int sum = accumulate(value1d.begin(), value1d.end(), 0);
        value_sum1d.push_back(sum);
    }
    
    vector<int> value_sort_index;
    value_sort_index = sort_indexes(value_sum1d);
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // The actual algorithm starts here. We sort the bricks by the total value of individual bricks,      //
    // and then use a greedy-like algorithm to look up from the max value to min value. If the current    //
    // brick can be inserted in the current column, we insert it. Otherwise we look further until no more //
    // bricks can be inserted.                                                                            //
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    int final_value = 0;
    
    // fill columns one by one
    vector<vector<int>> result2d;
    for(int column=0;column<width;column++)
    {
        int flags[height]={0}; // indicate which rows are filled in the current column
        vector<int> result1d;

        int id1 = value_sort_index.size();
        int id2 = value_sort_index.size();
        while(id1>0)
        {   
            int curr_index = value_sort_index[id1-1];
            vector<int> brick_color = color2d[curr_index]; // array storing color of this brick
            bool insert = true;
            
            for(auto color:brick_color)
            {
                if(flags[color]!=0) // color is already filled, cannot insert this brick, break
                {
                    insert = false;
                    break;
                }
            }
            if(insert==true)
            {
                final_value = final_value + value_sum1d[curr_index];
                
                // if insert, reduce the array size that store the sorted index by 1
                value_sort_index.erase(value_sort_index.begin()+id1-1); 
                result1d.push_back(curr_index);
                id2--;
                id1 = id2;
                for(auto color:brick_color)
                {
                  flags[color]=1;
                }
            }
            else
            {
                id1--;
            }
            
        }
        result2d.push_back(result1d);
    }

    // output results
    cout<<final_value<<endl;
    for(int i=0;i<result2d.size();i++)
    {
        for(auto e:result2d[i])
        {
            cout<<e<<" ";
        }
        cout<<endl;
    }
    return 0;
}