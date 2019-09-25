#include <opencv2/opencv.hpp>
#include <string>

std::string print_color_background(std::string text, unsigned char r, unsigned char g, unsigned char b){
    std::string str;
    str = "\e[48;2;" + std::to_string(r);
    str += ";";
    str += std::to_string(g);
    str += ";";
    str += std::to_string(b);
    str += "m";
    str += text;
    str += "\e[0m";
    return str;
}

std::string print_color_dot(std::string text, unsigned char rc, unsigned char gc, unsigned char bc, unsigned char r, unsigned char g, unsigned char b){
    std::string str;
    str = "\e[38;2;" + std::to_string(rc);
    str += ";";
    str += std::to_string(gc);
    str += ";";
    str += std::to_string(bc);
    str += "m";
    str += print_color_background(text, r, g, b);
    return str;
}

void putcc(unsigned r, unsigned g, unsigned b){
    std::cout << print_color_background(" ", r, g, b); 
}

void putcd(unsigned rc, unsigned gc, unsigned bc, unsigned r, unsigned g, unsigned b){
    std::cout << print_color_dot("▀", rc, gc, bc, r, g, b); 
}

int main(int argc, char *argv[]){
    cv::Mat img;
    img = cv::imread(argv[1], 1);
    
    double sum[3];
    double sum1[3];
    for(int y=0; y<23; y++){
        for(int x=0; x<80; x++){
            sum[0] = 0;
            sum[1] = 0;
            sum[2] = 0;
            sum1[0] = 0;
            sum1[1] = 0;
            sum1[2] = 0;
            for(int i=0; i<9; i++){
                for(int j=0; j<9; j++){
                    sum[0] += img.at<cv::Vec3b>(i+y*18, j+x*9)[0];
                    sum[1] += img.at<cv::Vec3b>(i+y*18, j+x*9)[1];
                    sum[2] += img.at<cv::Vec3b>(i+y*18, j+x*9)[2];
                }
            }
            for(int i=0; i<9; i++){
                for(int j=0; j<9; j++){
                    sum1[0] += img.at<cv::Vec3b>(i+y*18+9, j+x*9)[0];
                    sum1[1] += img.at<cv::Vec3b>(i+y*18+9, j+x*9)[1];
                    sum1[2] += img.at<cv::Vec3b>(i+y*18+9, j+x*9)[2];
                }
            }
            sum[0] /= 81;
            sum[1] /= 81;
            sum[2] /= 81;
            sum1[0] /= 81;
            sum1[1] /= 81;
            sum1[2] /= 81;
            putcd((unsigned char)sum[2], (unsigned char)sum[1], (unsigned char)sum[0], (unsigned char)sum1[2], (unsigned char)sum1[1], (unsigned char)sum1[0]);
        }
    }
    
    return 0;
}