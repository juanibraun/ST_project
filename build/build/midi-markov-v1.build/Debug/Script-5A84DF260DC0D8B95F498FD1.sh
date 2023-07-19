#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/juanbraun/dev/ST_project/build
  /Users/juanbraun/dev/ST_project/build/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide header /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/Debug/Defs.txt /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/JuceHeader.h
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/juanbraun/dev/ST_project/build
  /Users/juanbraun/dev/ST_project/build/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide header /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/Release/Defs.txt /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/JuceHeader.h
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/juanbraun/dev/ST_project/build
  /Users/juanbraun/dev/ST_project/build/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide header /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/MinSizeRel/Defs.txt /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/JuceHeader.h
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/juanbraun/dev/ST_project/build
  /Users/juanbraun/dev/ST_project/build/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide header /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/RelWithDebInfo/Defs.txt /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/JuceHeader.h
fi

