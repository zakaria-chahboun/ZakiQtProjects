# Qt5 Projects

**Integrate** OpenCV 3 With **Qt5 Widgets** (QImage) by ***<a href="http://develnoter.blogspot.com/2012/05/integrating-opencv-in-qt-gui.html">"CVImageWidget"</a>*** Class :sparkles:

Add this on your (.pro) file:

```QMAKE
SOURCES += CVImageWidget/cvimagewidget.cpp
HEADERS  += CVImageWidget/cvimagewidget.h

# OpenCV Path : My Variable
OPENCV_PATH = C:\Qt\OpenCV3.2.0vc14

INCLUDEPATH += $$OPENCV_PATH/opencv/build/include

LIBS += $$OPENCV_PATH/mybuild/bin/libopencv_core320.dll
LIBS += $$OPENCV_PATH/mybuild/bin/libopencv_highgui320.dll
LIBS += $$OPENCV_PATH/mybuild/bin/libopencv_imgcodecs320.dll
LIBS += $$OPENCV_PATH/mybuild/bin/libopencv_imgproc320.dll
LIBS += $$OPENCV_PATH/mybuild/bin/libopencv_features2d320.dll
LIBS += $$OPENCV_PATH/mybuild/bin/libopencv_calib3d320.dll
# Fore Video Capture
LIBS += $$OPENCV_PATH/mybuild/bin/libopencv_videoio320.dll
# Fore Object (face detecting ..)
LIBS += $$OPENCV_PATH/mybuild/bin/libopencv_objdetect320.dll
```


> Note : Change `OPENCV_PATH` With Your (OpenCV Path), Also Change `LIBS += $$OPENCV_PATH/mybuild/bin/` With Correct Path :innocent:

-----------------
<img src="/View.JPG">

-----------------

<img src="https://upload.wikimedia.org/wikipedia/fr/thumb/c/c8/Twitter_Bird.svg/1259px-Twitter_Bird.svg.png" width="20px"> <a href="https://twitter.com/Zaki_Chahboun">@Zaki_Chahboun</a>
<br>
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/c2/F_icon.svg/1024px-F_icon.svg.png" width="20px"> <a href="https://facebook.com/zakaria.chahboun.2018">Zakaria Chahboun</a>


