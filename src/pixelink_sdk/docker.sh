#!/bin/bash -ex

X_OPTS="--env=DISPLAY --env=QT_X11_NO_MITSHM=1 --volume=${HOME}/.Xauthority:/home/${USER}/.Xauthority:rw --volume=/tmp/.X11-unix:/tmp/.X11-unix:rw"

NET_OPTS='--net=host'

MOUNT_OPTS="-v ~/project:/home/dev/project -v ~/:/mnt"

USB_DEVICES_OPTS="-v /dev/platform:/dev/platform:rw"

DEVICES_OPTS="-v /dev:/dev:rw"

DEVS="$(lsusb -d 1996: | cut -d ' ' -f 2,4 | sed 's/://')"

IFS='
'
for dev in $DEVS; do
   BUS="$(echo $dev | cut -d ' ' -f 1)"
   DEVICE="$(echo $dev | cut -d ' ' -f 2)"
   CAMERA_OPTS="--device=/dev/bus/usb/${BUS}/${DEVICE} ${CAMERA_OPTS}"
   sudo chmod 777 /dev/bus/usb/$BUS/$DEVICE
done
echo 1024 | sudo tee /sys/module/usbcore/parameters/usbfs_memory_mb

VIDEO_OPTS="-v /dev/video0:/dev/video0"

DEVICES_OPTS="$USB_DEVICES_OPTS $CAMERA_OPTS $VIDEO_OPTS"

eval "nvidia-docker run --privileged $DEVICES_OPTS $X_OPTS $MOUNT_OPTS $NET_OPTS -it dm/ai /bin/bash"

