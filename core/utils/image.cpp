#include "./image.hpp"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"

std::tuple<double, double, double> rgb_to_cairo(uint8_t r, uint8_t g, uint8_t b){
    return {(double)r / 255, (double)g / 255, (double)b / 255};
};

tuple<uint8_t, uint8_t, uint8_t> load_image(const string& image){
    cv::Mat img = cv::imread(image, cv::IMREAD_COLOR);
    if(img.empty()){
        return {0, 0, 0};
    }

    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

    int hist[4096] = {0};

    for(int y = 0; y < img.rows; y++){
        for(int x =0; x < img.cols; x++){
            cv::Vec3b c = img.at<cv::Vec3b>(y, x);
            int r = c[2] >> 4;
            int g = c[1] >> 4;
            int b = c[0] >> 4;
            
            int idx = (r << 8) | (g << 4) | b;
            hist[idx]++;

        }
    }

    int maxIdx = 0;
    for(int i = 1; i < 4096; i++){
        if(hist[i] > hist[maxIdx]) maxIdx = i;
    }

    int r  = ((maxIdx >> 8) & 0xF) * 16 + 8;
    int g  = ((maxIdx >> 4) & 0xF) * 16 + 8;
    int b  = ((maxIdx & 0xF)) * 16 + 8;

    return {r, g, b};
}
