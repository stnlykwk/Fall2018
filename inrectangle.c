/* 
1. Write a function that matches the following 
declaration:

    int InRectangle( float pt[2], float rect[4] );

2. Argument pt[2] defines a point on the plane: 
pt[0] is the x-coordinate, pt[1] is the y-coordinate.
3. Argument rect[4] defines a rectangle on the same 
plane. rect[0] and rect[1] define the x- and 
y- cordinates respectively of one corner of the 
rectangle. rect[2] and rect[3] define the 
opposite corner.
4. Coordinates may be any valid floating point value, 
including negative values.
5. The function returns int 0 (false) for any point 
that lies outside the rectangle, and 1 (true) for 
any other point (i.e. points inside and on the 
boundary of the rectangle). 
 */

int InRectangle( float pt[2], float rect[4] )
{
    float xmin = rect[0], xmax = rect[2], 
    ymin = rect[1], ymax = rect[3];
//set boundaries    
    if(rect[2] < xmin)
        xmin = rect[2];

    if(rect[0] > xmax)
        xmax = rect[0];

    if(rect[3] < ymin)
        ymin = rect[3];

    if(rect[1] > ymax)
        ymax = rect[1];
//check if pt is within boundaries
    if((pt[0] >= xmin && pt[0] <= xmax) &&
        (pt[1] >= ymin && pt[1] <= ymax)){
        return 1;
    }
    else{
        return 0;
    }
}
