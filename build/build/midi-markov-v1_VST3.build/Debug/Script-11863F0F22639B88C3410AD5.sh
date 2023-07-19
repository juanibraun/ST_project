#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/juanbraun/dev/ST_project/build
  /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E copy /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/midi-markov-v1_VST3/PkgInfo /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/Debug/VST3/midi-markov-v1.vst3/Contents
  cd /Users/juanbraun/dev/ST_project/build
  /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -Dsrc=/Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/Debug/VST3/midi-markov-v1.vst3 -P /Users/juanbraun/src/JUCE/extras/Build/CMake/checkBundleSigning.cmake
  cd /Users/juanbraun/dev/ST_project/build
  /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -Dsrc=/Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/Debug/VST3/midi-markov-v1.vst3 -Ddest=/Users/juanbraun/Library/Audio/Plug-Ins/VST3 -P /Users/juanbraun/src/JUCE/extras/Build/CMake/copyDir.cmake
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/juanbraun/dev/ST_project/build
  /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E copy /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/midi-markov-v1_VST3/PkgInfo /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/Release/VST3/midi-markov-v1.vst3/Contents
  cd /Users/juanbraun/dev/ST_project/build
  /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -Dsrc=/Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/Release/VST3/midi-markov-v1.vst3 -P /Users/juanbraun/src/JUCE/extras/Build/CMake/checkBundleSigning.cmake
  cd /Users/juanbraun/dev/ST_project/build
  /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -Dsrc=/Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/Release/VST3/midi-markov-v1.vst3 -Ddest=/Users/juanbraun/Library/Audio/Plug-Ins/VST3 -P /Users/juanbraun/src/JUCE/extras/Build/CMake/copyDir.cmake
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/juanbraun/dev/ST_project/build
  /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E copy /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/midi-markov-v1_VST3/PkgInfo /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/MinSizeRel/VST3/midi-markov-v1.vst3/Contents
  cd /Users/juanbraun/dev/ST_project/build
  /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -Dsrc=/Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/MinSizeRel/VST3/midi-markov-v1.vst3 -P /Users/juanbraun/src/JUCE/extras/Build/CMake/checkBundleSigning.cmake
  cd /Users/juanbraun/dev/ST_project/build
  /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -Dsrc=/Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/MinSizeRel/VST3/midi-markov-v1.vst3 -Ddest=/Users/juanbraun/Library/Audio/Plug-Ins/VST3 -P /Users/juanbraun/src/JUCE/extras/Build/CMake/copyDir.cmake
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/juanbraun/dev/ST_project/build
  /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E copy /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/midi-markov-v1_VST3/PkgInfo /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/RelWithDebInfo/VST3/midi-markov-v1.vst3/Contents
  cd /Users/juanbraun/dev/ST_project/build
  /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -Dsrc=/Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/RelWithDebInfo/VST3/midi-markov-v1.vst3 -P /Users/juanbraun/src/JUCE/extras/Build/CMake/checkBundleSigning.cmake
  cd /Users/juanbraun/dev/ST_project/build
  /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -Dsrc=/Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/RelWithDebInfo/VST3/midi-markov-v1.vst3 -Ddest=/Users/juanbraun/Library/Audio/Plug-Ins/VST3 -P /Users/juanbraun/src/JUCE/extras/Build/CMake/copyDir.cmake
fi

