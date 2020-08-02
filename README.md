## Locating-a-Defined-Area-in-the-Star

 *Author: Vefak Murat Akman*

 ---
[//]: # (Image References)

[image1]: ./img/result.png "Rotated"
[image2]: ./img/result2.png "Normal"



### My enviroment
* OpenCV version   = 3.14.0
* CMake version    = 3.10.2
* Ubuntu version   = 18.04.4 LTS
 

### Install OpenCV with extra modules

Please, follow steps in 	[OpenCV installation](https://docs.opencv.org/3.4/d7/d9f/tutorial_linux_install.html)

* To install `xfeatures2d`, make sure that both opencv and opencv_contrib repos are downloaded
* At building step of installation process, use the following cmake command instead of the one in link

```shell
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local OPENCV_EXTRA_MODULES_PATH= /home/vefak/opencv_contrib/modules/ -D OPENCV_ENABLE_NONFREE:BOOL=ON ..
```


### Building and Running Code

Just execute `build_and_run.sh ` file.
```shell
source build_and_run.sh 
```

Hit any key to change current frame and open next one

### Results

#### Rotated Image Place
![alt text][image1]

#### Normal Image Place

![alt text][image2]