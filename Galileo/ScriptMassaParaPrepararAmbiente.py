#!/usr/bin/python

import apt
import sys
import os
import shutil
packages_to_install = ['build-essential', 'make', 'git', 'libgtk2.0-dev',
                       'pkg-config', 'libavcodec-dev', 'libavformat-dev',
                       'libswscale-dev', 'python-dev', 'python-numpy',
                       'libtbb2', 'libtbb-dev', 'libjpeg-dev', 'libpng12-dev',
                       'libtiff5-dev', 'libjasper-dev', 'libdc1394-22-dev']

n_tem_no_yocto = ['build-essential', 'libavcodec-dev', 'libavformat-dev',
                  'libswscale-dev', 'libtbb2', 'libtbb-dev', 'libjasper-dev',
                  'libdc1394-22-dev']
def checkOpencv():
    if (os.path.exists('/usr/local/include/opencv2/face')):
        import cv2
        if (cv2.__version__ >= '3.1.0-dev'):
            return True
    return False

def installPackages():
    print 'Checking apt-get status...'
    cache = apt.cache.Cache()
    cache.update()
    print 'Starting to install packages...'
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
    print 'Cloning opencv...'
    os.system('git clone https://github.com/Itseez/opencv.git')

def cloneContrib():
    print 'Cloning opencv_contrib...'
    os.system('git clone https://github.com/Itseez/opencv_contrib.git')

def checkPaths():
    return os.path.exists('opencv'), os.path.exists('opencv_contrib')

def main_script():
    installPackages()
    gotOpenCV, gotContrib = checkPaths()
    if (not gotOpenCV):
        cloneOpenCV()
    if (not gotContrib):
        cloneContrib()
    else:
        print "Updating opencv repository"
        os.chdir('opencv')
        os.system('git pull')
        os.chdir('..')
    if os.path.exists('build'):
        shutil.rmtree('build')
    else:
        print "Updating opencv_contrib repository"
        os.chdir('opencv_contrib')
        os.system('git pull')
        os.chdir('..')
    os.mkdir('build')
    os.chdir('build')
    os.system('cmake  -D CMAKE_BUILD_TYPE=RELEASE -DBUILD_PYTHON_SUPPORT=ON -DBUILD_NEW_PYTHON_SUPPORT=ON -DCMAKE_INSTALL_PREFIX=/usr/local ../opencv/')
    print 'Making opencv...'
    os.system('make -j5')
    os.system('cmake -DBUILD_PYTHON_SUPPORT=ON -DBUILD_NEW_PYTHON_SUPPORT=ON -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules ../opencv/')
    print 'Making opencv_contrib...'
    os.system('make -j5')
    print 'Installing opencv...'
    os.system('sudo make install')

if __name__ == '__main__':
    if ((len(sys.argv) == 1)):
        if(checkOpencv()):
            print ('OpenCV is installed correctly, nothing to do (use -f to force reinstallation)')
        else:
            main_script()
    else:
        if(checkOpencv() and (not (sys.argv[1] == '-f'))):
            print ('OpenCV is installed correctly, nothing to do (use -f to force reinstallation)')
        else:
            main_script()
