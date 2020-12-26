sudo apt-get install gcc cmake build-essential qt-creator qt5-default libgdal-dev gdal-bin python python3 python-pip python3-pip ccache git g++
sudo apt-get install ubuntu-desktop
sudo apt install -y virtualenv curl python-setuptools build-essential gcc g++ cmake python3-dev python-virtualenv binutils libproj-dev 
sudo add-apt-repository ppa:ubuntugis/ubuntugis-unstable
sudo apt-get update
sudo update-alternatives --install /usr/bin/python python /usr/bin/python2.7 1
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.6 2
python -m pip install sphinx breathe
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

sudo apt install libgl1-mesa-dev libglu1-mesa-dev freeglut3 freeglut3-dev nginx

sudo apt-get install unar
sudo apt-get install flex bison
sudo apt install libzip-dev
sudo apt-get install autoconf automake libtool curl make g++ unzip

sudo apt-get install libprotobuf* protobuf-c-compiler protobuf-compiler
sudo apt-get install libqt5serialport5-dev

sudo apt-get install grass grass-core grass-dev grass-gui libgdal-grass qgis-plugin-grass qgis-provider-grass
sudo apt-get install libqt5*
sudo apt-get install qtwayland5 -y
sudo apt-get install qttools5*
sudo apt install qtpositioning5-dev
sudo apt install -y qca* libqca* libgsl*

python -m pip install --upgrade pip
python -m pip install pyqt5 pyqt5-tools sip
sudo apt install sip-dev

sudo apt install exiv2 libexiv2*

sudo apt install libssl-dev sqlite3 libsqlite3-dev libqt5webkit5-dev qttools5-dev qttools5-dev-tools python-sphinx texlive-latex-base inotify-tools qt5keychain-dev
sudo apt install libqwt-qt5-dev libqwt-dev
sudo apt install libqsci*-qt5*

sudo apt install libspatialindex*
python -m pip install qscintilla
