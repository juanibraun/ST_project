#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/juanbraun/dev/ST_project/build/JUCE/tools
  echo Build\ all\ projects
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/juanbraun/dev/ST_project/build/JUCE/tools
  echo Build\ all\ projects
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/juanbraun/dev/ST_project/build/JUCE/tools
  echo Build\ all\ projects
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/juanbraun/dev/ST_project/build/JUCE/tools
  echo Build\ all\ projects
fi
