# Firefly
Quadcopter project (Side Project)

The objective of this project is to build an ultra low cost quadcopter platform for swarm of drones.

## Table of Contents

- [Build-1](#build-1)
- [References](#references)



# Build-1

The first build of the nano quad uses a 
- 90mm carbon fiber quadrotor frame
- 8520 coreless brushed motors
- 55mm propellers
- 600maH 1S Lipo cell
- WeMos D1 mini module as PPM receiver <a href="https://github.com/DipanshuShukla/ESP-PPM">(ESP-PPM)</a>
- SPRACING F3 EVO brushed flight controller

The reason behind using a ESP module instead of traditional RX modules is that ESP modules are easily programmable with the Arduino IDE, and ESP supports mesh networks which might be useful for swarming. The control interface is a web socket server that can be used from a smartphone browser with touch controls or firefox browser on PC with a traditional Gamepad. 

<figure align="center">
    <img src="images/build1.jpg" alt="drawing" width="400"/>
    <figcaption>Build 1</figcaption>
</figure>

Successful flight was achieved on September 2, 2020. For details on the build process, head on to the <a href="Build 1/README.md">Build-1 page</a>

# References

- https://robotzero.one/esp32-camera-module/
- https://opencv-python-tutroals.readthedocs.io/en/latest/py_tutorials/py_video/py_lucas_kanade/py_lucas_kanade.html
- https://robotics.stackexchange.com/questions/1844/stabilizing-a-quadcopter-with-optical-flow
- https://dronerush.com/drone-gps-10778/
- https://stackoverflow.com/questions/11217674/how-to-calculate-distance-from-wifi-router-using-signal-strength
- https://www.kalmanfilter.net/background.html
