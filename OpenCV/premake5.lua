workspace "Lockotron"
   configurations { "default", "yocto-galileo" }

project "GetPicture"
  location "GetPicture/"
  kind "ConsoleApp"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"
  files { "*GetPicture/*.h", "GetPicture/*.cpp" }
  libdirs { "/usr/local/lib" }
  links { "opencv_highgui", "opencv_objdetect", "opencv_video", "opencv_core", "opencv_imgproc", "opencv_imgcodecs", "opencv_videoio"}

project "Trainer"
  location "Trainer/"
  kind "ConsoleApp"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"
  files { "Trainer/*.h", "Trainer/*.cpp" }
  filter "configurations:default"
    libdirs { "/usr/local/lib" }
    links { "opencv_highgui", "opencv_contrib", "opencv_core", "opencv_imgproc"}
  filter "configurations:yocto-galileo"
    libdirs { "/usr/lib" }
    links { "opencv_highgui", "opencv_contrib", "opencv_core", "opencv_imgproc"}

project "GetSamples"
  location "GetSamples/"
  kind "ConsoleApp"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"
  files { "GetSamples/*.h", "GetSamples/*.cpp" }
  libdirs { "/usr/local/lib" }
  links { "opencv_highgui", "opencv_objdetect", "opencv_video", "opencv_core", "opencv_imgproc", "opencv_videoio"}

project "Recognizer"
  location "Recognizer/"
  kind "ConsoleApp"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"
  files { "Recognizer/*.h", "Recognizer/*.cpp" }
  filter "configurations:default"
    libdirs { "/usr/local/lib" }
    links { "opencv_highgui", "opencv_contrib", "opencv_core", "opencv_imgproc"}
  filter "configurations:yocto-galileo"
    libdirs { "/usr/lib" }
    links { "opencv_highgui", "opencv_contrib", "opencv_core", "opencv_imgproc"}

project "testcv2"
  location "testcv2/"
  kind "ConsoleApp"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"
  files { "testcv2/*.h", "testcv2/*.cpp" }
  filter "configurations:default"
    libdirs { "/usr/local/lib" }
    links { "opencv_contrib", "opencv_core", "opencv_imgproc"}
  filter "configurations:yocto-galileo"
    libdirs { "/usr/lib" }
    links { "opencv_contrib", "opencv_core", "opencv_imgproc"}
