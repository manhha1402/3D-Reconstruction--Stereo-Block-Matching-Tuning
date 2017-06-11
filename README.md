# 3D-Reconstruction--Stereo-Block-Matching-Tuning
The Source Code implements the method "Stereo" that is used to reconstruct 3D model.
1. Firstly, it detects features and matches features in 2 images.
2. Assume that I have a pair of stereo images that can be taken from camera calibration and rectification processes. I create trackbars 
to tune parameters of stereo block matching algorithms to find out a good disparity. Then I compute depthmaps of images from the disparity.
3. Compute 3D points from depthmaps and use PCL library to visualize the result
