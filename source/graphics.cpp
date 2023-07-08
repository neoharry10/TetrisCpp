#include <raylib.h>
#include <cmath>

// void UpdateGrid(Grid& gridInfo){|


// }


void MakeGrid(Vector2 ratio){
    int scale = 20;

    Vector2 st = {GetScreenWidth()/2, GetScreenHeight()/2};
    Vector2 nst = {(ratio.x*scale)/2, (ratio.y*scale)/2};

    st.x = st.x - nst.x;
    st.y = st.y - nst.y;

    //DrawLine(st.x, st.y, st.x + ratio.x*scale, st.y + ratio.y*scale, RED);

    DrawLine(st.x, st.y, st.x + ratio.x*scale, st.y, RED); 
    DrawLine(st.x, st.y, st.x, st.y + ratio.y*scale, RED); 
    DrawLine(st.x + ratio.x*scale, st.y, st.x + ratio.x*scale, st.y + ratio.y*scale, RED); 
    DrawLine(st.x, st.y + ratio.y*scale, st.x + ratio.x*scale, st.y + ratio.y*scale, RED); 

    // --> Make the Squares inside

}