#include <raylib.h>
#include <cmath>

// void UpdateGrid(Grid& gridInfo){|


// }


void MakeGrid(Vector2 ratio, int scale){

    //Centering the grid
    Vector2 st; //= {GetScreenWidth()/2, GetScreenHeight()/2};
    Vector2 nst = {(ratio.x*scale)/2, (ratio.y*scale)/2};

    st.x = st.x - nst.x;
    st.y = st.y - nst.y;

    //DrawLine(st.x, st.y, st.x + ratio.x*scale, st.y + ratio.y*scale, RED);
    /*
    //Starts at left right goes straight forward
    DrawLine(st.x, st.y, st.x + ratio.x*scale, st.y, RED); 
    //Goes down
    DrawLine(st.x, st.y, st.x, st.y + ratio.y*scale, RED); 
    //Starts Left Right goesdown
    DrawLine(st.x + ratio.x*scale, st.y, st.x + ratio.x*scale, st.y + ratio.y*scale, RED); 
    //Starts downleft goes right
    DrawLine(st.x, st.y + ratio.y*scale, st.x + ratio.x*scale, st.y + ratio.y*scale, RED); 
    */

    // --> Make the Squares inside
    int dist = scale;
    for (int i = 0; i <= ratio.y; i++){
        DrawLine(st.x, st.y + i*dist, st.x + ratio.x*scale, st.y + i*dist, BLUE); 
    }

    for (int i = 0; i <= ratio.x; i++){
        DrawLine(st.x + i*dist, st.y, st.x + i*dist, st.y + ratio.y*scale, BLUE);
    }

    //So for a given place/square in the grid, its local starting point would be st.x + x*scale, st.y + y*scale

    
}