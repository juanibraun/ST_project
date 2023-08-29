# ST_project
The aim of this project was to develop a plugin that was able to generate a second voice of a given melody. The first way is to repeat the melody as it is played originally with a given time delay, in this scenario the sum of the two voices could be considered a cannon. The second way is to generate the second voice via a Markov Chain that listens to the input melody and generates the second voice based on the rules configured in it. 

The plug-in was developed using the JUCE framework: https://github.com/juce-framework/JUCE and the markov library from professor Matthew Yee-King: https://github.com/yeeking/MarkovModelCPP
