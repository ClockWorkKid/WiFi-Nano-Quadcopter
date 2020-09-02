                   .:                     :,                                          
,:::::::: ::`      :::                   :::                                          
,:::::::: ::`      :::                   :::                                          
.,,:::,,, ::`.:,   ... .. .:,     .:. ..`... ..`   ..   .:,    .. ::  .::,     .:,`   
   ,::    :::::::  ::, :::::::  `:::::::.,:: :::  ::: .::::::  ::::: ::::::  .::::::  
   ,::    :::::::: ::, :::::::: ::::::::.,:: :::  ::: :::,:::, ::::: ::::::, :::::::: 
   ,::    :::  ::: ::, :::  :::`::.  :::.,::  ::,`::`:::   ::: :::  `::,`   :::   ::: 
   ,::    ::.  ::: ::, ::`  :::.::    ::.,::  :::::: ::::::::: ::`   :::::: ::::::::: 
   ,::    ::.  ::: ::, ::`  :::.::    ::.,::  .::::: ::::::::: ::`    ::::::::::::::: 
   ,::    ::.  ::: ::, ::`  ::: ::: `:::.,::   ::::  :::`  ,,, ::`  .::  :::.::.  ,,, 
   ,::    ::.  ::: ::, ::`  ::: ::::::::.,::   ::::   :::::::` ::`   ::::::: :::::::. 
   ,::    ::.  ::: ::, ::`  :::  :::::::`,::    ::.    :::::`  ::`   ::::::   :::::.  
                                ::,  ,::                               ``             
                                ::::::::                                              
                                 ::::::                                               
                                  `,,`


http://www.thingiverse.com/thing:1221911
Micro 105 FPV Quadcopter - 8.5mm Motors, Micro Scisky by punkkills is licensed under the Creative Commons - Attribution - Non-Commercial - Share Alike license.
http://creativecommons.org/licenses/by-nc-sa/3.0/

# Summary

This frame was inspired by the [FireFlo V2](http://www.thingiverse.com/thing:1133306) and the [Alpine Drones Micro H](http://www.thingiverse.com/thing:717375).  My goals were to keep it crash resistant, light weight and offer good protection for onboard gear. 

It measures ~105mm.  The V1 frame weighs ~10g and the V2 frame weighs ~8g when printed in PLA.  My full build (currently V2 base and V1 top) weighs ~38g without the battery.  It is designed around 8.5mm motors and the Micro Scisky flight controller.  The camera mount is angled up 13 degrees to accommodate fast forward flight.

Build Instructions
==============
[Guide to configuring the Micro Scisky](http://bit.ly/29Burcd)
See the full build instructions on [instructables](http://bit.ly/1Xmzxuw).

Base Setup
=======
* **Flight Controller**:  You need a Flight Controller with a receiver that matches your radio.  I list radio options for the different protocols below.
  * [Eachine F3 FrSky](http://www.banggood.com/Eachine-FRF3_EVO-Brushed-Flight-Control-Board-Built-in-FRSKY-Compatible-SBUS-8CH-Receiver-p-1091779.html?p=4S26211552037201504F)
  * [Eachine F3 FlySky](http://www.banggood.com/Eachine-FLF3_EVO-Brushed-Flight-Control-Board-Built-in-FLYSKY-Compatible-PPM-6CH-Receiver-p-1091775.html?p=4S26211552037201504F)
  * [Eachine F3 DSM2](http://www.banggood.com/Eachine-DSF3_EVO-Brushed-Flight-Control-Board-Built-in-DSM2-Compatible-PPM-6CH-Receiver-p-1091777.html?p=4S26211552037201504F)
  * [FlySky Micro Scisky](http://www.banggood.com/Micro-Scisky-32bits-Brushed-Flight-Control-Board-Built-in-FlySky-Compatible-RX-For-DIY-Micro-Frame-p-1093312.html?p=4S26211552037201504F)
  * [FrSky Micro Scisky](http://www.banggood.com/Micro-Scisky-32bits-Brushed-Flight-Control-Board-Based-On-Naze-32-For-Quadcopters-p-1002341.html?p=4S26211552037201504F)
  * [DSMX/DSM2 Micro Scisky](http://www.banggood.com/Micro-Scisky-32bits-Brushed-Flight-Control-Board-With-1_25mm-Plugs-For-DIY-Micro-Quadcopter-Frame-p-1067976.html?p=4S26211552037201504F).  You might need to remove the motor plugs from this one in order to fit inside the frame.
* **Motors**: [Hubsan X4 H107c 8.5mm Motors](http://bit.ly/1ZuQCkX)
* **Battery**: I use a mix of a few batteries. [380mAh Hubsan](http://bit.ly/1Txxbna), [500mAh Hubsan](http://bit.ly/1T6hCIM) and [300mAh Nano-Techs](http://www.hobbyking.com/hobbyking/store/uh_viewitem.asp?idproduct=37566) **CAUTION:** When using the Nano-Techs, make sure the battery polarity is correct.  I have had to switch the connector position on these.
* **Props**: I am currently using  [Ladybird props](http://bit.ly/1s69iNy).  They hold up a lot better than the Hubsan props.
* **Battery Pigtail**: I cut one of the leads off of a [charging adapter](http://bit.ly/21MhQFg).
* **Nylon Hardware**: M3 [nylon nuts](http://bit.ly/1T6byOA) and [machine screws](http://bit.ly/1T9ebBg).  I used the 20mm machine screws and cut them to size after attaching to the frame.
* **Printable Standoff And Clip**: As an alternative to using nylon hardware, navyblueboss made a very nice [pin and clip set](http://www.thingiverse.com/thing:1336747).  I have not yet printed a set of these but they look great.
* **JST SH Connector**: A [JST SH connector](http://goo.gl/VNbjMQ) can be used to get get a 5v supply for fpv gear straight from the Scisky. **CAUTION:** I managed to fry the power supply on one of my Scisky boards.  Other users have reported the same when using the FC to power FPV gear.  Another option is to use straight battery power or a voltage regulator from battery for VTX and camera.

All in One FPV Gear
================
There are a few new options for an all in one FPV setup.  You can connect these straight to battery power and don't need a voltage regulator.  These camera and video transmitter modules can be used with the v4 frame.  Here are a few options that I have tested with.
* **[FX798T](http://bit.ly/2a9r491)**
* **[FX797T](http://bit.ly/2aGxYVd)**

DIY FPV Gear
==========
These components will allow you to build the FPV setup yourself.  These components are for v1, v2, and v3 frames.
* **VTX**: [FX758-2 5.8G 200mW Video Transmitter](http://bit.ly/1SZvaAB)
* **Antenna**: I used the inner wire from the coaxial cable of a broken clover leaf antenna. I used the default frequency on the FX758-2 which is 5865. After soldering the wire on, I cut the antenna to 12.8mm which is the [quarter wavelength of that frequency](https://www.easycalculation.com/physics/electromagnetism/antenna-wavelength.php)
* **Camera**: [170 Degree Wide Angle Camera](http://bit.ly/1WhNkmX)
* **5v Step-Up Voltage Regulator**: Use a [pololu 5v step-up](https://www.pololu.com/product/2115) instead of the JST SH connector to avoid burning up the voltage regulator on the Scisky.

Radio Options
===========
You need a radio that matches the protocol of your FC.  Here are some options for a few protocols.
* FlySky
  * [FlySky FS-i6](http://www.banggood.com/FlySky-FS-i6-2_4G-6CH-AFHDS-RC-Transmitter-With-FS-iA6B-Receiver-p-983537.html?p=4S26211552037201504F)
  * [FlySky FS-i6X](http://www.banggood.com/Flysky-FS-i6X-10CH-2_4GHz-AFHDS-2A-RC-Transmitter-With-FS-iA10B-Receiver-p-1101154.html?p=4S26211552037201504F)
* FrSky
  * [Taranis Plus](http://bit.ly/1VPPlqm)
  * [Taranis QX7](http://www.banggood.com/FrSky-ACCST-Taranis-Q-X7-2_4GHz-16CH-Transmitter-White-Black-p-1112717.html?p=4S26211552037201504F)
* DSM2/DSMX
  * [Spektrum DX6i](http://amzn.to/1rC5ZNC)
  * [Spektrum DX5e](http://amzn.to/1NnO2fK)
  * [FsFly T-Six](http://bit.ly/1s6ssTu)

Video Options
===========
* [Eachine EV800 Goggles](http://bit.ly/1Ykxsjg) - These are inexpensive goggles that can double as a standalone screen.  These would make a good pair of starter goggles.
* [Fatshark Dominator V3 Goggles](http://amzn.to/1VTX9Y6) + [Receiver Module](http://amzn.to/1Wr7njq)

Alternate Electronics
================
People have had success transplanting the flight controller and motors from a [Hubsan X4 H107C](http://amzn.to/1QZuWqY).  Going this route, you would get motors, flight controller, a battery, a radio and a set of props for relatively cheap.  You could then add FPV with a camera, VTX and a voltage regulator.  I have not tried this route yet, but plan to build one soon for a friend.  I will post my results when I do.

Updates
=======
* **1/9/2016** - Added bottom-v2-experimental.  I was able to reduce the weight of the bottom of the frame to ~5.5g.  This saves ~1.5g from v1.  I don't think the frame durability will be affected much.
* **1/10/2016** - Added top-v2-experimental.  I was able to reduce the weight of the top of the frame to ~2.3g.  This save  ~0.5g from v1.  The v2 top and bottom combined should be ~8g when printed in PLA.  Both the v2 top and bottom will feel a bit flexy separately, but once they are connected the quad will feel solid but still allow some give in crashes.  I recommend using M3 nylon hardware to secure the pieces together.  I do not anticipate the v2 top compromising durability in any way.  **NOTE**: I have printed, but not flown with this top.  My camera is hot glued to the v1 top so I will need to find some time to make the switch.
* **1/11/2016** - Added top-v2-no-cam-experimental.  I've been doing some indoor LOS flying and wanted to see how it preformed without the FPV gear.  Wow, there is a lot of pop.
* **1/16/2016** - Added top-v2-cam-down-7.  This points the camera down 7 degrees. In order to clear the base plate, I had to push the camera forward just a bit and I made the standoffs of cam-down 1mm taller so the camera does not extend below the bottom plate.  I also removed the word "experimental" from v2 filenames.
* **5/9/2016** - Added bottom-v3.  This version should be much stronger than v2 but it weighs only ~0.2g more.  I was able to increase the thickness of the arms while saving some weight with a few other modifications.  I also added some relief to the back to make it easier to plug a USB cable into the Scisky.
* **7/25/2016** - Added v4 top and bottom which allow for all in one FPV modules.  The bottom has hooks for an underslung battery and the top has a recessed seat for the FPV gear.  I also added a 7mm version of the v4 bottom.  I did not test the 7mm version as I don't have any 7mm motors.  Please let me know how it works if you use this frame.

Videos
======
https://youtu.be/qZ-qDsXewZI

# Instructions

Infill: 100%
Layer Height: 0.3mm
Bottom Piece: 4 Perimeters
Top Piece: 2 Perimeters
Extrusion Width: 0.4mm for all tops and v1, and v2 bottoms.  0.48mm for v3 and v4 bottoms.  I optimized the dimensions to be all perimeters hoping that it makes it stronger.