# Mobile3D

Getting Started:  
1. Install Docker.
2. Run `docker build --tag mobile3d .`. The first time will take a while to build OpenCV. (Make sure you give Docker enough RAM. Docker Desktop --> Preferences --> Resources. Max out CPU and memory.)  
3. Run `docker images` to see the new docker image!  
3. Run `docker run -it mobile3d` to get a shell in the container.