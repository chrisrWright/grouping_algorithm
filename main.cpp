/*Author: Christopher Wright
 Date created: 4/08/2018
 Last edited: 4/19/2018
 Description: This program's purpose is to simulate the break up of a company into subcompanies to prevent monopoly. After the input is received, the output will be a list of companies, in lexicographical order, that are allowed to be together according to the input. The input consists of two integers 'n' to indicate the amount of companies, and 'm' to indicate the amount of sub groups requested. For the next 'i' lines, the user will input the company numbers that cannot be grouped together. If 'j' is on the ith line then 'j' and 'i' cannot be together. The end of each input line should have a 0;
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
template <class Object>
class Matrix
{
public:
    Matrix( int rows=0, int cols=0 ) : array( rows )
    {
        for( int i = 0; i < rows; i++ )
            array[ i ].resize( cols );
    }
    void resize( int rows, int cols )
    {
        array.resize(rows);
        for( int i = 0; i < rows; i++ )
            array[ i ].resize( cols );
    }
    const vector<Object> & operator[]( int row ) const
    { return array[ row ]; }
    vector<Object> & operator[]( int row )
    { return array[ row ]; }
    int numrows( ) const
    { return array.size( ); }
    int numcols( ) const
    { return numrows( ) ? array[ 0 ].size( ) : 0; }
private:
    vector< vector<Object> > array;
    
};

class Company
{
public:
    Company(int size){matrix.resize(size, size);}
    
    void setMat(int subComp, int line)
    {
        matrix[line][subComp-1] = 1;
      
    }
    
    bool backtracking(int numComp, int numSub, int find)
    {
        if(find == numComp)
        {
            return true;
        }
        
        for(int i = 1; i <= numSub; i++)
        {
            if(legal(numComp, find, i))
            {
                storage[find]= i;
                if(backtracking(numComp, numSub, find+1))
                {
                    return true;
                }
                storage[find] = 0;
            }
               
        }
        return false;
    }
    
    bool legal(int numComp, int find, int compare)
    {
        for(int i = 0; i < numComp; i++)
        {
            for(int j = 0; j < numComp; j++)
            {
                if(matrix[find][j] == 1 && compare == storage[j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool outputComps(int numComp, int numSub)
    {
        int zero = 0, temp = 1;
        storage.resize(numComp);
        
        if(backtracking(numComp, numSub, zero) == false)
        {
            
            cout << "no solution"<<endl;;
            return true;
        }
        else
        {
            for(int i = 0; i < numSub; i++)
            {
                for(int j = 0; j < numComp; j++)
                {
                    if(temp == storage[j])
                    {
                        cout << j+1 << " ";
                        
                    }
                }
                temp++;
                cout << endl;
                
            }
            cout<<endl;
            return true;
        }
        
    }
    
private:
    Matrix<int> matrix;
    vector <int> storage;
};

int main()
{
    int numComp = 0, numSub = 0, subComp = -1, line = 0;
    cin >> numComp >> numSub;
    Company company(numComp);

    for(int i = 0; i < numComp; i++)
    {
        while(subComp != 0)
        {
            cin >> subComp;
    
            if(subComp!=0)
            {
                company.setMat(subComp, line);
            }
        }
        
        subComp = -1;
        line++;
    }
    
    company.outputComps(numComp, numSub);
  
    return 0;
}
