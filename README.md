# Readme



## RUNNING THE PROGRAM

Warning: In order to run the program with google tests, googletest has to be downloaded from
https://github.com/google/googletest. The folder should be placed next to the build folder and
the source files.

STEP 1: Build the program from a build folder
-Open a terminal and go to the desired location, next to the source files

--&gt;mkdir build

--&gt;cd build

--&gt;cmake &lt;Path to the src folder&gt;

--&gt;make

STEP 2: Execute the program

From the build folder

Main program  --&gt; ./image_process

tests --&gt; ./runTests


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   ## PROCEDURE: Running ./image_process
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

# Fourier transform

The programm will first load an image using the library "OpenCV".
The loaded image is transformed to a square image of a size of power of two.

It will also load a sinusoidal image to have a good representation of the Fourier transform on an image. 
It will then calculate the 2D fast Fourier transform on both images and display them in three windows containing the real part, imaginary part and amplitude. 
The three windows are the follow:

 - Original image (imaginary part should be black)
 - Representation of the Fourier transformation, for a nicer representation, we bring the low frequencies from the corners to the center
 - Re-transformed image (should be the same as the original image)
 
Between each windows you will have to press any key to display the next window.

The sinusolidal image with its transform and as we see, only one frequence in the real part is non-zero.

<img src="/pics/sinus - Re-transformed - (Real, Imaginary, Amplitude).png" alt="square image" width="600"/>
<img src="/pics/sinus - Transformed - (Real, Imaginary, Amplitude).png" alt="square image" width="600"/>

An original squared image with its Fourier transform

<img src="/pics/256.png - Untransformed - (Real, Imaginary, Amplitude).png" alt="square image" width="600"/>
<img src="/pics/256.png - Transformed - (Real, Imaginary, Amplitude).png" alt="square image" width="600"/>

You are then asked to choose between four filters that can be applied on the representation of the fourier transform:

 1) Select only the low frequencies, represented by a circle in the center, it will blur the image.
    The user will have to choose the radius of the circle.
    It is given by the percentage of the image size.
    
    An example with a radius of 10% of the image size.
    
    <img src="/pics/Blurred with a radius divided by 10.000000 - (Original, Real part filtered, Transformed).png" alt="square image" width="600"/>


 2) Select only the high frequencies, represented by erasing a circle in the center of the fourier transform.
    The user will have to choose the radius of the circle.
    It is given by the percentage of the image size.
    
    An example with a radius 30% of the image size.
    
    <img src="/pics/Blurred with a radius divided by 3.333333 - (Original, Real part filtered, Transformed).png" alt="square image" width="600"/>
    
    Note that the lowest frequency is kept to have a better representation. Otherwise, the image would be very dark.


 3) Select only a band between low and high frequencies.
    The user will choose two radius to create two circles, it will select only a band between these two circles.
    The radius are given by the percentage of the image size.
    
    An example with radius of 5% and 30% of the image size.
    
    <img src="/pics/Transformed with a selected band - (Original, Real part filtered, Transformed).png" alt="square image" width="600"/>


 4) Select only very low and very high frequencies.
    The user will choose two radius to create two circles, it will erase the band between these two circles.
    The radius are given by the percentage of the image size.
    
    An example with radius of 5% and 30% of the image size.
    
    <img src="/pics/Transformed with a band erased - (Original, Real part filtered, Transformed).png" alt="square image" width="600"/>


# Histograms, edge detection, noise removal

The image of Lena is displayed is in color.



<img src="/pics/lena.png" alt="Lena color" width="400"/>

After pressing a key, four histograms are displayed showing the intensity distribution of the pixels for the image in gray and the three channels separately, Red, Green and Blue. The range of intensity values goes from 0 being black to 255, the brightest.

The histogram is plotted with Python, but the histogram data comes from the c++ code and is stored in the histogram.txt file.


<img src="/pics/gray.png" alt="Gray histogram" width="400"/>

There are pics of intensity around the low values (50) and medium (150).


<img src="/pics/red.png" alt="Lena red" width="400"/>

For the red, the peak is located around 225, showing high values of intensity for the red distribution.
It can be explained by the pinky/red bakground.


<img src="/pics/blue.png" alt="Lena blue" width="400"/>

The repartition of the blue intensities is well distributed across all values from 0 to 220.

<img src="/pics/green.png" alt="Lena green" width="400"/>

Concerning the green pixels, there are no low intensities. They are all belonging to a medium value range between 50 and 200.

After the histogram, each keystroke will display the image of Lena with the following filter apply by convolution.
By using the convolution, it was requiered to implement a zero padding, that consists in a boolean
For the convolution, we emulate a zero padding with the use of a boolean function that returns false, and assigned the value 0 if the selected coordonates are out the bounds of the image, and true otherwise.
The image of Lena appears in succession, first Prewitt horizontal then vertical, third the high pass filter of the original image and at last the median filter on the former high pass filter of the image.


**Prewitt for horizontal edge detection**



<img src="/pics/prewitt_h.png" alt=" prewitt horizontal" width="200"/>





<img src="/pics/horizontal.png" alt="Lena prewitt horizontal" width="400"/>



**Prewitt for vertical edge detection**

<img src="/pics/prewitt_v.png" alt=" prewitt vertical" width="200"/>


<img src="/pics/vertical.png" alt="Lena prewitt vertical" width="400"/>


**High Pass**


<img src="/pics/high_pass.png" alt="high pass" width="200"/>



<img src="/pics/highpass.png" alt="Lena high" width="400"/>


The high pass filter accentuates the bright features of the image.
As you can see on the image, several bright spots have appeared which can be likened to salt and pepper noise.
The perfect opportunity to test our median filter for noise removal!

**Median filter**

By applying the median filter, each pixel takes the median value for the surrounding pixels.
We can see that, compared to the high pass filter Lena, the noise is reduced.


<img src="/pics/median_filter.png" alt="Lena median" width="400"/>

**Edge detection**

We also tried to apply the edge detection with horizontal prewitt on the image of hand shadows.


<img src="/pics/hand_shadows.png" alt="Hand shadows" width="400"/>


<img src="/pics/hand_shadows_contour.png" alt="Hand shadows" width="400"/>

We can see that it detects the edges.



- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   ## TEST: Running ./runTests
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

We implemented the following tests.

**image_convolution**
We tested the function convolve a 3x3 filter on a 3x3 image and by calculation by the hand the expected result and comparing it to the output.

**is_In_Bounds**
We tested if the function isInBounds was able to recognize if some coordonates were in bounds or not for the zero padding.

**get_Intensity**
We created an image with our image class, modified the pixel (10,10) with the function set_pixel_intensity and used the function get_intensity to see if we obtain the modified intensity value of the same pixel.
By this test, we tried both set_pixel_intensity and get_intensity.

**FFT2D**
We created a random image of a power of 2 size represented by an array, transformed it with the 2D fast Fourier transform and transformed it again with the negative fft. We wanted to see if at the end of both transformation we got back to the original array.

**blur**
We created a random image represented by an array and add the low pass filter. We then looked if the points at the corner of the image were erased.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   ## To Do's and perspective
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

- Use nicer blur like Gaussian filter to have less distortion in the blury image.

- Use a tclap implementation in order to allow the use of user defined options.

- Check if the filter applied by fourier and by convolution produce the same result.

- Generalize the function of convolution for different sizes of filter (in this project, it is always a 3x3 filter).

- Unify our two classes.
