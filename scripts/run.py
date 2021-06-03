sourceFile = './examples/FizzBuzz.jan'
flags = '--debug-stopwatch'


import os
import subprocess
binPath = os.path.join(os.path.dirname(__file__), '..', 'bin', 'janelle.exe')
os.system(binPath + ' ' + sourceFile + ' ' + flags)