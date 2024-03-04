#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
int main() {
    cv::Mat image = cv::imread("C:/Users/huyan/Desktop/11.jpg");
    cout<<image.size<<endl;
    if (image.empty()){
        cout<<"image is None";
        return 0;
    }
    imshow("tuxiang",image);
    cv::waitKey(0);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}