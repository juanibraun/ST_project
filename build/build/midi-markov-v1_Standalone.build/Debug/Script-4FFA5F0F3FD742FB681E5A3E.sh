#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/juanbraun/dev/ST_project/build
  /Users/juanbraun/dev/ST_project/build/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide pkginfo "Standalone Plugin" /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/midi-markov-v1_Standalone/PkgInfo
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/juanbraun/dev/ST_project/build
  /Users/juanbraun/dev/ST_project/build/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide pkginfo "Standalone Plugin" /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/midi-markov-v1_Standalone/PkgInfo
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/juanbraun/dev/ST_project/build
  /Users/juanbraun/dev/ST_project/build/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide pkginfo "Standalone Plugin" /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/midi-markov-v1_Standalone/PkgInfo
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/juanbraun/dev/ST_project/build
  /Users/juanbraun/dev/ST_project/build/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide pkginfo "Standalone Plugin" /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/midi-markov-v1_Standalone/PkgInfo
fi

