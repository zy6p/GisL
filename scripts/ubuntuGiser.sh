apt-get install ubuntu-desktop gcc cmake build-essential qtcreator qt5-default libgdal-dev gdal-bin python python3 python-pip python3-pip ccache git g++ virtualenv curl python-setuptools build-essential gcc g++ cmake python3-dev binutils libproj-dev libgdal-dev python3-gdal gdal-bin doxygen-latex doxygen-doc doxygen-gui graphviz qgisqttools5* qtpositioning5-dev gmt
add-apt-repository ppa:ubuntugis/ubuntugis-unstable
apt-get update && apt-get upgrade -y
#update-alternatives --install /usr/bin/python python /usr/bin/python2.7 1
#update-alternatives --install /usr/bin/python python /usr/bin/python3.6 2
python -m pip install sphinx breathe
