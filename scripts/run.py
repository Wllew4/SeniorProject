sourceFile = './examples/FizzBuzz.jan'
flags = ''


import os
import subprocess
binPath = os.path.join(os.path.dirname(__file__), '..', 'bin', 'janelle.exe')
os.system(binPath + ' ' + sourceFile + ' ' + flags)