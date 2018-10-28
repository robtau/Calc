# Calc
C++ implementation of arbitrary-precision calculator

This program was created in cooperation with my fellow Robert as a part of our semester-ending work, his git can be found at https://github.com/robtau.

The idea came from fact that the highest possible accuracy in computer calculations is double-precision with 15 significant figures at most. We wanted to go beyond this limitation so that our only limit would be memory of a computer.
We managed to get it working pretty good, at this moment (28.10.18) our little program is able to:
-work with at least (depending on your computers' architecture) 18,446,744,073,709,551,615 characters long equations
-calculate with arbitraly chosen precision
-perform basic arithmetics including parentheses
-keep correct order of calculations during whole process
-work with floating point numbers
-validate input

