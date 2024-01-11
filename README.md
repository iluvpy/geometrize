# geometrize
create images from random shapes

# dependencies
- opencv
- ninja
- clang
- SDL 2

# setup
if you run into issues with .so files try running 
`export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/lib`

# install opencv
to install opencv please follow the instructions on https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html 
or google how to install it on your os


# Usage
just install all the dependencies and run `ninja`, after that you can run `client <your-image.png>`.     
Note: you can use any image format


# Problems
algorithm can get "stuck" where it adds shapes that dont change the image enough to be visible,
essentially a local 