#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/juanbraun/dev/ST_project/build
  /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E copy /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/midi-markov-v1_Standalone/PkgInfo /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/Debug/Standalone/midi-markov-v1.app/Contents
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/juanbraun/dev/ST_project/build
  /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E copy /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/midi-markov-v1_Standalone/PkgInfo /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/Release/Standalone/midi-markov-v1.app/Contents
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/juanbraun/dev/ST_project/build
  /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E copy /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/midi-markov-v1_Standalone/PkgInfo /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/MinSizeRel/Standalone/midi-markov-v1.app/Contents
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/juanbraun/dev/ST_project/build
  /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E copy /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/JuceLibraryCode/midi-markov-v1_Standalone/PkgInfo /Users/juanbraun/dev/ST_project/build/midi-markov-v1_artefacts/RelWithDebInfo/Standalone/midi-markov-v1.app/Contents
fi

