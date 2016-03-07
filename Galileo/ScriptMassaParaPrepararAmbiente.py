#!/usr/bin/python

import apt
import sys
import os

packages_to_install = ['build-essential', 'make', 'git', 'libgtk2.0-dev',
                       'pkg-config', 'libavcodec-dev', 'libavformat-dev',
                       'libswscale-dev', 'python-dev', 'python-numpy',
                       'libtbb2', 'libtbb-dev', 'libjpeg-dev', 'libpng-dev',
                       'libtiff-dev', 'libjasper-dev', 'libdc1394-22-dev']

def checkOpencv():
    if (os.path.exists('/usr/local/include/opencv2/face')):
        import cv2
        if (cv2.__version__ == '3.0.0-dev'):
            return True
    return False

def installPackages():
    cache = apt.cache.Cache()
    cache.update()

    for pkg_name in packages_to_install:
        pkg = cache[pkg_name]
        if (pkg.is_installed):
            print "{pkg_name} already installed".format(pkg_name=pkg_name)
        else:
            pkg.mark_install()

    try:
        cache.commit()
    except Exception, arg:
        print >> sys.stderr, "Sorry, package installation failed [{err}]".format(err=str(arg))

def cloneOpenCV():
    pass

def cloneContrib():
    pass

def checkPaths():
    return os.path.exists('opencv'), os.path.exists('contrib')

if __name__ == '__main__':
    if(checkOpencv() and (not (sys.argv[1] == '-force'))):
        print ('OpenCV is installed correctly, nothing to do')
    else:
        installPackages()
        gotOpenCV, gotContrib = checkPaths()
        if (not gotOpenCV):
            cloneOpenCV()
        if (not gotContrib):
            cloneContrib()
        os.mkdir('build')
        os.chdir('build')
        system('cmake  -D CMAKE_BUILD_TYPE=RELEASE -DBUILD_PYTHON_SUPPORT=ON -DBUILD_NEW_PYTHON_SUPPORT=ON -DCMAKE_INSTALL_PREFIX=/usr/local ../opencv/')
        system('make -j5')
        system('cmake -DBUILD_PYTHON_SUPPORT=ON -DBUILD_NEW_PYTHON_SUPPORT=ON OPENCV_EXTRA_MODULES_PATH=../contrib/opencv_contrib/modules ../opencv/')
        system('make -j5')
        system('sudo make install')
