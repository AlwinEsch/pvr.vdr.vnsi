# *<p align="center">pvr.vdr.vnsi</p>*
#### *<p align="center">Kodi's PVR add-on to use for VDR's plugin vnsi-server</p>*
*<p align="center">![alt tag](https://raw.githubusercontent.com/kodi-pvr/pvr.vdr.vnsi/master/pvr.vdr.vnsi/icon.png)</p>*

To build add-on manually can you use the following ways:

--------------------

##### Linux:

###### 1. The first step is if you have the source code available:
```bash
# the following is only a example, dir can be everywhere, only 
# the last value of cmake must point to them.
#
# This build becomes on this example created there on folder 
# where "xbmc" is, 'ls' brings for you on end as 
# example "... build xbmc ...".

mkdir ./build
cd ./build
cmake -DADDONS_TO_BUILD=pvr.vdr.vnsi \
      -DCMAKE_INSTALL_PREFIX=$HOME/.kodi/addons \
      -DPACKAGE_ZIP=1 \
      ../xbmc/project/cmake/addons
make
```
By the commands above is the add-on installed on your home folder where kodi stores also his other add-ons and data.

-------------
### License of add-on
- [GNU GENERAL PUBLIC LICENSE Version 2, June 1991](https://github.com/AlwinEsch/pvr.vdr.vnsi/raw/master/LICENSE.GPL)
