
<p align="center">
    <img src="images/Opentracker.png", width="480">
</p>

**Why most of the trackers are written by matlab? Slow speed, lots of extra-packages, need loads of money to buy the licences, version compliance problems (gcc4.9 gcc5.0 oh my god)... Anyway, I hate that! C++ is fast and clear! I even doubt that the FPS measured by using matlab is really meaningful, especially for actual and embedded system use! So I will re-implement those trackers by cpp day by day, keep the clarity and less extra-packages in mind, hope you like it!**

<p align="center">
    <img src="images/Crossing.gif", width="480">
</p>

**2018/06/28 -- New features** Now it support automatic initialization with Web camera using OpenPose.

## Supported tracker (more in progressing):
Included                                   | Tracker    
-------------------------------------------|---------------
:ballot_box_with_check:                    | CSK          
:ballot_box_with_check:                    | KCF          
:ballot_box_with_check:                    | DSST          
:ballot_box_with_check:                    | GOTURN         
 :hammer:                    | ECO         
 :hammer:                    | C-COT
 :hammer:                    | SRDCF
 :hammer:                    | SRDCF-Deep                           

## Supported Dataset (more in progressing):

Included                                   | Dataset    | Reference
-------------------------------------------|--------------|-----------
:ballot_box_with_check:                    | VOT-2017     | [Web](http://votchallenge.net/vot2017/dataset.html)
:ballot_box_with_check:                    | TB-2015      | [Web](http://cvlab.hanyang.ac.kr/tracker_benchmark/index.html)
:ballot_box_with_check:                    | TLP          | [Web](https://amoudgl.github.io/tlp/)
:ballot_box_with_check:                    | UAV123       | [Web](https://ivul.kaust.edu.sa/Pages/Dataset-UAV123.aspx)

## Supported Autodetection with Web Camera
Included                                   | Dataset    | Reference
-------------------------------------------|--------------|-----------
:ballot_box_with_check:                    | OpenPose     | [Web](https://github.com/CMU-Perceptual-Computing-Lab/openpose)

## Tested Operating Systems
Included                   | OS    
---------------------------|-------------
:ballot_box_with_check:    | Ubuntu 16.04
:ballot_box_with_check:    | macOS Sierra
 :hammer:                  | NVIDIA Jetson TX1/2
 :hammer:                  | Rasperberry PI 3
 :hammer:                  | Windows10

# Quick start -- Ubuntu
To run a test with ECO without Deep feature, no need to install Caffe, CUDA etc.
```
cd eco
make -j`nproc`
./runecotracker.bin
```
# Quick start -- macOS
```
brew install tesseract
cd eco
make  -j`nproc`
./runecotracker.bin
```


# Compile and Run 
--------------------------------
For the **environment settings** and detailed procedures (with all the packages from the very beginning), refer to: [[My DeeplearningSettings](https://github.com/rockkingjy/DeepLearningSettings)].

The only extra-package is: **Opencv3.x** (already installed if you follow the environment settings above).

Of course, for trackers that use Deep features, you need to install [[**caffe**](https://github.com/rockkingjy/caffe)] (maybe I will use Darknet with C in the future, I like Darknet :lips: ), and change the **makefile** according to your path. Compile of caffe refer to : [[Install caffe by makefile](https://github.com/rockkingjy/DeepLearningSettings/blob/master/caffe.md)].

If you want to autodetection the people with web camera, you need to install [[OpenPose](https://github.com/CMU-Perceptual-Computing-Lab/openpose)]. 


## Parameters setting
If you want to use Openpose, in `./makefile`, set `OPENPOSE=1`, else set `OPENPOSE=0`.

Change the datasets, in `inputs/readdatasets.hpp`, change the number of `string databaseType = databaseTypes[1];`

Change the path of datasets, in `inputs/readdatasets.cc`, change the `path` to your path of data.

## To use web camera with openpose
By raising your two arms higher than your nose, it will atomatically detect the person and start the tracking programme.


## Run to compare all the trackers at the same time
```
make all
./trackerscompare.bin
```

## Run ECO
### Compile without Caffe
If you don't want to compile with Caffe, that means you cannot use Deep features, set in **eco/makefile**: `USE_CAFFE=0`.

If you don't want to compile with CUDA, that means you cannot use Deep features, set in **eco/makefile**: `USE_CUDA=0`.

### Compile with Caffe
If you want to compile with Caffe, set in **eco/makefile**: `USE_CAFFE=1` (CUDA will automatically set to use), and set the according caffe path of your system in **eco/makefile**:
```
ifeq ($(USE_CAFFE), 1)
CXXFLAGS+= -DUSE_CAFFE
LDFLAGS+= -L/media/elab/sdd/mycodes/caffe/build/lib -lcaffe 
CXXFLAGS+= -I/media/elab/sdd/mycodes/caffe/build/include/ -I/media/elab/sdd/mycodes/caffe/include/ 
endif
```

Download a pretrained [[VGG_CNN_M_2048.caffemodel (370 MB)](https://drive.google.com/file/d/1-kYYCcTR7gBZyHM5oVChNvu0Q9XPdva3/view?usp=sharing)], put it into folder: **eco/model**

For using Deep features, in **eco/parameters.cc**, change to `bool useDeepFeature = true;`.

### Datasets settings
Change the path of your test images in **eco/runecotracker.cc**.

Change the datasets, in **eco/runecotracker.cc**, change the number of `string databaseType = databaseTypes[1];`.

### Show heatmap
If you want to show the heatmap of the tracking, in **eco/parameters.cc**, change to `#define DEBUG 1`.

### Compile and Run:
```
cd eco
make -j`nproc`
./runecotracker.bin
```

## Run Opencv trackers
Change the path of your test images in **kcf/opencvtrackers.cc**.
```
cd opencvtrackers
make 
./opencvtrackers.bin
```

## Run KCF / DSST
Change the path of your test images in **kcf/runkcftracker.cc**.
```
cd kcf
make -j`nproc`
./runkcftracker.bin
```

## Run GOTURN
Change the path of your test images in **goturn/rungoturntracker.cc**.

### Pretrained model
You can download a pretrained [[goturun_tracker.caffemodel (434 MB)](https://drive.google.com/file/d/1uc9k8sTqug_EY9kv1v_QnrDxjkrTJejR/view?usp=sharing)], put it into folder: **goturn/nets**

```
cd goturn
make -j`nproc`
./rungoturntracker.bin
```

### Run caffe classification for simple test
```
./classification.bin   /media/elab/sdd/caffe/models/bvlc_reference_caffenet/deploy.prototxt   /media/elab/sdd/caffe/models/bvlc_reference_caffenet/bvlc_reference_caffenet.caffemodel   /media/elab/sdd/caffe/data/ilsvrc12/imagenet_mean.binaryproto   /media/elab/sdd/caffe/data/ilsvrc12/synset_words.txt   /media/elab/sdd/caffe/examples/images/cat.jpg
```

# References 
--------------------------------
(not complete, tell me if I forgot you)

## GOTURN Tracker
**[Learning to Track at 100 FPS with Deep Regression Networks](http://davheld.github.io/GOTURN/GOTURN.html)**,
<br>
[David Held](http://davheld.github.io/),
[Sebastian Thrun](http://robots.stanford.edu/),
[Silvio Savarese](http://cvgl.stanford.edu/silvio/),
<br>
European Conference on Computer Vision (ECCV), 2016 (In press)

## KCF Tracker
J. F. Henriques, R. Caseiro, P. Martins, J. Batista,   
"High-Speed Tracking with Kernelized Correlation Filters", TPAMI 2015.

## CSK Tracker
J. F. Henriques, R. Caseiro, P. Martins, J. Batista,   
"Exploiting the Circulant Structure of Tracking-by-detection with Kernels", ECCV 2012.

## ECO Tracker
Martin Danelljan, Goutam Bhat, Fahad Khan, Michael Felsberg.  
<a href="https://arxiv.org/abs/1611.09224">ECO: Efficient Convolution Operators for Tracking</a>.  
In Proceedings of the IEEE Conference on Computer Vision and Pattern Recognition (CVPR), 2017. 

## C-COT Tracker
Martin Danelljan, Andreas Robinson, Fahad Khan, Michael Felsberg.  
    Beyond Correlation Filters: Learning Continuous Convolution Operators for Visual Tracking.  
    In Proceedings of the European Conference on Computer Vision (ECCV), 2016.  
    http://www.cvl.isy.liu.se/research/objrec/visualtracking/conttrack/index.html
    
## SRDCF Tracker
Martin Danelljan, Gustav Häger, Fahad Khan, Michael Felsberg.  
    Learning Spatially Regularized Correlation Filters for Visual Tracking.  
    In Proceedings of the International Conference in Computer Vision (ICCV), 2015.  
    http://www.cvl.isy.liu.se/research/objrec/visualtracking/regvistrack/index.html

## SRDCF-Deep Tracker
Martin Danelljan, Gustav Häger, Fahad Khan, Michael Felsberg.  
    Convolutional Features for Correlation Filter Based Visual Tracking.  
    ICCV workshop on the Visual Object Tracking (VOT) Challenge, 2015.  
    http://www.cvl.isy.liu.se/research/objrec/visualtracking/regvistrack/index.html
	
## DSST Tracker
Martin Danelljan, Gustav Häger, Fahad Khan and Michael Felsberg.  
    Accurate Scale Estimation for Robust Visual Tracking.  
    In Proceedings of the British Machine Vision Conference (BMVC), 2014.  
    http://www.cvl.isy.liu.se/research/objrec/visualtracking/scalvistrack/index.html
    

Martin Danelljan, Gustav Häger, Fahad Khan, Michael Felsberg.  
    Discriminative Scale Space Tracking.  
    Transactions on Pattern Analysis and Machine Intelligence (TPAMI), 2017.  
    http://www.cvl.isy.liu.se/research/objrec/visualtracking/scalvistrack/index.html

## HOG feature
N. Dalal and B. Triggs.  
    Histograms of oriented gradients for human detection.  
    In CVPR, 2005. 

## Color Names feature
J. van de Weijer, C. Schmid, J. J. Verbeek, and D. Larlus.  
    Learning color names for real-world applications.  
    TIP, 18(7):1512–1524, 2009.  

## OBT database
 Y. Wu, J. Lim, and M.-H. Yang.  
    Online object tracking: A benchmark.  
    TPAMI 37(9), 1834-1848 (2015).  
    https://sites.google.com/site/trackerbenchmark/benchmarks/v10

 Y. Wu, J. Lim, and M.-H. Yang.  
    Object tracking benchmark.  
    In CVPR, 2013.  

## VOT database
http://votchallenge.net/


## Some code references

KCF: [joaofaro/KCFcpp](https://github.com/joaofaro/KCFcpp).

DSST: [liliumao/KCF-DSST](https://github.com/liliumao/KCF-DSST), the max_scale_factor and min_scale_factor is set to 10 and 0.1 in case of divergence error (Tested on UAV123 dataset when the object is quite small, ex.uav2/3/4...).

GOTURN: [davheld/GOTURN](https://github.com/davheld/GOTURN).

ECO: [martin-danelljan/ECO](https://github.com/martin-danelljan/ECO).




