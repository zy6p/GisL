sudo apt-get install gcc cmake build-essential qt-creator qt5-default libgdal-dev gdal-bin python python3 python-pip python3-pip ccache git g++
sudo apt-get install ubuntu-desktop
sudo apt install -y virtualenv curl python-setuptools build-essential gcc g++ cmake python3-dev python-virtualenv binutils libproj-dev 
sudo add-apt-repository ppa:ubuntugis/ubuntugis-unstable
sudo apt-get update
sudo update-alternatives --install /usr/bin/python python /usr/bin/python2.7 1
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.6 2
pip install sphinx breathe
# 首先更新apt源
sudo apt-get update && sudo apt-get upgrade -y
# 安装 PROJ
sudo apt-get install libproj-dev proj-data proj-bin -y
# 安装 GEOS
sudo apt-get install libgeos-dev -y
# 安装 GDAL
sudo apt-get install libgdal-dev python3-gdal gdal-bin -y
# 安装 PDAL 
sudo apt-get install libpdal-dev pdal libpdal-plugin-python -y
sudo apt-get install doxygen-latex  doxygen-doc doxygen-gui graphviz
sudo apt-get install qgis qgis-server qgis-plugin-grass

sudo apt install libgl1-mesa-dev libglu1-mesa-dev freeglut3 freeglut3-dev