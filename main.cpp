#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#define ARGCOUNT 2

using namespace cv;
using namespace std;

class Circle{
    private:
        Mat gray,src;
        vector<Vec3f> circles;
        int radius;

    public:
        int loadImage(const char * fileName){
            const char* filename = fileName;
            src = imread( samples::findFile( filename ), IMREAD_COLOR );
            if(src.empty()){
                cout << "Image not loaded";
                return EXIT_FAILURE;
                }
            return 1;
            }  
            
        void drawCircle(){
            cvtColor(src, gray, COLOR_BGR2GRAY);
            medianBlur(gray, gray, 5);
            HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                        gray.rows/1,
                        100, 30, 0, 0 
                         );
            for( size_t i = 0; i < circles.size(); i++ )
            {
                Vec3i c = circles[i];
                Point center = Point(c[0], c[1]);
                radius = c[2];
                cout << center <<  ", " <<radius;
                circle( src, center, radius, Scalar(0,0,255), 10, LINE_AA);
            }
            imwrite("output.png",src);

            }
};

int main(int argc, char** argv)
{
    if(argc != ARGCOUNT)
    {
        EXIT_FAILURE;
    }
    
    const char* filename = argv[1];
    Circle obj;
    
    obj.loadImage(filename);
    obj.drawCircle();

    return EXIT_SUCCESS;
}



