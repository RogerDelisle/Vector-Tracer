# Vector-Tracer

This application will record user mouse movements in real-time to record a trace that can be replicated on screen. But the important feature of this project will be to transmit this vector over RF by modulating the x-y coordinates of the trace in real-time over I/Q dimensions. Demodulation is designed to be possible with a simple 2-channel oscilloscope.

## Status
The source code is currently implemented using the Qt platform.  I'm currently still working on the Digital Signal Processing (DSP) portion and it will be uploaded in early April 2018. Meanwhile, the user interface and real-time animation portion compile and work well.

## Next Steps
Generation of the audio signal using DSP will generate a buffer of the x-axis tracing on the real (I) portion of the signal and the y-axis tracing on the imaginary (Q) portion of the signal. 

## Environment
I've compiled this using Qt Creator 4.5.1 (Based on Qt 5.10.1) and compiling using MSVC 2015, 64-bits on x86. Even though I haven't yet put much effort on portability at this early stage of the implementation, your comments on any portability issues you encounter are most welcome. If you are interested in my MFC version of this project, please contact me.

## Language Features, Classes, Techniques

- C++
- Qt Widgets
- Qt Signal/Slot communications
- Qt Widget promotion
- User interface animation by using the QPropertyAnimation class
- Unconventional User Interface
- Use of STL containers such as std::vector<>, std::map<>
- Use of a variadic template to process a parameter pack
- Real-time programming and example of using the std::chrono STL templates.
- Digital Signal Processing (DSP)


# Installation
 Simply compile all the code in Qt Creator using all files in the same directory.

# License
All the source code in this Repository is original and its licensing is modeled after the MIT License (https://opensource.org/licenses/MIT) 

Copyright 2018 Roger M. Delisle

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
