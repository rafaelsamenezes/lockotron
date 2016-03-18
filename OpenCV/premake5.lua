workspace "Lockotron"
   configurations { "x64", "i586" }

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
  libdirs { "/usr/local/lib" }
  links { "opencv_highgui", "opencv_contrib", "opencv_core", "opencv_imgcodecs", "opencv_imgproc"}

project "Recognizer"
  location "Recognizer/"
  kind "ConsoleApp"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"
  files { "Recognizer/*.h", "Recognizer/*.cpp" }
  libdirs { "/usr/local/lib" }
  links { "opencv_highgui", "opencv_contrib", "opencv_core", "opencv_imgcodecs", "opencv_imgproc"}

project "testcv2"
  location "testcv2/"
  kind "ConsoleApp"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"
  files { "testcv2/*.h", "testcv2/*.cpp" }
  libdirs { "/usr/local/lib" }
  links { "opencv_contrib", "opencv_core", "opencv_imgcodecs", "opencv_imgproc"}
