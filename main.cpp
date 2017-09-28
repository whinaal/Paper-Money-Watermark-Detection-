#include <iostream>
#include <stdlib.h>
#include "opencv\cv.h"
#include "opencv\highgui.h"
using namespace std;
using namespace cv;

//Fungsi Histogram Equalization
void hist_eq(IplImage* src, IplImage* histogram)
{
    IplImage* hsv = cvCreateImage(cvGetSize(src),8,3);
    IplImage* h = cvCreateImage(cvGetSize(src),8,1);
    IplImage* s = cvCreateImage(cvGetSize(src),8,1);
    IplImage* v = cvCreateImage(cvGetSize(src),8,1);

    //convert to HSV
    cvCvtColor(src,hsv,CV_RGB2HSV);
    //split image to single channel
    cvSplit(hsv,h,s,v,NULL);
    //equalize histogram in channel 1
    cvEqualizeHist(v,v);
    cvMerge(h,s,v,NULL,hsv);
    cvCvtColor(hsv,histogram,CV_HSV2RGB);
}

void thres(IplImage *src, IplImage *gray)
{
    IplImage* imgRed = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
    IplImage* imgGreen = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
    IplImage* imgBlue = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
    cvSplit(src,imgBlue,imgGreen,imgRed,NULL);
    cvThreshold(imgRed,gray,195,255,CV_THRESH_BINARY);
    cvThreshold(imgBlue,gray,195,255,CV_THRESH_BINARY);
}


int main()
{
    IplImage* src=cvLoadImage("10.jpg",CV_LOAD_IMAGE_COLOR);
    IplImage* dst=cvCloneImage(src);
    IplImage* gray= cvCreateImage(cvGetSize(src),8,1);
    IplImage* smooth=cvCloneImage(dst);
    //Smooth : Menghilangkan Noise
    cvSmooth(dst,smooth,3);
    cvShowImage("Smoothing",smooth);
    //hist_eq(smooth,smooth);
    //cvShowImage("smooth",smooth);
    //cvNot(dst,negative);
    //cvCvtColor(negative,negative,CV_YCrCb2RGB);
    //cvShowImage("negative",negative);
    //cvSaveImage("neg.jpg",negative);

    //cvCvtColor(smooth,gray,CV_RGB2GRAY);
    //cvCvtColor(src,dst,CV_RGB2GRAY);


    //Opening image -> Meratakan Cahaya
    IplImage *openingImg = cvCloneImage(src);
    cvDilate(src, openingImg,NULL,2);
    cvErode(openingImg, src,NULL,2);
    cvShowImage("OPENING",src);
    //Fungsi histogram equalization -> Menambah contrast
    hist_eq(src,openingImg);
    cvShowImage("hist",openingImg);
    //Thres untuk memisahkan warna biru dan merah
    thres(openingImg,gray);

    cvShowImage("GRAY",gray);


    /*cvThreshold(gray,gray,224,255,CV_THRESH_BINARY);
    //cvShowImage("EDIT",gray);*/

    //cvSobel(gray,gray,1,1,3);
    //cvShowImage("ediit",gray);

    IplImage* dilateImg = cvCloneImage(gray);
    IplImage* erodeImg = cvCloneImage(gray);

    cvDilate(gray,dilateImg,NULL,3);
    cvErode(dilateImg,erodeImg,NULL,3);

    /* src is the source image which you want to mask
     * mask is a single channel binary image as a mask
     * result is the image with the same size, depth, channel with src
     */

    /*IplImage* mask=cvCloneImage(src);
    IplImage* result=cvCloneImage(src);

    cvZero(result);
    CvSize sz = cvSize(src->width, src->height);

    IplImage* refImg = cvCreateImage(sz, src->depth, src->nChannels);
    cvZero(refImg);
    cvOr(src, refImg, result, mask);
    cvShowImage("MASK",mask);

    CvRect rect = cvRect(40, 70, 500, 600 );
    IplImage* bgModel=cvCloneImage(mask);
    IplImage* fgModel=cvCloneImage(src);
    */
// grabCut(src,mask,rect,bgModel,fgModel,5,GC_EVAL); ini g bisa euy

    cvWaitKey(0);
    return 0;
}
