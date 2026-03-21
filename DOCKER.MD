docker build -t security .

open -a XQuartz

xhost + 127.0.0.1

docker run -it \
-e DISPLAY=host.docker.internal:0 \
-e QT_XCB_NO_MITSHM=1 \
-v .:/app \
security \
/bin/sh