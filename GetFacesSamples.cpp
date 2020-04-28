//C++头文件
#include <iostream>
#include <vector>
#include <fstream>

//Opencv头文件
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
/*人脸数据采集部分*/
using namespace cv;
using namespace std;
//加载haar库的人脸特征数据
string haar_face_datapath = "C:/opencv/build/etc/haarcascades/haarcascade_frontalface_alt_tree.xml";
int main(int argc, char** argv) {
	VideoCapture capture(0); // open camera
	if (!capture.isOpened()) {
		printf("could not open camera...\n");
		return -1;
	}
	Size S = Size((int)capture.get(CAP_PROP_FRAME_WIDTH), (int)capture.get(CAP_PROP_FRAME_HEIGHT));
	//获取数据宽度高度
	int fps = capture.get(CAP_PROP_FPS);
	//获取图片的帧数
	CascadeClassifier faceDetector;//级联分类器
	faceDetector.load(haar_face_datapath);//把人脸特征加入到分类器中

	Mat frame;
	namedWindow("camera-demo", WINDOW_FULLSCREEN);
	vector<Rect> faces;  //创建一个人脸目标序列
	int count = 0;
	while (capture.read(frame)) {
		flip(frame, frame, 1); //防止左右颠倒
		faceDetector.detectMultiScale(frame, faces, 1.1, 1, 0, Size(100, 120), Size(400, 450));
		for (int i = 0; i < faces.size(); i++) {
			Mat dst;
			resize(frame(faces[i]), dst, Size(500, 500));//把每个图片都设置成同样的尺寸
			imwrite(format("C:/Users/xpp19/Documents/Myfaces/face_%d.jpg", count++), dst);
			rectangle(frame, faces[i], Scalar(0, 0, 255), 2, 8, 0);//绘制矩形框
		}
		imshow("camera-demo", frame);
		char c = waitKey(10);
		if (c == 27) {
			break;
		}
		count++;
	}

	capture.release();

	waitKey(0);
	return 0;
}