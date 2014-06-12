#!/usr/bin/python

'''
Work with virtual machines managed by libvirt

depends: libvirt Python module
'''

# Import python libs
import os
import shutil
import subprocess
from xml.dom import minidom

# Import third party libs
try:
	import libvirt
	HAS_LIBVIRT = True
except ImportError:
	HAS_LIBVIRT = False
#import yaml

# Import salt libs
#import salt.utils
#from salt._compat import StringIO as _StringIO
#from salt.exceptions import CommandExecutionError

from ctypes import *

print 'Hello'
