Host
====

Only one* BF thread will run on the host, and this thread is the main one: it's 
the only one allowed to use the IO operators ('.' and ',') and thus the only 
one that has access to the API. In case of BrainFuck.cl projects it's most 
important rule is to handle IO - read in data and write results.

 * note: OpenCL code is able to run on the CPU, thus you can use the CPU as a 
device and run multiple BF threads on the CPU - however as the threads run on a
device they'll be restricted just like they'd be restriced on the GPU. But
these threads are still device threads, only one host thread can exist at any
time. If this thread exits the whole application exits.

Device
======

Device BF threads are executed by uniform OpenCL kernels. Each and every OpenCL
kernel is a BF interpreter - see kernel.md for more details.

Device BF kernels ("kernels for short") are restricted - IO operations are
pointless due to race conditions, so these operators are ignored in the code.
You can create any number of kernels and one tape can be attached to multiple
kernels but a kernel can be associated to only one tape at any time. Kernels
can only be associated to a tape on the same device.

Host-device communication
=========================

As the only difference between host and device threads is the lack of IO on 
device threads communication for any other task than IO is pointless as copying
between host and device memory is an expensive operation. Communication is
handled through the API: the host can copy between tapes (both device-device
and host-device tapes). Device threads should create a string ready to be
printed in order to minimize pointless traffic between threads.

