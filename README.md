# OWT 
In a setup where data packets are sent from a device to a PC, the simplified OWT (One Way Translater) maitains an estimate of the clock offset from the device to the PC and translates the PTS (Device) timestamp to the system (PC) timestamp given the system receive time `sys` of the data packet and the PTS timestamp `pts` contained in the data packet. It is assumed that the packet transmission delay follows a non-Gaussian distribution with a long tail and the clock skew differs only slightly. Hence the lower bound of the measured clock offset `sys - pts` in a time window of `window_size` will be used as the estimated clock offset.

Please refer to https://github.com/ethz-asl/cuckoo_time_translator for a more comprehensive treatment of this problem.
## Usage
The following example shows how a owt with `window_size = 300ms` is constructed and used.
```c++
using namespace std::chrono_literals;
Owt<std::chrono::nanoseconds> owt(300ms);
auto sys_from_pts = owt(pts, sys);
```

## Result of running example.cpp
```
|  pts  |  sys  | trans.|
|-------|-------|-------|
|     10|     20|     20|
|     20|     30|     30|
|     30|     35|     35|
|     40|     42|     42|
|     50|     65|     52|
|     60|     68|     62|
|     70|     83|     72|
|     70|     83|     72|
|     90|    100|     92|
|    100|    110|    108|
|    110|    120|    120|
```
