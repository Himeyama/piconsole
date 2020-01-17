#include <iostream>
#include <opencv2/opencv.hpp>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;
using namespace cv;

class PiConsole{
    public:
        Mat img;
        int row;
        int col;

        string color_bg(string text, Vec3b bgr){
            return "\e[48;2;"
                + to_string(bgr[2])
                + ";"
                + to_string(bgr[1])
                + ";"
                + to_string(bgr[0])
                + "m"
                + text
                + "\e[0m";
        }

        string color_dot(string text, Vec3b bgr1, Vec3b bgr2){
            return "\e[38;2;"
                + to_string(bgr1[2])
                + ";"
                + to_string(bgr1[1])
                + ";"
                + to_string(bgr1[0])
                + "m"
                + color_bg(text, bgr2);
        }

        void putcc(Vec3b bgr){
            cout << color_bg(" ", bgr) << ends; 
        }

        void putcd(Vec3b bgr1, Vec3b bgr2){
            cout << color_dot("▀", bgr1, bgr2) << ends; 
        }

        void resize(){
            cv::resize(img, img, Size(col * 9, row * 18));
        }

        void print(){
            Vec3d bgr1, bgr2;
            for(int y = 0; y < row-1; y++){
                for(int x = 0; x < col; x++){
                    bgr1 = Vec3b(0, 0, 0);
                    bgr2 = Vec3b(0, 0, 0);
                    for(int i=0; i<9; i++){
                        for(int j=0; j<9; j++){
                            bgr1 += img.at<Vec3b>(i+y*18, j+x*9);
                        }
                    }
                    for(int i=0; i<9; i++){
                        for(int j=0; j<9; j++){
                            bgr2 += img.at<Vec3b>(i+y*18+9, j+x*9);
                        }
                    }
                    bgr1 /= 81;
                    bgr2 /= 81;
                    putcd((Vec3b)bgr1, (Vec3b)bgr2);
                }
                cout << "\n" << ends;
            }
        }


};

int main(int argc, char* argv[]){
    if(argc != 2) exit(EXIT_FAILURE);

    PiConsole piconsole;
    struct winsize ws;

    piconsole.img = imread(argv[1], 1);
    ioctl( STDOUT_FILENO, TIOCGWINSZ, &ws );
    piconsole.row = ws.ws_row;
    piconsole.col = ws.ws_col;
    piconsole.resize();
    piconsole.print();

    return 0;
}