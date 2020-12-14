#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <chrono>
using namespace cv;
using namespace std;



int main() {
    VideoCapture cap("solidWhiteRight.mp4");

    if(!cap.isOpened()) {
        cout << "Error" << endl;
        return -1;
    }
    namedWindow("Road");
    namedWindow("Trapeze");

    int top = 120;
    int base = 400;
    int height = 170;
    int maxtop = 500;
    int maxbase = 460;
    int maxheight = 500;

    //создаем ползунки
    createTrackbar("Top", "Road", &top, maxtop);
    createTrackbar("Base", "Road", &base, maxbase);
    createTrackbar("Height", "Road", &height,maxheight);

    while(1) {
        Mat src;
        cap >> src;

        if (src.empty())
            break;

        Point2f src_vertices[4];
        src_vertices[0] = Point(490 - top, maxheight - height);
        src_vertices[1] = Point(490 + top, maxheight - height);
        src_vertices[2] = Point(500 + base, maxheight);
        src_vertices[3] = Point(500 - base, maxheight);

        Point2f dst_vertices[4];
        dst_vertices[0] = Point(0, 0);
        dst_vertices[1] = Point(640, 0);
        dst_vertices[2] = Point(640, 480);
        dst_vertices[3] = Point(0, 480);

        // сегментируем внутреннее пространство трапеции в новую матрицу
	Mat M = getPerspectiveTransform(src_vertices, dst_vertices);
	Mat dst(480, 640, CV_8UC3);
 	warpPerspective(src, dst, M, dst.size());

        // рисуем эту трапецию
 	line(src, Point(488 - top, maxheight - height),
      		 Point(488 + top, maxheight - height), Scalar(0, 255, 0), 1);
  	line(src, Point(488 + top, maxheight - height),
      		 Point(505 + base, src.rows - 1), Scalar(0, 255, 0), 1);
  	line(src, Point(505 + base, src.rows - 1), Point(505 - base, src.rows - 1),
      		 Scalar(0, 255, 0), 1);
  	line(src, Point(505 - base, src.rows - 1),
      		 Point(488 - top, maxheight - height), Scalar(0, 255, 0), 1);


        //вывоодим полученные изображения
        imshow("Road", src);
        imshow("Trapeze", dst);
        // 
        char c=(char)waitKey(25);
        if(c==27)
            break;

    }
    cap.release();
    destroyAllWindows();
    return 0;
}
